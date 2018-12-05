//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"

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
    ChiSquare(std::vector<DataHandler> const& DHVect);

    /**
     * @brief The default "ChiSquare" constructor.
     */
    ChiSquare();

    /**
     * @brief Add "DataHandler" block to the "DHVect" vector
     * @param DHBlock:: the "DataHandler" block to be appended
     */
    void AddBlock(DataHandler const& DHBlock) { _DHVect.push_back(DHBlock); };

    /**
     * @brief Function that evaluates the chi2
     * @param ids: the dataset index
     * @param pred: the vector of predictions
     * @return the value of the total chi2 normalised to the number of data.
     */
    double Evaluate(int const& ids, std::vector<double> const& pred) const;

  protected:
    std::vector<DataHandler> _DHVect; //!< Vector of "DataHandler" objects
  };
}
