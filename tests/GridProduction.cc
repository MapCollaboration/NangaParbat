//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/factories.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"

#include <LHAPDF/LHAPDF.h>
#include <sys/stat.h>
#include <fstream>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./GridProduction <report folder> <pdf/ff> <output>\n" << std::endl;
      exit(-10);
    }

  const std::string pf = argv[2];

  // Produce the folder with the grids
  NangaParbat::ProduceTMDGrid(argv[1], argv[3], pf);

  // ===========================================================================
  // Now start direct computation
  // Read configuration file
  const std::string RepFolder = argv[1];
  const YAML::Node config = YAML::LoadFile(RepFolder + "/tables/config.yaml");

  // Open LHAPDF set
  LHAPDF::PDF* dist = LHAPDF::mkPDF(config[pf + "set"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());

  // Rotate sets into the QCD evolution basis
  const auto RotDists = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(dist->xfxQ(x, mu)); };

  // Heavy-quark thresholds
  std::vector<double> Thresholds;
  const double Ci  = config["TMDscales"]["Ci"].as<double>();
  for (auto const& v : dist->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(dist->quarkThreshold(v));

  // Define x-space grid
  std::vector<apfel::SubGrid> vsg;
  for (auto const& sg : config["xgridpdf"])
    vsg.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
  const apfel::Grid g{vsg};

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedDists = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotDists, mu)};
  };

  // Tabulate collinear distributions
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabDists{EvolvedDists, 100, dist->qMin(), dist->qMax(), 3, Thresholds};

  // Build evolved TMD distributions
  const int    pto = config["PerturbativeOrder"].as<int>();
  const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };
  const auto CollDists = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabDists.Evaluate(mu); };

  std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> EvTMDs = BuildTmdPDFs(apfel::InitializeTmdObjectsLite(g, Thresholds),
                                                                                                                    CollDists, Alphas, pto, Ci);

  // b* prescription
  const std::function<double(double const&, double const&)> bs = NangaParbat::bstarMap.at(config["bstar"].as<std::string>());

  // Get report
  const YAML::Node rep = YAML::LoadFile(RepFolder + "/replica_0/Report.yaml");

  // Get parameterisation and sets of parameters
  NangaParbat::Parameterisation *NPFunc = NangaParbat::GetParametersation(rep["Parameterisation"].as<std::string>());

  // Get parameters
  const std::map<std::string, double> pars = rep["Parameters"].as<std::map<std::string, double>>();

  // Collect parameters in vector
  std::vector<double> vpars;
  for (auto const p : NPFunc->GetParameterNames())
    vpars.push_back(pars.at(p));

  // Set vector of parameters
  NPFunc->SetParameters(vpars);

  // Double exponential quadrature
  apfel::DoubleExponentialQuadrature DEObj{};

  // Test grid against direct calculation
  std::cout << "Start testing grids against direct calculation" << std::endl;

  // Create folder to store the output
  const std::string outdir = std::string(argv[3]) + "/testresults";
  mkdir(outdir.c_str(), ACCESSPERMS);
  std::cout << "Creating folder " + outdir << std::endl;
  std::cout << "\n";

  // Select flavour
  const int ifl = 2; // quark up

  // Values of Q to test
  std::vector<double> Qg
  {
    3.000000e+00, 7.000000e+00,
    2.800000e+01, 4.342641e+01, 6.000000e+01, 9.118760e+01,
    2.000000e+02, 2.466432e+02
    //1.100000e+03
  };

  // Values of x to test
  std::vector<double> xg
  {
    2.050000e-04, 8.070000e-03,
    1.750000e-02,
    0.1, 0.3, 0.5, 0.7
  };

  // Read in grid
  NangaParbat::TMDGrid* TMDs = NangaParbat::mkTMD(argv[3]);

  // Read grids and test interpolation
  for (int iq = 0; iq < (int) Qg.size(); iq++)
    {
      const double Q  = Qg[iq];
      const double Q2 = Q * Q;
      for (int ix = 0; ix < (int) xg.size(); ix++)
        {
          const double x  = xg[ix];

          // Values of kT
          const int nkT   = 50;
          const double kTmin = Q * 1e-4;
          const double kTmax = 0.5 * Q;
          // const double kTstp = exp( log( kTmax / kTmin ) / ( nkT - 1 ) );
          const double kTstp = (kTmax - kTmin)/ nkT;

          // bT-space TMD
          const auto xFb = [&] (double const& bT) -> double
          {
            return bT * QCDEvToPhys(EvTMDs(bs(bT, Q), Q, Q2).GetObjects()).at(ifl).Evaluate(x) * NPFunc->Evaluate(x, bT, Q2, (pf == "pdf" ? 0 : 1)) / (pf == "pdf" ? 1 : x * x);
          };
          const std::function<double(double const&)> txFb = [&] (double const& bT) -> double{ return xFb(bT); };

          // Fill vectors with grid interpolation and direct computation
          std::vector<double> gridinterp;
          std::vector<double> direct;
          for (double kT = kTmin; kT <= kTmax * ( 1 + 1e-5 ); kT += kTstp)
            {
              gridinterp.push_back(TMDs->Evaluate(x, kT, Q).at(ifl));
              direct.push_back(DEObj.transform(txFb, kT));
            }

          // YAML Emitter
          YAML::Emitter em;

          em << YAML::BeginMap;
          em << YAML::Key << "ifl" << YAML::Value << ifl;
          em << YAML::Key << "Q"   << YAML::Value << Q;
          em << YAML::Key << "x"   << YAML::Value << x;
          em << YAML::Key << "kT"  << YAML::Value << YAML::Flow << YAML::BeginSeq;
          for (double kT = kTmin; kT <= kTmax * ( 1 + 1e-5 ); kT += kTstp)
            em << kT;
          em << YAML::EndSeq;
          em << YAML::Key << "Grid interpolation" << YAML::Value << YAML::Flow << YAML::BeginSeq;
          for (int i = 0; i < (int) gridinterp.size(); i++)
            em << gridinterp[i];
          em << YAML::EndSeq;
          em << YAML::Key << "Direct calculation" << YAML::Value << YAML::Flow << YAML::BeginSeq;
          for (int i = 0; i < (int) direct.size(); i++)
            em << direct[i];
          em << YAML::EndSeq;
          em << YAML::Key << "Grid over direct" << YAML::Value << YAML::Flow << YAML::BeginSeq;
          for (int i = 0; i < (int) gridinterp.size(); i++)
            em << gridinterp[i] / direct[i];
          em << YAML::EndSeq;
          em << YAML::EndMap;

          // Produce output file
          std::ofstream fout(outdir + "/test_Q_" + std::to_string(Q) + "_x_" + std::to_string(x) + ".yaml");
          fout << em.c_str() << std::endl;
          fout.close();

          // ===================================================================

          /*
            // Try a convolution
            const auto conv = Convolution(TMDs, [] (double const&) -> std::vector<double> { return apfel::QCh2; });

            // Values of qT
            const int nqT   = 10;
            const double qTmin = Q * 1e-4;
            const double qTmax = 0.2 * Q;
            const double qTstp = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );
            std::vector<double> qTv;
            for (double qT = qTmin; qT <= qTmax * ( 1 + 1e-5 ); qT *= qTstp)
              std::cout << qT << "  " << qT * conv(x, x, Q, qT) << std::endl;
          */
        }
    }
  delete TMDs;
  return 0;
}
