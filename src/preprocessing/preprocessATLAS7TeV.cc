/*
 * Author: Chiara Bissolotti
 */

#include "NangaParbat/preprocessing.h"

#include <yaml-cpp/yaml.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessATLAS7TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing ATLAS 7 TeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins1300647-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"Table3.yaml"};

    // Vector of tables to process
    const std::string ofolder = "ATLAS";

    // Initialize naming map for the Q-integration ranges
    std::map<std::string, std::string> yranges = {{"0.0-1.0", "_y_0_1"}, {"1.0-2.0", "_y_1_2"}, {"2.0-2.4", "_y_2_2.4"}};
    std::map<std::string, std::pair<std::string, std::string>> yrangelims = {{"0.0-1.0", {"0", "1"}}, {"1.0-2.0", {"1", "2"}}, {"2.0-2.4", {"2", "2.4"}}};

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);

        // Get qT bin bounds
        std::vector<std::pair<double,double>> qTb;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            qTb.push_back(std::make_pair(vl["low"].as<double>(), vl["high"].as<double>()));

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            std::string ofile;
            std::pair<std::string, std::string> ylims;
            std::string level;
            for (auto const& q : dv["qualifiers"])
              if (q["name"].as<std::string>() == "ABS(YRAP(Z))")
                {
                  ofile  = ofolder + "_7TeV" + yranges[q["value"].as<std::string>()];
                  ylims = yrangelims[q["value"].as<std::string>()];
                }
              else if (q["name"].as<std::string>() == "Level")
                level = q["value"].as<std::string>();

            // If the level is "Dressed" continue with the next block
            if (level == "Dressed")
              continue;

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
              {"title", "ATLAS at 7 TeV, 66 GeV < Q < 116 GeV, " + ylims.first + " < |#it{y}| < " + ylims.second},
              {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
              {"ylabelpy", "$\\frac{1}{\\sigma}\\frac{d\\sigma}{dq_{T}}[\\rm{GeV}^{-1}]$"},
              {"titlepy", "ATLAS at 7 TeV, 66 GeV < Q < 116 GeV, " + ylims.first + " < $|y|$ < " + ylims.second}
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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 7000 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << 66 << YAML::Key << "high" << YAML::Value << 116 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << ylims.first << YAML::Key << "high" << YAML::Value << ylims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                 << "pTmin" << YAML::Value << 20 << YAML::Key << "etamin" << YAML::Value << -2.4 << YAML::Key << "etamax" << YAML::Value << 2.4 << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            for (auto const& v : dv["values"])
              {
                std::string stat = v["errors"][0]["symerror"].as<std::string>();
                std::string sysu = v["errors"][1]["symerror"].as<std::string>();
                std::string sysc = v["errors"][2]["symerror"].as<std::string>();
                stat.erase(std::remove(stat.begin(), stat.end(), '%'), stat.end());
                sysu.erase(std::remove(sysu.begin(), sysu.end(), '%'), sysu.end());
                sysc.erase(std::remove(sysc.begin(), sysc.end(), '%'), sysc.end());

                const double val = v["value"].as<double>();
                const double unc = sqrt( pow(val * std::stod(stat) / 100, 2) + pow(val * std::stod(sysu) / 100, 2));
                const double cor = std::stod(sysc) / 100;

                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe;
                // stream >> dum >> dum >> dum >> dum >> dum >> pe >> dum;
                stream >> dum >> dum >> dum >> dum >> pe >> dum;

                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                if (PDFError)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << std::max(pe, 0.0) * 0.8 << YAML::EndMap;
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << std::max(pe, 0.0) * val * 0.6 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << cor << YAML::EndMap;
                // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0.005 * val << YAML::EndMap; //[TEMPORARY] trial of introduction of new theoretical error
                emit << YAML::EndSeq;
                emit << YAML::Key << "value" << YAML::Value << val;
                emit << YAML::EndMap;
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
      "  - {name: ATLAS_7TeV_y_0_1,     file: ATLAS_7TeV_y_0_1.yaml}\n"
      "  - {name: ATLAS_7TeV_y_1_2,     file: ATLAS_7TeV_y_1_2.yaml}\n"
      "  - {name: ATLAS_7TeV_y_2_2.4,   file: ATLAS_7TeV_y_2_2.4.yaml}\n";
  }
}
