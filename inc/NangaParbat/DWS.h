//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  /**
   * @brief Davies-Webber-Stirling parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class DWS: public NangaParbat::Parameterisation
  {
  public:

    DWS(): Parameterisation{"DWS", 2, std::vector<double>{0.207309505279, 0.09258432985738}, true}, _Q02(3.2) { };

    double Evaluate(double const&, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[DWS::Evaluate]: function index out of range");

      const double g1 = this->_pars[0];
      const double g2 = this->_pars[1];

      return exp( - ( g1 + g2 * log(zeta / _Q02) / 2 ) * pow(b, 2) / 2 );
    };

    double Derive(double const&, double const& b, double const& zeta, int const& ifunc, int const& ipar) const
    {
      const double g1 = this->_pars[0];
      const double g2 = this->_pars[1];

      // Derivative w.r.t. "g1"
      if (ipar == 0)
        {
          const double b2 = b * b;
          return - b2 * exp( - ( g1 + g2 * log(zeta / _Q02) / 2 ) * b2 / 2 ) / 2;
        }
      // Derivative w.r.t. "g2"
      else if (ipar == 1)
        {
          const double b2 = b * b;
          const double ln = log(zeta / _Q02);
          return - ln * b2 * exp( - ( g1 + g2 * ln / 2 ) * b2 / 2 ) / 4;
        }
      else
        return 0;
    };

    std::string LatexFormula() const
    {
      return R"delimiter($$f_{\rm NP}(x,\zeta, b_T)=\exp\left[ - \frac{1}{2}\left( g_1 + \frac{1}{2}g_2 \log\left(\frac{\zeta}{Q_0^2}\right) \right) b_T^2 \right]$$)delimiter";
    };

    std::vector<std::string> GetParameterNames() const
    {
      return {R"delimiter($g_1$)delimiter", R"delimiter($g_2$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the Davies-Webber-Stirling TMD analysis.";
    };

  private:
    double const _Q02;
  };
}
