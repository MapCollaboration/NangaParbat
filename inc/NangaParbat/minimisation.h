//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/chisquare.h"
#include "NangaParbat/parameterisation.h"

#include <ROOT/Minuit2/FCNBase.h>
#include <ROOT/Minuit2/MnMigrad.h>

namespace NangaParbat
{
  /**
   * @brief The "MinuitMinimiser" function using Minuit2 as implemented in ROOT
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters to be minimised along with the relevant information
   */
  bool MinuitMinimiser(ChiSquare const& chi2, YAML::Node const& parameters);

  /**
   * @brief The "CeresMinimiser" function using ceres-solver
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters to be minimised along with the relevant information
   */
  bool CeresMinimiser(ChiSquare const& chi2, YAML::Node const& parameters);

  /**
   * @brief The "NoMinimiser" function simply returns predictions
   * @param chi2: the "ChiSquare" object that returns the values of all chi2's
   * @param parameters: the "YAML::Node" object that contains the
   * parameters to be minimised along with the relevant information
   */
  bool NoMinimiser(ChiSquare const& chi2, YAML::Node const& parameters);
}
