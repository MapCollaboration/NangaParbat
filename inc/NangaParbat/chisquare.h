//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"
#include "NangaParbat/convolutiontable.h"

namespace NangaParbat
{
  /**
   * @brief The "ChiSquare" class 
   */
  class ChiSquare
  {
  public:
    /**
     * @brief The default "ChiSquare" constructor.
     * @param DHVect: vector of "DataHandler" objects
     */
    ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DHVect);

    /**
     * @brief The default "ChiSquare" constructor.
     */
    ChiSquare();

    /**
     * @brief Add "DataHandler" block to the "DHVect" vector
     * @param DHBlock:: the "DataHandler" block to be appended
     */
    void AddBlock(std::pair<DataHandler,ConvolutionTable> const& DHBlock) { _DHVect.push_back(DHBlock); };

    /**
     * @brief Function that evaluates the chi2
     * @param ids: the dataset index
     * @param fNP1: the first non-perturbative function
     * @param fNP2: the second non-perturbative function
     * @return the value of the total chi2 normalised to the number of data.
     */
    double Evaluate(std::function<double(double const&, double const&, double const&)> const& fNP1,
		    std::function<double(double const&, double const&, double const&)> const& fNP2,
		    int const& ids = -1) const;

    /**
     * @brief Function that evaluates the chi2 assuming the same
     * non-perturbative function.
     * @param ids: the dataset index
     * @param fNP: the non-perturbative function
     * @return the value of the total chi2 normalised to the number of data.
     */
    double Evaluate(std::function<double(double const&, double const&, double const&)> const& fNP,
		    int const& ids = -1) const;

  protected:
    std::vector<std::pair<DataHandler,ConvolutionTable>> _DHVect; //!< Vector of "DataHandler" objects
  };
}
