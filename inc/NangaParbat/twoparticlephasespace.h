//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Fulvio Piacenza: fulvio.piacenza01@universitadipavia.it
//

#pragma once

#include <gsl/gsl_integration.h>
#include <math.h>

#include "NangaParbat/interval.h"

#define LIMIT_SIZE 50000

namespace NangaParbat
{
  /**
   * @note Calculate the phase-space volume within cuts relative to total phase-space for:
   * 		q -> k + kb
   * 	with:
   * 		k_T   > kTmin 	&&	kb_T   > kTmin
   * 		|eta| < etamax	&&	|etab| < etamax
   * 	excluding:
   * 		eta0 < |eta| < eta1  && eta0 < |etab| < eta1
   *
   * The following class has been extracted from the "Cute" program
   * version 2.0.0 (see https://cute.hepforge.org) and adapted to fit
   * into APFEL++.
   */
  class TwoParticlePhaseSpace
  {
  public:
    /**
     * @brief The "TwoParticlePhaseSpace" constructor.
     * @param kTmin: the minimum cut in the k_T of the single lepton (default = -1, i.e. no cut)
     * @param etamax: the maximum cut in the &eta; of the single lepton (default = -1, i.e. no cut)
     * @param eta0 and eta1: the bounds of the interval in the &eta; to be excluded (default = -1 and -1, i.e. no cut)
     */
    TwoParticlePhaseSpace(double const& kTmin = -1, double const& etamax = -1, double const& eta0 = -1, double const& eta1 = -1);

    /**
     * @brief The "TwoParticlePhaseSpace" destructor.
     */
    ~TwoParticlePhaseSpace() { gsl_integration_workspace_free(static_cast<gsl_integration_workspace*>(_workspace)); }

    /**
     * @brief Function that returns the phase-space reduction factor.
     * @param M: invariant mass of the leptonic pair
     * @param qT: transverse momentum of the leptonic pair
     * @param y: rapidity of the leptonic pair
     * @return the phase-space reduction factor as a function of th
     * invariant mass, transverse momentum and rapidity of the lepton
     * pair.
     */
    double PhaseSpaceReduction(double const& M, double const& qT, double const& y);

    /**
     * @brief Function that returns the phase-space reduction factor
     * along with its uncertainty in a human-readable format.
     */
    std::ostream& into_stream(std::ostream& os) const;

  private:
    /**
     * @defgroup GSLobj GSL objects
     */
    ///@{
    gsl_function _gsl_f;
    void*        _workspace;
    int          _gsl_status;
    ///@}

    /**
     * @defgroup Result Phase-space reduction factor and its integration uncertainty.
     */
    double _result;
    double _error;

    /**
     * @defgroup Cuts Variables that define the cuts on the single leptons
     */
    ///@{
    bool   _cuts;
    bool   _ex;
    double _kTmin;
    double _etamax;
    double _thetamax;
    double _theta0, _theta1;
    ///@}

    /**
     * @defgroup InputKin Input kinematics of the lepton pair
     */
    ///@{
    double _M;
    double _qT;
    double _y;
    ///@}

    /**
     * @defgroup DerVar Derived global variables
     */
    ///@{
    double aoE;
    double lM2;
    double lT;
    double ly;
    double nu;
    double Snu;
    Variable_Limit L_nu;
    Variable_Limit L_u;
    Variable_Exclusion E_nu_p;
    Variable_Exclusion E_nu_m;
    Variable_Exclusion E_u_m;
    Variable_Exclusion E_u_p;
    std::vector<double> integration_bins;
    ///@}

    /**
     * @defgroup PrivFuns Private utility functions
     */
    ///@{
    double f(double const& alpha_m, double const& alpha_p) const;
    double _fthb(double const& thb) const;
    static Interval& u_limit_to_alpha(Interval &I_u, const double um, const double iDu);
    bool _calc_alphas();
    double _integrand_nu(double const& nu);
    static double _gsl_integrand(double x, void* params);
    double _fnub_upm(double const& sthb, double const& su=-1.) const;
    double _set0();
    double _calc_one_region(const Variable_Limit& IR);
    double _calc_one_region(Variable_Limit& IR, Variable_Exclusion E1);
    double _calc_one_region(Variable_Limit& IR, const Variable_Exclusion& E1, Variable_Exclusion E2);
    ///@}
  };

  std::ostream& operator<<(std::ostream &os, const TwoParticlePhaseSpace& PS);
}
