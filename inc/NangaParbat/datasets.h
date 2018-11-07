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

  /**
   * @brief The "ins302822" class is a derived class of "DataHandler"
   * for the E605 dataset. HEPData page:
   * https://www.hepdata.net/record/ins302822
   */
  class ins302822: public DataHandler
  {
  public:
    ins302822();
  };
}
