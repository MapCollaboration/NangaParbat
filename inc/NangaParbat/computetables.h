//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"
#include "NangaParbat/fastinterface.h"

#include <utility>
#include <yaml-cpp/yaml.h>
//#include <apfel/apfelxx.h>

namespace NangaParbat
{
  /**
   * @brief This function computes the interpolation tables given as
   * an input a configuration file and a vector of "DataHandler"
   * objects.
   * @param config: configuration card in YAML format
   * @param DHVect: vector of "DataHandler" objects.
   * @return a vector of "YAML::Emitter" objects containing as many
   * tables as elements of "KinVect".
   */
  std::vector<YAML::Emitter> ComputeTables(YAML::Node const& config, std::vector<DataHandler> const& DHVect);
}
