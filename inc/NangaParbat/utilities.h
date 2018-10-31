//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

// YAML
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  // b* prescription
  double bstar(double const& b, double const& bmax);

  //_________________________________________________________________________________
  // Utility function to generate an interpolation grid
  std::vector<double> GenerateQGrid(int const& n, double const& min, double const& max);

  //_________________________________________________________________________________
  // Utility function that returns the kinematics read from the HEPData
  // file (Some edit may be required)
  void RetrieveKinematics(YAML::Node const& df, double& Vs, double& Qmin, double& Qmax, double& ymin, double& ymax, std::vector<double>& qTv);
}
