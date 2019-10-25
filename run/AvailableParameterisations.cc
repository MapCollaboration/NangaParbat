//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/nonpertfunctions.h"

//_________________________________________________________________________________
int main()
{
  // List the parameterisation currently available .
  std::cout << "\nAvailable parameterisations:" << std::endl;
  for (auto const& p : NangaParbat::AvPars)
    std::cout << "- " << p.first << ": " << p.second->GetDescription() << std::endl;
  std::cout << "\n";

  return 0;
}
