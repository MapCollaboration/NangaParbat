//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Alessandro Bacchetta: alessandro.bacchetta@unipv.it

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  /**
   * @brief Parameterisation derived from the "Parameterisation"
   * mother class used to fit the pion TMDs.
   */
  class MAPTMDPion: public NangaParbat::Parameterisation
  {
  public:

    MAPTMDPion():
    Parameterisation{"MAPTMDPion", 2, std::vector<double> {0, 0, 0, 0, 0, 0, 0}}
    {};

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[MAPTMDPion::Evaluate]: function index out of range");

        // If the value of 'x' exceeds one returns zero
        if (x >= 1)
          return 0;

        // Evolution
        const double g2   = this->_pars[0];
        const double evol = exp( - g2 * log(zeta / _Q02) * b * b / 4 );

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
      else
	{
    const double N1pi     = this->_pars[5];
    const double alphapi  = this->_pars[6];
	  return evol * N1pi * exp( - pow(alphapi * b / 2, 2) );
	}

    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda}{1 + g_1(x) b_T^2/4} + \lambda \exp \left(-g_{1B}(x) b_T^2 / 4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$)delimiter";
      formula += R"delimiter($$g_1(x) = \frac{N_1}{x\sigma} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha}\right)}{2 \sigma^2} \right]$$)delimiter";
      formula += R"delimiter($$g_{1B}(x) = \frac{N_{1B}}{x\sigma_B} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha_B}\right)}{2 \sigma_B^2} \right]$$)delimiter";
      formula += R"delimiter($$Q_0^2 = 1\;{\rm GeV}^2$$)delimiter";
      return formula;
    };

    std::vector<std::string> GetParameterNames() const
    {
      return {R"delimiter($g_2$)delimiter",
              R"delimiter($N_1$)delimiter",
              R"delimiter($\alpha$)delimiter",
              R"delimiter($\sigma$)delimiter",
              R"delimiter($\lambda$)delimiter",
              R"delimiter($N_1pi$)delimiter",
              R"delimiter($\alphapi$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the Pavia 2019 TMD analysis.";
    };

  private:
    double              const _Q02 = 1;
  };
}
