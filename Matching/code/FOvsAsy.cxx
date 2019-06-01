/*
 * Author: Valerio Bertone
 */

// LHAPDF libs
#include "LHAPDF/LHAPDF.h"

// APFEL++ libs
#include "apfel/apfelxx.h"

// Fixed-order coefficient functions
#include "FOCoeffFuncs.h"

int main() {
  // PDF and FF sets
  LHAPDF::PDF* PDFs = LHAPDF::mkPDF("CT14nlo");
  LHAPDF::PDF* FFs  = LHAPDF::mkPDF("DSS07_NLO_HadronSum");

  // Heavy quark masses.
  const double mc = PDFs->quarkThreshold(4);
  const double mb = PDFs->quarkThreshold(5);
  const double mt = PDFs->quarkThreshold(6);
  const std::vector<double> Masses{0, 0, 0, mc, mb, mt};

  // Function for the computation of the fixed-order cross section at
  // O(as).
  const auto xsecFO = [=] (double const& VS, double const& x, double const& Q2, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double y  = Q2 / x / VS / VS;
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
	const double gPDF = PDFs->xfxQ(21,xt,Q);
	const double gFF  = FFs->xfxQ(21,zt,Q);
	for (int i = 1; i <= nf; i++)
	  {
	    qq += apfel::QCh2[i-1] * ( PDFs->xfxQ(i,xt,Q) * FFs->xfxQ(i,zt,Q) + PDFs->xfxQ(-i,xt,Q) * FFs->xfxQ(-i,zt,Q) );
	    qg += apfel::QCh2[i-1] * gPDF * ( FFs->xfxQ(i,zt,Q) + FFs->xfxQ(-i,zt,Q) );
	    gq += apfel::QCh2[i-1] * ( PDFs->xfxQ(i,xt,Q) + PDFs->xfxQ(-i,xt,Q) ) * gFF;
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

  // Initialize space- and time-like splitting functions.
  const apfel::Grid g{{{100, 1e-5, 3}, {60, 1e-1, 3}, {50, 5e-1, 3}, {60, 7e-1, 3}}};
  const auto PDFObj = InitializeDglapObjectsQCD(g, Masses);
  const auto FFObj  = InitializeDglapObjectsQCDT(g, Masses);
 
  // Function for the computation of the asymptotic cross section at
  // O(as).
  const auto xsecAsy = [=,&g] (double const& VS, double const& x, double const& Q2, double const& z, double const& qT2) -> double
    {
      // Internal kinematic variables
      const double y  = Q2 / x / VS / VS;
      const double Q  = sqrt(Q2);
      const double qT = sqrt(qT2);

      // Useful definitions
      const double qToQ2  = qT2 / Q2;
      const double y2     = y * y;
      const double Yp     = 1 + pow(1-y, 2);
      const int nf        = apfel::NF(Q, Masses);
      const double as     = PDFs -> alphasQ(Q) / apfel::FourPi;
      const double alpha2 = pow(1./137, 2);
      const double L      = 4 * apfel::CF * ( - log(qToQ2) - 3. / 2 );

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

	  DoubDist.AddTerm({apfel::QCh2[abs(j)-1] * L, DistPDFs.at(j), DistFFs.at(j)});
	  DoubDist.AddTerm({apfel::QCh2[abs(j)-1], DistPDFs.at(j), Pff});
	  DoubDist.AddTerm({apfel::QCh2[abs(j)-1], Ppdf, DistFFs.at(j)});
	}

      return 2 * M_PI * alpha2 * Yp * ( as * DoubDist.Evaluate(x,z) / qT2 / z ) / x / Q2 / Q2;
    };

  // Kinematics in terms of the variables in which TIMBA is
  // differential.
  //const double EP = 820;
  //const double El = 27.6;
  const double EP = 1;
  const double El = 160;
  const double VS = sqrt( 4 * EP * El );
  const double x  = 0.157;
  const double z  = 0.35;
  const double Q2 = 20;

  const int    nqT    = 50;
  const double qTmin  = 0.0001;
  const double qTmax  = 10;
  const double qTstep = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );

  std::cout << std::scientific;
  double qT = qTmin;
  for (int iqT = 0; iqT < nqT; iqT++)
    {
      std::cout << qT << "  "
		<< xsecFO(VS, x, Q2, z, qT) << "  "
		<< xsecAsy(VS, x, Q2, z, qT) << "  "
		<< std::endl;
      qT *= qTstep;
    }

  return 0;
}
