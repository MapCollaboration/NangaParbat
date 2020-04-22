//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/factories.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"

#include <LHAPDF/LHAPDF.h>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateGrid <report folder> <output>\n" << std::endl;
      exit(-10);
    }

  // Produce the folder with the grids
  //NangaParbat::ProduceTMDGrid(argv[1], argv[2]);

  // =================================================================
  // Now start direct computation
  // Read configuration file
  const std::string RepFolder = argv[1];
  const YAML::Node config = YAML::LoadFile(RepFolder + "/tables/config.yaml");

  // Open LHAPDF set
  LHAPDF::PDF* dist = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());

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

  //  Test grid against direct calculation
  const int ifl   = 2;
  const double x  = 0.1111;
  const double kT = 5;
  const double Q  = 100;
  const double Q2 = Q * Q;

  // bT-space TMD
  const auto xFb = [&] (double const& bT) -> double { return bT * QCDEvToPhys(EvTMDs(bs(bT, Q), Q, Q2).GetObjects()).at(ifl).Evaluate(x) * NPFunc->Evaluate(x, bT, Q2, 0); };
  const std::function<double(double const&)> txFb = [&] (double const& bT) -> double{ return xFb(bT); };

  // Read in grid
  NangaParbat::TMDGrid* TMDs = NangaParbat::mkTMD(argv[2]);

  std::cout << std::scientific;
  std::cout << "\nGrid / Direct:   xf_" << ifl << "(x = " << x << ", kT = " << kT << " GeV, Q = " << Q << " GeV) = "
            << TMDs->Evaluate(x, kT, Q).at(ifl) / DEObj.transform(txFb, kT) << std::endl;
  //std::cout << "Direct: xf_" << ifl << "(x = " << x << ", kT = " << kT << " GeV, Q = " << Q << " GeV) = " << DEObj.transform(txFb, kT) << std::endl;
  std::cout << "\n";
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
  delete TMDs;
  return 0;
}
