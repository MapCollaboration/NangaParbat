//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/computetables.h"
#include "NangaParbat/utilities.h"

#include <LHAPDF/LHAPDF.h>
#include <apfel/apfelxx.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::vector<YAML::Emitter> ComputeTables(YAML::Node const& config, std::vector<DataHandler> const& DHVect)
  {
    // Retrieve relevant parameters for the luminosity from the
    // configuration file
    const int    pto  = config["PerturbativeOrder"].as<int>();
    const double Ci   = config["TMDscales"]["Ci"].as<double>();
    const double Cf   = config["TMDscales"]["Cf"].as<double>();
    const double aref = config["alphaem"]["aref"].as<double>();
    const double Qref = config["alphaem"]["Qref"].as<double>();
    const bool   arun = config["alphaem"]["run"].as<bool>();

    // Set verbosity level of APFEL++ to the minimum
    apfel::SetVerbosityLevel(0);

    // Open LHAPDF PDF set
    LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());

    // Heavy-quark thresholds (from PDFs)
    std::vector<double> Thresholds;
    for (auto const& v : distpdf->flavors())
      if (v > 0 && v < 7)
	Thresholds.push_back(distpdf->quarkThreshold(v));

    // Alpha_s. Get it from the LHAPDF set and tabulate it.
    const apfel::TabulateObject<double> TabAlphas{[&] (double const& mu) -> double{ return distpdf->alphasQ(mu); }, 100, distpdf->qMin(), distpdf->qMax(), 3, Thresholds};
    const auto Alphas = [&] (double const& mu) -> double{ return TabAlphas.Evaluate(mu); };

    // Define x-space grid
    std::vector<apfel::SubGrid> vsg;
    for (auto const& sg : config["xgridpdf"])
      vsg.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    const apfel::Grid g{vsg};

    // Rotate PDF set into the QCD evolution basis
    const auto RotPDFs = [&] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(distpdf->xfxQ(x,mu)); };

    // Construct set of distributions as a function of the scale to be
    // tabulated
    const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
      {
	return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotPDFs, mu)};
      };

    // Tabulate collinear PDFs
    const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, distpdf->qMin(), distpdf->qMax(), 3, Thresholds};
    const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

    // Build evolved TMD PDFs
    const auto EvTMDPDFs = BuildTmdPDFs(apfel::InitializeTmdObjects(g, Thresholds), CollPDFs, Alphas, pto, Ci);

    // Alpha_em
    const apfel::AlphaQED alphaem{aref, Qref, Thresholds, {0, 0, 1.777}, 0};

    // Construct luminosity function
    const auto TabulatedLuminosity = [&] (double const& bs, double const& Qmin, double const& Qmax) -> apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>>
      {
	// Tabulate the TMD luminosity in 'bs' in the range
	// [Qb.first:Qb.second].
	const auto Lumi = [&] (double const& Q) -> apfel::DoubleObject<apfel::Distribution>
	{
	  // TMD scales
	  const double muf   = Cf * Q;
	  const double zetaf = Q * Q;

	  // Number of active flavours at 'Q'
	  const int nf = apfel::NF(muf, Thresholds);

	  // EW charges
	  const std::vector<double> Bq = apfel::ElectroWeakCharges(Q, true);

	  // Electromagnetic coupling squared
	  const double aem2 = pow((arun ? alphaem.Evaluate(Q) : aref), 2);

	  // Compute the hard factor
	  const double hcs = apfel::HardFactorDY(pto, Alphas(muf), nf, Cf);

	  // Global factor
	  const double factor = apfel::ConvFact * 8 * M_PI * aem2 * hcs / 9;

	  apfel::DoubleObject<apfel::Distribution> Lumi;
	  const std::map<int,apfel::Distribution> xF = QCDEvToPhys(EvTMDPDFs(bs, muf, zetaf).GetObjects());
	  for (int i = 1; i <= nf; i++)
	    {
	      Lumi.AddTerm({factor * Bq[i-1], xF.at(i), xF.at(-i)});
	      Lumi.AddTerm({factor * Bq[i-1], xF.at(-i), xF.at(i)});
	    }
	  return Lumi;
	};
	return apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>>{Lumi, 200, Qmin, Qmax, 1, {}};
      };

    // Delete LHAPDF set
    delete distpdf;

    // Retrieve relevant parameters for the numerical integration from
    // the configuration file
    const double bmax   = config["bstar"]["bmax"].as<double>();
    const int    nOgata = config["nOgata"].as<int>();
    const int    nQ     = config["Qgrid"]["n"].as<int>();
    const int    idQ    = config["Qgrid"]["InterDegree"].as<int>();
    const double epsQ   = config["Qgrid"]["eps"].as<double>();
    const int    nxi    = config["xigrid"]["n"].as<int>();
    const int    idxi   = config["xigrid"]["InterDegree"].as<int>();
    const double epsxi  = config["xigrid"]["eps"].as<double>();

    // Initialise container of YAML:Emitter objects.
    std::vector<YAML::Emitter> Tabs(DHVect.size());

    // Loop over the vector of "Kinematics" objects
    std::cout << std::endl;
    for (int i = 0; i < (int) DHVect.size(); i++)
      {
	// Timer
	apfel::Timer t;

	// Name of the dataset
	const std::string name = DHVect[i].GetName();

	// Retrieve kinematics
	const DataHandler::Kinematics  kin   = DHVect[i].GetKinematics();
	const double                   Vs    = kin.Vs;    // C.M.E.
	const std::vector<double>      qTv   = kin.qTv;   // Transverse momentum bin bounds
	const std::pair<double,double> Qb    = kin.var1b; // Invariant mass interval
	const std::pair<double,double> yb    = kin.var2b; // Rapidity interval
	const bool                     IntqT = kin.IntqT; // Whether the bins in qTv are to be integrated over
	const bool                     IntQ  = kin.Intv1; // Whether the bin in Q is to be integrated over
	const bool                     Inty  = kin.Intv2; // Whether the bin in y is to be integrated over

	// Ogata-quadrature object of degree one or zero according to
	// weather the cross sections have to be integrated over the
	// bins in qT or not.
	apfel::OgataQuadrature OgataObj{(IntqT ? 1 : 0)};

	// Unscaled coordinates and weights of the Ogata quadrature.
	std::vector<double> zo = OgataObj.GetCoordinates();
	std::vector<double> wo = OgataObj.GetWeights();

	// Construct QGrid-like grids for the integration in Q and y
	const std::vector<double> Qg  = (IntQ ? GenerateQGrid(nQ, Qb.first, Qb.second, idQ - 1) :
					 std::vector<double>{( Qb.first + Qb.second ) / 2});
	const std::vector<double> xig = (Inty ? GenerateQGrid(nxi, exp(yb.first), exp(yb.second), idxi - 1) :
					 std::vector<double>{exp( ( yb.first + yb.second ) / 2 )});
	const apfel::QGrid<double> Qgrid {Qg, idQ};
	const apfel::QGrid<double> xigrid{xig, idxi};

	// Number of points of the grids
	const int nO   = std::min(nOgata, (int) zo.size());
	const int nQe  = Qg.size();
	const int nxie = xig.size();

	// Write kinematics on the YAML emitter
	Tabs[i].SetFloatPrecision(8);
	Tabs[i].SetDoublePrecision(8);
	Tabs[i] << YAML::BeginMap;
	Tabs[i] << YAML::Comment("Kinematics and grid information");
	Tabs[i] << YAML::Key << "name" << YAML::Value << name;
	Tabs[i] << YAML::Key << "CME" << YAML::Value << Vs;
	Tabs[i] << YAML::Key << "qT_bounds" << YAML::Value << YAML::Flow << qTv;
	Tabs[i] << YAML::Key << "Ogata_coordinates" << YAML::Value << YAML::Flow << std::vector<double>(zo.begin(), zo.begin() + nO);
	Tabs[i] << YAML::Key << "Qgrid" << YAML::Value << YAML::Flow << Qg;
	Tabs[i] << YAML::Key << "xigrid" << YAML::Value << YAML::Flow << xig;
	Tabs[i] << YAML::EndMap;
	Tabs[i] << YAML::Newline;
	Tabs[i] << YAML::BeginMap;
	Tabs[i] << YAML::Comment("Weights");

	// Total number of steps for this particular table. Used to
	// report the progress of the computation.
	const int nsteps = qTv.size() * nO * nQe * nxie;

	// Counter for the status report
	int istep = 0;

	// Loop over the qT-bin bounds
	for (auto const& qT : qTv)
	  {
	    // Allocate container of the weights
	    std::vector<std::vector<std::vector<double>>> W(nO, std::vector<std::vector<double>>(nQe, std::vector<double>(nxie)));

	    // Loop over the Ogata-quadrature points
	    for (int n = 0; n < nO; n++)
	      {
		// Get impact parameters 'b' and 'b*'
		const double b  = zo[n] / qT;
		const double bs = bstar(b, bmax);

		// Call luminosity function
		const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> TabLumi = TabulatedLuminosity(bs, Qb.first, Qb.second);

		// Initialise vector of fixed points for the integration in Q
		std::vector<double> FixPtsQ;

		// Loop over the grids in Q
		for (int tau = 0; tau < nQe; tau++)
		  {
		    // Update vector of fixed points for the integration in Q
		    if (tau > 0 && tau < nQ)
		      FixPtsQ.push_back(Qg[tau]);
		    if (FixPtsQ.size() > idQ || tau >= nQ)
		      FixPtsQ.erase(FixPtsQ.begin());

		    // Get integration bounds for the integration in Q
		    const double Qmin = Qg[std::max(tau - idQ, 0)];
		    const double Qmax = Qg[std::min(tau + 1, nQ)];

		    // Initialise vector of fixed points for the integration in xi
		    std::vector<double> FixPtsxi;

		    // Loop over the grid in xi
		    for (int alpha = 0; alpha < nxie; alpha++)
		      {
			// Update vector of fixed points for the integration in xi
			if (alpha > 0 && alpha < nxi)
			  FixPtsxi.push_back(xig[alpha]);
			if (FixPtsxi.size() > idxi || alpha >= nxi)
			  FixPtsxi.erase(FixPtsxi.begin());

			// Get integration bounds for the integration in xi
			const double ximin = xig[std::max(alpha - idxi, 0)];
			const double ximax = xig[std::min(alpha + 1, nxi)];

			// Function to be integrated in Q
			const auto Qintegrand = [&] (double const& Q) -> double
			  {
			    // Function to be integrated in xi
			    const auto xiintegrand = [&] (double const& xi) -> double
			    {
			      // Compute 'x1' and 'x2'
			      const double x1 = Q * xi / Vs;
			      const double x2 = Q / xi / Vs;

			      // Get interpolating function in xi but
			      // return 1 if no integration over xi is
			      // required
			      const double Ixi = (Inty ? xigrid.Interpolant(0, alpha, xi) : 1);

			      // Return xi integrand
			      return Ixi * TabLumi.EvaluatexzQ(x1, x2, Q) / xi;
			    };

			    // Perform the integral in xi
			    const apfel::Integrator xiIntObj{xiintegrand};
			    const double xiintegral = (Inty ? xiIntObj.integrate(ximin, ximax, FixPtsxi, epsxi) : xiintegrand(xig[alpha]));

			    // Get interpolating function in Q but
			    // return 1 if no integration over Q is
			    // required
			    const double IQ = (IntQ ? Qgrid.Interpolant(0, tau, Q) : 1);

			    // Return Q integrand
			    return IQ * xiintegral / pow(Q, 3);
			  };

			// Perform the integral in Q
			const apfel::Integrator QIntObj{Qintegrand};
			const double Qintegral = (IntQ ? QIntObj.integrate(Qmin, Qmax, FixPtsQ, epsQ) : Qintegrand(Qg[tau]));

			// Compute the weight
			W[n][tau][alpha] = wo[n] * Qintegral;

			// If not intergrating over qT, multiply by b
			if (!IntqT)
			  W[n][tau][alpha] *= b;

			// Report progress
			istep++;
			const double perc = 100. * istep / nsteps;
			std::cout << "Status report for table '" << name << "': "<< std::setw(6) << std::setprecision(4) << perc << "\% completed...\r";
			std::cout.flush();
		      }  // End loop over alpha
		  }  // End loop over tau
	      } // End loop over n
	    Tabs[i] << YAML::Key << qT;
	    Tabs[i] << YAML::Value << YAML::Flow << W;
	  }
	Tabs[i] << YAML::EndMap;

	// Stop timer and force to display the time elapsed
	std::cout << std::endl;
	t.stop(true);
      }
    std::cout << std::endl;

    return Tabs;
  }
}
