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
  class QGG6: public NangaParbat::Parameterisation
  {
  public:

    QGG6(): Parameterisation{"QGG6", 2, std::vector<double>{0.13, 0.285, 2.98, 0.173, 0.39, 0.0}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[QGG6::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Free paraMeters
      const double g2     = this->_pars[0];
      const double N1     = this->_pars[1];
      const double alpha  = this->_pars[2];
      const double sigma  = this->_pars[3];
      const double lambda = this->_pars[4];
      const double delta  = this->_pars[5];

      // TMD PDFs
      const double Q02 = 1;
      const double xhat = 0.1;

      const double g1   = N1 * ( pow(x, sigma) ) / ( pow(xhat, sigma) ) * pow((1 - x) / (1 - xhat), alpha);

      // ---  PV19 QGaussian + Gaussian, 6 parameters ---
      return ((1 - pow(lambda, 2)) / (pow(1 + g1 / 4 * b * b, 1)) + pow(lambda,2) * exp( - delta/ 2 * b * b ) ) * exp( - g2 * log(zeta / Q02) * b * b / 4 );
    };

    // PV19, 6 parameters
    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)=\left[\frac{1-\lambda^2}{\left(1 + \left(\frac{g_1}{4}\right)b_T^2\right)}+\lambda^2e^{-\delta\frac{b_T^2}{2}}\right]e^{- g_2 \log\left(\frac{\zeta}{Q_0^2}\right)\frac{b_T^2}{4}}$$\\)delimiter";
      formula += R"delimiter($$g_1(x) = N_1 \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$\\)delimiter";
      formula += R"delimiter($$Q_0^2 = 1\;{\rm GeV}^2$$\\)delimiter";
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
              R"delimiter($\delta$)delimiter",
              R"delimiter($\lambdaB$)delimiter",
              R"delimiter($g1B$)delimiter",
              R"delimiter($g1C$)delimiter",
              R"delimiter($qq$)delimiter"};
    };
  };
}
