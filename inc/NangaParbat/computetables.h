//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <utility>
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  /**
   * @brief Structure containing the kinematic information of one
   * single data set.
   */
  struct Kinematics
  {
    std::string              name;   //!< Name associated to the block
    double                   Vs;     //!< Center of mass energy
    std::vector<double>      qTv;    //!< Vector of qT values
    std::pair<double,double> Qb;     //!< Q integration bounds
    std::pair<double,double> yb;     //!< y integration bounds
    bool                     IntqT;  //!< If true computes the primitive in qTv
  };

  /**
   * @brief Function that returns the kinematics read from the HEPData
   * file (some edit may be required).
   * @param configfile: configuration card in YAML format
   * @return a vector of "Kinematics" objects.
   * @note This function is meant to limit the "dirty" stuff required
   * to parse a datafile to a single function. This function returns a
   * structure (a "Kinematics" object) that encapsulates information
   * on kinematics in a format that can be processed by the
   * "ComputeTable" function.
   */
  std::vector<Kinematics> RetrieveKinematics(YAML::Node const& datalist);

  /**
   * @brief This function computes the interpolation tables given as
   * an input a configuration file and dataset file.
   * @param configfile: configuration card in YAML format
   * @param datasetfile: vector of "Kinematics" objects.
   * @return a vector of "YAML::Emitter" objects containing as many
   * tables as elements of "KinVect".
   */
  std::vector<YAML::Emitter> ComputeTables(YAML::Node const& config, std::vector<Kinematics> const& KinVect);
}
