//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/fastinterface.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/utilities.h"

#include <fstream>
#include <apfel/timer.h>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 5 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateTables <configuration file> <path to data folder> <output folder> <test tables? [y/n]> [optional selected datasets]\n" << std::endl;
      exit(-10);
    }

  // Vector of selected datasets
  std::vector<std::string> selsets;
  for (int i = 5; i < argc; i++)
    selsets.push_back(std::string(argv[i]));

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
      if(std::find(selsets.begin(), selsets.end(), ds["name"].as<std::string>()) != selsets.end() || selsets.empty())
        {
          std::cout << "- " << ds["name"].as<std::string>() << std::endl;
          const std::string datafile = std::string(argv[2]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
          DHVect.push_back(NangaParbat::DataHandler{ds["name"].as<std::string>(), YAML::LoadFile(datafile)});
        }

  // Compute tables
  const std::vector<YAML::Emitter> Tabs = FIObj.ComputeTables(DHVect, NangaParbat::bstarmin);

  // Dump table to file
  for (auto const& tab : Tabs)
    {
      std::ofstream fout(std::string(argv[3]) + YAML::Load(tab.c_str())["name"].as<std::string>() + ".yaml");
      fout << tab.c_str() << std::endl;
      fout.close();
    }

  // Now test tables if required
  if (std::strncmp(argv[4], "y", 1) == 0)
    {
      // Allocate "Parameterisation" derived object. Use DWS for the
      // test.
      NangaParbat::DWS NPFunc{};

      // Compute direct predictions
      auto const fNP = [=] (double const& x, double const& b, double const& zeta) -> double { return NPFunc.Evaluate(x, b, zeta, 0); };
      const std::vector<std::vector<double>> dc = FIObj.DirectComputation(DHVect, NangaParbat::bstarmin, fNP, fNP);

      // No read convolution tables and compute predictions from the grids
      std::vector<std::vector<double>> gc;
      for (auto const& exp : datasets)
        for (auto const& ds : exp.second)
          {
            const std::string table = std::string(argv[3]) + "/" + ds["name"].as<std::string>() + ".yaml";
            const NangaParbat::ConvolutionTable ct{YAML::LoadFile(table)};
            gc.push_back(ct.GetPredictions(fNP));
          }

      std::cout << "Testing tables against direct computation...\n" << std::endl;
      // Report results
      std::cout << std::scientific;
      for (int i = 0; i < (int) gc.size(); i++)
        {
          std::cout << "Dataset " << i + 1 << ")" << std::endl;
          std::cout << "  Direct          Table           Ratio" << std::endl;
          for (int j = 0; j < (int) gc[i].size(); j++)
            std::cout << dc[i][j] << "\t" << gc[i][j] << "\t" << dc[i][j] / gc[i][j] << std::endl;
          std::cout << "\n";
        }
    }
  return 0;
}
