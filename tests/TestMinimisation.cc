//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/minimisation.h"
#include "NangaParbat/DWS.h"

#include <math.h>
#include <iostream>

#include <ROOT/Minuit2/MnUserParameters.h>
#include <ROOT/Minuit2/MnMachinePrecision.h>
#include <ROOT/Minuit2/MnMigrad.h>
#include <ROOT/Minuit2/FunctionMinimum.h>
#include <ROOT/Minuit2/MnPrint.h>

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
