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
    Parameterisation();

    /**
     * @brief Function that sets the free parameters of the
     * parameterisation.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) const { }

    std::vector<double> GetParameters() const { return _pars; }

    //virtual std::function<double(double const&, double const&, double const&)> Evaluate(int const& ifunc = 0) const = 0;

    virtual double Evaluate(double const&, double const&, double const&) const = 0;

  private:
    std::vector<double> _pars; //!< The vector of free parameters
  };
}
