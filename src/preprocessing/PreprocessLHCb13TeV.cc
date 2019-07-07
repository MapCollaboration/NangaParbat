/*
 * Author: Chiara Bissolotti
 */

#include "NangaParbat/preprocessing.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <copyfile.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessLHCb13TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath)
  {
    std::cout << "Processing LHCb 13 TeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/LHCb_13TeV/";

    // Table to copy
    const std::string tab = "LHCb_13TeV.yaml";

    // Output folder
    const std::string ofolder = "LHCb";


    // In this case just copy the file
    // Loop over tables
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Copy file
    copyfile_state_t s;
    s = copyfile_state_alloc();
    copyfile((RawDataFolder + tab).c_str(), (opath + "/" + tab).c_str(), s, COPYFILE_DATA);

    return "#   - {name: LHCb_13TeV, file: LHCb_13TeV.yaml}\n";
  }
}
