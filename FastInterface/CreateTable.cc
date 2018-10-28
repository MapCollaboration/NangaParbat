//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

// APFEL++
#include <apfel/apfelxx.h>

// LHAPDF
#include <LHAPDF/LHAPDF.h>

// YAML
#include <yaml-cpp/yaml.h>

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

// b* prescription
double bstar(double const& b, double const& bmax) { return b / sqrt( 1 + pow(b / bmax, 2) ); }

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
  // Read configuration parameters with YAML
  const YAML::Node config = YAML::LoadFile("config.yaml");

 // Open LHAPDF set
  LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"].as<std::string>());

  // Heavy-quark thresholds
  std::vector<double> Thresholds;
  for (auto const& v : distpdf->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(distpdf->quarkThreshold(v));

  // Alpha_s
  const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

  // Set lowest verbosity level for APFEL
  //apfel::SetVerbosityLevel(0);

  // x-space grid
  std::vector<apfel::SubGrid> vsg;
  for (auto const& sg : config["xgridpdf"])
    vsg.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
  const apfel::Grid g{vsg};

  // Rotate PDF set into the QCD evolution basis
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(distpdf->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>{
    return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)};
  };

  // Tabulate PDFs
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, distpdf->qMin(), distpdf->qMax(), 3, Thresholds};
  const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

  // Initialize TMD objects
  const auto TmdObj = apfel::InitializeTmdObjects(g, Thresholds);

  // Build evolved TMD PDFs
  const auto EvTMDPDFs = BuildTmdPDFs(TmdObj, CollPDFs, Alphas, config["PerturbativeOrder"].as<int>(), config["TMDscales"]["Ci"].as<double>());

  // Ogata-quadrature object of degree one (required to compute the
  // primitive in qT of the cross section)
  apfel::OgataQuadrature OgataObj{1};

  // Retrieve relevant parameters from the configuration file
  const double Cf            = config["TMDscales"]["Cf"].as<double>();
  const int    nQ            = config["Qgrid"]["nQ"].as<int>();
  const int    InterDegreeQ  = config["Qgrid"]["InterDegreeQ"].as<int>();
  const int    nxi           = config["xigrid"]["nxi"].as<int>();
  const int    InterDegreexi = config["xigrid"]["InterDegreexi"].as<int>();

  // Timer
  apfel::Timer t;

  // Construct QGrid-like grids for the integration in Q and y
  const std::vector<double> Qg  = GenerateQGrid(nQ, Qmin, Qmax);
  const std::vector<double> xig = GenerateQGrid(nxi, exp(ymin), exp(ymax));
  const apfel::QGrid<double> Qgrid {Qg,  InterDegreeQ};
  const apfel::QGrid<double> xigrid{xig, InterDegreexi};

  // Unscaled coordinates and weights of the degree-one Ogata
  // quadrature.
  std::vector<double> z1 = OgataObj.GetCoordinates(); 
  std::vector<double> w1 = OgataObj.GetWeights(); 

  // Loop over the qT bin bounds
  for (auto const& qT : qTv)
    {
      // Loop over the Ogata-quadrature points
      for (int n = 0; n < std::min(config["nOgata"].as<int>(), (int) z1.size()); n++)
	{
	  // Get impact parameter 'b' and 'b*'
	  const double b  = z1[n] / qT;
	  const double bs = bstar(b, config["bstar"]["bmax"].as<double>());

	  // Tabulate TMDs in Q
	  const auto EvolvedTMDPDFs = [&] (double const& Q) -> apfel::Set<apfel::Distribution>{ return EvTMDPDFs(bs, Cf * Q, Q * Q); };
	  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabEvolvedTMDPDFs{EvolvedTMDPDFs, Qg, InterDegreeQ};

	  // Loop over the grid in Q
	  for (int tau = 0; tau < nQ; tau++)
	    {
	      // Loop over the grid in Q
	      for (int alpha = 0; alpha < nxi; alpha++)
		{
		  // Function to be integrated in Q
		  const auto Qintegrand = [&] (double const& Q) -> double
		    {
		      // Renormalisation scale
		      const double muf = Cf * Q;

		      // Number of active flavours at 'Q'
		      const int nf = apfel::NF(muf, Thresholds);

		      // EW charges
		      const std::vector<double> Bq = apfel::ElectroWeakCharges(Q, true);

		      // Get Evolved TMD PDFs and rotate them into the physical basis
		      const std::map<int,apfel::Distribution> xF = QCDEvToPhys(TabEvolvedTMDPDFs.Evaluate(Q).GetObjects());

		      // Function to be integrated in xi
		      const auto xiintegrand = [&] (double const& xi) -> double
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

			// Return xi integrand
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
		      const double hcs = apfel::HardFactorDY(config["PerturbativeOrder"].as<int>(), Alphas(muf), nf, Cf);

		      // Return Q integrand
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

