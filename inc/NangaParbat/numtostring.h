//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>

namespace NangaParbat
{
  /**
   * @brief Function that, given an integer 'i', outputs a string
   * version of 'i' of length 'len' preceeded by as many zeros as
   * needed to reach lenght 'len'.
   * @param i: number to transform in string
   * @param len: length of the string (default: 4)
   */
  std::string num_to_string(int const& i, int const& len = 4);
}
