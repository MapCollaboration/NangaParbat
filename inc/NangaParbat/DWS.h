//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

//_________________________________________________________________________________
// Davies-Webber-Stirling Parameterisation derived from the
// "Parameterisation" mother class
class DWS: public NangaParbat::Parameterisation
{
public:
  DWS(): Parameterisation{2, std::vector<double>{0.016, 0.54}} { };

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
