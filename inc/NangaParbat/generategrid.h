//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <vector>

namespace NangaParbat
{
  /**
   * @brief Utility function to generate an interpolation grid
   * @param n: the number of nodes of the grid
   * @param min: the lower bound
   * @param max: the upper bound
   * @param ext: the number of extra nodes (default: 0)
   * @param lgt: whether the grid is logarithmically spaced (default: false)
   * @return a linearly-spaced grid with "n" nodes between "min" and
   * "max" plus "ext" extra nodes on the right.
   */
  std::vector<double> GenerateGrid(int const& n, double const& min, double const& max, int const& ext = 0, bool const& lgt = false);
}
