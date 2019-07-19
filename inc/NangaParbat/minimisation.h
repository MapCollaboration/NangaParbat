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

  /**
   * @brief The "FcnMinuit" class is a derived class of of the
   * "FCNBase" mother class of Minuit that returns the figure of merit
   * (&chi;<SUP>2</SUP>) to be minimised.
   */
  class FcnMinuit: public ROOT::Minuit2::FCNBase
  {
  public:
    /**
     * @brief The "FcnMinuit" default constructor
     * @param chi2: the "ChiSquare" object that returns the values of all chi2's
     */
    FcnMinuit(ChiSquare const& chi2);

    /**
     * @brief Operator required by Minuit to compute the function to
     * be minimised.
     * @param pars: the vector of parameters
     * @return the function to be minimised
     */
    double operator()(std::vector<double> const& pars) const;

    double Up() const { return 4; }

    /**
     * @brief Function that sets the parameter of the "ChiSquare" object.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) { _chi2.SetParameters(pars); };

  private:
    mutable ChiSquare _chi2; //!< The "ChiSquare" object that returns the values of all chi2's
  };

  /**
   * @brief The "FcnCeres" class
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
