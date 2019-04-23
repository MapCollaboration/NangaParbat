//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/utilities.h"

#include <numeric>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ChiSquare::ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DSVect, Parameterisation& NPFunc, double const& qToQMax):
    _NPFunc(NPFunc),
    _qToQMax(qToQMax)
  {
    // The input parameterisation has to contain 2 functions, othewise
    // stop the code.
    if (_NPFunc.GetNumberOfFunctions() != 2)
      throw std::runtime_error("[ChiSquare::ChiSquare]: the number of functions of the input parameterisation is different from two");

    // Loop over the the blocks and and push them into the "_DSVect"
    // container.
    for (auto const& ds : _DSVect)
      AddBlock(ds);
  }

  //_________________________________________________________________________________
  ChiSquare::ChiSquare(Parameterisation& NPFunc, double const& qToQMax):
    ChiSquare{{}, NPFunc, qToQMax}
  {
  }

  //_________________________________________________________________________________
  void ChiSquare::AddBlock(std::pair<DataHandler,ConvolutionTable> const& DSBlock)
  {
    // Push "DataHandler-ConvolutionTable" back
    _DSVect.push_back(DSBlock);

    // Determine number of data points that pass the cut qT / Q.
    const DataHandler::Kinematics kin  = DSBlock.first.GetKinematics();
    const std::vector<double>     qTv  = kin.qTv;
    const double                  Qmin = (kin.Intv1 ? kin.var1b.first : ( kin.var1b.first + kin.var1b.second ) / 2);

    // Run over the qTv vector, count how many data points pass
    // the cut and push the number into the "_ndata" vector.
    int idata = 0;
    for (auto const& qT : qTv)
      if (qT / Qmin < _qToQMax)
        idata++;
    _ndata.push_back(idata - (kin.IntqT ? 1 : 0));
  };

  //_________________________________________________________________________________
  double ChiSquare::Evaluate(int const& ids) const
  {
    // Define index range
    int istart = 0;
    int iend   = (int) _DSVect.size();
    if (ids >= istart && ids < iend)
      {
	istart = ids;
	iend   = ids + 1;
      }
    else if (ids >= iend)
      throw std::runtime_error("[ChiSquare::Evaluate]: index out of range");

    // Initialise chi2 and number of data points
    double chi2 = 0;
    int ntot = 0;

    // Loop over the the blocks
    for (int i = istart; i < iend; i++)
      {
	// Get "DataHandler" and "ConvolutionTable" objects
	const DataHandler      dh = _DSVect[i].first;
	const ConvolutionTable ct = _DSVect[i].second;

	// Get experimental central values
	const std::vector<double> mean = dh.GetMeanValues();

	// Get predictions
	auto const fNP = [&] (double const& x, double const& b, double const& zeta, int const& ifun) -> double{ return _NPFunc.Evaluate(x, b, zeta, ifun); };
	const std::vector<double> pred = ct.GetPredictions(fNP);

	// Check that the number of points in the DataHandler and
	// Convolution table objects is the same.
	if (mean.size() != pred.size())
	  throw std::runtime_error("[ChiSquare::Evaluate]: mismatch in the number of points");

	// Compute residuals only for the points that pass the cut qT
	// / Q, set the others to zero.
	std::vector<double> res(mean.size(), 0.);
	for (int j = 0; j < _ndata[i]; j++)
	  res[j] = mean[j] - pred[j];

	// Solve system
	const std::vector<double> x = SolveLowerSystem(dh.GetCholeskyDecomposition(), res);

	// Compute contribution to the chi2 as absolute value of "x"
	chi2 += std::inner_product(x.begin(), x.end(), x.begin(), 0.);

	// Increment number of points
	ntot += _ndata[i];
      }
    return chi2 / ntot;
  }
}
