//
// Author: Valerio Bertone: valerio.bertone@cern.ch,
//         Alessandro Bacchetta: alessandro.bacchetta@unipv.it

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  /**
   * @brief MAP 2021 parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class MAP22g5: public NangaParbat::Parameterisation
  {
  public:
    MAP22g5(): Parameterisation{"MAP22g5", 2, std::vector<double>{0.12840E+00, 0.28516E+00, 0.29755E+01, 0.17293E+00, 0.39432E+00, 2.12062E-01, 0.21012E+01, 0.93554E-01, 0.25246E+01, 0.52915E+01, 3.37975E-02, 0.28516E+00, 0.28516E+00, 0.39432E+00, 0.29755E+01, 0.29755E+01, 0.17293E+00, 0.17293E+00, 0.21012E+01, 0.93554E-01, 0.25246E+01, 0.01}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[MAP22g5::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Evolution
      const double g2   = this->_pars[0];
      const double g2B  = this->_pars[21];
      const double b2 = b * b;
      const double lnz    = log(zeta / _Q02);
      const double NPevol = exp( - ( pow(g2, 2) * b2 + pow(g2B, 2) * pow(b, 0.2) ) * lnz / 4 );


      // TMD PDFs
      if (ifunc == 0)
        {
          const double N1      = this->_pars[1];
          const double alpha1  = this->_pars[2];
          const double alpha2  = this->_pars[14];
          const double alpha3  = this->_pars[15];
          const double sigma1  = this->_pars[3];
          const double sigma2  = this->_pars[16];
          const double sigma3  = this->_pars[17];
          const double lambda  = this->_pars[4];
	  const double N1B     = this->_pars[11];
          const double N1C     = this->_pars[12];
          const double lambda2 = this->_pars[13];
          const double xhat    = 0.1;
          const double g1      = N1 * pow(x / xhat, sigma1) * pow((1 - x) / (1 - xhat), pow(alpha1, 2));
	  const double g1B     = N1B * pow(x / xhat, sigma2) * pow((1 - x) / (1 - xhat), pow(alpha2, 2));
          const double g1C     = N1C * pow(x / xhat, sigma3) * pow((1 - x) / (1 - xhat), pow(alpha3, 2));
	        return NPevol * ( g1 * exp( - g1 * pow(b / 2, 2))
                          +  pow(lambda, 2)  * pow(g1B, 2) * ( 1 - g1B * pow(b / 2, 2)) * exp( - g1B * pow(b / 2, 2)) + g1C * pow(lambda2, 2) * exp( - g1C * pow(b / 2, 2)))
                 / ( g1 +  pow(lambda, 2)  * pow(g1B, 2) + g1C * pow(lambda2, 2));
        }
      // TMD FFs
      else
        {
          const double N3        = this->_pars[5];
          const double beta1     = this->_pars[6];
          const double beta2     = this->_pars[18];
          //const double beta3     = this->_pars[21];
          const double delta1    = this->_pars[7];
          const double delta2    = this->_pars[19];
          //const double delta3    = this->_pars[23];
          const double gamma1    = this->_pars[8];
          const double gamma2    = this->_pars[20];
          //const double gamma3    = this->_pars[25];
          const double lambdaF   = this->_pars[9];
          const double N3B       = this->_pars[10];
          //const double N3C       = this->_pars[13];
          //const double lambdaF2  = this->_pars[15];
          const double zhat      = 0.5;
          const double cmn1      = ( ( pow(x, beta1) + pow(delta1, 2) ) / ( pow(zhat, beta1) + pow(delta1, 2) ) ) * pow((1 - x) / (1 - zhat), pow(gamma1, 2));
          const double cmn2      = ( ( pow(x, beta2) + pow(delta2, 2) ) / ( pow(zhat, beta2) + pow(delta2, 2) ) ) * pow((1 - x) / (1 - zhat), pow(gamma2, 2));
          //const double cmn3      = ( ( pow(x, beta3) + pow(delta3, 2) ) / ( pow(zhat, beta3) + pow(delta3, 2) ) ) * pow((1 - x) / (1 - zhat), pow(gamma3, 2));
          const double g3       = N3 * cmn1;
          const double g3B      = N3B * cmn2;
          //const double g3C      = N3C * cmn3;
          const double z2       = x * x;
          //return NPevol * ( g3 * exp( - g3 * pow(b / 2, 2) / z2 )
          //                + ( lambdaF / z2 ) * pow(g3B, 2) * ( 1 - g3B * pow(b / 2, 2) / z2 ) * exp( - g3B * pow(b / 2, 2) / z2 ) + g3C * lambdaF2 * exp( - g3C * pow(b / 2, 2) / z2) )
          //       / ( g3 + ( lambdaF / z2 ) * pow(g3B, 2) + g3C * lambdaF2 );
          return NPevol * ( g3 * exp( - g3 * pow(b / 2, 2) / z2 )
                          + ( lambdaF / z2 ) * pow(g3B, 2) * ( 1 - g3B * pow(b / 2, 2) / z2 ) * exp( - g3B * pow(b / 2, 2) / z2 ) )
                 / ( g3 + ( lambdaF / z2 ) * pow(g3B, 2) );
        }
    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)= \exp(S_{\rm NP}(\zeta, b_T)))delimiter";
      formula += R"delimiter(\frac{g_1(x) \exp( - g_1(x) \frac{b_T^2}{4}) + \lambda g_{1B}^2(x) ( 1 - g_{1B}(x) \frac{b_T^2}{4}) \exp( - g_{1B}(x) \frac{b_T^2}{4}) + \lambda_2^2 g_{1C}(x) exp( - g_{1C}(x) \frac{b_T^2}{4}) }{  g_1(x) +  \lambda g_{1B}^2(x) + \lambda_2^2 g_{1C}(x) }$$)delimiter";
      formula += R"delimiter($$D_{\rm NP}(z,\zeta, b_T)= \exp(S_{\rm NP}(\zeta, b_T)))delimiter";
      formula += R"delimiter(\frac{g_3(z) \exp( - g_3(z) \frac{b_T^2}{4z^2}) + \frac{\lambda_F}{z^2} g_{3B}^2(z) \big ( 1 - g_{3B}(z) \frac{b_T^2}{4z^2} \big ) \exp( - g_{3B}(z) \frac{b_T^2}{4z^2}) }{  g_3(z) +  \frac{\lambda_F}{z^2} g_{3B}^2(z) }$$)delimiter";
      formula += R"delimiter($$S_{\rm NP} = \exp\left[ - \left( g_2^2b_T^2 + g_{2B}b_T^{0.2} \right) \frac{1}{4} \log \big (\frac{\zeta}{Q_0^2}\big ) \right]$$)delimiter";
      formula += R"delimiter($$g_{1,1B,1C}(x) = N_{1,1B,1C} \frac{x^{\sigma_{1,2,3}}(1-x)^{\alpha^2_{1,2,3}}}{\hat{x}^{\sigma_{1,2,3}}(1-\hat{x})^{\alpha^2_{1,2,3}}}$$)delimiter";
      formula += R"delimiter($$g_{3,3B}(z) = N_{3,3B} \frac{(z^{\beta_{1,2}}+\delta^2_{1,2})(1-z)^{\gamma^2_{1,2}}}{(\hat{z}^{\beta_{1,2}}+\delta^2_{1,2})(1-\hat{z})^{\gamma^2_{1,2}}}$$)delimiter";
      formula += R"delimiter($$Q_0^2 = 1\;{\rm GeV}^2$$)delimiter";
      formula += R"delimiter($$\hat{x} = 0.1$$)delimiter";
      formula += R"delimiter($$\hat{z} = 0.5$$)delimiter";

      //formula  = R"delimiter($$f_{\rm NP}(x,\zeta, b_T)=\exp\left[ - \left( g_2 + \frac{1}{2}g_2 \log\left(\frac{\zeta}{Q_0^2}\right) \right) b_T^2 \right])delimiter";
      //formula += R"delimiter(\left[1  - \frac{\lambda g_1^2(x) b_T^2}{4(1 + \lambda g_1(x))}\right]$$\\)delimiter";
      //formula += R"delimiter($$D_{\rm NP}(x,\zeta, b_T)= \frac{1}{g_{3 a\to h} +\big(\lambda_F/z^2\big) g_{3b a \to h}^{2}})delimiter";
      //      formula += R"delimiter(\bigg(e^{- \frac{\bm{P}_{T}^2}{g_{3 a \to h}}} + \lambda_F \frac{\bm{P}_{\T}^2}{z^2} \  e^{- \frac{\bm{P}_{\T}^2}{g_{4 a \to h}}} \bigg)$$\\)delimiter";
      //formula += R"delimiter($$g_{1,1b}(x) = N_{1,1b} \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$\\)delimiter";
      //formula += R"delimiter($$g_{3,3b}(z) = N_{3,3b} \frac{(z^{\beta}+\delta)(1-z)^{\gamma}}{(\hat{z}^{\beta}+\delta)(1-\hat{x})^{\gamma}}$$\\)delimiter";
      //formula += R"delimiter($$Q_0^2 = 1\;{\rm GeV}^2$$\\)delimiter";
      //formula += R"delimiter($$\hat{x} = 0.1$$\\)delimiter";
      //formula += R"delimiter($$\hat{z} = 0.5$$)delimiter";
      return formula;
    };

    std::vector<std::string> GetParameterNames() const
    {
      return {R"delimiter($g_2$)delimiter",
              R"delimiter($N_1$)delimiter",
              R"delimiter($\alpha_1$)delimiter",
              R"delimiter($\sigma_1$)delimiter",
              R"delimiter($\lambda$)delimiter",
              R"delimiter($N_3$)delimiter",
              R"delimiter($\beta_1$)delimiter",
              R"delimiter($\delta_1$)delimiter",
              R"delimiter($\gamma_1$)delimiter",
              R"delimiter($\lambda_F$)delimiter",
              R"delimiter($N_{3B}$)delimiter",
              R"delimiter($N_{1B}$)delimiter",
              R"delimiter($N_{1C}$)delimiter",
              R"delimiter($\lambda_2$)delimiter",
              R"delimiter($\alpha_2$)delimiter",
              R"delimiter($\alpha_3$)delimiter",
              R"delimiter($\sigma_2$)delimiter",
              R"delimiter($\sigma_3$)delimiter",
              R"delimiter($\beta_2$)delimiter",
              R"delimiter($\delta_2$)delimiter",
              R"delimiter($\gamma_2$)delimiter",
	      R"delimiter($g_{2B}$)delimiter"};
    };

    std::string GetDescription() const
    {
      return "Parameterisation used for the MAP 2022 TMD analysis.";
    };

  private:
    const double _Q02  = 1;
   };
}
