//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#include <NangaParbat/bstar.h>
#include <NangaParbat/nonpertfunctions.h>
#include "NangaParbat/createstructgrid.h"
#include "NangaParbat/structgrid.h"
#include "NangaParbat/factories.h"

#include <LHAPDF/LHAPDF.h>
#include <apfel/apfelxx.h>
#include <yaml-cpp/yaml.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 5 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./FUUTGridProduction <main fit directory with TMD grids> <name of TMD PDF set> <name of TMD FF set> <output grid name> <[optional] replica ID>\n" << std::endl;
      exit(-10);
    }

  // Set replica ID, if it is specified
  std::string rID;
  if (argv[5])
    rID = argv[5];
  else
    rID = "none";

  // Produce grids and their folder
  // NangaParbat::ProduceStructGrid(argv[1], argv[2], argv[3], argv[4], rID);

  // ===========================================================================
  // Start testing grid against direct calculation
  // ===========================================================================

  // Create directory to store the output, if not already there
  const std::string outdir = "test_" + std::string(argv[4]);
  mkdir(outdir.c_str(), ACCESSPERMS);
  std::cout << "Creating folder " + outdir << std::endl;
  std::cout << "\n";

  // *************
  // Read configuration file
  const std::string RepFolder = argv[1];
  const YAML::Node config = YAML::LoadFile(RepFolder + "/tables/config.yaml");

  // Perturbative order
  const int PerturbativeOrder = config["PerturbativeOrder"].as<int>();

  // Scale-variation factors
  const double Ci = config["TMDscales"]["Ci"].as<double>();
  const double Cf = config["TMDscales"]["Cf"].as<double>();

  // Open LHAPDF sets
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());
  LHAPDF::PDF* distff  = LHAPDF::mkPDF(config["ffset"]["name"].as<std::string>(),  config["ffset"]["member"].as<int>());

  // Get heavy-quark thresholds from the PDF LHAPDF set
  std::vector<double> ThresholdsPDF;
  for (auto const& v : distpdf->flavors())
    if (v > 0 && v < 7)
      ThresholdsPDF.push_back(distpdf->quarkThreshold(v));

  // Get heavy-quark thresholds from the FF LHAPDF set
  std::vector<double> ThresholdsFF;
  for (auto const& v : distff->flavors())
    if (v > 0 && v < 7)
      ThresholdsFF.push_back(distff->quarkThreshold(v));

  // Alpha_s (from PDFs and FFs)
  const auto AlphasPDF = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };
  const auto AlphasFF  = [&] (double const& mu) -> double{ return distff->alphasQ(mu); };

  // Setup APFEL++ x-space grid for PDFs
  std::vector<apfel::SubGrid> vsgp;
  for (auto const& sg : config["xgridpdf"])
    vsgp.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
  const apfel::Grid gpdf{vsgp};

  // Setup APFEL++ x-space grid for FFs
  std::vector<apfel::SubGrid> vsgf;
  for (auto const& sg : config["xgridff"])
    vsgf.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
  const apfel::Grid gff{vsgf};

  // Rotate PDF set into the QCD evolution basis
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x, mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distff->xfxQ(x, mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&gpdf] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, ThresholdsPDF)}, DistributionMap(gpdf, RotPDFs, mu)};
  };
  const auto EvolvedFFs = [=,&gff] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, ThresholdsPDF)}, DistributionMap(gff, RotFFs, mu)};
  };

  // Tabulate collinear PDFs and FFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, 0.5, distpdf->qMax(), 3, ThresholdsPDF};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabFFs{EvolvedFFs, 100, 0.5, distff->qMax(), 3, ThresholdsPDF};
  const auto CollFFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabFFs.Evaluate(mu); };

  // Initialize TMD objects
  const auto TmdObjPDF = apfel::InitializeTmdObjectsLite(gpdf, ThresholdsPDF);
  const auto TmdObjFF  = apfel::InitializeTmdObjectsLite(gff,  ThresholdsPDF);

  // Build evolved TMD PDFs and FFs
  const auto EvTMDPDFs = BuildTmdPDFs(TmdObjPDF, CollPDFs, AlphasPDF, PerturbativeOrder, Ci);
  const auto EvTMDFFs  = BuildTmdFFs(TmdObjFF, CollFFs, AlphasFF, PerturbativeOrder, Ci);

  // Functions used for the tabulation
  const auto TabFunc    = [] (double const& b) -> double{ return log(b); };
  const auto InvTabFunc = [] (double const& fb) -> double{ return exp(fb); };

  // Get report
  const YAML::Node rep = YAML::LoadFile(RepFolder + "/replica_105/Report.yaml");

  // Get parameterisation
  NangaParbat::Parameterisation* fNP = NangaParbat::GetParametersation(rep["Parameterisation"].as<std::string>());

  // Get parameters
  const std::map<std::string, double> pars = rep["Parameters"].as<std::map<std::string, double>>();

  // Collect parameters in vector
  std::vector<double> vpars;
  for (auto const& p : fNP->GetParameterNames())
    vpars.push_back(pars.at(p));

  // Set vector of parameters
  fNP->SetParameters(vpars);

  // Apfel timer
  apfel::Timer t;
  apfel::SetVerbosityLevel(0);

  // Read Structure Function in grid (repl. 105)
  NangaParbat::StructGrid* SFs = NangaParbat::mkSF(argv[4], argv[1], 105);

  // Read Kinematics
  YAML::Node kin = YAML::LoadFile("KinematicsFUUT.yaml");

  // Kinematics
  const std::vector<double> qTv = kin["qToQ"].as<std::vector<double>>(); // not used at the moment
  const std::vector<double> Qv  = kin["Q"].as<std::vector<double>>();
  const std::vector<double> xv  = kin["x"].as<std::vector<double>>();
  const std::vector<double> zv  = kin["z"].as<std::vector<double>>();

  // Test grid against direct calculation
  std::cout << "Start testing grids against direct calculation ... " << std::endl;

  // Read grids and test interpolation
  for (int iQ = 0; iQ < (int) Qv.size(); iQ++)
    {
      // value of Q
      const double Q  = Qv[iQ];

      for (int ix = 0; ix < (int) xv.size(); ix++)
        {
          // value of x
          const double x  = xv[ix];

          for (int iz = 0; iz < (int) zv.size(); iz++)
            {
              // value of z
              const double z  = zv[iz];

              // Values of qT
              const double qTmin = Q * 1e-4;
              const double qTmax = Q;
              const int    nqT   = 50;
              const double qTstp = (qTmax - qTmin)/ nqT;

              // The mesh value h can be adjusted according to qT (TODO)
              apfel::OgataQuadrature DEObj{0, 1e-9, 0.00001};

              // Renormalisation and rapidity scales
              const double mu   = Cf * Q;
              const double zeta = Q * Q;

              // EW charges
              const std::vector<double> Bq = apfel::QCh2;

              // Number of active flavours at mu
              const int nf = apfel::NF(mu, ThresholdsPDF);

              // Define kT-distribution function for direct calculation
              const std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> Lumib = [=] (double const& bs) -> apfel::DoubleObject<apfel::Distribution>
              {
                // Get Evolved TMD PDFs and FFs and rotate them into the physical basis.
                const std::map<int, apfel::Distribution> xF = QCDEvToPhys(EvTMDPDFs(bs, mu, zeta).GetObjects());
                const std::map<int, apfel::Distribution> xD = QCDEvToPhys(EvTMDFFs(bs, mu, zeta).GetObjects());

                // Luminosity
                apfel::DoubleObject<apfel::Distribution> L{};
                for (int i = 1; i <= nf; i++)
                  {
                    L.AddTerm({Bq[i-1], xF.at(+i), xD.at(+i)});
                    L.AddTerm({Bq[i-1], xF.at(-i), xD.at(-i)});
                  }
                return L;
              };

              // Perturbative contribution in b-space. We know a priori that
              // this is enclosed bewteen bmin and bmax. Include an overflow
              // (and underflow) by a 20% to avoid interpolation problems.
              const double overflow = 1.2;
              const double bmin = NangaParbat::bstarmin(0.00001, Q) / overflow;
              const double bmax = NangaParbat::bstarmin(10, Q) * overflow;

              const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> tLumib{Lumib, 200, bmin, bmax, 3, {}, TabFunc, InvTabFunc};

              // Function in bT space
              const std::function<double(double const&)> bInt = [=] (double const& b) -> double
              {
                double bTintegrand = b * fNP->Evaluate(x, b, zeta, 0) * fNP->Evaluate(z, b, zeta, 1) / z / z * tLumib.EvaluatexzQ(x, z, NangaParbat::bstarmin(b, Q));

                return bTintegrand;
              };

              // Initialize vectors
              std::vector<double> gridinterp;
              std::vector<double> direct;

              // Fill vectors with grid interpolation and direct computation
              for (double qT = qTmin; qT <= qTmax * ( 1 + 1e-5 ); qT += qTstp)
                {
                  // Grid interpolation
                  gridinterp.push_back(SFs->Evaluate(x,z, qT, Q));

                  // Direct calculation
                  direct.push_back(DEObj.transform(bInt, qT)/ z / (2 * M_PI));
                }

              // **************
              // YAML Emitter
              YAML::Emitter em;

              em << YAML::BeginMap;
              em << YAML::Key << "Q"   << YAML::Value << Q;
              em << YAML::Key << "x"   << YAML::Value << x;
              em << YAML::Key << "z"   << YAML::Value << z;
              em << YAML::Key << "qT"  << YAML::Value << YAML::Flow << YAML::BeginSeq;
              for (double qT = qTmin; qT <= qTmax * ( 1 + 1e-5 ); qT += qTstp)
                em << qT;
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
              std::ofstream fout(outdir + "/SFfuut_Q_" + std::to_string(Q) + "_x_" + std::to_string(x) + "_z_"  + std::to_string(z) + ".yaml");
              fout << em.c_str() << std::endl;
              fout.close();
            }
        }
    }

  delete distpdf;
  delete distff;
  delete fNP;
  delete SFs;

  return 0;
}
