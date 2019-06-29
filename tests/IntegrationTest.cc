//
// APFEL++ 2017
//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/utilities.h"
#include "NangaParbat/twobodyphasespace.h"

#include <LHAPDF/LHAPDF.h>
#include <apfel/apfelxx.h>

// Non-perturnative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double g1 = 0.02;
  const double g2 = 0.5;
  const double Q0 = 1.6;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

// Main program
int main()
{
  // Allocate "FastInterface" object
  const YAML::Node config = YAML::LoadFile("../cards/config.yaml");
  const NangaParbat::FastInterface FIObj{config};

  // Vector of datafiles
  const std::vector<NangaParbat::DataHandler> DHVect{NangaParbat::DataHandler{"Test_data", YAML::LoadFile("../data/TestData/Table5.yaml")}};
  //const std::vector<NangaParbat::DataHandler> DHVect{NangaParbat::DataHandler{"Test_data", YAML::LoadFile("../data/CDF_RunI/CDF_RunI.yaml")}};

  // Compute interpolation table(s)
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect, NangaParbat::bstar);

  // Write tables to file
  for (auto const& tab : Tabs)
    {
      std::ofstream fout("../tables/" + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();
    }

  // Now start direct computation
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
  const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x,mu)); };

  // Construct set of distributions as a function of the scale to be
  // tabulated
  const auto EvolvedPDFs = [=,&g] (double const& mu) -> apfel::Set<apfel::Distribution>
  {
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
  const double eps = 1e-4;
  const double Cf  = config["TMDscales"]["Cf"].as<double>();

  // Loop over the vector of "Kinematics" objects
  for (int i = 0; i < (int) DHVect.size(); i++)
    {
      // Load convolution table and do the convolution
      const NangaParbat::ConvolutionTable CTable{YAML::Load(Tabs[i].c_str())};
      //const NangaParbat::ConvolutionTable CTable{YAML::LoadFile("../tables/TestData3.yaml")};
      const std::vector<double> Conv = CTable.GetPredictions(fNP);

      // Retrieve kinematics
      const NangaParbat::DataHandler::Kinematics kin = DHVect[i].GetKinematics();
      const double                   Vs       = kin.Vs;       // C.M.E.
      const std::pair<double,double> yb       = kin.var2b;    // Rapidity interval
      const std::pair<double,double> Qb       = kin.var1b;    // Invariant mass interval
      const std::vector<double>      qTv      = kin.qTv;      // Transverse momentum bin bounds
      const double                   pTMin    = kin.pTMin;    // Minimum pT of the final-state leptons
      const std::pair<double,double> etaRange = kin.etaRange; // Allowed range in eta of the final-state leptons

      // Ogata-quadrature object of degree zero
      apfel::OgataQuadrature OgataObj{};

      // Phase-space reduction factor
      NangaParbat::TwoBodyPhaseSpace ps{pTMin, etaRange.first, etaRange.second};

      // Loop over the qT-bin bounds
      const auto qTintegrand = [&] (double const& qT) -> double
                               //for (auto const& qT : qTv)
      {
        // Construct the TMD luminosity in b scale to be fed to be
        // trasformed in qT space.
        const auto TMDLumib = [&] (double const& b) -> double
        {
          // Tabulate TMDs in Q
          const auto EvolvedTMDPDFs = [&] (double const& Q) -> apfel::Set<apfel::Distribution>{ return EvTMDPDFs(NangaParbat::bstar(b, Q), Cf * Q, Q * Q); };
          const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabEvolvedTMDPDFs{EvolvedTMDPDFs, 50, Qb.first, Qb.second, 3, {}};

          // Function to be integrated in Q
          const auto Qintegrand = [&] (double const& Q) -> double
          {
            // Renormalisation scales
            const double muf   = Cf * Q;
            const double zetaf = Q * Q;

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

              // Combine TMDs through the EW charges
              double lumi = 0;
              for (int i = 1; i <= nf; i++)
                lumi += Bq[i-1] * ( xF.at(i).Evaluate(x1) * xF.at(-i).Evaluate(x2) + xF.at(-i).Evaluate(x1) * xF.at(i).Evaluate(x2) ) / 2;

              // Return xi integrand
              return ps.PhaseSpaceReduction(Q, log(xi), qT) * lumi * fNP(x1, b, zetaf) * fNP(x2, b, zetaf) / xi;
            };

            // Perform the integral in xi
            const apfel::Integrator xiIntObj{xiintegrand};
            const double xiintegral = xiIntObj.integrate(exp(yb.first), exp(yb.second), eps);

            // Electromagnetic coupling squared
            const double aem2 = pow((config["alphaem"]["run"].as<bool>() ? alphaem.Evaluate(Q) : config["alphaem"]["ref"].as<double>()), 2);

            // Compute the hard factor
            const double hcs = apfel::HardFactorDY(config["PerturbativeOrder"].as<int>(), Alphas(muf), nf, Cf);

            // Return Q integrand
            return aem2 * hcs * xiintegral / pow(Q, 3);
          };

          // Perform the integral in Q
          const apfel::Integrator QIntObj{Qintegrand};
          double Qintegral = b * apfel::ConvFact * qT * 8 * M_PI * QIntObj.integrate(Qb.first, Qb.second, eps) / 9;
          return Qintegral;
        };
        const double direct = OgataObj.transform(TMDLumib, qT);
        return direct;
      };

      // Timer
      apfel::Timer t;
      const apfel::Integrator qTIntObj{qTintegrand};
      std::cout << std::scientific;
      for (int iqT = 0; iqT < (int) qTv.size() - 1; iqT++)
        //std::cout << "[" << qTv[iqT] << ":" << qTv[iqT+1] << "]: "
        std::cout << qTv[iqT] << "\t" << qTv[iqT+1] << "\t" << ( qTv[iqT] + qTv[iqT+1] ) / 2 << "\t"
                  << DHVect[i].GetMeanValues()[iqT] << "\t"
                  << DHVect[i].GetUncorrelatedUnc()[iqT] << "\t"
                  //<< qTIntObj.integrate(qTv[iqT], qTv[iqT+1], eps) / ( qTv[iqT+1] - qTv[iqT] ) << "  "
                  << Conv[iqT] / ( qTv[iqT] + qTv[iqT+1] ) * 2 / 6.8 << "  "
                  //<< Conv[iqT] / qTv[iqT] / 6.8 << "  "
                  << std::endl;
      std::cout << "\n";
      t.stop();
    }
  delete distpdf;
  return 0;
}
