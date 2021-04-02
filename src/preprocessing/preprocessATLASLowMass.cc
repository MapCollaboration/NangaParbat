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
  std::string PreprocessATLASLowMass(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing ATLAS 13 TeV data to make predictions ..." << std::endl;

    /*
    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath;
    */

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Initialize Q-integration ranges
    const std::vector<std::pair<int, int>> Qrangelims = {{12, 14}, {14, 17}, {17, 22}, {22, 28}, {28, 36}, {36, 46}, {46, 56}};

    // qT bin bounds
    const std::vector<std::pair<double,double>> qTb = {{0, 1.5}, {1.5, 3}, {3, 5}, {5, 10}, {10, 16}, {16, 22}, {22, 30}, {30, 40}, {40, 55}, {55, 85}};

    // Square root of s
    const int Vs = 13000;

    // Vector of tables to process
    const std::string ofolder = "ATLASLowMass";

    // Create output directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    for (auto Qlims : Qrangelims)
      {
        std::string ofile = ofolder + "_13TeV_Q_" + std::to_string(Qlims.first) + "_" + std::to_string(Qlims.second);

        // Open PDF-error file
        std::ifstream pdferr(PDFErrorFolder + ofile + ".out");
        std::string line;
        getline(pdferr, line);
        getline(pdferr, line);

        ofile += ".yaml";

        const double ymax = log(Vs / Qlims.first);

        // Plot labels
        std::map<std::string, std::string> labels
        {
          {"xlabel", "#it{q}_{T} [GeV]"},
          {"ylabel", "#frac{1}{#it{#sigma}} #frac{d#it{#sigma}}{d#it{q}_{T}}  [GeV^{-1}]"},
          {"title", "ATLAS at 13 TeV, " + std::to_string(Qlims.first) + " GeV < Q < " + std::to_string(Qlims.second) + " GeV, |#it{y}| < " + std::to_string(ymax)},
          {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
          {"ylabelpy", "$\\frac{1}{\\sigma}\\frac{d\\sigma}{dq_{T}}[\\rm{GeV}^{-1}]$"},
          {"titlepy", "ATLAS at 13 TeV, " + std::to_string(Qlims.first) + " GeV < Q < " + std::to_string(Qlims.second) + " GeV, $|y|$ < " + std::to_string(ymax)}
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
        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 13000 << YAML::EndMap;
        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
             << "low" << YAML::Value << Qlims.first << YAML::Key << "high" << YAML::Value << Qlims.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
             << "low" << YAML::Value << 0 << YAML::Key << "high" << YAML::Value << ymax << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
             << "pTmin" << YAML::Value << 4.5 << YAML::Key << "etamin" << YAML::Value << -2.4 << YAML::Key << "etamax" << YAML::Value << 2.4 << YAML::EndMap;
        emit << YAML::EndSeq;
        emit << YAML::Key << "values" << YAML::Value;
        emit << YAML::BeginSeq;
        for (int i = 0; i < qTb.size(); i++)
          {
            // Read PDF errors
            getline(pdferr, line);
            std::stringstream stream(line);
            double dum, pe;
            stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

            emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
            // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0 << YAML::EndMap;
            if (PDFError)
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0 << YAML::EndMap;
              // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
            // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << 0 << YAML::EndMap;
            emit << YAML::EndSeq;
            emit << YAML::Key << "value" << YAML::Value << 0;
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

    return
      "  - {name: ATLAS_13TeV_Q_12_14,   file: ATLAS_13TeV_Q_12_14.yaml}\n"
      "  - {name: ATLAS_13TeV_Q_14_17,   file: ATLAS_13TeV_Q_14_17.yaml}\n"
      "  - {name: ATLAS_13TeV_Q_17_22,   file: ATLAS_13TeV_Q_17_22.yaml}\n"
      "  - {name: ATLAS_13TeV_Q_22_28,   file: ATLAS_13TeV_Q_22_28.yaml}\n"
      "  - {name: ATLAS_13TeV_Q_28_36,   file: ATLAS_13TeV_Q_28_36.yaml}\n"
      "  - {name: ATLAS_13TeV_Q_36_46,   file: ATLAS_13TeV_Q_36_46.yaml}\n"
      "  - {name: ATLAS_13TeV_Q_46_56,   file: ATLAS_13TeV_Q_46_56.yaml}\n";
  }
}
