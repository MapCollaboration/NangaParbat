//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/factories.h"

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateGrid <report folder> <output>\n" << std::endl;
      exit(-10);
    }

  // Produce the folder with the grids
  NangaParbat::ProduceTMDGrid(argv[1], argv[2]);

  // Read in grid
  NangaParbat::TMDGrid* TMDs = NangaParbat::mkTMD(argv[2]);

  //  Test grid
  const int ifl   = 2;
  const double x  = 0.1;
  const double kT = 0.2;
  const double Q  = 90;
  std::cout << std::scientific;
  std::cout << "\nxf_" << ifl << "(x = " << x << ", kT =" << kT << " GeV, Q = " << Q << " GeV) = " << TMDs->Evaluate(x, kT, Q).at(ifl) << std::endl;
  std::cout << "\n";

  // Performance test
  apfel::Timer t;
  const int n = 1000000;
  std::cout << "Making " << n << " TMD calls... ";
  for (int i = 0; i < n; i++)
    TMDs->Evaluate(x, kT, Q);
  t.stop();
  delete TMDs;

  return 0;
}
