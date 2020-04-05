//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"

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
  /*
  // Read configuration file
  NangaParbat::TMDGrid* TMDs = NangaParbat::mkTMD("PV19_n3ll");
  std::cout << std::scientific;
  for (int iqT = 0; iqT < (int) qTv.size(); iqT++)
    std::cout << qTv[iqT] << "\t" << TMDs->Evaluate(x, qTv[iqT], Q).at(ifl) / tmds[0][iqT] << std::endl;
  std::cout << "\n";
  delete TMDs;
  */
  return 0;
}
