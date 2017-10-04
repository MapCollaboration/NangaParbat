//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <apfel/dglapbuilder.h>
#include <apfel/grid.h>
#include <apfel/timer.h>
#include <apfel/tools.h>
#include <apfel/alphaqcd.h>
#include <apfel/tabulateobject.h>
#include <apfel/tmdbuilder.h>
#include <apfel/rotations.h>

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
  const TabulateObject<Set<Distribution>> CollPDFs{EvolvedPDFs, 50, Qmin, Qmax, 3, Thresholds};

  //const auto DglapObj = InitializeDglapObjectsQCD(g, Thresholds);
  //auto EvolvedPDFs = BuildDglap(DglapObj, RotPDFs, Qmin, PerturbativeOrder, Alphas);
  //const TabulateObject<Set<Distribution>> CollPDFs{*EvolvedPDFs, 50, Qmin, Qmax, 3};

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
      const double bmax = 1;
      const double Q0   = 1;
      return C0 * sqrt( 1 + pow(b/bmax,2) ) / b + Q0;
    };

  // Non-perturbative TMD function.
  const auto fNP = [] (double const& x, double const& b) -> double
    {
      const double L1 = 0.156;
      const double L2 = - 0.0379;
      return exp( - L1 * b ) * ( 1 + L2 * b * b );
    };

  // Get evolved TMDs (this assumes the zeta-prescription).
  const auto EvolvedTMDs = BuildTmdPDFs(TmdObj, DglapObj, CollPDFs, fNP, Mub, Mub, PerturbativeOrder, Alphas);

  // Print evolved singlet and gluon TMDs as functions of the impact
  // parameter for a set of example parameters.
  const double Vs    = 8000;
  const double Q     = 91.2;
  const double y     = 2.5;
  const double x1    = Q * exp(-y) / Vs;
  const double x2    = Q * exp(y) / Vs;
  const double muf   = Q;
  const double zetaf = Q * Q;

  // Tabulate TMDs in the impact parameter
  const auto TabFunc = [] (double const& b)->double{ return log(b); };
  const auto InvTabFunc = [] (double const& fb)->double{ return exp(fb); };
  const TabulateObject<Set<Distribution>> TabulatedTMDs{[&] (double const& b)->Set<Distribution>{ return EvolvedTMDs(b, muf, zetaf); }, 100, 1e-7, 100, 3, Thresholds, TabFunc, InvTabFunc};

  const int nb       = 10;
  const double bmin  = 0.1;
  const double bmax  = 1;
  const double bstep = ( bmax - bmin ) / ( nb - 1 );

  cout << scientific << "\n";
  cout << " b [1/GeV]    "
       << " Mu(b) [GeV]  "
       << "TMPDF(gluon)  "
       << " Tabulated    "
       << "TMPDF(sigma)  "
       << " Tabulated    "
       << endl;
  double b = bmin;
  for (int ib = 0; ib < nb; ib++)
    {
      cout << b << "  " << Mub(b) << "  "
	   << EvolvedTMDs(b, muf, zetaf).at(0).Evaluate(x2) / x2 << "  "
	   << TabulatedTMDs.EvaluatexQ(0, x2, b) / x2 << "  "
	   << EvolvedTMDs(b, muf, zetaf).at(1).Evaluate(x2) / x2 << "  "
	   << TabulatedTMDs.EvaluatexQ(1, x2, b) / x2 << "  "
	   << endl;
      b += bstep;
    }
  cout << "\n";

  // Now construct the integrand of the Fourier (Hankel) tranform,
  // that is the TMD luminosity.
  const auto TMDLumi = [=] (double const& b, double const& qT) -> double
    {
      // Get map of the TMDs in "x1" and "x2" and rotate them into the
      // physical basis.
      map<int,double> TMD1 = QCDEvToPhys(TabulatedTMDs.EvaluateMapxQ(x1, b));
      map<int,double> TMD2 = QCDEvToPhys(TabulatedTMDs.EvaluateMapxQ(x2, b));

      // Construct the combination of TMDs weighted with the charges.
      double lumi = 0;
      for (int i = 1; i <= 6; i++)
	lumi += QCh2[i-1] * ( TMD1[i] * TMD2[-i] + TMD1[-i] * TMD2[i] );

      // Multuply it by the bessel function j0/2, by the Jacobian "b",
      // and divide by x1 and x2 because the "EvolvedTMDs" function
      // returns x times the TMDs.
      lumi *= b * j0(b*qT) / 2 / x1 / x2;

      return lumi;
    };

  Timer t;
  t.start();
  const vector<double> qT{1, 2, 3, 4, 5, 10, 15, 20, 25, 30};;

  for (auto const& q : qT)
    {
      vector<double> nodes;
      for (auto const& jz : j0Zeros)
	nodes.push_back(jz / q);

      // Integrate Luminosity over b.
      const Integrator TMDLumqT{TMDLumi, q};
      cout << q << "  " << TMDLumqT.integrate(0.000001, 20, nodes, eps5) << endl;
    }
  cout << "Integration... ";
  t.stop();

/*
  // Drell-Yan hard cross section
  const auto HardCrossSectionDY = [Alphas,Thresholds] (int const& pt, double const& Qh, double const& mu)->double
    {
      // Compute log anf its powers.
      const double lQ2  = 2 * log( mu / Qh );
      const double lQ22 = lQ2 * lQ2;
      const double lQ23 = lQ22 * lQ2;
      const double lQ24 = lQ23 * lQ2;

      // Compute coupling and its powers.
      const double as  = Alphas(mu) / FourPi;
      const double as2 = as * as;

      // Now compute hard cross section accordi to the perturnative
      // order.
      double hxs = 1;
      if (pt > 0)
	hxs += 2 * as * CF * ( - lQ22 - 3 * lQ2 - 8 + 7 * Pi2 / 6 );
      if (pt > 1)
	hxs += 2 * as2 * CF *
	  ( CF * ( lQ24 + 6 * lQ23 + ( 25 - 7 * Pi2 / 3 ) * lQ22 + ( 93. / 2. - 5 * Pi2 - 24 * zeta3 ) * lQ2 +
		   511. / 8. - 83 * Pi2 / 6 - 30 * zeta3 + 67 * Pi2 * Pi2 / 60 ) +
	    CA * ( - 11 * lQ23 / 9 + ( - 233 / 18 + Pi2 / 3 ) * lQ22 + ( - 2545. / 54. + 22 * Pi2 / 9 + 26 * zeta3 ) * lQ2 +
		   - 51157. / 648. + 1061 * Pi2 / 108 + 313 * zeta3 / 9 - 4 * Pi2 * Pi2 / 45 ) +
	    TR * NF(mu, Thresholds) * ( 4 * lQ23 / 9 + 38 * lQ22 / 9 + ( 418. / 27. - 8 * Pi2 / 9 ) * lQ2 +
					4085. / 162. - 91 * Pi2 / 27 + 4 * zeta3 / 9 ) );

      return hxs;
    };
*/

  return 0;
}

