//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <vector>
#include <utility>

#include <apfel/matrix.h>
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  /**
   * @brief The "DataHandler" class provides a common interface to all
   * datasets. It provides methods to get kinematics, central values,
   * uncertainties, etc.
   */
  class DataHandler
  {
  public:
    /**
     * @brief The process enumerator
     */
    enum Process: int {DY, SIDIS};

    /**
     * @brief The observable enumerator
     */
    enum Observable: int {dydQdqT, dxFdQdqT};

    /**
     * @brief Structure containing the kinematic information of one
     * single data set.
     */
    struct Kinematics
    {
      int                      ndata;  //!< Number of data points
      double                   Vs;     //!< Center of mass energy
      std::vector<double>      qTv;    //!< Vector of qT values
      std::pair<double,double> var1b;  //!< Variable 1 integration bounds
      std::pair<double,double> var2b;  //!< Variable 1 integration bounds
      bool                     IntqT;  //!< Whether the bins in qTv are integrated over
      bool                     Intv1;  //!< Whether the bins in Q are integrated over
      bool                     Intv2;  //!< Whether the bins in y are integrated over
    };

    /**
     * @brief The "DataHandler" constructor.
     * @param name: the name associated to the data set
     * @param datafile: the YAML:Node with the interpolation table
     */
    DataHandler(std::string const& name, YAML::Node const& datafile);

    /**
     * @brief Function that returns the name of the dataset
     */
    std::string GetName() const { return _name; };

    /**
     * @brief Function that returns the process code
     */
    Process GetProcess() const { return _proc; };

    /**
     * @brief Function that returns the observable code
     */
    Observable GetObservable() const { return _obs; };

    /**
     * @brief Function that returns the target isoscalarity
     * @note The code always assumes that one of the hadrons has
     * isoscalarity 1, meaning that it's a single hadron whose
     * distributions don't need to be manipulated.
     */
    double GetTargetIsoscalarity() const { return _targetiso; };

    /**
     * @brief Function that returns any possible constant prefactor to
     * be used to multiply the theoretical predictions.
     */
    double GetPrefactor() const { return _prefact; };

    /**
     * @brief Function that returns the kinematic object
     */
    Kinematics GetKinematics() const { return _kin; };

    /**
     * @brief Function that returns the mean values
     */
    std::vector<double> GetMeanValues() const { return _mean; };

    /**
     * @brief Function that returns the covariance matrix of the
     * correlated uncertainties.
     */
    apfel::matrix<double> GetCovarianceMatrix() const { return _covmat; };

    /**
     * @brief Function that returns the sum in quadrature of the
     * uncorrelated uncertainties.
     */
    std::vector<double> GetUncorrelatedUnc() const { return _uncor; };

    /**
     * @brief Function that returns the Cholesky decomposition of the
     * covariance matrix.
     */
    apfel::matrix<double> GetCholeskyDecomposition() const { return _CholL; };

  protected:
    std::string                      _name;        //!< Name of the dataset
    Process                          _proc;        //!< The process
    Observable                       _obs;         //!< The observable
    double                           _targetiso;   //!< Isoscalarity of the target
    double                           _prefact;     //!< Possible prefactor to multiply the theoretical predictions
    Kinematics                       _kin;         //!< Kinematics block
    std::vector<double>              _mean;        //!< Vector of central values
    std::vector<double>              _uncor;       //!< Vector of uncorrelated uncertainties
    std::vector<std::vector<double>> _corr;        //!< Correlated uncertainties
    apfel::matrix<double>            _covmat;      //!< Covariance matrix
    apfel::matrix<double>            _CholL;       //!< Cholesky decomposition of the covariance matrix
  };
}
