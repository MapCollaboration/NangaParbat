//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <math.h>

#include <ROOT/Minuit2/MnUserParameters.h>
#include <ROOT/Minuit2/MnMigrad.h>
#include <ROOT/Minuit2/FunctionMinimum.h>
#include <ROOT/Minuit2/MnPrint.h>

//_________________________________________________________________________________
// Davies-Webber-Stirling Parameterisation derived from the
// "Parameterisation" mother class
class DWS: public NangaParbat::Parameterisation
{
public:
  DWS(): Parameterisation{2, std::vector<double>{0.016, 0.54}} { };

  double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
  {
    if (ifunc < 0 || ifunc >= this->_nfuncs)
      throw std::runtime_error("[DWS::Evaluate]: function index out of range");

    const double g1  = this->_pars[0];
    const double g2  = this->_pars[1];
    const double Q02 = 3.2;

    return exp( - ( g1 + g2 * log(zeta / Q02) / 2 ) * pow(b, 2) / 2 );
  };
};

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
  DWS NPFunc{};

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

  // Define "Minuit" object
  NangaParbat::FcnMinuit fcn{chi2};

  // Create Minuit parameters with names
  ROOT::Minuit2::MnUserParameters upar;
  upar.Add("g1", 0.01, 0.001);
  upar.Add("g2", 0.1, 0.005);

  // create MIGRAD minimiser
  ROOT::Minuit2::MnMigrad migrad(fcn, upar);

  // Minimise
  ROOT::Minuit2::FunctionMinimum min = migrad();

  // Output of Minuit
  std::cout << "minimum: " << min << std::endl;

  // Now print (This also produces plots in pdf with ROOT)
  std::cout << "Total chi2 = " << chi2() << std::endl;
  std::cout << chi2;

  return 0;
}
