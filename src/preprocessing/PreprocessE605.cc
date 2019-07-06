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
  void PreprocessE605(std::string const& RawDataPath, std::string const& ProcessedDataPath)
  {
    std::cout << "Processing E605 data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins302822-v1-yaml/";

    // Vector of tables to process
    const std::string ofolder = "E605";
    const std::vector<std::string> tables = {"Table17.yaml", "Table18.yaml", "Table19.yaml", "Table20.yaml", "Table21.yaml"};

    // Initialize naming map for the Q-integration ranges
    std::map<std::string, std::string> enranges = {{"7 TO 8", "_Q_7_8"}, {"8 TO 9", "_Q_8_9"}, {"10.5 TO 11.5", "_Q_10.5_11.5"},
      {"11.5 TO 13.5", "_Q_11.5_13.5"}, {"13.5 TO 18.0", "_Q_13.5_18"}
    };

    std::map<std::string, std::pair<double, double>> enrangelims = {{"7 TO 8", {7, 8}}, {"8 TO 9", {8, 9}}, {"10.5 TO 11.5", {10.5, 11.5}},
      {"11.5 TO 13.5", {11.5, 13.5}}, {"13.5 TO 18.0", {13.5, 18}}
    };

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
            qTb.push_back(std::make_pair(-1, vl["value"].as<double>()));

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            std::string ofile;
            std::pair<double, double> enlims;
            double y = 0;
            double Qav = 0;
            const double Vs = 38.8;
            for (auto const& q : dv["qualifiers"])
              {
                if (q["name"].as<std::string>() == "M(P=3 4)")
                  {
                    ofile  = ofolder + enranges[q["value"].as<std::string>()] + ".yaml";
                    enlims = enrangelims[q["value"].as<std::string>()];
                  }
                if (q["name"].as<std::string>() == "XL")
                  {
                    const double xF = - q["value"].as<double>();
                    Qav = ( enlims.first + enlims.second ) / 2;
                    y = log(Vs * ( xF + sqrt( pow(xF, 2) + pow(2 * Qav / Vs, 2 ) ) ) / 2 / Qav );
                  }
              }

            // Overall factor
            const double factor = Vs / 2 / Qav / cosh(y) / M_PI;

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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << factor << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << Vs << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << enlims.first << YAML::Key << "high" << YAML::Value << enlims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << y << YAML::Key << "high" << YAML::Value << y << YAML::Key << "integrate" << YAML::Value << "false" << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            for (auto const& v : dv["values"])
              {
                const double val = v["value"].as<double>();
                const double uncsys = 0.05 * val;
                const double unc = sqrt( pow(v["errors"][0]["symerror"].as<double>(), 2) + pow(uncsys, 2) );
                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value"
                     << YAML::Value << unc << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.15 << YAML::EndMap;
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
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "value" << YAML::Value << qT.second
                   << YAML::Key << "factor" << YAML::Value << 1. / 2. / qT.second << YAML::EndMap;
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
  }
}
