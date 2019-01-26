//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/chisquare.h"
#include "NangaParbat/parameterisation.h"

#include <root/Minuit2/FCNBase.h>

namespace NangaParbat
{
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
     * @param func: the "Parameterisation" object that encapsulates the non-perturnative function(s)
     */
    FcnMinuit(ChiSquare const& chi2);

    /**
     * @brief Operator required by Minuit to compute the function to
     * be minimised.
     * @param pars: the vector of parameters
     * @return the function to be minimised
     */
    double operator()(const std::vector<double>& pars);

    double Up() const { return 4; }
  private:
    ChiSquare _chi2; //!< The "ChiSquare" object that returns the values of all chi2's
  };
}
