//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/minimisation.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  FcnMinuit::FcnMinuit(ChiSquare const& chi2, Parameterisation const& func):
    _chi2(chi2),
    _func(func)
  {
  }

  //_________________________________________________________________________________
  double FcnMinuit::operator ()(const std::vector<double>& pars) const
  {
    _func.SetParameters(pars);
    const auto func = [this] (double const& x, double const& b, double const& zeta) -> double{ return _func.Evaluate(x, b, zeta); };
    return _chi2.Evaluate(func);
  }
}
