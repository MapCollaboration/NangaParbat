//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <math.h>
#include <LHAPDF/LHAPDF.h>
#include <apfel/apfelxx.h>
#include <yaml-cpp/yaml.h>

// b* prescription
double bstar(double const& b, double const& Q)
{
  const double bmax = 2 * exp( - apfel::emc);
  return b / sqrt( 1 + pow(b / bmax, 2) );
}

// Non-perturnative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double g1 = 0.2;
  const double g2 = 0.5;
  const double Q0 = 1.6;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

// Main program
int main()
{
  // Read configuration file
  const YAML::Node config = YAML::LoadFile("configDrellYan.yaml");

  // Open LHAPDF set
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());

  // Heavy-quark thresholds
  std::vector<double> Thresholds;
  for (auto const& v : distpdf->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(distpdf->quarkThreshold(v));

  // Alpha_s (from PDFs)
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

  // x-space grid (to setup APFEL++ computation)
  std::vector<apfel::SubGrid> vsg;
  for (auto const& sg : config["xgridpdf"])
    vsg.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
  const apfel::Grid g{vsg};

  // Rotate PDF set into the QCD evolution basis
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)};
  };

  // Tabulate collinear PDFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, distpdf->qMin(), distpdf->qMax(), 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

  // Initialize TMD objects
  const auto TmdObj = apfel::InitializeTmdObjects(g, Thresholds);

  // Build evolved TMD PDFs
  const auto EvTMDPDFs = BuildTmdPDFs(TmdObj, CollPDFs, Alphas, config["PerturbativeOrder"].as<int>(), config["TMDscales"]["Ci"].as<double>());

  // Alpha_em
  const apfel::AlphaQED alphaem{config["alphaem"]["aref"].as<double>(), config["alphaem"]["Qref"].as<double>(), Thresholds, {0, 0, 1.777}, 0};

  // Final-scale variation factor
  const double Cf = config["TMDscales"]["Cf"].as<double>();

  // Timer
  apfel::Timer t;

  // Kinematics
  const double Vs = 13000;    // C.M.E.
  const double yb = 0;        // Rapidity
  const double Qb = 91.2;     // Invariant mass

  // Ogata-quadrature object of degree zero (do not integrate in qT).
  apfel::OgataQuadrature OgataObj{};

  // Renormalisation scales
  const double muf   = Cf * Qb;
  const double zetaf = Qb * Qb;

  // Number of active flavours at 'muf'
  const int nf = apfel::NF(muf, Thresholds);

  // EW charges
  const std::vector<double> Bq = apfel::ElectroWeakCharges(Qb, true);

  // Compute Bjorken 'x1' and 'x2'
  const double xi = exp(yb);
  const double x1 = Qb * xi / Vs;
  const double x2 = Qb / xi / Vs;

  // Electromagnetic coupling squared
  const double aem2 = pow((config["alphaem"]["run"].as<bool>() ? alphaem.Evaluate(Qb) : config["alphaem"]["ref"].as<double>()), 2);

  // Compute the hard factor
  const double hcs = apfel::HardFactorDY(config["PerturbativeOrder"].as<int>(), Alphas(muf), nf, Cf);

  // Construct the TMD luminosity in b space to be fed to be
  // trasformed in qT space.
  const auto TMDLumib = [=] (double const& b) -> double
  {
    // Get Evolved TMD PDFs and rotate them into the physical
    // basis
    const std::map<int,apfel::Distribution> xF = QCDEvToPhys(EvTMDPDFs(bstar(b, Qb), muf, zetaf).GetObjects());

    // Combine TMDs through the EW charges
    double lumi = 0;
    for (int i = 1; i <= nf; i++)
      lumi += Bq[i-1] * ( xF.at(i).Evaluate(x1) * xF.at(-i).Evaluate(x2) + xF.at(-i).Evaluate(x1) * xF.at(i).Evaluate(x2) );

    // Combine all pieces and return
    return b * lumi * fNP(x1, b, zetaf) * fNP(x2, b, zetaf);
  };

  // Loop over the qT-bin bounds
  const int nqT = 100;
  const double qTmin = 0.01;
  const double qTmax = 50;
  const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );

  std::cout << "\n  qT [GeV]     cross-sect." << std::endl;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      // Perform Fourier transform and obtain cross section
      const double prediction = apfel::ConvFact * qT * 8 * M_PI * aem2 * hcs * OgataObj.transform(TMDLumib, qT) / pow(Qb, 3) / 9;

      // Print results
      std::cout << std::scientific << qT << "  " << prediction << std::endl;
      qT *= qTstep;
    }
  std::cout << std::endl;
  t.stop();

  delete distpdf;
  return 0;
}
