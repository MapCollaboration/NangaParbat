//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/utilities.h"

#include <LHAPDF/LHAPDF.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  FastInterface::FastInterface(YAML::Node const& config):
    _config(config)
  {
    // Set verbosity level of APFEL++ to the minimum
    apfel::SetVerbosityLevel(0);

    // Open LHAPDF PDF set
    LHAPDF::PDF* distpdf = LHAPDF::mkPDF(_config["pdfset"]["name"].as<std::string>(), _config["pdfset"]["member"].as<int>());

    // Rotate PDF set into the QCD evolution basis
    const auto RotPDFs = [&] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(distpdf->xfxQ(x, mu)); };

    // Heavy-quark thresholds (from PDFs)
    for (auto const& v : distpdf->flavors())
      if (v > 0 && v < 7)
	_Thresholds.push_back(distpdf->quarkThreshold(v));

    // Alpha_s (from PDFs). Get it from the LHAPDF set and tabulate it.
    _TabAlphas = std::unique_ptr<apfel::TabulateObject<double>>(new apfel::TabulateObject<double>{[&] (double const& mu) -> double{return distpdf->alphasQ(mu); },
	  100, distpdf->qMin(), distpdf->qMax(), 3, _Thresholds});

    // Open LHAPDF FF set
    LHAPDF::PDF* distff = LHAPDF::mkPDF(_config["ffset"]["name"].as<std::string>(), _config["ffset"]["member"].as<int>());

    // Rotate PF set into the QCD evolution basis
    const auto RotFFs = [&] (double const& x, double const& mu) -> std::map<int,double>{ return apfel::PhysToQCDEv(distff->xfxQ(x, mu)); };

    // Define x-space grid for PDFs
    std::vector<apfel::SubGrid> vsgpdf;
    for (auto const& sg : _config["xgridpdf"])
      vsgpdf.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    _gpdf = std::unique_ptr<const apfel::Grid>(new apfel::Grid({vsgpdf}));

    // Construct set of distributions as a function of the scale to be
    // tabulated for PDFs
    const auto EvolvedPDFs = [=] (double const& mu) -> apfel::Set<apfel::Distribution>
      {
	return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, _Thresholds)}, DistributionMap(*_gpdf, RotPDFs, mu)};
      };

    // Tabulate collinear PDFs
    _TabPDFs = std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>
      (new apfel::TabulateObject<apfel::Set<apfel::Distribution>>{EvolvedPDFs, 100, distpdf->qMin(), distpdf->qMax(), 3, _Thresholds});

    // Define x-space grid for FFs
    std::vector<apfel::SubGrid> vsgff;
    for (auto const& sg : _config["xgridff"])
      vsgff.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    _gff = std::unique_ptr<const apfel::Grid>(new apfel::Grid({vsgff}));

    // Construct set of distributions as a function of the scale to be
    // tabulated for FFs
    const auto EvolvedFFs = [=] (double const& mu) -> apfel::Set<apfel::Distribution>
      {
	return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, _Thresholds)}, DistributionMap(*_gff, RotFFs, mu)};
      };

    // Tabulate collinear FFs
    _TabFFs = std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>
      (new apfel::TabulateObject<apfel::Set<apfel::Distribution>>{EvolvedFFs, 100, distff->qMin(), distff->qMax(), 3, _Thresholds});

    // Initialise TMD objects for PDFs
    _TmdPdfObjs = apfel::InitializeTmdObjects(*_gpdf, _Thresholds);

    // Initialise TMD objects for FFs
    _TmdFfObjs = apfel::InitializeTmdObjects(*_gff, _Thresholds);

    // Build evolved TMD PDFs and FFs
    const int    pto = _config["PerturbativeOrder"].as<int>();
    const double Ci  = _config["TMDscales"]["Ci"].as<double>();
    const auto Alphas = [&] (double const& mu) -> double{ return _TabAlphas->Evaluate(mu); };

    const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution>{ return _TabPDFs->Evaluate(mu); };
    _EvTMDPDFs = BuildTmdPDFs(_TmdPdfObjs, CollPDFs, Alphas, pto, Ci);

    const auto CollFFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution>{ return _TabFFs->Evaluate(mu); };
    _EvTMDFFs = BuildTmdFFs(_TmdFfObjs, CollFFs, Alphas, pto, Ci);

    // Delete LHAPDF sets
    delete distpdf;
    delete distff;

    // Alpha_em (provided by APFEL)
    apfel::AlphaQED a{_config["alphaem"]["aref"].as<double>(), _config["alphaem"]["Qref"].as<double>(), _Thresholds, {0, 0, 1.777}, 0};
    _TabAlphaem = std::unique_ptr<apfel::TabulateObject<double>>(new apfel::TabulateObject<double>{a, 100, 0.9, 1001, 3});
  }

  //_________________________________________________________________________________
  apfel::DoubleObject<apfel::Distribution> FastInterface::LuminosityDY(double const& bT, double const& Q, double const& targetiso) const
  {
    // TMD scales
    const int    pto   = _config["PerturbativeOrder"].as<int>();
    const double Cf    = _config["TMDscales"]["Cf"].as<double>();
    const double aref  = _config["alphaem"]["aref"].as<double>();
    const bool   arun  = _config["alphaem"]["run"].as<bool>();
    const double muf   = Cf * Q;
    const double zetaf = Q * Q;

    // Whether the target is a particle or an antiparticle
    int sign = 1;
    if (targetiso < 0)
      sign = -1;

    // Fractions of protons and neutrons in the target
    const double frp = std::abs(targetiso);
    const double frn = 1 - frp;

    // Number of active flavours at 'Q'
    const int nf = apfel::NF(muf, _Thresholds);

    // EW charges
    const std::vector<double> Bq = apfel::ElectroWeakCharges(Q, true);

    // Electromagnetic coupling squared
    const double aem2 = pow((arun ? _TabAlphaem->Evaluate(Q) : aref), 2);

    // Compute the hard factor
    const double hcs = apfel::HardFactorDY(pto, _TabAlphas->Evaluate(muf), nf, Cf);

    // Global factor
    const double factor = apfel::ConvFact * 8 * M_PI * aem2 * hcs / 9 / pow(Q, 3);

    const std::map<int,apfel::Distribution> xF = QCDEvToPhys(_EvTMDPDFs(bT, muf, zetaf).GetObjects());
    apfel::DoubleObject<apfel::Distribution> Lumi;
    // Treat down and up separately to take isoscalarity of the target
    // into account
    Lumi.AddTerm({factor * Bq[0], frp * xF.at(sign)    + frn * xF.at(sign*2),  xF.at(-1)});
    Lumi.AddTerm({factor * Bq[0], frp * xF.at(-sign)   + frn * xF.at(-sign*2), xF.at(1)});
    Lumi.AddTerm({factor * Bq[1], frp * xF.at(sign*2)  + frn * xF.at(sign),    xF.at(-2)});
    Lumi.AddTerm({factor * Bq[1], frp * xF.at(-sign*2) + frn * xF.at(-sign),   xF.at(2)});
    // Now run over the remaining flavours
    for (int i = 3; i <= nf; i++)
      {
	const int ip = i * sign;
	Lumi.AddTerm({factor * Bq[i-1], xF.at(ip), xF.at(-i)});
	Lumi.AddTerm({factor * Bq[i-1], xF.at(-ip), xF.at(i)});
      }
    return Lumi;
  }

  //_________________________________________________________________________________
  apfel::DoubleObject<apfel::Distribution> FastInterface::LuminositySIDIS(double const& bT, double const& Q, double const& targetiso) const
  {
    // TMD scales
    const int    pto   = _config["PerturbativeOrder"].as<int>();
    const double Cf    = _config["TMDscales"]["Cf"].as<double>();
    const double aref  = _config["alphaem"]["aref"].as<double>();
    const bool   arun  = _config["alphaem"]["run"].as<bool>();
    const double muf   = Cf * Q;
    const double zetaf = Q * Q;

    // Whether the target is a particle or an antiparticle
    int sign = 1;
    if (targetiso < 0)
      sign = -1;

    // Fractions of protons and neutrons in the target
    const double frp = std::abs(targetiso);
    const double frn = 1 - frp;

    // Number of active flavours at 'Q'
    const int nf = apfel::NF(muf, _Thresholds);

    // EW charges
    const std::vector<double> Bq = apfel::ElectroWeakCharges(Q, false);

    // Electromagnetic coupling squared
    const double aem2 = pow((arun ? _TabAlphaem->Evaluate(Q) : aref), 2);

    // Compute the hard factor
    const double hcs = apfel::HardFactorSIDIS(pto, _TabAlphas->Evaluate(muf), nf, Cf);

    // Global factor (TO BE ADJUSTED!)
    const double factor = apfel::ConvFact * aem2 * hcs;

    const std::map<int,apfel::Distribution> xF = QCDEvToPhys(_EvTMDPDFs(bT, muf, zetaf).GetObjects());
    const std::map<int,apfel::Distribution> xD = QCDEvToPhys(_EvTMDFFs(bT, muf, zetaf).GetObjects());
    apfel::DoubleObject<apfel::Distribution> Lumi;
    // Treat down and up separately to take isoscalarity of the target
    // into account
    Lumi.AddTerm({factor * Bq[0], frp * xF.at(sign)    + frn * xF.at(sign*2),  xD.at(-1)});
    Lumi.AddTerm({factor * Bq[0], frp * xF.at(-sign)   + frn * xF.at(-sign*2), xD.at(1)});
    Lumi.AddTerm({factor * Bq[1], frp * xF.at(sign*2)  + frn * xF.at(sign),    xD.at(-2)});
    Lumi.AddTerm({factor * Bq[1], frp * xF.at(-sign*2) + frn * xF.at(-sign),   xD.at(2)});
    // Now run over the remaining flavours
    for (int i = 3; i <= nf; i++)
      {
	const int ip = i * sign;
	Lumi.AddTerm({factor * Bq[i-1], xF.at(ip), xD.at(-i)});
	Lumi.AddTerm({factor * Bq[i-1], xF.at(-ip), xD.at(i)});
      }
    return Lumi;
  }

  //_________________________________________________________________________________
  std::vector<YAML::Emitter> FastInterface::ComputeTables(std::vector<DataHandler> const& DHVect) const
  {
    // Retrieve relevant parameters for the numerical integration from
    // the configuration file
    const double bmax   = _config["bstar"]["bmax"].as<double>();
    const int    nOgata = _config["nOgata"].as<int>();
    const int    nQ     = _config["Qgrid"]["n"].as<int>();
    const int    idQ    = _config["Qgrid"]["InterDegree"].as<int>();
    const double epsQ   = _config["Qgrid"]["eps"].as<double>();
    const int    nxi    = _config["xigrid"]["n"].as<int>();
    const int    idxi   = _config["xigrid"]["InterDegree"].as<int>();
    const double epsxi  = _config["xigrid"]["eps"].as<double>();
    const double qToQ   = _config["qToverQmax"].as<double>();

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

	// Process
	const DataHandler::Process proc = DHVect[i].GetProcess();

	// Observable
	const DataHandler::Observable obs = DHVect[i].GetObservable();

	// Target isoscalarity
	const double targetiso = DHVect[i].GetTargetIsoscalarity();

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
	Tabs[i] << YAML::Key << "process" << YAML::Value << proc;
	Tabs[i] << YAML::Key << "observable" << YAML::Value << obs;
	Tabs[i] << YAML::Key << "target_isoscalarity" << YAML::Value << targetiso;
	Tabs[i] << YAML::Key << "CME" << YAML::Value << Vs;
	Tabs[i] << YAML::Key << "qTintegrated" << YAML::Value << IntqT;
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
	int nqT = 0;
	for (auto const& qT : qTv)
	  if (qT / Qb.first <= qToQ)
	    nqT++;
	const int nsteps = nqT * nO * nQe * nxie;

	// Counter for the status report
	int istep = 0;

	// Loop over the qT-bin bounds
	for (auto const& qT : qTv)
	  {
	    // Allocate container of the weights
	    std::vector<std::vector<std::vector<double>>> W(nO, std::vector<std::vector<double>>(nQe, std::vector<double>(nxie, 0.)));

	    // If the value of qT / Qmin is above that allowed print
	    // all zero's and constinue with the next value of qT
	    if (qT / Qb.first > qToQ)
	      {
		Tabs[i] << YAML::Key << qT;
		Tabs[i] << YAML::Value << YAML::Flow << W;
		continue;
	      }

	    // Loop over the Ogata-quadrature points
	    for (int n = 0; n < nO; n++)
	      {
		// Get impact parameters 'b' and 'b*'
		const double b  = zo[n] / qT;
		const double bs = bstar(b, bmax);

		// Call luminosity function
		std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> Lumi;
		Lumi = [&] (double const& Q) -> apfel::DoubleObject<apfel::Distribution>{ return LuminosityDY(bs, Q, targetiso); };
		const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> TabLumi{Lumi, 200, Qb.first, Qb.second, 1, {}};

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
			    return IQ * xiintegral;
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
