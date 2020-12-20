//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  /**
   * @brief Derivation of the class Cut to impose cut on the variable
   * "z".
   */
  class ZCut: public Cut
  {
  public:
    /**
     * @brief The "ZCut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param zmin: mininum value
     * @param zmax: maximal value
     */
    ZCut(DataHandler const& dataset, double const& zmin, double const& zmax);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  };
}
