//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  /**
   * @brief Derivation of the class Cut to impose a cut on the variable
   * "z" as a function of x.
   */
  class XZCut: public Cut
  {
  public:
    /**
     * @brief The "XZcut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param betamin: mininum value
     * @param betamax: maximum value
     * @param alpha: angular coefficient
     */
    XZCut(DataHandler const& dataset, double const& betamin, double const& betamax, double const& alpha);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  private:
    double const _alpha;
  };

  /**
   * @brief Derivation of the class Cut to impose yet a different cut
   * on the variable "z" as a function of x.
   */
  class XZCutQuadratic: public Cut
  {
  public:
    /**
     * @brief The "XZcut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param betamin: mininum value
     * @param betamax: maximum value
     */
    XZCutQuadratic(DataHandler const& dataset, double const& betamin, double const& betamax);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  };
}
