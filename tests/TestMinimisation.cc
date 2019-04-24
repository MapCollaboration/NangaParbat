//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <math.h>
#include <iostream>
#include <apfel/apfelxx.h>

#include <ROOT/Minuit2/MnUserParameters.h>
#include <ROOT/Minuit2/MnMachinePrecision.h>
#include <ROOT/Minuit2/MnMigrad.h>
#include <ROOT/Minuit2/FunctionMinimum.h>
#include <ROOT/Minuit2/MnPrint.h>

// Davies-Webber-Stirling Parameterisation derived from the
// "Parameterisation" mother class
class DWS: public NangaParbat::Parameterisation
{
public:
  DWS(): Parameterisation{2, std::vector<double>(2, 1.)} {};
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
int main()
{
  // Allocate "Parameterisation" derived object
  DWS NPFunc{};

  // Datafile
  const NangaParbat::DataHandler DHand{"TestData", YAML::LoadFile("../data/TestData/Table1.yaml")};

  // Convolution table
  const NangaParbat::ConvolutionTable CTable{YAML::LoadFile("../tables/Test_data.yaml")};

  // Define "ChiSquare" object
  NangaParbat::ChiSquare chi2{NPFunc};

  // Append dataset to the chi2 object
  chi2.AddBlock(std::make_pair(DHand, CTable));

  // Define "Minuit" object
  NangaParbat::FcnMinuit fcn{chi2};

  // Create Minuit parameters with names
  ROOT::Minuit2::MnUserParameters upar;
  upar.Add("g1", 0.01, 0.0001);
  upar.Add("g2", 0.5, 0.005);

  // create MIGRAD minimiser
  ROOT::Minuit2::MnMigrad migrad(fcn, upar);

  // Minimise
  ROOT::Minuit2::FunctionMinimum min = migrad();

  // Output of Minuit
  std::cout << "minimum: " << min << std::endl;

  return 0;
}
