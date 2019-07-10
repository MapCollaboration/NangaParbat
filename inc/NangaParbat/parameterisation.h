//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <vector>
#include <iostream>

namespace NangaParbat
{
  /**
   * @brief Mother class that implements the main feautures of a
   * functional parameterisation of non-perturbative functions.
   */
  class Parameterisation
  {
  public:
    /**
     * @brief The "Parameterisation" constructor
     */
    Parameterisation(std::string const& name, int const& nfuncs = 0, std::vector<double> pars = {});

    /**
     * @brief The "Parameterisation" destructor
     */
    virtual ~Parameterisation() {};

    /**
     * @brief Function that sets the free parameters of the
     * parameterisation.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) { _pars = pars; };

    /**
     * @brief Virtual function that returns the value of one of the functions.
     * @param x: momentum fraction
     * @param b: impact parameter
     * @param zeta: rapidity scale &zeta
     * @param ifunc: index of the function;
     * @return it returns the value of the ifunc-th function at (x, b,
     * &zeta;)
     */
    virtual double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const { return 0; };

    /**
     * @brief Virtual function that returns the value of the
     * derivative of one of the functions.
     * @param x: momentum fraction
     * @param b: impact parameter
     * @param zeta: rapidity scale
     * @param ifunc: index of the function;
     * @param ipar: index of the parameter
     * @return it returns the value of the derivative w.r.t. the
     * ipar-th parameter of the ifunc-th function at (x, b, &zeta;)
     */
    virtual double Derive(double const& x, double const& b, double const& zeta, int const& ifunc, int const& ipar) const { return 0; };

    /**
     * @defgroup ParameterisationGetters Getter functions to retrieve
     * the feauture of the parameterisation
     */
    ///@{
    std::string         GetName()              const { return _name; }
    int                 GetNumberOfFunctions() const { return _nfuncs; }
    std::vector<double> GetParameters()        const { return _pars; }
    ///@}

  protected:
    std::string         _name;   //!< Name of the parameterisation
    int                 _nfuncs; //!< Number of output functions
    std::vector<double> _pars;   //!< The vector of free parameters
  };
}
