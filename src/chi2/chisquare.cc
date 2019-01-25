//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/chisquare.h"
#include "NangaParbat/utilities.h"

#include <iostream>
#include <numeric>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ChiSquare::ChiSquare(std::vector<std::pair<DataHandler,ConvolutionTable>> const& DHVect):
    _DHVect(DHVect)
  {
  }

  //_________________________________________________________________________________
  ChiSquare::ChiSquare():
    _DHVect(std::vector<std::pair<DataHandler,ConvolutionTable>>{})
  {
  }

  //_________________________________________________________________________________
  double ChiSquare::Evaluate(std::function<double(double const&, double const&, double const&)> const& fNP1,
			     std::function<double(double const&, double const&, double const&)> const& fNP2,
			     int const& ids) const
  {
    // Define index range
    int istart = 0;
    int iend   = _DHVect.size();
    if (ids >= istart && ids < iend)
      {
	istart = ids;
	iend   = ids;
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
	const DataHandler dh      = _DHVect[i].first;
	const ConvolutionTable ct = _DHVect[i].second;

	// Get experimental central values
	const std::vector<double> mean = dh.GetMeanValues();

	// Get predictions according to the process
	const int proc = ct.GetProcess();
	std::vector<double> pred;
	if (proc == 0)
	  pred = ct.GetPredictions(fNP1);
	else if (proc == 1)
	  pred = ct.GetPredictions(fNP1, fNP2);
	else if (proc == 2)
	  pred = ct.GetPredictions(fNP2);
	else
	  pred = ct.GetPredictions(fNP1, fNP2);

	const int ndata = pred.size();
	if (mean.size() != ndata)
	  throw std::runtime_error("[ChiSquare::Evaluate]: mismatch in the number of points");

	// Compute residuals
	std::vector<double> res(ndata);
	for (int i = 0; i < ndata; i++)
	  res[i] = mean[i] - pred[i];

	// Solve system
	const std::vector<double> x = SolveLowerSystem(dh.GetCholeskyDecomposition(), res);

	// Compute contribution to the chi2 as absolute value of "x"
	chi2 += std::inner_product(x.begin(), x.end(), x.begin(), 0.);

	// Increment number of points
	ntot += ndata;
      }
    return chi2 / ntot;
  }

  //_________________________________________________________________________________
  double ChiSquare::Evaluate(std::function<double(double const&, double const&, double const&)> const& fNP,
			     int const& ids) const
  {
    return Evaluate(fNP, fNP, ids);
  }
}
