//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/bstar.h"

#include <apfel/apfelxx.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  double bstarCSS(double const& b, double const&)
  {
    const double bmax = 2 * exp( - apfel::emc);
    return b / sqrt( 1 + pow(b / bmax, 2) );
  }

  //_________________________________________________________________________________
  double bstarmin(double const& b, double const& Q)
  {
    const double bmax  = 2 * exp( - apfel::emc);
    const double bmin  = bmax / Q;
    const double power = 4;
    // Avoid numerical problems when b is too small
    if (b < 1e-4)
      return bmin;
    else
      //return bmax * pow( ( 1 - exp( - pow(b / bmax, power) ) ) /
      //		 ( 1 - exp( - pow(b / bmin, power) ) ), 1 / power);
      return bmax * pow( ( - expm1( - pow(b / bmax, power) ) ) /
                         ( - expm1( - pow(b / bmin, power) ) ), 1 / power);
  }
}
