//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

// APFEL++
#include <apfel/constants.h>
#include <apfel/grid.h>
#include <apfel/timer.h>
#include <apfel/alphaqcd.h>
#include <apfel/constants.h>
#include <apfel/tmdbuilder.h>
#include <apfel/rotations.h>
#include <apfel/tools.h>
#include <apfel/hardfactors.h>
#include <apfel/ogataquadrature.h>
#include <apfel/doubleobject.h>
#include <apfel/evolutionbasisqcd.h>

// LHAPDF
#include <LHAPDF/LHAPDF.h>

// Global parameters to be eventually put in an input card

// Values of bmin and bmax required by the b* prescription
//const double bmin = 0;
const double bmax = 1;

// Name of the PDF set
const std::string pdfset = "MMHT2014nlo68cl";

// Perturbative order
const int PerturbativeOrder = 1;

// Initial scale-variation factor
const double Ci = 1;

// Final scale-variation factor
const double Cf = 1;

// Kinematics
// C.M.E.
const double Vs = 13000;

// Invariant mass bin
const double Qmin = 66;
const double Qmax = 116;

// Rapidity bin
const double ymin = -1;
const double ymax =  1;

// Transverse momentum bin bounds
const std::vector<double> qTv{1, 3};


// Parameters of the computation

// Maximum number of Ogata-quadrature points
const int nOgata = 10;

// Number of points and interpolation degree of the grid in Q
const int nQ  = 5;
const int InterDegreeQ  = 3;

// Number of points and interpolation degree of the grid in xi
const int nxi = 5;
const int InterDegreexi = 3;










// b* prescription
double bstar(double const& b) { return b / sqrt( 1 + pow(b / bmax, 2) ); }

// Electroweak charges
std::vector<double> EWCharges(double const& Q)
{
  // Relevant constants for the computation of the EW charges
  // (See https://arxiv.org/pdf/hep-ph/9711387.pdf)
  const double MZ2   = apfel::ZMass * apfel::ZMass;
  const double GmZ2  = apfel::GammaZ * apfel::GammaZ;
  const double S2ThW = apfel::Sin2ThetaW;
  const double VD    = - 0.5 + 2 * S2ThW / 3;
  const double VU    = + 0.5 - 4 * S2ThW / 3;
  const double AD    = - 0.5;
  const double AU    = + 0.5;
  const double Ve    = - 0.5 + 2 * S2ThW;
  const double Ae    = - 0.5;
  const std::vector<double> Vq = {VD, VU, VD, VU, VD, VU};
  const std::vector<double> Aq = {AD, AU, AD, AU, AD, AU};

  const double Q2  = Q * Q;
  const double PZ  = Q2 * ( Q2 -  MZ2 ) / ( pow(Q2 - MZ2,2) + MZ2 * GmZ2 ) / ( 4 * S2ThW * ( 1 - S2ThW ) );
  const double PZ2 = pow(Q2,2) / ( pow(Q2 - MZ2,2) + MZ2 * GmZ2 ) / pow(4 * S2ThW * ( 1 - S2ThW ),2);
  std::vector<double> EWCharges;
  for (auto i = 0; i < 6; i++)
    {
      const double b = apfel::QCh2[i]
	- 2 * apfel::QCh[i] * Vq[i] * Ve * PZ
	+ ( Ve * Ve + Ae * Ae ) * ( Vq[i] * Vq[i] + Aq[i] * Aq[i] ) * PZ2;
      EWCharges.push_back(b);
    }
  return EWCharges;
};

// E.M. coupling (to be adjusted)
double alphaem(double const& Q)
{
  return ( 1. / 128.77 ) / ( 1 - 0.00167092 * log(Q / apfel::ZMass) );
}

// Generate an interpolation grid
std::vector<double> GenerateQGrid(int const& n, double const& min, double const& max)
{
  // Define (linear) step;
  const double step = ( max - min ) / ( n - 1 );
  std::vector<double> grid(n+1);
  for (int i = 0; i < n + 1; i++)
    grid[i] = min + i * step;
  return grid;
}

