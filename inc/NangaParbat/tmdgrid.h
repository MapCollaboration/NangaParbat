//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <vector>
#include <memory>
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  /**
   * @brief Function that produce the TMD interpolation grid in
   * momentum space. This is suppose to resamble an LHAPDF grid for
   * the TMDs. We use plain YAML format.
   * @param config: the YAML not with the theory settings
   * @param parameterisation: the parameterisation type
   * @param params: the vector of parameters to be used for the tabulation
   * @param pf: whether PDFs ("pdf") of FFs ("ff")
   * @return a YAML emitter
   */
  std::unique_ptr<YAML::Emitter> TMDGrid(YAML::Node          const& config,
                                         std::string         const& parameterisation,
                                         std::vector<double> const& params,
                                         std::string         const& pf);
}
