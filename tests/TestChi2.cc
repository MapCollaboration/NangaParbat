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
int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      std::cerr << "Usage: " << argv[0] << " <data file> <table>" << std::endl;
      exit(-1);
    }

  // Allocate "Parameterisation" derived object
  NangaParbat::DWS NPFunc{};

  // Datafile
  NangaParbat::DataHandler DHand{"TestData", YAML::LoadFile(argv[1])};

  // Convolution table
  apfel::Timer t;
  NangaParbat::ConvolutionTable CTable{YAML::LoadFile(argv[2]), 0.1};
  t.stop();

  // Define "ChiSquare" object
  NangaParbat::ChiSquare chi2{&NPFunc};

  // Append dataset to the chi2 object
  chi2.AddBlock(std::make_pair(&DHand, &CTable));

  // Compute chi2
  t.start();
  std::cout << "chi2 = " << chi2() << std::endl;
  t.stop();

  return 0;
}
