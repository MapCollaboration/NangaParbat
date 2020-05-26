/*
 * Author: Chiara Bissolotti
 */

#include "NangaParbat/preprocessing.h"

#include <iostream>
#include <sys/stat.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessEICPseudodata(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const&)
  {
    std::cout << "Processing EIC pseudodata ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/EIC_Pseudodata/";

    // Table to copy
    const std::string tab = "EIC_PseudoData_x_0.0002_0.0006_Q_1_1.8_z_0.1_0.2.yaml";

    // Output folder
    const std::string ofolder = "EIC";

    // In this case just copy the file
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Copy file
    system(("cp " + RawDataFolder + tab + " " + opath + "/" + tab).c_str());

    return "  - {name: EIC_PseudoData, file: EIC_PseudoData_x_0.0002_0.0006_Q_1_1.8_z_0.1_0.2.yaml}\n";
  }
}
