/*
 * Author: Matteo Cerutti
 */

#include "NangaParbat/preprocessing.h"

#include <yaml-cpp/yaml.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessCMS13TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing CMS 13 TeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins1753680-v2-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"figures_9_to_13.yaml"}; //differential cross section
    // const std::vector<std::string> tables = {"figures_15_to_19.yaml"}; //norm. differential cross section

    // Output folder
    const std::string ofolder = "CMS"; //diff. cross section
    // const std::string ofolder = "CMS_norm"; //norm. diff. cross section

    // Initialize naming map for the y-integration ranges
    std::map<std::string, std::string> yranges = {{"0 < |y(Z)| < 0.4 bin", "_y_0_0.4"}, {"0.4 < |y(Z)| < 0.8 bin", "_y_0.4_0.8"}, {"0.8 < |y(Z)| < 1.2 bin", "_y_0.8_1.2"}, {"1.2 < |y(Z)| < 1.6 bin", "_y_1.2_1.6"}, {"1.6 < |y(Z)| < 2.4 bin", "_y_1.6_2.4"}};
    std::map<std::string, std::pair<std::string, std::string>> yrangelims = {{"0 < |y(Z)| < 0.4 bin", {"0", "0.4"}}, {"0.4 < |y(Z)| < 0.8 bin", {"0.4", "0.8"}}, {"0.8 < |y(Z)| < 1.2 bin", {"0.8", "1.2"}}, {"1.2 < |y(Z)| < 1.6 bin", {"1.2", "1.6"}}, {"1.6 < |y(Z)| < 2.4 bin", {"1.6", "2.4"}}}; //diff

    // std::map<std::string, std::string> yranges = {{"0 < |y(Z)| < 0.4", "_y_0_0.4"}, {"0.4 < |y(Z)| < 0.8", "_y_0.4_0.8"}, {"0.8 < |y(Z)| < 1.2", "_y_0.8_1.2"}, {"1.2 < |y(Z)| < 1.6", "_y_1.2_1.6"}, {"1.6 < |y(Z)| < 2.4", "_y_1.6_2.4"}};
    // std::map<std::string, std::pair<std::string, std::string>> yrangelims = {{"0 < |y(Z)| < 0.4", {"0", "0.4"}}, {"0.4 < |y(Z)| < 0.8", {"0.4", "0.8"}}, {"0.8 < |y(Z)| < 1.2", {"0.8", "1.2"}}, {"1.2 < |y(Z)| < 1.6", {"1.2", "1.6"}}, {"1.6 < |y(Z)| < 2.4", {"1.6", "2.4"}}}; //norm. diff.

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);

        // Get qT bin bounds new
        std::vector<std::pair<double,double>> qTb;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            qTb.push_back(std::make_pair(vl["low"].as<double>(), vl["high"].as<double>()));

        // for (auto const& qT : qTb)
        //   std::cout << qT.first << "   " << qT.second << std::endl;
        // */

        // Run over the energy ranges
        for (auto const& yb : exp["dependent_variables"])
          {
            // std::cout << "output:" << yb["header"]["name"].as<std::string>().substr(37) << std::endl; // ok
            std::string ofile = ofolder + "_13TeV" + yranges[yb["header"]["name"].as<std::string>().substr(31)]; //diff
            // std::string ofile = ofolder + "_13TeV" + yranges[yb["header"]["name"].as<std::string>().substr(37)]; //norm
            // std::cout << "output: " << yb["header"]["name"].as<std::string>().substr(37, 42) << std::endl;
            // std::cout << "yrangestrial: " << yranges["0 < |y(Z)| < 0.4"] << std::endl;
            // std::cout << "yranges: " << yranges[yb["header"]["name"].as<std::string>().substr(37,42)] << std::endl;
            // std::cout << "ofile: " << ofile << std::endl;
            // y limits for plots
            std::pair<std::string, std::string> ylims = yrangelims[yb["header"]["name"].as<std::string>().substr(31)];

            // Open PDF-error file
            std::ifstream pdferr(PDFErrorFolder + ofile + ".out");
            std::string line;
            getline(pdferr, line);
            getline(pdferr, line);

            ofile += ".yaml";

            // Plot labels
            std::map<std::string, std::string> labels
            {
              {"xlabel", "#it{q}_{T} [GeV]"},
              {"ylabel", "#frac{1}{#it{#sigma}} #frac{d#it{#sigma}}{d#it{q}_{T}}  [GeV^{-1}]"},
              {"title", "CMS at 13 TeV,  76.1876 GeV < Q < 106.1876 GeV, " + ylims.first + " < |#it{y}| < " + ylims.second},
              {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
              {"ylabelpy", "$\\frac{1}{\\sigma}\\frac{d\\sigma}{dq_{T}}[\\rm{GeV}^{-1}]$"},
              {"titlepy", "CMS at 13 TeV,  76.1876 GeV < Q < 106.1876 GeV, " + ylims.first + " < $|y|$ < " + ylims.second}
            };

            // Allocate emitter
            YAML::Emitter emit;

            // Write kinematics on the YAML emitter
            emit.SetFloatPrecision(8);
            emit.SetDoublePrecision(8);
            emit << YAML::BeginMap;
            emit << YAML::Key << "dependent_variables";
            emit << YAML::BeginSeq;
            emit << YAML::BeginMap;
            emit << YAML::Key << "header" << YAML::Value << YAML::Flow << labels;
            emit << YAML::Key << "qualifiers" << YAML::Value;
            emit << YAML::BeginSeq;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "process" << YAML::Key << "value" << YAML::Value << "DY" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1  << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 13000 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << 76.1876 << YAML::Key << "high" << YAML::Value << 106.1876 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << ylims.first << YAML::Key << "high" << YAML::Value << ylims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                 << "pTmin" << YAML::Value << 25 << YAML::Key << "pTmax" << YAML::Value << 1500 << YAML::Key << "etamin" << YAML::Value << -2.4 << YAML::Key << "etamax" << YAML::Value << 2.4 << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            int it = 0;
            for (auto const& v : yb["values"])
              {
                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe;
                stream >> dum >> dum >> dum >> dum >> dum >> pe >> dum;

                // Vectors of uncorrelated and correlated errors
                // from article https://arxiv.org/pdf/1606.05864.pdf Tab.4
                // std::vector<double> addart = {0.0274, 0.0138, 0.005, 0.0134, 0.0274, 0.0233, 0.0130, 0.0165, 0.0041, 0.067, 0.0129, 0.0156, 0.0272, 0.0357, 0.0372, 0.0201, 0.1166, 0.0209}; NO OTHERS ERRORS

                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value"
                     << YAML::Value << v["errors"][0]["symerror"].as<double>() << YAML::EndMap; // read unc errors from HEPData file
                if (PDFError)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
                // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value"
                     // << YAML::Value << addart[it] << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::Key << "value" << YAML::Value << v["value"].as<double>();
                // std::cout <<  v["value"].as<double>() << std::endl;
                emit << YAML::EndMap;
                it++;
              }
            emit << YAML::EndSeq;
            emit << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "independent_variables";
            emit << YAML::BeginSeq;
            emit << YAML::BeginMap;
            emit << YAML::Key << "header" << YAML::Value << YAML::Flow;
            emit << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PT" << YAML::Key << "units" << YAML::Value << "GEV" << YAML::EndMap;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            for (auto const& qT : qTb)
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << qT.second
                   << YAML::Key << "low" << YAML::Value << std::max(qT.first, 1e-5) << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::EndMap;

            // Close PDF-error file
            pdferr.close();

            // Dump table to file
            std::ofstream fout(opath + "/" + ofile);
            fout << emit.c_str() << std::endl;
            fout.close();
          }
      }
    return
      "  - {name: CMS_13TeV_y_0_0.4,   file: CMS_13TeV_y_0_0.4.yaml}\n"
      "  - {name: CMS_13TeV_y_0.4_0.8, file: CMS_13TeV_y_0.4_0.8.yaml}\n"
      "  - {name: CMS_13TeV_y_0.8_1.2, file: CMS_13TeV_y_0.8_1.2.yaml}\n"
      "  - {name: CMS_13TeV_y_1.2_1.6, file: CMS_13TeV_y_1.2_1.6.yaml}\n"
      "  - {name: CMS_13TeV_y_1.6_2.4, file: CMS_13TeV_y_1.6_2.4.yaml}\n";


  }
}
