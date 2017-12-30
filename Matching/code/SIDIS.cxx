/*
  Author: Valerio Bertone
 */

// Standard libs
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <glob.h>
#include <iomanip>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <functional>

// LHAPDF libs
#include "LHAPDF/LHAPDF.h"

// APFEL++ libs
#include "apfel/dglapbuilder.h"
#include "apfel/grid.h"
#include "apfel/timer.h"
#include "apfel/alphaqcd.h"
#include "apfel/tabulateobject.h"
#include "apfel/evolutionbasisqcd.h"
#include "apfel/matchingbasisqcd.h"
#include "apfel/dglap.h"
#include "apfel/rotations.h"
#include "apfel/constants.h"
#include "apfel/tools.h"
#include "apfel/integrator.h"

using namespace std;
using namespace apfel;

double B2FOqq(double const& x, double const& z, double const& qT, double const& Q)
{
  return 2 * CF * ( ( 1 - x ) * ( 1 - z ) + 4 * x * z + ( 1 + x * x * z * z ) * Q * Q / x / z / qT / qT ); 
}

double B2FOqg(double const& x, double const& z, double const& qT, double const& Q)
{
  return 2 * TR * ( 8 * x * ( 1 - x ) + ( x * x + ( 1 - x ) * ( 1 - x ) ) * ( z * z + ( 1 - z ) * ( 1 - z ) ) * ( 1 - x ) * Q * Q / x / z / z / qT / qT ); 
}

double B2FOgq(double const& x, double const& z, double const& qT, double const& Q)
{
  return 2 * CF * ( ( 1 - x ) * z + 4 * x * ( 1 - z ) + ( 1 + x * x * ( 1 - z ) * ( 1 - z ) ) * ( 1 - z ) * Q * Q / x / z / z / qT / qT ); 
}

double BLFOqq(double const& x, double const& z)
{
  return 8 * CF * x * z;
}

double BLFOqg(double const& x, double const&)
{
  return 16 * TR * x * ( 1 -  x );
}

double BLFOgq(double const& x, double const& z)
{
  return 8 * CF * x * ( 1 - z );
}

int main() {
  // Kinematics in terms of the variables in which TIMBA is
  // differential.
  const double EP  = 820;
  const double El  = 27.6;
  const double VS  = sqrt( 4 * EP * El );
  const double x   = 5e-5;
  const double Q2  = 2;
  const double pT  = 3.5;
  const double eta = 0;

  // Internal kinematic variables
  const double Q  = sqrt(Q2);
  const double y  = Q2 / x / VS / VS;
  const double qT = exp(-eta) * VS * sqrt( y * ( 1 - x ) );
  const double z  = pT / qT;

  // PDF and FF sets
  LHAPDF::PDF* PDFs = LHAPDF::mkPDF("NNPDF31_nlo_as_0118");
  LHAPDF::PDF* FFs  = LHAPDF::mkPDF("NNFF10_HadronSum_nlo");

  // Heavy quark masses.
  const double mc = PDFs->quarkThreshold(4);
  const double mb = PDFs->quarkThreshold(5);
  const double mt = PDFs->quarkThreshold(6);
  const vector<double> Masses{0, 0, 0, mc, mb, mt};

  // Useful definitions
  const double qToQ2  = qT * qT / Q2;
  const double zmax   = ( 1 - x ) / ( 1 - x * ( 1 - qToQ2 ) );
  const double y2     = y * y;
  const double Yp     = 1 + pow(1-y, 2);
  const double nf     = NF(Q, Masses);
  const double as     = PDFs->alphasQ(Q) / FourPi;
  const double alpha2 = pow(1./137,2);
  const double hc2    = 0.38942957e6;

  // Define integrands.
  const auto Xsec = [=] (double const& zb) -> double
    {
      const double xb0 = ( 1 - zb ) / ( 1 - zb * ( 1 - qToQ2 ) );
      const double xt  = x / xb0;
      const double zt  = z / zb;

      // Distribution combinations
      double qq = 0;
      double qg = 0;
      double gq = 0;
      const double gPDF = PDFs->xfxQ(21,xt,Q);
      const double gFF  = FFs->xfxQ(21,zt,Q);
      for (int i = 1; i <= nf; i++)
	{
	  qq += QCh2[i-1] * ( PDFs->xfxQ(i,xt,Q) * FFs->xfxQ(i,zt,Q) + PDFs->xfxQ(-i,xt,Q) * FFs->xfxQ(-i,zt,Q) );
	  qg += QCh2[i-1] * gPDF * ( FFs->xfxQ(i,zt,Q) + FFs->xfxQ(-i,zt,Q) );
	  gq += QCh2[i-1] * ( PDFs->xfxQ(i,xt,Q) + PDFs->xfxQ(-i,xt,Q) ) * gFF;
	}
      qq /= xt * zt;
      qg /= xt * zt;
      gq /= xt * zt;

      // Construct integrand
      const double integrand = as * x * xb0 *
      ( ( B2FOqq(xb0, zb, qT, Q) - y2 / Yp * BLFOqq(xb0, zb) ) * qq
      + ( B2FOqg(xb0, zb, qT, Q) - y2 / Yp * BLFOqg(xb0, zb) ) * qg
      + ( B2FOgq(xb0, zb, qT, Q) - y2 / Yp * BLFOgq(xb0, zb) ) * gq ) / Q / Q / ( 1 - zb );

      return 2 * pT * hc2 * 2 * M_PI * alpha2 * Yp * integrand / z / x / pow(Q,4);
    };

  // Integrate
  // Integrate also over x
  const Integrator Integral{Xsec};
  const double value = Integral.integrate(z, zmax, 1e-5);

  cout << x << "  " << Q2 << "  " << pT << "  " << eta << "  " << value << endl;

  return 0;
}
