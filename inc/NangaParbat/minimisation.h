//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/chisquare.h"
#include "NangaParbat/parameterisation.h"

#include <root/Minuit2/FCNBase.h>
#include <root/Minuit2/MnMigrad.h>

namespace NangaParbat
{
  /**
   * @brief The "MinuitMinimiser" function using Minuit2 as implemented in ROOT
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters to be minimised along with the relevant information
   * @param rng: GSL random number object
   */
  bool MinuitMinimiser(ChiSquare const& chi2, YAML::Node const& parameters, gsl_rng* rng = NULL);

  /**
   * @brief The "CeresMinimiser" function using ceres-solver
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters to be minimised along with the relevant information
   * @param rng: GSL random number object
   */
  bool CeresMinimiser(ChiSquare const& chi2, YAML::Node const& parameters, gsl_rng* rng = NULL);

  /**
   * @brief The "NoMinimiser" function simply returns predictions
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters to be minimised along with the relevant information
   */
  bool NoMinimiser(ChiSquare const& chi2, YAML::Node const& parameters);

  /**
   * @brief The "MinuitScan" function performs a scan around the parameters using
   * Minuit2
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters
   * @param outfolder: folder for the output
   */
  bool MinuitScan(ChiSquare const& chi2, YAML::Node const& parameters, std::string const& outfolder);
}
