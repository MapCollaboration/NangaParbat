//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datasets.h"

#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  TestData::TestData(double const& Vs,
		     double const& Qmin, double const& Qmax,
		     double const& ymin, double const& ymax,
		     std::vector<double> const& qTv):
    DataHandler("TestData")
  {
    // Process
    this->_proc = DY;

    // Fill in kinematics block
    this->_kin.ndata = qTv.size() - 1;
    this->_kin.Vs    = Vs;
    this->_kin.qTv   = qTv;
    this->_kin.var1b = std::make_pair(Qmin, Qmax);
    this->_kin.var2b = std::make_pair(ymin, ymax);
    this->_kin.IntqT = true;
    this->_kin.Intv1 = true;
    this->_kin.Intv2 = true;

    // Fill in vector of mean values with zero
    this->_mean = std::vector<double>(this->_kin.ndata, 0.);

    // Fill in vector of uncorrelated uncertainties (all 1)
    this->_unc = std::vector<double>(this->_kin.ndata, 1.);

    // Zero uncorrelated covariance matrix
    this->_cov.resize(this->_kin.ndata, this->_kin.ndata);
    for (int i = 0; i < this->_kin.ndata; i++)
      for (int j = 0; j < this->_kin.ndata; j++)
	this->_cov(i, j) = 0;
  }

  //_________________________________________________________________________________
  ins302822::ins302822():
    DataHandler("ins302822")
  {
    // Try to open HEPData submission.yaml file in the "data"
    // folder.
    const std::vector<YAML::Node> subfile = YAML::LoadAllFromFile(this->_datafolder + "HEPData-" + this->_name + "-v1-yaml/submission.yaml");

    // Loop over the sumbission file to get the available tables
    std::vector<std::string> tables;
    for (auto const& f : subfile)
      if (f["data_file"])
	tables.push_back(f["data_file"].as<std::string>());

    for (auto const& t : tables)
      std::cout << t << std::endl;
  }
}
