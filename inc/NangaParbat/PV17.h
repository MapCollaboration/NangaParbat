//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  // Pavia 2017 Parameterisation derived from the "Parameterisation"
  // mother class
  class PV17: public NangaParbat::Parameterisation
  {
  public:

    PV17(): Parameterisation{"PV17", 2, std::vector<double>{0.13, 0.285, 2.98, 0.173, 0.39}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[PV17::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Free paraMeters
      const double g2     = this->_pars[0];
      const double Npt    = this->_pars[1];
      const double alpha  = this->_pars[2];
      const double sigma  = this->_pars[3];
      const double lambda = this->_pars[4];

      // TMD PDFs
      const double Q02  = 1;
      const double xhat = 0.1;
      const double g1   = Npt * pow(x / xhat, sigma) * pow((1 - x) / (1 - xhat), alpha);

      return exp( - ( g1 + g2 * log(zeta / Q02) / 2 ) * b * b ) * ( 1 - lambda * pow(g1 * b / 2, 2) / ( 1 + lambda * g1 ) );
    };
  };
}
