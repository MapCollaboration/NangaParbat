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
  std::string PreprocessD0RunIImu(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing D0 Run II data for muons ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins856972-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"Table1.yaml"};

    // Output folder
    const std::string ofolder = "D0";

    // Output file
    const std::string ofile = "D0_RunIImu.yaml";

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // FSR correction factors
        const std::vector<double> fsr{1.06, 1.01, 0.97, 0.95, 0.98, 0.99, 1.00, 1.01, 1.02, 1.03, 1.03, 1.04, 1.05};

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
            // Open PDF-error file
            std::ifstream pdferr(PDFErrorFolder + "D0_RunIImu.out");
            std::string line;
            getline(pdferr, line);
            getline(pdferr, line);

            // Plot labels
            std::map<std::string, std::string> labels
            {
              {"xlabel", "#it{q}_{T} [GeV]"},
              {"ylabel", "#frac{1}{#it{#sigma}} #frac{d#it{#sigma}}{d#it{q}_{T}}  [GeV^{-1}]"},
              {"title", "D0 Run II muons, 65 GeV < Q < 115 GeV, |#it{y}| < 1.7"},
              {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
              {"ylabelpy", "$\\frac{1}{\\sigma}\\frac{d\\sigma}{dq_{T}}[\\rm{GeV}^{-1}]$"},
              {"titlepy", "D0 Run II muons, 65 GeV < Q < 115 GeV, $|y|$ < 1.7"}
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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << -1 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 1960 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << 65 << YAML::Key << "high" << YAML::Value << 115 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << -1.7 << YAML::Key << "high" << YAML::Value << 1.7 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                 << "pTmin" << YAML::Value << 15 << YAML::Key << "etamin" << YAML::Value << -1.7 << YAML::Key << "etamax" << YAML::Value << 1.7 << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            int i = 0;
            for (auto const& v : dv["values"])
              {
                std::string stat  = v["errors"][0]["symerror"].as<std::string>();
                std::string sysun = v["errors"][1]["symerror"].as<std::string>();
                std::string sysc1;
                if (v["errors"][2]["symerror"])
                  sysc1 = v["errors"][2]["symerror"].as<std::string>();
                else if (v["errors"][2]["asymerror"])
                  sysc1 = v["errors"][2]["asymerror"]["minus"].as<std::string>();
                std::string sysc2 = v["errors"][3]["symerror"].as<std::string>();
                std::string sysc3 = v["errors"][4]["symerror"].as<std::string>();
                sysun.erase(std::remove(sysun.begin(), sysun.end(), '%'), sysun.end());
                sysc1.erase(std::remove(sysc1.begin(), sysc1.end(), '%'), sysc1.end());
                sysc2.erase(std::remove(sysc2.begin(), sysc2.end(), '%'), sysc2.end());
                sysc3.erase(std::remove(sysc3.begin(), sysc3.end(), '%'), sysc3.end());

                const double val  = fsr[i] * v["value"].as<double>();
                const double unc  = sqrt( pow(fsr[i++] * std::stod(stat), 2) + pow(val * std::stod(sysun) / 100, 2));
                const double cor1 = std::stod(sysc1) / 100;
                const double cor2 = std::stod(sysc2) / 100;
                const double cor3 = std::stod(sysc3) / 100;

                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe;
                stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                if (PDFError)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << cor1 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << cor2 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << cor3 << YAML::EndMap;
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
            emit << YAML::Key << "header" << YAML::Value << "{name: PT, units: GEV}";
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
    return "  - {name: D0_RunIImu, file: D0_RunIImu.yaml}\n";
  }
}
