//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/parameterisation.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  Parameterisation::Parameterisation(int const& nfuncs):
    _nfuncs(nfuncs)
  {
    if (nfuncs < 1)
      throw std::runtime_error("[Parameterisation::Parameterisation]: the number of parameterised functions cannot be negative");
  }
  
  //_________________________________________________________________________________
  double Parameterisation::Evaluate(double const&, double const&, double const&, int const& ifunc) const
  {
    if (ifunc < 0 || ifunc >= _nfuncs)
      throw std::runtime_error("[Parameterisation::Evaluate]: function index out of range");

    return 0;
  }

  //_________________________________________________________________________________
  double Parameterisation::Derive(double const&, double const&, double const&, int const& ifunc, int const& ipar) const
  {
    if (ifunc < 0 || ifunc >= _nfuncs)
      throw std::runtime_error("[Parameterisation::Derive]: function index out of range");

    if (ipar < 0 || ifunc > _pars.size())
      throw std::runtime_error("[Parameterisation::Derive]: parameter index out of range");

    return 0;
  }
}
