//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/bstar.h"
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
  std::vector<double> bThresholds;
  const double Ci  = config["TMDscales"]["Ci"].as<double>();
  for (auto const& v : dist->flavors())
    if (v > 0 && v < 7)
      {
        Thresholds.push_back(dist->quarkThreshold(v));
        bThresholds.push_back(Ci * 2 * exp(- apfel::emc) / dist->quarkThreshold(v));
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
  const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabDists{EvolvedDists, 100, dist->qMin()*0.9, dist->qMax(), 3, Thresholds};

  // Build evolved TMD distributions
  const int pto = config["PerturbativeOrder"].as<int>();
  const auto Alphas = [&] (double const& mu) -> double{ return dist->alphasQ(mu); };
  const auto CollDists = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabDists.Evaluate(mu); };
  std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> EvTMDs;
  if (pf == "pdf")
    EvTMDs = BuildTmdPDFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else if (pf == "ff")
    EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else if (pf == "ff2")
    EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else if (pf == "ff3")
    EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else if (pf == "ff4")
    EvTMDs = BuildTmdFFs(apfel::InitializeTmdObjects(g, Thresholds), CollDists, Alphas, pto, Ci);
  else
    throw std::runtime_error("[PlotTMDs]: Unknown distribution prefix");

  // b* prescription
  const std::function<double(double const&, double const&)> bs = NangaParbat::bstarMap.at(config["bstar"].as<std::string>());

  // Flavour index
  const int ifl = std::stoi(argv[4]);

  // Final scale
  const double Q = std::stoi(argv[5]);
  const double Q2 = Q * Q;

  // Value of x
  const double x = std::stod(argv[6]);

  // Double exponential quadrature
  // apfel::OgataQuadrature DEObj{0, 1e-10};
  apfel::DoubleExponentialQuadrature DEObj{0, 1e-10};

  // Values of qT
  const int nqT   = 100;
  const double qTmin = Q * 1e-4;
  const double qTmax = Q * 2;
  const double qTstp = exp( log( qTmax / qTmin ) / ( nqT - 1 ) );
  std::vector<double> qTv;
  for (double qT = qTmin; qT <= qTmax * ( 1 + 1e-5 ); qT *= qTstp)
    qTv.push_back(qT);
  /*
    const std::vector<double> qTv
    {
      0.00001, 0.0001, 0.001, 0.01,
      0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1,
      1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2,
      2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3,
      3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4,
      4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5,
      6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10
    };

    const std::vector<double> qTv
    {
      0.0001*Q, 0.0010*Q, 0.0025*Q, 0.0050*Q, 0.0075*Q, 0.0100*Q, 0.0200*Q, 0.0300*Q, 0.0400*Q,
      0.0500*Q, 0.0600*Q, 0.0700*Q, 0.0800*Q, 0.0900*Q, 0.1000*Q, 0.1250*Q, 0.1500*Q, 0.1750*Q,
      0.2000*Q, 0.2250*Q, 0.2500*Q, 0.2750*Q, 0.3000*Q, 0.3500*Q, 0.4000*Q, 0.4500*Q, 0.5000*Q,
      0.5500*Q, 0.6000*Q, 0.6500*Q, 0.7000*Q, 0.8000*Q, 0.9000*Q, 1*Q
    };

  */

  // Read file of parameters
  const YAML::Node parfile = YAML::LoadFile(argv[7]);

  // Get parameterisation and sets of parameters
  NangaParbat::Parameterisation *NPFunc = NangaParbat::GetParametersation(parfile["Parameterisation"].as<std::string>());
  const std::vector<std::vector<double>> pars = parfile["Parameters"].as<std::vector<std::vector<double>>>();

  const double bTmin = 0.000005;
  const double bTmax = 1000;

  apfel::Timer t;
  // Loop over sets of parameters
  std::vector<std::vector<double>> tmds(pars.size(), std::vector<double>(qTv.size()));
  for (int ip = 0; ip < (int) pars.size(); ip++)
    {
      // Set vector of parameters
      NPFunc->SetParameters(pars[ip]);

      // bT-space TMD
      const auto xFb = [&] (double const& bT) -> double { return bT * QCDEvToPhys(EvTMDs(bs(bT, Q), Q, Q2).GetObjects()).at(ifl).Evaluate(x) * NPFunc->Evaluate(x, bT, Q2, (pf == "pdf" ? 0 : 1)); };
      const apfel::TabulateObject<double> TabxFb{xFb, 300, bTmin, bTmax, 3, bThresholds, [] (double const& x)->double{ return log(x); }, [] (double const& x)->double{ return exp(x); }};
      const std::function<double(double const&)> txFb = [&] (double const& bT) -> double{ return TabxFb.Evaluate(bT); };

      const std::function<double(double const&)> fnp = [&] (double const& bT) -> double { return bT * NPFunc->Evaluate(x, bT, Q2, (pf == "pdf" ? 0 : 1));};

      // const std::function<double(double const&)> fpert = [&] (double const& bT) -> double { return QCDEvToPhys(EvTMDs(bs(bT, Q), Q, Q2).GetObjects()).at(ifl).Evaluate(x);};
      //
      // std::cout << " " << fpert(1.0) << std::endl;

      // Compute TMDs in qT space
      for (int iqT = 0; iqT < (int) qTv.size(); iqT++)
        {
          // tmds[ip][iqT] = DEObj.transform(txFb, qTv[iqT], 200);
          tmds[ip][iqT] = DEObj.transform(txFb, qTv[iqT]);
          // tmds[ip][iqT] = DEObj.transform(fnp, qTv[iqT]);
          // std::cout << qTv[iqT] << " " << DEObj.transform(fnp, qTv[iqT]) << std::endl;
        }
    }
  t.stop();

  // YAML::Emitter where predictions will be dumped
  YAML::Emitter out;
  out.SetFloatPrecision(8);
  out.SetDoublePrecision(8);
  out << YAML::BeginMap;
  out << YAML::Key << "Flavour index" << YAML::Value << ifl;
  out << YAML::Key << "Scale" << YAML::Value << Q;
  out << YAML::Key << "Bjorken x" << YAML::Value << x;
  out << YAML::Key << "bTmin" << YAML::Value << bTmin;
  out << YAML::Key << "bTmax" << YAML::Value << bTmax;
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
