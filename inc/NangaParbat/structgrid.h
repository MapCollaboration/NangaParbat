//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#pragma once

#include <yaml-cpp/yaml.h>
#include <apfel/apfelxx.h>

namespace NangaParbat
{
  /**
   * @brief Class for the interpolation of a single TMD grid
   */
  class StructGrid
  {
  public:
    /**
     * @brief The "StructGrid" constructor
     * @param info: the info file of the grid
     * @param grid: the YAML node containing the grid
     */
    StructGrid(YAML::Node const& info, YAML::Node const& grid);

    /**
     * @brief Function that returns the value of one of the functions.
     * @param x: momentum fraction
     * @param z: momentum fraction
     * @param qT: transverse momentum
     * @param Q: renormalisation scale (assumed to be equal to the square root of zeta)
     * @return It returns the value of structure function distributions
     */
    double Evaluate(double const& x, double const& z, double const& qT, double const& Q) const;

    /**
     * @brief Function that returns the YAML Node with the set info
     */
    YAML::Node GetInfoNode() const { return _info; };

  private:
    YAML::Node                                                   const  _info;
    std::unique_ptr<apfel::QGrid<double>>                        const  _xg;
    std::unique_ptr<apfel::QGrid<double>>                        const  _zg;
    std::unique_ptr<apfel::QGrid<double>>                        const  _qToQg;
    std::unique_ptr<apfel::QGrid<double>>                        const  _Qg;
    std::vector<std::vector<std::vector<std::vector<double>>>>   const  _stfunc;
  };
}
