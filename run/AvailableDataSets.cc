//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include <yaml-cpp/yaml.h>
#include <iostream>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./AvailableDataSets <path to data folder>\n" << std::endl;
      exit(-10);
    }

  // List datasets reported in the datasets.yaml file in the data
  // folder.
  std::cout << "\nAvailable datasets:" << std::endl;
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[1]) + "/datasets.yaml");
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      std::cout << "- " << ds["name"].as<std::string>() << std::endl;
  std::cout << "\n";

  return 0;
}
