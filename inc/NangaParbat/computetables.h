//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

// YAML
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  // Compute the interpolation tables given as an input a
  // configuration file and dataset file.
  void ComputeTables(std::string const& configfile, std::string const& datasetfile);
}
