/*
 * Author: Valerio Bertone
 */

// LHAPDF libs
#include "LHAPDF/LHAPDF.h"

// APFEL++ libs
#include "apfel/apfelxx.h"

// APFEL libs
#include "apfel/APFEL.h"

// Fixed-order coefficient functions
#include "FOCoeffFuncs.h"

// b* prescription
double bstar(double const& b, double const& Q)
{
  const double bmax = 2 * exp( - apfel::emc) / 2;
  return sqrt( pow(b, 2) / ( 1 + pow(b / bmax, 2) ) + pow(bmax / Q, 2) );
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
  // Kinematics
  const double y  = 0.439;
  const double x  = 0.157;
  const double z  = 0.35;
  const double Q2 = 20;

  // PDF and FF sets
  LHAPDF::PDF* PDFs = LHAPDF::mkPDF("CT14nlo");
  LHAPDF::PDF* FFs  = LHAPDF::mkPDF("DSS07_NLO_HadronSum");

  // Heavy quark masses.
  const double mc = PDFs->quarkThreshold(4);
  const double mb = PDFs->quarkThreshold(5);
  const double mt = PDFs->quarkThreshold(6);
  const std::vector<double> Masses{0, 0, 0, mc, mb, mt};

  // Initialize TMD and DGLAP objects.
  const apfel::Grid gPDF{{{100, 1e-3, 3}, {60, 1e-1, 3}, {50, 5e-1, 3}, {60, 7e-1, 3}}};
  const apfel::Grid gFF{{{100, 1e-2, 3}, {60, 1e-1, 3}, {50, 5e-1, 3}, {60, 7e-1, 3}}};

  // Alpha_s
  const auto Alphas = [&] (double const& mu) -> double{ return PDFs->alphasQ(mu); };

  // Rotate distributions into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(PDFs->xfxQ(x,mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(FFs->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&gPDF] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Masses)}, DistributionMap(gPDF, RotPDFs, mu)};
    };
  const auto EvolvedFFs  = [=,&gFF] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Masses)}, DistributionMap(gFF, RotFFs, mu)};
    };

  // Get relevant objects.
  const auto PDFObj = InitializeDglapObjectsQCD(gPDF, Masses);
  const auto FFObj  = InitializeDglapObjectsQCDT(gFF, Masses);
  const auto TmdObjPDF = InitializeTmdObjects(gPDF, Masses);
  const auto TmdObjFF  = InitializeTmdObjects(gFF, Masses);

  // Get TMD evolution factors.
  const auto EvolFactors = EvolutionFactors(TmdObjFF, Alphas, 1);

  // Ogata-quadrature object of degree zero.
  apfel::OgataQuadrature OgataObj{0, 1e-11};

  // Function for the computation of the resummed cross section.
  const auto xsecRes = [=] (double const& y, double const& x, double const& Q2, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Get matched TMD PDFs and FFs.
      const auto MatchedTmdPDFs = MatchTmdPDFs(TmdObjPDF, EvolvedPDFs, Alphas, -1);
      const auto MatchedTmdFFs  = MatchTmdFFs(TmdObjFF,  EvolvedFFs,  Alphas, -1);

      // Useful definitions
      const double qToQ2  = qT2 / Q2;
      const double Yp     = 1 + pow(1-y, 2);
      const int nf        = apfel::NF(Q, Masses);
      const double as     = PDFs -> alphasQ(Q) / apfel::FourPi;
      const double alpha2 = pow(1./137,2);
      const double L      = 4 * apfel::CF * ( - log(qToQ2) - 3. / 2 );

      // Function to be integrated over b
      const auto TMDLumib = [=] (double const& b) -> double
      {
	// Evolve TMDs.
	const std::vector<double> ef = EvolFactors(bstar(b, Q), Q, Q2);
	const auto EvolvedTMDPDFs = ef * MatchedTmdPDFs(bstar(b, Q)) * fNP(x, b, Q2);
	const auto EvolvedTMDFFs  = ef * MatchedTmdFFs(bstar(b, Q)) * fNP(z, b, Q2);

	std::map<int,apfel::Distribution> PDFs = QCDEvToPhys(EvolvedTMDPDFs.GetObjects());
	std::map<int,apfel::Distribution> FFs  = QCDEvToPhys(EvolvedTMDFFs.GetObjects());
	double lumi = 0;
	for (int i = 1; i <= nf; i++)
	  lumi += apfel::QCh2[i-1] * ( PDFs.at(i).Evaluate(x) * FFs.at(i).Evaluate(z) + PDFs.at(-i).Evaluate(x) * FFs.at(-i).Evaluate(z) );

	return b * lumi;
      };

      // Kinmatic factors inclusing the hard form factor.
      const double hcs = 2 * M_PI * alpha2 * Yp * apfel::HardFactorSIDIS(-1, as * apfel::FourPi, nf, 1) / z / x / Q2 / Q2;

      // Integrate over b.
      return hcs * OgataObj.transform(TMDLumib, qT);
    };

  // Function for the computation of the asymptotic cross section at
  // O(as).
  const auto xsecAsy = [=,&gPDF,&gFF] (double const& y, double const& x, double const& Q2, double const& z, double const& qT2, bool const& NonPert) -> double
    {
      // Internal kinematic variables
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Useful definitions
      const double Yp     = 1 + pow(1 - y, 2);
      const int nf        = apfel::NF(Q, Masses);
      const double as     = PDFs -> alphasQ(Q) / apfel::FourPi;
      const double alpha2 = pow(1./137, 2);
      const double S11    = 6 * apfel::CF;
      const double S12    = - 2 * apfel::CF;

      // Include or not non-perturbative effects
      double I0 = 0;
      double I1 = 0;
      double I2 = 0;
      if (NonPert)
	{
	  const auto integrand0 = [=] (double const& b) -> double
	    {
	      const double f1 = fNP(x, b, Q2);
	      const double f2 = fNP(z, b, Q2);
	      return b * f1 * f2 / 2;
	    };
	  const auto integrand1 = [=] (double const& b) -> double
	    {
	      const double f1 = fNP(x, b, Q2);
	      const double f2 = fNP(z, b, Q2);
	      const double lg = 2 * log(bstar(b, Q) * Q / 2 / exp( - apfel::emc));
	      return b * f1 * f2 * pow(lg, 1) / 2;
	    };
	  const auto integrand2 = [=] (double const& b) -> double
	    {
	      const double f1 = fNP(x, b, Q2);
	      const double f2 = fNP(z, b, Q2);
	      const double lg = 2 * log(bstar(b, Q) * Q / 2 / exp( - apfel::emc));
	      return b * f1 * f2 * pow(lg, 2) / 2;
	    };
	  I0 = OgataObj.transform(integrand0, qT);
	  I1 = OgataObj.transform(integrand1, qT);
	  I2 = OgataObj.transform(integrand2, qT);
	}
      else
	{
	  I0 = 0;
	  I1 = - 1 / qT2;
	  I2 = - 2 * log(Q2 / qT2) / qT2;
	}

      // Create sets of distributions for PDFs and FFs.
      const std::map<int,apfel::Distribution> DistPDFs = DistributionMap(gPDF, [=] (double const& x, double const& Q) -> std::map<int,double>{ return PDFs->xfxQ(x,Q); }, Q);
      const std::map<int,apfel::Distribution> DistFFs  = DistributionMap(gFF, [=] (double const& z, double const& Q) -> std::map<int,double>{ return FFs->xfxQ(z,Q); }, Q);

      apfel::DoubleObject<apfel::Distribution> DoubDist;
      for (int j = -nf; j <= nf; j++)
	{
	  if (j == 0)
	    continue;

	  const apfel::Set<apfel::Operator> Psl = PDFObj.at(nf).SplittingFunctions.at(0);
	  const apfel::Set<apfel::Operator> Ptl = FFObj.at(nf).SplittingFunctions.at(0);

	  const apfel::Distribution Ppdf = Psl.at(3) * DistPDFs.at(j) + Psl.at(4) * DistPDFs.at(21) / 2 / nf;
	  const apfel::Distribution Pff  = Ptl.at(3) * DistFFs.at(j)  + Ptl.at(4) * DistFFs.at(21) / 2 / nf;

	  // B00
	  DoubDist.AddTerm({ apfel::QCh2[abs(j)-1] * I0, DistPDFs.at(j), DistFFs.at(j)});

	  // B11
	  DoubDist.AddTerm({ as * apfel::QCh2[abs(j)-1] * S11 * I1, DistPDFs.at(j), DistFFs.at(j)});
	  DoubDist.AddTerm({ - as * apfel::QCh2[abs(j)-1] * I1, DistPDFs.at(j), Pff});
	  DoubDist.AddTerm({ - as * apfel::QCh2[abs(j)-1] * I1, Ppdf, DistFFs.at(j)});
	  // B12
	  DoubDist.AddTerm({ as * apfel::QCh2[abs(j)-1] * S12 * I2, DistPDFs.at(j), DistFFs.at(j)});
	}
      return 2 * M_PI * alpha2 * Yp * ( DoubDist.Evaluate(x,z) / z ) / x / Q2 / Q2;
    };

  // Function for the computation of the fixed-order cross section at
  // O(as).
  const auto xsecFO = [=] (double const& y, double const& x, double const& Q2, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Useful definitions
      const double qToQ2  = qT2 / Q2;
      const double zmax   = ( 1 - x ) / ( 1 - x * ( 1 - qToQ2 ) );
      const double y2     = y * y;
      const double Yp     = 1 + pow(1-y, 2);
      const int nf        = apfel::NF(Q, Masses);
      const double as     = PDFs -> alphasQ(Q) / apfel::FourPi;
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
	const double glPDF = PDFs->xfxQ(21,xt,Q);
	const double glFF  = FFs->xfxQ(21,zt,Q);
	for (int i = 1; i <= nf; i++)
	  {
	    qq += apfel::QCh2[i-1] * ( PDFs->xfxQ(i,xt,Q) * FFs->xfxQ(i,zt,Q) + PDFs->xfxQ(-i,xt,Q) * FFs->xfxQ(-i,zt,Q) );
	    qg += apfel::QCh2[i-1] * glPDF * ( FFs->xfxQ(i,zt,Q) + FFs->xfxQ(-i,zt,Q) );
	    gq += apfel::QCh2[i-1] * ( PDFs->xfxQ(i,xt,Q) + PDFs->xfxQ(-i,xt,Q) ) * glFF;
	  }
	qq /= xt * zt;
	qg /= xt * zt;
	gq /= xt * zt;

	// Construct integrand
	const double integrand = as * x * xb0 *
	( ( B2FOqq(xb0, zb, qT, Q) - y2 / Yp * BLFOqq(xb0, zb) ) * qq
	  + ( B2FOqg(xb0, zb, qT, Q) - y2 / Yp * BLFOqg(xb0, zb) ) * qg
	  + ( B2FOgq(xb0, zb, qT, Q) - y2 / Yp * BLFOgq(xb0, zb) ) * gq ) / Q / Q / ( 1 - zb );

	return 2 * M_PI * alpha2 * Yp * integrand / x / Q2 / Q2;
      };

      // Integrate over z.
      const apfel::Integrator Integral{Xsec};
      return Integral.integrate(z, zmax, 1e-5);
    };

  // Now compute inclusive DIS cross section with APFEL
  APFEL::SetMassScheme("FONLL-B");
  APFEL::SetProjectileDIS("electron");
  APFEL::SetTargetDIS("proton");
  APFEL::SetPerturbativeOrder(1);
  APFEL::SetPDFSet("CT14nlo");
  APFEL::SetAlphaQCDRef(PDFs -> alphasQ(91.1876), 91.1876);
  APFEL::SetPoleMasses(mc, mb, mt);
  //APFEL::EnableTargetMassCorrections(false);
  //APFEL::EnableDampingFONLL(true);
  APFEL::InitializeAPFEL_DIS();
  APFEL::ComputeStructureFunctionsAPFEL(sqrt(Q2), sqrt(Q2));
  const double Yp = 1 + pow(1-y, 2);
  const double alpha2 = pow(1./137,2);
  const double IncCrossSec = 2 * M_PI * alpha2 * ( Yp * APFEL::F2total(x) + y * y * APFEL::FLtotal(x) ) / x / Q2 / Q2;

  const int    nqT    = 200;
  //const double qTmin  = 0.0001;
  //const double qTmax  = 30;
  //const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );
  const double qTmin  = 0.0001;
  const double qTmax  = 10;
  const double qTstep = ( qTmax - qTmin ) / ( nqT - 1 );

  std::cout << std::scientific;
  std::cout << "  qT [GeV]    "
	    << "   Resummed     "
	    << "   Asy (NP on)  "
	    << "  Asy (NP off)  "
	    << "   Fixed-order  "
	    << std::endl;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      std::cout << qT << "\t"
		<< std::abs(xsecRes(y, x, Q2, z, qT)) / IncCrossSec << "\t"
		<< std::abs(xsecAsy(y, x, Q2, z, qT, true)) / IncCrossSec << "\t"
		<< std::abs(xsecAsy(y, x, Q2, z, qT, false)) / IncCrossSec << "\t"
		<< std::abs(xsecFO(y, x, Q2, z, qT)) / IncCrossSec
		<< std::endl;
      qT += qTstep;
    }

  return 0;
}
