//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/nonpertfunctions.h"

#include <fstream>
#include <cstring>
#include <algorithm>
#include <apfel/timer.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateTables <configuration file> <path to data folder> <output folder> [optional selected datasets]\n" << std::endl;
      exit(-10);
    }

  // Vector of selected datasets
  std::vector<std::string> selsets;
  for (int i = 4; i < argc; i++)
    selsets.push_back(std::string(argv[i]));

  // Allocate "FastInterface" object reading the parameters from an
  // input card.
  const NangaParbat::FastInterface FIObj{YAML::LoadFile(argv[1])};

  // Open datasets.yaml file that contains the list of tables to be
  // produced and push data sets into the a vector of DataHandler
  // objects. If a set of selected datasets is also provided, the code
  // produces tables only for those datasets.
  std::cout << "\nGenerating interpolation tables for:" << std::endl;
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[2]) + "/datasets.yaml");
  std::vector<NangaParbat::DataHandler> DHVect;
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      if(std::find(selsets.begin(), selsets.end(), ds["name"].as<std::string>()) != selsets.end() || selsets.empty())
        {
          std::cout << "- " << ds["name"].as<std::string>() << std::endl;
          const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
          DHVect.push_back(NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(datafile)});
        }

  // Compute tables
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect);

  // Dump table to file
  for (auto const& tab : Tabs)
    {
      std::ofstream fout(std::string(argv[3]) + "/" + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();
    }

  return 0;
}
