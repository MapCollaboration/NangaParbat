//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Stefano Carrazza: stefano.carrazza@cern.ch
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

using namespace apfel;
using namespace std;

// LH Toy PDFs
double xupv(double const& x)  { return 5.107200 * pow(x,0.8) * pow((1-x),3); }
double xdnv(double const& x)  { return 3.064320 * pow(x,0.8) * pow((1-x),4); }
double xglu(double const& x)  { return 1.7 * pow(x,-0.1) * pow((1-x),5); }
double xdbar(double const& x) { return 0.1939875 * pow(x,-0.1) * pow((1-x),6); }
double xubar(double const& x) { return xdbar(x) * (1-x); }
double xsbar(double const& x) { return 0.2 * ( xdbar(x) + xubar(x) ); }
map<int,double> LHToyPDFs(double const& x, double const&)
{
  // Call all functions once.
  const double upv  = xupv (x);
  const double dnv  = xdnv (x);
  const double glu  = xglu (x);
  const double dbar = xdbar(x);
  const double ubar = xubar(x);
  const double sbar = xsbar(x);

  // Construct QCD evolution basis conbinations.
  double const Gluon   = glu;
  double const Singlet = dnv + 2 * dbar + upv + 2 * ubar + 2 * sbar;
  double const T3      = upv + 2 * ubar - dnv - 2 * dbar;
  double const T8      = upv + 2 * ubar + dnv + 2 * dbar - 4 * sbar;
  double const Valence = upv + dnv;
  double const V3      = upv - dnv;

  // Fill in map in the QCD evolution basis.
  map<int,double> QCDEvMap;
  QCDEvMap.insert({0 , Gluon});
  QCDEvMap.insert({1 , Singlet});
  QCDEvMap.insert({2 , Valence});
  QCDEvMap.insert({3 , T3});
  QCDEvMap.insert({4 , V3});
  QCDEvMap.insert({5 , T8});
  QCDEvMap.insert({6 , Valence});
  QCDEvMap.insert({7 , Singlet});
  QCDEvMap.insert({8 , Valence});
  QCDEvMap.insert({9 , Singlet});
  QCDEvMap.insert({10, Valence});
  QCDEvMap.insert({11, Singlet});
  QCDEvMap.insert({12, Valence});

  return QCDEvMap;
}

int main()
{
  // =================================================================
  // Parameters
  // =================================================================
  // x-space grid.
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,6e-1,3}, SubGrid{50,8e-1,3}}};

  // Initial scale for the collinear PDF evolution.
  const double mui = sqrt(2);

  // Vectors of masses and thresholds.
  const vector<double> Masses = {0, 0, 0, sqrt(2), 4.5, 175};
  const vector<double> Thresholds = Masses;

  // Perturbative order.
  const int PerturbativeOrder = 2;

  // =================================================================
  // Alpha_s
  // =================================================================
  // Running coupling
  const double AlphaQCDRef = 0.35;
  const double MuAlphaQCDRef = sqrt(2);
  AlphaQCD a{AlphaQCDRef, MuAlphaQCDRef, Masses, PerturbativeOrder};
  const TabulateObject<double> TabAlphas{a, 100, 1, 1000001, 3};
  const auto Alphas = [&] (double const& mu) -> double{ return TabAlphas.Evaluate(mu); };

  // =================================================================
  // Collinear PDFs
  // =================================================================
  // Initialize DGLAP objects.
  const auto DglapObj = InitializeDglapObjectsQCD(g, Masses, Thresholds);

  // Construct the DGLAP evolution.
  auto EvolvedPDFs = BuildDglap(DglapObj, LHToyPDFs, mui, PerturbativeOrder, Alphas);

  // Tabulate PDFs
  const TabulateObject<Set<Distribution>> TabPDFs{*EvolvedPDFs, 50, 1, 1000000, 3};
  const auto CollPDFs = [&] (double const& mu) -> Set<Distribution> { return TabPDFs.Evaluate(mu); };

  // =================================================================
  // TMD PDFs
  // =================================================================
  // Initialize TMD objects.
  const auto TmdObj = InitializeTmdObjects(g, Thresholds);

  // Function that returns the scale mu as a function of the impact
  // parameter b.
  const auto Mub = [] (double const& b) -> double
    {
      const double C0   = 2 * exp(- emc);
      const double bmax = 1;
      return C0 * sqrt( 1 + pow(b/bmax,2) ) / b;
    };

  const auto bMu = [] (double const& mu) -> double
    {
      const double C0   = 2 * exp(- emc);
      const double bmax = 1;
      return 1. / sqrt( pow(mu/C0,2) - pow(1/bmax,2) );
    };

  // Non-perturbative TMD function.
  const auto fNP = [] (double const&, double const&) -> double{ return 1; };

  // Get evolved TMDs (this assumes the zeta-prescription).
  const auto EvolvedTMDs = BuildTmdPDFs(TmdObj, DglapObj, CollPDFs, fNP, Mub, Mub, PerturbativeOrder, Alphas);

  const double xb = 0.05;

  const int nmu      = 10;
  const double mumin = 2;
  const double mumax = 100;
  const double mustep = exp( log( mumax / mumin ) / ( nmu - 1 ) );

  double mu = mumin;
  cout << scientific;
  for (int imu = 0; imu < nmu; imu++)
    {
      cout << EvolvedTMDs(bMu(mu), mu, mu * mu).at(0).Evaluate(xb) << "  "
	   << EvolvedTMDs(bMu(mu), mu, mu * mu).at(1).Evaluate(xb) << "  "
	   << EvolvedTMDs(bMu(mu), mu, mu * mu).at(2).Evaluate(xb) << "  "
	   << EvolvedTMDs(bMu(mu), mu, mu * mu).at(3).Evaluate(xb) << "  "
	   << EvolvedTMDs(bMu(mu), mu, mu * mu).at(4).Evaluate(xb) << "  "
	   << EvolvedTMDs(bMu(mu), mu, mu * mu).at(5).Evaluate(xb) << "  "
	   << EvolvedTMDs(bMu(mu), mu, mu * mu).at(6).Evaluate(xb) << "  "
	   << endl;
      mu *= mustep;
    }

  return 0;
}

