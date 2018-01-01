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
#include "apfel/doubleobject.h"

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
  // PDF and FF sets
  //LHAPDF::PDF* PDFs = LHAPDF::mkPDF("NNPDF31_nlo_as_0118");
  //LHAPDF::PDF* FFs  = LHAPDF::mkPDF("NNFF10_HadronSum_nlo");
  LHAPDF::PDF* PDFs = LHAPDF::mkPDF("CT14nlo");
  LHAPDF::PDF* FFs  = LHAPDF::mkPDF("DSS07_NLO_HadronSum");

  // Heavy quark masses.
  const double mc = PDFs->quarkThreshold(4);
  const double mb = PDFs->quarkThreshold(5);
  const double mt = PDFs->quarkThreshold(6);
  const vector<double> Masses{0, 0, 0, mc, mb, mt};

  // Function for the computation of the fixed-order cross section at
  // O(as).
  const auto xsecFO = [=] (double const& VS, double const& x, double const& y, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double Q2 = x * y * VS * VS;
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Useful definitions
      const double qToQ2  = qT2 / Q2;
      const double zmax   = ( 1 - x ) / ( 1 - x * ( 1 - qToQ2 ) );
      const double y2     = y * y;
      const double Yp     = 1 + pow(1-y, 2);
      const int nf        = NF(Q, Masses);
      const double as     = PDFs->alphasQ(Q) / FourPi;
      const double alpha2 = pow(1./137,2);

      // Define integrands.
      const auto Xsec = [=] (double const& zb) -> double
      {
	const double xb0 = ( 1 - zb ) / ( 1 - zb * ( 1 - qToQ2 ) );
	const double xt  = x / xb0;
	const double zt  = z / zb;
	if (xt >= 1 || zt >=1)
	  return 0;

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

	return 2 * qT * 2 * M_PI * alpha2 * Yp * integrand / x / y / Q2;
      };

      // Integrate over z.
      const Integrator Integral{Xsec};
      return Integral.integrate(z, zmax, 1e-5);
    };

  // Initialize space- and time-like splitting functions.
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,5e-1,3}, SubGrid{60,7e-1,3}}};
  const auto PDFObj = InitializeDglapObjectsQCD(g, Masses);
  const auto FFObj  = InitializeDglapObjectsQCDT(g, Masses);
 
  // Function for the computation of the asymptotic cross section at
  // O(as).
  const auto xsecAsy = [=,&g] (double const& VS, double const& x, double const& y, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double Q2 = x * y * VS * VS;
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Useful definitions
      const double qToQ2  = qT * qT / Q2;
      const double y2     = y * y;
      const double Yp     = 1 + pow(1-y, 2);
      const int nf        = NF(Q, Masses);
      const double as     = PDFs->alphasQ(Q) / FourPi;
      const double alpha2 = pow(1./137,2);
      const double L      = 4 * CF * ( - log(qToQ2) - 3. / 2 );

      // Create sets of distributions for PDFs and FFs.
      const map<int,Distribution> DistPDFs = DistributionMap(g, [=] (double const& x, double const& Q)->map<int,double>{ return PDFs->xfxQ(x,Q); }, Q);
      const map<int,Distribution> DistFFs  = DistributionMap(g, [=] (double const& z, double const& Q)->map<int,double>{ return FFs->xfxQ(z,Q); }, Q);

      DoubleObject<Distribution> DoubDist;
      for (int j = -nf; j <= nf; j++)
	{
	  if (j == 0)
	    continue;

	  const Set<Operator> Psl = PDFObj.at(nf).SplittingFunctions.at(0);
	  const Set<Operator> Ptl = FFObj.at(nf).SplittingFunctions.at(0);

	  const Distribution Ppdf = Psl.at(3) * DistPDFs.at(j) + Psl.at(4) * DistPDFs.at(21) / 2 / nf;
	  const Distribution Pff  = Ptl.at(3) * DistFFs.at(j)  + Ptl.at(4) * DistFFs.at(21) / 2 / nf;

	  DoubDist.AddTerm({QCh2[abs(j)-1] * L, DistPDFs.at(j), DistFFs.at(j)});
	  DoubDist.AddTerm({QCh2[abs(j)-1], DistPDFs.at(j), Pff});
	  DoubDist.AddTerm({QCh2[abs(j)-1], Ppdf, DistFFs.at(j)});
	}

      return 2 * qT * 2 * M_PI * alpha2 * Yp * ( as * DoubDist.Evaluate(x,z) / qT2 / z ) / x / y / Q2;
    };

  // Kinematics in terms of the variables in which TIMBA is
  // differential.
  const double EP = 820;
  const double El = 27.6;
  const double VS = sqrt( 4 * EP * El );
  const double x  = 1e-3;
  const double z  = 1e-1;
  const double y  = 0.5;

  const int    nqT    = 100;
  const double qTmin  = 0.01;
  const double qTmax  = 20;
  const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );

  cout << scientific;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      cout << qT << "  "
	   << xsecFO(VS, x, y, z, qT) << "  "
	   << xsecAsy(VS, x, y, z, qT) << "  "
	   << endl;
      qT *= qTstep;
    }

  return 0;
}
