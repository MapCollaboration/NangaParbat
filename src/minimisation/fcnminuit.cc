//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fcnminuit.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  FcnMinuit::FcnMinuit(ChiSquare const& chi2):
    _chi2(chi2)
  {
  }

  //_________________________________________________________________________________
  double FcnMinuit::operator()(std::vector<double> const& pars) const
  {
    // Set the parameters of the parameterisation
    _chi2.SetParameters(pars);

    // Evaluate and return total chi2 (normalised to the total number
    // of points).
    return _chi2.Evaluate();
  }

  //_________________________________________________________________________________
  FcnMinuitGrad::FcnMinuitGrad(ChiSquare const& chi2):
    _chi2(chi2)
  {
  }

  //_________________________________________________________________________________
  double FcnMinuitGrad::operator()(std::vector<double> const& pars) const
  {
    // Set the parameters of the parameterisation
    _chi2.SetParameters(pars);

    // Evaluate and return total chi2 (normalised to the total number
    // of points).
    return _chi2.Evaluate();
  }

  //_________________________________________________________________________________
  std::vector<double> FcnMinuitGrad::Gradient(const std::vector<double>& pars) const
  {
    // Set the parameters of the parameterisation
    _chi2.SetParameters(pars);

    // Evaluate and return total chi2 (normalised to the total number
    // of points).
    return _chi2.Derive();
  }
}
