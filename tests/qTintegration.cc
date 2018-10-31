//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <apfel/grid.h>
#include <apfel/timer.h>
#include <apfel/alphaqcd.h>
#include <apfel/constants.h>
#include <apfel/tmdbuilder.h>
#include <apfel/rotations.h>
#include <apfel/evolutionbasisqcd.h>
#include <apfel/tools.h>
#include <apfel/hardfactors.h>
#include <apfel/ogataquadrature.h>
#include <apfel/doubleobject.h>

#include "LHAPDF/LHAPDF.h"

using namespace apfel;
using namespace std;

// Narrow-width-approximation charges.
vector<double> EWChargesNWA(double const& Q)
{
  // Relevant constants for the computation of the EW charges.
  // (See https://arxiv.org/pdf/hep-ph/9711387.pdf)
  const double MZ         = 91.1876;
  const double Sin2ThetaW = 0.23126;

  // Derived quantities
  const double VD         = - 0.5 + 2 * Sin2ThetaW / 3;
  const double VU         = + 0.5 - 4 * Sin2ThetaW / 3;
  const vector<double> Vq = {VD, VU, VD, VU, VD, VU};
  const double AD         = - 0.5;
  const double AU         = + 0.5;
  const vector<double> Aq = {AD, AU, AD, AU, AD, AU};
  const double alphaem    = ( 1. / 128.77 ) / ( 1 - 0.00167092 * log(Q/MZ) );

  vector<double> EWCharges;
  for (auto i = 0; i < 6; i++)
    EWCharges.push_back(alphaem * (Vq[i] * Vq[i] + Aq[i] * Aq[i]) / 4 / Sin2ThetaW / ( 1 - Sin2ThetaW ));
  return EWCharges;
};

