//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include "NangaParbat/datahandler.h"

namespace NangaParbat
{
  /**
   * @brief The "TestData" class is a derived class of "DataHandler"
   * used for testing purposed. It instantiates and fill in a
   * "DataHandler" object with hard-coded features.
   */
  class TestData: public DataHandler
  {
  public:
    TestData(double const& Vs,
	     double const& Qmin, double const& Qmax,
	     double const& ymin, double const& ymax,
	     std::vector<double> const& qTv);
  };
}
