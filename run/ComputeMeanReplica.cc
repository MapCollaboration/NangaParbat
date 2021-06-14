//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"
#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/meanreplica.h"

#include <apfel/timer.h>
#include <algorithm>
#include <fstream>
#include <sys/stat.h>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 5 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./ComputeMeanReplica <fit dir> <fit configuration file> <path to data folder> <path to tables folder> [replicas to be discarded]\n" << std::endl;
      exit(-10);
    }

  // Vector of selected datasets
  std::vector<int> discard;
  for (int i = 5; i < argc; i++)
    discard.push_back(std::stoi(argv[i]));

  // Timer
  apfel::Timer t;

  // Reading fit  parameters from an input card
  YAML::Node fitconfig = YAML::LoadFile(argv[2]);

  // Allocate "Parameterisation" derived object
  NangaParbat::Parameterisation *NPFunc = new NangaParbat::MeanReplica{std::string(argv[1]), std::string(argv[2]), discard};
  //NangaParbat::Parameterisation *NPFunc = new NangaParbat::DWS{};

  // Create replica folder
  const std::string OutputFolder = std::string(argv[1]) + "/mean_replica";
  mkdir((OutputFolder).c_str(), ACCESSPERMS);

  // Define "ChiSquare" object with a given qT / Q cut
  NangaParbat::ChiSquare chi2{NPFunc};

  // Open datasets.yaml file that contains the list of datasets to be
  // fitted and push the corresponding pairs of "DataHandler" and
  // "ConvolutionTable" objects into the a vector.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[3]) + "/datasets.yaml");
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        std::cout << "Reading table for " << ds["name"].as<std::string>() << "..." << std::endl;

        // Convolution table
        //NangaParbat::ConvolutionTable* ct =  new NangaParbat::ConvolutionTable{YAML::LoadFile(std::string(argv[4]) + "/" + ds["name"].as<std::string>() + ".yaml"), fitconfig["qToQmax"].as<double>()};
        NangaParbat::ConvolutionTable* ct =  new NangaParbat::ConvolutionTable{YAML::LoadFile(std::string(argv[4]) + "/" + ds["name"].as<std::string>() + ".yaml"), fitconfig["cutParam"].as<std::vector<double>>()};

        // Datafile
        NangaParbat::DataHandler* dh = new NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(std::string(argv[3]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>())};

        // Add chi2 block
        chi2.AddBlock(std::make_pair(dh, ct));
      }
  // Report time elapsed
  t.stop();

  // Minimise the chi2 using the minimiser indicated in the input card
  t.start();
  const bool status  = NoMinimiser(chi2, fitconfig["Parameters"]);

  // Print the total chi2 on screen
  std::cout << "Total chi2 = " << chi2() << "\n" << std::endl;

  // Produce the report
  YAML::Emitter out;
  out << chi2;
  std::ofstream rout(OutputFolder + "/Report.yaml");
  rout << "Status: " << status << std::endl;
  rout << out.c_str() << std::endl;
  rout.close();

  // Delete "Parameterisation" object
  delete NPFunc;

  // Report time elapsed
  t.stop();

  return 0;
}
