//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/preprocessing.h"

#include <iostream>
#include <fstream>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if(argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./Filter <path to raw-data folder> <path to processed data>\n" << std::endl;
      exit(-10);
    }

  // Path to the raw-data folder
  const std::string RawDataPath = std::string(argv[1]);

  // Path to to output folder
  const std::string ProcessedDataPath = std::string(argv[2]);

  // Dataset file created dunring the filtering
  std::ofstream fout(ProcessedDataPath + "/datasets.yaml");

  fout << "E605:\n";
  fout << NangaParbat::PreprocessE605(RawDataPath, ProcessedDataPath);

  fout << "E288:\n";
  fout << NangaParbat::PreprocessE288(RawDataPath, ProcessedDataPath);

  fout << "STAR:\n";
  fout << NangaParbat::PreprocessSTAR510(RawDataPath, ProcessedDataPath);

  fout << "CDF:\n";
  fout << NangaParbat::PreprocessCDFRunI(RawDataPath,  ProcessedDataPath);
  fout << NangaParbat::PreprocessCDFRunII(RawDataPath, ProcessedDataPath);

  fout << "D0:\n";
  fout << NangaParbat::PreprocessD0RunI(RawDataPath,  ProcessedDataPath);
  fout << NangaParbat::PreprocessD0RunII(RawDataPath, ProcessedDataPath);

  fout << "LHCb:\n";
  fout << NangaParbat::PreprocessLHCb7TeV(RawDataPath,  ProcessedDataPath);
  fout << NangaParbat::PreprocessLHCb8TeV(RawDataPath,  ProcessedDataPath);
  fout << NangaParbat::PreprocessLHCb13TeV(RawDataPath, ProcessedDataPath);

  fout << "CMS:\n";
  fout << NangaParbat::PreprocessCMS7TeV(RawDataPath, ProcessedDataPath);
  fout << NangaParbat::PreprocessCMS8TeV(RawDataPath, ProcessedDataPath);

  fout << "ATLAS:\n";
  fout << NangaParbat::PreprocessATLAS7TeV(RawDataPath, ProcessedDataPath);
  fout << NangaParbat::PreprocessATLAS8TeV(RawDataPath, ProcessedDataPath);

  fout.close();

  return 0;
}
