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
#include <string>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessE537_xF(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing E537 data binned in x_F..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins253413-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"Table6.yaml"};

    // specify a folder where the preprocessed data will be inserted
    const std::string ofolder = "E537";

    // Initialize naming map for the xF-integration ranges
    std::map<std::string, std::string> xFranges = {{"-0.1TO0.", "_xF_-0.1_0.0"}, {"0.0TO0.1", "_xF_0.0_0.1"}, {"0.1TO0.2", "_xF_0.1_0.2"}, {"0.2TO0.3","_xF_0.2_0.3"}, {"0.3TO0.4","_xF_0.3_0.4"}, {"0.4TO0.5","_xF_0.4_0.5"}, {"0.5TO0.6","_xF_0.5_0.6"}, {"0.6TO0.7","_xF_0.6_0.7"}, {"0.7TO0.8","_xF_0.7_0.8"}, {"0.8TO0.9","_xF_0.8_0.9"}, {"0.9TO1.0","_xF_0.9_1.0"}};
    std::map<std::string, std::pair<std::string, std::string>> xFrangelims = {{"-0.1TO0.", {"-0.1", "0.0"}}, {"0.0TO0.1", {"0.0", "0.1"}}, {"0.1TO0.2", {"0.1", "0.2"}}, {"0.2TO0.3",{"0.2","0.3"}}, {"0.3TO0.4",{"0.3","0.4"}}, {"0.4TO0.5",{"0.4","0.5"}}, {"0.5TO0.6",{"0.5","0.6"}}, {"0.6TO0.7",{"0.6","0.7"}}, {"0.7TO0.8",{"0.7","0.8"}}, {"0.8TO0.9",{"0.8","0.9"}}, {"0.9TO1.0",{"0.9","1.0"}}};
    std::map<std::string, std::pair<double,double>> xFextremes= {{"-0.1TO0.", {-0.1,0.0}}, {"0.0TO0.1", {0.0,0.1}}, {"0.1TO0.2", {0.1,0.2}}, {"0.2TO0.3",{0.2,0.3}}, {"0.3TO0.4",{0.3,0.4}}, {"0.4TO0.5", {0.4,0.5}}, {"0.5TO0.6",{0.5,0.6}}, {"0.6TO0.7", {0.6,0.7}}, {"0.7TO0.8", {0.7,0.8}}, {"0.8TO0.9", {0.8,0.9}}, {"0.9TO1.0", {0.9,1.0}}};
    // Create directory on the basis of "ofolder" specified previously
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);

        // Get pT bin bounds (transverse momentum)
        std::vector<std::pair<double,double>> pT;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            pT.push_back(std::make_pair(vl["low"].as<double>(), vl["high"].as<double>()));

        // Run over the x ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            //  Define the minimum and the maximum value of y
            // NOTE on the calculation of y_min and y_max: y=arcsinh(sqrt{s}*xF/(2Q)).
            //                                             The value of Q_min = 4.0, then y_min= arcsinh(x_min*sqrt(s)/(2*9.0)) for a specific x_min<xF<x_max bin
            //                                                          Q_max = 9.0, then y_max = arcsinh(x_max*sqrt(s)/(2*4.0)) for a specific x_min<xF<x_max bin
            double xFexmin, xFexmax;
            double y_min, y_max;

            std::string ofile;
            std::pair<std::string, std::string> xFlims;
            std::pair<double, double> xFestremi;
            std::string level;

            for (auto const& q : dv["qualifiers"])
              if (q["name"].as<std::string>() == "XL(P=3 4 RF=CM DEF=PL/PLMAX)")
                {
                  ofile  = ofolder + xFranges[q["value"].as<std::string>()];
                  xFlims = xFrangelims[q["value"].as<std::string>()];
                  xFestremi = xFextremes[q["value"].as<std::string>()];
                  xFexmin = xFestremi.first;
                  xFexmax = xFestremi.second;
                  y_min = asinh((xFexmin*125)/(2*9.0));
                  y_max = asinh((xFexmax*125)/(2*4.0));
                }

            // Open PDF-error file
            std::ifstream pdferr(PDFErrorFolder + ofile + ".out");
            std::string line;
            getline(pdferr, line);
            getline(pdferr, line);

            ofile += ".yaml";


            // Plot labels, check the range of Q
            std::map<std::string, std::string> labels
            {
              {"xlabel", "#it{x}_{F}"},
              {"ylabel", "#frac{d2#it{#sigma}}{d#it{p}_{T}^2d#it{x}_{F}}  [GeV^{-2}]"},
              {"title", "E537 at 125 GeV, " + xFlims.first + " < xF < " + xFlims.second + "," + std::to_string(y_min) + "< |#it{y}| < " +std::to_string(y_max)},
              {"xlabelpy", "$x_F$"},
              {"ylabelpy", "$\\frac{d2\\sigma}{dp_{T}^2dx_F}[\\rm{GeV}^{-2}]$"},
              {"titlepy", "E537 at 125 GeV, " + xFlims.first + " < xF <" + xFlims.second + ", " + std::to_string(y_min) + " < $|y|$ < " +std::to_string(y_max)}
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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 0.4025 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 125 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "xF" << YAML::Key
                 << "low" << YAML::Value << xFlims.first << YAML::Key << "high" << YAML::Value << xFlims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                 << "low" << YAML::Value << y_min << YAML::Key << "high" << YAML::Value << y_max << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
            /*  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                   << "pTmin" << YAML::Value << "###" << YAML::Key << "etamin" << YAML::Value << "###" << YAML::Key << "etamax" << YAML::Value << "###" << YAML::EndMap; */
            emit << YAML::EndSeq;
            emit << YAML::Key << "values" << YAML::Value;
            emit << YAML::BeginSeq;
            for (auto const& v : dv["values"])
              {
                std::string stat = v["errors"][0]["symerror"].as<std::string>();
                stat.erase(std::remove(stat.begin(), stat.end(), '%'), stat.end());

                const double val = v["value"].as<double>();
                const double unc = std::stod(stat);

                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe;
                stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                if (PDFError)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.08 << YAML::EndMap;
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
            for (auto const& pTs : pT)
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << pTs.second
                   << YAML::Key << "low" << YAML::Value << std::max(pTs.first, 1e-5) << YAML::EndMap;
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
      "  - {name: E537_xF_-0.1_0.0,    file: E537_xF_-0.1_0.0.yaml}\n"
      "  - {name: E537_xF_0.0_0.1,     file: E537_xF_0.0_0.1.yaml}\n"
      "  - {name: E537_xF_0.1_0.2,     file: E537_xF_0.1_0.2.yaml}\n"
      "  - {name: E537_xF_0.2_0.3,     file: E537_xF_0.2_0.3.yaml}\n"
      "  - {name: E537_xF_0.3_0.4,     file: E537_xF_0.3_0.4.yaml}\n"
      "  - {name: E537_xF_0.4_0.5,     file: E537_xF_0.4_0.5.yaml}\n"
      "  - {name: E537_xF_0.5_0.6,     file: E537_xF_0.5_0.6.yaml}\n"
      "  - {name: E537_xF_0.6_0.7,     file: E537_xF_0.6_0.7.yaml}\n"
      "  - {name: E537_xF_0.7_0.8,     file: E537_xF_0.7_0.8.yaml}\n"
      "  - {name: E537_xF_0.8_0.9,     file: E537_xF_0.8_0.9.yaml}\n"
      "  - {name: E537_xF_0.9_1.0,     file: E537_xF_0.9_1.0.yaml}\n";
  }
}
