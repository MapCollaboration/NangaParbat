//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/utilities.h"
#include "NangaParbat/nonpertfunctions.h"

#include <fstream>
#include <cstring>
#include <algorithm>
#include <apfel/apfelxx.h>
#include <LHAPDF/LHAPDF.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 8 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./PlotTMDs <configuration file> <output file> <pdf/ff> <flavour ID> <Scale in GeV> <value of x> <parameters file>\n" << std::endl;
      exit(-10);
    }

  // Read configuration file
  const YAML::Node config = YAML::LoadFile(argv[1]);

  // Output file
  const std::string output = std::string(argv[2]);

  // Distribution prefix
  const std::string pf = argv[3];

  // Open LHAPDF set
  LHAPDF::PDF* dist = LHAPDF::mkPDF(config[pf + "set"]["name"].as<std::string>(), config[pf + "set"]["member"].as<int>());

  // Rotate sets into the QCD evolution basis
  const auto RotDists = [&] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(dist->xfxQ(x, mu)); };

  // Heavy-quark thresholds
  std::vector<double> Thresholds;
  for (auto const& v : dist->flavors())
    if (v > 0 && v < 7)
      Thresholds.push_back(dist->quarkThreshold(v));

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
  const int    pto = config["PerturbativeOrder"].as<int>();
  const double Ci  = config["TMDscales"]["Ci"].as<double>();
  const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };
  const auto CollDists = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabDists.Evaluate(mu); };

  std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> EvTMDs;
  if (pf == "pdf")
    EvTMDs = BuildTmdPDFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else if (pf == "ff")
    EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else
    throw std::runtime_error("[PlotTMDs]: Unknown distribution prefix");

  // Flavour index
  const int ifl = std::stoi(argv[4]);

  // Final scale
  const double Q = std::stoi(argv[5]);
  const double Q2 = Q * Q;

  // Value of x
  const double x = std::stod(argv[6]);

  // Double exponential quadrature
  apfel::DoubleExponentialQuadrature DEObj{};

  // Values of qT
  const std::vector<double> qTv
  {
    0.001, 0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9,
    1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5,
    6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5,
    11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5,
    16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20
  };

  // Read file of parameters
  const YAML::Node parfile = YAML::LoadFile(argv[7]);

  // Get parameterisation and sets of parameters
  NangaParbat::Parameterisation *NPFunc = NangaParbat::GetParametersation(parfile["Parameterisation"].as<std::string>());
  const std::vector<std::vector<double>> pars = parfile["Parameters"].as<std::vector<std::vector<double>>>();

  // Loop over sets of parameters
  std::vector<std::vector<double>> tmds(pars.size(), std::vector<double>(qTv.size()));
  for (int ip = 0; ip < (int) pars.size(); ip++)
    {
      // Set vector of parameters
      NPFunc->SetParameters(pars[ip]);

      // bT-space TMD
      const auto xFb = [=] (double const& bT) -> double
      {
        return QCDEvToPhys(EvTMDs(NangaParbat::bstarmin(bT, Q), Q, Q2).GetObjects()).at(ifl).Evaluate(x) * NPFunc->Evaluate(x, bT, Q2, (pf == "pdf" ? 0 : 1));
      };

      // Tabulate integrand
      const apfel::TabulateObject<double> TabxFb{xFb, 300, 0.0001, 10, 3, {}, [] (double const& x)->double{ return log(x); }, [] (double const& x)->double{ return exp(x); }};
      const auto txFb = [=] (double const& bT) -> double{ return TabxFb.Evaluate(bT); };

      // Compute TMDs in kT space
      for (int iqT = 0; iqT < (int) qTv.size(); iqT++)
        tmds[ip][iqT] = DEObj.transform(txFb, qTv[iqT]);
    }

  // YAML::Emitter where predictions will be dumped
  YAML::Emitter out;
  out.SetFloatPrecision(8);
  out.SetDoublePrecision(8);
  out << YAML::BeginMap;
  out << YAML::Key << "Flavour index" << YAML::Value << ifl;
  out << YAML::Key << "Scale" << YAML::Value << Q;
  out << YAML::Key << "Bjorken x" << YAML::Value << x;
  out << YAML::Key << "qT" << YAML::Value << YAML::Flow << qTv;
  out << YAML::Key << "TMD" << YAML::Value << YAML::Flow << tmds;
  out << YAML::EndMap;

  // Dump result to file
  std::ofstream fout(output);
  fout << out.c_str() << std::endl;
  fout.close();

  // Delete LHAPDF set
  delete dist;

  return 0;
}
