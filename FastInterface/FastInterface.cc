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
#include <apfel/evolutionbasisqcd.h>

#include <cmath>
#include <map>
#include <iomanip>
#include <algorithm>

#include "LHAPDF/LHAPDF.h"

using namespace apfel;
using namespace std;

int main()
{
  // Timer
  Timer t;

  // Open LHAPDF set.
  LHAPDF::PDF* dist = LHAPDF::mkPDF("MMHT2014nnlo68cl");

  // Get thresholds.
  const vector<double> Thresholds{dist->quarkThreshold(1),
      dist->quarkThreshold(2),
      dist->quarkThreshold(3),
      dist->quarkThreshold(4),
      dist->quarkThreshold(5),
      dist->quarkThreshold(6)};

  // Get perturbative order.
  const int PerturbativeOrder = dist->orderQCD();

  // Get tabulation limits.
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
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> Set<Distribution>
    {
      return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)};
    };

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
      const double C0 = 2 * exp(- emc);
      return C0 / b + 2;
    };

  // Get evolved TMDs (this assumes the zeta-prescription).
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, DglapObj, CollPDFs, Mub, PerturbativeOrder, Alphas);
  const auto EvolFactors    = EvolutionFactors(TmdObj, Mub, Mub, PerturbativeOrder, Alphas);

  // Tabulate matched TMDs on a grid in the impact parameter b.
  const int    nb   = 50;
  const double bmin = 5e-5;
  const double bmax = 30;
  const int    intd = 3;
  const auto TabFunc    = [] (double const& b) -> double{ return log(b); };
  const auto InvTabFunc = [] (double const& fb) -> double{ return exp(fb); };
  const TabulateObject<Set<Distribution>> TabTMDs{MatchedTMDPDFs, nb, bmin, bmax, intd, {}, TabFunc, InvTabFunc};

  // =================================================================
  // Cross section
  // =================================================================
  // Set kinematics cross section.
  const double Vs    = 8000;
  const double Q     = 91.2;
  const double y     = 2.5;
  const double qT    = 5;

  // Derived quantities.
  const double muf   = Q;
  const double zetaf = Q * Q;
  const double lx1   = log( Q * exp(y) / Vs );
  const double lx2   = log( Q * exp(-y) / Vs );

  // Create distributions with the x-space interpolation functions
  // computed in "x1" and "x2" to eventually multiply to the matched
  // TMDs.
  Distribution wx1{g};
  Distribution wx2{g};
  // Fill joint grids.
  for (int alpha = 0; alpha < (int) g.GetJointGrid().nx(); alpha++)
    {
      wx1.PushJointGrid(wx1.Interpolant(alpha, lx1, g.GetJointGrid()));
      wx2.PushJointGrid(wx2.Interpolant(alpha, lx2, g.GetJointGrid()));
    }
  // Fill subgrids
  for (int ig = 0; ig < (int) g.nGrids(); ig++)
    {
      bool next = true;
      for (int alpha = 0; alpha < g.GetSubGrid(ig).nx(); alpha++)
	{
	  wx1.PushSubGrid(wx1.Interpolant(alpha, lx1, g.GetSubGrid(ig)), next);
	  wx2.PushSubGrid(wx2.Interpolant(alpha, lx2, g.GetSubGrid(ig)), next);
	  next = false;
	}
    }

  // Compute Ktau factors and rotated TMD PDFs times x-space
  // interpolation functions of the grid of "TabTMDs" (don't use the
  // last two nodes onf the grid).
  vector<double> Ktau;
  vector<map<int,Distribution>> F1GridPhys;
  vector<map<int,Distribution>> F2GridPhys;

  const vector<double> bGrid = TabTMDs.GetQGrid();
  const vector<Set<Distribution>> FGridEv = TabTMDs.GetQGridValues();
  for (int tau = 0; tau < (int) bGrid.size() - 2; tau++)
    {
      const int taul = max(tau - intd, 0);
      const int tauu = min(tau + 1, nb - 1); 
      const auto func = [=] (double const& b) -> double
	{
	  return b * j0(qT * b) * pow(EvolFactors(b, muf, zetaf)[1],2) * TabTMDs.Interpolant(0, tau, TabFunc(b));
	};
      const Integrator integrand{func};
      Ktau.push_back(integrand.integrate(bGrid[taul], bGrid[tauu], {bGrid.begin() + taul + 1, bGrid.begin() + tauu}, eps7));

      // Rotate matched TMDs from the evolution to the physical basis.
      const map<int,Distribution> f = QCDEvToPhys(FGridEv[tau].GetObjects());
      map<int,Distribution> f1;
      map<int,Distribution> f2;
      // Apply interpolation function vectors.
      for (auto const& d : f)
	{
	  const Distribution d1 = wx1 * d.second;
	  const Distribution d2 = wx2 * d.second;
	  f1.insert({d.first, d1});
	  f2.insert({d.first, d2});
	}
      F1GridPhys.push_back(f1);
      F2GridPhys.push_back(f2);
    }

  cout << "Total computation... ";
  t.stop();

  return 0;
}

