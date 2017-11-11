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
  SetVerbosityLevel(0);
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
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, DglapObj, CollPDFs, Mub, PerturbativeOrder, Alphas);
  const auto EvolFactors    = EvolutionFactors(TmdObj, Mub, Mub, PerturbativeOrder, Alphas);

  // Compute Drell-Yan cross section.
  const double Vs = 8000;
  const double y  = 0;

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
  const double alphaem    = 1. / 127.91;
  const double alphaem2   = alphaem * alphaem;
  const double Br         = 0.03645;

  // Complete charges.
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

  // Charges gamma-gamma.
  const auto fEWChargesGG = [=] (double const& Q) -> vector<double>
    {
      vector<double> EWCharges;
      for (auto i = 0; i < (int) Thresholds.size(); i++)
	{
	  const double b = QCh2[i];
	  EWCharges.push_back(alphaem2*b);
	}
      return EWCharges;
    };

  // Charges ZZ.
  const auto fEWChargesZZ = [=] (double const& Q) -> vector<double>
    {
      const double Q2  = Q * Q;
      const double PZ2 = pow(Q2,2) / ( pow(Q2 - MZ2,2) + MZ2 * GammaZ2 ) / pow(4 * Sin2ThetaW * ( 1 - Sin2ThetaW ),2);
      vector<double> EWCharges;
      for (auto i = 0; i < (int) Thresholds.size(); i++)
	{
	  const double b = ( Ve * Ve + Ae * Ae ) * ( Vq[i] * Vq[i] + Aq[i] * Aq[i] ) * PZ2;
	  EWCharges.push_back(alphaem2*b);
	}
      return EWCharges;
    };

  // Charges gamma-Z.
  const auto fEWChargesGZ = [=] (double const& Q) -> vector<double>
    {
      const double Q2  = Q * Q;
      const double PZ  = Q2 * ( Q2 -  MZ2 ) / ( pow(Q2 - MZ2,2) + MZ2 * GammaZ2 ) / ( 4 * Sin2ThetaW * ( 1 - Sin2ThetaW ) );
      vector<double> EWCharges;
      for (auto i = 0; i < (int) Thresholds.size(); i++)
	{
	  const double b = - 2 * QCh[i] * Vq[i] * Ve * PZ;
	  EWCharges.push_back(alphaem2*b);
	}
      return EWCharges;
    };

  // Narrow-width-approximation charges.
  const auto fEWChargesNWA = [=] (double const&) -> vector<double>
    {
      vector<double> EWCharges;
      for (auto i = 0; i < (int) Thresholds.size(); i++)
	EWCharges.push_back((Vq[i] * Vq[i] + Aq[i] * Aq[i]) / 4 / Sin2ThetaW / ( 1 - Sin2ThetaW ));
      return EWCharges;
    };

  const int nQ       = 1000;
  const double qmin  = 20;
  const double qmax  = 200;
  const double Qstep = ( qmax - qmin ) / ( nQ - 1 );
  double Q = qmin;
  cout << scientific;
  for (int iQ = 0; iQ < nQ; iQ++)
    {
      function<double(double const&)> xsec   = TmdCrossSectionDY(Vs, Q, y, EvolvedTMDPDFs, Alphas, fEWCharges,   PerturbativeOrder, Thresholds);
      function<double(double const&)> xsecgg = TmdCrossSectionDY(Vs, Q, y, EvolvedTMDPDFs, Alphas, fEWChargesGG, PerturbativeOrder, Thresholds);
      function<double(double const&)> xseczz = TmdCrossSectionDY(Vs, Q, y, EvolvedTMDPDFs, Alphas, fEWChargesZZ, PerturbativeOrder, Thresholds);
      function<double(double const&)> xsecgz = TmdCrossSectionDY(Vs, Q, y, EvolvedTMDPDFs, Alphas, fEWChargesGZ, PerturbativeOrder, Thresholds);
      cout << Q << "  "
	   << 2 * Q * xsec(5)   << "  "
	   << 2 * Q * xsecgg(5) << "  "
	   << 2 * Q * xseczz(5) << "  "
	   << 2 * Q * xsecgz(5) << "  "
	   << endl;
      Q += Qstep;
    }

/*
  // Drell-Yann cross section.
  function<double(double const&)> TmdXsecDY    = TmdCrossSectionDY(Vs, MZ,      y,    EvolvedTMDPDFs,              Alphas, fEWChargesNWA, PerturbativeOrder, Thresholds);
  function<double(double const&)> TmdXsecDYInt = TmdCrossSectionDY(Vs, 66, 116, y, y, MatchedTMDPDFs, EvolFactors, Alphas, fEWCharges,    PerturbativeOrder, Thresholds);

  const vector<double> qT{1, 2, 3, 4, 5, 10, 15, 20, 25, 30};
  Timer t;
  t.start();
  cout << "Computing TMD luminosity in qT space ..." << endl;
  cout << "\n  qT [GeV]   "
       << "   d(sigma)/dQdyd(qT^2)"
       << endl;
  for (auto const& q : qT)
    cout << q << "  "
	 << 3 * M_PI * alphaem * Br * MZ2 * TmdXsecDY(q) / TmdXsecDYInt(q) << "  "
	 << endl;

  cout << "\n";
  cout << "Integration... ";
  t.stop();
*/
  return 0;
}

