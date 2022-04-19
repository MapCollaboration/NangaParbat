/*
 * Author: Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
 */

#include "NangaParbat/preprocessing.h"
#include "NangaParbat/listdir.h"
#include "NangaParbat/tostringwprecision.h"

#include <yaml-cpp/yaml.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>


namespace NangaParbat
{

  //_________________________________________________________________________________
  std::string PreprocessCOMPASS(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing COMPASS data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HEPData-ins1624692-v1-yaml/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process:
    // get all the files in RawDataFolder and remove 'submission.yaml' from the list
    std::vector<std::string> tables = NangaParbat::list_dir(RawDataFolder);
    std::vector<std::string>::iterator result = find(tables.begin(), tables.end(), "submission.yaml");
    // If result points to tables.end() it couldn't find the string to erase so it can't be deleted.
    if (result == tables.end())
      std::cout << "submission.yaml is not in the rawdata folder!" << std::endl;
    else
      tables.erase(result);

    // Output folder
    const std::string ofolder = "COMPASS";

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Vector for output names
    std::vector<std::string> filenames;
    std::map<std::string, bool> namecommented;

    // Our cuts on z and x
    const double zlower = 0.2;
    const double zupper = 0.7;
    const double xupper = 0.8;
    const double Qlower = 1.4;
    // const double Qlower = 1.1832; // original PV17 cut, Q2 > 1.4 GeV2

    std::cout << "\033[1;37mDatasets that do not pass the following cuts are commented in datasets.yaml"  << std::endl;
    std::cout << "\033[1;37mApplied cuts:"  << std::endl;
    std::cout << "\033[1;37m- z:  ["        << zlower << ": " << zupper << "]" << std::endl;
    std::cout << "\033[1;37m- x:  [1e-05: " << xupper << "]\033[0m" << std::endl;
    std::cout << "\033[1;37m- Q > " << Qlower << "\n\033[0m" << std::endl;

    // Comment (or not) datafile name in datafiles.yaml.
    /* --- If a bin does not pass the cut we impose,
    (e.g. the bin z: [0.1, 0.2] is  generally too low
    to be included in a fit), produce the datafile
    but comment it in datasets.yaml. --- */
    bool comment = false;

    // Loop over tables
    for (auto const& tab : tables)
      {
        if (tab == "." || tab == "..")
          continue;
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + tab);

        for (auto const& str : exp["dependent_variables"])
          if (str["header"]["name"].as<std::string>() == "$M^{h^{-}}$" ||
              str["header"]["name"].as<std::string>() == "$M^{h^{+}}$")
            {
              std::string hcharge = str["header"]["name"].as<std::string>();
              hcharge.erase(std::remove(hcharge.begin(), hcharge.end(), '$'), hcharge.end());

              // Initializate bins for kinematical values
              std::pair<double,double> xbin, zbin, Q2bin;

              // Central values
              double xcvalue, zcvalue, Q2cvalue;

              // Useful variables to read qualifiers
              double low, high;
              std::string dum, binplow, highp;

              // Get x (central value) with its bin
              for (auto const& it : str["qualifiers"])
                if (it["name"].as<std::string>() == "$x$")
                  {
                    const std::string xline = it["value"].as<std::string>();

                    // Create a stringstream of the current line
                    std::stringstream ss(xline);

                    // Extract each value in the line
                    // In data1.yaml there is an extra space to take into account
                    (tab == "data1.yaml" ? ss >> xcvalue >> dum >> low >> dum >> highp : ss >> xcvalue >> binplow >> dum >> highp);

                    /*
                    // Remove '(BIN=' from lower bound
                    std::size_t pos = binplow.find("(BIN=");
                    low = (tab == "data1.yaml" ? low : std::stod(binplow.substr(pos + 5)));

                    // Remove ')' from upper bound (last character)
                    high = std::stod(highp.substr(0, highp.size() - 1));
                    */

                    // xbin = {low, high} where '(BIN=' has been removed from the lower bound
                    // and ')' from the upper bound (last character).
                    std::size_t pos = binplow.find("(BIN=");
                    xbin = {(tab == "data1.yaml" ? low : std::stod(binplow.substr(pos + 5))), std::stod(highp.substr(0, highp.size() - 1))};

                  }

              // Get z (central value) with its bin
              for (auto const& it : str["qualifiers"])
                if (it["name"].as<std::string>() == "$z$")
                  {
                    const std::string zline = it["value"].as<std::string>();

                    // Create a stringstream of the current line
                    std::stringstream ss(zline);

                    // Extract each value in the line
                    // In data1.yaml there is an extra space to take into account
                    (tab == "data1.yaml" ? ss >> zcvalue >> dum >> low >> dum >> highp : ss >> zcvalue >> binplow >> dum >> highp);

                    // zbin = {low, high} where '(BIN=' has been removed from the lower bound
                    // and ')' from the upper bound (last character).
                    std::size_t pos = binplow.find("(BIN=");
                    zbin = {(tab == "data1.yaml" ? low : std::stod(binplow.substr(pos + 5))), std::stod(highp.substr(0, highp.size() - 1))};

                  }

              // Get Q2 (central value) with its bin
              for (auto const& it : str["qualifiers"])
                if (it["name"].as<std::string>() == "$Q^2$")
                  {
                    const std::string Q2line = it["value"].as<std::string>();

                    // Check rawdata: some tables have extra spaces and some others do not
                    // (i.e. "value: 4.5 (BIN= 3.0 TO  7.0)" WITH a space between
                    // "(BIN=" and the following number ).
                    std::size_t found = Q2line.find("(BIN= ");
                    const bool space = (found!= std::string::npos ? true : false);

                    // Create a stringstream of the current line
                    std::stringstream ss(Q2line);

                    // Extract each value in the line
                    (space ? ss >> Q2cvalue >> dum >> binplow >> dum >> highp : ss >> Q2cvalue >> binplow >> dum >> highp);

                    // Deal with scientific notation for lower bound
                    std::size_t pos = binplow.find("(BIN=");
                    std::istringstream lo(space ? binplow : binplow.substr(pos + 5));
                    lo >> low;

                    // Deal with scientific notation for upper bound
                    std::istringstream up(highp.substr(0, highp.size() - 1));
                    up >> high;

                    // Q2bin = {low, high} where '(BIN=' has been removed from the lower bound
                    // and ')' from the upper bound (last character).
                    Q2bin = {low, high};
                  }

              // Get y
              double y;
              for (auto const& it : str["qualifiers"])
                if (it["name"].as<std::string>() == "$y$")
                  y = it["value"].as<double>();

              // Comment datasets that do not pass the x cut, z cut or Q2 cut
              if (xcvalue > xupper)
                comment = true;

              if (zcvalue < zlower || zcvalue > zupper )
                comment = true;

              if (sqrt(Q2cvalue) < Qlower)
                comment = true;

              // Map for hadron names (output files)
              std::map<std::string, std::string> hadrons = {{"M^{h^{+}}", "Pp_Kp"}, {"M^{h^{-}}", "Pm_Km"}};

              // Map for hadron names (plot titles)
              std::map<std::string, std::string> hadtitle = {{"M^{h^{+}}", "$M^{h^{+}}$"}, {"M^{h^{-}}", "$M^{h^{-}}$"}};

              // Output file names
              std::string ofile = "COMPASS_Deu_" + hadrons[hcharge] + "_x_" + NangaParbat::to_string_with_precision(xcvalue, 4) + "_z_" + NangaParbat::to_string_with_precision(zcvalue);

              // Fill output vector string
              filenames.push_back(ofile);

              // Fill map <dataset name, commented or not in datasets.yaml>
              namecommented[ofile] = comment;

              // Open PDF-error file
              std::ifstream pdferr(PDFErrorFolder + ofile + ".out");
              std::string line;
              getline(pdferr, line);
              getline(pdferr, line);

              // Plot labels
              std::map<std::string, std::string> labels
              {
                {"xlabel", "#it{P}_{hT} [GeV]"},
                {"ylabel", hcharge + "#left(x, z, |{P}_{hT}|^2, Q^2 #right)"},
                {"title", "COMPASS, Deu  -  " + hadtitle[hcharge] + "   " + std::to_string(xbin.first) + " < x < " + std::to_string(xbin.second) + " , " + std::to_string(zbin.first) + " < |#it{z}| < " + std::to_string(zbin.second)},
                {"xlabelpy", "$P_{hT} \\rm{ [GeV]}$"},
                {"ylabelpy", "$" + hcharge + "\\left(x, z, |{P}_{hT}|^2, Q^2 \\right)$"},
                {"titlepy", "COMPASS, Deu - " + hadtitle[hcharge] + " \\\\ " + std::to_string(xbin.first) + " < x < " + std::to_string(xbin.second) + " , " + std::to_string(zbin.first) + " < z < " + std::to_string(zbin.second)}
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
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "process" << YAML::Key << "value" << YAML::Value << "SIDIS" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "observable" << YAML::Key << "value" << YAML::Value << "(dsigma/dxdzdQ2dPhT2)/dsigmaDIS" << YAML::EndMap;
              // "multiplicity" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 0.5 << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "hadron" << YAML::Key << "value" << YAML::Value << "HD" << YAML::EndMap;
              // (hcharge == "M^{h^{+}}" ? "Pp + Kp" : "Pm + Km") << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "charge" << YAML::Key << "value" << YAML::Value << (hcharge == "M^{h^{+}}" ? 1 : -1) << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
              // ### Square root of s, calculated as Vs = sqrt(2*M*Ee-) = sqrt(2*0.938*160 GeV) = 17.325
              // ### in PV17 Vs = 17.3
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 17.325 << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                   << "low" << YAML::Value << sqrt(Q2bin.first) << YAML::Key << "high" << YAML::Value << sqrt(Q2bin.second) << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "x" << YAML::Key
                   << "low" << YAML::Value << xbin.first << YAML::Key << "high" << YAML::Value << xbin.second << YAML::Key << "integrate" << YAML::Value << "true" // << YAML::Key << "value" << YAML::Value << xcvalue
                   << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "z" << YAML::Key
                   << "low" << YAML::Value << zbin.first << YAML::Key << "high" << YAML::Value << zbin.second << YAML::Key << "integrate" << YAML::Value << "true" // << YAML::Key << "value" << YAML::Value << zcvalue
                   << YAML::EndMap;
              emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                   << "W"  << YAML::Value << 5
                   << "ymin" << YAML::Value << 0.1 << YAML::Key << "ymax" << YAML::Value << 0.9
                   << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (auto const& m : str["values"])
                {
                  emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << m["errors"][0]["symerror"].as<double>() << YAML::EndMap;
                  if (PDFError)
                    {
                      // Now read PDF errors
                      getline(pdferr, line);
                      std::stringstream stream(line);
                      double dum, pe;
                      stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

                      // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
                    }
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << m["errors"][1]["symerror"] << YAML::EndMap; // read systematic errors from HEPdata file
                  // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << "###" << YAML::EndMap;
                  emit << YAML::EndSeq;
                  emit << YAML::Key << "value" << YAML::Value << m["value"].as<double>();
                  emit << YAML::EndMap;
                }
              emit << YAML::EndSeq;
              emit << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::Key << "independent_variables";
              emit << YAML::BeginSeq;
              emit << YAML::BeginMap;
              emit << YAML::Key << "header" << YAML::Value << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PhT" << YAML::Key
                   << "units" << YAML::Value << "GeV" << YAML::EndMap;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (auto const& iv : exp["independent_variables"])
                for (auto const& vl : iv["values"])
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << sqrt(vl["high"].as<double>()) << YAML::Key << "low" << YAML::Value << std::max(sqrt(vl["low"].as<double>()), 1e-5) << YAML::Key << "value" << YAML::Value << sqrt(vl["value"].as<double>()) << YAML::Key << "factor" << YAML::Value << (sqrt(vl["high"].as<double>()) - std::max(sqrt(vl["low"].as<double>()), 1e-5)) / (vl["high"].as<double>() - pow(std::max(sqrt(vl["low"].as<double>()), 1e-5), 2)) << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::EndMap;
              emit << YAML::BeginMap;
              emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "x" << YAML::EndMap;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (int i = 0; i < (int) str["values"].size(); ++i )
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << xbin.second << YAML::Key << "low" << YAML::Value << xbin.first << YAML::Key << "value" << YAML::Value << xcvalue << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::EndMap;
              emit << YAML::BeginMap;
              emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "z" << YAML::EndMap;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (int i = 0; i < (int) str["values"].size(); ++i )
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << zbin.second << YAML::Key << "low" << YAML::Value << zbin.first << YAML::Key << "value" << YAML::Value << zcvalue << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::EndMap;
              emit << YAML::BeginMap;
              emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::EndMap;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (int i = 0; i < (int) str["values"].size(); ++i )
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << 0.9 << YAML::Key << "low" << YAML::Value << 0.1 << YAML::Key << "value" << YAML::Value << y << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::EndMap;
              emit << YAML::BeginMap;
              emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q2" << YAML::EndMap;
              emit << YAML::Key << "values" << YAML::Value;
              emit << YAML::BeginSeq;
              for (int i = 0; i < (int) str["values"].size(); ++i )
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << Q2bin.second << YAML::Key << "low" << YAML::Value << Q2bin.first << YAML::Key << "value" << YAML::Value << Q2cvalue << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::EndMap;
              emit << YAML::EndSeq;
              emit << YAML::EndMap;

              // Close PDF-error file
              pdferr.close();

              // Dump table to file
              std::ofstream fout(opath + "/" + ofile + ".yaml");
              fout << emit.c_str() << std::endl;
              fout.close();

              // Reset comment for the following dataset
              comment = false;
            }

      }

    // Sort datafiles names
    std::sort(filenames.begin(), filenames.end());

    // Produce outputnames to put in datasets.yaml
    std::string outputnames;
    for (std::string name : filenames)
      outputnames += (namecommented[name] ? "#  - {name: " : "  - {name: ") + name + ", file: " + name + ".yaml}\n";

    return outputnames;
  }
}
