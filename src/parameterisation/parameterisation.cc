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

  //_________________________________________________________________________________
  std::function<double(double const&, double const&, double const&, int const&)> Parameterisation::Function() const
  {
    return [this] (double const& x, double const& b, double const& zeta, int const& ifun) -> double{ return Evaluate(x, b, zeta, ifun); };
  }

  //_________________________________________________________________________________
  std::function<double(double const&, double const&, double const&, int const&, int const&)> Parameterisation::Derivative() const
  {
    return [this] (double const& x, double const& b, double const& zeta, int const& ifun, int const& ipar) -> double{ return Derive(x, b, zeta, ifun, ipar); };
  }
}
