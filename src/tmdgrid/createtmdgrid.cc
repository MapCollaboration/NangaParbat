//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/listdir.h"
#include "NangaParbat/direxists.h"
#include "NangaParbat/numtostring.h"

#include <LHAPDF/LHAPDF.h>
#include <fstream>

namespace NangaParbat
{
  //_________________________________________________________________________________
  void ProduceTMDGrid(std::string const& ReportFolder, std::string const& Output)
  {
    // Check if output folder already exists
    if (dir_exists(Output))
      throw std::runtime_error("[ProduceTMDGrid]: output folder already exists.");

    // Distribution type
    const std::string pf = "pdf";

    // Read configuration file
    const YAML::Node config = YAML::LoadFile(ReportFolder + "/tables/config.yaml");

    // Read fir configuration file
    const YAML::Node fitconfig = YAML::LoadFile(ReportFolder + "/fitconfig.yaml");

    // Collect reports of valid replicas
    std::vector<std::unique_ptr<YAML::Emitter>> grids;
    for (auto const f : list_dir(ReportFolder))
      {
        const std::string repfile = ReportFolder + "/" + f + "/Report.yaml";

        // Check if the report exists
        std::fstream fs(repfile);
        if (!fs.fail())
          {
            // Read the report
            const YAML::Node rep = YAML::LoadFile(repfile);

            // Skip mean_replica if present
            if (f == "mean_replica")
              continue;

            // If the fit converged push it back
            if (rep["Status"].as<int>() == 1)
              {
                std::cout << "Computing grid for " << repfile << " ..." << std::endl;
                // Get parameterisation
                const std::string pms = rep["Parameterisation"].as<std::string>();
                NangaParbat::Parameterisation *NPFunc = NangaParbat::GetParametersation(pms);

                // Get parameters
                const std::map<std::string, double> pars = rep["Parameters"].as<std::map<std::string, double>>();

                // Collect parameters in vector
                std::vector<double> vpars;
                for (auto const p : NPFunc->GetParameterNames())
                  vpars.push_back(pars.at(p));

                // Compute grid and push it back. In the case of
                // replica_0 push it in the front to make sure it's
                // the first replica.
                if (f == "replica_0")
                  grids.insert(grids.begin(), EmitTMDGrid(config, pms, vpars, pf));
                else
                  grids.push_back(EmitTMDGrid(config, pms, vpars, pf));

                // Delete Parameterisation object
                delete NPFunc;
              }
          }
      }

    // Create output directory
    mkdir(Output.c_str(), ACCESSPERMS);

    // Write info file
    std::ofstream iout(Output + "/" + Output + ".info");
    iout << NangaParbat::EmitTMDInfo(config, grids.size(), pf)->c_str() << std::endl;
    iout.close();

    // Dump grids to file
    for (int i = 0; i < (int) grids.size(); i++)
      {
        std::ofstream fpout(Output + "/" + Output + "_" + num_to_string(i) + ".yaml");
        fpout << grids[i]->c_str() << std::endl;
        fpout.close();
      }
  }

  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> EmitTMDGrid(YAML::Node          const& config,
                                             std::string         const& parameterisation,
                                             std::vector<double> const& params,
                                             std::string         const& pf,
                                             ThreeDGrid          const& tdg)
  {
    // Timer
    apfel::Timer t;

    // Open LHAPDF set
    LHAPDF::PDF* dist = LHAPDF::mkPDF(config[pf + "set"]["name"].as<std::string>(), config[pf + "set"]["member"].as<int>());

    // Rotate set into the QCD evolution basis
    const auto RotDists = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(dist->xfxQ(x, mu)); };

