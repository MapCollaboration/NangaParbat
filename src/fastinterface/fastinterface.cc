//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//
#include <numeric> // std::accumulate

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/generategrid.h"
#include "NangaParbat/bstar.h"

#include <LHAPDF/LHAPDF.h>
#include <apfel/SIDIS.h>

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

    // Open LHAPDF PDF2 set
    LHAPDF::PDF* distpdf2 = LHAPDF::mkPDF(_config["pdfset2"]["name"].as<std::string>(), _config["pdfset2"]["member"].as<int>());

    // Rotate PDF set into the QCD evolution basis
    const auto RotPDFs = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x, mu)); };

    // Rotate PDF2 set into the QCD evolution basis
    const auto RotPDFs2 = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf2->xfxQ(x, mu)); };

    // Heavy-quark thresholds (from PDFs)
    for (auto const& v : distpdf->flavors())
      if (v > 0 && v < 7)
        _Thresholds.push_back(distpdf->quarkThreshold(v));

    // Alpha_s (from PDFs). Get it from the LHAPDF set and tabulate it.
    _TabAlphas = std::unique_ptr<apfel::TabulateObject<double>>(new apfel::TabulateObject<double> {[&] (double const& mu) -> double{return distpdf->alphasQ(mu); },
                                                                                                   100, distpdf->qMin() - 0.1, distpdf->qMax(), 3, _Thresholds
                                                                                                  });

    // Open LHAPDF FF set
    LHAPDF::PDF* distff = LHAPDF::mkPDF(_config["ffset"]["name"].as<std::string>(), _config["ffset"]["member"].as<int>());

    // Open LHAPDF FF2 set
    LHAPDF::PDF* distff2 = LHAPDF::mkPDF(_config["ffset2"]["name"].as<std::string>(), _config["ffset2"]["member"].as<int>());

    // Rotate FF set into the QCD evolution basis
    const auto RotFFs = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distff->xfxQ(x, mu)); };

    // Rotate FF2 set into the QCD evolution basis
    const auto RotFFs2 = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distff2->xfxQ(x, mu)); };

    // Define x-space grid for PDFs
    std::vector<apfel::SubGrid> vsgpdf;
    for (auto const& sg : _config["xgridpdf"])
      vsgpdf.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    _gpdf = std::unique_ptr<const apfel::Grid>(new apfel::Grid({vsgpdf}));

    // Define x-space grid for PDF2
    std::vector<apfel::SubGrid> vsgpdf2;
    for (auto const& sg : _config["xgridpdf"])
      vsgpdf2.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    _gpdf2 = std::unique_ptr<const apfel::Grid>(new apfel::Grid({vsgpdf2}));

    // Construct set of distributions as a function of the scale to be
    // tabulated for PDFs
    const auto EvolvedPDFs = [=] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, _Thresholds)}, DistributionMap(*_gpdf, RotPDFs, mu)};
    };

    // Construct set of distributions as a function of the scale to be
    // tabulated for PDF2
    const auto EvolvedPDFs2 = [=] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, _Thresholds)}, DistributionMap(*_gpdf2, RotPDFs2, mu)};
    };

    // Tabulate collinear PDFs
    _TabPDFs = std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>
               (new apfel::TabulateObject<apfel::Set<apfel::Distribution>> {EvolvedPDFs, 100, distpdf->qMin() - 0.1, distpdf->qMax(), 3, _Thresholds});

    // Tabulate collinear PDF2
    _TabPDFs2 = std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>
              (new apfel::TabulateObject<apfel::Set<apfel::Distribution>> {EvolvedPDFs2, 100, distpdf2->qMin() - 0.1, distpdf2->qMax(), 3, _Thresholds});

    // Define x-space grid for FFs
    std::vector<apfel::SubGrid> vsgff;
    for (auto const& sg : _config["xgridff"])
      vsgff.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    _gff = std::unique_ptr<const apfel::Grid>(new apfel::Grid({vsgff}));

    // Define x-space grid for FFs2
    std::vector<apfel::SubGrid> vsgff2;
    for (auto const& sg : _config["xgridff"])
      vsgff2.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    _gff2 = std::unique_ptr<const apfel::Grid>(new apfel::Grid({vsgff2}));

    // Construct set of distributions as a function of the scale to be
    // tabulated for FFs
    const auto EvolvedFFs = [=] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, _Thresholds)}, DistributionMap(*_gff, RotFFs, mu)};
    };

    // Construct set of distributions as a function of the scale to be
    // tabulated for FFs
    const auto EvolvedFFs2 = [=] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, _Thresholds)}, DistributionMap(*_gff2, RotFFs2, mu)};
    };

    // Tabulate collinear FFs
    _TabFFs = std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>
              (new apfel::TabulateObject<apfel::Set<apfel::Distribution>> {EvolvedFFs, 100, distff->qMin() - 0.1, distff->qMax(), 3, _Thresholds});

    // Tabulate collinear FFs2
    _TabFFs2 = std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>
              (new apfel::TabulateObject<apfel::Set<apfel::Distribution>> {EvolvedFFs2, 100, distff2->qMin() - 0.1, distff2->qMax(), 3, _Thresholds});

    // Initialise TMD objects for PDFs
    _TmdPdfObjs = apfel::InitializeTmdObjects(*_gpdf, _Thresholds);

    // Initialise TMD objects for FFs
    _TmdFfObjs = apfel::InitializeTmdObjects(*_gff, _Thresholds);

    // Initialise TMD objects for FFs
    _TmdFfObjs2 = apfel::InitializeTmdObjects(*_gff2, _Thresholds);

    // Build evolved TMD PDFs and FFs
    const int    pto = _config["PerturbativeOrder"].as<int>();
    const double Ci  = _config["TMDscales"]["Ci"].as<double>();
    const double Cf  = _config["TMDscales"]["Cf"].as<double>();
    const auto Alphas = [&] (double const& mu) -> double{ return _TabAlphas->Evaluate(mu); };

    const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return _TabPDFs->Evaluate(mu); };
    _EvTMDPDFs = BuildTmdPDFs(_TmdPdfObjs, CollPDFs, Alphas, pto, Ci);
    _MatchTMDPDFs = MatchTmdPDFs(_TmdPdfObjs, CollPDFs, Alphas, pto, Ci);

    const auto CollFFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return _TabFFs->Evaluate(mu); };
    _EvTMDFFs = BuildTmdFFs(_TmdFfObjs, CollFFs, Alphas, pto, Ci);
    _MatchTMDFFs = MatchTmdFFs(_TmdFfObjs, CollFFs, Alphas, pto, Ci);

    const auto CollFFs2 = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return _TabFFs2->Evaluate(mu); };
    _EvTMDFFs2 = BuildTmdFFs(_TmdFfObjs2, CollFFs2, Alphas, pto, Ci);
    _MatchTMDFFs2 = MatchTmdFFs(_TmdFfObjs2, CollFFs2, Alphas, pto, Ci);

    _QuarkSudakov = QuarkEvolutionFactor(_TmdPdfObjs, Alphas, pto, Ci, 1e5);

    _HardFactorDY    = apfel::HardFactor("DY",    _TmdPdfObjs, Alphas, pto, Cf);
    _HardFactorSIDIS = apfel::HardFactor("SIDIS", _TmdPdfObjs, Alphas, pto, Cf);

    // Delete LHAPDF sets
    delete distpdf;
    delete distpdf2;
    delete distff;
    delete distff2;

    // b* presciption
    _bstar = bstarMap.at(_config["bstar"].as<std::string>());

    // Alpha_em (provided by APFEL)
    apfel::AlphaQED a{_config["alphaem"]["aref"].as<double>(), _config["alphaem"]["Qref"].as<double>(), _Thresholds, {0, 0, 1.777}, 0};
    _TabAlphaem = std::unique_ptr<apfel::TabulateObject<double>>(new apfel::TabulateObject<double> {a, 100, 0.9, 1001, 3});
  }

  //_________________________________________________________________________________
  apfel::DoubleObject<apfel::Distribution> FastInterface::LuminosityDY(double const& bT, double const& Q, double const& targetiso) const
  {
    // TMD scales
    const double Cf    = _config["TMDscales"]["Cf"].as<double>();
    const double aref  = _config["alphaem"]["aref"].as<double>();
    const bool   arun  = _config["alphaem"]["run"].as<bool>();
    const double muf   = Cf * Q;
    const double zetaf = Q * Q;

    // Whether the target is a particle or an antiparticle
    const int sign = (targetiso >= 0 ? 1 : -1);

    // Fractions of protons and neutrons in the target
    const double frp = std::abs(targetiso);
    const double frn = 1 - frp;

    // Number of active flavours at 'Q'
    const int nf = apfel::NF(muf, _Thresholds);

    // EW charges
    const std::vector<double> Bq = apfel::ElectroWeakCharges(Q, true);

    // Electromagnetic coupling squared
    const double aem2 = pow((arun ? _TabAlphaem->Evaluate(Q) : aref), 2);

    // Global factor
    const double factor = apfel::ConvFact * 8 * M_PI * aem2 * _HardFactorDY(muf) / 9 / pow(Q, 3);
    const std::map<int, apfel::Distribution> xF = QCDEvToPhys(_EvTMDPDFs(bT, muf, zetaf).GetObjects());
    apfel::DoubleObject<apfel::Distribution> Lumi;

    // Treat down and up separately to take isoscalarity of the target
    // into account.
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
  std::vector<std::string> FastInterface::ComputeTables(std::vector<DataHandler> const& DHVect) const
  {
    std::vector<std::string> Tabs;
    for (auto const& dh : DHVect)
      {
        switch (dh.GetProcess())
          {
          case DataHandler::Process::DY:
            Tabs.push_back(ComputeTablesDY({dh})[0].c_str());
            break;
          case DataHandler::Process::SIDIS:
            Tabs.push_back(ComputeTablesSIDIS({dh})[0].c_str());
            break;
          default:
            throw std::runtime_error("[FastInterface::ComputeTables]: Unsupported process.");
          }
      }
    return Tabs;
  }

  //_________________________________________________________________________________
  std::vector<YAML::Emitter> FastInterface::ComputeTablesDY(std::vector<DataHandler> const& DHVect) const
  {
    // Retrieve relevant parameters for the numerical integration from
    // the configuration file
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

        // Report kinematic details of the dataset
        std::cout << DHVect[i] << std::endl;

        // Name of the dataset
        const std::string name = DHVect[i].GetName();

        // Process
        const DataHandler::Process proc = DHVect[i].GetProcess();

        // Stop the code if the process is not Drell-Yan
        if (proc != DataHandler::Process::DY)
          throw std::runtime_error("[FastInterface::ComputeTablesDY]: Only Drell-Yan data sets can be treated here.");

        // Target isoscalarity
        const double targetiso = DHVect[i].GetTargetIsoscalarity();

        // Prefactor
        const double prefactor = DHVect[i].GetPrefactor();

        // Retrieve kinematics
        const DataHandler::Kinematics                kin      = DHVect[i].GetKinematics();
        const double                                 Vs       = kin.Vs;       // C.M.E.
        const std::vector<double>                    qTv      = kin.qTv;      // Transverse momentum bin bounds
        const std::vector<std::pair<double, double>> qTmap    = kin.qTmap;    // Map of qT bounds to associate to the single bins
        const std::vector<double>                    qTfact   = kin.qTfact;   // Possible bin-by-bin prefactors to multiply the theoretical predictions
        const std::pair<double, double>              Qb       = kin.var1b;    // Invariant mass interval
        const std::pair<double, double>              yb       = kin.var2b;    // Rapidity interval
        const bool                                   IntqT    = kin.IntqT;    // Whether the bins in qTv are to be integrated over
        const bool                                   IntQ     = kin.Intv1;    // Whether the bin in Q is to be integrated over
        const bool                                   Inty     = kin.Intv2;    // Whether the bin in y is to be integrated over
        const bool                                   PSRed    = kin.PSRed;    // Whether there is a final-state PS reduction
        const double                                 pTMin    = kin.pTMin;    // Minimum pT of the final-state leptons
        const std::pair<double, double>              etaRange = kin.etaRange; // Allowed range in eta of the final-state leptons

        // Initialise two-particle phase-space object
        apfel::TwoBodyPhaseSpace ps{pTMin, etaRange.first, etaRange.second};

        // Ogata-quadrature object of degree one or zero according to
        // whether the cross sections have to be integrated over the
        // bins in qT or not.
        apfel::OgataQuadrature OgataObj{IntqT ? 1 : 0};

        // Unscaled coordinates and weights of the Ogata quadrature.
        std::vector<double> zo = OgataObj.GetCoordinates();
        std::vector<double> wo = OgataObj.GetWeights();

        // Construct QGrid-like grids for the integration in Q
        const double Qav = ( Qb.first + Qb.second ) / 2;
        const std::vector<double> Qg = (IntQ ? GenerateGrid(nQ, Qb.first, Qb.second, idQ - 1) : std::vector<double> {Qav});
        const apfel::QGrid<double> Qgrid{Qg, idQ};

        // Construct QGrid-like grids for the integration in y
        const double xil  = exp(yb.first);
        const double xiu  = exp(yb.second);
        const double xiav = exp( ( yb.first + yb.second ) / 2 );
        const std::vector<double> xig = (Inty ? GenerateGrid(nxi, xil, xiu, idxi - 1, true) : std::vector<double> {xiav});
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
        Tabs[i] << YAML::Key << "name"         << YAML::Value << name;
        Tabs[i] << YAML::Key << "process"      << YAML::Value << proc;
        Tabs[i] << YAML::Key << "CME"          << YAML::Value << Vs;
        Tabs[i] << YAML::Key << "qTintegrated" << YAML::Value << IntqT;
        Tabs[i] << YAML::Key << "qT_bounds"    << YAML::Value << YAML::Flow << qTv;
        Tabs[i] << YAML::Key << "qT_map"       << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (auto const& qTp : qTmap)
          Tabs[i] << YAML::Flow << YAML::BeginSeq << qTp.first << qTp.second << YAML::EndSeq;
        Tabs[i] << YAML::EndSeq;
        Tabs[i] << YAML::Key << "bin_factors"       << YAML::Value << YAML::Flow << qTfact;
        Tabs[i] << YAML::Key << "prefactor"         << YAML::Value << prefactor;
        Tabs[i] << YAML::Key << "Ogata_coordinates" << YAML::Value << YAML::Flow << std::vector<double>(zo.begin(), zo.begin() + nO);
        Tabs[i] << YAML::Key << "Qgrid"             << YAML::Value << YAML::Flow << Qg;
        Tabs[i] << YAML::Key << "xigrid"            << YAML::Value << YAML::Flow << xig;

        // Phase-space reduction factor and its derivative on the grid
        // in Q and xi for each value of qT. Equal to one and zero
        // respectively if no cut is present.
        std::map<double,std::vector<std::vector<double>>> mPS;
        std::map<double,std::vector<std::vector<double>>> mdPS;

        // Loop over the qT-bin bounds
        for (auto const& qT : qTv)
          {
            // Allocate containers of the PS reduction factors
            std::vector<std::vector<double>> PS(nQe, std::vector<double>(nxie, 1.));
            std::vector<std::vector<double>> dPS(nQe, std::vector<double>(nxie, 0.));
            if (PSRed)
              for (int tau = 0; tau < nQe; tau++)
                for (int alpha = 0; alpha < nxie; alpha++)
                  {
                    const double Q   = Qg[tau];
                    const double xi  = xig[alpha];
                    const double rap = log(xi);
                    PS[tau][alpha] = ps.PhaseSpaceReduction(Q, rap, qT);
                    if (IntqT)
                      dPS[tau][alpha] = ps.DerivePhaseSpaceReduction(Q, rap, qT);
                  }
            mPS.insert({qT, PS});
            mdPS.insert({qT, dPS});
          }

        // Output phase-space reduction factor and its
        // derivative.
        Tabs[i] << YAML::Newline << YAML::Newline;
        Tabs[i] << YAML::Comment("Phase-space cuts");
        Tabs[i] << YAML::Key << "PS_reduction_factor" << YAML::Value << YAML::Flow << mPS;
        Tabs[i] << YAML::Newline << YAML::Newline;
        Tabs[i] << YAML::Key << "PS_reduction_factor_derivative" << YAML::Value << YAML::Flow << mdPS;

        // Compute and write the weights
        Tabs[i] << YAML::Newline << YAML::Newline;
        Tabs[i] << YAML::Comment("Weights");
        Tabs[i] << YAML::Key << "weights" << YAML::Value << YAML::BeginMap;

        // Total number of steps for this particular table. Used to
        // report the percent progress of the computation.
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
            // all zero's and continue with the next value of qT
            if (qT / Qb.first > qToQ)
              {
                Tabs[i] << YAML::Key << qT << YAML::Value << YAML::Flow << W;
                continue;
              }

            // Loop over the Ogata-quadrature points
            for (int n = 0; n < nO; n++)
              {
                // Get impact parameters 'b' as the ratio beween the
                // Ogata coordinate and the qT.
                const double b = zo[n] / qT;

                // Tabulate luminosity function using b* as an impact
                // parameter. If no integration in Q is requested
                // compute the luminosity at "Qav" even when
                // tabulating.
                std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> Lumi =
                  [&] (double const& Q) -> apfel::DoubleObject<apfel::Distribution>
                {
                  const double Qt = (IntQ ? Q : Qav);
                  return LuminosityDY(_bstar(b, Qt), Qt, targetiso);
                };
                const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> TabLumi{Lumi, (IntQ ? 200 : 2), Qb.first, Qb.second, 1, {}};

                // Loop over the grids in Q
                for (int tau = 0; tau < nQe; tau++)
                  {
                    // Loop over the grid in xi
                    for (int alpha = 0; alpha < nxie; alpha++)
                      {
                        // Function to be integrated in Q
                        const apfel::Integrator QIntObj
                        {
                          [&] (double const& Q) -> double
                          {
                            // Function to be integrated in xi
                            const apfel::Integrator xiIntObj{
                              [&] (double const& xi) -> double
                              {
                                // Return xi integrand
                                return xigrid.Interpolant(0, alpha, xi) / xi * TabLumi.EvaluatexzQ(Q * xi / Vs, Q / xi / Vs, Q);
                              }
                            };
                            // Perform the integral in xi
                            double xiintegral = 0;
                            if (Inty)
                              for (int ixi = std::max(alpha - idxi, 0); ixi < std::min(alpha + 1, nxi); ixi++)
                                xiintegral += xiIntObj.integrate(xig[ixi], xig[ixi+1], epsxi);
                            else
                              xiintegral = xig[alpha] * xiIntObj.integrand(xig[alpha]);

                            // Return Q integrand
                            return Qgrid.Interpolant(0, tau, Q) * xiintegral;
                          }
                        };
                        // Perform the integral in Q
                        double Qintegral = 0;
                        if (IntQ)
                          for (int iQ = std::max(tau - idQ, 0); iQ < std::min(tau + 1, nQ); iQ++)
                            Qintegral += QIntObj.integrate(Qg[iQ], Qg[iQ+1], epsQ);
                        else
                          Qintegral = QIntObj.integrand(Qg[tau]);

                        // Compute the weight by multiplying the
                        // integral by the Ogata weight. If not
                        // intergrating over qT, multiply by b.
                        W[n][tau][alpha] = (IntqT ? 1 : b) * wo[n] * Qintegral;

                        // Report progress
                        istep++;
                        const double perc = 100. * istep / nsteps;
                        std::cout << "Status report for table '" << name << "': "<< std::setw(6) << std::setprecision(4) << perc << "\% completed...\r";
                        std::cout.flush();
                      }
                  }
              }
            Tabs[i] << YAML::Key << qT << YAML::Value << YAML::Flow << W;
          }
        Tabs[i] << YAML::EndMap;
        Tabs[i] << YAML::EndMap;

        // Stop timer and force to display the time elapsed
        std::cout << std::endl;
        t.stop(true);
      }
    std::cout << std::endl;

    return Tabs;
  }

  //_________________________________________________________________________________
  std::vector<YAML::Emitter> FastInterface::ComputeTablesSIDIS(std::vector<DataHandler> const& DHVect) const
  {
    // Retrieve relevant parameters for the numerical integration from
    // the configuration file
    const int    nOgata = _config["nOgata"].as<int>();
    const int    nQ     = _config["Qgrid"]["n"].as<int>();
    const int    idQ    = _config["Qgrid"]["InterDegree"].as<int>();
    //const double epsQ   = _config["Qgrid"]["eps"].as<double>();
    const int    nxb    = _config["xbgrid"]["n"].as<int>();
    const int    idxb   = _config["xbgrid"]["InterDegree"].as<int>();
    //const double epsxb  = _config["xbgrid"]["eps"].as<double>();
    const int    nz     = _config["zgrid"]["n"].as<int>();
    const int    idz    = _config["zgrid"]["InterDegree"].as<int>();
    //const double epsz   = _config["zgrid"]["eps"].as<double>();
    // const double qToQ   = _config["qToverQmax"].as<double>();
    const double param1   = _config["param1"].as<double>();
    const double param2   = _config["param2"].as<double>();
    const double param3   = _config["param3"].as<double>();
    const double Cf     = _config["TMDscales"]["Cf"].as<double>();
    const double aref   = _config["alphaem"]["aref"].as<double>();
    const bool   arun   = _config["alphaem"]["run"].as<bool>();
    const int    pto    = _config["PerturbativeOrder"].as<int>();

    // Initialise container of YAML::Emitter objects.
    std::vector<YAML::Emitter> Tabs(DHVect.size());

    // Loop over the vector of "Kinematics" objects
    std::cout << std::endl;
    for (int i = 0; i < (int) DHVect.size(); i++)
      {
        // Timer
        apfel::Timer t;

        // Report kinematic details of the dataset
        std::cout << DHVect[i] << std::endl;

        // Name of the dataset
        const std::string name = DHVect[i].GetName();

        // Whether the observable is differential in PhT^2 or not
        const bool dPhT2 = (name.substr(0, 7) == "COMPASS" ? true : false);

        // Process
        const DataHandler::Process proc = DHVect[i].GetProcess();

        // Stop the code if the process is not SIDIS
        if (proc != DataHandler::Process::SIDIS)
          throw std::runtime_error("[FastInterface::ComputeTablesSIDIS]: Only SIDIS data sets can be treated here.");

        // Retrieve kinematics
        const DataHandler::Kinematics                kin    = DHVect[i].GetKinematics();
        const double                                 Vs     = kin.Vs;       // C.M.E.
        const std::vector<double>                    qTv    = kin.qTv;      // Transverse momentum bin bounds
        const std::vector<std::pair<double, double>> qTmap  = kin.qTmap;    // Map of PhT bounds to associate to the single bins
        const std::vector<double>                    qTfact = kin.qTfact;   // Possible bin-by-bin prefactors to multiply the theoretical predictions
        const std::pair<double, double>              Qb     = kin.var1b;    // Invariant mass interval
        const std::pair<double, double>              xbb    = kin.var2b;    // Bjorken x interval
        const std::pair<double, double>              zb     = kin.var3b;    // z interval
        const bool                                   IntqT  = kin.IntqT;    // Whether the bins in qTv are to be integrated over
        const bool                                   IntQ   = kin.Intv1;    // Whether the bin in Q is to be integrated over
        const bool                                   Intxb  = kin.Intv2;    // Whether the bin in Bjorken x is to be integrated over
        const bool                                   Intz   = kin.Intv3;    // Whether the bin in z is to be integrated over
        const bool                                   PSRed  = kin.PSRed;    // Whether there is a final-state PS reduction
        const double                                 Wmin   = kin.pTMin;    // Minimum W of the final-state lepton
        const std::pair<double, double>              yRange = kin.etaRange; // Allowed y of the final-state lepton

        // Get average Q as average value in the bin
        std::vector<double> Qv(DHVect[i].GetKinematics().ndata);
        for (int j = 0; j < DHVect[i].GetKinematics().ndata; j++)
          Qv[j] = DHVect[i].GetBinning()[j].Qav;
        const double Qav = std::accumulate(Qv.begin(), Qv.end(), 0.) / Qv.size();

        // Get average x as average value in the bin
        std::vector<double> xv(DHVect[i].GetKinematics().ndata);
        for (int j = 0; j < DHVect[i].GetKinematics().ndata; j++)
          xv[j] = DHVect[i].GetBinning()[j].xav;
        const double xav = std::accumulate(xv.begin(), xv.end(), 0.) / xv.size();

        // Get average z as average value in the bin
        std::vector<double> zv(DHVect[i].GetKinematics().ndata);
        for (int j = 0; j < DHVect[i].GetKinematics().ndata; j++)
          zv[j] = DHVect[i].GetBinning()[j].zav;
        const double zav = std::accumulate(zv.begin(), zv.end(), 0.) / zv.size();

        // Tabulate initial scale TMD FFs in b in the physical basis
        std::function<apfel::Set<apfel::Distribution>(double const&)> isTMDFFs =
          [&] (double const& b) -> apfel::Set<apfel::Distribution>
        {
          return apfel::Set<apfel::Distribution>{QCDEvToPhys(_MatchTMDFFs(b).GetObjects())};
        };
        const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabMatchTMDFFs{isTMDFFs, 200, 1e-2, 2, 1, {},
                                                                                    [] (double const& x) -> double{ return log(x); },
                                                                                    [] (double const& y) -> double{ return exp(y); }};

        // Tabulate initial scale TMD FFs2 in b in the physical basis
        std::function<apfel::Set<apfel::Distribution>(double const&)> isTMDFFs2 =
          [&] (double const& b) -> apfel::Set<apfel::Distribution>
        {
          return apfel::Set<apfel::Distribution>{QCDEvToPhys(_MatchTMDFFs2(b).GetObjects())};
        };
        const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabMatchTMDFFs2{isTMDFFs2, 200, 1e-2, 2, 1, {},
                                                                                    [] (double const& x) -> double{ return log(x); },
                                                                                    [] (double const& y) -> double{ return exp(y); }};



        // Target isoscalarity
        const double targetiso = DHVect[i].GetTargetIsoscalarity();

        // Tabulate initial scale TMD PDFs in b in the physical basis
        // taking into account the isoscalarity of the target
        const int sign = (targetiso >= 0 ? 1 : -1);
        const double frp = std::abs(targetiso);
        const double frn = 1 - frp;
        std::function<apfel::Set<apfel::Distribution>(double const&)> isTMDPDFs =
          [&] (double const& b) -> apfel::Set<apfel::Distribution>
        {
          const apfel::Set<apfel::Distribution> xF = QCDEvToPhys(_MatchTMDPDFs(b).GetObjects());
          std::map<int, apfel::Distribution> xFiso;

          // Treat down and up separately to take isoscalarity of
          // the target into account.
          xFiso.insert({1,  frp * xF.at(sign) + frn * xF.at(sign*2)});
          xFiso.insert({-1, frp * xF.at(-sign) + frn * xF.at(-sign*2)});
          xFiso.insert({2,  frp * xF.at(sign*2) + frn * xF.at(sign)});
          xFiso.insert({-2, frp * xF.at(-sign*2) + frn * xF.at(-sign)});
          // Now run over the remaining flavours
          for (int i = 3; i <= 6; i++)
            {
              const int ip = i * sign;
              xFiso.insert({i, xF.at(ip)});
              xFiso.insert({-i, xF.at(-ip)});
            }
          return apfel::Set<apfel::Distribution>{xFiso};
        };
        const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabMatchTMDPDFs{isTMDPDFs, 200, 1e-2, 2, 1, {},
                                                                                     [] (double const& x) -> double{ return log(x); },
                                                                                     [] (double const& y) -> double{ return exp(y); }};

        // Compute inclusive cross section. First adjust PDFs to
        // account for the isoscalarity.
        const std::function<std::map<int, double>(double const&, double const&)> tPDFs = [&] (double const& x, double const& Q) -> std::map<int, double>
        {
          // Get PDFs in the physical basis
          const std::map<int, double> pr = apfel::QCDEvToPhys(_TabPDFs->EvaluateMapxQ(x, Q));
          std::map<int, double> tg = pr;
          // Apply isoscalarity
          tg.at(1)  = frp * pr.at(1)  + frn * pr.at(2);
          tg.at(2)  = frp * pr.at(2)  + frn * pr.at(1);
          tg.at(-1) = frp * pr.at(-1) + frn * pr.at(-2);
          tg.at(-2) = frp * pr.at(-2) + frn * pr.at(-1);
          return tg;
        };

        // Rotate input PDF set back into the QCD evolution basis
        const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int, double> { return apfel::PhysToQCDEv(tPDFs(x, mu)); };

        // EW charges (only photon contribution, i.e. only electric
        // charges squared).
        std::function<std::vector<double>(double const&)> fBq = [] (double const&) -> std::vector<double> { return apfel::QCh2; };

        // Determine perturbative order according to the logarithmic
        // accuracy
        int PerturbativeOrder = 0;
        if (pto > 1 || pto < 0)
          PerturbativeOrder++;
        if (pto > 2 || pto < -1)
          PerturbativeOrder++;

        // Initialise inclusive structure functions
        const auto IF2 = BuildStructureFunctions(InitializeF2NCObjectsZM(*_gpdf, _Thresholds), RotPDFs, PerturbativeOrder,
                                                 [=] (double const& Q) -> double{ return _TabAlphas->Evaluate(Q); }, fBq);
        const auto IFL = BuildStructureFunctions(InitializeFLNCObjectsZM(*_gpdf, _Thresholds), RotPDFs, PerturbativeOrder,
                                                 [=] (double const& Q) -> double{ return _TabAlphas->Evaluate(Q); }, fBq);

        // Q integrand for the inclusive cross section
        const apfel::Integrator IncQIntegrand{[=] (double const& Q) -> double
          {
            // Q-dependent factors of the cross section
            const apfel::Distribution f2 = IF2.at(0).Evaluate(Q);
            const apfel::Distribution fl = IFL.at(0).Evaluate(Q);

            // x integrand for the inclusive cross section
            const apfel::Integrator IncxIntegrand{
              [=] (double const& x) -> double
              {
                // Cross section
                return ( 1 + pow(1 - pow(Q / Vs, 2) / x, 2) ) * f2.Evaluate(x) / x - pow(Q / Vs, 4) * fl.Evaluate(x) / pow(x, 3);
              }
            };
            // Integration bounds in x accounting for fiducial cuts
            // if required.
            double xbmin = xbb.first;
            double xbmax = xbb.second;
            if (PSRed)
              {
                xbmin = std::min(xbmax, std::max(xbmin, pow(Q / Vs, 2) / yRange.second));
                xbmax = std::max(xbmin, std::min(std::min(xbmax, pow(Q / Vs, 2) / yRange.first), 1 / ( 1 + pow(Wmin / Q, 2) )));
              }
            return pow(_TabAlphaem->Evaluate(Q), 2) / pow(Q, 3) * (Intxb ? IncxIntegrand.integrate(xbmin, xbmax, 1e-5) : IncxIntegrand.integrand(xav)) / (2 * Q);
          }
        };

        // Prefactor that includes the inverse of the inclusive cross
        // section.  If no integration in Q is requested, compute the
        // integrand at Q average.
        const double prefactor = DHVect[i].GetPrefactor() / (IntQ ? IncQIntegrand.integrate(Qb.first, Qb.second, 1e-5) : IncQIntegrand.integrand(Qav));

        // Ogata-quadrature object of degree one or zero according to
        // whether the cross sections have to be integrated over the
        // bins in qT or not.
        apfel::OgataQuadrature OgataObj{IntqT ? 1 : 0};

        // Unscaled coordinates and weights of the Ogata quadrature.
        std::vector<double> zo = OgataObj.GetCoordinates();
        std::vector<double> wo = OgataObj.GetWeights();

        // Construct QGrid-like grids for the integration in Q
        const std::vector<double> Qg = (IntQ ? GenerateGrid(nQ, Qb.first, Qb.second, idQ - 1) : std::vector<double> {Qav});
        const apfel::QGrid<double> Qgrid{Qg, idQ};

        // Construct QGrid-like grids for the integration in Bjorken x
        const std::vector<double> xbg = (Intxb ? GenerateGrid(nxb, xbb.first, xbb.second, idxb - 1, true) : std::vector<double> {xav});
        const apfel::QGrid<double> xbgrid{xbg, idxb};

        // Construct QGrid-like grids for the integration in z
        const std::vector<double> zg = (Intz ? NangaParbat::GenerateGrid(nz, zb.first, zb.second, idz - 1, true) : std::vector<double> {zav});
        const apfel::QGrid<double> zgrid{zg, idz};

        // Number of points of the grids
        const int nO   = std::min(nOgata, (int) zo.size());
        const int nQe  = Qg.size();
        const int nxbe = xbg.size();
        const int nze  = zg.size();

        //Value of the cut qToverQmax as same as PV17
        double qToQ = std::min(param1 / zb.first, param2) + param3 / Qb.first / zb.first;
        // double qToQ = std::min(std::max( param2 , param3 / zb.first / Qb.first ) , 1 )

        // Write kinematics on the YAML emitter
        Tabs[i].SetFloatPrecision(8);
        Tabs[i].SetDoublePrecision(8);
        Tabs[i] << YAML::BeginMap;
        Tabs[i] << YAML::Comment("Kinematics and grid information");
        Tabs[i] << YAML::Key << "name"         << YAML::Value << name;
        Tabs[i] << YAML::Key << "process"      << YAML::Value << proc;
        Tabs[i] << YAML::Key << "CME"          << YAML::Value << Vs;
        Tabs[i] << YAML::Key << "qTintegrated" << YAML::Value << IntqT;
        Tabs[i] << YAML::Key << "qT_bounds"    << YAML::Value << YAML::Flow << qTv;
        Tabs[i] << YAML::Key << "qT_map"       << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (auto const& qTp : qTmap)
          Tabs[i] << YAML::Flow << YAML::BeginSeq << qTp.first << qTp.second << YAML::EndSeq;
        Tabs[i] << YAML::EndSeq;
        Tabs[i] << YAML::Key << "bin_factors"       << YAML::Value << YAML::Flow << qTfact;
        Tabs[i] << YAML::Key << "prefactor"         << YAML::Value << prefactor;
        Tabs[i] << YAML::Key << "Ogata_coordinates" << YAML::Value << YAML::Flow << std::vector<double>(zo.begin(), zo.begin() + nO);
        Tabs[i] << YAML::Key << "Qgrid"             << YAML::Value << YAML::Flow << Qg;
        Tabs[i] << YAML::Key << "xbgrid"            << YAML::Value << YAML::Flow << xbg;
        Tabs[i] << YAML::Key << "zgrid"             << YAML::Value << YAML::Flow << zg;

        // Compute and write the weights
        Tabs[i] << YAML::Newline << YAML::Newline;
        Tabs[i] << YAML::Comment("Weights");
        Tabs[i] << YAML::Key << "weights" << YAML::Value << YAML::BeginMap;

        // Total number of steps for this particular table. Used to
        // report the percent progress of the computation.
        int nqT = 0;
        for (auto const& qT : qTv)
          if (qT / Qb.first / zb.first <= qToQ)
            nqT++;
        const int nsteps = nqT * nO * nQe * nxbe * nze;

        std::cout << "ComputeTables report:" << std::endl;
        std::cout << "- Cut qT/Q: " << qToQ << std::endl;
        std::cout << "- Number of points that pass the cut: " << nqT << "\n" << std::endl;

        // Counter for the status report
        int istep = 0;

        // Maximum number of active flavours
        const int nf = apfel::NF(Qb.second, _Thresholds);

        // Loop over the qT-bin bounds. IMPORTANT: In the SIDIS case,
        // the vector "qTv" contains the values of of the hadronic pTh
        // (= zqT).
        for (auto const& qT : qTv)
          {
            // Allocate container for the weights
            std::vector<std::vector<std::vector<std::vector<double>>>>
            W(nO, std::vector<std::vector<std::vector<double>>>(nQe, std::vector<std::vector<double>>(nxbe, std::vector<double>(nze, 0.))));

            // If the value of qT / Qmin is above that allowed print
            // all zero's and continue with the next value of qT
            if (qT / Qb.first / zb.first > qToQ)
              {
                Tabs[i] << YAML::Key << qT << YAML::Value << YAML::Flow << W;
                continue;
              }

            // Loop over the Ogata-quadrature points
            for (int n = 0; n < nO; n++)
              {
                // Loop over the grids in Q
                for (int tau = 0; tau < nQe; tau++)
                  {
                    // Loop over the grid in xb
                    for (int alpha = 0; alpha < nxbe; alpha++)
                      {
                        // Loop over the grid in z
                        for (int beta = 0; beta < nze; beta++)
                          {
                            // Function to be integrated in Q
                            const apfel::Integrator QIntObj
                            {
                              [&] (double const& Q) -> double
                              {
                                // Renormalisation and rapidity scales
                                const double muf   = Cf * Q;
                                const double zetaf = Q * Q;

                                // Partonic fractional energy
                                const double TauP = pow(Q / Vs, 2);

                                // Function to be integrated in z
                                const apfel::Integrator zIntObj
                                {
                                  [&] (double const& z) -> double
                                  {
                                    // bstar at the relevant point
                                    const double bs = _bstar(z * zo[n] / qT, Q);

                                    // Sum up contribution from the
                                    // active flavours.
                                    double xbintegralq = 0;
                                    for (int q = -nf; q <= nf; q++)
                                      {
                                        // Skip the gluon
                                        if (q == 0)
                                          continue;

                                        // Function to be integrated in xb
                                        const apfel::Integrator xbIntObj
                                        {
                                          [&] (double const& xb) -> double
                                          {
                                            // Return x integrand
                                            const double Yp = 1 + pow(1 - TauP / xb, 2);
                                            return xbgrid.Interpolant(0, alpha, xb) * Yp * TabMatchTMDPDFs.EvaluatexQ(q, xb, bs) / xb;
                                          }
                                        };
                                        // Reduce the x-space integral
                                        // phase space according to
                                        // the fiducal cuts if
                                        // necessary.
                                        double xmin = 0;
                                        double xmax = 1;
                                        if (PSRed)
                                          {
                                            xmin = pow(Q / Vs, 2) / yRange.second;
                                            xmax = std::min(pow(Q / Vs, 2) / yRange.first, 1 / ( 1 + pow(Wmin / Q, 2)));
                                          }
                                        // Perform the integral in x
                                        double xbintegral = 0;
                                        if (Intxb)
                                          for (int ixb = std::max(alpha - idxb, 0); ixb < std::min(alpha + 1, nxb); ixb++)
                                            {
                                              if (xbg[ixb+1] < xmin || xbg[ixb] > xmax)
                                                continue;
                                              else if (xbg[ixb] < xmin && xbg[ixb+1] > xmin)
                                                xbintegral += xbIntObj.integrate(xmin, xbg[ixb+1], 0);
                                              else if (xbg[ixb] < xmax && xbg[ixb+1] > xmax)
                                                xbintegral += xbIntObj.integrate(xbg[ixb], xmax, 0);
                                              else if (xbg[ixb] < xmin && xbg[ixb+1] > xmax)
                                                xbintegral += xbIntObj.integrate(xmin, xmax, 0);
                                              else
                                                xbintegral += xbIntObj.integrate(xbg[ixb], xbg[ixb+1], 0);
                                            }
                                        else
                                          xbintegral = xbIntObj.integrand(xbg[alpha]);

                                        // Multiply by electric charge and the FF
                                        xbintegral *= apfel::QCh2[std::abs(q)-1] * (TabMatchTMDFFs.EvaluatexQ(q, z, bs) + TabMatchTMDFFs2.EvaluatexQ(q, z, bs));

                                        // Include current term
                                        xbintegralq += xbintegral;
                                      }

                                    // Return z integrand
                                    // If qT integration is not required, multiply by b = csi(0) / qT = csi(0) * z / PhT.
                                    return zgrid.Interpolant(0, beta, z) * pow(_QuarkSudakov(bs, muf, zetaf), 2) * xbintegralq / z * (IntqT ? 1 : (z * zo[n] / qT));
                                  }
                                };

                                // Perform the integral in z
                                double zintegral = 0;
                                if(Intz)
                                  for (int iz = std::max(beta - idz, 0); iz < std::min(beta + 1, nz); iz++)
                                    zintegral += zIntObj.integrate(zg[iz], zg[iz+1], 0) / (zb.second - zb.first);
                                else
                                  zintegral = zIntObj.integrand(zg[beta]) * (dPhT2 ? 1 / (2 * pow(zg[beta], 2) * qT / zg[beta]) : 1 / zg[beta]);

                                // Return Q integrand
                                return Qgrid.Interpolant(0, tau, Q) * pow((arun ? _TabAlphaem->Evaluate(Q) : aref), 2) * _HardFactorSIDIS(muf) / pow(Q, 3) * zintegral / (2 * Q);
                              }
                            };
                            // Perform the integral in Q
                            double Qintegral = 0;
                            if (IntQ)
                              for (int iQ = std::max(tau - idQ, 0); iQ < std::min(tau + 1, nQ); iQ++)
                                Qintegral += QIntObj.integrate(Qg[iQ], Qg[iQ+1], 0);
                            else
                              Qintegral = QIntObj.integrand(Qg[tau]);

                            // Compute the weight by multiplying the
                            // integral by the Ogata weight (note that
                            // a factor 4 * pi is missing because it
                            // cancels against the inclusive cross
                            // section in the denominator).
                            W[n][tau][alpha][beta] = wo[n] * Qintegral;

                            // Report progress
                            istep++;
                            const double perc = 100. * istep / nsteps;
                            std::cout << "Status report for table '" << name << "': "<< std::setw(6) << std::setprecision(4) << perc << "\% completed...\r";
                            std::cout.flush();
                          }
                      }
                  }
              }
            Tabs[i] << YAML::Key << qT << YAML::Value << YAML::Flow << W;
          }
        Tabs[i] << YAML::EndMap;
        Tabs[i] << YAML::EndMap;

        // Stop timer and force to display the time elapsed
        std::cout << std::endl;
        t.stop(true);
      }
    std::cout << std::endl;

    return Tabs;
  }

  //_________________________________________________________________________________
  std::vector<double> FastInterface::NormalisationFactorsSIDIS(std::vector<DataHandler> const& DHVect) const
  {
    // Get logarihtmic perturbative order
    const int pto = _config["PerturbativeOrder"].as<int>();

    // Determine perturbative order according to the logarithmic
    // accuracy
    int PerturbativeOrder = 0;
    if (pto > 1 || pto < 0)
      PerturbativeOrder++;
    if (pto > 2 || pto < -1)
      PerturbativeOrder++;

    // Initialize SIDIS objects (use the PDF grid)
    //const apfel::SidisObjects so = InitializeSIDIS(*_gpdf, *_gff);
    // The following line makes it possible to exclude the so-called "mixed" terms in the calculation of the collinear structure functions
    const apfel::SidisObjects so = InitializeSIDIS(*_gpdf2, *_gff, {5, 6, 8, 9, 10, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22});

    const apfel::SidisObjects so2 = InitializeSIDIS(*_gpdf2, *_gff2, {5, 6, 8, 9, 10, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22});

    // Initialise container of vector of normalisation factors
    std::vector<double> NormFacts(DHVect.size());

    // Loop over the vector of "Kinematics" objects
    for (int i = 0; i < (int) DHVect.size(); i++)
      {
        // Process
        const DataHandler::Process proc = DHVect[i].GetProcess();

        // Stop the code if the process is not SIDIS
        if (proc != DataHandler::Process::SIDIS)
          throw std::runtime_error("[FastInterface::NormalisationFactorsSIDIS]: Only SIDIS data sets can be treated here.");

        // Get target isoscalarity
        const double targetiso = DHVect[i].GetTargetIsoscalarity();

        // Fractions of protons and neutrons in the target
        const double frp = std::abs(targetiso);
        const double frn = 1 - frp;

        // Whether the target is isoscalar of proton or antiproton
        const int sign = (targetiso >= 0 ? 1 : -1);

        // Retrieve kinematics
        const DataHandler::Kinematics   kin   = DHVect[i].GetKinematics();
        const double                    Vs    = kin.Vs;       // C.M.E.
        const std::pair<double, double> Qb    = kin.var1b;    // Invariant mass interval
        const std::pair<double, double> xbb   = kin.var2b;    // Bjorken x interval
        const std::pair<double, double> zb    = kin.var3b;    // z interval
        const bool                      IntQ  = kin.Intv1;    // Whether the bin in Q is to be integrated over
        const bool                      Intxb = kin.Intv2;    // Whether the bin in Bjorken x is to be integrated over
        const bool                      Intz  = kin.Intv3;    // Whether the bin in z is to be integrated over

        // Define function to compute SIDIS fixed-order cross section at O(as)
        const std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> CrossSectionFO = [=] (double const& Q) -> apfel::DoubleObject<apfel::Distribution>
        {
          // Functions of x and z that multiplies the structure
          // functions.
          const std::function<double(double const&)> y2 = [=] (double const& x) -> double{ return pow(pow(Q / Vs, 2) / x, 2) / x; };
          const std::function<double(double const&)> yp = [=] (double const& x) -> double{ return ( 1 + pow(1 - pow(Q / Vs, 2) / x, 2) ) / x; };
          const std::function<double(double const&)> iz = [=] (double const& z) -> double{ return 1 / z; };

          // Compute number of active flavours
          const int nf = apfel::NF(Q, _Thresholds);

          // Coupling from PDF set
          const double coup = _TabAlphas->Evaluate(Q) / apfel::FourPi;

          // Get distributions for PDFs and FFs in the physical
          // basis.
          const std::map<int, apfel::Distribution> dPDF = apfel::QCDEvToPhys(_TabPDFs2->Evaluate(Q).GetObjects());
          const std::map<int, apfel::Distribution> dFF  = apfel::QCDEvToPhys(_TabFFs->Evaluate(Q).GetObjects());
          const std::map<int, apfel::Distribution> dFF2 = apfel::QCDEvToPhys(_TabFFs2->Evaluate(Q).GetObjects());

          // Put together double object
          apfel::DoubleObject<apfel::Distribution> distqq;
          apfel::DoubleObject<apfel::Distribution> distgq;
          apfel::DoubleObject<apfel::Distribution> distqg;

          apfel::DoubleObject<apfel::Distribution> distqq2;
          apfel::DoubleObject<apfel::Distribution> distgq2;
          apfel::DoubleObject<apfel::Distribution> distqg2;

          // Adjust up and down PDFs according to the target isoscalarity
          const apfel::Distribution dw  = frp * dPDF.at(sign)    + frn * dPDF.at(sign*2);
          const apfel::Distribution up  = frp * dPDF.at(sign*2)  + frn * dPDF.at(sign);
          const apfel::Distribution dwb = frp * dPDF.at(-sign)   + frn * dPDF.at(-sign*2);
          const apfel::Distribution upb = frp * dPDF.at(-sign*2) + frn * dPDF.at(-sign);

          distqq.AddTerm({apfel::QCh2[0], dw,         dFF.at(1)});
          distgq.AddTerm({apfel::QCh2[0], dw,         dFF.at(0)});
          distqg.AddTerm({apfel::QCh2[0], dPDF.at(0), dFF.at(1)});

          distqq.AddTerm({apfel::QCh2[0], dwb,        dFF.at(-1)});
          distgq.AddTerm({apfel::QCh2[0], dwb,        dFF.at(0)});
          distqg.AddTerm({apfel::QCh2[0], dPDF.at(0), dFF.at(-1)});

          distqq.AddTerm({apfel::QCh2[1], up,         dFF.at(2)});
          distgq.AddTerm({apfel::QCh2[1], up,         dFF.at(0)});
          distqg.AddTerm({apfel::QCh2[1], dPDF.at(0), dFF.at(2)});

          distqq.AddTerm({apfel::QCh2[1], upb,        dFF.at(-2)});
          distgq.AddTerm({apfel::QCh2[1], upb,        dFF.at(0)});
          distqg.AddTerm({apfel::QCh2[1], dPDF.at(0), dFF.at(-2)});

          // second FF

          distqq2.AddTerm({apfel::QCh2[0], dw,         dFF2.at(1)});
          distgq2.AddTerm({apfel::QCh2[0], dw,         dFF2.at(0)});
          distqg2.AddTerm({apfel::QCh2[0], dPDF.at(0), dFF2.at(1)});

          distqq2.AddTerm({apfel::QCh2[0], dwb,        dFF2.at(-1)});
          distgq2.AddTerm({apfel::QCh2[0], dwb,        dFF2.at(0)});
          distqg2.AddTerm({apfel::QCh2[0], dPDF.at(0), dFF2.at(-1)});

          distqq2.AddTerm({apfel::QCh2[1], up,         dFF2.at(2)});
          distgq2.AddTerm({apfel::QCh2[1], up,         dFF2.at(0)});
          distqg2.AddTerm({apfel::QCh2[1], dPDF.at(0), dFF2.at(2)});

          distqq2.AddTerm({apfel::QCh2[1], upb,        dFF2.at(-2)});
          distgq2.AddTerm({apfel::QCh2[1], upb,        dFF2.at(0)});
          distqg2.AddTerm({apfel::QCh2[1], dPDF.at(0), dFF2.at(-2)});

          // Now run over the other quark flavours
          for (auto j = 3; j <= nf; j++)
            {
              const int jp = j * sign;
              distqq.AddTerm({apfel::QCh2[j-1], dPDF.at(jp), dFF.at(jp)});
              distgq.AddTerm({apfel::QCh2[j-1], dPDF.at(jp), dFF.at(0)});
              distqg.AddTerm({apfel::QCh2[j-1], dPDF.at(0),  dFF.at(jp)});

              distqq.AddTerm({apfel::QCh2[j-1], dPDF.at(-jp), dFF.at(-jp)});
              distgq.AddTerm({apfel::QCh2[j-1], dPDF.at(-jp), dFF.at(0)});
              distqg.AddTerm({apfel::QCh2[j-1], dPDF.at(0),   dFF.at(-jp)});

              // second FF

              distqq2.AddTerm({apfel::QCh2[j-1], dPDF.at(jp), dFF2.at(jp)});
              distgq2.AddTerm({apfel::QCh2[j-1], dPDF.at(jp), dFF2.at(0)});
              distqg.AddTerm({apfel::QCh2[j-1], dPDF.at(0),  dFF2.at(jp)});

              distqq2.AddTerm({apfel::QCh2[j-1], dPDF.at(-jp), dFF2.at(-jp)});
              distgq2.AddTerm({apfel::QCh2[j-1], dPDF.at(-jp), dFF2.at(0)});
              distqg2.AddTerm({apfel::QCh2[j-1], dPDF.at(0),   dFF2.at(-jp)});

            }

          // Assemble double distribution for the cross section as
          // Y^+ F2 - y^2 FL times a constant.
          return ( 4 * M_PI * pow(_TabAlphaem->Evaluate(Q), 2) / pow(Q, 3) )
                 * ( ( ( so.C20qq + coup * so.C21qq ) * distqq + coup * ( so.C21gq * distgq + so.C21qg * distqg ) ).MultiplyBy(yp, iz)
                     - ( coup * ( so.CL1qq * distqq + so.CL1gq * distgq + so.CL1qg * distqg ) ).MultiplyBy(y2, iz) ) +
                 ( 4 * M_PI * pow(_TabAlphaem->Evaluate(Q), 2) / pow(Q, 3) )
                 * ( ( ( so2.C20qq + coup * so2.C21qq ) * distqq2 + coup * ( so2.C21gq * distgq2 + so2.C21qg * distqg2 ) ).MultiplyBy(yp, iz)
                     - ( coup * ( so2.CL1qq * distqq2 + so2.CL1gq * distgq2 + so2.CL1qg * distqg2 ) ).MultiplyBy(y2, iz) );
        };

        // Tabulate cross section
        const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> TabCrossSectionFO{CrossSectionFO, 50, 1, 20, 3, _Thresholds};

        // Define function to compute SIDIS asymptotic cross section at O(as)
        const std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> CrossSectionAsy = [=] (double const& Q) -> apfel::DoubleObject<apfel::Distribution>
        {
          // Functions of x and z that multiplies the structure
          // functions.
          const std::function<double(double const&)> yp = [=] (double const& x) -> double{ return ( 1 + pow(1 - pow(Q / Vs, 2) / x, 2) ) / x; };
          const std::function<double(double const&)> iz = [=] (double const& z) -> double{ return 1 / z; };

          // Compute number of active flavours
          const int nf = apfel::NF(Q, _Thresholds);

          // Get matched PDFs and FFs in the physical basis
          const double bmin = _config["TMDscales"]["Ci"].as<double>() * 2 * exp(- apfel::emc) / Q;
          const std::map<int, apfel::Distribution> dPDF = apfel::QCDEvToPhys(_MatchTMDPDFs(bmin).GetObjects());
          const std::map<int, apfel::Distribution> dFF  = apfel::QCDEvToPhys(_MatchTMDFFs(bmin).GetObjects());
          const std::map<int, apfel::Distribution> dFF2  = apfel::QCDEvToPhys(_MatchTMDFFs2(bmin).GetObjects());

          // Put together double object
          apfel::DoubleObject<apfel::Distribution> distqq;
          apfel::DoubleObject<apfel::Distribution> distqq2;


          // Adjust up and down PDFs according to the target isoscalarity
          const apfel::Distribution dw  = frp * dPDF.at(sign)   + frn * dPDF.at(sign*2);
          const apfel::Distribution up  = frp * dPDF.at(sign*2) + frn * dPDF.at(sign);
          const apfel::Distribution dwb = frp * dPDF.at(-sign)   + frn * dPDF.at(-sign*2);
          const apfel::Distribution upb = frp * dPDF.at(-sign*2) + frn * dPDF.at(-sign);

          distqq.AddTerm({apfel::QCh2[0], dw,  dFF.at(1)});
          distqq.AddTerm({apfel::QCh2[0], dwb, dFF.at(-1)});
          distqq.AddTerm({apfel::QCh2[1], up,  dFF.at(2)});
          distqq.AddTerm({apfel::QCh2[1], upb, dFF.at(-2)});

          // second FF

          distqq2.AddTerm({apfel::QCh2[0], dw,  dFF2.at(1)});
          distqq2.AddTerm({apfel::QCh2[0], dwb, dFF2.at(-1)});
          distqq2.AddTerm({apfel::QCh2[1], up,  dFF2.at(2)});
          distqq2.AddTerm({apfel::QCh2[1], upb, dFF2.at(-2)});

          // Now run over the other quark flavours
          for (auto j = 3; j <= nf; j++)
            {
              const int jp = j * sign;
              distqq.AddTerm({apfel::QCh2[j-1], dPDF.at(jp),  dFF.at(jp)});
              distqq.AddTerm({apfel::QCh2[j-1], dPDF.at(-jp), dFF.at(-jp)});

              // second FF

              distqq2.AddTerm({apfel::QCh2[j-1], dPDF.at(jp),  dFF2.at(jp)});
              distqq2.AddTerm({apfel::QCh2[j-1], dPDF.at(-jp), dFF2.at(-jp)});
            }

          return ( 4 * M_PI * pow(_TabAlphaem->Evaluate(Q), 2) / pow(Q, 3) * _HardFactorSIDIS(Q) ) * distqq.MultiplyBy(yp, iz) + ( 4 * M_PI * pow(_TabAlphaem->Evaluate(Q), 2) / pow(Q, 3) * _HardFactorSIDIS(Q) ) * distqq2.MultiplyBy(yp, iz);
        };

        // Tabulate cross section
        const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> TabCrossSectionAsy{CrossSectionAsy, 50, 1, 20, 3, {}};

        // Put normalisation factor together integrating as
        // appropriate. If the accuracy is LO set it to one.
        if (PerturbativeOrder == 0)
          NormFacts[i] = 1;
        else if (!IntQ && !Intxb && !Intz)
          NormFacts[i] = TabCrossSectionFO.Evaluate(( Qb.first + Qb.second ) / 2).Evaluate(( xbb.first + xbb.second ) / 2, ( zb.first + zb.second ) / 2)
                         / TabCrossSectionAsy.Evaluate(( Qb.first + Qb.second ) / 2).Evaluate(( xbb.first + xbb.second ) / 2, ( zb.first + zb.second ) / 2);
        else if (!IntQ && !Intxb && Intz)
          NormFacts[i] = TabCrossSectionFO.Evaluate(( Qb.first + Qb.second ) / 2).Integrate2(zb.first, zb.second ).Evaluate(( xbb.first + xbb.second ) / 2)
                         / TabCrossSectionAsy.Evaluate(( Qb.first + Qb.second ) / 2).Integrate2(zb.first, zb.second ).Evaluate(( xbb.first + xbb.second ) / 2);
        else if (!IntQ && Intxb && !Intz)
          NormFacts[i] = TabCrossSectionFO.Evaluate(( Qb.first + Qb.second ) / 2).Integrate1(xbb.first, xbb.second ).Evaluate(( zb.first + zb.second ) / 2)
                         / TabCrossSectionAsy.Evaluate(( Qb.first + Qb.second ) / 2).Integrate2(zb.first, zb.second ).Evaluate(( xbb.first + xbb.second ) / 2);
        else if (!IntQ && Intxb && Intz)
          NormFacts[i] = TabCrossSectionFO.Evaluate(( Qb.first + Qb.second ) / 2).Integrate(xbb.first, xbb.second, zb.first, zb.second)
                         / TabCrossSectionAsy.Evaluate(( Qb.first + Qb.second ) / 2).Integrate(xbb.first, xbb.second, zb.first, zb.second);
        else if (IntQ && !Intxb && !Intz)
          NormFacts[i] = TabCrossSectionFO.Integrate(Qb.first, Qb.second).Evaluate(( xbb.first + xbb.second ) / 2, ( zb.first + zb.second ) / 2)
                         / TabCrossSectionAsy.Integrate(Qb.first, Qb.second).Evaluate(( xbb.first + xbb.second ) / 2, ( zb.first + zb.second ) / 2);
        else if (IntQ && !Intxb && Intz)
          NormFacts[i] = TabCrossSectionFO.Integrate(Qb.first, Qb.second).Integrate2(zb.first, zb.second ).Evaluate(( xbb.first + xbb.second ) / 2)
                         / TabCrossSectionAsy.Integrate(Qb.first, Qb.second).Integrate2(zb.first, zb.second ).Evaluate(( xbb.first + xbb.second ) / 2);
        else if (IntQ && Intxb && !Intz)
          NormFacts[i] = TabCrossSectionFO.Integrate(Qb.first, Qb.second).Integrate1(xbb.first, xbb.second ).Evaluate(( zb.first + zb.second ) / 2)
                         / TabCrossSectionAsy.Integrate(Qb.first, Qb.second).Integrate2(zb.first, zb.second ).Evaluate(( xbb.first + xbb.second ) / 2);
        else
          NormFacts[i] = TabCrossSectionFO.Integrate(Qb.first, Qb.second).Integrate(xbb.first, xbb.second, zb.first, zb.second)
                         / TabCrossSectionAsy.Integrate(Qb.first, Qb.second).Integrate(xbb.first, xbb.second, zb.first, zb.second);

        std::cout << "Computing SIDIS normalisation factors..." << std::setw(6) << std::setprecision(4) << 100. * ( i + 1 ) / DHVect.size() << "\% completed\r";
        std::cout.flush();
      }

    return NormFacts;
  }
}
