//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/utilities.h"
#include "NangaParbat/twobodyphasespace.h"

#include <LHAPDF/LHAPDF.h>
#include <apfel/apfelxx.h>

// Non-perturbative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double g1 = 0.02;
  const double g2 = 0.5;
  const double Q0 = 1.6;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

// Main program
int main()
{
  // Allocate "FastInterface" object
  const YAML::Node config = YAML::LoadFile("../cards/config.yaml");

  // Datafiles
  const NangaParbat::DataHandler DHObj{"qTintegration_test", YAML::LoadFile("../data/TestData/Table2.yaml")};

  // Now start direct computation
  // Open LHAPDF set
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());

  // Heavy-quark thresholds
  std::vector<double> Thresholds;
  for (auto const& v : distpdf->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(distpdf->quarkThreshold(v));

  // Alpha_s.
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

  // Perturbative order.
  const int PerturbativeOrder = config["PerturbativeOrder"].as<int>();

  // Initial scale-variation factor;
  const double Ci = config["TMDscales"]["Ci"].as<double>();

  // Final scale-variation factor;
  const double Cf = config["TMDscales"]["Cf"].as<double>();

  // x-space grid.
  std::vector<apfel::SubGrid> vsg;
  for (auto const& sg : config["xgridpdf"])
    vsg.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
  const apfel::Grid g{vsg};

  // Rotate PDF set into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)};
  };

  // Tabulate PDFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 50, 1, 100000, 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

  // Initialize TMD objects.
  const auto TmdObj = InitializeTmdObjects(g, Thresholds);

  // Get evolution factors.
  const auto QuarkEvolFactor = QuarkEvolutionFactor(TmdObj, Alphas, PerturbativeOrder, Ci);

  // Match TMD PDFs
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, CollPDFs, Alphas, PerturbativeOrder, Ci);

  // Alpha_em
  const apfel::AlphaQED alphaem{config["alphaem"]["aref"].as<double>(), config["alphaem"]["Qref"].as<double>(), Thresholds, {0, 0, 1.777}, 0};

  // Retrieve kinematics
  const NangaParbat::DataHandler::Kinematics kin = DHObj.GetKinematics();
  const double                   Vs       = kin.Vs;       // C.M.E.
  const std::pair<double,double> yb       = kin.var2b;    // Rapidity interval
  const std::pair<double,double> Qb       = kin.var1b;    // Invariant mass interval
  const std::vector<double>      qTv      = kin.qTv;      // Transverse momentum bin bounds
  const double                   pTMin    = kin.pTMin;    // Minimum pT of the final-state leptons
  const std::pair<double,double> etaRange = kin.etaRange; // Allowed range in eta of the final-state leptons

  // Hard scale
  const double Q = ( Qb.first + Qb.second ) / 2;

  // Rapidity
  const double y = ( yb.first + yb.second ) / 2;

  // TMD scales
  const double muf   = Cf * Q;
  const double zetaf = Q * Q;

  // Construct function that returns evolved TMDs including the
  // non-perturbative part. This can be tabulated in b.
  const auto EvolvedTMDPDFs = [=] (double const& b) -> apfel::Set<apfel::Distribution>
  {
    const double bs = NangaParbat::bstar(b, 0);
    return fNP(0, b, zetaf) * QuarkEvolFactor(bs, muf, zetaf) * MatchedTMDPDFs(bs);
  };

  // Tabulate input TMDs in the impact parameter to make the
  // integral faster.
  const auto TabFunc    = [] (double const& b) -> double{ return log(b); };
  const auto InvTabFunc = [] (double const& fb) -> double{ return exp(fb); };
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabEvolvedTMDPDFs{EvolvedTMDPDFs, 50, 5e-5, 10, 3, {}, TabFunc, InvTabFunc};

  // EW charges
  const std::vector<double> Bq = apfel::ElectroWeakCharges(Q, true);

  // Bjorken variables
  const double x1 = Q * exp(-y) / Vs;
  const double x2 = Q * exp(y) / Vs;

  // Compute hard coefficient, including the other kinematic
  // factors.
  const double hcs = apfel::HardFactorDY(PerturbativeOrder, Alphas(muf), apfel::NF(muf, Thresholds), Cf);

  // Electromagnetic coupling squared
  const double aem2 = pow((config["alphaem"]["run"].as<bool>() ? alphaem.Evaluate(Q) : config["alphaem"]["ref"].as<double>()), 2);

  // Ogata quadrature object with default settings.
  apfel::OgataQuadrature bintegrand{};

  // Phase-space reduction factor
  NangaParbat::TwoBodyPhaseSpace ps{pTMin, etaRange.first, etaRange.second};

  // Define qT-distribution function using a DoubleObject
  const auto Lumi = [=] (double const& bs) -> apfel::DoubleObject<apfel::Distribution>
  {
    const std::map<int,apfel::Distribution> xF = QCDEvToPhys((QuarkEvolFactor(bs, muf, zetaf) * MatchedTMDPDFs(bs)).GetObjects());
    apfel::DoubleObject<apfel::Distribution> L{};
    for (int i = 1; i <= 5; i++)
      {
        L.AddTerm({Bq[i-1], xF.at(i), xF.at(-i)});
        L.AddTerm({Bq[i-1], xF.at(-i), xF.at(i)});
      }
    return L;
  };
  const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> TabLumi{Lumi, 50, 5e-5, 1.1, 3, {}, TabFunc, InvTabFunc};

  // Define qT-distribution function
  const auto qTdist = [&] (double const& qT) -> double
  {
    // Construct the TMD luminosity in b scale to be fed to be
    // trasformed in qT space.
    const auto TMDLumibNew = [=] (double const& b) -> double{ return b * TabLumi.EvaluatexzQ(x1, x2, NangaParbat::bstar(b, 0)) * fNP(0, b, zetaf) * fNP(0, b, zetaf) / 2; };
    return apfel::ConvFact * qT * 8 * M_PI * aem2 * hcs * ps.PhaseSpaceReduction(Q, y, qT) * bintegrand.transform(TMDLumibNew, qT) / pow(Q, 3) / 9;
  };

  apfel::Timer t;
  std::cout << std::scientific;
  std::cout << "\nNumerical computation of the integral in qT" << std::endl;
  std::cout << "    [qTmin:qTmax] [GeV]      "
            << "   sigma      "
            << std::endl;
  const apfel::Integrator IntQt{qTdist};
  for (int iqT = 0; iqT < (int) qTv.size() - 1; iqT++)
    std::cout << "[" << qTv[iqT] << ":" << qTv[iqT+1] << "]: " << IntQt.integrate(qTv[iqT], qTv[iqT+1], 1e-5) << std::endl;
  std::cout << "\n";
  t.stop();

  // Ogata quadrature object with default settings.
  apfel::OgataQuadrature qTintegrand{1};
  const auto qTPrimitive = [&] (double const& qT, bool const& lower) -> double
  {
    // Construct the TMD luminosity in b scale to be fed to be
    // trasformed in qT space.
    const auto TMDLumibPrim = [=] (double const& b) -> double{ return TabLumi.EvaluatexzQ(x1, x2, NangaParbat::bstar(b, 0)) * fNP(0, b, zetaf) * fNP(0, b, zetaf) / 2; };
    const double DqT    = (lower ? 1 : -1); // This assumes that the bin-width is equal to 2 GeV
    const double PSRed  = ps.PhaseSpaceReduction(Q, y, qT);
    const double dPSRed = ps.DerivePhaseSpaceReduction(Q, y, qT);
    return apfel::ConvFact * qT * 8 * M_PI * aem2 * hcs * ( PSRed + dPSRed * DqT ) * qTintegrand.transform(TMDLumibPrim, qT) / pow(Q, 3) / 9;
  };

  t.start();
  std::cout << "\nAnalytic computation of the integral in qT" << std::endl;
  std::cout << "    [qTmin:qTmax] [GeV]      "
            << "   sigma      "
            << std::endl;
  for (int iqT = 0; iqT < (int) qTv.size() - 1; iqT++)
    std::cout << "[" << qTv[iqT] << ":" << qTv[iqT+1] << "]: "
              << qTPrimitive(qTv[iqT+1], false) - qTPrimitive(qTv[iqT], true) << "  "
              << std::endl;
  std::cout << "\n";
  t.stop();

  // Now produce interpolation grid and test it against the methods
  // above.
  /*
  const NangaParbat::FastInterface FIObj{config};
  const std::vector<YAML::Emitter> tab = FIObj.ComputeTables({DHObj}, NangaParbat::bstar);
  std::ofstream fout("../tables/" + YAML::Load(tab[0].c_str())["name"].as<std::string>() + ".yaml");
  fout << tab[0].c_str() << std::endl;
  fout.close();
  const NangaParbat::ConvolutionTable CTable{YAML::Load(tab[0].c_str())};
  */
  const NangaParbat::ConvolutionTable CTable{YAML::LoadFile("../tables/qTintegration_test.yaml")};
  const std::vector<double> Conv = CTable.GetPredictions(fNP);
  t.start();
  std::cout << "\nGrid computation of the integral in qT" << std::endl;
  std::cout << "    [qTmin:qTmax] [GeV]      "
            << "   sigma      "
            << std::endl;
  for (int iqT = 0; iqT < (int) qTv.size() - 1; iqT++)
    std::cout << "[" << qTv[iqT] << ":" << qTv[iqT+1] << "]: "
              << Conv[iqT] << "  "
              << std::endl;
  std::cout << "\n";
  t.stop();
  std::cout << "\n";

  return 0;
}