    // Heavy-quark thresholds and their b-space counterparts. Also
    // collect quarks and anti-quarks indices.
    std::vector<double> Thresholds;
    std::vector<int> flv;
    for (int f : dist->flavors())
      if (f > 0 && f < 7)
        {
          Thresholds.push_back(dist->quarkThreshold(f));
          flv.push_back(f);
          flv.insert(flv.begin(), -f);
        }

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
    const auto CollDists = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabDists.Evaluate(mu); };

    // Strong coupling
    const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };

    // Get TMDs distributions
    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> Tmds;
    if (pf == "pdf")
      Tmds = BuildTmdPDFs(apfel::InitializeTmdObjectsLite(g, Thresholds), CollDists, Alphas,
                          config["PerturbativeOrder"].as<int>(), config["TMDscales"]["Ci"].as<double>());
    else if (pf == "ff")
      Tmds = BuildTmdFFs(apfel::InitializeTmdObjectsLite(g, Thresholds), CollDists, Alphas,
                         config["PerturbativeOrder"].as<int>(), config["TMDscales"]["Ci"].as<double>());
    else
      throw std::runtime_error("[EmitTMDGrid]: Unknown distribution prefix.");

    // Get b* prescription
    const std::function<double(double const&, double const&)> bstar = bstarMap.at(config["bstar"].as<std::string>());
    //const std::function<double(double const&, double const&)> bstar = bstarMap.at("bstarCSS");

    // Allocate parameterisation object and set parameters
    Parameterisation *NPFunc = GetParametersation(parameterisation);
    NPFunc->SetParameters(params);

    // Double-exponential quadrature object for the Hankel transform
    const apfel::DoubleExponentialQuadrature DEObj{};

    // Convolution map to be used for all sets of distributions to
    // avoid problems with the heavy quark thresholds.
    const apfel::EvolutionBasisQCD cevb{6};

    // Allocate map of TMDs on the three dimensional grid
    std::map<int, std::vector<std::vector<std::vector<double>>>> TMDs;
    for (int f : flv)
      TMDs.insert({f, std::vector<std::vector<std::vector<double>>>(tdg.Qg.size(),
                                                                    std::vector<std::vector<double>>(tdg.xg.size(),
                                                                                                     std::vector<double>(tdg.qToQg.size())))});
    for (int iQ = 0; iQ < (int) tdg.Qg.size(); iQ++)
      {
        // Integrand
        const std::function<apfel::Set<apfel::Distribution>(double const&)> bTintegrand = [=] (double const& b) -> apfel::Set<apfel::Distribution>
        {
          const double Q  = tdg.Qg[iQ];
          const double Q2 = Q * Q;
          const double bs = bstar(b, Q);
          apfel::Set<apfel::Distribution> tdist = Tmds(bs, Q, Q2);
          tdist.SetMap(cevb);
          return [&] (double const& x) -> double{ return NPFunc->Evaluate(x, b, Q2, (pf == "pdf" ? 0 : 1)); } * tdist;
        };
        for (int iqT = 0; iqT < (int) tdg.qToQg.size(); iqT++)
          {
            // Transform into qT space
            const std::map<int, apfel::Distribution> DqT = apfel::QCDEvToPhys(DEObj.transform(bTintegrand, tdg.Qg[iQ] * tdg.qToQg[iqT]).GetObjects());
            for (int f : flv)
              {
                const apfel::Distribution Df = DqT.at(f);
                for (int ix = 0; ix < (int) tdg.xg.size(); ix++)
                  TMDs[f][iQ][ix][iqT] = Df.Evaluate(tdg.xg[ix]);
              }
          }
        // Report computation status
        const double perc = 100. * ( iQ + 1 ) / tdg.Qg.size();
        std::cout << "Status report for the TMD grid computation: "<< std::setw(6) << std::setprecision(4) << perc << "\% completed...\r";
        std::cout.flush();
      }
    std::cout << "\n";

    // Dump grids to emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);
    out->SetFloatPrecision(6);
    out->SetDoublePrecision(6);
    *out << YAML::BeginMap;
    *out << YAML::Key << "Qg"    << YAML::Value << YAML::Flow << tdg.Qg;
    *out << YAML::Key << "xg"    << YAML::Value << YAML::Flow << tdg.xg;
    *out << YAML::Key << "qToQg" << YAML::Value << YAML::Flow << tdg.qToQg;
    *out << YAML::Key << "TMDs"  << YAML::Value << YAML::Flow << TMDs;
    *out << YAML::EndMap;

    // Delete LHAPDF set and NP function
    delete dist;

    // Stop timer
    t.stop();

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
