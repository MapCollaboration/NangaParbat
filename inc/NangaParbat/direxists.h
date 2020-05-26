//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>

namespace NangaParbat
{
  /**
   * @brief Function that checks whether the input folder exists in
   * the current folder.
   * @param dir: directory name
   */
  bool dir_exists(std::string const& dir);
}
