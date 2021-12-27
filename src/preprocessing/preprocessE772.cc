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
  std::string PreprocessE772(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing E772 data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins372414-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::string ofolder = "E772";
    // std::cout <<  "Prima di tables" << std::endl;
    const std::vector<std::string> tables = {{"Table5.yaml"}, {"Table6.yaml"}};
    // std::cout <<  "Dopo tables" << std::endl;

    // Initialize naming map for the Q-integration ranges
    std::map<std::string, std::string> enranges = {{"5.5", "_Q_5_6"},{"6.5", "_Q_6_7"},  {"7.5", "_Q_7_8"}, {"8.5", "_Q_8_9"}, {"11.5", "_Q_11_12"}, {"12.5", "_Q_12_13"}, {"13.5", "_Q_13_14"}, {"14.5", "_Q_14_15"}};

    std::map<std::string, std::pair<std::string, std::string>> enrangelims = {{"5.5", {"5", "6"}}, {"6.5", {"6", "7"}}, {"7.5", {"7", "8"}}, {"8.5", {"8", "9"}}, {"11.5", {"11", "12"}}, {"12.5", {"12", "13"}}, {"13.5", {"13", "14"}}, {"14.5", {"14", "15"}}};

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        // std::cout <<  "Prima di leggere" << std::endl;
        // std::cout <<  RawDataFolder + tab << std::endl;
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);
        // std::cout <<  "Dopo aver letto la tabella" << std::endl;

        // Get qT bin bounds
        std::vector<std::pair<double,double>> qTb;
        for (auto const& iv : exp["independent_variables"])
          for (auto const& vl : iv["values"])
            qTb.push_back(std::make_pair(-1, vl["value"].as<double>()));

        // Run over the energy ranges
        for (auto const& dv : exp["dependent_variables"])
          {
            std::string ofile;
            std::pair<std::string, std::string> enlims;
            double y = 0;
            double ymin = 0;
            double ymax = 0;
            const double xFmin = 0.1;
            const double xFmax = 0.3;
            double Qav = 0;
            // const double Vs = sqrt(2*(0.9383 + 0.9395)*800);
            const double Vs = sqrt(2 * 0.9383 * 800);
            for (auto const& q : dv["qualifiers"])
              {
                if (q["name"].as<std::string>() == "M")
                  {
                    ofile  = ofolder + enranges[q["value"].as<std::string>()];
                    enlims = enrangelims[q["value"].as<std::string>()];
                    Qav = ( std::stod(enlims.first) + std::stod(enlims.second) ) / 2;
                    ymin = log(Vs * ( xFmin + sqrt( pow(xFmin, 2) + pow(2 * Qav / Vs, 2 ) ) ) / 2 / Qav );
                    ymax = log(Vs * ( xFmax + sqrt( pow(xFmax, 2) + pow(2 * Qav / Vs, 2 ) ) ) / 2 / Qav );
                    y = ( ymin + ymax ) / 2;
                  }
              }

            // Open PDF-error file
            std::ifstream pdferr(PDFErrorFolder + ofile + ".out");
            std::string line;
            getline(pdferr, line);
            getline(pdferr, line);

            ofile += ".yaml";

            // Overall factor
            const double factor = (Qav * cosh(y) )/ M_PI / Vs / (xFmax - xFmin);

            // Plot labels
            std::map<std::string, std::string> labels
            {
              {"xlabel", "#it{q}_{T} [GeV]"},
              {"ylabel", "#it{E} #frac{d^{3}#it{#sigma}}{d^{3}#it{q}}  [pb GeV^{-2}]"},
              {
                "title", "E772, "
                + enlims.first + " GeV < Q < "
                + enlims.second + " GeV, 0.1 < #it{x}_{F} < 0.3"
              },
              {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
              {"ylabelpy", "$\\rm{E }\\frac{d^{3}\\sigma}{d^{3}q}{[\\rm{pb GeV}^{-2}]}$"},
              {
                "titlepy", "E772, "
                + enlims.first + " GeV < Q < "
                + enlims.second + " GeV, 0.1 < $x_{F}$ < 0.3"
              }
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
            emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 0.5 << YAML::EndMap;
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
                // Now read PDF errors
                getline(pdferr, line);
                std::stringstream stream(line);
                double dum, pe = 0;
                // stream >> dum >> dum >> dum >> dum >> dum >> pe >> dum;
                stream >> dum >> dum >> dum >> dum >> pe >> dum;

                if (v["value"].as<std::string>() != "-")
                  {
                    const double val = v["value"].as<double>();
                    // const double uncsys = 0.10 * val;
                    // // sum of statistical and systematic errors
                    // const double unc = sqrt( pow(v["errors"][0]["symerror"].as<double>(), 2) + pow(uncsys, 2) );
                    emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << v["errors"][0]["symerror"].as<double>() << YAML::EndMap;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0.1 * val << YAML::EndMap;
                    if (PDFError)
                      emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << std::max(pe, 0.0) << YAML::EndMap;
                    // [TEMPORARY] Simulation of the correlated error associated to collinear PDFs
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.10 << YAML::EndMap;
                    //[TEMPORARY] trial of introduction of new theoretical error
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0.01 * val << YAML::EndMap;
                    emit << YAML::EndSeq;
                    emit << YAML::Key << "value" << YAML::Value << val;
                    emit << YAML::EndMap;
                  }

                if (v["value"].as<std::string>() == "-")
                  {
                    const double val = 0;
                    const double unc = 0.1;
                    // const double unc = v["errors"][0]["symerror"].as<double>();
                    emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << unc << YAML::EndMap;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.1 << YAML::EndMap;
                    // Simulation of the correlated error associated to collinear PDFs
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.10 << YAML::EndMap;
                    //[TEMPORARY] trial of introduction of new theoretical error
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0.005 * val << YAML::EndMap;
                    emit << YAML::EndSeq;
                    emit << YAML::Key << "value" << YAML::Value << val;
                    emit << YAML::EndMap;
                  }

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
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "value" << YAML::Value << qT.second
                   << YAML::Key << "factor" << YAML::Value << 1. / qT.second << YAML::EndMap;
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
      "  - {name: E772_Q_5_6,       file: E772_Q_5_6.yaml}\n"
      "  - {name: E772_Q_6_7,       file: E772_Q_6_7.yaml}\n"
      "  - {name: E772_Q_7_8,       file: E772_Q_7_8.yaml}\n"
      "  - {name: E772_Q_8_9,       file: E772_Q_8_9.yaml}\n"
      "  - {name: E772_Q_11_12,     file: E772_Q_11_12.yaml}\n"
      "  - {name: E772_Q_12_13,     file: E772_Q_12_13.yaml}\n"
      "  - {name: E772_Q_13_14,     file: E772_Q_13_14.yaml}\n"
      "  - {name: E772_Q_14_15,     file: E772_Q_14_15.yaml}\n";
  }
}
