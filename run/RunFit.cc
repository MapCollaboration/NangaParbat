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
  if (argc < 6 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./RunFit <output dir> <fit configuration file> <path to data folder> <path to tables folder> <replica ID>\n" << std::endl;
      exit(-10);
    }

  // Timer
  apfel::Timer t;

  // Reading fit  parameters from an input card
  YAML::Node fitconfig = YAML::LoadFile(argv[2]);

  // Allocate "Parameterisation" derived object
  NangaParbat::Parameterisation *NPFunc = NangaParbat::GetParametersation(fitconfig["Parameterisation"].as<std::string>());

  // Initialise GSL random-number generator
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_ranlxs2);
  gsl_rng_set(rng, fitconfig["Seed"].as<int>());

  // Replica ID number
  const int ReplicaID = atoi(argv[5]);

  // Create replica folder
  const std::string OutputFolder = std::string(argv[1]) + "/replica_" + std::string(argv[5]);
  mkdir((OutputFolder).c_str(), ACCESSPERMS);

  // Define "ChiSquare" object with a given qT / Q cut
  NangaParbat::ChiSquare chi2{NPFunc};

  // Set parameters for the t0 predictions using "t0parameters" in the
  // configuration card only if the the t0 has been enabled and the
  // central replica is not being computed.
  if (fitconfig["t0prescription"].as<bool>())
    NPFunc->SetParameters(fitconfig["t0parameters"].as<std::vector<double>>());

  // Open datasets.yaml file that contains the list of datasets to be
  // fitted and push the corresponding pairs of "DataHandler" and
  // "ConvolutionTable" objects into the a vector.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[3]) + "/datasets.yaml");
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        std::cout << "Reading table for " << ds["name"].as<std::string>() << "..." << std::endl;

        // Convolution table
        const std::string table = std::string(argv[4]) + "/" + ds["name"].as<std::string>() + ".yaml";
        NangaParbat::ConvolutionTable ct{YAML::LoadFile(table), fitconfig["qToQmax"].as<double>()};
        //ct.NumericalAccuracy(NPFunc->Function());

        // Datafile
        const std::string datafile = std::string(argv[3]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
        NangaParbat::DataHandler dh{ds["name"].as<std::string>(), YAML::LoadFile(datafile), rng, ReplicaID,
                                    (fitconfig["t0prescription"].as<bool>() ? ct.GetPredictions(NPFunc->Function()) : std::vector<double>{})};

        // Add chi2 block
        chi2.AddBlock(std::make_pair(&dh, &ct));
      }
  // Report time elapsed
  t.stop();

  // Minimise the chi2 using the minimiser indicated in the input card
  t.start();
  bool status;
  if (fitconfig["Minimiser"].as<std::string>() == "none")
    status = NoMinimiser(chi2, fitconfig["Parameters"]);
  else if (fitconfig["Minimiser"].as<std::string>() == "minuit")
    status = MinuitMinimiser(chi2, fitconfig["Parameters"], (fitconfig["Paramfluct"].as<bool>() ? rng : NULL));
  else if (fitconfig["Minimiser"].as<std::string>() == "ceres")
    status = CeresMinimiser(chi2, fitconfig["Parameters"], (fitconfig["Paramfluct"].as<bool>() ? rng : NULL));
  else if (fitconfig["Minimiser"].as<std::string>() == "scan")
    status = MinuitScan(chi2, fitconfig["Parameters"], std::string(argv[1]));
  else
    throw std::runtime_error("[RunFit]: Unknown minimiser");

  // Print the total chi2 on screen
  std::cout << "Total chi2 = " << chi2() << "\n" << std::endl;

  // Produce the report
  YAML::Emitter out;
  out << chi2;
  std::ofstream rout(OutputFolder + "/Report.yaml");
  rout << "Status: " << status << std::endl;
  rout << out.c_str() << std::endl;
  rout.close();

  // Produce plots and modify fitconfig.yaml to dump into the output
  // folder. Do it only for replica 0.
  if (ReplicaID == 0)
    {
      chi2.MakePlots(OutputFolder);
      const std::vector<double> pars = chi2.GetParameters();
      int i = 0;
      for (auto p : fitconfig["Parameters"])
        p["starting_value"] = pars[i++];
      fitconfig["t0parameters"] = pars;
      std::ofstream fout(OutputFolder + "/fitconfig.yaml");
      fout << fitconfig;
      fout.close();
    }

  // Delete random-number generator
  gsl_rng_free(rng);

  // Delete "Parameterisation" object
  delete NPFunc;

  // Report time elapsed
  t.stop();

  return status;
}
