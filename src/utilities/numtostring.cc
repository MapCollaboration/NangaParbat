//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/numtostring.h"

#include <stdexcept>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::string num_to_string(int const& i, int const& len)
  {
    std::string str = std::to_string(i);
    const int bf = len - str.size();
    if (bf < 0)
      throw std::runtime_error("[num_to_string]: The input integer exceeds the string length.");
    for (int j = 0; j < bf; j++)
      str = "0" + str;
    return str;
  }
}
