//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/cut.h"

namespace NangaParbat
{
  /**
   * @brief Derivation of the class Cut to impose cut on the variable
   * "Q".
   */
  class QCut: public Cut
  {
  public:
    /**
     * @brief The "QCut" constructor
     * @param dataset: the DataHandler object subject to the cuts
     * @param Qmin: mininum value
     * @param Qmax: maximal value
     */
    QCut(DataHandler const& dataset, double const& Qmin, double const& Qmax);

    /**
     * @brief Purely virtual function to be used implemented in the
     * derived class to eforce the cut.
     */
    void EnforceCut();
  };
}
