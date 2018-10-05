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
//#include <apfel/tmdcrosssections.h>
#include <apfel/ogataquadrature.h>
#include <apfel/evolutionbasisqcd.h>

#include <cmath>
#include <map>
#include <iomanip>

#include "LHAPDF/LHAPDF.h"

using namespace apfel;
using namespace std;

int main()
{
  cout << __PRETTY_FUNCTION__ << "\n";

  // Open LHAPDF set.
  LHAPDF::PDF* PDFs = LHAPDF::mkPDF("MMHT2014nnlo68cl");
  LHAPDF::PDF* FFs  = LHAPDF::mkPDF("DSS14_NLO_Pip");

  // Thresholds.
  const vector<double> Thresholds{PDFs->quarkThreshold(1),
      PDFs->quarkThreshold(2),
      PDFs->quarkThreshold(3),
      PDFs->quarkThreshold(4),
      PDFs->quarkThreshold(5),
      PDFs->quarkThreshold(6)};

  // Perturbative order.
  const int PerturbativeOrder = PDFs->orderQCD();

  // =================================================================
  // Alpha_s from PDFs
  // =================================================================
  const auto Alphas = [&] (double const& mu) -> double{ return PDFs->alphasQ(mu); };

  // =================================================================
  // Collinear PDFs and FFs
  // =================================================================
  // x-space grid.
  const Grid g{{SubGrid{100,1e-5,3}, SubGrid{60,1e-1,3}, SubGrid{50,6e-1,3}, SubGrid{50,8e-1,3}}};

  // Rotate PDF and FF sets into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> map<int,double>{ return PhysToQCDEv(PDFs->xfxQ(x,mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> map<int,double>{ return PhysToQCDEv(FFs->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> Set<Distribution>{ return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)}; };
  const auto EvolvedFFs  = [=,&g] (double const& mu) -> Set<Distribution>{ return Set<Distribution>{EvolutionBasisQCD{NF(mu, Thresholds)}, DistributionMap(g, RotFFs, mu)}; };

  // =================================================================
  // TMD PDFs
  // =================================================================
  // Initialize TMD and DGLAP objects.
  const auto TmdObj = InitializeTmdObjects(g, Thresholds);
  const auto PDFObj = InitializeDglapObjectsQCD(g, Thresholds);
  const auto FFObj  = InitializeDglapObjectsQCDT(g, Thresholds);

  // Function that returns the inital scale mu as a function of the
  // impact parameter b.
  const auto Mub = [] (double const& b) -> double
    {
      const double C0 = 2 * exp(- emc);
      return C0 / b + 2;
    };

  // Non-perturbative TMD function.
  const auto fNP = [] (double const&, double const&) -> double{ return 1; };

  // Get evolved TMDs (this assumes the zeta-prescription).
  const auto EvolvedTMDPDFs = BuildTmdPDFs(TmdObj, PDFObj, EvolvedPDFs, fNP, Mub, Mub, PerturbativeOrder, Alphas);
  const auto EvolvedTMDFFs  = BuildTmdFFs(TmdObj, FFObj,  EvolvedFFs,  fNP, Mub, Mub, PerturbativeOrder, Alphas);

  // EW charges.
  //const auto fEWCharges = [=] (double const&) -> vector<double>{ return QCh2; };

  // Kinematics
  const double Vs = 8000;
  const double x  = 0.1;
  const double z  = 0.1;
  const double Q  = 91;
  const double Q2 = Q * Q;

  // Test evolution factors and matching
  const auto EvolFactors = EvolutionFactors(TmdObj, Mub, Mub, PerturbativeOrder, Alphas);
  const auto mFFs  = MatchTmdFFs(TmdObj, FFObj, EvolvedFFs, Mub, PerturbativeOrder, Alphas);
  const auto mPDFs = MatchTmdPDFs(TmdObj, PDFObj, EvolvedPDFs, Mub, PerturbativeOrder, Alphas);

  const int nbT = 10;
  const double bTmin  = 0.1;
  const double bTmax  = 10;
  const double bTstep = ( bTmax - bTmin ) / ( nbT - 1 );

  double bT = bTmin;
  cout << scientific;
  for (int ibT = 0; ibT < nbT; ibT++)
    {
      const Set<Distribution> ffs = EvolvedTMDFFs(bT, Q, Q2);
      const Set<Distribution> pdfs = EvolvedTMDPDFs(bT, Q, Q2);
      cout << bT << "\t" 
	   << ffs.at(0).Evaluate(z) / pow(z, 3) << "\t"
	   << ffs.at(1).Evaluate(z) / pow(z, 3) << "\t"
	   << ffs.at(2).Evaluate(z) / pow(z, 3) << "\t"
	   << ffs.at(3).Evaluate(z) / pow(z, 3) << "\t"
	   << pdfs.at(0).Evaluate(x) / x << "\t"
	   << pdfs.at(1).Evaluate(x) / x  << "\t"
	   << pdfs.at(2).Evaluate(x) / x  << "\t"
	   << pdfs.at(3).Evaluate(x) / x  << "\t"
	   << endl;
      bT += bTstep;
    }

  // Construct the TMD luminosisty in b scale to be fed to be
  // trasformed in qT space.
  const auto TMDLumib = [=] (double const& b) -> double
    {
      // Get map of the TMDs in "x" and "z" and rotate them into the
      // physical basis.
      map<int,Distribution> PDFs = QCDEvToPhys(EvolvedTMDPDFs(b, Q, Q2).GetObjects());
      map<int,Distribution> FFs  = QCDEvToPhys(EvolvedTMDFFs(b, Q, Q2).GetObjects());
      double lumi = 0;
      for (int i = 1; i <= NF(Mub(b), Thresholds); i++)
	lumi += QCh2[i-1] * ( PDFs.at(i).Evaluate(x) * FFs.at(i).Evaluate(z) + PDFs.at(-i).Evaluate(x) * FFs.at(-i).Evaluate(z) );
      return lumi / pow(z,3);
    };

  // Cross section function
  Timer t;
  cout << "\n  qT [GeV]   "
       << "   F_{UU}"
       << endl;
  for (int j = 0; j < 50; j++)
    {
      const double q = 0.2 * Q * z * ( j + 1 ) / 5;
      cout << q << "  " << OgataQuadrature(TMDLumib, q, 1e-7, 0.001 * M_PI) << endl;
    }
  return 0;
}
