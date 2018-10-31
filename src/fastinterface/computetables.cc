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
  std::vector<Kinematics> RetrieveKinematics(YAML::Node const& datalist)
  {
    // Initialise output container
    std::vector<Kinematics> KinVect;

    // Loop over the dataset list. Each dataset may have more than one
    // distribution. Threfore, loop also over the distributions.
    for (auto const& dl : datalist)
      for (auto const& dist : dl.second)
	{
	  // Open HEPData datafile name
	  const YAML::Node df = YAML::LoadFile("../Data/" + dl.first.as<std::string>() + "/" + dist.as<std::string>());

	  // Initialise a "Kinematics" object
	  Kinematics kin;

	  // Assing to the "kin" structure the name of the data file
	  // along with its folder.
	  kin.name = dl.first.as<std::string>() + "_" + dist.as<std::string>();

	  // Retrieve kinematics
	  for (auto const& dv : df["dependent_variables"])
	    for (auto const& ql : dv["qualifiers"])
	      {
		// We assume that each table contains one single bin
		// in rapidity and one single bin in invariant mass
		// that need to be integrated over. In addition we
		// interpret the qT vector as a vector o bounds of the
		// bins that also need to be integrated over.
		kin.IntqT = true;

		// Rapidity interval interval
		if (ql["name"].as<std::string>() == "ABS(ETARAP)")
		  {
		    std::string tmp;
		    std::stringstream ss(ql["value"].as<std::string>());
		    ss >> tmp >> kin.yb.second;
		    kin.yb.first = - kin.yb.second;
		  }

		// Invariant-mass interval
		if (ql["name"].as<std::string>() == "M(P=3_4)")
		  {
		    std::string tmp;
		    std::stringstream ss(ql["value"].as<std::string>());
		    ss >> kin.Qb.first >> tmp >> kin.Qb.second;
		  }

		// Center-of-mass energy
		if (ql["name"].as<std::string>() == "SQRT(S)")
		  kin.Vs = ql["value"].as<double>();
	      }

	  // Transverse momentum bin bounds
	  std::vector<double> qTv;
	  for (auto const& iv : df["independent_variables"])
	    for (auto const& vl : iv["values"])
	      {
		if(std::find(kin.qTv.begin(), kin.qTv.end(), vl["low"].as<double>()) == kin.qTv.end())
		  kin.qTv.push_back(std::max(vl["low"].as<double>(), 1e-5));
		if(std::find(kin.qTv.begin(), kin.qTv.end(), vl["high"].as<double>()) == kin.qTv.end())
		  kin.qTv.push_back(vl["high"].as<double>());
	      }

	  // Push "Kinematics" object into the container
	  KinVect.push_back(kin);
	}
    return KinVect;
  }

  //_________________________________________________________________________________
  std::vector<YAML::Emitter> ComputeTables(YAML::Node const& config, std::vector<Kinematics> const& KinVect)
  {
    // Set verbosity level of APFEL++
    apfel::SetVerbosityLevel(config["verbosity"].as<int>());

    // Open LHAPDF set
    LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());

    // Heavy-quark thresholds
    std::vector<double> Thresholds;
    for (auto const& v : distpdf->flavors())
      if (v > 0 && v < 7)
	Thresholds.push_back(distpdf->quarkThreshold(v));

    // Alpha_s
    const auto Alphas = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };

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

    // Tabulate collinear PDFs
    const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, distpdf->qMin(), distpdf->qMax(), 3, Thresholds};
    const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

    // Initialize TMD objects
    const auto TmdObj = apfel::InitializeTmdObjects(g, Thresholds);

    // Build evolved TMD PDFs
    const auto EvTMDPDFs = BuildTmdPDFs(TmdObj, CollPDFs, Alphas, config["PerturbativeOrder"].as<int>(), config["TMDscales"]["Ci"].as<double>());

    // Alpha_em
    const apfel::AlphaQED alphaem{config["alphaem"]["aref"].as<double>(), config["alphaem"]["Qref"].as<double>(), Thresholds, {0, 0, 1.777}, 0};

    // Retrieve relevant parameters from the configuration file
    const double Cf     = config["TMDscales"]["Cf"].as<double>();
    const double eps    = config["integration_accuracy"].as<double>();
    const int    nOgata = config["nOgata"].as<int>();
    const int    nQ     = config["Qgrid"]["nQ"].as<int>();
    const int    idQ    = config["Qgrid"]["InterDegreeQ"].as<int>();
    const int    nxi    = config["xigrid"]["nxi"].as<int>();
    const int    idxi   = config["xigrid"]["InterDegreexi"].as<int>();

    // Initialise container of YAML:Emitter objects.
    std::vector<YAML::Emitter> Tabs(KinVect.size());

    // Loop over the vector of "Kinematics" objects
    for (int i = 0; i < (int) KinVect.size(); i++)
      {
	// Timer
	apfel::Timer t;

	// Retrieve kinematics
	double                   Vs  = KinVect[i].Vs;  // C.M.E.
	std::pair<double,double> yb  = KinVect[i].yb;  // Rapidity interval
	std::pair<double,double> Qb  = KinVect[i].Qb;  // Invariant mass interval
	std::vector<double>      qTv = KinVect[i].qTv; // Transverse momentum bin bounds

	// Ogata-quadrature object of degree one or zero according to
	// weather the cross sections have to be integrated over the
	// bins in qT or not.
	apfel::OgataQuadrature OgataObj{(KinVect[i].IntqT ? 1 : 0)};

	// Unscaled coordinates and weights of the Ogata quadrature.
	std::vector<double> zo = OgataObj.GetCoordinates();
	std::vector<double> wo = OgataObj.GetWeights();

	// Construct QGrid-like grids for the integration in Q and y
	const std::vector<double> Qg  = GenerateQGrid(nQ, Qb.first, Qb.second);
	const std::vector<double> xig = GenerateQGrid(nxi, exp(yb.first), exp(yb.second));
	const apfel::QGrid<double> Qgrid {Qg,  idQ};
	const apfel::QGrid<double> xigrid{xig, idxi};

	// Write kinematics on the YAML emitter
	Tabs[i].SetFloatPrecision(8);
	Tabs[i].SetDoublePrecision(8);
	Tabs[i] << YAML::BeginMap;
	Tabs[i] << YAML::Comment("Kinematics and grid information");
	Tabs[i] << YAML::Key << "name" << YAML::Value << KinVect[i].name;
	Tabs[i] << YAML::Key << "CME" << YAML::Value << Vs;
	Tabs[i] << YAML::Key << "qT_bounds" << YAML::Value << YAML::Flow << qTv;
	Tabs[i] << YAML::Key << "Ogata_coordinates" << YAML::Value << YAML::Flow << std::vector<double>(zo.begin(), zo.begin() + nOgata);
	Tabs[i] << YAML::Key << "Qgrid" << YAML::Value << YAML::Flow << std::vector<double>(Qg.begin(), Qg.end() - 1);
	Tabs[i] << YAML::Key << "xigrid" << YAML::Value << YAML::Flow << std::vector<double>(xig.begin(), xig.end() - 1);
	Tabs[i] << YAML::EndMap;
	Tabs[i] << YAML::Newline;
	Tabs[i] << YAML::BeginMap;
	Tabs[i] << YAML::Comment("Weights");

	// Loop over the qT-bin bounds
	for (auto const& qT : qTv)
	  {
	    // Allocate container of the weights
	    std::vector<std::vector<std::vector<double>>> W(nOgata, std::vector<std::vector<double>>(nQ, std::vector<double>(nxi)));

	    // Loop over the Ogata-quadrature points
	    for (int n = 0; n < std::min(nOgata, (int) zo.size()); n++)
	      {
		// Get impact parameters 'b' and 'b*'
		const double b  = zo[n] / qT;
		const double bs = bstar(b, config["bstar"]["bmax"].as<double>());

		// Tabulate TMDs in Q
		const auto EvolvedTMDPDFs = [&] (double const& Q) -> apfel::Set<apfel::Distribution>{ return EvTMDPDFs(bs, Cf * Q, Q * Q); };
		const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabEvolvedTMDPDFs{EvolvedTMDPDFs, Qg, idQ};

		// Loop over the grids in Q
		for (int tau = 0; tau < nQ; tau++)
		  // Loop over the grid in xi
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

			  // Get Evolved TMD PDFs and rotate them into
			  // the physical basis
			  const std::map<int,apfel::Distribution> xF = QCDEvToPhys(TabEvolvedTMDPDFs.Evaluate(Q).GetObjects());

			  // Function to be integrated in xi
			  const auto xiintegrand = [&] (double const& xi) -> double
			  {
			    // Compute 'x1' and 'x2'
			    const double x1 = Q * xi / Vs;
			    const double x2 = Q / xi / Vs;

			    // Get interpolating function in xi
			    const double Ixi = xigrid.Interpolant(0, alpha, xi);

			    // Combine TMDs through the EW charges
			    double integrand = 0;
			    for (int i = 1; i <= nf; i++)
			      integrand += Bq[i-1] * ( xF.at(i).Evaluate(x1) * xF.at(-i).Evaluate(x2) + xF.at(-i).Evaluate(x1) * xF.at(i).Evaluate(x2) );

			    // Return xi integrand
			    return Ixi * integrand / xi;
			  };

			  // Get integration bounds and fixed points
			  // in xi to help the integration
			  const int iximin = std::max(alpha - idxi, 0);
			  const int iximax = std::min(alpha + 1, nxi);
			  std::vector<double> FixPtsxi(xig.begin() + iximin + 1, xig.begin() + std::max(iximax - 1, iximin + 1));

			  // Perform the integral in xi
			  const apfel::Integrator xiIntObj{xiintegrand};
			  const double xiintegral = xiIntObj.integrate(xig[iximin], xig[iximax], FixPtsxi, eps);

			  // Get interpolating function in Q
			  const double IQ = Qgrid.Interpolant(0, tau, Q);

			  // Electromagnetic coupling squared
			  const double aem2 = pow((config["alphaem"]["run"].as<bool>() ? alphaem.Evaluate(Q) : config["alphaem"]["ref"].as<double>()), 2);

			  // Compute the hard factor
			  const double hcs = apfel::HardFactorDY(config["PerturbativeOrder"].as<int>(), Alphas(muf), nf, Cf);

			  // Return Q integrand
			  return IQ * aem2 * hcs * xiintegral / pow(Q, 3);
			};

		      // Get integration bounds and fixed points in Q
		      // to help the integration
		      const int iQmin = std::max(tau - idQ, 0);
		      const int iQmax = std::min(tau + 1, nQ);
		      std::vector<double> FixPtsQ(Qg.begin() + iQmin + 1, Qg.begin() + std::max(iQmax - 1, iQmin + 1));

		      // Perform the integral in Q
		      const apfel::Integrator QIntObj{Qintegrand};
		      const double Qintegral = QIntObj.integrate(Qg[iQmin], Qg[iQmax], FixPtsQ, eps);

		      // Compute the weight
		      W[n][tau][alpha] = apfel::ConvFact * 8 * M_PI * wo[n] * Qintegral / 9;

		      // If not intergrating over qT multiply by b =
		      // zo[n] / qT.
		      if (!KinVect[i].IntqT)
			W[n][tau][alpha] *= zo[n] / qT;
		    }
	      }
	    Tabs[i] << YAML::Key << qT;
	    Tabs[i] << YAML::Value << YAML::Flow << W;
	  }
	Tabs[i] << YAML::EndMap;
	t.stop();
      }
    return Tabs;
  }
}
