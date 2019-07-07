//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  // Davies-Webber-Stirling Parameterisation derived from the
  // "Parameterisation" mother class
  class DWS: public NangaParbat::Parameterisation
  {
  public:

    DWS(): Parameterisation{"DWS", 2, std::vector<double>{0.016, 0.54}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[DWS::Evaluate]: function index out of range");

      const double g1  = this->_pars[0];
      const double g2  = this->_pars[1];
      const double Q02 = 3.2;

      return exp( - ( g1 + g2 * log(zeta / Q02) / 2 ) * pow(b, 2) / 2 );
    };
  };

  class PV17: public NangaParbat::Parameterisation
  {
  public:

    PV17(): Parameterisation{"PV17", 2, std::vector<double>{0.285, 2.98, 0.173, 0.39}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[PV17::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      const double Npt    = this->_pars[0];
      const double alpha  = this->_pars[1];
      const double sigma  = this->_pars[2];
      const double lambda = this->_pars[3];

      const double g1  = Npt * pow(x, sigma) * pow((1 - x), alpha) / pow(0.1, sigma) / pow((1 - 0.1), alpha);
      const double g1a = g1;

      return exp( - g1a * pow(b / 2, 2)) * ( 1 - lambda * pow(g1a, 2) / ( 1 + lambda * g1a ) * pow(b / 2, 2) );
    };
  };
}
