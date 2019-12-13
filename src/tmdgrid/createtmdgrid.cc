//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"

#include <LHAPDF/LHAPDF.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> EmitTMDGrid(YAML::Node          const& config,
                                             std::string         const& parameterisation,
                                             std::vector<double> const& params,
                                             std::string         const& pf,
                                             TDGrid              const& tdg)
  {
    // Open LHAPDF set
    LHAPDF::PDF* dist = LHAPDF::mkPDF(config[pf + "set"]["name"].as<std::string>(), config[pf + "set"]["member"].as<int>());

    // Rotate sets into the QCD evolution basis
    const auto RotDists = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(dist->xfxQ(x, mu)); };

    // Heavy-quark thresholds and their b-space counterparts. Also
    // collects quarks and anti-quarks indices.
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
    //apfel::SetVerbosityLevel(0);

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
    const int pto = config["PerturbativeOrder"].as<int>();
    const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };
    const auto CollDists = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabDists.Evaluate(mu); };

    const auto TmdObj = apfel::InitializeTmdObjects(g, Thresholds);
    const std::function<double(double const&, double const&, double const&)> Evf = QuarkEvolutionFactor(TmdObj, Alphas, pto, Ci);
    std::function<apfel::Set<apfel::Distribution>(double const&)> Tmds;
    if (pf == "pdf")
      Tmds = MatchTmdPDFs(TmdObj, CollDists, Alphas, pto, Ci);
    else if (pf == "ff")
      Tmds = MatchTmdFFs(TmdObj, CollDists, Alphas, pto, Ci);
    else
      throw std::runtime_error("[PlotTMDs]: Unknown distribution prefix");

    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> EvTMDs;
    if (pf == "pdf")
      EvTMDs = BuildTmdPDFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
    else if (pf == "ff")
      EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
    else
      throw std::runtime_error("[PlotTMDs]: Unknown distribution prefix");

    // b* prescription
    const std::function<double(double const&, double const&)> bstar = bstarMap.at(config["bstar"].as<std::string>());

    // Double-exponential quadrature
    apfel::DoubleExponentialQuadrature DEObj{};

    // Get parameterisation and set parameters
    Parameterisation *NPFunc = GetParametersation(parameterisation);
    NPFunc->SetParameters(params);

    // Allocate map of TMDs
    std::map<int, std::vector<std::vector<std::vector<double>>>> TMDs;
    for (int f : flv)
      TMDs.insert({f, std::vector<std::vector<std::vector<double>>>(tdg.Qg.size(), std::vector<std::vector<double>>(tdg.xg.size(), std::vector<double>(tdg.qToQg.size())))});

    // Loop over flavours
    for (int iQ = 0; iQ < (int) tdg.Qg.size(); iQ++)
      {
        const double Q  = tdg.Qg[iQ];
        const double Q2 = Q * Q;

        // Tabulate TMDs
        const auto pTMDs = [&] (double const& bT) -> apfel::Set<apfel::Distribution>
        {
          const double bs = bstar(bT, Q);
          const apfel::Set<apfel::Distribution> set  = Tmds(bs);
          return apfel::Set<apfel::Distribution>{set.GetMap(), QCDEvToPhys(set.GetObjects())}
          * [&] (double const& x) -> double{ return NPFunc->Evaluate(x, bT, Q2, (pf == "pdf" ? 0 : 1)); }
          * Evf(bs, Q, Q2);
        };
        const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabpTMDs{pTMDs, 100, 0.0001, 10, 3, bThresholds,
                                                                              [] (double const& x) -> double{ return log(x); },
                                                                              [] (double const& x) -> double{ return exp(x); }};
        const auto tpTMDs = [&] (double const& bT) -> apfel::Set<apfel::Distribution> { return TabpTMDs.Evaluate(bT); };

        for (int f : flv)
          {
            for (int ix = 0; ix < (int) tdg.xg.size(); ix++)
              {
                const double x = tdg.xg[ix];

                // bT-space TMD
                const auto xFb = [&] (double const& bT) -> double { return tpTMDs(bT).at(f).Evaluate(x); };
                const apfel::TabulateObject<double> TabxFb{xFb, 100, 0.0001, 10, 3, bThresholds,
                                                           [] (double const& x) -> double{ return log(x); },
                                                           [] (double const& x) -> double{ return exp(x); }};
                const auto txFb = [&] (double const& bT) -> double{ return TabxFb.Evaluate(bT); };

                // Compute TMDs in qT space
                for (int iqT = 0; iqT < (int) tdg.qToQg.size(); iqT++)
                  TMDs[f][iQ][ix][iqT] = DEObj.transform(txFb, tdg.qToQg[iqT] * Q);
              }
          }
      }

    // Dump grids to emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);
    out->SetFloatPrecision(6);
    out->SetDoublePrecision(6);
    (*out) << YAML::BeginMap;
    (*out) << YAML::Key << "Qg"    << YAML::Value << YAML::Flow << tdg.Qg;
    (*out) << YAML::Key << "xg"    << YAML::Value << YAML::Flow << tdg.xg;
    (*out) << YAML::Key << "qToQg" << YAML::Value << YAML::Flow << tdg.qToQg;
    (*out) << YAML::Key << "TMDs"  << YAML::Value << YAML::Flow << TMDs;
    (*out) << YAML::EndMap;

    // Delete LHAPDF set and NP function
    delete dist;

    // Reset verbosity level of APFEL++ to its default
    apfel::SetVerbosityLevel(2);

    // Return the emitter
    return out;
  }

  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> EmitTMDInfo(YAML::Node  const& config,
                                             int         const& NumMembers,
                                             std::string const& pf,
                                             std::string const& SetDesc,
                                             std::string const& Authors,
                                             std::string const& Reference,
                                             std::string const& SetIndex,
                                             std::string const& Format,
                                             std::string const& DataVersion,
                                             std::string const& ErrorType)
  {
    // Allocate YAML emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);

    // Dump grids to emitter
    out->SetFloatPrecision(8);
    out->SetDoublePrecision(8);
    (*out) << YAML::BeginMap;
    (*out) << YAML::Key << "SetDesc"        << YAML::Value << SetDesc;
    (*out) << YAML::Key << "Authors"        << YAML::Value << Authors;
    (*out) << YAML::Key << "Reference"      << YAML::Value << Reference;
    (*out) << YAML::Key << "SetIndex"       << YAML::Value << SetIndex;
    (*out) << YAML::Key << "DistType"       << YAML::Value << pf;
    (*out) << YAML::Key << "CollDist"       << YAML::Value << config[pf + "set"]["name"].as<std::string>();
    (*out) << YAML::Key << "CollDistMember" << YAML::Value << config[pf + "set"]["member"].as<std::string>();
    (*out) << YAML::Key << "Format"         << YAML::Value << Format;
    (*out) << YAML::Key << "DataVersion"    << YAML::Value << DataVersion;
    (*out) << YAML::Key << "OrderQCD"       << YAML::Value << PtOrderMap.at(config["PerturbativeOrder"].as<int>());
    (*out) << YAML::Key << "Regularisation" << YAML::Value << config["bstar"].as<std::string>();
    (*out) << YAML::Key << "NumMembers"     << YAML::Value << NumMembers;
    (*out) << YAML::Key << "ErrorType"      << YAML::Value << ErrorType;
    (*out) << YAML::EndMap;

    // Return the emitter
    return out;
  }
}
