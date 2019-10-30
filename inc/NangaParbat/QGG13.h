//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>
#include <apfel/constants.h>

namespace NangaParbat
{
  /**
   * @brief Pavia 2019 parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class QGG13: public NangaParbat::Parameterisation
  {
  public:

    QGG13(): Parameterisation{"QGG13", 2, std::vector<double>{0.13, 0.285, 2.98, 0.173, 0.39, 0., 0.1, 0.1, 0., 0., 0., 0.1, 1.}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[QGG13::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Free paraMeters
      const double g2      = this->_pars[0];
      const double N1      = this->_pars[1];
      const double alpha   = this->_pars[2];
      const double sigma   = this->_pars[3];
      const double delta   = this->_pars[4];
      const double lambdaB = this->_pars[5];
      const double N1B     = this->_pars[6];
      const double alphaB  = this->_pars[7];
      const double sigmaB  = this->_pars[8];
      const double deltaB  = this->_pars[9];
      const double lambdaC = this->_pars[10];
      const double g1C     = this->_pars[11];
      const double qq      = this->_pars[12];

      // TMD PDFs
      const double Q02   = 1;
      const double xhat  = 0.1;
      const double g1    = N1 * ( pow(x, sigma) + delta ) / ( pow(xhat, sigma) + delta ) * pow((1 - x) / (1 - xhat), alpha);
      const double g1B   = N1B * ( pow(x, sigmaB) + deltaB ) / ( pow(xhat, sigmaB) + deltaB ) * pow((1 - x) / (1 - xhat), alphaB);

      return (
               ((1 - pow(lambdaB, 2)) / (pow(1 +  g1/4  * b * b, qq)))
               +  pow(lambdaB, 2) *
               (
                 g1B * exp( - g1B / 4  * b * b )
                 + pow(lambdaC, 2) * pow(g1C, 2) * ( 1 - g1C / 4  * b * b )
                 * exp( - g1C / 4  * b * b )
               )
               / (g1B + pow(lambdaC, 2) * pow(g1C, 2))
             )
             * exp( - g2 * log(zeta / Q02) * b * b / 4 );
    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)= \Biggl(\frac{1-\lambda_B^2}{1 + g_1^2(x) b_T^2/4} + \lambda_B^2 \exp \left(-g_{1B} b_T^2 /4 \right)\Biggr) \exp\left[ - g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4\right]$$)delimiter";
      formula += R"delimiter($$g_1(x) = N_1 \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$)delimiter";
      formula += R"delimiter($$g_{1B}(x) = N_{1B} \frac{x^{\sigma_B}(1-x)^{\alpha_B}}{\hat{x}^{\sigma_B}(1-\hat{x})^{\alpha_B}}$$)delimiter";
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
              R"delimiter($\delta$)delimiter",
              R"delimiter($\lambdaB$)delimiter",
              R"delimiter($N_{1B}$)delimiter",
              R"delimiter($\alpha_B$)delimiter",
              R"delimiter($\sigma_B$)delimiter",
              R"delimiter($\delta_B$)delimiter",
              R"delimiter($\lambdaC$)delimiter",
              R"delimiter($g1C$)delimiter",
              R"delimiter($qq$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation with a q-Gaussian and a Gaussian and 13 parameters.";
    };
  };
}
