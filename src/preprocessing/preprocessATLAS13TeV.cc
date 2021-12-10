/*
 * Author: Matteo Cerutti
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
  std::string PreprocessATLAS13TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing ATLAS 13 TeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins1768911-v2-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {{"table4_a.yaml"}, {"table4_b.yaml"}};

    // Output folder
    const std::string ofolder = "ATLAS";

    // Output file
    const std::string ofile = "ATLAS_13TeV.yaml";

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

          // If the name is "Dressed" continue with the next block
          // if (dv["header"]["name"].as<std::string>() == "$k_{dressed}$")
          //   continue;

          if (dv["header"]["units"])
            {
              // Open PDF-error file
              std::ifstream pdferr(PDFErrorFolder + "ATLAS_13TeV.out");
              std::string line;
              getline(pdferr, line);
              getline(pdferr, line);

              // Plot labels
              std::map<std::string, std::string> labels
              {
                {"xlabel", "#it{q}_{T} [GeV]"},
                {"ylabel", "#frac{1}{#it{#sigma}} #frac{d#it{#sigma}}{d#it{q}_{T}}  [GeV^{-1}]"},
                {"title", "ATLAS at 13 TeV, 66 GeV < Q < 116 GeV, |#it{y}| < 2.5"},
                {"xlabelpy", "$q_T \\rm{ [GeV]}$"},
                {"ylabelpy", "$\\frac{1}{\\sigma}\\frac{d\\sigma}{dq_{T}}[\\rm{GeV}^{-1}]$"},
                {"titlepy", "ATLAS at 13 TeV, 66 GeV < Q < 116 GeV, $|y|$ < 2.5"}
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
                   << "low" << YAML::Value << 66 << YAML::Key << "high" << YAML::Value << 116 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                   << "low" << YAML::Value << 0 << YAML::Key << "high" << YAML::Value << 2.5 << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                   << "pTmin" << YAML::Value << 27 << YAML::Key << "etamin" << YAML::Value << -2.5 << YAML::Key << "etamax" << YAML::Value << 2.5 << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              int it = 0;
              for (auto const& v : dv["values"])
                {
                  std::string cerr = v["errors"][0]["symerror"].as<std::string>();
                  std::string uerr = v["errors"][1]["symerror"].as<std::string>();

                  cerr.erase(std::remove(cerr.begin(), cerr.end(), '%'), cerr.end());
                  uerr.erase(std::remove(uerr.begin(), uerr.end(), '%'), uerr.end());


                  const double val = v["value"].as<double>();
                  const double unc = val * std::stod(uerr) / 100;
                  const double cor = std::stod(cerr) / 100;


                  // Now read PDF errors
                  getline(pdferr, line);
                  std::stringstream stream(line);
                  double dum, pe;
                  stream >> dum >> dum >> dum >> dum >> dum >> pe >> dum;

                  // Vectors of uncorrelated and correlated errors
                  // from article https://arxiv.org/pdf/1606.05864.pdf Tab.4
                  // std::vector<double> uncart = {0.00184452597, 0.00254048238, 0.0024849562, 0.00223087769, 0.002096844359, 0.00181079344, 0.00170785626, 0.00153076104, 0.00047904096, 0.000357489585, 0.000284907396, 0.000140513793, 9.2774641399999996e-05, 6.4174134500000004e-05, 2.75466744e-05, 1.8862854690000001e-05, 6.1849813950000005e-06, 1.957222454e-06};
                  // std::vector<double> addart = {0.0274, 0.0138, 0.005, 0.0134, 0.0274, 0.0233, 0.0130, 0.0165, 0.0041, 0.067, 0.0129, 0.0156, 0.0272, 0.0357, 0.0372, 0.0201, 0.1166, 0.0209};

                  emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value"
                       << YAML::Value << unc << YAML::EndMap;
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value"
                            << YAML::Value << cor << YAML::EndMap;
                  // << YAML::Value << v["errors"][0]["symerror"].as<double>()<< YAML::EndMap; // read unc errors from HEPData file
                  if (PDFError)
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;

                  emit << YAML::EndSeq;
                  emit << YAML::Key << "value" << YAML::Value << val;
                  emit << YAML::EndMap;
                  it++;
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
    return "  - {name: ATLAS_13TeV, file: ATLAS_13TeV.yaml}\n";
  }
}