// Main program
int main()
{
 // Open LHAPDF set
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF(pdfset);

  // Thresholds
  const std::vector<double> Thresholds{distpdf->quarkThreshold(1),
      distpdf->quarkThreshold(2),
      distpdf->quarkThreshold(3),
      distpdf->quarkThreshold(4),
      distpdf->quarkThreshold(5)};

  // Alpha_s
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

  // x-space grid
  const apfel::Grid g{{{100,1e-5,3}, {60,1e-1,3}, {50,6e-1,3}, {100,8e-1,3}}};

  // Rotate PDF set into the QCD evolution basis
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double>{
    return apfel::PhysToQCDEv(distpdf->xfxQ(x,mu));
  };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>{
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)};
  };

  // Tabulate PDFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 50, 1, 100000, 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

  // Initialize TMD objects
  const auto TmdObj = apfel::InitializeTmdObjects(g, Thresholds);

  // Get evolution factors
  const auto QuarkEvolFactor = apfel::QuarkEvolutionFactor(TmdObj, Alphas, PerturbativeOrder, Ci);

  // Match TMD PDFs
  const auto MatchedTMDPDFs = apfel::MatchTmdPDFs(TmdObj, CollPDFs, Alphas, PerturbativeOrder, Ci);

  // Construct QGrid-like grids for the integration in Q and y
  const std::vector<double> Qg  = GenerateQGrid(nQ, Qmin, Qmax);
  const std::vector<double> xig = GenerateQGrid(nxi, exp(ymin), exp(ymax));
  const apfel::QGrid<double> Qgrid {Qg,  InterDegreeQ};
  const apfel::QGrid<double> xigrid{xig, InterDegreexi};

  // Ogata-quadrature object of degree one (required to compute the
  // primitive in qT of the cross section)
  apfel::OgataQuadrature OgataObj{1};
  std::vector<double> z1 = OgataObj.GetCoordinates(); 
  std::vector<double> w1 = OgataObj.GetWeights(); 

  // Timer
  apfel::Timer t;

  // Loop over the qT bin bounds
  for (auto const& qT : qTv)
    {
      // Loop over the Ogata-quadrature points
      for (int n = 0; n < std::min(nOgata, (int) z1.size()); n++)
	{
	  // Get impact parameter 'b' and 'b*'
	  const double b  = z1[n] / qT;
	  const double bs = bstar(b);

	  // Tabulate TMDs in Q
	  const auto EvolvedTMDPDFs = [&] (double const& Q) -> apfel::Set<apfel::Distribution>
	    {
	      return QuarkEvolFactor(bs, Cf * Q, Q * Q) * MatchedTMDPDFs(bs);
	    };
	  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabEvolvedTMDPDFs{EvolvedTMDPDFs, Qg, InterDegreeQ};

	  // Loop over the grid in Q
	  for (int tau = 0; tau < nQ; tau++)
	    {
	      // Loop over the grid in Q
	      for (int alpha = 0; alpha < nxi; alpha++)
		{

		  // Function to be integrated in Q
		  const auto Qintegrand = [=] (double const& Q) -> double
		    {
		      // Renormalisation scale
		      const double muf = Cf * Q;

		      // Number of active flavours at 'Q'
		      const int nf = apfel::NF(muf, Thresholds);

		      // EW charges
		      const std::vector<double> Bq = EWCharges(Q);

		      // Get Evolved TMD PDFs and rotate them into the physical basis
		      const std::map<int,apfel::Distribution> xF = QCDEvToPhys(TabEvolvedTMDPDFs.Evaluate(Q).GetObjects());

		      // Function to be integrated in xi
		      const auto xiintegrand = [=] (double const& xi) -> double
		      {
			// Compute 'x1' and 'x2'
			const double x1 = Q * xi / Vs;
			const double x2 = Q / xi / Vs;

			// Get interpolating function in Q
			const double Ixi = xigrid.Interpolant(0, alpha, xi);

			// Combine TMDs through the EW charges
			double integrand = 0;
			for (int i = 1; i <= nf; i++)
			  integrand += Bq[i-1] * ( xF.at(i).Evaluate(x1) * xF.at(-i).Evaluate(x2) + xF.at(-i).Evaluate(x1) * xF.at(i).Evaluate(x2) );

			return Ixi * integrand / xi;
		      };

		      // Get integration bounds and fixed points in xi
		      const int iximin = std::max(alpha - InterDegreexi, 0);
		      const int iximax = std::min(alpha + 1, nxi);
		      std::vector<double> FixPtsxi(xig.begin() + iximin + 1, xig.begin() + std::max(iximax - 1, iximin + 1));

		      // Perform the integral in xi
		      const apfel::Integrator xiIntObj{xiintegrand};
		      const double xiintegral = xiIntObj.integrate(xig[iximin], xig[iximax], FixPtsxi, apfel::eps5);

		      // Get interpolating function in Q
		      const double IQ = Qgrid.Interpolant(0, tau, Q);

		      // Electromagnetic coupling squared
		      const double aem2 = pow(alphaem(Q), 2);

		      // Compute hard factor
		      const double hcs = apfel::HardFactorDY(PerturbativeOrder, Alphas(muf), nf, Cf);

		      return IQ * aem2 * hcs * xiintegral / pow(Q, 3);
		    };

		  // Get integration bounds and fixed points in Q
		  const int iQmin = std::max(tau - InterDegreeQ, 0);
		  const int iQmax = std::min(tau + 1, nQ);
		  std::vector<double> FixPtsQ(Qg.begin() + iQmin + 1, Qg.begin() + std::max(iQmax - 1, iQmin + 1));

		  // Perform the integral in Q
		  const apfel::Integrator QIntObj{Qintegrand};
		  const double Qintegral = QIntObj.integrate(Qg[iQmin], Qg[iQmax], FixPtsQ, apfel::eps5);

		  // Compute weight
		  const double W = apfel::ConvFact * 8 * M_PI * w1[n] * Qintegral / 9;

		  std::cout << qT << "  " << n << "  " << tau << "  " << alpha << "  " << W << std::endl;
		}
	    }
	}
    }
  t.stop();

  return 0;
}

