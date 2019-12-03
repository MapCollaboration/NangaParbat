//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/generategrid.h"

#include <cmath>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::vector<double> GenerateGrid(int const& n, double const& min, double const& max, int const& ext, bool const& lgt)
  {
    std::vector<double> grid(n+ext+1);
    if (lgt)
      {
        const double step = log( max / min ) / n;
        for (int i = 0; i <= n + ext; i++)
          grid[i] = min * exp( i * step );
      }
    else
      {
        const double step = ( max - min ) / n;
        for (int i = 0; i <= n + ext; i++)
          grid[i] = min + i * step;
      }
    return grid;
  }
}
