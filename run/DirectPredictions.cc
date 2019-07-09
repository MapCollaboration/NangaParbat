//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/fastinterface.h"
#include "NangaParbat/utilities.h"

#include <fstream>
#include <apfel/timer.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./DirectPredictions <configuration file> <path to data folder>" << std::endl;
      exit(-10);
    }

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
      {
	std::cout << "- " << ds["name"].as<std::string>() << std::endl;
	const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
	DHVect.push_back(NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(datafile)});
      }

  // Allocate "Parameterisation" derived object
  NangaParbat::DWS NPFunc{};

  // Compute direct predictions
  auto const fNP = [=] (double const& x, double const& b, double const& zeta) -> double { return NPFunc.Evaluate(x, b, zeta, 0); };
  const std::vector<std::vector<double>> dc = FIObj.DirectComputation(DHVect, NangaParbat::bstarmin, fNP, fNP);

  // Report results
  std::cout << "Direct computation...\n" << std::endl;
  std::cout << std::scientific;
  for (int i = 0; i < (int) dc.size(); i++)
    {
      std::cout << "Dataset " << i + 1 << ")" << std::endl;
      std::cout << "j   Predictions" << std::endl;
      for (int j = 0; j < (int) dc[i].size(); j++)
	std::cout << j << "\t" << dc[i][j] << std::endl;
      std::cout << "\n";
    }

  return 0;
}
