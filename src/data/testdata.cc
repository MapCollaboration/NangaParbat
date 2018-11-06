//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/testdata.h"

#include <iostream>

namespace NangaParbat
{
  //_________________________________________________________________________________
  TestData::TestData(double const& Vs,
		     double const& Qmin, double const& Qmax,
		     double const& ymin, double const& ymax,
		     std::vector<double> const& qTv):
    DataHandler("TestData")
  {
    // Fill in kinematics block
    this->_kin.ndata = qTv.size() - 1;
    this->_kin.Vs    = Vs;
    this->_kin.qTv   = qTv;
    this->_kin.Qb    = std::make_pair(Qmin, Qmax);
    this->_kin.yb    = std::make_pair(ymin, ymax);
    this->_kin.IntqT = true;
    this->_kin.IntQ  = true;
    this->_kin.Inty  = true;

    // Fill in vector of mean values with zero
    this->_mean = std::vector<double>(this->_kin.ndata, 0.);

    // Unity covariance matrix
    this->_cov.resize(this->_kin.ndata, this->_kin.ndata);
    for (int i = 0; i < this->_kin.ndata; i++)
      for (int j = 0; j < this->_kin.ndata; j++)
	if (i == j)
	  this->_cov(i, j) = 1;
	else
	  this->_cov(i, j) = 0;
  }
}
