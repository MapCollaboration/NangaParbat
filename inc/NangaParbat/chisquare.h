//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <numeric>

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
     * @param DSVect: vector of pairs of "DataHandler" and
     * "ConvolutionTable" objects
     * @param NPFunc: "Parameterisation" object containing the
     * non-perturbative function(s)
     */
    ChiSquare(std::vector<std::pair<DataHandler, ConvolutionTable>> const& DSVect, Parameterisation& NPFunc, double const& qToQMax = 100);

    /**
     * @brief The default "ChiSquare" constructor.

     * @param NPFunc: "Parameterisation" object containing the
     * non-perturbative function(s)
     */
    ChiSquare(Parameterisation& NPFunc, double const& qToQMax = 100);

    /**
     * @brief Add ("DataHandler","ConvolutionTable") pair block to the
     * "DSVect" vector.
     * @param DSBlock: the ("DataHandler","ConvolutionTable")-pair
     * block to be appended
     */
    void AddBlock(std::pair<DataHandler, ConvolutionTable> const& DSBlock);

    /**
     * @brief Function that returns the residuals of the
     * &chi;<SUP>2</SUP> deriving from the Cholesky decomposition of
     * the covariance matrix.
     * @param ids: the dataset index
     * @param central: if true, the residuals are computed using the
     * experimental central values rather than the fluctuated data
     * (default: false)
     * @return the vector of residuals
     */
    std::vector<double> GetResiduals(int const& ids, bool const& central = false) const;

    /**
     * @brief Function that returns the derivative of the residuals of
     * the &chi;<SUP>2</SUP> deriving from the Cholesky decomposition
     * of the covariance matrix w.r.t. the "ipar"-th parameter.
     * @param ids: the dataset index
     * @param ipar: the parameter index
     * @return the vector of derivatives of the residuals
     */
    std::vector<double> GetResidualDerivatives(int const& ids, int const& ipar) const;

    /**
     * @brief Function that returns the systematic shifts and the
     * associated penalty term of the &chi;<SUP>2</SUP>.
     * @param ids: the dataset index
     * @return a pair with the vector of nuisance parameters as a
     * first entry and the penalty as a second.
     */
    std::pair<std::vector<double>, double> GetSystematicShifts(int const& ids) const;

    /**
     * @brief Function that evaluates the &chi;<SUP>2</SUP>'s
     * @param ids: the dataset index (default: -1, the global
     * &chi;<SUP>2</SUP> is computed)
     * @param central: if true, the &chi;<SUP>2</SUP> is computed
     * using the experimental central values rather than the
     * fluctuated data (default: false)
     * @return the value of the &chi;<SUP>2</SUP> of the "ids"-th
     * block normalised to the number of data points.
     */
    double Evaluate(int const& ids = -1, bool const& central = false) const;

    /**
     * @brief Function that evaluates the (analytic) derivative of the
     * &chi;<SUP>2</SUP>'s w.r.t. the "ipar"-th parameter.
     * @return a vector containing the value of the derivatives w.r.t.
     * the parameters of global &chi;<SUP>2</SUP> normalised to the
     * number of data points.
     * @note As opposed to the Evaluate function, there seems to be no
     * need to allow for the computation of the derivarive of the
     * &chi;<SUP>2</SUP> of the single dataset.
     */
    std::vector<double> Derive() const;

    /**
     * @brief Utility operator that shortcuts the Evaluate method.
     */
    double operator()(int const& ids = -1) { return Evaluate(ids); };

    /**
     * @brief Function that sets the free parameters of the
     * parameterisation.
     * @param pars: the vector of parameters
     */
    void SetParameters(std::vector<double> const& pars) { _NPFunc.SetParameters(pars); };

    /**
     * @brief Function that returns the vector of ("DataHandler",
     * "ConvolutionTable") object-pairs for all the datasets.
     * @return The vector of ("DataHandler", "ConvolutionTable")
     * object-pairs
     */
    std::vector<std::pair<DataHandler, ConvolutionTable>> GetBlocks() const { return _DSVect; };

    /**
     * @brief Function that returns the "Parameterisation" object
     * associated to this chisquare object.
     * @return The "Parameterisation" object
     */
    Parameterisation& GetNonPerturbativeFunction() const { return _NPFunc; };

    /**
     * @brief Function that returns value of the cut in qT / Q.
     * @return The cut in qT / Q
     */
    double GetCutqToverQ() const { return _qToQMax; };

    /**
     * @brief Function that gets the number of data points that pass
     * the qT / Q cut for each data set in the form of a vector of
     * integers.
     * @return The number of data points that pass the qT / Q cut for
     * each data set
     */
    std::vector<int> GetDataPointNumbers() const { return _ndata; };

    /**
     * @brief Function that gets the number of data points that pass
     * the qT / Q cut for the whole dataset.
     * @return The number of data points that pass the qT / Q cut for
     * the whole dataset
     */
    int GetDataPointNumber() const { return std::accumulate(_ndata.begin(), _ndata.end(), 0); };

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

    /**
     * @brief Function that produces data-theory comparison plots
     * using ROOT.
     * @param path: path to where the "plots" folder will be placed
     * @note This function is parlticularly lengthy and relies on ROOT
     * and is not particularly useful. It may be convenient to remove
     * it.
     */
    void MakePlots(std::string const& path) const;

  protected:
    std::vector<std::pair<DataHandler, ConvolutionTable>> _DSVect;  //!< Vector of "DataHandler-ConvolutionTable" pairs
    Parameterisation&                                     _NPFunc;  //!< Parameterisation of the non-perturbative component
    double                                                _qToQMax; //!< Max value of the ratio qT / Q allowed in the computation of the &chi;<SUP>2</SUP>
    std::vector<int>                                      _ndata;   //!< Vector constaining the number of data points per dataset that pass the qT/Q cut

    friend YAML::Emitter& operator << (YAML::Emitter& os, ChiSquare const& chi2);
  };

  /**
   * @brief Method which prints ChiSquare feautures with cout <<.
   */
  YAML::Emitter& operator << (YAML::Emitter& os, ChiSquare const& chi2);
}
