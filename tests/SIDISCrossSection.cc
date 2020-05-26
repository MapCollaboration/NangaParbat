//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <math.h>
#include <LHAPDF/LHAPDF.h>
#include <apfel/apfelxx.h>
#include <yaml-cpp/yaml.h>
#include <stdlib.h>
#include <algorithm>

// b* prescription
double bstar(double const& b, double const& kappa = 1, bool const& css = true)
{
  const double b0 = 2 * exp( - apfel::emc);
  const double bmax = b0 / kappa;
  if (css)
    return b / sqrt( 1 + pow(b / bmax, 2) );
  else
    return b;
}

// mu* prescription
double mustar(double const& mu, double const& kappa = 1, bool const& css = true)
{
  const double b0 = 2 * exp( - apfel::emc);
  return b0 / bstar(b0 / mu, kappa, !css);
}

// Non-perturbative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double Q02 = 1;//3.2;
  const double g1  = 0;//0.4;
  const double g2  = 0;//0.035;
  return exp( - ( g1 + g2 * log(zetaf / Q02) / 2 ) * pow(b, 2) / 2 );
}

// Main program
int main()
{
  const bool css     = true;
  const double kappa = 1;
  const double Ci    = 1;
  const double Cf    = 1;

  // Open LHAPDF set
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF("MMHT2014nnlo68cl", 0);
  LHAPDF::PDF* distff  = LHAPDF::mkPDF("DSS14_NLO_PiSum", 0);

  // Heavy-quark thresholds
  std::vector<double> Thresholds;
  for (auto const& v : distpdf->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(distpdf->quarkThreshold(v));

  // Alpha_s (from PDFs)
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mustar(mu, kappa, css)); };

  // x-space grid (to setup APFEL++ computation)
  const apfel::Grid gpdf{{{100, 1e-6, 3}, {60, 1e-1, 3}, {50, 6e-1, 3}, {50, 8e-1, 3}}};
  const apfel::Grid gff{{{60, 1e-1, 3}, {50, 6e-1, 3}, {50, 8e-1, 3}}};

  // Rotate PDF set into the QCD evolution basis
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x, mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distff->xfxQ(x, mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&gpdf] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(gpdf, RotPDFs, mu)};
  };
  const auto EvolvedFFs = [=,&gff] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(gff, RotFFs, mu)};
  };

  // Tabulate collinear PDFs and FFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, 0.5, distpdf->qMax(), 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mustar(mu, kappa, css)); };

  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabFFs{EvolvedFFs, 100, 0.5, distff->qMax(), 3, Thresholds};
  const auto CollFFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabFFs.Evaluate(mustar(mu, kappa, css)); };

  // Initialize TMD objects
  const auto TmdObjPDF = apfel::InitializeTmdObjectsLite(gpdf, Thresholds);
  const auto TmdObjFF  = apfel::InitializeTmdObjectsLite(gff, Thresholds);

  // Alpha_em
  const double aref = 0.007555310522369057;
  const double Qref = 91.15348061918276;
  const bool   arun = false;
  const apfel::AlphaQED alphaem{aref, Qref, Thresholds, {0, 0, 1.777}, 0};

  // Perturbative order
  int PerturbativeOrder = 3;

  // Kinematics
  const double Vs = 300;    // C.M.E.
  const std::vector<double> ybv{0}; //Rapidity vector
  const std::vector<double> Qbv{10}; // Invariant mass vector
  const std::vector<double> qTv
  {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    45, 50, 55, 60, 65, 70, 75, 80, 85, 90,
    95, 100};

  // Double exponential quadrature
  apfel::DoubleExponentialQuadrature DEObj{};

  // Timer
  apfel::Timer t;

  // Build evolved TMD PDFs
  const auto EvTMDPDFs = BuildTmdPDFs(TmdObjPDF, CollPDFs, Alphas, PerturbativeOrder, Ci);
  const auto EvTMDFFs  = BuildTmdFFs(TmdObjFF, CollFFs, Alphas, PerturbativeOrder, Ci);

  // Get hard-factor function
  const auto Hf = HardFactor("SIDIS", TmdObjPDF, Alphas, PerturbativeOrder, Cf);

  for (auto const& Qb : Qbv)
    {
      for (auto const& yb : ybv)
        {
          // Renormalisation scales
          const double muf   = Cf * Qb;
          const double zetaf = Qb * Qb;

          // Number of active flavours at 'muf'
          const int nf = apfel::NF(muf, Thresholds);

          // Compute Bjorken 'x1' and 'x2'
          const double xi = exp(yb);
          const double x1 = Qb * xi / Vs;
          const double x2 = Qb / xi / Vs;

          // Electromagnetic coupling squared
          const double aem2 = pow((arun ? alphaem.Evaluate(Qb) : aref), 2);

          // Compute the hard factor
          const double hcs = Hf(muf);

          // Construct the TMD luminosity in b space to be fed to be
          // trasformed in qT space.
          const std::function<double(double const&)> TMDLumib = [=] (double const& b) -> double
          {
            // Get Evolved TMD PDFs and rotate them into the physical
            // basis
            const std::map<int,apfel::Distribution> xF = QCDEvToPhys(EvTMDPDFs(bstar(b, kappa, css), muf, zetaf).GetObjects());
            const std::map<int,apfel::Distribution> xD = QCDEvToPhys(EvTMDFFs(bstar(b, kappa, css), muf, zetaf).GetObjects());

            // Combine TMDs through the EW charges
            double lumi = 0;
            for (int i = 1; i <= nf; i++)
              lumi += apfel::QCh2[i-1] * ( xF.at(i).Evaluate(x1) * xD.at(i).Evaluate(x2) + xF.at(-i).Evaluate(x1) * xD.at(-i).Evaluate(x2) );

            // Combine all pieces and return
            return b * lumi * fNP(x1, b, zetaf) * fNP(x2, b, zetaf);
          };

          for (auto const& qT : qTv)
            {
              // Perform Fourier transform and obtain cross section
              const auto prefactor = [=] (double const& qTc) -> double { return apfel::ConvFact * qTc * 8 * M_PI * aem2 * hcs / pow(Qb, 3) / 9; };

              // Alternative integration
              const double de = prefactor(qT) * DEObj.transform(TMDLumib, qT);

              // Print results
              std::cout << std::scientific << Qb << "  " << yb << "  " << qT << "  " << de << std::endl;
            }
        }
    }
  std::cout << std::endl;
  t.stop();

  delete distpdf;
  return 0;
}
