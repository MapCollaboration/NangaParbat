/*
 * Author: Simone Venturini
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
  std::string PreprocessE537(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing E537 data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins253413-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"Table5.yaml"};

    // specify a folder where the preprocessed data will be inserted
    const std::string ofolder = "E537";

    // Initialize naming map for the Q-integration ranges
    std::map<std::string, std::string> Qranges = {{"4.0TO4.5", "_Q_4.0_4.5"}, {"4.5TO5.0", "_Q_4.5_5.0"}, {"5.0TO5.5", "_Q_5.0_5.5"}, {"5.5TO6.0","_Q_5.5_6.0"}, {"6.0TO6.5","_Q_6.0_6.5"}, {"6.5TO7.0","_Q_6.5_7.0"}, {"7.0TO7.5","_Q_7.0_7.5"}, {"7.5TO8.0","_Q_7.5_8.0"}, {"8.0TO8.5","_Q_8.0_8.5"}, {"8.5TO9.0","_Q_8.5_9.0"}};
    std::map<std::string, std::pair<std::string, std::string>> Qrangelims = {{"4.0TO4.5", {"4", "5"}}, {"4.5TO5.0", {"4.5", "5.0"}}, {"5.0TO5.5", {"5", "5.5"}}, {"5.5TO6.0",{"5.5","6"}}, {"6.0TO6.5",{"6","6.5"}}, {"6.5TO7.0",{"6.5","7"}}, {"7.0TO7.5",{"7","7.5"}}, {"7.5TO8.0",{"7.5","8"}}, {"8.0TO8.5",{"8","8.5"}}, {"8.5TO9.0",{"8.5","9"}}};

    // Create directory on the basis of "ofolder" specified previously
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);

        // Get qT bin bounds (transverse momentum)
        std::vector<std::pair<double,double>> qTb;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            qTb.push_back(std::make_pair(vl["low"].as<double>(), vl["high"].as<double>()));

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            std::string ofile;
            std::pair<std::string, std::string> Qlims;
            std::string level;
            for (auto const& q : dv["qualifiers"])
              if (q["name"].as<std::string>() == "M(P=3 4)")
                {
                  ofile  = ofolder + Qranges[q["value"].as<std::string>()];
                  Qlims = Qrangelims[q["value"].as<std::string>()];
                }


          /*
                else if (q["name"].as<std::string>() == "Level")
                level = q["value"].as<std::string>();

            // If the level is "Dressed" continue with the next block
            if (level == "Dressed")
              continue;
          */


            // Open PDF-error file
            std::ifstream pdferr(PDFErrorFolder + ofile + ".out");
            std::string line;
            getline(pdferr, line);
            getline(pdferr, line);

            ofile += ".yaml";

            // Plot labels, check the range of Q
            std::map<std::string, std::string> labels
            {
              {"xlabel", "#it{q}_{T} [GeV]"},
              {"ylabel", "#frac{1}{#it{#sigma}} #frac{d#it{#sigma}}{d#it{q}_{T}}  [GeV^{-1}]"},
              {"title", "E537 at 125 GeV, " + Qlims.first + " GeV < Q < " + Qlims.second + " GeV, ### < |#it{y}| < ### "},
              {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
              {"ylabelpy", "$\\frac{1}{\\sigma}\\frac{d\\sigma}{dq_{T}}[\\rm{GeV}^{-1}]$"},
              {"titlepy", "E537 at 125 GeV, " + Qlims.first + " GeV < Q <" + Qlims.second + "GeV, ### < $|y|$ < ### "}
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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << "###" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << "###" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 125 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << Qlims.first << YAML::Key << "high" << YAML::Value << Qlims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << "###" << YAML::Key << "high" << YAML::Value << "###" << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                 << "pTmin" << YAML::Value << "###" << YAML::Key << "etamin" << YAML::Value << "###" << YAML::Key << "etamax" << YAML::Value << "###" << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            for (auto const& v : dv["values"])
              {
                std::string stat = v["errors"][0]["symerror"].as<std::string>();

                // std::string sysu = v["errors"][1]["symerror"].as<std::string>();
                // std::string sysc = v["errors"][2]["symerror"].as<std::string>();
                //
                stat.erase(std::remove(stat.begin(), stat.end(), '%'), stat.end());
                // sysu.erase(std::remove(sysu.begin(), sysu.end(), '%'), sysu.end());
                // sysc.erase(std::remove(sysc.begin(), sysc.end(), '%'), sysc.end());

                const double val = v["value"].as<double>();
                const double unc = std::stod(stat);
                // const double unc = sqrt( pow(val * std::stod(stat) / 100, 2) + pow(val * std::stod(sysu) / 100, 2));

                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe;
                stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                if (PDFError)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.16 << YAML::EndMap;
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
      "  - {name: E537_Q_4.0_4.5,     file: E537_Q_4.0_4.5.yaml}\n"
      "  - {name: E537_Q_4.5_5.0,     file: E537_Q_4.5_5.0.yaml}\n"
      "  - {name: E537_Q_5.0_5.5,     file: E537_Q_5.0_5.5.yaml}\n"
      "  - {name: E537_Q_5.5_6.0,     file: E537_Q_5.5_6.0.yaml}\n"
      "  - {name: E537_Q_6.0_6.5,     file: E537_Q_6.0_6.5.yaml}\n"
      "  - {name: E537_Q_6.5_7.0,     file: E537_Q_6.5_7.0.yaml}\n"
      "  - {name: E537_Q_7.0_7.5,     file: E537_Q_7.0_7.5.yaml}\n"
      "  - {name: E537_Q_7.5_8.0,     file: E537_Q_7.5_8.0.yaml}\n"
      "  - {name: E537_Q_8.0_8.5,     file: E537_Q_8.0_8.5.yaml}\n"
      "  - {name: E537_Q_8.5_9.0,     file: E537_Q_8.5_9.0.yaml}\n";
  }
}
