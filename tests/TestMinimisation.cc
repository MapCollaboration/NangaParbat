//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"

#include <math.h>
#include <iostream>
#include <apfel/apfelxx.h>

#include <root/Minuit2/MnUserParameters.h>
#include <root/Minuit2/MnMachinePrecision.h>
#include <root/Minuit2/MnMigrad.h>
#include <root/Minuit2/FunctionMinimum.h>
#include <root/Minuit2/MnPrint.h>

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
    const double Q02 = 3;
    return exp( - ( g1 + g2 * log(zeta / Q02) ) * pow(b, 2) );
  };
};

//_________________________________________________________________________________
// Main program
int main()
{
  // Allocate "Parameterisation" derived object
  DWS NPFunc{};

  // Datafile
  const NangaParbat::DataHandler DHand{"CDF_Run_I", YAML::LoadFile("../data/HEPData-ins505738-v1-yaml/Table1.yaml")};

  // Convolution table
  const NangaParbat::ConvolutionTable CTable{YAML::LoadFile("../tables/CDF_Run_I.yaml")};

  // Define "ChiSquare" object
  NangaParbat::ChiSquare chi2{NPFunc};

  // Append dataset to the chi2 object
  chi2.AddBlock(std::make_pair(DHand, CTable));

  // Define "Minuit" object
  NangaParbat::FcnMinuit fcn{chi2};

  // Create Minuit parameters with names
  ROOT::Minuit2::MnUserParameters upar;
  upar.Add("g1", 1, 0.1);
  upar.Add("g2", 1, 0.1);

  // create MIGRAD minimiser
  ROOT::Minuit2::MnMigrad migrad(fcn, upar);

  // Minimise
  ROOT::Minuit2::FunctionMinimum min = migrad();

  // output
  std::cout << "minimum: " << min << std::endl;

  return 0;
}
