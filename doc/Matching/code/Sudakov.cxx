/*
  Author: Valerio Bertone
 */

// APFEL++ libs
#include "apfel/apfelxx.h"
#include "apfel/gammacusp.h"
#include "apfel/gammacs.h"
#include "apfel/gammav.h"
#include "apfel/betaqcd.h"

using namespace std;
using namespace apfel;

int main() {
  const vector<double> Masses{0, 0, 0};

  // Reference value of the strong coupling and heavy-quark
  // thresholds.
  const double AlphaQCDRef = 0.35;
  const double MuQCDRef    = sqrt(2);

  // Iniatialize the running of the coupling at all available
  // perturbative orders.
  AlphaQCD as{AlphaQCDRef, MuQCDRef, Masses, 0};

  // Initialize TMD and DGLAP objects.
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,5e-1,3}, SubGrid{60,7e-1,3}}};

  // Alpha_s
  const auto Alphas = [&] (double const& mu) -> double{ return as.Evaluate(mu); };

  // Get relevant objects.
  const auto TmdObj = InitializeTmdObjects(g, Masses);

  // Get TMD evolution factors.
  const auto EvolFactors = EvolutionFactors(TmdObj, Alphas, 2);

  const int nb = 10;
  const double bmin = 0.1;
  const double bmax = 5;
  const double bstep = exp( log(bmax / bmin) / ( nb - 1 ) );
  const vector<double> Qv{2, 5, 10, 100};

  // Coefficient of the expansion
  const double S11 = CF * CSd10() + gammaVq0();
  const double S12 = - CF * GammaCusp0() / 4;

  const double S21 = CF * CSd11() + gammaVq1(3);
  const double S22 = beta0qcd(3) * CF * CSd10() + beta0qcd(3) * gammaVq0() / 2 - CF * GammaCusp1(3) / 4;
  const double S23 = - beta0qcd(3) * GammaCusp0() / 6;

  const double S21w = S21;
  const double S22w = S22 + pow(S11, 2) / 2;
  const double S23w = S23 + S11 * S12;
  const double S24w = pow(S12, 2) / 2;

  cout << scientific;
  for (auto const& Q : Qv)
    {
      double b = bmin;
      const double Q2  = Q * Q;
      const double as  = Alphas(Q) / FourPi;
      const double as2 = as * as;
      for (int ib = 0; ib < nb; ib++)
	{
	  const double mub2 = pow(2 * exp(-emc) / b, 2);
	  const double L1   = log(Q2 / mub2);
	  const double L2   = L1 * L1;
	  const double L3   = L2 * L1;
	  const double L4   = L3 * L1;
	  const double expand = 1 + as * ( S11 * L1 + S12 * L2 ) + as2 * ( S21w * L1 + S22w * L2 + S23w * L3 + S24w * L4 );

	  const vector<double> ef = EvolFactors(b, Q, Q2);
	  cout << b << "\t" << L1 << "\t" << ef[1] * ef[1] << "\t" << expand << endl;
	  b *= bstep;
	}
      cout << "\n";
    }

  return 0;
}
