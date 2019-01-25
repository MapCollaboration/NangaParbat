//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include <vector>
#include <functional>

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
    Parameterisation(int const& nfuncs);

    /**
     * @brief Function that sets the free parameters of the
     * parameterisation.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) const { }

    /**
     * @brief Virtual function that returns the value of one of the functions.
     * @param x: momentum fraction
     * @param b: impact parameter
     * @param zeta: rapidity scale &zeta
     * @param ifunc: index of the function;
     * @return it returns the value of the ifunc-th function at (x, b,
     * &zeta;)
     */
    virtual double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const;

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
    virtual double Derive(double const& x, double const& b, double const& zeta, int const& ifunc, int const& ipar) const;

    /**
     * @defgroup ParameterisationGetters Getter functions to retrieve
     * the feauture of the parameterisation
     */
    ///@{
    int                 GetNumberOfFunctions() const { return _nfuncs; }
    std::vector<double> GetParameters()        const { return _pars; }
    ///@}

  private:
    const int           _nfuncs; //!< Number output functions
    std::vector<double> _pars;   //!< The vector of free parameters
  };
}
