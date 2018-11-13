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
#include "apfel/tmdbuilder.h"
#include "apfel/ogataquadrature.h"
#include "apfel/tmdcrosssections.h"

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
  const double EP = 820;
  const double El = 27.6;
  const double VS = sqrt( 4 * EP * El );
  const double x  = 1e-3;
  const double z  = 1e-1;
  const double y  = 0.5;

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

  // Initialize TMD and DGLAP objects.
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,5e-1,3}, SubGrid{60,7e-1,3}}};

  // Alpha_s
  const auto Alphas = [&] (double const& mu) -> double{ return PDFs->alphasQ(mu); };

  // Rotate distributions into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> map<int,double>{ return PhysToQCDEv(PDFs->xfxQ(x,mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> map<int,double>{ return PhysToQCDEv(FFs->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> Set<Distribution>{ return Set<Distribution>{EvolutionBasisQCD{NF(mu, Masses)}, DistributionMap(g, RotPDFs, mu)}; };
  const auto EvolvedFFs  = [=,&g] (double const& mu) -> Set<Distribution>{ return Set<Distribution>{EvolutionBasisQCD{NF(mu, Masses)}, DistributionMap(g, RotFFs, mu)}; };

  // Tabulate PDFs
  const TabulateObject<Set<Distribution>> TabPDFs{EvolvedPDFs, 50, PDFs->qMin(), PDFs->qMax(), 3, Masses};
  const TabulateObject<Set<Distribution>> TabFFs{EvolvedFFs,   50, FFs->qMin(),  FFs->qMax(),  3, Masses};
  const auto CollPDFs = [&] (double const& mu) -> Set<Distribution> { return TabPDFs.Evaluate(mu); };
  const auto CollFFs  = [&] (double const& mu) -> Set<Distribution> { return TabFFs.Evaluate(mu); };

  // Get relevant objects.
  const auto PDFObj = InitializeDglapObjectsQCD(g, Masses);
  const auto FFObj  = InitializeDglapObjectsQCDT(g, Masses);
  const auto TmdObj = InitializeTmdObjects(g, Masses);

  // Get TMD evolution factors.
  const auto Mub = [] (double const& b) -> double{ return 2 * exp(- emc) / b; };
  const auto EvolFactors = EvolutionFactors(TmdObj, Mub, Mub, 1, Alphas);

  // Function for the computation of the resummed cross section.
  const auto xsecRes = [=,&g] (double const& VS, double const& x, double const& y, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double Q2 = x * y * VS * VS;
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Get matched TMD PDFs and FFs.
      const auto Qb = [Q] (double const&) -> double{ return Q; };
      const auto MatchedTmdPDFs = MatchTmdPDFs(TmdObj, PDFObj, CollPDFs, Qb, 1, Alphas);
      const auto MatchedTmdFFs  = MatchTmdFFs(TmdObj,  FFObj,  CollFFs,  Qb, 1, Alphas);

      // Useful definitions
      const double qToQ2  = qT * qT / Q2;
      const double y2     = y * y;
      const double Yp     = 1 + pow(1-y, 2);
      const int nf        = NF(Q, Masses);
      const double as     = PDFs->alphasQ(Q) / FourPi;
      const double alpha2 = pow(1./137,2);
      const double L      = 4 * CF * ( - log(qToQ2) - 3. / 2 );

      // Function to be integrated over b
      const auto TMDLumib = [=] (double const& b) -> double
      {
	// Evolve TMDs.
	const vector<double> ef = EvolFactors(b, Q, Q2);
	const auto EvolvedTMDPDFs = ef * MatchedTmdPDFs(b);
	const auto EvolvedTMDFFs  = ef * MatchedTmdFFs(b);

	map<int,Distribution> PDFs = QCDEvToPhys(EvolvedTMDPDFs.GetObjects());
	map<int,Distribution> FFs  = QCDEvToPhys(EvolvedTMDFFs.GetObjects());
	double lumi = 0;
	for (int i = 1; i <= nf; i++)
	  lumi += QCh2[i-1] * ( PDFs.at(i).Evaluate(x) * FFs.at(i).Evaluate(z) + PDFs.at(-i).Evaluate(x) * FFs.at(-i).Evaluate(z) );
	return lumi / z;
      };

      // Kinmatic factors inclusing the hard form factor.
      const double hcs = 2 * qT * 2 * M_PI * alpha2 * Yp * HardCrossSectionSIDIS(1, as * FourPi, nf, 1) / x / y / Q2;

      // Integrate over b.
      return hcs * OgataQuadrature(TMDLumib, qT);
    };

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

  const int    nqT    = 200;
  const double qTmin  = 0.01;
  const double qTmax  = 100;
  const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );

  cout << scientific;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      const double FO  = xsecFO(VS, x, y, z, qT);
      const double Res = xsecRes(VS, x, y, z, qT);
      const double Asy = xsecAsy(VS, x, y, z, qT);
      cout << qT << "  "
	   << FO  << "  "
	   << Res << "  "
	   << Asy << "  "
	   << FO + Res - Asy << "  "
	   << endl;
      qT *= qTstep;
    }

  return 0;
}
