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
  std::string PreprocessE288(std::string const& RawDataPath, std::string const& ProcessedDataPath)
  {
    std::cout << "Processing E288 data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins153009-v1-yaml/";

    // Vector of tables to process
    const std::string ofolder = "E288";
    const std::map<std::string, std::string> tables{{"Table11.yaml", "E288_200"}, {"Table10.yaml", "E288_300"}, {"Table9.yaml", "E288_400"}};

    // Initialize naming map for the Q-integration ranges
    std::map<std::string, std::string> enranges = {{"4.TO5.", "_Q_4_5"}, {"5.TO6.", "_Q_5_6"}, {"6.TO7.", "_Q_6_7"},
      {"7.TO8.", "_Q_7_8"}, {"8.TO9.", "_Q_8_9"}, {"9.TO10.", "_Q_9_10"},
      {"10.TO11.", "_Q_10_11"}, {"11.TO12.", "_Q_11_12"}, {"12.TO13.", "_Q_12_13"},
      {"13.TO14.", "_Q_13_14"}
    };
    std::map<std::string, std::pair<double, double>> enrangelims = {{"4.TO5.", {4,5}}, {"5.TO6.", {5, 6}}, {"6.TO7.", {6, 7}},
      {"7.TO8.", {7, 8}}, {"8.TO9.", {8, 9}}, {"9.TO10.", {9, 10}},
      {"10.TO11.", {10, 11}}, {"11.TO12.", {11, 12}}, {"12.TO13.", {12, 13}},
      {"13.TO14.", {13, 14}}
    };

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab.first);

        // Get qT bin bounds
        std::vector<std::pair<double,double>> qTb;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            qTb.push_back(std::make_pair(vl["low"].as<double>(), vl["high"].as<double>()));

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            std::string ofile;
            std::pair<double, double> enlims;
            double y = 0;
	    double Vs = 0;
	    if (tab.second == "E288_200")
	      Vs = 19.4;
	    else if (tab.second == "E288_300")
	      Vs = 23.8;
	    else if (tab.second == "E288_400")
	      Vs = 27.4;
            for (auto const& q : dv["qualifiers"])
              {
                if (q["name"].as<std::string>() == "W(P=3 4)")
                  {
                    ofile  = tab.second + enranges[q["value"].as<std::string>()] + ".yaml";
                    enlims = enrangelims[q["value"].as<std::string>()];
                  }
                if (q["name"].as<std::string>() == "YRAP(P=3 4,RF=CM)")
                  y = q["value"].as<double>();
              }

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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 0.4603 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 / M_PI << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << Vs << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << enlims.first << YAML::Key << "high" << YAML::Value << enlims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << y << YAML::Key << "high" << YAML::Value << y << YAML::Key << "integrate" << YAML::Value << "false" << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            std::vector<std::pair<double,double>> qTav;
            int i = 0;
            for (auto const& v : dv["values"])
              {
                if (v["value"].as<std::string>() != "-")
                  {
                    emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value"
                         << YAML::Value << v["errors"][0]["symerror"].as<double>() / 1000 << YAML::EndMap;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.25 << YAML::EndMap;
                    emit << YAML::EndSeq;
                    emit << YAML::Key << "value" << YAML::Value << v["value"].as<double>() / 1000;
                    emit << YAML::EndMap;
                    qTav.push_back(qTb[i]);
                  }
                i++;
              }
            emit << YAML::EndSeq;
            emit << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "independent_variables";
            emit << YAML::BeginSeq;
            emit << YAML::BeginMap;
            emit << YAML::Key << "header" << YAML::Value << "{name: 'PT(P=3 4,RF=CM)', units: GEV}";
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            for (auto const& qT : qTav)
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "value" << YAML::Value << ( qT.first + qT.second ) / 2
                   << YAML::Key << "factor" << YAML::Value << 1 / ( qT.first + qT.second ) << YAML::EndMap;
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
    return
      "  - {name: E288_200_Q_4_5,   file: E288_200_Q_4_5.yaml}\n"
      "  - {name: E288_200_Q_5_6,   file: E288_200_Q_5_6.yaml}\n"
      "  - {name: E288_200_Q_6_7,   file: E288_200_Q_6_7.yaml}\n"
      "  - {name: E288_200_Q_7_8,   file: E288_200_Q_7_8.yaml}\n"
      "  - {name: E288_200_Q_8_9,   file: E288_200_Q_8_9.yaml}\n"
      "#   - {name: E288_200_Q_9_10,  file: E288_200_Q_9_10.yaml}\n"
      "#   - {name: E288_200_Q_10_11, file: E288_200_Q_10_11.yaml}\n"
      "  - {name: E288_300_Q_4_5,   file: E288_300_Q_4_5.yaml}\n"
      "  - {name: E288_300_Q_5_6,   file: E288_300_Q_5_6.yaml}\n"
      "  - {name: E288_300_Q_6_7,   file: E288_300_Q_6_7.yaml}\n"
      "  - {name: E288_300_Q_7_8,   file: E288_300_Q_7_8.yaml}\n"
      "  - {name: E288_300_Q_8_9,   file: E288_300_Q_8_9.yaml}\n"
      "#   - {name: E288_300_Q_9_10,  file: E288_300_Q_9_10.yaml}\n"
      "#   - {name: E288_300_Q_10_11, file: E288_300_Q_10_11.yaml}\n"
      "#   - {name: E288_300_Q_11_12, file: E288_300_Q_11_12.yaml}\n"
      "  - {name: E288_400_Q_5_6,   file: E288_400_Q_5_6.yaml}\n"
      "  - {name: E288_400_Q_6_7,   file: E288_400_Q_6_7.yaml}\n"
      "  - {name: E288_400_Q_7_8,   file: E288_400_Q_7_8.yaml}\n"
      "  - {name: E288_400_Q_8_9,   file: E288_400_Q_8_9.yaml}\n"
      "#   - {name: E288_400_Q_9_10,  file: E288_400_Q_9_10.yaml}\n"
      "#   - {name: E288_400_Q_10_11, file: E288_400_Q_10_11.yaml}\n"
      "  - {name: E288_400_Q_11_12, file: E288_400_Q_11_12.yaml}\n"
      "  - {name: E288_400_Q_12_13, file: E288_400_Q_12_13.yaml}\n"
      "  - {name: E288_400_Q_13_14, file: E288_400_Q_13_14.yaml}\n";
  }
}
