//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/parameterisation.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  Parameterisation::Parameterisation(std::string const& name, int const& nfuncs, std::vector<double> pars, bool const& anders):
    _name(name),
    _nfuncs(nfuncs),
    _pars(pars),
    _anders(anders)
  {
  }
}
