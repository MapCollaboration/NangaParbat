/*
 * Author: Valerio Bertone
 */

// LHAPDF libs
#include "LHAPDF/LHAPDF.h"

// APFEL++ libs
#include "apfel/apfelxx.h"

// b* prescription
double bstar(double const& b, double const& Q)
{
  const double bmax = 2 * exp( - apfel::emc);
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
  //const double EP  = 820;
  //const double El  = 27.6;
  const double EP = 1;
  const double El = 160;
  const double VS = sqrt( 4 * EP * El );
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
  const apfel::Grid g{{{100, 1e-5, 3}, {60, 1e-1, 3}, {50, 5e-1, 3}, {60, 7e-1, 3}}};

  // Alpha_s
  const auto Alphas = [&] (double const& mu) -> double{ return PDFs->alphasQ(mu); };

  // Rotate distributions into the QCD evolution basis.
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(PDFs->xfxQ(x,mu)); };
  const auto RotFFs  = [=] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(FFs->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated.
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Masses)}, DistributionMap(g, RotPDFs, mu)};
    };
  const auto EvolvedFFs  = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Masses)}, DistributionMap(g, RotFFs, mu)};
    };

  // Get relevant objects.
  const auto PDFObj = InitializeDglapObjectsQCD(g, Masses);
  const auto FFObj  = InitializeDglapObjectsQCDT(g, Masses);
  const auto TmdObj = InitializeTmdObjects(g, Masses);

  // Get TMD evolution factors.
  const auto EvolFactors = EvolutionFactors(TmdObj, Alphas, 1);

  // Ogata-quadrature object of degree zero.
  apfel::OgataQuadrature OgataObj{};

  // Function for the computation of the resummed cross section.
  const auto xsecRes = [=,&g] (double const& VS, double const& x, double const& Q2, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double y  = Q2 / x / VS / VS;
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Get matched TMD PDFs and FFs.
      const auto MatchedTmdPDFs = MatchTmdPDFs(TmdObj, EvolvedPDFs, Alphas, -1);
      const auto MatchedTmdFFs  = MatchTmdFFs(TmdObj,  EvolvedFFs,  Alphas, -1);

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
  const auto xsecAsy = [=,&g] (double const& VS, double const& x, double const& Q2, double const& z, double const& qT2, bool const& NonPert) -> double
    {
      // Internal kinematic variables
      const double y  = Q2 / x / VS / VS;
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
      const std::map<int,apfel::Distribution> DistPDFs = DistributionMap(g, [=] (double const& x, double const& Q) -> std::map<int,double>{ return PDFs->xfxQ(x,Q); }, Q);
      const std::map<int,apfel::Distribution> DistFFs  = DistributionMap(g, [=] (double const& z, double const& Q) -> std::map<int,double>{ return FFs->xfxQ(z,Q); }, Q);

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

  const int    nqT    = 50;
  const double qTmin  = 0.001;
  const double qTmax  = 20;
  const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );

  std::cout << std::scientific;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      std::cout << qT << "  "
		<< xsecRes(VS, x, Q2, z, qT) << "  "
		<< xsecAsy(VS, x, Q2, z, qT, true) << "  "
		<< xsecAsy(VS, x, Q2, z, qT, false) << "  "
		<< std::endl;
      qT *= qTstep;
    }

  return 0;
}
