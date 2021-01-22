//
// Author: Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#pragma once

#include <string>
#include <sstream>
#include <algorithm>

namespace NangaParbat
{
  /**
   * @brief Function that, given a number 'a_value', outputs a string
   * version of 'a_value' rounding the double to show only
   * 'n' significant figures.
   * @param a_value: number to transform in string
   * @param n: length of the string (default: 3)
   */
  std::string to_string_with_precision(const double a_value, const int n = 3);
}
