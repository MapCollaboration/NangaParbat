//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "apfel/constants.h"

double B2FOqq(double const& x, double const& z, double const& qT, double const& Q)
{
  return 2 * apfel::CF * ( ( 1 - x ) * ( 1 - z ) + 4 * x * z + ( 1 + x * x * z * z ) * Q * Q / x / z / qT / qT ); 
}

double B2FOqg(double const& x, double const& z, double const& qT, double const& Q)
{
  return 2 * apfel::TR * ( 8 * x * ( 1 - x ) + ( x * x + ( 1 - x ) * ( 1 - x ) ) * ( z * z + ( 1 - z ) * ( 1 - z ) ) * ( 1 - x ) * Q * Q / x / z / z / qT / qT ); 
}

double B2FOgq(double const& x, double const& z, double const& qT, double const& Q)
{
  return 2 * apfel::CF * ( ( 1 - x ) * z + 4 * x * ( 1 - z ) + ( 1 + x * x * ( 1 - z ) * ( 1 - z ) ) * ( 1 - z ) * Q * Q / x / z / z / qT / qT ); 
}

double BLFOqq(double const& x, double const& z)
{
  return 8 * apfel::CF * x * z;
}

double BLFOqg(double const& x, double const&)
{
  return 16 * apfel::TR * x * ( 1 -  x );
}

double BLFOgq(double const& x, double const& z)
{
  return 8 * apfel::CF * x * ( 1 - z );
}

