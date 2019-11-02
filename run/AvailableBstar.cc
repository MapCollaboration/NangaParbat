//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/bstar.h"

#include <cstring>
#include <iostream>

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // List the parameterisation currently available.
  if (argc > 1 && std::strncmp(argv[1], "python", 6) == 0)
    {
      std::cout << "=== ";
      for (auto const& b : NangaParbat::bstarMap)
        std::cout << b.first << " ";
      std::cout << "===\n";
    }
  else
    {
      std::cout << "\nAvailable b* prescriptions:" << std::endl;
      for (auto const& b : NangaParbat::bstarMap)
        std::cout << "- " << b.first << std::endl;
      std::cout << "\n";
    }

  return 0;
}
