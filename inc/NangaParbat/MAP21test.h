//
// Author: Valerio Bertone: valerio.bertone@cern.ch,
//         Alessandro Bacchetta: alessandro.bacchetta@unipv.it

#pragma once

#include "NangaParbat/parameterisation.h"

#include <yaml-cpp/yaml.h>
#include <math.h>

namespace NangaParbat
{
  /**
   * @brief MAP 2021 parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class MAP21test: public NangaParbat::Parameterisation
  {
  public:
    MAP21test(): Parameterisation{"MAP21test", 2, std::vector<double>{0.12840E+00, 0.28516E+00, 0.29755E+01, 0.17293E+00, 0.39432E+00, 2.12062E-01, 0.21012E+01, 0.93554E-01, 0.25246E+01, 0.52915E+01, 3.37975E-02, 0.0, 0.28516E+00}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[MAP21test::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Evolution
      const double g2     = this->_pars[0];
      const double g2B    = this->_pars[11];
      const double b2     = b * b;
      const double lnz    = log(zeta / _Q02);
      const double NPevol = exp( - ( g2 * b2 + g2B * b2 * b2 ) * lnz / 4 );

      // TMD PDFs
      if (ifunc == 0 || ifunc == 1)
        {
          const double N1     = this->_pars[1];
          const double alpha  = this->_pars[2];
          const double sigma  = this->_pars[3];
          const double lambda = this->_pars[4];
          const double N1B    = this->_pars[12];
          const double xhat   = 0.1;
          const double g1     = N1 * pow(x / xhat, sigma) * pow((1 - x) / (1 - xhat), alpha);
          const double g1B    = N1B * pow(x / xhat, sigma) * pow((1 - x) / (1 - xhat), alpha);
          return NPevol * ( g1 * exp( - g1 * pow(b / 2, 2))
                            +  lambda  * pow(g1B, 2) * ( 1 - g1B * pow(b / 2, 2)) * exp( - g1B * pow(b / 2, 2)) )
                 / ( g1 +  lambda  * pow(g1B, 2) );
        }
      // TMD FFs
      else
        {
          const double N3      = this->_pars[5];
          const double beta    = this->_pars[6];
          const double delta   = this->_pars[7];
          const double gamma   = this->_pars[8];
          const double lambdaF = this->_pars[9];
          const double N3B     = this->_pars[10];
          const double zhat    = 0.5;
          const double cmn     = ( ( pow(x, beta) + delta ) / ( pow(zhat, beta) + delta ) ) * pow((1 - x) / (1 - zhat), gamma);
          const double g3      = N3 * cmn;
          const double g3B     = N3B * cmn;
          const double z2      = x * x;
          return NPevol * ( g3 * exp( - g3 * pow(b / 2, 2) / z2 )
                            + ( lambdaF / z2 ) * pow(g3B, 2) * ( 1 - g3B * pow(b / 2, 2) / z2 ) * exp( - g3B * pow(b / 2, 2) / z2 ) )
                 / ( g3 + ( lambdaF / z2 ) * pow(g3B, 2) );
        }
    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)=\exp\left[ - \left( g_1(x) + \frac{1}{2}g_2 \log\left(\frac{\zeta}{Q_0^2}\right) \right) b_T^2 \right])delimiter";
      formula += R"delimiter(\left[1  - \frac{\lambda g_1^2(x) b_T^2}{4(1 + \lambda g_1(x))}\right]$$\\)delimiter";
      formula += R"delimiter($$D_{\rm NP}(x,\zeta, b_T)= \frac{1}{g_{3 a\to h} +\big(\lambda_F/z^2\big) g_{3b a \to h}^{2}})delimiter";
      //      formula += R"delimiter(\bigg(e^{- \frac{\bm{P}_{T}^2}{g_{3 a \to h}}} + \lambda_F \frac{\bm{P}_{\T}^2}{z^2} \  e^{- \frac{\bm{P}_{\T}^2}{g_{4 a \to h}}} \bigg)$$\\)delimiter";
      formula += R"delimiter($$g_{1,1b}(x) = N_{1,1b} \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$\\)delimiter";
      formula += R"delimiter($$g_{3,3b}(z) = N_{3,3b} \frac{(z^{\beta}+\delta)(1-z)^{\gamma}}{(\hat{z}^{\beta}+\delta)(1-\hat{x})^{\gamma}}$$\\)delimiter";
      formula += R"delimiter($$Q_0^2 = 1\;{\rm GeV}^2$$\\)delimiter";
      formula += R"delimiter($$\hat{x} = 0.1$$\\)delimiter";
      formula += R"delimiter($$\hat{z} = 0.5$$)delimiter";
      return formula;
    };

    std::vector<std::string> GetParameterNames() const
    {
      return {R"delimiter($g_2$)delimiter",
              R"delimiter($N_1$)delimiter",
              R"delimiter($\alpha$)delimiter",
              R"delimiter($\sigma$)delimiter",
              R"delimiter($\lambda$)delimiter",
              R"delimiter($N_3$)delimiter",
              R"delimiter($\beta$)delimiter",
              R"delimiter($\delta$)delimiter",
              R"delimiter($\gamma$)delimiter",
              R"delimiter($\lambda_F$)delimiter",
              R"delimiter($N_{3B}$)delimiter",
              R"delimiter($g_{2B}$)delimiter",
              R"delimiter($N_{1B}$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the MAP 2021 TMD analysis.";
    };

  private:
    const double _Q02  = 1;
  };
}
