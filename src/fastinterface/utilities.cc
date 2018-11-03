//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/utilities.h"

#include <iostream>
#include <cmath> 
#include <apfel/messages.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  double bstar(double const& b, double const& bmax)
  {
    return b / sqrt( 1 + pow(b / bmax, 2) );
  }

  //_________________________________________________________________________________
  std::vector<double> GenerateQGrid(int const& n, double const& min, double const& max, int const& ext)
  {
    std::vector<double> grid(n+ext+1);
    const double step = ( max - min ) / n;
    for (int i = 0; i <= n + ext; i++)
      grid[i] = min + i * step;
    return grid;
  }
}
