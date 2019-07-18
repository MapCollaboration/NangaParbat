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
  std::string PreprocessPHENIX200(std::string const& RawDataPath, std::string const& ProcessedDataPath)
  {
    std::cout << "Processing PHENIX at 200 GeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/PHENIX_200/";

    // Table to copy
    const std::string tab = "PHENIX_200.yaml";

    // Output folder
    const std::string ofolder = "PHENIX";

    // In this case just copy the file
    // Loop over tables
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Copy file
    //copyfile_state_t s;
    //s = copyfile_state_alloc();
    //copyfile((RawDataFolder + tab).c_str(), (opath + "/" + tab).c_str(), s, COPYFILE_DATA);
    system(("cp " + RawDataFolder + tab + " " + opath + "/" + tab).c_str());

    return "  - {name: PHENIX_200, file: PHENIX_200.yaml}\n";
  }
}
