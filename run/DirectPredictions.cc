//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/fastinterface.h"
#include "NangaParbat/utilities.h"

#include <fstream>
#include <cstring>
#include <apfel/timer.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./DirectPredictions <configuration file> <path to data folder> <parametrisation [DWS, PV17, PV19]>\n" << std::endl;
      exit(-10);
    }
  std::cout << "\nWARNING: This could be unbearably slow!\n" << std::endl;

  // Timer
  apfel::Timer t;

  // Allocate "FastInterface" object reading the parameters from an
  // input card.
  const NangaParbat::FastInterface FIObj{YAML::LoadFile(argv[1])};

  // Open datasets.yaml file that contains the list of tables to be
  // produced and push data sets into the a vector of DataHandler
  // objects. If a set of selected datasets is also provided, the code
  // produces tables only for those datasets.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[2]) + "/datasets.yaml");
  std::vector<NangaParbat::DataHandler> DHVect;
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
        DHVect.push_back(NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(datafile)});
      }

  // Allocate "Parameterisation" derived object
  NangaParbat::Parameterisation *NPFunc;
  if (std::string(argv[3]) == "DWS")
    NPFunc = new NangaParbat::DWS{};
  else if (std::string(argv[3]) == "PV17")
    NPFunc = new NangaParbat::PV17{};
  else if (std::string(argv[3]) == "PV19")
    NPFunc = new NangaParbat::PV19{};
  else
    throw std::runtime_error("[DirectPredictions]: Unknown parameterisation");

  // Compute direct predictions
  auto const fNP = [=] (double const& x, double const& b, double const& zeta) -> double { return (*NPFunc).Evaluate(x, b, zeta, 0); };
  const std::vector<std::vector<double>> dc = FIObj.DirectComputation(DHVect, NangaParbat::bstarmin, fNP, fNP);

  // Report results
  std::cout << "Direct computation...\n" << std::endl;
  std::cout << std::scientific;
  for (int i = 0; i < (int) dc.size(); i++)
    {
      std::cout << "Dataset " << i + 1 << "): " << DHVect[i].GetName() << std::endl;
      const std::vector<double> qTv = DHVect[i].GetKinematics().qTv;
      std::cout << "j         qT [GeV]      Predictions" << std::endl;
      for (int j = 0; j < (int) dc[i].size(); j++)
        std::cout << j << "\t" << qTv[j] << "\t" << dc[i][j] << std::endl;
      std::cout << "\n";
    }

  // Delete "Parameterisation" object
  delete NPFunc;

  // Report time elapsed
  t.stop();

  return 0;
}
