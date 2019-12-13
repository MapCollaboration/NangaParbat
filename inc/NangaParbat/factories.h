//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/tmdgrid.h"

namespace NangaParbat
{
  /**
   * @brief Factory that returns a "TMDGrid" object.
   * @param name: name of the TMD set (assumed to be in the current folder for now)
   * @param mem: member to be read (defaul: 0, i.e. central member)
   */
  TMDGrid* mkTMD(std::string const& name, int const& mem = 0);

  /**
   * @brief Factory that returns a vector of "TMDGrid" objects.
   * @param name: name of the TMD set (assumed to be in the current folder for now)
   */
  std::vector<TMDGrid*> mkTMDs(std::string const& name);
}
