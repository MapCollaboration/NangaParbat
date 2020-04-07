//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <vector>

namespace NangaParbat
{
  /**
   * @brief Function that lists elements in a directory
   * @param path: path to the directory
   * @return a vector of elements
   */
  std::vector<std::string> list_dir(std::string const& path);
}
