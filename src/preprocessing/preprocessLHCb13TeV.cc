/*
 * Author: Chiara Bissolotti
 */

#include "NangaParbat/preprocessing.h"

#include <iostream>
#include <sys/stat.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string PreprocessLHCb13TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath, bool const& PDFError)
  {
    std::cout << "Processing LHCb 13 TeV data ..." << std::endl;

    // Path to the raw-data folder
    const std::string RawDataFolder = RawDataPath + "/LHCb_13TeV/";

    // Table to copy
    const std::string tab = "LHCb_13TeV.yaml";

    // Output folder
    const std::string ofolder = "LHCb";

    // In this case just copy the file
    std::string opath = ProcessedDataPath + "/" + ofolder;
    mkdir(opath.c_str(), ACCESSPERMS);

    // Copy file
    if (PDFError)
      system(("cp " + RawDataFolder + tab + ".pdferr " + opath + "/" + tab).c_str());
    else
      system(("cp " + RawDataFolder + tab + " " + opath + "/" + tab).c_str());

    return "  - {name: LHCb_13TeV, file: LHCb_13TeV.yaml}\n";
  }
}
