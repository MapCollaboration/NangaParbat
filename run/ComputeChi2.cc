//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/DWS.h"
#include "NangaParbat/chisquare.h"

//_________________________________________________________________________________
// Main program
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if(argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << std::endl;
      std::cout << "Invalid Parameters:" << std::endl;
      std::cout << "Syntax: ./ComputeChi2 <path to data folder> <path to tables folder>" << std::endl;
      std::cout << std::endl;
      exit(-10);
    }

  // Allocate "Parameterisation" derived object
  //DWS NPFunc{};
  PV17 NPFunc{};

  // Define "ChiSquare" object with a given qT / Q cut
  const double qToQmax = 0.3;
  NangaParbat::ChiSquare chi2{NPFunc, qToQmax};

  // Open datasets.yaml file that contains the list of tables to be
  // produced and push data sets into the a vector of DataHandler
  // objects.
  const YAML::Node datasets = YAML::LoadFile(std::string(argv[1]) + "/datasets.yaml");
  for (auto const& exp : datasets)
    for (auto const& ds : exp.second)
      {
        std::cout << "Reading " << ds["name"].as<std::string>() << " ..." << std::endl;
        // Datafile
        const std::string datafile = std::string(argv[1]) + "/" + exp.first.as<std::string>() + "/" + ds["file"].as<std::string>();
        const NangaParbat::DataHandler dh{ds["name"].as<std::string>(), YAML::LoadFile(datafile)};

        // Convolution table
        const std::string table = std::string(argv[2]) + "/" + ds["name"].as<std::string>() + ".yaml";
        const NangaParbat::ConvolutionTable ct{YAML::LoadFile(table)};

        // Add chi2 block
        chi2.AddBlock(std::make_pair(dh, ct));
      }

  // Get number of data points for each experiment
  const std::vector<int> ndata = chi2.GetDataPointNumbers();

  // // Compute total chi2 with the initial parameters
  // std::cout << "\nTotal chi2 = " << chi2() << std::endl;
  // for (int iexp = 0; iexp < (int) ndata.size(); iexp++)
  //   std::cout << iexp << ") Partial chi2 / #d.p.= " << chi2(iexp) << " (#d.p = " << ndata[iexp] << ")" << std::endl;
  // std::cout << "\n";

  // // Update parameters and recompute chi2's
  // chi2.SetParameters({1e-3, 1e-3, 1e-3, 1e-3});
  // std::cout << "Total chi2 = " << chi2() << std::endl;
  // for (int iexp = 0; iexp < (int) ndata.size(); iexp++)
  //   std::cout << iexp << ") Partial chi2 / #d.p.= " << chi2(iexp) << " (#d.p = " << ndata[iexp] << ")" << std::endl;
  // std::cout << "\n";

  // Now print (This also produces plots in pdf with ROOT)
  std::cout << chi2;

  return 0;
}
