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
  const auto EvolvedTMDPDFs = BuildTmdPDFs(TmdObj, DglapObj, CollPDFs, fNP, Mub, Mub, PerturbativeOrder, Alphas);
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, DglapObj, CollPDFs, fNP, Mub, PerturbativeOrder, Alphas);
  const auto EvolFactors = EvolutionFactors(TmdObj, Mub, Mub, PerturbativeOrder, Alphas);

  // Compute Drell-Yan cross section.
  const double Vs = 8000;
  const double Q  = 91.2;
  const double y  = 2.5;

  // Relevant constants for the computation of the EW charges.
  const double MZ         = 91.1876;
  const double MZ2        = MZ * MZ;
  const double GammaZ     = 2.4952;
  const double GammaZ2    = GammaZ * GammaZ;
  const double Sin2ThetaW = 0.23126;
  const double VD         = - 0.5 + 2 * Sin2ThetaW / 3;
  const double VU         = + 0.5 - 4 * Sin2ThetaW / 3;
  const vector<double> Vq = {VD, VU, VD, VU, VD, VU};
  const double AD         = - 0.5;
  const double AU         = + 0.5;
  const vector<double> Aq = {AD, AU, AD, AU, AD, AU};
  const double Ve         = - 0.5 + 2 * Sin2ThetaW;
  const double Ae         = - 0.5;
  const double alphaem    = ( 1. / 127.91 ) / ( 1 - 0.00167092 * log(Q/MZ) );
  const double alphaem2   = alphaem * alphaem;

  // Actual charges.
  const auto fEWCharges = [=] (double const& Q) -> vector<double>
    {
      const double Q2  = Q * Q;
      const double PZ  = Q2 * ( Q2 -  MZ2 ) / ( pow(Q2 - MZ2,2) + MZ2 * GammaZ2 ) / ( 4 * Sin2ThetaW * ( 1 - Sin2ThetaW ) );
      const double PZ2 = pow(Q2,2) / ( pow(Q2 - MZ2,2) + MZ2 * GammaZ2 ) / pow(4 * Sin2ThetaW * ( 1 - Sin2ThetaW ),2);
      vector<double> EWCharges;
      for (auto i = 0; i < (int) Thresholds.size(); i++)
	{
	  const double b = QCh2[i]
	    - 2 * QCh[i] * Vq[i] * Ve * PZ
	    + ( Ve * Ve + Ae * Ae ) * ( Vq[i] * Vq[i] + Aq[i] * Aq[i] ) * PZ2;
	  EWCharges.push_back(alphaem2*b);
	}
      return EWCharges;
    };

  const double dQ = 0.01;
  const double dy = 0.001;

  // Drell-Yann cross section.
  function<double(double const&)> TmdXsecDY    = TmdCrossSectionDY(Vs, Q,          y,          EvolvedTMDPDFs,              Alphas, fEWCharges, PerturbativeOrder, Thresholds);
  function<double(double const&)> TmdXsecDYInt = TmdCrossSectionDY(Vs, Q-dQ, Q+dQ, y-dy, y+dy, MatchedTMDPDFs, EvolFactors, Alphas, fEWCharges, PerturbativeOrder, Thresholds);

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
	   << EvolvedTMDPDFs(b, muf, zetaf).at(0).Evaluate(x2) / x2 << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(1).Evaluate(x2) / x2 << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(2).Evaluate(x2) / x2 << "  "
	   << EvolvedTMDPDFs(b, muf, zetaf).at(3).Evaluate(x2) / x2 << "  "
	   << endl;
      b += bstep;
    }
  cout << "\n";

  const vector<double> qT{1, 2, 3, 4, 5, 10, 15, 20, 25, 30};
  Timer t;
  t.start();
  cout << "Computing TMD luminosity in qT space ..." << endl;
  cout << "\n  qT [GeV]   "
       << "   d(sigma)/dQdyd(qT^2)"
       << endl;
  for (auto const& q : qT)
    cout << q << "  "
	 << TmdXsecDY(q) << "  "
	 << TmdXsecDYInt(q) / dQ / dy / 4 << "  "
	 << endl;

  cout << "\n";
  cout << "Integration... ";
  t.stop();

  const int nqT = 1000;
  const double qTmin = 1;
  const double qTmax = 30;
  const double qTstep = ( qTmax - qTmin ) / ( nqT - 1 );
  cout << "\nComputing " << nqT << " unintegrated cross sections... ";
  t.start();
  double qTv = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      TmdXsecDY(qTv);
      qTv += qTstep;
    }
  t.stop();

  return 0;
}

