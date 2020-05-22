//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/createtmdgrid.h"
#include "NangaParbat/factories.h"

#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 4 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateGrids <report folder> <pdf/ff> <output>\n" << std::endl;
      exit(-10);
    }

  // Produce the folder with the grids
  NangaParbat::ProduceTMDGrid(argv[1], argv[3], argv[2]);

  return 0;
}
