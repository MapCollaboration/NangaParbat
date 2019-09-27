//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/PV17.h"
#include "NangaParbat/PV19.h"
#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <apfel/timer.h>
#include <algorithm>
#include <fstream>
#include <sys/stat.h>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 7 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./RunFit <output dir> <fit configuration file> <path to data folder> <path to tables folder> <replica ID> <fluctuate initial parameters? [y/n]>\n" << std::endl;
      exit(-10);
    }

  // Timer
  apfel::Timer t;

  // Reading fit  parameters from an input card
  const YAML::Node fitconfig = YAML::LoadFile(argv[2]);

  // Allocate "Parameterisation" derived object
  NangaParbat::Parameterisation *NPFunc;
  if (fitconfig["Parameterisation"].as<std::string>() == "DWS")
    NPFunc = new NangaParbat::DWS{};
  else if (fitconfig["Parameterisation"].as<std::string>() == "PV17")
    NPFunc = new NangaParbat::PV17{};
  else if (fitconfig["Parameterisation"].as<std::string>() == "PV19")
    NPFunc = new NangaParbat::PV19{};
  else
    throw std::runtime_error("[RunFit]: Unknown parameterisation");

  // Initialise GSL random-number generator
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_ranlxs2);
  gsl_rng_set(rng, fitconfig["Seed"].as<int>());

  // Replica ID number
  const int ReplicaID = atoi(argv[5]);

  // Create replica folder
  std::string ReplicaFolder = std::string(argv[1]) + "/replica_" + std::string(argv[5]);
  mkdir((ReplicaFolder).c_str(), ACCESSPERMS);

  // Define "ChiSquare" object with a given qT / Q cut
  NangaParbat::ChiSquare chi2{*NPFunc, fitconfig["qToQmax"].as<double>()};

  // Set parameters for the t0 predictions using "t0parameters" in the
  // configuration card.
  NPFunc->SetParameters(fitconfig["t0parameters"].as<std::vector<double>>());

  // Open datasets.yaml file that contains the list of datasets to be
  // fitted and push the corresponding pairs of "DataHandler" and
  // "ConvolutionTable" objects into the a vector.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[3]) + "/datasets.yaml");
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        std::cout << "Reading " << ds["name"].as<std::string>() << " ..." << std::endl;

        // Convolution table
        const std::string table = std::string(argv[4]) + "/" + ds["name"].as<std::string>() + ".yaml";
        const NangaParbat::ConvolutionTable ct{YAML::LoadFile(table)};

        // Datafile
        const std::string datafile = std::string(argv[3]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
        const NangaParbat::DataHandler dh{ds["name"].as<std::string>(), YAML::LoadFile(datafile), rng, ReplicaID,
                                          (fitconfig["t0prescription"].as<bool>() ? ct.GetPredictions(NPFunc->Function()) : std::vector<double>{})};

        // Add chi2 block
        chi2.AddBlock(std::make_pair(dh, ct));
      }

  // Fluctuate parameters, if required, only for replicas different
  // from zero.
  const bool fulctpar = (ReplicaID == 0 ? false : std::strncmp(argv[6], "y", 1) == 0);

  // Minimise the chi2 using the minimiser indicated in the input card
  bool status;
  if (fitconfig["Minimiser"].as<std::string>() == "minuit")
    status = MinuitMinimiser(chi2, fitconfig["Parameters"], (fulctpar ? rng : NULL));
  else if (fitconfig["Minimiser"].as<std::string>() == "ceres")
    status = CeresMinimiser(chi2, fitconfig["Parameters"], (fulctpar ? rng : NULL));
  else if (fitconfig["Minimiser"].as<std::string>() == "none")
    status = NoMinimiser(chi2, fitconfig["Parameters"], (fulctpar ? rng : NULL));
  else
    throw std::runtime_error("[RunFit]: Unknown minimiser");

  // Print the total chi2 on screen
  std::cout << "Total chi2 = " << chi2() << "\n" << std::endl;

  // Produce the report
  YAML::Emitter out;
  out << chi2;
  std::ofstream fout(ReplicaFolder + "/Report.yaml");
  //fout << chi2 << "\n";
  fout << "Status: " << status << std::endl;
  fout << out.c_str() << std::endl;
  fout.close();

  // Produce plots
  chi2.MakePlots(ReplicaFolder);

  // Delete random-number generator
  gsl_rng_free(rng);

  // Delete "Parameterisation" object
  delete NPFunc;

  // Report time elapsed
  t.stop();

  return status;
}
