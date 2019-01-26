//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/minimisation.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  FcnMinuit::FcnMinuit(ChiSquare const& chi2):
    _chi2(chi2)
  {
  }

  //_________________________________________________________________________________
  double FcnMinuit::operator()(const std::vector<double>& pars) const
  {
    // Set the parameters of the parameterisation
    _chi2.SetParameters(pars);

    // Evaluate and return total chi2 (normalised to the total number
    // of points).
    return _chi2.Evaluate();
  }
}
