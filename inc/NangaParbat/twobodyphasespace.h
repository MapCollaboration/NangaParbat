//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Fulvio Piacenza: fulvio.piacenza01@universitadipavia.it
//

#pragma once

namespace NangaParbat
{
  /**
   * @note Calculate the phase-space volume within cuts relative to total phase-space for:
   * 		q -> k + kb
   * 	with:
   * 		k_T   > pTmin 	&&  kb_T   > pTmin
   * 		|eta| < etamax	&&  |etab| < etamax
   */
  class TwoBodyPhaseSpace
  {
  public:
    /**
     * @brief The "TwoBodyPhaseSpace" constructor.
     * @param pTmin: the minimum cut in the p<SUB>T</SUB> of the single lepton
     * @param etamin: the minimum cut in the &eta; of the single lepton
     * @param etamax: the maximum cut in the &eta; of the single lepton
     * @param eps: the integration accuracy (default = 10<SUP>-9</SUP>)
     */
    TwoBodyPhaseSpace(double const& pTmin, double const& etamin, double const& etamax, double const& eps = 1e-9);

    /**
     * @brief Function that returns the phase-space reduction factor.
     * @param M: invariant mass of the leptonic pair
     * @param y: rapidity of the leptonic pair
     * @param qT: transverse momentum of the leptonic pair
     * @return the phase-space reduction factor as a function of the
     * invariant mass, transverse momentum and rapidity of the lepton
     * pair.
     */
    double PhaseSpaceReduction(double const& Q, double const& y, double const& qT);

    /**
     * @brief Function that returns the derivative w.r.t. qT of the
     * phase-space reduction factor.
     * @param M: invariant mass of the leptonic pair
     * @param y: rapidity of the leptonic pair
     * @param qT: transverse momentum of the leptonic pair
     * @return the derivative of the phase-space reduction factor as a
     * function of the invariant mass, transverse momentum and rapidity
     * of the lepton pair.
     */
    double DerivePhaseSpaceReduction(double const& Q, double const& y, double const& qT);

  private:
    /**
     * @name Cut variables
     * Cut Variables that define the cuts on the single leptons
     */
    ///@{
    double _pTmin;
    double _etamin;
    double _etamax;
    double _eps;
    ///@}
  };
}
