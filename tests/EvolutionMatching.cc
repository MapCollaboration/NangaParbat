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

#include "LHAPDF/LHAPDF.h"

using namespace apfel;
using namespace std;

int main()
{
  cout << __PRETTY_FUNCTION__ << "\n";

  // Open LHAPDF sets.
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF("MMHT2014nlo68cl");
  LHAPDF::PDF* distff  = LHAPDF::mkPDF("DSS14_NLO_Pip");

  // Thresholds.
  const vector<double> Thresholds{distpdf->quarkThreshold(1),
                                  distpdf->quarkThreshold(2),
                                  distpdf->quarkThreshold(3),
                                  distpdf->quarkThreshold(4),
                                  distpdf->quarkThreshold(5),
                                  distpdf->quarkThreshold(6)};

  // Alpha_s.
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

  // Perturbative order.
  const int PerturbativeOrder = 1;

  // x-space grid.
  const Grid g{{{100,1e-5,3}, {60,1e-1,3}, {50,6e-1,3}, {100,8e-1,3}}};

  // Initialize TMD objects.
  const auto TmdObj = InitializeTmdObjects(g, Thresholds);

  // Get evolution factors.
  const auto QuarkEvolFactor = QuarkEvolutionFactor(TmdObj, Alphas, PerturbativeOrder);

  // Rotate PDF and FF sets into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> map<int,double> { return PhysToQCDEv(distpdf->xfxQ(x,mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> map<int,double> { return PhysToQCDEv(distff->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> Set<Distribution> { return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)}; };
  const auto EvolvedFFs  = [=,&g] (double const& mu) -> Set<Distribution> { return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotFFs, mu)}; };

  // Tabulate PDFs and FFs
  const TabulateObject<Set<Distribution>> TabPDFs{EvolvedPDFs, 50, 1, 100, 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> Set<Distribution> { return TabPDFs.Evaluate(mu); };

  const TabulateObject<Set<Distribution>> TabFFs{EvolvedFFs, 50, 1, 100, 3, Thresholds};
  const auto CollFFs = [&] (double const& mu) -> Set<Distribution> { return TabFFs.Evaluate(mu); };

  // Match TMD PDFs and FFs
  const auto MatchedTMDPDFs = MatchTmdPDFs(TmdObj, CollPDFs, Alphas, PerturbativeOrder);
  const auto MatchedTMDFFs  = MatchTmdFFs(TmdObj, CollFFs, Alphas, PerturbativeOrder);

  // Test scales
  const vector<double> Qg{2, 10, 91};

  // Kinematics
  const int nb       = 10;
  const double bmin  = 0.01;
  const double bmax  = 1;
  const double bstep = exp( log(bmax / bmin) / ( nb - 1 ) );

  // Print evolution factors
  Timer t;

  for (auto const& Q : Qg)
    {
      const double Q2 = Q * Q;
      double b = bmin;
      cout << scientific << "\n";
      cout << " Q [GeV]      "
           << " b [1/GeV]    "
           << " mub [GeV]    "
           << " Ev. (sigma)  "
           << endl;
      for (int ib = 0; ib < nb; ib++)
        {
          const double mub = 2 * exp(- emc) / b;
          const double evfq = QuarkEvolFactor(b, Q, Q2);
          cout << Q << "  " << b << "  " <<  mub << "  " << evfq << endl;
          b *= bstep;
        }
      cout << "\n";
    }
  t.stop();

  // Print matched PDFs
  int nx       = 10;
  double xmin  = 1e-5;
  double xmax  = 0.9;
  double xstep = exp( log(xmax / xmin) / ( nx - 1 ) );

  t.start();
  for (auto const& Q : Qg)
    {
      const double b = 2 * exp(- emc) / Q;
      double x = xmin;
      cout << scientific << "\n";
      cout << " Q [GeV]      "
           << " b [1/GeV]    "
           << "      x       "
           << "   LHAPDF     "
           << "  down PDF    "
           << endl;
      for (int ib = 0; ib < nb; ib++)
        {
          const map<int,Distribution> mpdf = QCDEvToPhys(MatchedTMDPDFs(b).GetObjects());
          cout << Q << "  " << b << "  " <<  x << "  " << mpdf.at(1).Evaluate(x) << "  " << distpdf->xfxQ(1,x,Q) << endl;
          x *= xstep;
        }
      cout << "\n";
    }
  t.stop();

  // Print matched FFs
  nx    = 10;
  xmin  = 5e-2;
  xmax  = 0.9;
  xstep = exp( log(xmax / xmin) / ( nx - 1 ) );

  t.start();
  for (auto const& Q : Qg)
    {
      const double b = 2 * exp(- emc) / Q;
      double x = xmin;
      cout << scientific << "\n";
      cout << " Q [GeV]      "
           << " b [1/GeV]    "
           << "      x       "
           << "   LHAPDF     "
           << "  down FF     "
           << endl;
      for (int ib = 0; ib < nb; ib++)
        {
          const map<int,Distribution> mff = QCDEvToPhys(MatchedTMDFFs(b).GetObjects());
          cout << Q << "  " << b << "  " <<  x << "  " << mff.at(1).Evaluate(x) << "  " << distff->xfxQ(1,x,Q) << endl;
          x *= xstep;
        }
      cout << "\n";
    }
  t.stop();

  return 0;
}
