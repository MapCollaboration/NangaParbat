//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/nonpertfunctions.h"

//_________________________________________________________________________________
int main(int argc, char* argv[])
{
  // List the parameterisation currently available.
  if (argc > 1 && std::strncmp(argv[1], "python", 6) == 0)
    {
      std::cout << "=== ";
      for (auto const& p : NangaParbat::AvPars)
        std::cout << p.first << " ";
      std::cout << "===\n";
    }
  else
    {
      std::cout << "\nAvailable parameterisations:" << std::endl;
      for (auto const& p : NangaParbat::AvPars)
        std::cout << "- " << p.first << ": " << p.second->GetDescription() << std::endl;
      std::cout << "\n";
    }

  return 0;
}
