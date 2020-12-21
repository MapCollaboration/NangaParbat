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
  /**
   * @brief Class that implements the methods of the computation of
   * the interpolation tables.
   */
  class FastInterface
  {
  public:
    /**
     * @brief The "FastInterface" constructor.
     * @param config: the YAML:Node with the configuration information
     */
    FastInterface(YAML::Node const& config);

    /**
     * @brief Function returns the luminosity for the Drell-Yan
     * process as a "DoubleObject" for a fixed values of "b" and "Q".
     * @param b: value of the impact parameter
     * @param Q: value of the hard scale
     * @return the luminosity for Drell-Yan
     */
    apfel::DoubleObject<apfel::Distribution> LuminosityDY(double const& bT, double const& Q, double const& targetiso) const;

    /**
     * @brief Function returns the luminosity for the SIDIS process as
     * a "DoubleObject" for a fixed values of "b" and "Q".
     * @param b: value of the impact parameter
     * @param Q: value of the hard scale
     * @return the luminosity for SIDIS
     */
    apfel::DoubleObject<apfel::Distribution> LuminositySIDIS(double const& b, double const& Q, double const& targetiso) const;

    /**
     * @brief Function that computes the interpolation tables given as
     * an input vector of "DataHandler" objects.
     * @param DHVect: vector of "DataHandler" objects.
     * @return a vector of "YAML::Emitter" objects containing as many
     * tables as elements of "DHVect".
     */
    std::vector<YAML::Emitter> ComputeTables(std::vector<DataHandler> const& DHVect) const;

  private:
    YAML::Node                                                                                  _config;          //!< Configuration YAML::Node
    std::vector<double>                                                                         _Thresholds;      //!< Heavy-quark thresholds
    std::unique_ptr<apfel::TabulateObject<double>>                                              _TabAlphas;       //!< Strong coupling
    std::unique_ptr<apfel::TabulateObject<double>>                                              _TabAlphaem;      //!< Fine-structure coupling
    std::map<int,apfel::TmdObjects>                                                             _TmdPdfObjs;      //!< Space-like TMD objects
    std::map<int,apfel::TmdObjects>                                                             _TmdFfObjs;       //!< Time-like TMD objects
    std::unique_ptr<const apfel::Grid>                                                          _gpdf;            //!< APFEL x-space grid for PDFs
    std::unique_ptr<const apfel::Grid>                                                          _gff;             //!< APFEL x-space grid for FFs
    std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>                     _TabPDFs;         //!< Collinear PDFs
    std::unique_ptr<apfel::TabulateObject<apfel::Set<apfel::Distribution>>>                     _TabFFs;          //!< Collinear FFs
    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> _EvTMDPDFs;       //!< TMD PDFs
    std::function<apfel::Set<apfel::Distribution>(double const&, double const&, double const&)> _EvTMDFFs;        //!< TMD FFs
    std::function<double(double const&)>                                                        _HardFactorDY;    //!< Hard factor for Drell-Yan
    std::function<double(double const&)>                                                        _HardFactorSIDIS; //!< Hard factor for SIDIS
    std::function<double(double const&, double const&)>                                         _bstar;           //!< b* prescription
  };
}
