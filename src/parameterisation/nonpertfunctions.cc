//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/nonpertfunctions.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  Parameterisation* GetParametersation(std::string const& name)
  {
    return AvPars.at(name);
  }
}
