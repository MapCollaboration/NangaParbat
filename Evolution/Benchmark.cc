//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <apfel/dglapbuilder.h>
#include <apfel/grid.h>
#include <apfel/timer.h>
#include <apfel/constants.h>
#include <apfel/tools.h>
#include <apfel/alphaqcd.h>
#include <apfel/tabulateobject.h>
#include <apfel/tmdbuilder.h>
#include <apfel/rotations.h>
#include <apfel/tmdcrosssections.h>

#include <cmath>
#include <map>
#include <iomanip>

#include "LHAPDF/LHAPDF.h"

using namespace apfel;
using namespace std;

int main()
{
  cout << __PRETTY_FUNCTION__ << "\n";

  // Open LHAPDF set.
  LHAPDF::PDF* dist = LHAPDF::mkPDF("MMHT2014nnlo68cl");

  // Thresholds.
  const vector<double> Thresholds{dist->quarkThreshold(1),
      dist->quarkThreshold(2),
      dist->quarkThreshold(3),
      dist->quarkThreshold(4),
      dist->quarkThreshold(5),
      dist->quarkThreshold(6)};

  // Perturbative order.
  const int PerturbativeOrder = dist->orderQCD();

  // Tabulation limits
  const double Qmin = dist->qMin();
  const double Qmax = 5000 * dist->qMax();

  // =================================================================
  // Alpha_s
  // =================================================================
  const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };

  // =================================================================
  // Collinear PDFs
  // =================================================================
  // x-space grid.
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,6e-1,3}, SubGrid{50,8e-1,3}}};

  // Rotate PDF set into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> map<int,double>{ return PhysToQCDEv(dist->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> Set<Distribution>{ return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)}; };

  // Tabulate PDFs
  const TabulateObject<Set<Distribution>> TabPDFs{EvolvedPDFs, 50, Qmin, Qmax, 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> Set<Distribution> { return TabPDFs.Evaluate(mu); };

  //const auto DglapObj = InitializeDglapObjectsQCD(g, Thresholds);
  //auto EvolvedPDFs = BuildDglap(DglapObj, RotPDFs, Qmin, PerturbativeOrder, Alphas);
  //const TabulateObject<Set<Distribution>> TabPDFs{*EvolvedPDFs, 50, Qmin, Qmax, 3};
  //const auto CollPDFs = [&] (double const& mu) -> Set<Distribution> { return TabPDFs.Evaluate(mu); };

  // =================================================================
  // TMD PDFs
  // =================================================================
  // Initialize TMD and DGLAP objects.
  const auto TmdObj   = InitializeTmdObjects(g, Thresholds);
  const auto DglapObj = InitializeDglapObjectsQCD(g, Thresholds);

  // Function that returns the inital scale mu as a function of the
  // impact parameter b.
  const auto Mub = [] (double const& b) -> double
    {
      const double C0   = 2 * exp(- emc);
      return C0 / b + 2;
      //const double bmax = 1;
      //const double Q0   = 1;
      //return C0 * sqrt( 1 + pow(b/bmax,2) ) / b + Q0;
    };

  // Non-perturbative TMD function.
  const auto fNP = [] (double const& x, double const& bT) -> double
    {
      const double L1 = 0.2442;
      //const double L2 = 0;
      const double L3 = 0.3070;

      const double a = L3 / L1 / 2;
      const double b = L1 / 2;
      if (a == 0 || b == 0)
	return 0;
      else
	if ((a + b) * bT > 200)
	  if (a > b)
	    return exp( - L1 * bT );
	  else
	    return exp( - 2 * a * bT );
	else
	  return cosh( ( a - b ) * bT ) / cosh( ( a + b ) * bT );
      //const double L1 = 0.156;
      //const double L2 = - 0.0379;
      //return exp( - L1 * b ) * ( 1 + L2 * b * b );
    };

  // Get evolved TMDs (this assumes the zeta-prescription).
  const auto EvolvedTMDPDFs = BuildTmdPDFs(TmdObj, DglapObj, CollPDFs, fNP, Mub, Mub, PerturbativeOrder, Alphas);
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, DglapObj, CollPDFs, fNP, Mub, PerturbativeOrder, Alphas);
  const auto EvolFactors    = EvolutionFactors(TmdObj, Mub, Mub, PerturbativeOrder, Alphas);

  // Compute Drell-Yan cross section.
  const double Vs = 8000;
  const double Q  = 91.2;
  const double y  = 2.5;
  const double MZ = 91.1876;
  const double Br = 0.03645;

  const double x2    = Q * exp(y) / Vs;
  const double muf   = Q;
  const double zetaf = Q * Q;

  const int nb       = 100;
  const double bmin  = 0.1;
  const double bmax  = 10;
  const double bstep = ( bmax - bmin ) / ( nb - 1 );

  cout << scientific << "\n";
  cout << " b [1/GeV]    "
       << " Mu(b) [GeV]  "
       << " Ev. (gluon)  "
       << " Ev. (sigma)  "
       << "TMPDF(gluon)  "
       << "TMPDF(sigma)  "
       << " TMPDF(val.)  "
       << "  TMPDF(T3)   "
       << endl;
  double b = bmin;
  for (int ib = 0; ib < nb; ib++)
    {
      //const auto EvTMDs = EvolFactors(b, muf, zetaf) * MatchedTMDPDFs(b);
      cout << b << "  " << Mub(b) << "  "
	   << EvolFactors(b, muf, zetaf)[0] << "  "
	   << EvolFactors(b, muf, zetaf)[1] << "  "
	   << endl;
      b += bstep;
    }
  cout << "\n\n";
  b = bmin;
  for (int ib = 0; ib < nb; ib++)
    {
      //const auto EvTMDs = EvolFactors(b, muf, zetaf) * MatchedTMDPDFs(b);
      cout << b << "  " << Mub(b) << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(0).Evaluate(x2) / x2 << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(1).Evaluate(x2) / x2 << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(2).Evaluate(x2) / x2 << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(3).Evaluate(x2) / x2 << "  "
	   << endl;
      b += bstep;
    }
  cout << "\n\n";

  // Relevant constants for the computation of the EW charges.
  const double paramD = 0.51974146748459;
  const double paramU = 0.40321312240043;
  const double paramS = 0.51974146748459;
  const double paramC = 0.40321312240043;
  const double paramB = 0.51974146748459;
  const double paramT = 0.40321312240043;

  // Actual charges.
  const auto fEWCharges = [=] (double const&) -> vector<double>{ return {paramD, paramU, paramS, paramC, paramB, paramT}; };

  // Electromagnetic charge
  const double alphaem  = ( 1. / 127.91 ) / ( 1 - 0.00167092 * log(Q/MZ) );

  // Drell-Yann cross section.
  function<double(double const&)> TmdXsecDY = TmdCrossSectionDY(Vs, Q, y, EvolvedTMDPDFs, Alphas, fEWCharges, PerturbativeOrder, Thresholds);

  const vector<double> qT{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
      11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
      21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
  Timer t;
  t.start();
  cout << "Computing TMD luminosity in qT space ..." << endl;
  cout << "\n  qT [GeV]   "
       << "   d(sigma)/dyd(qT^2)"
       << endl;
  for (auto const& q : qT)
    cout << q << "  "
	 <<  3 * M_PI * alphaem * Br * TmdXsecDY(q) * MZ * MZ << "  "
	 << endl;

  return 0;
}

