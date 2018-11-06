//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <vector>
#include <utility>
#include <apfel/matrix.h>

namespace NangaParbat
{
  /**
   * @brief The "DataHandler" class is a mother class that provides a
   * common interface to all datasets. It provides methods to get
   * kinematics, central values, uncertainties, etc.
   */
  class DataHandler
  {
  public:
    /**
     * @brief Structure containing the kinematic information of one
     * single data set.
     */
    struct Kinematics
    {
      int                      ndata;  //!< Number of data points
      double                   Vs;     //!< Center of mass energy
      std::vector<double>      qTv;    //!< Vector of qT values
      std::pair<double,double> Qb;     //!< Q integration bounds
      std::pair<double,double> yb;     //!< y integration bounds
      bool                     IntqT;  //!< Whether the bins in qTv are integrated over
      bool                     IntQ;   //!< Whether the bins in Q are integrated over
      bool                     Inty;   //!< Whether the bins in y are integrated over
    };

    /**
     * @brief The default "DataHandler" constructor.
     */
    DataHandler(std::string const& name);

    /**
     * @brief Function to retrive the name of the dataset object
     */
    std::string GetName() const { return _name; };

    /**
     * @brief Function that returns the kinematic object
     */
    Kinematics GetKinematics() const { return _kin; };

    /**
     * @brief Function that returns the mean values
     */
    std::vector<double> GetMeanValues() const { return _mean; };

    /**
     * @brief Function that returns the covariance matrix
     */
    apfel::matrix<double> GetCovarianceMatrix() const { return _cov; };

  protected:
    std::string           _name;   //!< Name of the dataset
    Kinematics            _kin;    //!< Kinematics block
    std::vector<double>   _mean;   //!< vector of central values
    apfel::matrix<double> _cov;    //!< Covariance matrix
  };
}
