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
  if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateTables <configuration file> <path to data folder>\n" << std::endl;
      exit(-10);
    }

  // Allocate "FastInterface" object reading the parameters from an
  // input card.
  const NangaParbat::FastInterface FIObj{YAML::LoadFile(argv[1])};

  // Open datasets.yaml file that contains the list of tables to be
  // produced and push data sets into the a vector of DataHandler
  // objects. If a set of selected datasets is also provided, the code
  // produces tables only for those datasets.
  std::cout << "\nComputing SIDIS normalisation factors for:" << std::endl;
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[2]) + "/datasets.yaml");
  std::vector<NangaParbat::DataHandler> DHVect;
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        std::cout << "- " << ds["name"].as<std::string>() << std::endl;
        const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
        DHVect.push_back(NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(datafile)});
      }

  // Compute tables
  const std::vector<double> Facts = FIObj.NormalisationFactorsSIDIS(DHVect);

  std::cout << "Normalisation factors:" << std::endl;
  // Dump table to file
  for (int i = 0; i < Facts.size(); i++)
    {
      const NangaParbat::DataHandler::Kinematics kin = DHVect[i].GetKinematics();
      const std::pair<double, double> Qb  = kin.var1b;    // Invariant mass interval
      const std::pair<double, double> xbb = kin.var2b;    // Bjorken x interval
      const std::pair<double, double> zb  = kin.var3b;    // z interval
      std::cout << std::scientific << i << "\t"
                << " [" << Qb.first << ":" << Qb.second << "]"
                << " [" << xbb.first << ":" << xbb.second << "]"
                << " [" << zb.first << ":" << zb.second << "]"
                << "  " << Facts[i] << std::endl;
    }

  return 0;
}
