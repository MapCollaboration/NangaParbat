//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

// YAML
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  /**
   * @brief b* prescription to implement the CSS prescription.
   */
  double bstar(double const& b, double const& bmax);

  /**
   * @brief Utility function to generate an interpolation grid
   */
  std::vector<double> GenerateQGrid(int const& n, double const& min, double const& max);
}