// Non-perturnative function
double fNP(double const& b, double const& zetaf)
{
  const double g1 = 0.02;
  const double g2 = 0.5;
  const double Q0 = 1.6;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

// b* prescription
double bstar(double const& b)
{
  const double bmax = 1;
  const double bs = b / sqrt( 1 + pow(b / bmax, 2) );
  return bs;
}

// Main program
int main()
{
 // Open LHAPDF set.
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF("MMHT2014nlo68cl");

  // Thresholds.
  const vector<double> Thresholds{distpdf->quarkThreshold(1),
      distpdf->quarkThreshold(2),
      distpdf->quarkThreshold(3),
      distpdf->quarkThreshold(4),
      distpdf->quarkThreshold(5)};

  // Alpha_s.
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

  // Perturbative order.
  const int PerturbativeOrder = 1;

  // Initial scale-variation factor;
  const double Ci = 1;

  // Final scale-variation factor;
  const double Cf = 1;

  // x-space grid.
  const Grid g{{{100,1e-5,3}, {60,1e-1,3}, {50,6e-1,3}, {100,8e-1,3}}};

  // Rotate PDF set into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> map<int,double>{ return PhysToQCDEv(distpdf->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> Set<Distribution>{ return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)}; };

  // Tabulate PDFs
  const TabulateObject<Set<Distribution>> TabPDFs{EvolvedPDFs, 50, 1, 100000, 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> Set<Distribution> { return TabPDFs.Evaluate(mu); };

  // Initialize TMD objects.
  const auto TmdObj = InitializeTmdObjects(g, Thresholds);

  // Get evolution factors.
  const auto QuarkEvolFactor = QuarkEvolutionFactor(TmdObj, Alphas, PerturbativeOrder, Ci);

  // Match TMD PDFs
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, CollPDFs, Alphas, PerturbativeOrder, Ci);

  // Hard scale
  const double Q = 91.1876;

  // C.M.E.
  const double Vs = 13000;

  // TMD scales
  const double muf   = Cf * Q;
  const double zetaf = Q * Q;

  // Construct function that returns evolved TMDs including the
  // non-perturbative part. This can be tabulated in b.
  const auto EvolvedTMDPDFs = [=] (double const& b) -> Set<Distribution>
    {
      const double bs = bstar(b);
      return fNP(b, zetaf) * QuarkEvolFactor(bs, muf, zetaf) * MatchedTMDPDFs(bs);
    };

  // Tabulate input TMDs in the impact parameter to make the
  // integral faster.
  const auto TabFunc    = [] (double const& b) -> double{ return log(b); };
  const auto InvTabFunc = [] (double const& fb) -> double{ return exp(fb); };
  const TabulateObject<Set<Distribution>> TabEvolvedTMDPDFs{EvolvedTMDPDFs, 50, 5e-5, 10, 3, {}, TabFunc, InvTabFunc};

  // EW charges
  const vector<double> Bq = EWChargesNWA(Q);

  // Rapidity
  const double y = 0;

  // Bjorken variables
  const double x1 = Q * exp(-y) / Vs;
  const double x2 = Q * exp(y) / Vs;

  // Branching ratio Br(Z -> l+l-)
  const double Br = 0.033658;

  // Compute hard coefficient, including the other kinematic
  // factors.
  const double hcs = 4 * ConvFact * Br * Pi2 * HardFactorDY(PerturbativeOrder, Alphas(muf), NF(muf, Thresholds), Cf) / 3 / pow(Q,2);

  // Ogata quadrature object with default settings.
  OgataQuadrature bintegrand{};

  // Define qT-distribution function 
  const auto qTdist = [=] (double const& qT) -> double
    {
      // Construct the TMD luminosity in b scale to be fed to be
      // trasformed in qT space.
      const auto TMDLumib = [=] (double const& b) -> double
      {
	// Get map of the TMDs in "x1" and "x2" and rotate them into the
	// physical basis.
	map<int,double> TMD1 = QCDEvToPhys(TabEvolvedTMDPDFs.EvaluateMapxQ(x1, b));
	map<int,double> TMD2 = QCDEvToPhys(TabEvolvedTMDPDFs.EvaluateMapxQ(x2, b));

	// Construct the combination of TMDs weighted by the EW
	// charges. Remember that each TMD has a factor x in the
	// front. This effectively means that the luminosity is
	// multiplied by x1 * x2 = Q2 / s.
	double lumi = 0;
	for (int i = 1; i <= 5; i++)
	lumi += Bq[i-1] * ( TMD1[i] * TMD2[-i] + TMD1[-i] * TMD2[i] );

	// Multiply by "b" and divide by two to reduce to the Fourier
	// transform to a Hankel transform.
	return b * lumi / 2;
      };
      return bintegrand.transform(TMDLumib, qT);
    };

  // Use a different method using a DoubleObject
  const auto Lumi = [=] (double const& bs) -> DoubleObject<Distribution>
    {
      const map<int,Distribution> xF = QCDEvToPhys((QuarkEvolFactor(bs, muf, zetaf) * MatchedTMDPDFs(bs)).GetObjects());
      DoubleObject<Distribution> L{};
      for (int i = 1; i <= 5; i++)
	{
	  L.AddTerm({Bq[i-1], xF.at(i), xF.at(-i)});
	  L.AddTerm({Bq[i-1], xF.at(-i), xF.at(i)});
	}
      return L;
    };
  const TabulateObject<DoubleObject<Distribution>> TabLumi{Lumi, 50, 5e-5, 1.1, 3, {}, TabFunc, InvTabFunc};

  // Define qT-distribution function 
  const auto qTdistNew = [=] (double const& qT) -> double
    {
      // Construct the TMD luminosity in b scale to be fed to be
      // trasformed in qT space.
      const auto TMDLumibNew = [=] (double const& b) -> double{ return b * TabLumi.EvaluatexzQ(x1, x2, bstar(b)) * fNP(b, zetaf) * fNP(b, zetaf) / 2; };
      return 2 * qT * hcs * bintegrand.transform(TMDLumibNew, qT);
    };

  Timer t;
  const vector<double> qTv{1, 3, 5, 7, 9, 11, 13, 15, 17};
  cout << scientific << "\n";
  cout << "  qT [GeV]    "
       << "   sigma      "
       << endl;
  for (auto const& qT : qTv)
    cout << qT << "  " << 2 * qT * hcs * qTdist(qT) << endl;
  cout << "\n";
  t.stop();

  t.start();
  cout << "\n  qT [GeV]    "
       << "   sigma      "
       << endl;
  for (auto const& qT : qTv)
    cout << qT << "  " << qTdistNew(qT) << endl;
  cout << "\n";
  t.stop();

  // Integrate in qT
  t.start();
  cout << "\n    [qTmin:qTmax] [GeV]      "
       << "   sigma      "
       << endl;
  const Integrator IntQt{qTdistNew};
  for (int iqT = 0; iqT < (int) qTv.size() - 1; iqT++)
    cout << "[" << qTv[iqT] << ":" << qTv[iqT+1] << "]: " << IntQt.integrate(qTv[iqT], qTv[iqT+1], 1e-5) << endl;
  cout << "\n";
  t.stop();

  // Ogata quadrature object with default settings.
  t.start();
  cout << "\n    [qTmin:qTmax] [GeV]      "
       << "   sigma      "
       << endl;
  OgataQuadrature qTintegrand{1};
  const auto qTPrimitive = [=] (double const& qT) -> double
    {
      // Construct the TMD luminosity in b scale to be fed to be
      // trasformed in qT space.
      const auto TMDLumibPrim = [=] (double const& b) -> double{ return TabLumi.EvaluatexzQ(x1, x2, bstar(b)) * fNP(b, zetaf) * fNP(b, zetaf) / 2; };
      return 2 * qT * hcs * qTintegrand.transform(TMDLumibPrim, qT);
    };
  for (int iqT = 0; iqT < (int) qTv.size() - 1; iqT++)
    cout << "[" << qTv[iqT] << ":" << qTv[iqT+1] << "]: " << qTPrimitive(qTv[iqT+1]) - qTPrimitive(qTv[iqT]) << endl;
  cout << "\n";
  t.stop();

  cout << "\n";
  return 0;
}

