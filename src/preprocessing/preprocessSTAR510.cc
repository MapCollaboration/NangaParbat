/*
 * Author: Chiara Bissolotti
 */

#include "NangaParbat/preprocessing.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
//#include <copyfile.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessSTAR510(std::string const& RawDataPath, std::string const& ProcessedDataPath)
  {
    std::cout << "Processing STAR 510 GeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/STAR_510/";

    // Table to copy
    const std::string tab = "STAR_510.yaml";

    // Output folder
    const std::string ofolder = "STAR";

    // In this case just copy the file
    // Loop over tables
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Copy file
    //copyfile_state_t s;
    //s = copyfile_state_alloc();
    //copyfile((RawDataFolder + tab).c_str(), (opath + "/" + tab).c_str(), s, COPYFILE_DATA);
    system(("cp " + RawDataFolder + tab + " " + opath + "/" + tab).c_str());

    return "  - {name: STAR_510, file: STAR_510.yaml}\n";
  }
}
