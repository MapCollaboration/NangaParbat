//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"
#include "NangaParbat/convolutiontable.h"

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
     */
    ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DHVect);

    /**
     * @brief The default "ChiSquare" constructor.
     */
    ChiSquare();

    /**
     * @brief Add ("DataHandler","ConvolutionTable") pair block to the
     * "DHVect" vector.
     * @param DHBlock: the ("DataHandler","ConvolutionTable")-pair block to be appended
     */
    void AddBlock(std::pair<DataHandler,ConvolutionTable> const& DHBlock) { _DHVect.push_back(DHBlock); };

    /**
     * @brief Function that evaluates the &chi;<SUP>2</SUP>'s
     * @param fNP1: the first non-perturbative function
     * @param fNP2: the second non-perturbative function
     * @param ids: the dataset index (default: -1, the global &chi;<SUP>2</SUP> is computed)
     * @return the value of the &chi;<SUP>2</SUP> of the "ids"-th block normalised to the number of data points.
     *
     * @note This function assumes that "fNP1" is associated to a PDF
     * and "fNP2" is associated to a FF. This is relevant when
     * computing DY, SIDIS, or e+e- annihilation into two hadrons. In
     * the first case (DY) the code uses "fNP1" only, in the second
     * case (SIDIS) it uses both "fNP1" and "fNP2", and in the third
     * case (e+e-) it uses "fNP2" only.
     */
    double Evaluate(std::function<double(double const&, double const&, double const&)> const& fNP1,
		    std::function<double(double const&, double const&, double const&)> const& fNP2,
		    int const& ids = -1) const;

    /**
     * @brief Function that evaluates the &chi;<SUP>2</SUP>'s assuming
     * that the two non-perturbative functions are equal.
     * @param fNP: the non-perturbative function
     * @param ids: the dataset index (default: -1, the global &chi;<SUP>2</SUP> is computed)
     * @return the value of the &chi;<SUP>2</SUP> of the "ids"-th block normalised to the number of data points.
     */
    double Evaluate(std::function<double(double const&, double const&, double const&)> const& fNP,
		    int const& ids = -1) const;

  protected:
    std::vector<std::pair<DataHandler,ConvolutionTable>> _DHVect; //!< Vector of "DataHandler" objects
  };
}
