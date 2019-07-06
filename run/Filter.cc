//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/preprocessing.h"

#include <iostream>

//_________________________________________________________________________________
// Main program
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if(argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << std::endl;
      std::cout << "Invalid Parameters:" << std::endl;
      std::cout << "Syntax: ./Filter <path to raw-data folder> <path to the processed data>" << std::endl;
      std::cout << std::endl;
      exit(-10);
    }

  // Path to raw-data as a std::string
  const std::string RawDataPath = std::string(argv[1]);

  // Path to to the output folder as a std::string
  const std::string ProcessedDataPath = std::string(argv[2]);

  // E605
  NangaParbat::PreprocessE605(RawDataPath, ProcessedDataPath);

  // E288
  NangaParbat::PreprocessE288(RawDataPath, ProcessedDataPath);

  // CDF Run I
  NangaParbat::PreprocessCDFRunI(RawDataPath, ProcessedDataPath);

  // CDF Run II
  NangaParbat::PreprocessCDFRunII(RawDataPath, ProcessedDataPath);

  // D0 Run I
  NangaParbat::PreprocessD0RunI(RawDataPath, ProcessedDataPath);

  // D0 Run II
  NangaParbat::PreprocessD0RunII(RawDataPath, ProcessedDataPath);

  // LHCb 7 TeV
  NangaParbat::PreprocessLHCb7TeV(RawDataPath, ProcessedDataPath);

  // LHCb 8 TeV
  NangaParbat::PreprocessLHCb8TeV(RawDataPath, ProcessedDataPath);

  // LHCb 13 TeV
  NangaParbat::PreprocessLHCb13TeV(RawDataPath, ProcessedDataPath);

  return 0;
}
