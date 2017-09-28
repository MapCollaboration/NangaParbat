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
  // x-space grid
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,6e-1,3}, SubGrid{50,8e-1,3}}};

  // Initial scale
  const double mu0 = sqrt(2);

  // Vectors of masses and thresholds
  const vector<double> Masses = {0, 0, 0, sqrt(2), 4.5, 175}; // Check in the level above that they are ordered
  const vector<double> Thresholds = Masses;

  // Perturbative order
  const int PerturbativeOrder = 1;

  // Running coupling
  const double AlphaQCDRef = 0.35;
  const double MuAlphaQCDRef = sqrt(2);
  AlphaQCD a{AlphaQCDRef, MuAlphaQCDRef, Masses, PerturbativeOrder};
  const TabulateObject<double> Alphas{a, 100, 0.9, 1001, 3};
  const auto as = [&] (double const& mu) -> double{ return Alphas.Evaluate(mu); };

  // Initialize QCD evolution objects
  const auto DglapObj = InitializeDglapObjectsQCD(g, Masses, Thresholds);

  // Construct the DGLAP object
  auto EvolvedPDFs = BuildDglap(DglapObj, LHToyPDFs, mu0, PerturbativeOrder, as);

  // Tabulate PDFs
  const TabulateObject<Set<Distribution>> TabulatedPDFs{*EvolvedPDFs, 50, 1, 1000, 3};

  // Initialize matching functions
  const auto TmdObj = InitializeTmdObjects(g, Thresholds);

  // Function that returns the scale mu as function of the impact
  // parameter b.
  const double C0   = 2 * exp(- emc);
  const double bmax = 1;
  const auto Mub = [C0,bmax] (double const& b) -> double{ return C0 * sqrt( 1 + pow(b/bmax,2) ) / b; };

  // Function that returns the matching functions as functions of the
  // absolute value of the impact parameter b.
  const auto MatchFunc = [&] (double const& b) -> Set<Operator>
    {
      const double mu   = Mub(b);
      const double Lmu  = 2 * log( b * mu / C0 );
      const double coup = as(mu) / FourPi;
      const double nf   = NF(mu, Thresholds);
      return TmdObj.at(nf).MatchingFunctions.at(0) + coup * ( - Lmu * DglapObj.at(nf).SplittingFunctions.at(0) + TmdObj.at(nf).MatchingFunctions.at(1) );
    };

  // Define non-perturbative function
  const double Lq = 10;
  const double L1 = 0.2;
  const auto fNP = [Lq,L1] (double const& x, double const& b) -> double
    {
      const double fact    = Lq * x * b;
      return exp( - fact * b / sqrt( 1 + pow( fact / L1, 2) ) );
    };

  // Function that returns the PDFs times the non-perturbative
  // function as functions of the absolute value of the impact
  // parameter b.
  const auto PDFsNP = [&] (double const& b) -> Set<Distribution>
    {
      map<int,Distribution> NonPertPDFs;
      const map<int,Distribution> PertPDFs = TabulatedPDFs.Evaluate(Mub(b)).GetObjects();
      for (auto const& id : PertPDFs)
	NonPertPDFs.insert({id.first, id.second * [=] (double const& x)->double{ return fNP(x, b); }});

      return Set<Distribution>{TabulatedPDFs.Evaluate(Mub(b)).GetMap(), NonPertPDFs};
    };

  // Tabulate product of matching functions an PDFs + NP function.
  const TabulateObject<Set<Distribution>> TabulatedTMDs{[=] (double const& b)->Set<Distribution>{ return MatchFunc(b) * PDFsNP(b); }, 50, 1, 1000, 3, Thresholds};

  // Compute evolution factor for both quark and gluon distributions
  

  // Test values of the impact parameter and Bjorken x.
  const double bT = 1;
  const double xb = 0.2;

  // Print results
  cout << (MatchFunc(bT)*PDFsNP(bT)).at(0).Evaluate(xb) << "  "
       << TabulatedTMDs.EvaluatexQ(0,xb,bT) << "  "
       << TabulatedPDFs.Evaluate(Mub(bT)).at(0).Evaluate(xb) << endl;

  // Performance test
  Timer t;
  int k = 1000000;
  cout << "Interpolating " << k << " times a single TMD on the (x,b) grid... ";
  t.start();
  for (auto i = 0; i < k; i++)
    TabulatedTMDs.EvaluatexQ(0,xb,bT);
  t.stop();

  return 0;
}
