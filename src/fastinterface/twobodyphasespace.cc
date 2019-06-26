//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Fulvio Piacenza: fulvio.piacenza01@universitadipavia.it
//

#include "NangaParbat/twobodyphasespace.h"

#include <math.h>
#include <algorithm>
#include <apfel/integrator.h>

namespace NangaParbat
{
  //_________________________________________________________________________
  TwoBodyPhaseSpace::TwoBodyPhaseSpace(double const& pTmin, double const& etamax, double const& eps):
    _pTmin(pTmin),
    _etamax(etamax),
    _eps(eps)
  {
  }

  //_________________________________________________________________________
  double TwoBodyPhaseSpace::PhaseSpaceReduction(double const& Q, double const& y, double const& qT)
  {
    // Return automatically zero if "y" is larger that "_etamax"
    if (y >= _etamax)
      return 0;

    // Useful definitions
    const double Q2     = Q * Q;
    const double qT2    = qT * qT;
    const double qT4    = qT2 * qT2;
    const double pTmin2 = _pTmin * _pTmin;
    const double M2     = Q2 + qT2;
    const double M      = sqrt(M2);
    const double ctgh   = 1 / tanh(y - _etamax);

    // Integrand function with g^{\mu\nu}
    const auto IntegrandP = [&] (double const& eta) -> double
    {
      // Useful definitions
      const double ch    = cosh(eta - y);
      const double sh2   = ch * ch - 1;
      const double Eq    = M * ch;
      const double Eq2   = Eq * Eq;
      const double Eq4   = Eq2 * Eq2;
      const double EmqT2 = Eq2 - qT2;
      const double EmqT4 = EmqT2 * EmqT2;
      const double EmqT  = sqrt(EmqT2);

      // Auxiliary functions
      const double f2 = ( 2 * _pTmin * Eq - Q2 ) / 2 / _pTmin / qT;
      const double f3 = ( Eq * ( Q2 - 2 * pTmin2 + 2 * qT2 ) - Q2 * sqrt( Eq2 - M2 + pTmin2 ) ) / 2 / qT / ( M2 - pTmin2 );
      const double f4 = Eq / qT - Q2 * ( sinh(eta - y) * ctgh + ch ) / 2 / qT / M;

      // Integration limits in cos(phi)
      const double x1 = std::max(f2, -1.);
      const double x2 = std::min(std::min(f3, f4), 1.);

      // Return zero if x2 < x1
      if (x2 <= x1)
        return 0;

      // Primitive function of the intregration in cos(phi) (up to a
      // factor that can be compute externally) when contractin the
      // leptonic tensor with g^{\mu\nu}_\perp.
      const auto Fbar = [&] (double const& x) -> double
      {
        const double x2 = x * x;
        const double xp = sqrt( 1 - x2 );
	const double atanfact = Eq * ( atan( ( qT - x * Eq ) / EmqT / xp ) - atan( ( qT + x * Eq ) / EmqT / xp ) ) / EmqT;
        const double Fi = qT2 * x * xp / ( x2 * qT2 - Eq2 ) - atanfact;
        const double Gi = Q2 * sh2
	* ( qT2 * xp * ( ( ( 11 * Eq2 * qT2 + 4 * qT4 ) * x2 + 3 * Eq * qT * ( 9 * Eq2 + qT2 ) * x + 18 * Eq4 - 5 * Eq2 * qT2 + 2 * qT4 ) / pow(x * qT + Eq, 3) +
			 ( ( 11 * Eq2 * qT2 + 4 * qT4 ) * x2 - 3 * Eq * qT * ( 9 * Eq2 + qT2 ) * x + 18 * Eq4 - 5 * Eq2 * qT2 + 2 * qT4 ) / pow(x * qT - Eq, 3) )
	    - 6 * ( 2 * Eq2 + 3 * qT2 ) * atanfact ) / EmqT4 / 4;

        return 3 * Fi + Gi;
      };
      return ( Fbar(x2) - Fbar(x1) ) / EmqT2;
    };

    // Return integral
    const apfel::Integrator Ieta{IntegrandP};
    return Q2 * Ieta.integrate(-_etamax, _etamax, _eps) / 16 / M_PI;
  }

  //_________________________________________________________________________
  double TwoBodyPhaseSpace::DerivePhaseSpaceReduction(double const& Q, double const& y, double const& qT)
  {
    return 0;
  }
}
