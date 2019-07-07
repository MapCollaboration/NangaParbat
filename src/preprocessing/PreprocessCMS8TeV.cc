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

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessCMS8TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath)
  {
    std::cout << "Processing CMS 8 TeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins1471281-v1-yaml/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"ZtoMuMu.yaml"};

    // Output folder
    const std::string ofolder = "CMS";

    // Output file
    const std::string ofile = "CMS_8TeV.yaml";

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Create directory
        std::string opath = ProcessedDataPath + "/" + ofolder;
        mkdir(opath.c_str(), ACCESSPERMS);

        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);

        // Get qT bin bounds
        std::vector<std::pair<double,double>> qTb;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            qTb.push_back(std::make_pair(vl["low"].as<double>(), vl["high"].as<double>()));

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          if (dv["header"]["units"])
            {
              // Allocate emitter
              YAML::Emitter emit;

              // Write kinematics on the YAML emitter
              emit.SetFloatPrecision(8);
              emit.SetDoublePrecision(8);
              emit << YAML::BeginMap;
              emit << YAML::Key << "dependent_variables";
              emit << YAML::BeginSeq;
              emit << YAML::BeginMap;
              emit << YAML::Key << "header" << YAML::Value << dv["header"];
              emit << YAML::Key << "qualifiers" << YAML::Value;
              emit << YAML::BeginSeq;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "process" << YAML::Key << "value" << YAML::Value << "DY" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 8000 << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                   << "low" << YAML::Value << 60 << YAML::Key << "high" << YAML::Value << 120 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                   << "low" << YAML::Value << 0 << YAML::Key << "high" << YAML::Value << 2.1 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                   << "pTmin" << YAML::Value << 15 << YAML::Key << "etamin" << YAML::Value << -2.1 << YAML::Key << "etamax" << YAML::Value << 2.1 << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (auto const& v : dv["values"])
                {
                  emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value"
                       << YAML::Value << v["errors"][0]["symerror"].as<double>()<< YAML::EndMap;
                  emit << YAML::EndSeq;
                  emit << YAML::Key << "value" << YAML::Value << v["value"].as<double>();
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

              // Dump table to file
              std::ofstream fout(opath + "/" + ofile);
              fout << emit.c_str() << std::endl;
              fout.close();
            }
      }
    return "#   - {name: CMS_8TeV, file: CMS_8TeV.yaml}\n";
  }
}
