//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#include "NangaParbat/createstructgrid.h"
#include "NangaParbat/tmdgrid.h"
#include "NangaParbat/factories.h"
#include "NangaParbat/listdir.h"
#include "NangaParbat/direxists.h"
#include "NangaParbat/numtostring.h"

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
        for (auto const f : list_dir(GridsDirectory + "/" + GridTMDPDFfolder))
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
    iout << NangaParbat::EmitStructInfo(config, grids.size(), pf, Inter4DGrid(pf))->c_str() << std::endl;
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
            // std::cout << "x =   " << fdg.xg[ix] << std::endl;
            for (int iz = 0; iz < (int) fdg.zg.size(); iz++)
              {
                for (int iqT = 0; iqT < (int) fdg.qToQg.size(); iqT++)
                  {
                    const auto conv = Convolution(TMDPDFs, TMDFFs, [] (double const&) -> std::vector<double> { return apfel::QCh2;}, qToQcut);
                    // std::cout << conv(fdg.xg[ix], fdg.zg[iz], 1 , fdg.Qg[iQ] * fdg.qToQg[iqT]) / fdg.zg[iz]/ (2 * M_PI) << std::endl;
                    SFs[iQ][ix][iz][iqT] = conv(fdg.xg[ix], fdg.zg[iz], fdg.Qg[iQ] , fdg.Qg[iQ] * fdg.qToQg[iqT]) / fdg.zg[iz] / (2 * M_PI);
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
  std::unique_ptr<YAML::Emitter> EmitStructInfo(YAML::Node       const& config,
                                                int              const& NumMembers,
                                                std::string      const& pf,
                                                FourDGrid        const& fdg,
                                                std::vector<int> const& Flavors,
                                                std::string      const& SetDesc,
                                                std::string      const& Authors,
                                                std::string      const& Reference,
                                                std::string      const& SetIndex,
                                                std::string      const& Format,
                                                std::string      const& DataVersion,
                                                std::string      const& ErrorType)
  {
    // Allocate YAML emitter
    std::unique_ptr<YAML::Emitter> out = std::unique_ptr<YAML::Emitter>(new YAML::Emitter);

    // Dump grids to emitter
    out->SetFloatPrecision(8);
    out->SetDoublePrecision(8);
    *out << YAML::BeginMap;
    *out << YAML::Key << "SetDesc"        << YAML::Value << SetDesc;
    *out << YAML::Key << "Authors"        << YAML::Value << Authors;
    *out << YAML::Key << "Reference"      << YAML::Value << Reference;
    *out << YAML::Key << "SetIndex"       << YAML::Value << SetIndex;
    *out << YAML::Key << "TMDType"        << YAML::Value << pf;
    *out << YAML::Key << "CollDistPDF"       << YAML::Value << config["pdfset"]["name"].as<std::string>();
    *out << YAML::Key << "CollDistMemberPDF" << YAML::Value << config["pdfset"]["member"].as<std::string>();
    *out << YAML::Key << "CollDistFF"        << YAML::Value << config["ffset"]["name"].as<std::string>();
    *out << YAML::Key << "CollDistMemberFF"  << YAML::Value << config["ffset"]["member"].as<std::string>();
    *out << YAML::Key << "Format"         << YAML::Value << Format;
    *out << YAML::Key << "DataVersion"    << YAML::Value << DataVersion;
    *out << YAML::Key << "OrderQCD"       << YAML::Value << config["PerturbativeOrder"].as<int>();
    // *out << YAML::Key << "OrderQCD"       << YAML::Value << NangaParbat::PtOrderMap.at(config["PerturbativeOrder"].as<int>());
    *out << YAML::Key << "Regularisation" << YAML::Value << "bstar";
    *out << YAML::Key << "NumMembers"     << YAML::Value << NumMembers;
    *out << YAML::Key << "ErrorType"      << YAML::Value << ErrorType;
    *out << YAML::Key << "Flavors"        << YAML::Value << YAML::Flow << Flavors;
    *out << YAML::Key << "NumFlavors"     << YAML::Value << std::round(Flavors.size() / 2);
    *out << YAML::Key << "XMin"           << YAML::Value << fdg.xg[0];
    *out << YAML::Key << "XMax"           << YAML::Value << fdg.xg.back();
    *out << YAML::Key << "ZMin"           << YAML::Value << fdg.zg[0];
    *out << YAML::Key << "ZMax"           << YAML::Value << fdg.zg.back();
    *out << YAML::Key << "QMin"           << YAML::Value << fdg.Qg[0];
    *out << YAML::Key << "QMax"           << YAML::Value << fdg.Qg.back();
    *out << YAML::Key << "KtoQMin"        << YAML::Value << fdg.qToQg[0];
    *out << YAML::Key << "KtoQMax"        << YAML::Value << fdg.qToQg.back();
    *out << YAML::EndMap;

    // Return the emitter
    return out;
  }
}
