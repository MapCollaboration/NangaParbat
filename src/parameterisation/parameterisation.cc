//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/parameterisation.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  Parameterisation::Parameterisation(int const& nfuncs, std::vector<double> pars):
    _nfuncs(nfuncs),
    _pars(pars)
  {
  }
}
