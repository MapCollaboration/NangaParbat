/*
 * Author: Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
 */

#include "NangaParbat/preprocessing.h"

#include <yaml-cpp/yaml.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <algorithm>  // erase-remove idiom in Linux

namespace NangaParbat
{

  //_________________________________________________________________________________
  std::string PreprocessHERMES(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError, bool const& FFError)
  {
    std::cout << "Processing HERMES data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/HERMES/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/SIDIS/N3LL/HERMES/";

    // Path to the FF-error folder
    const std::string FFErrorFolder = RawDataPath + "/FFErrors/N3LL/HERMES/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"hermes.deuteron.zxpt-3D.vmsub.mults_kminus.list", "hermes.deuteron.zxpt-3D.vmsub.mults_kplus.list", "hermes.deuteron.zxpt-3D.vmsub.mults_piminus.list", "hermes.deuteron.zxpt-3D.vmsub.mults_piplus.list", "hermes.proton.zxpt-3D.vmsub.mults_kminus.list", "hermes.proton.zxpt-3D.vmsub.mults_kplus.list", "hermes.proton.zxpt-3D.vmsub.mults_piminus.list", "hermes.proton.zxpt-3D.vmsub.mults_piplus.list"};

    // Output folder
    const std::string ofolder = "HERMES";

    // Vector for output names
    std::vector<std::string> datafilestrings;

    // Initialize naming map for the z-integration ranges (the first element is for the name of the output data file)
    // (from http://hermesmults.appspot.com/, section Balanced Binning)
    const std::map<std::string, std::pair<double, double>> zrangelims = {{"_z_0.1_0.2", {0.1, 0.2}}, {"_z_0.2_0.25", {0.2, 0.25}}, {"_z_0.25_0.3", {0.25, 0.3}}, {"_z_0.3_0.375", {0.3, 0.375}}, {"_z_0.375_0.475", {0.375, 0.475}}, {"_z_0.475_0.6", {0.475, 0.6}}, {"_z_0.6_0.8", {0.6, 0.8}}, {"_z_0.8_1.1", {0.8, 1.1}}};

    // Initialize map for the x-integration ranges
    // (from http://hermesmults.appspot.com/, section Balanced Binning)
    const std::map<std::string, std::pair<double, double>> xrangelims = {{"_x_0.023_0.047", {0.023, 0.047}}, {"_x_0.047_0.075", {0.047, 0.075}}, {"_x_0.075_0.12", {0.075, 0.12}}, {"_x_0.12_0.2", {0.12, 0.2}}, {"_x_0.2_0.35", {0.2, 0.35}}, {"_x_0.35_0.6", {0.35, 0.6}}};

    // Initialize naming map for the Php-integration ranges
    // (from http://hermesmults.appspot.com/, section Balanced Binning)
    const std::vector<std::pair<double, double>> Phplims = {{0.0, 0.15}, {0.15, 0.25}, {0.25, 0.35}, {0.35, 0.45}, {0.45, 0.6}, {0.6, 0.8}, {0.8, 1.2}};

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Our cuts on z and x
    const double zlower = 0.2;
    const double zupper = 0.7;
    const double xupper = 0.8;
    const double Qlower = 1.4;
    // const double Qlower = 1.1832;  // original PV17 cut, Q^2 > 1.4 GeV^2

    std::cout << "\033[1;37mDatasets that do not pass the following cuts are commented in datasets.yaml"  << std::endl;
    std::cout << "\033[1;37mApplied cuts:"  << std::endl;
    std::cout << "\033[1;37m- z:  ["        << zlower << ": " << zupper << "]" << std::endl;
    std::cout << "\033[1;37m- x:  [1e-05: " << xupper << "]\033[0m" << std::endl;
    std::cout << "\033[1;37m- Q > " << Qlower << "\n\033[0m" << std::endl;

    // Loop over tables
    for (auto const& tab : tables)
      {
        // Reading table with YAML
        const YAML::Node exp = YAML::LoadFile(RawDataFolder + "/" + tab);

        // Create an input filestream
        std::ifstream rawfile(RawDataFolder + tab);

        // Make sure the file is open
        if(!rawfile.is_open()) throw std::runtime_error("Could not open file");

        // Dummy variables to read columns
        std::string line;
        int vindex;
        double vmult, vstat, vsyst, vQ2, vx, vz, vPhp;

        // Create map to store the data
        std::map<std::string, std::map<int, double>> data;

        //  Create inner maps, one for each column of interest in the rawdatafile
        std::map<int, double> imult, istat, isyst, iQ2, ix, iz, iPhp;

        // The first 35 lines of the raw data files are headers, (34 + 1 for column names).
        // Skip those lines and start reading data.
        if(rawfile.good())
          {
            while(std::getline(rawfile, line))
              {
                // If the line starts whith #, skip it.
                // (They are comments in the header of the rawdata file).
                if (line[0] == '#')
                  continue;

                // Read data.
                // Create a stringstream of the current line
                std::stringstream ss(line);

                // Extract each value in the line
                ss >> vindex >> vmult >> vstat >> vsyst >> vQ2 >> vx >> vz >> vPhp;

                // Construct maps of index and values.
                // This is done so that the separation between values in bins can be done by index.
                imult[vindex]  = vmult;
                istat[vindex]  = vstat;
                isyst[vindex]  = vsyst;
                iQ2[vindex]    = vQ2;
                ix[vindex]     = vx;
                iz[vindex]     = vz;
                iPhp[vindex]   = vPhp;
              }
          }

        // Now that all lines have been read and the inner maps are filled,
        // put them in the correct column of the data outer map.
        data["mult"] = imult;
        data["stat"] = istat;
        data["syst"] = isyst;
        data["Q2"]   = iQ2;
        data["x"]    = ix;
        data["z"]    = iz;
        data["Php"]  = iPhp;

        // Maps for target and hadron names
        std::map<std::string, std::string> targets = {{"deuter", "_Deu"}, {"proton", "_Pro"}};
        std::map<std::string, std::string> hadrons = {{"kminus.list", "_Km"}, {"kplus.list", "_Kp"}, {"piminus.list", "_Pim"}, {"piplus.list", "_Pip"}};
        std::string hadtype;
        if (tab.find("piplus") != std::string::npos ||  tab.find("piminus") != std::string::npos)
          hadtype = "PI";
        else
          hadtype = "KA";

        // Start composing output file name
        std::size_t pos = tab.find("mults_");
        std::string ofile = "HERMES" + targets[tab.substr(7,6)] + hadrons[tab.substr(pos + 6)];

        // Comment (or not) datafile name in datafiles.yaml.
        /* --- If a bin does not pass the cut we impose,
        (e.g. the bin z: [0.1, 0.2] is  generally too low
        to be included in a fit), produce the datafile
        but comment it in datasets.yaml. --- */
        bool comment = false;

        // Conditions to separate the values in the columns into different files.
        // Loop on x bin boundaries.
        for (auto const& xb : xrangelims)
          {
            // File name picks up the x boundaries
            std::string ofileX = ofile + xb.first;

            // Initialize indexes vector for future selection
            std::vector<int> indexesX;
            double xvalue;

            // Select x bin
            for (auto const& ix : data["x"])
              // data["x"] is a map <index, x value> of all the values in the original table,
              // so ix.first is the index (int) and ix.second the value (double).
              if (ix.second > xb.second.first && ix.second < xb.second.second)
                {
                  // Store indexes
                  indexesX.push_back(ix.first);

                  // Get x value
                  xvalue = ix.second;

                  // Apply x cut (aim: reproduce PV17)
                  if (ix.second > xupper)
                    comment = true;
                }

            // Loop on z bin boundaries
            for (auto const& zb : zrangelims)
              {
                // Prepare (outer) map for each output data file
                std::map<std::string, std::map<int, double>> filedata;

                // File name picks up the z boundaries
                std::string ofileXZ = ofileX + zb.first;

                // Initialize indexes vector for future selection and z inner map
                std::vector<int> indexesZ;
                std::map<int, double> fdz;

                // Select data
                for (int i : indexesX)
                  {
                    if (data["z"][i] > zb.second.first && data["z"][i] < zb.second.second)
                      {
                        // Fill inner map with selected values (bin)
                        fdz[i] = data["z"][i];

                        // Store indexes
                        indexesZ.push_back(i);

                        // Apply our z cut to avoid including in the
                        // fit too low or too high z values. The cut is
                        // applied on the z mean values, therefore, for examples
                        // in the case of z bin = [0.6, 0.8] with a  z = 0.7
                        // cut, if none of the actual z mean values is above
                        // 0.7 the bin is included, otherwise is commented.
                        if (data["z"][i] < zlower || data["z"][i] > zupper )
                          comment = true;
                      }

                    // z bin outer map
                    filedata["z"] = fdz;
                  }

                // z values
                std::vector<double> zvalues;
                for (auto const& z : filedata["z"])
                  zvalues.push_back(z.second);

                // Initialize result maps
                std::map<int, double> fdmult, fdstat, fdsyst;

                // Finally select multiplicities and their uncertainties associated with this bin in (x,z).
                for (int n : indexesZ)
                  {
                    // Check on terminal
                    // std::cout << zb.first << "  index = " << n << std::endl;

                    fdmult[n] = data["mult"][n];
                    fdstat[n] = data["stat"][n];
                    fdsyst[n] = data["syst"][n];
                  }

                filedata["mult"] = fdmult;
                filedata["stat"] = fdstat;
                filedata["syst"] = fdsyst;

                // Create Php vector of pairs for <bin min, bin max> and <index, exact value>.
                // It can not be a map because there may be two points within the same Php bin
                // and in that case there would be two equal keys (the bin boundaries).
                std::vector<std::pair<std::pair<double, double>, std::pair<int,double>>> Phpbinval;

                bool inPhTbin = false;
                std::vector<int> notinPhTbin;

                for (int n : indexesZ)
                  {
                    for (auto const& bin : Phplims)
                      if (data["Php"][n] > bin.first && data["Php"][n] < bin.second)
                        {
                          Phpbinval.push_back(std::make_pair(bin, std::make_pair(n, data["Php"][n])));
                          inPhTbin = true;
                        }
                    if(!inPhTbin)
                      notinPhTbin.push_back(n);
                  }

                for (int n : notinPhTbin)
                  {
                    indexesZ.erase(std::remove(indexesZ.begin(), indexesZ.end(), n), indexesZ.end());
                    filedata["z"].erase(n);
                    filedata["mult"].erase(n);
                  }


                // Open PDF-error file
                std::ifstream pdferr(PDFErrorFolder + ofileXZ + ".out");
                std::string line;
                getline(pdferr, line);
                getline(pdferr, line);

                // Open FF-error file
                std::ifstream fferr(FFErrorFolder + ofileXZ + ".out");
                std::string linef;
                getline(fferr, linef);
                getline(fferr, linef);

                // Plot labels
                std::map<std::string, std::string> labels
                {
                  {"xlabel", "#it{P}_{hT} [GeV]"},
                  {"ylabel", "M^{h}_{n}#left(x, z, |{P}_{hT}|, Q^2 #right)"},
                  {"title", "HERMES, " + targets[tab.substr(7,6)].substr(1) + "  -  " + hadrons[tab.substr(pos + 6)].substr(1) + "   " + std::to_string(xb.second.first) + " < x < " + std::to_string(xb.second.second) + " , " + std::to_string(zb.second.first) + " < |#it{z}| < " + std::to_string(zb.second.second)},
                  {"xlabelpy", "$P_{hT} \\rm{ [GeV]}$"},
                  {"ylabelpy", "$M^{h}_{n}\\left(x, z, |{P}_{hT}|, Q^2 \\right)$"},
                  {"titlepy", "HERMES, " + targets[tab.substr(7,6)].substr(1) + "  -  " + hadrons[tab.substr(pos + 6)].substr(1) + " \\\\ " + std::to_string(xb.second.first) + " < x < " + std::to_string(xb.second.second) + " , " + std::to_string(zb.second.first) + " < z < " + std::to_string(zb.second.second)}
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
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "observable" << YAML::Key << "value" << YAML::Value << "multiplicity" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << (targets[tab.substr(7,6)] == "_Pro" ? 1 : 0.5) << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "hadron" << YAML::Key << "value" << YAML::Value << hadtype << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "charge" << YAML::Key << "value" << YAML::Value << (tab.find("minus") != std::string::npos ? -1 : 1 ) << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
                // ### Square root of s, calculated as Vs = sqrt(2*M*Ee-) = sqrt(2*0.938*27.6 GeV) = 7.195665.
                // ### Check the number 7.256544907874546
                // ### in PV17 Vs = 7.3
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 7.256544907874546 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                     << "low" << YAML::Value << 1 << YAML::Key << "high" << YAML::Value << 3.872983346  << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "x" << YAML::Key
                     << "low" << YAML::Value << xb.second.first << YAML::Key << "high" << YAML::Value << xb.second.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "z" << YAML::Key
                     << "low" << YAML::Value << zb.second.first << YAML::Key << "high" << YAML::Value << zb.second.second << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                     << "W"    << YAML::Value << 3.162277660168379   << YAML::Key << YAML::Key
                     << "ymin" << YAML::Value << 0.1 << YAML::Key << "ymax" << YAML::Value << 0.85 << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (auto const& m : filedata["mult"])
                  {
                    emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << filedata["stat"][m.first] << YAML::EndMap;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << filedata["syst"][m.first] << YAML::EndMap;
                    if (PDFError)
                      {
                        // Now read PDF errors
                        getline(pdferr, line);
                        std::stringstream stream(line);
                        double dum, pe;
                        stream >> dum >> dum >> dum >> dum >> pe >> dum;

                        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << pe * 0.8 << YAML::EndMap;
                        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe * m.second * 0.6 << YAML::EndMap;
                      }
                    if (FFError)
                      {
                        // Now read FF errors
                        getline(fferr, linef);
                        std::stringstream stream(linef);
                        double dum, pe;
                        stream >> dum >> dum >> dum >> dum >> pe >> dum;

                        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << pe * 0.8 << YAML::EndMap;
                        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe * m.second * 0.6 << YAML::EndMap;
                      }
                    //[TEMPORARY] introduction of 5 per mil of error
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << 0.005 * m.second << YAML::EndMap;
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << "###" << YAML::EndMap;
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << "0.05" << YAML::EndMap;
                    emit << YAML::EndSeq;
                    emit << YAML::Key << "value" << YAML::Value << m.second;
                    emit << YAML::Key << "id"    << YAML::Value << m.first;
                    emit << YAML::EndMap;
                  }
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::Key << "independent_variables";
                emit << YAML::BeginSeq;
                emit << YAML::BeginMap;
                emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PhT" << YAML::Key << "units" << YAML::Value << "GeV" << YAML::EndMap;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (auto const& pT : Phpbinval)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << pT.first.second << YAML::Key << "low" << YAML::Value << std::max(pT.first.first, 1e-5) << YAML::Key << "value" << YAML::Value << pT.second.second << YAML::Key << "id" << YAML::Value << pT.second.first<< YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::BeginMap;
                emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "x" << YAML::EndMap;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (int i = 0; i < (int) indexesZ.size(); i++ )
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << xb.second.second << YAML::Key << "low" << YAML::Value << xb.second.first << YAML::Key << "value" << YAML::Value << xvalue << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::BeginMap;
                emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "z" << YAML::EndMap;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (auto const& z : filedata["z"])
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << zb.second.second << YAML::Key << "low" << YAML::Value << zb.second.first << YAML::Key << "value" << YAML::Value << z.second << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::BeginMap;
                emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q2" << YAML::EndMap;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (int n : indexesZ)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "high" << YAML::Value << 15 << YAML::Key << "low" << YAML::Value << 1 << YAML::Key << "value" << YAML::Value << data["Q2"][n] << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::BeginMap;
                emit << YAML::Key << "header" << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::EndMap;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (int n : indexesZ)
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "value" << YAML::Value << data["Q2"][n] / (data["x"][n] * pow(7.256544907874546, 2)) << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;

                // Close PDF-error file
                pdferr.close();

                // Close PDF-error file
                fferr.close();

                // Dump table to file
                std::ofstream fout(opath + "/" + ofileXZ + ".yaml");
                fout << emit.c_str() << std::endl;
                fout.close();

                // Map to space properly the dataset names in datasets.yaml
                std::map<int, std::string> spaces = {{34,"         "}, {35, "        "}, {36, "       "}, {37, "      "}, {38, "     "}, {39, "    "}, {40, "   "}, {41, "  "}, {42, " "}};

                // Eliminate datafiles without any points
                if (ofileXZ == "HERMES_Deu_Km_x_0.35_0.6_z_0.8_1.1")
                  break;

                // Comment datasets that do not pass the Q2 cut
                if (sqrt(data["Q2"][indexesZ[0]]) < Qlower)
                  comment = true;

                // Compose datafile strings
                datafilestrings.push_back((comment ? "#  - {name: " : "  - {name: ") + ofileXZ + "," + spaces[ofileXZ.size()] + "file: " + ofileXZ + ".yaml}\n");

                // Reset comment to false
                comment = false;

              }

          }

      }

    // Produce outputnames to put in datasets.yaml
    std::string outputs;
    for (std::string names : datafilestrings)
      outputs += names;

    return outputs;
  }
}
