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
#include "apfel/apfelxx.h"

using namespace std;
using namespace apfel;

// b* prescription
double bstar(double const& b, double const& Q)
{
  const double bmax = 2 * exp( - apfel::emc);
  return sqrt( pow(b, 2) / ( 1 + pow(b / bmax, 2) ) );//+ pow(bmax / Q, 2) );
}

// Non-perturbative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double g1 = 0.02;
  const double g2 = 0.5;
  const double Q0 = 1;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

int main() {
  // Kinematics in terms of the variables in which TIMBA is
  // differential.
  const double EP  = 820;
  const double El  = 27.6;
  const double VS  = sqrt( 4 * EP * El );
  const double x   = 1e-3;
  const double z   = 1e-1;
  const double y   = 0.5;
  const int    pto = 2;

  // PDF and FF sets
  LHAPDF::PDF* PDFs = LHAPDF::mkPDF("CT14nlo");
  //LHAPDF::PDF* FFs  = LHAPDF::mkPDF("NNFF10_PIsum_nlo");
  //LHAPDF::PDF* PDFs = LHAPDF::mkPDF("NNPDF31_nlo_as_0118");
  LHAPDF::PDF* FFs  = LHAPDF::mkPDF("NNFF11_HadronSum_nlo");
  //LHAPDF::PDF* PDFs = LHAPDF::mkPDF("CT14nlo");
  //LHAPDF::PDF* FFs  = LHAPDF::mkPDF("DSS07_NLO_HadronSum");

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
  const auto EvolFactors = EvolutionFactors(TmdObj, Alphas, pto);

  // Ogata-quadrature object of degree zero.
  apfel::OgataQuadrature OgataObj{};

  // Function for the computation of the resummed cross section.
  const auto xsecRes = [=,&g] (double const& VS, double const& x, double const& y, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double Q2 = x * y * VS * VS;
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Get matched TMD PDFs and FFs.
      const auto Qb = [Q] (double const&) -> double{ return Q; };
      const auto MatchedTmdPDFs = MatchTmdPDFs(TmdObj, CollPDFs, Alphas, pto);
      const auto MatchedTmdFFs  = MatchTmdFFs(TmdObj,  CollFFs,  Alphas, pto);
      //const auto MatchedTmdPDFs = MatchTmdPDFs(TmdObj, EvolvedPDFs, Alphas, pto);
      //const auto MatchedTmdFFs  = MatchTmdFFs(TmdObj,  EvolvedFFs,  Alphas, pto);

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
	const vector<double> ef = EvolFactors(bstar(b, Q), Q, Q2);
	const auto EvolvedTMDPDFs = ef * MatchedTmdPDFs(bstar(b, Q)) * fNP(x, b, Q2);
	const auto EvolvedTMDFFs  = ef * MatchedTmdFFs(bstar(b, Q)) * fNP(z, b, Q2);

	map<int,Distribution> PDFs = QCDEvToPhys(EvolvedTMDPDFs.GetObjects());
	map<int,Distribution> FFs  = QCDEvToPhys(EvolvedTMDFFs.GetObjects());
	double lumi = 0;
	for (int i = 1; i <= nf; i++)
	  lumi += QCh2[i-1] * ( PDFs.at(i).Evaluate(x) * FFs.at(i).Evaluate(z) + PDFs.at(-i).Evaluate(x) * FFs.at(-i).Evaluate(z) );
	return b * lumi;
      };

      // Kinmatic factors inclusing the hard form factor.
      const double hcs = 2 * qT * 2 * M_PI * alpha2 * Yp * HardFactorSIDIS(1, as * FourPi, nf, pto) / z / x / y / Q2;

      // Integrate over b.
      return hcs * OgataObj.transform(TMDLumib, qT);
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

  const int    nqT    = 50;
  const double qTmin  = 0.01;
  const double qTmax  = 100;
  const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );

  cout << scientific;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      cout << qT << "  "
	   << xsecRes(VS, x, y, z, qT) << "  "
	   << xsecAsy(VS, x, y, z, qT) << "  "
	   << endl;
      qT *= qTstep;
    }

  return 0;
}
