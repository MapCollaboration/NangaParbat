//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <yaml-cpp/yaml.h>
#include <apfel/apfelxx.h>

namespace NangaParbat
{
  /**
   * @brief Class for the interpolation of a single TMD grid
   */
  class TMDGrid
  {
  public:
    /**
     * @brief The "TMDGrid" constructor
     * @param grid: the YAML node containing the grid
     */
    TMDGrid(YAML::Node const& grid);

    /**
     * @brief Function that returns the value of one of the functions.
     * @param x: momentum fraction
     * @param qT: transverse momentum
     * @param Q: renormalisation scale (assumed to be equal to the square root of zeta)
     * @return It returns the value of all the flavour TMD distributions
     */
    std::map<int, double> Evaluate(double const& x, double const& qT, double const& Q) const;

  private:
    std::unique_ptr<apfel::QGrid<double>>                              _xg;
    std::unique_ptr<apfel::QGrid<double>>                              _qToQg;
    std::unique_ptr<apfel::QGrid<double>>                              _Qg;
    std::map<int, std::vector<std::vector<std::vector<double>>>> const _tmds;
  };
}
