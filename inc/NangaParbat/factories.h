//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/tmdgrid.h"
#include "NangaParbat/structgrid.h"

namespace NangaParbat
{
  /**
   * @brief Factory that returns a "TMDGrid" object.
   * @param name: name of the TMD set (assumed to be in the current folder for now)
   * @param mem: member to be read (defaul: 0, i.e. central member)
   */
  TMDGrid* mkTMD(std::string const& name, int const& mem = 0);

  /**
   * @brief Factory that returns a "TMDGrid" object.
   * @param name: name of the TMD set
   * @param folder: name of the folder where the TMD set is
   * @param mem: member to be read (defaul: 0, i.e. central member)
   */
  TMDGrid* mkTMD(std::string const& name, std::string const& folder, int const& mem = 0);

  /**
   * @brief Factory that returns a vector of "TMDGrid" objects.
   * @param name: name of the TMD set (assumed to be in the current folder for now)
   */
  std::vector<TMDGrid*> mkTMDs(std::string const& name);

  /**
   * @brief Factory that returns a "StructGrid" object.
   * @param name: name of the structure function set (assumed to be in the current folder for now)
   * @param mem: member to be read (defaul: 0, i.e. central member)
   */
  StructGrid* mkSF(std::string const& name, int const& mem = 0);

  /**
   * @brief Factory that returns a "StructGrid" object.
   * @param name: name of the structure function set
   * @param folder: name of the folder where the structure function set is
   * @param mem: member to be read (defaul: 0, i.e. central member)
   */
  StructGrid* mkSF(std::string const& name, std::string const& folder, int const& mem = 0);

  /**
   * @brief Factory that returns a vector of "StructGrid" objects.
   * @param name: name of the structure function set (assumed to be in the current folder for now)
   */
  std::vector<StructGrid*> mkSFs(std::string const& name);

  /**
   * @brief Function that performs the convolution of two TMD
   * distributions in kT space.
   * @param TMD1: first distribution
   * @param TMD2: second distribution
   * @param Charges: to be used as weights of the partonic combinations
   * @param kTCutOff: cutoff on the integration in kT relative to Q (default: 1)
   * @param IntEps: integration relative accuracy (default: 1e-5)
   */
  std::function<double(double const&, double const&, double const&, double const&)> Convolution(TMDGrid                                           const* TMD1,
                                                                                                TMDGrid                                           const* TMD2,
                                                                                                std::function<std::vector<double>(double const&)> const& Charges,
                                                                                                double                                            const& kTCutOff = 1,
                                                                                                double                                            const& IntEps = 1e-5);

  /**
   * @brief Function that performs the convolution of two TMD
   * distributions in kT space assuming that first and second
   * distributions are equal.
   * @param TMD: distribution
   * @param Charges: to be used as weights of the partonic combinations
   * @param kTCutOff: cutoff on the integration in kT relative to Q (default: 1)
   * @param IntEps: integration relative accuracy (default: 1e-5)
   */
  std::function<double(double const&, double const&, double const&, double const&)> Convolution(TMDGrid                                           const* TMD,
                                                                                                std::function<std::vector<double>(double const&)> const& Charges,
                                                                                                double                                            const& kTCutOff = 1,
                                                                                                double                                            const& IntEps = 1e-5);
}
