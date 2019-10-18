//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti

#pragma once

#include "NangaParbat/parameterisation.h"

namespace NangaParbat
{
  /**
   * @brief Parameterisation derived from the "Parameterisation"
   * mother class to compute the mean replica of a Monte Carlo set.
   */
  class MeanReplica: public NangaParbat::Parameterisation
  {
  public:
    /**
     * @brief The "Parameterisation" constructor
     * @param InputFolder: path to the folder where the replicas are
     * @param FitConfigFile: configuration file in YAML format
     */
    MeanReplica(std::string const& InputFolder, std::string const& FitConfigFile);

    /**
     * @brief The "MeanReplica" destructor
     */
    ~MeanReplica();

    /**
     * @brief Function that returns the value of one of the functions.
     * @param x: momentum fraction
     * @param b: impact parameter
     * @param zeta: rapidity scale &zeta;
     * @param ifunc: index of the function
     * @return it returns the value of the ifunc-th function at (x, b,
     * &zeta;)
     */
    double Evaluate(double const& x, double const& b, double const& zeta, int const& ifunc) const;

    /**
     * @brief Function that returns a string with the formula
     * of the non-perturbative function(s) in LaTex format.
     */
    std::string LatexFormula() const;

    /**
     * @brief Function that returns a vector of strings containing the
     * names of the parameters in LaTex format.
     */
    std::vector<std::string> GetParameterNames() const;

  private:
    NangaParbat::Parameterisation               *_NPFunc;
    std::vector<NangaParbat::Parameterisation*>  _NPFuncv;
  };
}
