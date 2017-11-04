//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Stefano Carrazza: stefano.carrazza@cern.ch
//

#include <apfel/dglapbuilder.h>
#include <apfel/grid.h>
#include <apfel/timer.h>
#include <apfel/constants.h>
#include <apfel/alphaqcd.h>
#include <apfel/tabulateobject.h>
#include <apfel/tmdbuilder.h>
#include <apfel/rotations.h>
#include <apfel/lhtoypdfs.h>

#include <cmath>
#include <map>
#include <iomanip>

using namespace apfel;
using namespace std;

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

