//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/nonpertfunctions.h"

#include <math.h>
#include <iostream>
#include <apfel/apfelxx.h>

//_________________________________________________________________________________
// Main program
int main()
{
  // Allocate "Parameterisation" derived object
  NangaParbat::DWS NPFunc{};

  // Datafile
  NangaParbat::DataHandler DHand{"CDF_Run_I", YAML::LoadFile("../data/TestData/Table1.yaml")};

  // Convolution table
  NangaParbat::ConvolutionTable CTable{YAML::LoadFile("../tables/Test_data.yaml"), 0.1};

  // Define "ChiSquare" object
  NangaParbat::ChiSquare chi2{&NPFunc};

  // Append dataset to the chi2 object
  chi2.AddBlock(std::make_pair(&DHand, &CTable));

  // Compute chi2
  std::cout << "chi2 = " << chi2() << std::endl;
  /*
    // Performance test
    apfel::Timer t;
    const int n = 1000;
    for (int i = 0; i < n; i++)
        chi2();
    std::cout << "Evaluating chi2 " << n << " times... ";
    t.stop(true);
  */
  return 0;
}
