//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/fcnceres.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  FcnCeres::FcnCeres(ChiSquare const& chi2):
    _chi2(chi2)
  {
  }

  //_________________________________________________________________________________
  bool FcnCeres::operator()(double const* const* parameters, double* residuals) const
  {
    // Put parameters into a vector.
    const int Np = _chi2.GetNumberOfParameters();

    std::vector<double> vpars(Np);
    for (int ip = 0; ip < Np; ip++)
      vpars[ip] = parameters[0][ip];

    // Set the parameters of the parameterisation
    _chi2.SetParameters(vpars);

    // Now get residuals for all experiments and put them in the array
    int j = 0;
    for (int iexp = 0; iexp < (int) _chi2.GetNumberOfExperiments(); iexp++)
      {
        const std::vector<double> vres = _chi2.GetResiduals(iexp);
        for (int i = 0; i < (int) vres.size(); i++)
          residuals[j++] = vres[i];
      }
    return true;
  }
}
