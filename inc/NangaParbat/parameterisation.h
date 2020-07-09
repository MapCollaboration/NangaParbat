//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <vector>
#include <iostream>
#include <functional>
#include <map>

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
     * @param name: name of the parameterisation object
     * @param nfuncs: number of parametric functions
     * @param pars: vector of parameters (default: empty vector)
     * @param anders: whether analytic derivatives are provided
     */
    Parameterisation(std::string const& name, int const& nfuncs = 0, std::vector<double> pars = {}, bool const& anders = false);

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
     * @param zeta: rapidity scale &zeta;
     * @param ifunc: index of the function
     * @return it returns the value of the ifunc-th function at (x, b,
     * &zeta;)
     */
    virtual double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const { return 0; };

    /**
     * @brief Function that returns the parametrisation in the form of
     * a std::function.
     */
    std::function<double(double const&, double const&, double const&, int const&)> Function() const;
    virtual std::function<std::map<int, double>(double const &, double const &)> LHAPDF_Function() const { this->LHAPDF_Function(); }

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
     * @brief Function that returns the derivative of the
     * parametrisation in the form of a std::function.
     */
    std::function<double(double const&, double const&, double const&, int const&, int const&)> Derivative() const;

    /**
     * @brief Virtual function that returns a string with the formula
     * of the non-perturbative function(s) in LaTex format.
     */
    virtual std::string LatexFormula() const { return ""; };

    /**
     * @brief Virtual function that returns a vector of strings
     * containing the names of the parameters in LaTex format.
     */
    virtual std::vector<std::string> GetParameterNames() const { return {}; };

    /**
     * @brief Virtual function that returns a short description of the
     * parametrisation.
     */
    virtual std::string GetDescription() const { return ""; };

    /**
     * @name Getters
     * Functions to retrieve the feauture of the parameterisation
     */
    ///@{
    std::string         GetName()              const { return _name; }
    int                 GetNumberOfFunctions() const { return _nfuncs; }
    std::vector<double> GetParameters()        const { return _pars; }
    bool                HasGradient()          const { return _anders; }
    ///@}

  protected:
    std::string         _name;   //!< Name of the parameterisation
    int                 _nfuncs; //!< Number of output functions
    std::vector<double> _pars;   //!< The vector of free parameters
    bool                _anders; //!< Whether the parametersation provides analytic derivatives
  };
}
