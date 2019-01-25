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
    // Set the parameters of the parameterisation
    _func.SetParameters(pars);

    // Get the number of functions contained in the parameterisation
    const int nfuncs = _func.GetNumberOfFunctions();

    // Define lambda functions to feed for the computation of the
    // chi2.
    std::function<double(double const&, double const&, double const&)> func1;
    std::function<double(double const&, double const&, double const&)> func2;
    if (nfuncs == 1)
      {
	func1 = [this] (double const& x, double const& b, double const& zeta) -> double{ return _func.Evaluate(x, b, zeta, 0); };
	func2 = func1;
      }
    else if (nfuncs == 2)
      {
	func1 = [this] (double const& x, double const& b, double const& zeta) -> double{ return _func.Evaluate(x, b, zeta, 0); };
	func2 = [this] (double const& x, double const& b, double const& zeta) -> double{ return _func.Evaluate(x, b, zeta, 1); };
      }
    else
      throw std::runtime_error("[FcnMinuit::operator()]: only one or two parameterised functions are allowed");

    return _chi2.Evaluate(func1, func2);
  }
}
