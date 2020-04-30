//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  /**
   * @brief Pavia 2017 parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class PV17: public NangaParbat::Parameterisation
  {
  public:
    // The default parameters correspond to those of replica 105 of
    // the PV17 fit. See Tabs. X and XI of
    // https://arxiv.org/pdf/1703.10157.pdf.
    PV17(): Parameterisation{"PV17", 2, std::vector<double>{0.128, 0.285, 2.98, 0.173, 0.39, 0.212, 2.10, 0.094, 2.52, 5.29, 0.033}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[PV17::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Evolution
      const double g2   = this->_pars[0];
      const double Q02  = 1;
      const double evol = exp( - g2 * log(zeta / Q02) * b * b / 4 );

      // TMD PDFs
      if (ifunc == 0)
        {
          const double N1     = this->_pars[1];
          const double alpha  = this->_pars[2];
          const double sigma  = this->_pars[3];
          const double lambda = this->_pars[4];
          const double xhat   = 0.1;
          const double g1     = N1 * pow(x / xhat, sigma) * pow((1 - x) / (1 - xhat), alpha);
          return evol * exp( - g1 * pow(b / 2, 2) ) * ( 1 - lambda * pow(g1 * b / 2, 2) / ( 1 + lambda * g1 ) );
        }
      // TMD FFs
      else
        {
          const double N3      = this->_pars[5];
          const double beta    = this->_pars[6];
          const double delta   = this->_pars[7];
          const double gamma   = this->_pars[8];
          const double lambdaF = this->_pars[9];
          const double N4      = this->_pars[10];
          const double zhat    = 0.5;
          const double cmn     = ( ( pow(x, beta) + delta ) / ( pow(zhat, beta) + delta ) ) * pow((1 - x) / (1 - zhat), gamma);
          const double g3      = N3 * cmn;
          const double g4      = N4 * cmn;
          const double z2      = x * x;
          return evol * ( g3 * exp( - g3 * pow(b / 2, 2) / z2 )
                          + ( lambdaF / z2 ) * pow(g4, 2) * ( 1 - g4 * pow(b / 2, 2) / z2 ) * exp( - g4 * pow(b / 2, 2) / z2 ) )
                 / ( z2 * ( g3 + ( lambdaF / z2 ) * pow(g4, 2) ) );
        }
    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)=\exp\left[ - \left( g_1(x) + \frac{1}{2}g_2 \log\left(\frac{\zeta}{Q_0^2}\right) \right) b_T^2 \right])delimiter";
      formula += R"delimiter(\left[1  - \frac{\lambda g_1^2(x) b_T^2}{4(1 + \lambda g_1(x))}\right]$$\\)delimiter";
      formula += R"delimiter($$D_{\rm NP}(x,\zeta, b_T)=\mbox{ Whatever}$$\\)delimiter";
      formula += R"delimiter($$g_1(x) = N_1 \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$\\)delimiter";
      formula += R"delimiter($$g_{3,4}(z) = N_{3,4} \frac{(z^{\beta}+\delta)(1-z)^{\gamma}}{(\hat{z}^{\beta}+\delta)(1-\hat{x})^{\gamma}}$$\\)delimiter";
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
              R"delimiter($N_4$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the Pavia 2017 TMD analysis.";
    };
  };
}
