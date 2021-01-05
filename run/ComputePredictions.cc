//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/nonpertfunctions.h"
#include "NangaParbat/convolutiontable.h"

#include <apfel/timer.h>
#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./ComputePredictions <table>\n" << std::endl;
      exit(-10);
    }

  // Allocate "Parameterisation" object
  NangaParbat::DWS NPFunc{};

  // Upload convolution table
  NangaParbat::ConvolutionTable ct{argv[1]};

  // Timer
  apfel::Timer t;

  // Get predictions and print them
  for (double p : ct.GetPredictions(NPFunc.Function()))
    std::cout << std::scientific << p << std::endl;

  t.stop();
  return 0;
}
