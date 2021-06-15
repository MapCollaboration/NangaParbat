/*
 * Authors: Simone Venturini
 *          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
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
  std::string PreprocessE537(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing E537 data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins253413-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"Table5.yaml"};

    // Output folder for preprocessed data
    const std::string ofolder = "E537";

    // Initialize naming map for the Q-integration ranges
    std::map<std::string, std::string> Qranges = {{"4.0TO4.5", "_Q_4.0_4.5"}, {"4.5TO5.0", "_Q_4.5_5.0"}, {"5.0TO5.5", "_Q_5.0_5.5"}, {"5.5TO6.0", "_Q_5.5_6.0"}, {"6.0TO6.5","_Q_6.0_6.5"}, {"6.5TO7.0", "_Q_6.5_7.0"}, {"7.0TO7.5", "_Q_7.0_7.5"}, {"7.5TO8.0", "_Q_7.5_8.0"}, {"8.0TO8.5", "_Q_8.0_8.5"}, {"8.5TO9.0", "_Q_8.5_9.0"}};
    std::map<std::string, std::pair<std::string, std::string>> Qrangelims = {{"4.0TO4.5", {"4", "5"}}, {"4.5TO5.0", {"4.5", "5.0"}}, {"5.0TO5.5", {"5", "5.5"}}, {"5.5TO6.0", {"5.5", "6"}}, {"6.0TO6.5", {"6", "6.5"}}, {"6.5TO7.0", {"6.5", "7"}}, {"7.0TO7.5", {"7", "7.5"}}, {"7.5TO8.0", {"7.5", "8"}}, {"8.0TO8.5", {"8", "8.5"}}, {"8.5TO9.0", {"8.5", "9"}}};
    std::map<std::string, std::pair<double,double>> Qextremes= {{"4.0TO4.5", {4, 4.5}}, {"4.5TO5.0", {4.5, 5.0}}, {"5.0TO5.5", {5.0, 5.5}}, {"5.5TO6.0", {5.5, 6.0}}, {"6.0TO6.5", {6.0, 6.5}}, {"6.5TO7.0", {6.5, 7.0}}, {"7.0TO7.5", {7.0, 7.5}}, {"7.5TO8.0", {7.5, 8.0}}, {"8.0TO8.5", {8.0, 8.5}}, {"8.5TO9.0", {8.5, 9.0}}};

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

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            /*
            NOTE on the calculation of y_min and y_max: y = arcsinh(sqrt{s}*xF/(2Q)).
            The value of x_min = - 0.1, then y_min = arcsinh(-0.1*sqrt(s)/(2 Q_max)) for a specific Qmin < Q < Qmax bin
            x_max = 1, then y_max = arcsinh(sqrt(s)/(2 Q_min)) for a specific Qmin < Q < Qmax bin
            */

            // Define the minimum and the maximum value of y
            double Qexmin, Qexmax;
            double y_min, y_max;

            std::string ofile;
            std::pair<std::string, std::string> Qlims;
            std::pair<double, double> Qestremi;
            std::string level;

            for (auto const& q : dv["qualifiers"])
              if (q["name"].as<std::string>() == "M(P=3 4)")
                {
                  ofile    = ofolder + Qranges[q["value"].as<std::string>()];
                  Qlims    = Qrangelims[q["value"].as<std::string>()];
                  Qestremi = Qextremes[q["value"].as<std::string>()];
                  Qexmin   = Qestremi.first;
                  Qexmax   = Qestremi.second;
                  y_min    = asinh((- 0.1 * 125) / (2 * Qexmax));
                  y_max    = asinh(125 / (2 * Qexmin));
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
              {"xlabel", "#it{q}_{T} [GeV]"},
              {"ylabel", "#frac{d2#it{#sigma}}{d#it{q}_{T}d#it{p}_{T}^2}  [GeV^{-3}]"},
              {"title", "E537 at 125 GeV, " + Qlims.first + " GeV < Q < " + Qlims.second + " GeV," + std::to_string(y_min) + "< |#it{y}| < " +std::to_string(y_max)},
              {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
              {"ylabelpy", "$\\frac{d2\\sigma}{dq_{T}dp_{T}^2}[\\rm{GeV}^{-3}]$"},
              {"titlepy", "E537 at 125 GeV, " + Qlims.first + " GeV < Q <" + Qlims.second + "GeV, " + std::to_string(y_min) + " < $|y|$ < " +std::to_string(y_max)}
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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "beam" << YAML::Key << "value" << YAML::Value << "PI" << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 125 << YAML::EndMap;
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                 << "low" << YAML::Value << Qlims.first << YAML::Key << "high" << YAML::Value << Qlims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
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
                const double unc = std::max(std::stod(stat), 1e-05);

                const double val = v["value"].as<double>();

                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe;
                stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

                emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                if (PDFError)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0 << YAML::EndMap;
                  /* !! When PDF uncertainties will be available, use the line below instead of the one above !! */
                  // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
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
      "  - {name: E537_Q_4.0_4.5,      file: E537_Q_4.0_4.5.yaml}\n"
      "  - {name: E537_Q_4.5_5.0,      file: E537_Q_4.5_5.0.yaml}\n"
      "  - {name: E537_Q_5.0_5.5,      file: E537_Q_5.0_5.5.yaml}\n"
      "  - {name: E537_Q_5.5_6.0,      file: E537_Q_5.5_6.0.yaml}\n"
      "  - {name: E537_Q_6.0_6.5,      file: E537_Q_6.0_6.5.yaml}\n"
      "  - {name: E537_Q_6.5_7.0,      file: E537_Q_6.5_7.0.yaml}\n"
      "  - {name: E537_Q_7.0_7.5,      file: E537_Q_7.0_7.5.yaml}\n"
      "  - {name: E537_Q_7.5_8.0,      file: E537_Q_7.5_8.0.yaml}\n"
      "  - {name: E537_Q_8.0_8.5,      file: E537_Q_8.0_8.5.yaml}\n"
      "  - {name: E537_Q_8.5_9.0,      file: E537_Q_8.5_9.0.yaml}\n";
  }
}
