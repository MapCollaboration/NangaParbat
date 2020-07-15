//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/fcnminuit.h"
#include "NangaParbat/nonpertfunctions.h"

#include <math.h>
#include <iostream>

#include <root/Minuit2/MnUserParameters.h>
#include <root/Minuit2/MnMachinePrecision.h>
#include <root/Minuit2/MnMigrad.h>
#include <root/Minuit2/FunctionMinimum.h>
#include <root/Minuit2/MnPrint.h>

//_________________________________________________________________________________
// Main program
int main()
{
  // Allocate "Parameterisation" derived object
  NangaParbat::DWS NPFunc{};

  // Datafile
  NangaParbat::DataHandler DHand{"TestData", YAML::LoadFile("../data/TestData/Table1.yaml")};

  // Convolution table
  NangaParbat::ConvolutionTable CTable{YAML::LoadFile("../tables/Test_data.yaml")};

  // Define "ChiSquare" object
  NangaParbat::ChiSquare chi2{&NPFunc};

  // Append dataset to the chi2 object
  chi2.AddBlock(std::make_pair(&DHand, &CTable));

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
