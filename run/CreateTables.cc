//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/computetables.h"
#include "NangaParbat/convolutiontable.h"

#include <iostream>
#include <math.h>

#include <apfel/timer.h>

//_________________________________________________________________________________
// Non-perturnative function
double fNP(double const&, double const& b, double const& zetaf)
{
  const double g1 = 0.02;
  const double g2 = 0.5;
  const double Q0 = 1.6;
  return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );
}

//_________________________________________________________________________________
// Main program
int main(int argc, char **argv)
{
  if (argc != 3)
    {
      std::cout << "\nusage: ./CreateTable config.yaml datasets.yaml\n" << std::endl;
      exit(-1);
    }

  // Compute table
  NangaParbat::ComputeTables(argv[1], argv[2]);

  // Convolute table
  const NangaParbat::ConvolutionTable Table{"../Tables/TestData_Table1.yaml"};
  for (auto const& p : Table.Convolute(fNP))
    std::cout << p.first << "  " << p.second << std::endl;

  apfel::Timer t;  
  for (int i = 0; i < 8000; i++)
    for (auto const& p : Table.Convolute(fNP))
      p.second;
  t.stop();

  return 0;
}
