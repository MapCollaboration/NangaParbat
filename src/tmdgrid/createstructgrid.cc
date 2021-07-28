//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#include "NangaParbat/createstructgrid.h"
#include "NangaParbat/bstar.h"
#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/tmdgrid.h"
#include "NangaParbat/factories.h"
#include "NangaParbat/listdir.h"
#include "NangaParbat/direxists.h"
#include "NangaParbat/numtostring.h"

#include <LHAPDF/LHAPDF.h>
#include <iomanip>
#include <fstream>
#include <sys/stat.h>

namespace NangaParbat
{
  //____________________________________________________________________________________________________
  void ProduceStructGrid(std::string const& GridsDirectory,
                         std::string const& GridTMDPDFfolder,
                         std::string const& GridTMDFFfolder,
                         std::string const& Output,
                         std::string const& repID,
                         std::string const& structype)
  {
    // Distribution type
    const std::string pf = structype;

    // Read configuration file
    const YAML::Node config = YAML::LoadFile(GridsDirectory + "/tables/config.yaml");

    // Define vector for grid names
    std::vector<std::string> fnames;

    // Collect TMD grids to compute the structure function
    std::vector<std::unique_ptr<YAML::Emitter>> grids;

    // If the replica number (replica ID) is not specified, produce one structure function grid
    // for every TMD PDF grid present in the TMDPDF folder. TMD PDF and TMD FF are matched by replica ID.
    if (repID == "none")
      {
        for (auto const& f : list_dir(GridsDirectory + "/" + GridTMDPDFfolder))
          {
            // TMDPDF grid file
            const std::string gridfile = GridsDirectory + "/" + GridTMDPDFfolder + "/" + f;

            // Check if the TMDPDF grid file exists
            std::fstream fs(gridfile);

            if (!fs.fail())
              {
                if (f.substr(f.size() - 5, 5) == ".yaml")
                  {
                    // Get replica number from the name of the PDF Grids
                    const std::string repnum = f.substr(f.size() - 9, 4);

                    std::cout << "Computing grid for structure function with replica " << repnum << " ..." << std::endl;

                    // Compute grid and push it back. In the case of
                    // replica_0 push it in the front to make sure it's
                    // the first replica.
                    if (repnum == "0000")
                      {
                        grids.insert(grids.begin(), EmitStructGrid(GridsDirectory, GridTMDPDFfolder, GridTMDFFfolder, std::stoi(repnum), pf, Inter4DGrid(pf)));
                        fnames.insert(fnames.begin(), repnum);
                      }
                    else
                      {
                        grids.push_back(EmitStructGrid(GridsDirectory, GridTMDPDFfolder, GridTMDFFfolder, std::stoi(repnum), pf, Inter4DGrid(pf)));
                        fnames.push_back(repnum);
                      }
                  }
              }
          }
      }

    // If the replica ID is specified, do only the grid for that replica.
    else
      {
        std::cout << "Computing grid for structure function with replica " << repID << " ..." << std::endl;

        grids.push_back(EmitStructGrid(GridsDirectory, GridTMDPDFfolder, GridTMDFFfolder, std::stoi(repID), pf, Inter4DGrid(pf)));
        fnames.push_back(repID);
      }

    // Output directory
    const std::string outdir = GridsDirectory + "/" + Output;

    // Create output directory if it does not exist
    if (!dir_exists(Output))
      mkdir(outdir.c_str(), ACCESSPERMS);

    // Write info file
    std::ofstream iout(outdir + "/" + Output + ".info");
    iout << NangaParbat::EmitStructInfo(GridsDirectory, GridTMDPDFfolder, GridTMDFFfolder, config, grids.size(), pf, Inter4DGrid(pf))->c_str() << std::endl;
    iout.close();

    // Dump grids to file
    for (int i = 0; i < (int) grids.size(); i++)
      {
        // Grids numbered sequentially
        // std::ofstream fpout(outdir + "/" + Output + "_" + num_to_string(i) + ".yaml");

        // Grid number = replica number
        std::ofstream fpout(outdir + "/" + Output + "_" + num_to_string(std::stoi(fnames[i])) + ".yaml");
        fpout << grids[i]->c_str() << std::endl;
        fpout.close();
      }

  }

  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> EmitStructGrid(std::string const& GridsDirectory,
                                                std::string const& GridTMDPDFfolder,
                                                std::string const& GridTMDFFfolder,
                                                int         const& repnumber,
                                                std::string const& pf,
                                                FourDGrid   const& fdg,
                                                int         const& qToQcut)
  {
    // Timer
    apfel::Timer t;

    // Get TMDs distributions from grids
    std::cout << "Read TMD grids " << std::endl;
    NangaParbat::TMDGrid* TMDPDFs = NangaParbat::mkTMD(GridTMDPDFfolder, GridsDirectory, repnumber);
    NangaParbat::TMDGrid* TMDFFs  = NangaParbat::mkTMD(GridTMDFFfolder, GridsDirectory, repnumber);

    // Allocate structure function on the four dimensional grid
    std::vector<std::vector<std::vector<std::vector<double>>>> SFs(fdg.Qg.size(),
                                                                   std::vector<std::vector<std::vector<double>>>(fdg.xg.size(),
                                                                                                                 std::vector<std::vector<double>>(fdg.zg.size(),
                                                                                                                     std::vector<double>(fdg.qToQg.size()))));

    // Compute structure function to put in grids, fully differential calculation.
    // At the moment the only SF implemented is FUUT.
    for (int iQ = 0; iQ < (int) fdg.Qg.size(); iQ++)
      {
        for (int ix = 0; ix < (int) fdg.xg.size(); ix++)
          {
            for (int iz = 0; iz < (int) fdg.zg.size(); iz++)
              {
                for (int iqT = 0; iqT < (int) fdg.qToQg.size(); iqT++)
                  {
                    const auto conv = Convolution(TMDPDFs, TMDFFs, [] (double const&) -> std::vector<double> { return apfel::QCh2;}, qToQcut);
                    SFs[iQ][ix][iz][iqT] = conv(fdg.xg[ix], fdg.zg[iz], fdg.Qg[iQ], fdg.Qg[iQ] * fdg.qToQg[iqT]) / fdg.zg[iz] / (2 * M_PI);
                  }
              }
          }

        // Report computation status
        const double perc = 100. * ( iQ + 1 ) / fdg.Qg.size();
        std::cout << "Status report for the structure function grid computation: "<< std::setw(6) << std::setprecision(4) << perc << "\% completed...\r";
        std::cout.flush();
      }

    std::cout << "\n";

    // Dump grids to emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);
    out->SetFloatPrecision(6);
    out->SetDoublePrecision(6);
    *out << YAML::BeginMap;
    *out << YAML::Key << "Qg"    << YAML::Value << YAML::Flow << fdg.Qg;
    *out << YAML::Key << "xg"    << YAML::Value << YAML::Flow << fdg.xg;
    *out << YAML::Key << "zg"    << YAML::Value << YAML::Flow << fdg.zg;
    *out << YAML::Key << "qToQg" << YAML::Value << YAML::Flow << fdg.qToQg;
    *out << YAML::Key << "StructureFunction"  << YAML::Value << YAML::Flow << SFs;
    *out << YAML::EndMap;

    // Delete TMD objects
    delete TMDPDFs;
    delete TMDFFs;

    // Stop timer
    t.stop();

    // Return the emitter
    return out;
  }

  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> EmitStructGridDirect(std::string const& FitDirectory,
                                                      int         const& repnumber,
                                                      std::string const& pf,
                                                      FourDGrid   const& fdg,
                                                      int         const& qToQcut)
  {
    // Timer
    apfel::Timer t;

    // Read configuration file
    const YAML::Node config = YAML::LoadFile(FitDirectory + "/tables/config.yaml");

    // Perturbative order
    const int PerturbativeOrder = config["PerturbativeOrder"].as<int>();

    // Scale-variation factors
    const double Ci = config["TMDscales"]["Ci"].as<double>();
    const double Cf = config["TMDscales"]["Cf"].as<double>();

    // Open LHAPDF sets
    LHAPDF::PDF* distpdf = LHAPDF::mkPDF(config["pdfset"]["name"].as<std::string>(), config["pdfset"]["member"].as<int>());
    LHAPDF::PDF* distff  = LHAPDF::mkPDF(config["ffset"]["name"].as<std::string>(),  config["ffset"]["member"].as<int>());

    // Get heavy-quark thresholds from the PDF LHAPDF set
    std::vector<double> ThresholdsPDF;
    for (auto const& v : distpdf->flavors())
      if (v > 0 && v < 7)
        ThresholdsPDF.push_back(distpdf->quarkThreshold(v));

    // Get heavy-quark thresholds from the FF LHAPDF set
    std::vector<double> ThresholdsFF;
    for (auto const& v : distff->flavors())
      if (v > 0 && v < 7)
        ThresholdsFF.push_back(distff->quarkThreshold(v));

    // Alpha_s (from PDFs and FFs)
    const auto AlphasPDF = [&] (double const& mu) -> double{ return distpdf->alphasQ(mu); };
    const auto AlphasFF  = [&] (double const& mu) -> double{ return distff->alphasQ(mu); };

    // Setup APFEL++ x-space grid for PDFs
    std::vector<apfel::SubGrid> vsgp;
    for (auto const& sg : config["xgridpdf"])
      vsgp.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    const apfel::Grid gpdf{vsgp};

    // Setup APFEL++ x-space grid for FFs
    std::vector<apfel::SubGrid> vsgf;
    for (auto const& sg : config["xgridff"])
      vsgf.push_back({sg[0].as<int>(), sg[1].as<double>(), sg[2].as<int>()});
    const apfel::Grid gff{vsgf};

    // Rotate PDF set into the QCD evolution basis
    const auto RotPDFs = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distpdf->xfxQ(x, mu)); };
    const auto RotFFs  = [=] (double const& x, double const& mu) -> std::map<int,double> { return apfel::PhysToQCDEv(distff->xfxQ(x, mu)); };

    // Construct set of distributions as a function of the scale to be
    // tabulated
    const auto EvolvedPDFs = [=,&gpdf] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, ThresholdsPDF)}, DistributionMap(gpdf, RotPDFs, mu)};
    };
    const auto EvolvedFFs = [=,&gff] (double const& mu) -> apfel::Set<apfel::Distribution>
    {
      return apfel::Set<apfel::Distribution>{apfel::EvolutionBasisQCD{apfel::NF(mu, ThresholdsPDF)}, DistributionMap(gff, RotFFs, mu)};
    };

    // Tabulate collinear PDFs and FFs
    const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabPDFs{EvolvedPDFs, 100, 0.5, distpdf->qMax(), 3, ThresholdsPDF};
    const auto CollPDFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabPDFs.Evaluate(mu); };

    const apfel::TabulateObject<apfel::Set<apfel::Distribution>> TabFFs{EvolvedFFs, 100, 0.5, distff->qMax(), 3, ThresholdsPDF};
    const auto CollFFs = [&] (double const& mu) -> apfel::Set<apfel::Distribution> { return TabFFs.Evaluate(mu); };

    // Initialize TMD objects
    const auto TmdObjPDF = apfel::InitializeTmdObjects(gpdf, ThresholdsPDF);
    const auto TmdObjFF  = apfel::InitializeTmdObjects(gff,  ThresholdsPDF);

    // Build evolved TMD PDFs and FFs
    const auto EvTMDPDFs = BuildTmdPDFs(TmdObjPDF, CollPDFs, AlphasPDF, PerturbativeOrder, Ci);
    const auto EvTMDFFs  = BuildTmdFFs(TmdObjFF, CollFFs, AlphasFF, PerturbativeOrder, Ci);

    // Functions used for the tabulation
    const auto TabFunc    = [] (double const& b) -> double{ return log(b); };
    const auto InvTabFunc = [] (double const& fb) -> double{ return exp(fb); };

    // Get report
    const YAML::Node rep = YAML::LoadFile(FitDirectory + "/replica_" + std::to_string(repnumber) + "/Report.yaml");

    // Get parameterisation
    NangaParbat::Parameterisation* fNP = NangaParbat::GetParametersation(rep["Parameterisation"].as<std::string>());

    // Double-exponential quadrature object for the Hankel transform
    // const apfel::DoubleExponentialQuadrature DEObj{};
    const apfel::OgataQuadrature DEObj{0, 1e-9, 0.00001};

    // Convolution map to be used for all sets of distributions to
    // avoid problems with the heavy quark thresholds.
    const apfel::EvolutionBasisQCD cevb{6};

    // Allocate structure function on the four dimensional grid
    std::vector<std::vector<std::vector<std::vector<double>>>> SFs(fdg.Qg.size(),
                                                                   std::vector<std::vector<std::vector<double>>>(fdg.xg.size(),
                                                                                                                 std::vector<std::vector<double>>(fdg.zg.size(),
                                                                                                                     std::vector<double>(fdg.qToQg.size()))));

    // Compute structure function to put in grids, fully differential calculation.
    // At the moment the only SF implemented is FUUT.
    for (int iQ = 0; iQ < (int) fdg.Qg.size(); iQ++)
      {
        const double Q  = fdg.Qg[iQ];

        // Renormalisation and rapidity scales
        const double mu   = Cf * Q;
        const double zeta = Q * Q;

        // EW charges
        const std::vector<double> Bq = apfel::QCh2;

        // Number of active flavours at mu
        const int nf = apfel::NF(mu, ThresholdsPDF);

        // Define kT-distribution function for direct calculation
        const std::function<apfel::DoubleObject<apfel::Distribution>(double const&)> Lumib = [=] (double const& bs) -> apfel::DoubleObject<apfel::Distribution>
        {
          // Get Evolved TMD PDFs and FFs and rotate them into the physical basis.
          const std::map<int, apfel::Distribution> xF = QCDEvToPhys(EvTMDPDFs(bs, mu, zeta).GetObjects());
          const std::map<int, apfel::Distribution> xD = QCDEvToPhys(EvTMDFFs(bs, mu, zeta).GetObjects());

          // Luminosity
          apfel::DoubleObject<apfel::Distribution> L{};
          for (int i = 1; i <= nf; i++)
            {
              L.AddTerm({Bq[i-1], xF.at(+i), xD.at(+i)});
              L.AddTerm({Bq[i-1], xF.at(-i), xD.at(-i)});
            }
          return L;
        };

        // Perturbative contribution in b-space. We know a priori that
        // this is enclosed bewteen bmin and bmax. Include an overflow
        // (and underflow) by a 20% to avoid interpolation problems.
        const double overflow = 1.2;
        const double bmin = NangaParbat::bstarmin(0.00001, Q) / overflow;
        const double bmax = NangaParbat::bstarmin(10, Q) * overflow;

        const apfel::TabulateObject<apfel::DoubleObject<apfel::Distribution>> tLumib{Lumib, 200, bmin, bmax, 3, {}, TabFunc, InvTabFunc};

        for (int ix = 0; ix < (int) fdg.xg.size(); ix++)
          {
            const double x  = fdg.xg[ix];

            for (int iz = 0; iz < (int) fdg.zg.size(); iz++)
              {
                const double z  = fdg.zg[iz];

                // Function in bT space
                const std::function<double(double const&)> bInt = [=] (double const& b) -> double
                {
                  double bTintegrand = b * fNP->Evaluate(x, b, zeta, 0) * fNP->Evaluate(z, b, zeta, 1) / z / z * tLumib.EvaluatexzQ(x, z, NangaParbat::bstarmin(b, Q));
                  return bTintegrand;
                };

                // Transform in qT space and fill grid
                for (int iqT = 0; iqT < (int) fdg.qToQg.size(); iqT++)
                  {
                    const double qT  = Q * fdg.qToQg[iqT];
                    SFs[iQ][ix][iz][iqT] = DEObj.transform(bInt, qT)/ z / (2 * M_PI);
                  }
              }
          }

        // Report computation status
        const double perc = 100. * ( iQ + 1 ) / fdg.Qg.size();
        std::cout << "Status report for the structure function grid computation: "<< std::setw(6) << std::setprecision(4) << perc << "\% completed...\r";
        std::cout.flush();
      }

    std::cout << "\n";

    // Dump grids to emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);
    out->SetFloatPrecision(6);
    out->SetDoublePrecision(6);
    *out << YAML::BeginMap;
    *out << YAML::Key << "Qg"    << YAML::Value << YAML::Flow << fdg.Qg;
    *out << YAML::Key << "xg"    << YAML::Value << YAML::Flow << fdg.xg;
    *out << YAML::Key << "zg"    << YAML::Value << YAML::Flow << fdg.zg;
    *out << YAML::Key << "qToQg" << YAML::Value << YAML::Flow << fdg.qToQg;
    *out << YAML::Key << "StructureFunction"  << YAML::Value << YAML::Flow << SFs;
    *out << YAML::EndMap;

    // Stop timer
    t.stop();

    // Return the emitter
    return out;
  }

  //_________________________________________________________________________________
  std::unique_ptr<YAML::Emitter> EmitStructInfo(std::string      const& GridsDirectory,
                                                std::string      const& GridTMDPDFfolder,
                                                std::string      const& GridTMDFFfolder,
                                                YAML::Node       const& config,
                                                int              const& NumMembers,
                                                std::string      const& pf,
                                                FourDGrid        const& fdg,
                                                std::vector<int> const& Flavors,
                                                std::string      const& SetDesc,
                                                std::string      const& Target,
                                                std::string      const& Hadron,
                                                std::string      const& Authors,
                                                std::string      const& Reference,
                                                std::string      const& SetIndex,
                                                std::string      const& Format,
                                                std::string      const& DataVersion,
                                                std::string      const& ErrorType)
  {
    // Allocate YAML emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);

    //Info file for TMDPDFs
    const YAML::Node pdfinfo = YAML::LoadFile(GridsDirectory + "/"  + GridTMDPDFfolder + "/" + GridTMDPDFfolder + ".info");

    //Info file for TMDFFs
    const YAML::Node ffinfo = YAML::LoadFile(GridsDirectory + "/"  + GridTMDFFfolder + "/" + GridTMDFFfolder + ".info");

    // FF distribution for final state hadron name
    const std::string ffdist = ffinfo["CollDist"].as<std::string>();

    // Dump grids to emitter
    out->SetFloatPrecision(8);
    out->SetDoublePrecision(8);
    *out << YAML::BeginMap;
    *out << YAML::Key << "SetDesc"           << YAML::Value << SetDesc;
    *out << YAML::Key << "Authors"           << YAML::Value << Authors;
    *out << YAML::Key << "Reference"         << YAML::Value << Reference;
    *out << YAML::Key << "SetIndex"          << YAML::Value << SetIndex;
    *out << YAML::Key << "StructFuncType"    << YAML::Value << pf;
    *out << YAML::Key << "TMDScheme"        << YAML::Value << "Pavia SFs";
    *out << YAML::Key << "Target"            << YAML::Value << Target;
    // *out << YAML::Key << "FinalStateHadron"  << YAML::Value << Hadron;
    *out << YAML::Key << "FinalStateHadron"  << YAML::Value << ffdist.substr(ffdist.size() - 3, 3);
    *out << YAML::Key << "TMDPDF"            << YAML::Value << pdfinfo["SetName"].as<std::string>();
    *out << YAML::Key << "TMDFF"             << YAML::Value << ffinfo["SetName"].as<std::string>();
    *out << YAML::Key << "Format"            << YAML::Value << Format;
    *out << YAML::Key << "DataVersion"       << YAML::Value << DataVersion;
    *out << YAML::Key << "OrderQCD"          << YAML::Value << pdfinfo["OrderQCD"].as<std::string>();
    *out << YAML::Key << "NumMembers"        << YAML::Value << NumMembers;
    *out << YAML::Key << "ErrorType"         << YAML::Value << ErrorType;
    *out << YAML::Key << "NumFlavors"        << YAML::Value << std::round(Flavors.size() / 2);
    *out << YAML::Key << "XMin"              << YAML::Value << fdg.xg[0];
    *out << YAML::Key << "XMax"              << YAML::Value << fdg.xg.back();
    *out << YAML::Key << "ZMin"              << YAML::Value << fdg.zg[0];
    *out << YAML::Key << "ZMax"              << YAML::Value << fdg.zg.back();
    *out << YAML::Key << "QMin"              << YAML::Value << fdg.Qg[0];
    *out << YAML::Key << "QMax"              << YAML::Value << fdg.Qg.back();
    *out << YAML::Key << "KtoQMin"           << YAML::Value << fdg.qToQg[0];
    *out << YAML::Key << "KtoQMax"           << YAML::Value << fdg.qToQg.back();
    *out << YAML::EndMap;

    // Return the emitter
    return out;
  }
}
