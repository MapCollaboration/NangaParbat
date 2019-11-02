//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <map>
#include <string>
#include <functional>

namespace NangaParbat
{
  /**
   * @brief b* prescription a la Collins
   * @param b: the impact parameter
   * @param Q: the hard scale
   * @return b*
   */
  double bstarCSS(double const& b, double const& Q);

  /**
   * @brief b* prescription with bmin
   * @param b: the impact parameter
   * @param Q: the hard scale
   * @return b*
   */
  double bstarmin(double const& b, double const& Q);

  /**
   * @brief Map of available b* star functions
   */
  const std::map<std::string, std::function<double(double const&, double const&)>> bstarMap
  {
    {"bstarCSS", bstarCSS},
    {"bstarmin", bstarmin}
  };
}
