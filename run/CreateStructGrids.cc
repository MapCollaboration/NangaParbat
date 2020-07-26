//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//


#include "NangaParbat/createstructgrid.h"
#include "NangaParbat/structgrid.h"
#include "NangaParbat/factories.h"

#include <cstring>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // Check that the input is correct otherwise stop the code
  if (argc < 5 || strcmp(argv[1], "--help") == 0)
    {
      std::cout << "\nInvalid Parameters:" << std::endl;
      std::cout << "Syntax: ./CreateStructGrids <main fit directory with TMD grids> <name of TMD PDF set> <name of TMD FF set> <output> <[optional] replica ID>\n" << std::endl;
      exit(-10);
    }

  // Set replica ID, if it is specified
  std::string rID;
  if (argv[5])
    rID = argv[5];
  else
    rID = "none";

  // Produce grids and their folder
  NangaParbat::ProduceStructGrid(argv[1], argv[2], argv[3], argv[4], rID);

  return 0;
}
