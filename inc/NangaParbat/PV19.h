//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>
#include <apfel/constants.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  // Pavia 2019 Parameterisation derived from the "Parameterisation"
  // mother class
  class PV19: public NangaParbat::Parameterisation
  {
  public:

    PV19(): Parameterisation{"PV19", 2, std::vector<double>{0.13, 0.285, 2.98, 0.173, 0.39, 0.}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[PV19::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Free paraMeters
      const double g2     = this->_pars[0];
      const double Npt    = this->_pars[1];
      const double alpha  = this->_pars[2];
      const double sigma  = this->_pars[3];
      const double lambda = this->_pars[4];
      const double delta  = this->_pars[5];

      // TMD PDFs
      const double Q02 = 1;
      const double xhat = 0.1;
      const double g1   = Npt * ( pow(x, sigma) + delta ) / ( pow(xhat, sigma) + delta ) * pow((1 - x) / (1 - xhat), alpha);

      // Correction to 'b' due to the bmin prescription. Notice that
      // the non-perturbative function does not tend to one anymore
      // for 'b' tending to zero. (Not sure this is correct).
      //const double bmin  = 2 * exp( - apfel::emc) / sqrt(zeta);
      //const double power = 4;
      //const double bc    = b / pow( ( 1 - exp( - pow(b / bmin, power) ) ), 1 / power);

      //return exp( - ( g1 + g2 * log(zeta / Q02) / 2 ) * bc * bc ) * ( 1 - lambda * pow(g1 * bc / 2, 2) / ( 1 + lambda * g1 ) );
      return exp( - ( g1 + g2 * log(zeta / Q02) / 2 ) * b * b ) * ( 1 - lambda * pow(g1 * b / 2, 2) / ( 1 + lambda * g1 ) );
    };
  };
}
