//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/parameterisation.h"

#include <math.h>

namespace NangaParbat
{
  /**
   * @brief Pavia 20117 parameterisation derived from the
   * "Parameterisation" mother class.
   */
  class PV17: public NangaParbat::Parameterisation
  {
  public:

    PV17(): Parameterisation{"PV17", 2, std::vector<double>{0.13, 0.285, 2.98, 0.173, 0.39}} { };

    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const
    {
      if (ifunc < 0 || ifunc >= this->_nfuncs)
        throw std::runtime_error("[PV17::Evaluate]: function index out of range");

      // If the value of 'x' exceeds one returns zero
      if (x >= 1)
        return 0;

      // Free paraMeters
      const double g2     = this->_pars[0];
      const double Npt    = this->_pars[1];
      const double alpha  = this->_pars[2];
      const double sigma  = this->_pars[3];
      const double lambda = this->_pars[4];

      // TMD PDFs
      const double Q02  = 1;
      const double xhat = 0.1;
      const double g1   = Npt * pow(x / xhat, sigma) * pow((1 - x) / (1 - xhat), alpha);

      return exp( - ( g1 + g2 * log(zeta / Q02) / 2 ) * b * b ) * ( 1 - lambda * pow(g1 * b / 2, 2) / ( 1 + lambda * g1 ) );
    };

    std::string LatexFormula() const
    {
      std::string formula;
      formula  = "$$f_{\\rm NP}(x,\\zeta, b_T)=\\exp\\left[ - \\left( g_1(x) + \\frac{1}{2}g_2 \\log\\left(\\frac{\\zeta}{Q_0^2}\\right) \\right) b_T^2 \\right]";
      formula += "\\left[1  - \\frac{\\lambda g_1^2(x) b_T^2}{4(1 + \\lambda g_1(x))}\\right]$$\n";
      formula += "$$g_1(x) = N_1 \\frac{x^{\\sigma}(1-x)^{\\alpha}}{\\hat{x}^{\\sigma}(1-\\hat{x})^{\\alpha}}$$\n";
      formula += "$$Q_0^2 = 1\\;{\\rm GeV}^2$$\n";
      formula += "$$\\hat{x} = 0.1$$";
      return formula;
    };
  };
}
