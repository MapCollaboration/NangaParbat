//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  /**
   * @brief Derivation of the class Cut to impose a cut on the variable
   * "W".
   */
  class WCut: public Cut
  {
  public:
    /**
     * @brief The "Wcut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param Wmin: mininum value
     * @param Wmax: maximum value
     */
    WCut(DataHandler const& dataset, double const& Wmin, double const& Wmax);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  };
}
