//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/chisquare.h"

namespace NangaParbat
{
  /**
   * @brief The "FcnCeres" class to be used with ceres-solver to
   * minimise the &chi;<SUP>2</SUP>.
   */
  class FcnCeres
  {
  public:
    /**
     * @brief The "FcnCeres" default constructor
     * @param chi2: the "ChiSquare" object that returns the values of all chi2's
     */
    FcnCeres(ChiSquare const& chi2);

    /**
     * @brief Operator required by Ceres to compute the function to
     * be minimised.
     * @param parameters: the (double) array of parameters
     * @param residuals: the array of residual
     */
    bool operator()(double const* const* parameters, double* residuals) const;

  private:
    mutable ChiSquare _chi2; //!< The "ChiSquare" object that returns the values of all chi2's
  };
}
