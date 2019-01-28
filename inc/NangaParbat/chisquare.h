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
     * @param DHVect: vector of pairs of "DataHandler" and "ConvolutionTable" objects
     * @param NPFunc: "Parameterisation" object containing the non-perturbative function(s)
     */
    ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DHVect, Parameterisation& NPFunc);

    /**
     * @brief The default "ChiSquare" constructor.
     * @param NPFunc: "Parameterisation" object containing the non-perturbative function(s)
     */
    ChiSquare(Parameterisation& NPFunc);

    /**
     * @brief Add ("DataHandler","ConvolutionTable") pair block to the
     * "DHVect" vector.
     * @param DHBlock: the ("DataHandler","ConvolutionTable")-pair block to be appended
     */
    void AddBlock(std::pair<DataHandler,ConvolutionTable> const& DHBlock) { _DHVect.push_back(DHBlock); };

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

  protected:
    std::vector<std::pair<DataHandler,ConvolutionTable>> _DHVect; //!< Vector of "DataHandler" objects
    Parameterisation&                                    _NPFunc; //!< Parameterisation of the non-perturbative component
  };
}
