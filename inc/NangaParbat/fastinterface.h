//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"

#include <utility>
#include <memory>
#include <yaml-cpp/yaml.h>
#include <apfel/apfelxx.h>

namespace NangaParbat
{
  class FastInterface
  {
  public:
    /**
     * @brief The "FastInterface" constructor.
     * @param config: the YAML:Node with the configuration
     */
    FastInterface(YAML::Node const& config);

    /**
     * @brief This function returns a "double object" for a
     * fixed values of "b" and "Q".
     * @param b: value of the impact parameter
     * @param Q: value of the hard scale
     * @return the luminosity for Drell-Yan
     */
    apfel::DoubleObject<apfel::Distribution> LuminosityDY(double const& bT, double const& Q) const;

    /**
     * @brief This function returns a "double object" for a
     * fixed values of "b" and "Q".
     * @param b: value of the impact parameter
     * @param Q: value of the hard scale
     * @return the luminosity for SIDIS
     */
    apfel::DoubleObject<apfel::Distribution> LuminositySIDIS(double const& b, double const& Q) const;

    /**
     * @brief This function computes the interpolation tables given as
     * an input a configuration file and a vector of "DataHandler"
     * objects.
     * @param DHVect: vector of "DataHandler" objects.
     * @return a vector of "YAML::Emitter" objects containing as many
     * tables as elements of "DHVect".
     */
    std::vector<YAML::Emitter> ComputeTables(std::vector<DataHandler> const& DHVect) const;

  private:
    YAML::Node                                                              _config;
    std::vector<double>                                                     _Thresholds;
    std::unique_ptr<apfel::TabulateObject<double>>                          _TabAlphas;
    std::unique_ptr<apfel::TabulateObject<double>>                          _TabAlphaem;
    std::map<int,apfel::TmdObjects>                                         _TmdPdfObjs;
    std::map<int,apfel::TmdObjects>                                         _TmdFfObjs;
    std::unique_ptr<const apfel::Grid>                                      _gpdf;
    std::unique_ptr<const apfel::Grid>                                      _gff;
    std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>> _TabPDFs;
    std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>> _TabFFs;
    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> _EvTMDPDFs;
    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> _EvTMDFFs;
  };
}
