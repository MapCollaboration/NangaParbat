//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <ROOT/Minuit2/MnUserParameters.h>
#include <ROOT/Minuit2/MnMigrad.h>
#include <ROOT/Minuit2/FunctionMinimum.h>
#include <ROOT/Minuit2/MnPrint.h>

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

  // Define "Minuit" object
  NangaParbat::FcnMinuit fcn{chi2};

  // Create Minuit parameters with name, starting value, step and,
  // when available, upper and lower bounds.
  ROOT::Minuit2::MnUserParameters upar;
  for (auto const p : fitconfig["Parameters"])
    {
      upar.Add(p["name"].as<std::string>(), p["starting_value"].as<double>(), p["step"].as<double>());

      // Set limits if required
      if (p["lower_bound"])
        upar.SetLowerLimit(p["name"].as<std::string>(), p["lower_bound"].as<double>());

      if (p["upper_bound"])
        upar.SetUpperLimit(p["name"].as<std::string>(), p["upper_bound"].as<double>());

      // Fix parameter if required
      if (p["fix"] && p["fix"].as<bool>())
        upar.Fix(p["name"].as<std::string>());
    }

  // Create MIGRAD minimiser
  ROOT::Minuit2::MnMigrad minimiser(fcn, upar);

  // Increase verbosity of Minuit
  minimiser.Minimizer().Builder().SetPrintLevel(2);

  // Minimise
  ROOT::Minuit2::FunctionMinimum min = minimiser();

  // Output of Minuit
  std::cout << "minimum: " << min << std::endl;

  // Now print (This also produces plots in pdf with ROOT)
  std::cout << "Total chi2 = " << chi2() << std::endl;
  std::cout << chi2;

  // Delete parameterisation
  delete NPFunc;

  // Report time elapsed
  t.stop();

  return 0;
}
