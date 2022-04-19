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
  std::string PreprocessE615_xF(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing E615 data binned in xF ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/E615/";

    // Path to the PDF-error folder
    const std::string PDFErrorFolder = RawDataPath + "/PDFErrors/";

    // Vector of tables to process
    const std::vector<std::string> tables = {"dataE615_xF.txt"};

    // Output folder
    const std::string ofolder = "E615xF";

    // Vector for output names
    std::vector<std::string> filenames;

    // Initialize naming map for the xF-integration ranges (the first element is for the name of the output data file)
    const std::map<std::string, std::pair<double, double>> xFrangelims = {{"_xF_0.00_0.10", {0.00,0.10}}, {"_xF_0.10_0.20", {0.10, 0.20}}, {"_xF_0.20_0.30", {0.20, 0.30}}, {"_xF_0.30_0.40", {0.30, 0.40}}, {"_xF_0.40_0.50", {0.40, 0.50}}, {"_xF_0.50_0.60", {0.50, 0.60}}, {"_xF_0.60_0.70", {0.60, 0.70}}, {"_xF_0.70_0.80", {0.70, 0.80}}, {"_xF_0.80_0.90", {0.80, 0.90}}, {"_xF_0.90_1.00", {0.90, 1.00}}};

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
        double vxFmin, vxFmax, vpT, vcross, vstat;//, vsyst;
        //vsyst = 0.16;

        // Create map to store the data
        std::map<std::string, std::map<int, double>> data;

        //  Create inner maps, one for each column of interest in the rawdatafile
        std::map<int, double> ixFmin, ixFmax, ipT, icross, istat, isyst;

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
                ss >> vindex >> vxFmin >> vxFmax >> vpT >> vcross >> vstat;

                // Construct maps of index and values.
                // This is done so that the separation between values in bins can be done by index.
                ixFmin[vindex]  = vxFmin;
                ixFmax[vindex]  = vxFmax;
                ipT[vindex]    = vpT;
                icross[vindex] = vcross;
                istat[vindex]  = vstat;
              }
          }

        // Now that all lines have been read and the inner maps are filled,
        // put them in the correct column of the data outer map.
        data["xF_min"] = ixFmin;
        data["xF_max"] = ixFmax;
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
        // Loop on xF bin boundaries.
        for (auto const& xFb : xFrangelims)
          {
            // File name picks up the xF boundaries
            std::string ofilexF = "E615" + xFb.first;

            // Initialize indexes vector for future selection
            std::vector<int> indexesxF;
            // double xFvalue;

            // Select xF bin
            for (auto const& ixF : data["xF_min"])
              // data["xF_min"] is a map <index, xF_min value> of all the values in the original table,
              // so ixF.first is the index (int) and ixF.second the value (double).
              if (ixF.second >= xFb.second.first && ixF.second < xFb.second.second)
                {
                  // Store indexes
                  indexesxF.push_back(ixF.first);

                  // Get xF value
                  // xFvalue = ixF.second;
                }


                // Initialize result maps
                std::map<int, double> fdcross, fdstat, fdpT;

                // Prepare (outer) map for each output data file
                std::map<std::string, std::map<int, double>> filedata;

                // Finally select cross sections and their uncertainties.
                for (int i : indexesxF)
                  {
                    fdcross[i] = data["cross"][i];
                    fdstat[i]  = data["stat"][i];
                    fdpT[i]    = data["pT"][i];
                  }

                filedata["cross"] = fdcross;
                filedata["stat"]  = fdstat;
                filedata["pT"]    = fdpT;

                // Open PDF-error file
                std::ifstream pdferr(PDFErrorFolder + ofilexF + ".out");
                std::string line;
                getline(pdferr, line);
                getline(pdferr, line);

                // Plot labels
                std::map<std::string, std::string> labels
                {
                  {"xlabel", "#it{x}_{F}"},
                  {"ylabel", "#frac{d2#it{#sigma}}{d#it{x}_{F}#d#it{q}_{T}} [nb*GeV^{-2}"},
                  {"title", "E615, " + std::to_string(xFb.second.first) + " < xF < " + std::to_string(xFb.second.second)},
                  {"xlabelpy", "$x_F$"},
                  {"ylabelpy", "$\\frac{d^2\\sigma}{dp_{T} dq_{T}}[\\rm{nb}*{GeV}^{-2}]$"},
                  {"titlepy", "E615, \\n " + std::to_string(xFb.second.first) + " < xF < " + std::to_string(xFb.second.second)}
                };

                /*
                NOTE on the conversion factor for the cross section. We will insert it in the output file.
                The raw data have a cross section expressed in cm**2/GeV**2/nucleon, but we would like to have it in NB./NUCLEON/GEV**2,
                then we have to convert: 1barn = 10**{-28}m**2 = 10**{-24}cm**2. Therefore, 1 cm**2 = 10**{24}barn= 10**{33}nb.

                NOTE on the calculation of y_min and y_max: y=arcsinh(sqrt{s}*xF/(2Q)).
                The value of x_min = 0, then y_min=0 for all bin in Q
                x_max = 1, then y_max = arcsinh(sqrt(s)/(2 Q_min)) for a specific Qmin<Q<Qmax bin
                */

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
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "process" << YAML::Key << "value" << YAML::Value << "Drell Yan" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "observable" << YAML::Key << "value" << YAML::Value << "cross section" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "target_isoscalarity" << YAML::Key << "value" << YAML::Value << 0.4025 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "prefactor" << YAML::Key << "value" << YAML::Value << 1 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "Vs" << YAML::Key << "value" << YAML::Value << 252 << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "xF" << YAML::Key
                     << "low" << YAML::Value << xFb.second.first << YAML::Key << "high" << YAML::Value << xFb.second.second  << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "y" << YAML::Key
                     << "low" << YAML::Value << asinh((252*xFb.second.first)/(2*13.05)) << YAML::Key << "high" << YAML::Value << asinh((252*xFb.second.second)/(2* 4.05)) << YAML::Key << "integrate" << YAML::Value << "true" << YAML::EndMap;
                /*emit << YAML::Flow << YAML::BeginMap << YAML::Key << "name" << YAML::Value << "PS_reduction" << YAML::Key
                     << "pTmin" << YAML::Value << "###" << YAML::Key << "etamin" << YAML::Value << "###" << YAML::Key << "etamax" << YAML::Value << "###" << YAML::EndMap;
                emit << YAML::EndSeq;*/
                emit << YAML::Key << "values" << YAML::Value;
                for (auto const& f : filedata["cross"])
                  {
                    emit << YAML::BeginMap << YAML::Key << "errors" << YAML::Value << YAML::BeginSeq;
                    //REMEMBER the conversion factor for the cross section:
                    emit << YAML::Flow << YAML::BeginMap << YAML::Key << "label" << YAML::Value << "unc" << YAML::Key << "value" << YAML::Value << (filedata["stat"][f.first])*pow(10,33) << YAML::EndMap;
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
                    //REMEMBER the conversion factor for the cross section:
                    emit << YAML::Key << "value" << YAML::Value << (f.second)*pow(10,33);
                    // emit << YAML::Key << "id"    << YAML::Value << m.first;
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
                for (auto const& p : filedata["pT"])
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
                //REMEMBER the conversion factor for the cross section:
                //emit << YAML::Key << "value" << YAML::Value << (f.second)*pow(10,33);
                // emit << YAML::Key << "id"    << YAML::Value << m.first;
                emit << YAML::EndMap;
                emit << YAML::EndSeq;
                emit << YAML::EndMap;

                pdferr.close();

            // Dump table to file
            std::ofstream fout(opath + "/" + ofilexF + ".yaml");
            fout << emit.c_str() << std::endl;
            fout.close();

            filenames.push_back(ofilexF);

          }

      }

    // Map to space properly the dataset names in datasets.yaml
    std::map<int, std::string> spaces = {{17,"  "}};

    // Produce outputnames to put in datasets.yaml
    std::string outputnames;
    for (std::string name : filenames)
      outputnames += "  - {name: " + name + "," + spaces[name.size()] + "file: " + name + ".yaml}\n";

    return outputnames;
  }
}
