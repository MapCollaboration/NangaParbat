//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"
#include "NangaParbat/convolutiontable.h"
#include "NangaParbat/parameterisation.h"

namespace NangaParbat
{
  /**
   * @brief The "ChiSquare" class computes the &chi;<SUP>2</SUP>'s
   * given a set of "DataHandler" objects and the corresponding
   * "ConvolutionTable" objects. The computation depends of the
   * non-perturbative functions given as input.
   */
  class ChiSquare
  {
  public:
    /**
     * @brief The "ChiSquare" constructor.
     * @param DSVect: vector of pairs of "DataHandler" and "ConvolutionTable" objects
     * @param NPFunc: "Parameterisation" object containing the non-perturbative function(s)
     */
    ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DSVect, Parameterisation& NPFunc, double const& qToQMax = 100);

    /**
     * @brief The default "ChiSquare" constructor.
     * @param NPFunc: "Parameterisation" object containing the non-perturbative function(s)
     */
    ChiSquare(Parameterisation& NPFunc, double const& qToQMax = 100);

    /**
     * @brief Add ("DataHandler","ConvolutionTable") pair block to the
     * "DSVect" vector.
     * @param DSBlock: the ("DataHandler","ConvolutionTable")-pair block to be appended
     */
    void AddBlock(std::pair<DataHandler,ConvolutionTable> const& DSBlock);

    /**
     * @brief Function that returns the residuals of the chi2 deriving
     * from the Cholesky decomposition of the covariance matrix.
     * @param ids: the dataset index
     * @return the vector of residuals
     */
    std::vector<double> GetResiduals(int const& ids) const;

    /**
     * @brief Function that evaluates the &chi;<SUP>2</SUP>'s
     * @param ids: the dataset index (default: -1, the global &chi;<SUP>2</SUP> is computed)
     * @return the value of the &chi;<SUP>2</SUP> of the "ids"-th block normalised to the number of data points.
     */
    double Evaluate(int const& ids = -1) const;

    /**
     * @brief Utility operator that replaces the Evaluate method
     * above.
     */
    double operator()(int const& ids = -1) { return Evaluate(ids); };

    /**
     * @brief Function that sets the free parameters of the
     * parameterisation.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) { _NPFunc.SetParameters(pars); };

    /**
     * @brief Function that gets the number of data points that pass
     * the qT / Q cut for each data set in the form of a vector of
     * integers.
     * @return The number of data points that pass the qT / Q cut for
     * each data set
     */
    std::vector<int> GetDataPointNumbers() const { return _ndata; };

    /**
     * @brief Function that returns the number of experiments.
     * @return The number of experiments.
     */
    int GetNumberOfExperiments() const { return (int) _ndata.size(); };

    /**
     * @brief Function that returns the number of parameters of the
     * parameterisation objects.
     * @return The number of parameters.
     */
    int GetNumberOfParameters() const { return (int) _NPFunc.GetParameters().size(); };

    /**
     * @brief Function that returns the parameters of the
     * parameterisation objects.
     * @return The vector containing the parameters.
     */
    std::vector<double> GetParameters() const { return _NPFunc.GetParameters(); };

  protected:
    std::vector<std::pair<DataHandler,ConvolutionTable>> _DSVect;  //!< Vector of "DataHandler-ConcolutionTable" pairs
    Parameterisation&                                    _NPFunc;  //!< Parameterisation of the non-perturbative component
    double                                               _qToQMax; //!< Max value of the ratio qT / Q allowed in the computation of the chi2
    std::vector<int>                                     _ndata;   //!< Vector constaining the number of data points per dataset that pass the qT/Q cut

    friend std::ostream& operator<<(std::ostream& os, ChiSquare const& chi2);
  };

  /**
   * @brief Method which prints ChiSquare feautures with cout <<.
   */
  std::ostream& operator << (std::ostream& os, ChiSquare const& chi2);
}
