/*
 * Author: Simone Venturini
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

namespace NangaParbat
{

  //_________________________________________________________________________________
  std::string PreprocessE615(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing E615 data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/E615/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"dataE615.txt"};

    // Output folder
    const std::string ofolder = "E615";

    // Vector for output names
    std::vector<std::string> filenames;

    // Initialize naming map for the Q-integration ranges (the first element is for the name of the output data file)
    const std::map<std::string, std::pair<double, double>> Qrangelims = {{"_Q_4.05_4.50", {4.05,4.50}}, {"_Q_4.50_4.95", {4.50, 4.95}}, {"_Q_4.95_5.40", {4.95,5.40}}, {"_Q_5.40_5.85", {5.40, 5.85}}, {"_Q_5.85_6.75", {5.85, 6.75}}, {"_Q_6.75_7.65", {6.75, 7.65}}, {"_Q_7.65_9.00", {7.65, 9.00}}, {"_Q_9.00_10.35", {9.00, 10.35}}, {"_Q_10.35_11.70", {10.35, 11.70}}, {"_Q_11.70_13.05", {11.70, 13.05}}};

    // Create directory
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

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
        double vmmin, vmmax, vpT, vcross, vstat, vsyst;
        vsyst = 0.16;

        // Create map to store the data
        std::map<std::string, std::map<int, double>> data;

        //  Create inner maps, one for each column of interest in the rawdatafile
        std::map<int, double> immin, immax, ipT, icross, istat, isyst;

        // The first 14 lines of the raw data files are headers, (11 + 3 for column names).
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
                ss >> vindex >> vmmin >> vmmax >> vpT >> vcross >> vstat;

                // Construct maps of index and values.
                // This is done so that the separation between values in bins can be done by index.
                immin[vindex]  = vmmin;
                immax[vindex]  = vmmax;
                ipT[vindex]    = vpT;
                icross[vindex] = vcross;
                istat[vindex]  = vstat;
              }
          }

        // Now that all lines have been read and the inner maps are filled,
        // put them in the correct column of the data outer map.
        data["m_min"] = immin;
        data["m_max"] = immax;
        data["pT"]    = ipT;
        data["cross"] = icross;
        data["stat"]  = istat;

        /*
        // Maps for target and hadron names
        std::map<std::string, std::string> targets = {{"tungsten", "_W"}};
        std::map<std::string, std::string> hadrons = {{"pion pi-", "_pi-"}};
        std::string hadtype;
        if (tab.find("piplus") != std::string::npos ||  tab.find("piminus") != std::string::npos)
          hadtype = "PI";
        else
          hadtype = "KA";

        // Start composing output file name
        std::size_t pos = tab.find("mults_");
        std::string ofile = "HERMES" + targets[tab.substr(7,6)] + hadrons[tab.substr(pos + 6)];
        */

        // Conditions to separate the values in the columns into different files.
        // Loop on Q(i.e. m) bin boundaries.
        for (auto const& Qb : Qrangelims)
          {
            // File name picks up the m (i.e. Q) boundaries
            std::string ofileQ = "E615" + Qb.first;

            // Initialize indexes vector for future selection
            std::vector<int> indexesQ;
            double Qvalue;

            // Select Q bin
            for (auto const& iQ : data["m_min"])
              // data["m_min"] is a map <index, m_min value> of all the values in the original table,
              // so iQ.first is the index (int) and iQ.second the value (double).
              if (iQ.second >= Qb.second.first && iQ.second < Qb.second.second)
                {
                  // Store indexes
                  indexesQ.push_back(iQ.first);

                  // Get Q value
                  Qvalue = iQ.second;
                }


                // Initialize result maps
                std::map<int, double> fdcross, fdstat, fdpT;

                // Prepare (outer) map for each output data file
                std::map<std::string, std::map<int, double>> filedata;

                // Finally select cross sections and their uncertainties.
                for (int i : indexesQ)
                  {
                    fdcross[i] = data["cross"][i];
                    fdstat[i]  = data["stat"][i];
                    fdpT[i]    = data["pT"][i];
                  }

                filedata["cross"] = fdcross;
                filedata["stat"]  = fdstat;
                filedata["pT"]    = fdpT;


                // Open PDF-error file
                std::ifstream pdferr(PDFErrorFolder + ofileQ + ".out");
                std::string line;
                getline(pdferr, line);
                getline(pdferr, line);

                // Plot labels
                std::map<std::string, std::string> labels
                {
                  {"xlabel", "#it{q}_{T} [GeV]"},
                  {"ylabel", "#frac{d2#it{#sigma}}{d#it{p}_{T}#d#it{q}_{T}} [cm^{2}*GeV^{-2}"},
                  {"title", "E615, " + std::to_string(Qb.second.first) + " < Q < " + std::to_string(Qb.second.second)},
                  {"xlabelpy", "$q_T \\rm{[GeV]$"},
                  {"ylabelpy", "$\\frac{d^2\\sigma}{dp_{T} dq_{T}}[\\rm{cm}^2*{GeV}^{-2}]$"},
                  {"titlepy", "E615, \\n " + std::to_string(Qb.second.first) + " < Q < " + std::to_string(Qb.second.second)}
                };

                // Allocate emitter
                YAML::Emitter emit;


                // NOTE on the calculation of y_min and y_max: y=arcsinh(sqrt{s}*xF/(2Q)).
                //                                             The value of x_min = 0, then y_min=0 for all bin in Q
                //                                             x_max = 1, then y_max = arcsinh(sqrt(s)/(2 Q_min)) for a specific Qmin<Q<Qmax bin


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
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "process" << YAML::Key << "value" << YAML::Value << "Drell Yan" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "observable" << YAML::Key << "value" << YAML::Value << "cross section" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 0.4025 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 252 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Q" << YAML::Key
                     << "low" << YAML::Value << Qb.second.first << YAML::Key << "high" << YAML::Value << Qb.second.second  << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                     << "low" << YAML::Value << asinh(0) << YAML::Key << "high" << YAML::Value << asinh(252/(2* Qb.second.first)) << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                /*emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                     << "pTmin" << YAML::Value << "###" << YAML::Key << "etamin" << YAML::Value << "###" << YAML::Key << "etamax" << YAML::Value << "###" << YAML::EndMap;
                emit << YAML::EndSeq;*/
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (auto const& m : filedata["cross"])
                  {
                    emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << filedata["stat"][m.first] << YAML::EndMap;
                    if (PDFError)
                      {
                        // Now read PDF errors
                        getline(pdferr, line);
                        std::stringstream stream(line);
                        double dum, pe;
                        stream >> dum >> dum >> dum >> dum >> dum >> dum >> pe;

                        emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << 0.16 << YAML::EndMap;
                        // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << pe << YAML::EndMap;
                      }
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "add" << YAML::Key << "value" << YAML::Value << "###" << YAML::EndMap;
                    // emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "mult" << YAML::Key << "value" << YAML::Value << "###" << YAML::EndMap;
                    emit << YAML::EndSeq;
                    emit << YAML::Key << "value" << YAML::Value << m.second;
                    // emit << YAML::Key << "id"    << YAML::Value << m.first;
                    emit << YAML::EndMap;
                  }
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::EndSeq;

                // Close PDF-error file


                emit << YAML::Key << "independent_variables";
                emit << YAML::BeginSeq;
                emit << YAML::BeginMap;
                emit << YAML::Key << "header" << YAML::Value << YAML::Flow;
                emit << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PT" << YAML::Key << "units" << YAML::Value << "GEV" << YAML::EndMap;
                emit << YAML::Key << "values" << YAML::Value;
                emit << YAML::BeginSeq;
                for (auto const& p : filedata["pT"])
                  emit << YAML::Flow << YAML::BeginMap << YAML::Key << "value" << YAML::Value << p.second << YAML::Key << "high" << YAML::Value << (p.second - 0.125)
                       << YAML::Key << "low" << YAML::Value << (p.second + 0.125) << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;





                pdferr.close();

                // Dump table to file
                std::ofstream fout(opath + "/" + ofileQ + ".yaml");
                fout << emit.c_str() << std::endl;
                fout.close();

                filenames.push_back(ofileQ);

          }

      }

    // Map to space properly the dataset names in datasets.yaml
    std::map<int, std::string> spaces = {{34,"         "}, {35, "        "}, {36, "       "}, {37, "      "}, {38, "     "}, {39, "    "}, {40, "   "}, {41, "  "}, {42, " "}};

    // Produce outputnames to put in datasets.yaml
    std::string outputnames;
    for (std::string name : filenames)
      outputnames += "  - {name: " + name + "," + spaces[name.size()] + "file: " + name + ".yaml}\n";

    return outputnames;
  }
}
