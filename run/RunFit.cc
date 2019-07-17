//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <apfel/timer.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./RunFit <fit configuration file> <path to data folder> <path to tables folder>\n" << std::endl;
      exit(-10);
    }

  // Timer
  apfel::Timer t;

  // Allocate "FastInterface" object reading the parameters from an
  // input card.
  const YAML::Node fitconfig = YAML::LoadFile(argv[1]);

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

  // Define "ChiSquare" object with a given qT / Q cut
  NangaParbat::ChiSquare chi2{*NPFunc, fitconfig["qToQmax"].as<double>()};

  // Open datasets.yaml file that contains the list of tables to be
  // produced and push data sets into the a vector of DataHandler
  // objects.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[2]) + "/datasets.yaml");
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        std::cout << "Reading " << ds["name"].as<std::string>() << " ..." << std::endl;
        // Datafile
        const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
        const NangaParbat::DataHandler dh{ds["name"].as<std::string>(), YAML::LoadFile(datafile)};

        // Convolution table
        const std::string table = std::string(argv[3]) + "/" + ds["name"].as<std::string>() + ".yaml";
        const NangaParbat::ConvolutionTable ct{YAML::LoadFile(table)};

        // Add chi2 block
        chi2.AddBlock(std::make_pair(dh, ct));
      }

  // Minimise the chi2
  bool status;
  if (fitconfig["Minimiser"].as<std::string>() == "minuit")
    status = MinuitMinimiser(chi2, fitconfig["Parameters"]);
  else if (fitconfig["Minimiser"].as<std::string>() == "ceres")
    status = CeresMinimiser(chi2, fitconfig["Parameters"]);
  else
    throw std::runtime_error("[RunFit]: Unknown minimiser");

  // Now print the total chi2
  std::cout << "Total chi2 = " << chi2() << "\n" << std::endl;

  // Get number of data points for each experiment
  const std::vector<int> ndata = chi2.GetDataPointNumbers();

  // Print individual chi2's
  for (int iexp = 0; iexp < (int) ndata.size(); iexp++)
    std::cout << iexp << ") Partial chi2 / #d.p.= " << chi2(iexp) << " (#d.p. = " << ndata[iexp] << ")" << std::endl;
  std::cout << "\n";

  // Finally, this also produces plots
  std::cout << chi2;

  // Delete parameterisation
  delete NPFunc;

  // Report time elapsed
  t.stop();

  return 0;
}
