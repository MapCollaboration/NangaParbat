//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/PV17.h"
#include "NangaParbat/PV19.h"
#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <apfel/timer.h>
#include <fstream>

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

  // Reading fit  parameters from an input card
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

  // Open datasets.yaml file that contains the list of datasets to be
  // fitted and push the corresponding pairs of "DataHandler" and
  // "ConvolutionTable" objects into the a vector.
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

  // Minimise the chi2 using the minimiser indicated in the input card
  bool status;
  if (fitconfig["Minimiser"].as<std::string>() == "minuit")
    status = MinuitMinimiser(chi2, fitconfig["Parameters"]);
  else if (fitconfig["Minimiser"].as<std::string>() == "ceres")
    status = CeresMinimiser(chi2, fitconfig["Parameters"]);
  else if (fitconfig["Minimiser"].as<std::string>() == "none")
    status = NoMinimiser(chi2, fitconfig["Parameters"]);
  else
    throw std::runtime_error("[RunFit]: Unknown minimiser");

  // =================================================================
  // Report section (should I separate it from the rest of this code?)
  // =================================================================
  // Print the total chi2
  std::cout << "Total chi2 = " << chi2() << "\n" << std::endl;

  // Get number of data points for each experiment
  const std::vector<int> ndata = chi2.GetDataPointNumbers();

  // Print individual chi2's
  const auto blocks = chi2.GetBlocks();
  for (int iexp = 0; iexp < (int) ndata.size(); iexp++)
    std::cout << iexp << ") " << blocks[iexp].first.GetName() << ", partial chi2 / #d.p.= " << chi2(iexp) << " (#d.p. = " << ndata[iexp] << ")" << std::endl;
  std::cout << "\n";

  // Produce the report in markdown
  std::ofstream fout("Report.md");

  // Summary
  fout << "# Summary\n";
  fout << fitconfig["Description"].as<std::string>() << "\n";
  fout << "Minimiser: **" << fitconfig["Minimiser"].as<std::string>() << "**\n";
  fout << "Parameterisation: **" << fitconfig["Parameterisation"].as<std::string>() << "**\n";
  fout << "Cut on transverse momentum: **$\\mathbf{q_T/Q}$ > " << fitconfig["qToQmax"].as<std::string>() << "**\n";
  fout << "Global $\\chi^2$ per number of data points: **" << chi2() << "**\n";

  // Fitted parameters
  const std::vector<double> pars = chi2.GetParameters();
  fout << "# Non-perturbative function\n";
  fout << chi2.GetNonPerturbativeFunction().LatexFormula() << "\n";
  fout << "## Parameters\n";
  for (auto const p : fitconfig["Parameters"])
    fout << "| " << p["name"].as<std::string>();;
  fout << "|\n";
  for (int i = 0; i < (int) pars.size(); i++)
    fout << "|:---:";
  fout << "|\n";
  for (auto const& p : pars)
    fout << " | " << p;
  fout << "|\n";

  // Table of chi2's and plots
  fout << chi2;
  fout << "\n";

  fout << "# Fit card\n";
  fout << "```\n";
  fout << fitconfig << "\n";
  fout << "```\n";

  fout << "# Dataset card\n";
  fout << "```\n";
  fout << datasets << "\n";
  fout << "```\n";

  fout << "# Configuration card\n";
  fout << "This card is (and has to be) in the folder where the interpolation"
       << " tables are stored (" << std::string(argv[3]) << "). This is actually"
       << " not used in the fit but it reports the parameters used to compute"
       << " the interpolation tables.\n";
  fout << "```\n";
  fout << YAML::LoadFile(std::string(argv[3]) + "/config.yaml") << "\n";
  fout << "```\n";

  fout.close();

  // Delete "Parameterisation" object
  delete NPFunc;

  // Report time elapsed
  t.stop();
  // =================================================================

  return 0;
}
