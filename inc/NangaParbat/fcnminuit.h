//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/chisquare.h"

#include <root/Minuit2/FCNBase.h>
#include <root/Minuit2/FCNGradientBase.h>

namespace NangaParbat
{
  /**
   * @brief The "FcnMinuit" class is a derived class of of the
   * "FCNBase" mother class of Minuit that returns the
   * &chi;<SUP>2</SUP> to be minimised.
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

    double Up() const { return 1; }

    /**
     * @brief Function that sets the parameter of the "ChiSquare" object.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) { _chi2.SetParameters(pars); };

  private:
    mutable ChiSquare _chi2; //!< The "ChiSquare" object that returns the values of all chi2's
  };

  /**
   * @brief The "FcnMinuit" class is a derived class of of the
   * "FCNGradientBase" mother class of Minuit that returns the
   * &chi;<SUP>2</SUP> to be minimised along with it derivatives
   * w.r.t. the free parameters.
   */
  class FcnMinuitGrad: public ROOT::Minuit2::FCNGradientBase
  {
  public:
    /**
     * @brief The "FcnMinuitGrad" default constructor
     * @param chi2: the "ChiSquare" object that returns the values of all chi2's
     */
    FcnMinuitGrad(ChiSquare const& chi2);

    /**
     * @brief Operator required by Minuit to compute the function to
     * be minimised.
     * @param pars: the vector of parameters
     * @return the function to be minimised
     */
    double operator()(std::vector<double> const& pars) const;

    /**
     * @brief Function required by Minuit to compute the derivatives
     * of the function to be minimised.
     * @param pars: the vector of parameters
     * @return the vector of derivatives, one for each parameter
     */
    std::vector<double> Gradient(const std::vector<double>& pars) const;

    double Up() const { return 4; }

    /**
     * @brief Function that sets the parameter of the "ChiSquare" object.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) { _chi2.SetParameters(pars); };

  private:
    mutable ChiSquare _chi2; //!< The "ChiSquare" object that returns the values of all chi2's
  };
}
