//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/preprocessing.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>

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

  // Create output folder
  mkdir(ProcessedDataPath.c_str(), ACCESSPERMS);

  // Dataset file created dunring the filtering
  std::ofstream fout(ProcessedDataPath + "/datasets.yaml");

  // Include on not PDF uncertainties
  const bool pdferr = true;

  fout << "E605:\n";
  fout << NangaParbat::PreprocessE605(RawDataPath, ProcessedDataPath, pdferr);

  fout << "E288:\n";
  fout << NangaParbat::PreprocessE288(RawDataPath, ProcessedDataPath, pdferr);

  //fout << "PHENIX:\n";
  //fout << NangaParbat::PreprocessPHENIX200(RawDataPath, ProcessedDataPath, pdferr);

  fout << "STAR:\n";
  fout << NangaParbat::PreprocessSTAR510(RawDataPath, ProcessedDataPath, pdferr);

  fout << "CDF:\n";
  fout << NangaParbat::PreprocessCDFRunI(RawDataPath,  ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessCDFRunII(RawDataPath, ProcessedDataPath, pdferr);

  fout << "D0:\n";
  fout << NangaParbat::PreprocessD0RunI(RawDataPath,    ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessD0RunII(RawDataPath,   ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessD0RunIImu(RawDataPath, ProcessedDataPath, pdferr);

  fout << "LHCb:\n";
  fout << NangaParbat::PreprocessLHCb7TeV(RawDataPath,  ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessLHCb8TeV(RawDataPath,  ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessLHCb13TeV(RawDataPath, ProcessedDataPath, pdferr);

  fout << "CMS:\n";
  fout << NangaParbat::PreprocessCMS7TeV(RawDataPath, ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessCMS8TeV(RawDataPath, ProcessedDataPath, pdferr);

  fout << "ATLAS:\n";
  fout << NangaParbat::PreprocessATLAS7TeV(RawDataPath, ProcessedDataPath, pdferr);
  fout << NangaParbat::PreprocessATLAS8TeV(RawDataPath, ProcessedDataPath, pdferr);

  fout << "HERMES:\n";
  fout << NangaParbat::PreprocessHERMES(RawDataPath, ProcessedDataPath, pdferr);

  fout << "COMPASS:\n";
  fout << NangaParbat::PreprocessCOMPASS(RawDataPath, ProcessedDataPath, pdferr);

  fout << "E537:\n";
  fout << NangaParbat::PreprocessE537(RawDataPath, ProcessedDataPath, pdferr);
  // fout << NangaParbat::PreprocessE537_xF(RawDataPath, ProcessedDataPath, pdferr);

  fout << "E615:\n";
  fout << NangaParbat::PreprocessE615(RawDataPath, ProcessedDataPath, pdferr);
  // fout << NangaParbat::PreprocessE615_xF(RawDataPath, ProcessedDataPath, pdferr);

  fout.close();

  return 0;
}
