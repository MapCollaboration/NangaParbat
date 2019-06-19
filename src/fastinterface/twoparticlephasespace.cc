//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Fulvio Piacenza: fulvio.piacenza01@universitadipavia.it
//

#include "NangaParbat/twoparticlephasespace.h"

namespace NangaParbat
{
  //_________________________________________________________________________
  TwoParticlePhaseSpace::TwoParticlePhaseSpace(double const& kTmin, double const& etamax):
    _kTmin(kTmin),
    _etamax(etamax)
  {
    _cuts     = (_kTmin > 0 || _etamax > 0 ? true : false);
    _thetamax = (_etamax > 0 ? tanh(etamax) : 1);

    _result = 1;
    _error  = 0;

    _workspace      = static_cast<void*>(gsl_integration_workspace_alloc(LIMIT_SIZE));
    _gsl_f.function = &_gsl_integrand;
    _gsl_f.params   = this;
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::PhaseSpaceReduction(double const& M, double const& qT, double const& y)
  {
    _M  = M;
    _qT = qT;
    _y  = y;
    if (_cuts)
      {
        const double iE = 1 / sqrt( pow(_M, 2) + pow(_qT, 2) ) / cosh(_y);
        lM2 = pow(_M * iE, 2);
        lT  = _qT * iE;
        ly  = tanh(_y);

        integration_bins.clear();
        L_nu.init_min_max(-_thetamax, +_thetamax);
        integration_bins.push_back(-_thetamax);
        integration_bins.push_back(+_thetamax);

        if (_etamax > 0)
          {
            if (L_nu.contains_not(ly))
              return _set0();

            integration_bins.push_back(_fnub_upm(-_thetamax, -1));
            integration_bins.push_back(_fnub_upm(-_thetamax, +1));
            integration_bins.push_back(_fnub_upm(+_thetamax, +1));
            integration_bins.push_back(_fnub_upm(+_thetamax, -1));
          }

        if (_kTmin > 0)
          {
            aoE = _kTmin * iE;

            const double lp2   = 1 - pow(ly, 2);
            const double num1  = pow(2 * aoE, 2) * ly;
            const double num2  = sqrt( pow(lp2, 3) * ( lp2 - pow(2 * aoE, 2) ) );
            const double den   = 1 / ( pow(lp2, 2) + num1 * ly );
            const double nua_m = ( num1 - num2 ) * den;
            const double nua_p = ( num1 + num2 ) * den;

            L_nu.add_limit_min_max(nua_m, nua_p);
            integration_bins.push_back(nua_m);
            integration_bins.push_back(nua_p);

            if (L_nu.is_unvalid())
              return _set0();
          }

        std::sort(integration_bins.begin(), integration_bins.end());
        std::vector<double>::const_iterator itr(integration_bins.begin());
        const std::vector<double>::const_iterator end(integration_bins.end()-1);

        Variable_Limit IR;
        double res = 0;

        while (itr!=end)
          {
            IR.init_min(*itr);
            IR.init_max(*(++itr));
            IR.add_limit(L_nu);
            if (IR.is_valid())
              res += _calc_one_region(IR.min, IR.max);
          }
        _result = res;
      }
    return _result;
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::DerivePhaseSpaceReduction(double const& M, double const& qT, double const& y)
  {
    const double eps = 1e-3;
    return ( PhaseSpaceReduction(M, qT * ( 1 + eps ), y) - PhaseSpaceReduction(M, qT * ( 1 - eps ), y) ) / 2 / eps / qT;
  }

  //_________________________________________________________________________
  std::ostream& TwoParticlePhaseSpace::into_stream(std::ostream& os) const
  {
    os << "PS(" << _M << ", " << _qT << ", " << _y;
    if (_cuts)
      {
        if (0 < _kTmin)
          os << ", kTmin -> " << _kTmin;
        if (0 < _etamax)
          os << ", etamax -> " << _etamax;
      }
    os << ") = (" << _result << " +- " << _error << ")";
    return os;
  }

  //_________________________________________________________________________
  std::ostream& operator << (std::ostream& os, TwoParticlePhaseSpace const& ps)
  {
    return ps.into_stream(os);
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::f(double const& alpha_m, double const& alpha_p) const
  {
    return lM2 * ( ( 1 - ly * nu ) * ( asin(sqrt(alpha_p)) - asin(sqrt(alpha_m)) )
                   - lT * Snu * ( sqrt( alpha_p * ( 1 - alpha_p ) ) - sqrt( alpha_m * ( 1 - alpha_m ) ) ) )
           / pow( sqrt( pow(1 - ly * nu, 2) - pow(lT * Snu, 2) ), 3) / M_PI;
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::_fthb(double const& thb) const
  {
    return ( thb + ly ) / ( thb + nu );
  }

  //_________________________________________________________________________
  Interval& TwoParticlePhaseSpace::u_limit_to_alpha(Interval &I_u, const double um, const double iDu)
  {
    I_u.min = ( I_u.min - um ) * iDu;
    I_u.max = ( I_u.max - um ) * iDu;
    return I_u;
  }

  //_________________________________________________________________________
  bool TwoParticlePhaseSpace::_calc_alphas()
  {
    L_u.init_min_max(0., 1.);
    const double num1 = 1 - ly * nu;
    const double num2 = lT * Snu;
    const double den  = 0.5 * lM2 / ( pow(num1, 2) - pow(num2, 2 ) );
    L_u.add_limit_min_max(( num1 - num2 ) * den, ( num1 + num2 ) * den);

    if (L_u.is_unvalid())
      return false;

    const double um  = L_u.min;
    const double iDu = 1 / L_u.size();

    if (_kTmin > 0)
      {
        L_u.add_limit_min(aoE / Snu);
        L_u.add_limit_max( ( (1 - ly * nu) - sqrt( pow(ly - nu, 2) + pow(aoE * Snu, 2) ) ) / pow(Snu, 2) );
        if (L_u.is_unvalid())
          return false;
      }

    if (_etamax > 0)
      {
        L_u.add_limit_max(_fthb(copysign(1, nu - ly) * _thetamax));
        if (L_u.is_unvalid())
          return false;
      }

    u_limit_to_alpha(L_u, um, iDu);

    return true;
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::_integrand_nu(double const& nu)
  {
    this->nu = nu;
    double res = 0;
    Snu = sqrt(1 - pow(nu, 2));
    if (_calc_alphas())
      res = f(L_u.min, L_u.max);

    return res;
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::_gsl_integrand(double x, void* params)
  {
    TwoParticlePhaseSpace* p = static_cast<TwoParticlePhaseSpace*>(params);
    return p->_integrand_nu(x);
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::_fnub_upm(double const& sthb, double const& su) const
  {
    const double a = lT * ( sthb + ly );
    const double b = 0.5 * lM2 + ly * ( sthb + ly );
    const double c = ( sthb + ly ) - 0.5 * lM2 * sthb;
    const double D = pow(a, 2) + pow(b, 2) - pow(c, 2);
    if (D < 0)
      return copysign(1, sthb);
    else
      return ( b * c - su * a * sqrt(D) ) / ( pow(a, 2) + pow(b, 2) );
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::_set0()
  {
    _result = 0;
    _error  = 0;
    return 0;
  }

  //_________________________________________________________________________
  double TwoParticlePhaseSpace::_calc_one_region(double const& min, double const& max)
  {
    _gsl_status = gsl_integration_qag(&_gsl_f, min, max, 1e-5, 0., LIMIT_SIZE, GSL_INTEG_GAUSS31,
                                      static_cast<gsl_integration_workspace*>(_workspace), &_result, &_error);
    return _result;
  }
}
