//
// Author: Lorenzo Rossi
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
  class PV17jet3w: public NangaParbat::Parameterisation
  {
  public:
    // The default parameters correspond to those of replica 105 of
    // the PV17 fit. See Tabs. X and XI of
    // https://arxiv.org/pdf/1703.10157.pdf.
    PV17jet3w(): Parameterisation{"PV17jet3w", 2, std::vector<double>{0.12840E+00, 0.28516E+00, 0.29755E+01, 0.17293E+00, 0.39432E+00, 0.3E+00, 0.3E+00,0.05E+00}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[PV17jet::Evaluate]: function index out of range");

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
      // TMDJets
      else
        {
          const double g3           = this->_pars[5];
          const double lambda3      = this->_pars[6];
          const double g4           = this->_pars[7];
          //return evol * exp( - g3 * pow(b / 2, 2) ) * ( 1 + lambda * pow(g3 * b / 2, 2) / ( 1 + lambda * g3 ) );
          //return evol * exp( - g3 * pow(b / 2, 2) ) * pow(g3 * b / 2, 2) / ( 1 + g3 );
          //return evol * pow(1 + g3* pow( b / 2, 2), -4);
          // return evol * exp( - g3 * b * b / 4 ); // + 0. * x;
          return evol  * ( g3 * exp( - g3 * pow(b / 2, 2) ) +  pow(lambda3, 2)  * pow(g4, 2) * ( 1 - g4 * pow(b / 2, 2)) * exp( - g4 * pow(b / 2, 2)) ) / ( g3 + pow(lambda3, 2)  * pow(g4, 2) );
        }
    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)=\exp\Biggl[ - g_2 \log\left(\frac{\zeta}{Q_0^2}\right) \frac{b_T^2}{4}\Biggr]\exp\Biggl[ - g_1 \frac{b_T^2}{4}\Biggr]\left[1 - \frac{\lambda g_1^2(x)}{(1 + \lambda g_1(x))}\frac{b_T^2}{4}\right]$$)delimiter";
      formula += R"delimiter($$D_{\rm NP}(\zeta, b_T)=\exp\Biggl[ - g_2 \log\left(\frac{\zeta}{Q_0^2}\right) \frac{b_T^2}{4}\Biggr]\frac{\Biggl( \exp\left[ - g_3 \frac{b_T^2}{4}$$)delimiter";
      formula += R"delimiter($$g_1(x) = N_1 \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$)delimiter";
      formula += R"delimiter($$Q_0^2 = 1\;{\rm GeV}^2$$)delimiter";
      formula += R"delimiter($$\hat{x} = 0.1$$)delimiter";
      return formula;
    };

    std::vector<std::string> GetParameterNames() const
    {
      return {R"delimiter($g_2$)delimiter",
              R"delimiter($N_1$)delimiter",
              R"delimiter($\alpha$)delimiter",
              R"delimiter($\sigma$)delimiter",
              R"delimiter($\lambda$)delimiter",
              R"delimiter($g_3$)delimiter",
              R"delimiter($\lambda3$)delimiter",
              R"delimiter($g_4$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the Pavia 2017 TMDJet analysis.";
    };
  };
}
