//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/tmdgrid.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"

#include <apfel/apfelxx.h>
#include <LHAPDF/LHAPDF.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> TMDGrid(YAML::Node          const& config,
                                         std::string         const& parameterisation,
                                         std::vector<double> const& params,
                                         std::string         const& pf)
  {
    // Open LHAPDF set
    LHAPDF::PDF* dist = LHAPDF::mkPDF(config[pf + "set"]["name"].as<std::string>(), config[pf + "set"]["member"].as<int>());

    // Rotate sets into the QCD evolution basis
    const auto RotDists = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(dist->xfxQ(x, mu)); };

    // Heavy-quark thresholds
    std::vector<double> Thresholds;
    std::vector<double> bThresholds;
    std::vector<int> flv;
    const double Ci  = config["TMDscales"]["Ci"].as<double>();
    for (int f : dist->flavors())
      if (f > 0 && f < 7)
        {
          Thresholds.push_back(dist->quarkThreshold(f));
          bThresholds.push_back(Ci * 2 * exp(- apfel::emc) / dist->quarkThreshold(f));
          flv.push_back(f);
          flv.insert(flv.begin(), -f);
        }
    sort(bThresholds.begin(), bThresholds.end());

    // Set verbosity level of APFEL++ to the minimum
    apfel::SetVerbosityLevel(0);

    // Define x-space grid
    std::vector<apfel::SubGrid> vsg;
    for (auto const& sg : config["xgrid" + pf])
      vsg.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    const apfel::Grid g{vsg};

    // Construct set of distributions as a function of the scale to be
    // tabulated.
    const auto EvolvedDists = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, Thresholds)}, DistributionMap(g, RotDists, mu)};
    };

    // Tabulate collinear distributions
    const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabDists{EvolvedDists, 100, dist->qMin(), dist->qMax(), 3, Thresholds};

    // Build evolved TMD distributions
    const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };
    const auto CollDists = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabDists.Evaluate(mu); };

    const int pto = config["PerturbativeOrder"].as<int>();
    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> EvTMDs;
    if (pf == "pdf")
      EvTMDs = BuildTmdPDFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
    else if (pf == "ff")
      EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
    else
      throw std::runtime_error("[PlotTMDs]: Unknown distribution prefix");

    // b* prescription
    const std::function<double(double const&, double const&)> bs = bstarMap.at(config["bstar"].as<std::string>());

    // Double exponential quadrature
    apfel::DoubleExponentialQuadrature DEObj{};

    // Grid in Q
    const std::vector<double> Qg
    {
      1.000000e+00, 1.224745e+00, 1.581139e+00,
      1.788854e+00, 2.236068e+00, 2.828427e+00,
      3.162278e+00, 4.750000e+00, 6.324555e+00,
      8.000000e+00, 1.264911e+01, 2.000000e+01,
      2.529822e+01, 4.242641e+01, 7.483315e+01,
      9.118760e+01, 1.341641e+02, 2.366432e+02,
      3.162278e+02, 5.656854e+02, 1.000000e+03,
      1.341641e+03, 2.366432e+03, 4.242641e+03,
      5.656854e+03, 1.000000e+04
    };

    // Grid in x
    const std::vector<double> xg
    {
      1.000000e-05, 2.000000e-05, 4.000000e-05, 6.000000e-05, 8.000000e-05,
      1.000000e-04, 2.000000e-04, 4.000000e-04, 6.000000e-04, 8.000000e-04,
      1.000000e-03, 2.000000e-03, 4.000000e-03, 6.000000e-03, 8.000000e-03,
      1.000000e-02, 2.000000e-02, 4.000000e-02, 6.000000e-02, 8.000000e-02,
      1.000000e-01, 1.500000e-01, 2.000000e-01, 2.500000e-01, 3.000000e-01,
      3.500000e-01, 4.000000e-01, 4.500000e-01, 5.000000e-01, 5.500000e-01,
      6.000000e-01, 6.500000e-01, 7.000000e-01, 7.500000e-01, 8.000000e-01,
      8.500000e-01, 9.000000e-01, 9.250000e-01, 9.500000e-01, 9.750000e-01,
      1.000000e+00
    };

    // Grid in qT/Q
    const std::vector<double> qToQg
    {
      0.001,
      0.01, 0.05, 0.10, 0.15,
      0.20, 0.25, 0.30, 0.35,
      0.40, 0.45, 0.50, 0.55,
      0.60, 0.65, 0.70, 0.75,
      0.80, 0.85, 0.90, 0.95,
      1
    };

    // Get parameterisation and set parameters
    Parameterisation *NPFunc = GetParametersation(parameterisation);
    NPFunc->SetParameters(params);
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);
    out->SetFloatPrecision(8);
    out->SetDoublePrecision(8);
    (*out) << YAML::BeginMap;
    (*out) << YAML::Key << "Qg" << YAML::Value << YAML::Flow << Qg;
    (*out) << YAML::Key << "xg" << YAML::Value << YAML::Flow<< xg;
    (*out) << YAML::Key << "qToQg" << YAML::Value << YAML::Flow << qToQg;
    (*out) << YAML::Key << "TMDs" << YAML::Value << YAML::Flow;
    (*out) << YAML::BeginMap;

    // Loop over flavours
    for (int f : flv)
      {
        // Allocate 3d grid in Q, x, and qT
        std::vector<std::vector<std::vector<double>>> tmds(Qg.size(), std::vector<std::vector<double>>(xg.size(), std::vector<double>(qToQg.size())));
        for (int iQ = 0; iQ < (int) Qg.size(); iQ++)
          {
            const double Q  = Qg[iQ];
            const double Q2 = Q * Q;
            for (int ix = 0; ix < (int) xg.size(); ix++)
              {
                const double x = xg[ix];

                // bT-space TMD
                const auto xFb = [&] (double const& bT) -> double
                {
                  return QCDEvToPhys(EvTMDs(bs(bT, Q), Q, Q2).GetObjects()).at(f).Evaluate(x) * NPFunc->Evaluate(x, bT, Q2, (pf == "pdf" ? 0 : 1));
                };
                const apfel::TabulateObject<double> TabxFb{xFb, 100, 0.0001, 10, 3, bThresholds,
                                                           [] (double const& x)->double{ return log(x); },
                                                           [] (double const& x)->double{ return exp(x); }};
                const auto txFb = [&] (double const& bT) -> double{ return TabxFb.Evaluate(bT); };

                // Compute TMDs in qT space
                for (int iqT = 0; iqT < (int) qToQg.size(); iqT++)
                  tmds[iQ][ix][iqT] = DEObj.transform(txFb, qToQg[iqT] * Q);
              }
          }
        (*out) << YAML::Key << f << YAML::Value << YAML::Flow << tmds;
      }
    (*out) << YAML::EndMap;
    (*out) << YAML::EndMap;

    // Delete LHAPDF set
    delete dist;
    delete NPFunc;

    // Return the emitter
    return out;
  }
}
