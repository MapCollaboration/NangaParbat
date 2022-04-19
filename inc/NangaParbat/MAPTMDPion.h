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

    MAPTMDPion(YAML::Node Parameters, int const& ReplicaID):
    Parameterisation{"MAPTMDPion", 2, std::vector<double> {0, 0, 0, 0, 0, 0, 0, 0, 0}}
    {
      _ProtonPars = Parameters["Parameters"].as<std::vector<std::vector<double>>>()[ReplicaID];
    };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[MAPTMDPion::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      const double g2  = this->_pars[0];
      const double g2B = this->_pars[8];

      // bT-dependent bits
      const double b2 = b * b;

      // zeta-dependent bit (i.e. non perturbative evolution)
      const double NPevol = exp( - ( g2 + g2B * b2 ) * b2 * log(zeta / _Q02) / 4 );

      // TMD proton PDFs
      if (ifunc == 0)
        {
          // Free parameters
          const double N1     = this->_pars[1];
          const double alpha  = this->_pars[2];
          const double sigma  = this->_pars[3];
          const double lambda = this->_pars[4];
          const double N1B    = this->_pars[5];
          const double alphaB = this->_pars[6];
          const double sigmaB = this->_pars[7];

          // x-dependent bits
          const double g1  = N1  * exp( - pow(log(x / alpha),  2) / 2 / pow(sigma, 2)  ) / x / sigma;
          const double g1B = N1B * exp( - pow(log(x / alphaB), 2) / 2 / pow(sigmaB, 2) ) / x / sigmaB;

          return ( ( 1 - lambda ) / ( 1 + g1 / 4 * b2 ) + lambda * exp( - g1B / 4 * b2 ) ) * NPevol;
        }
      else
	{
	  return 0;
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
              R"delimiter($N_{1B}$)delimiter",
              R"delimiter($\alpha_B$)delimiter",
              R"delimiter($\sigma_B$)delimiter",
              R"delimiter($g_{2B}$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the Pavia 2019 TMD analysis.";
    };

  private:
    double              const _Q02 = 1;
    std::vector<double>       _ProtonPars;
  };
}
