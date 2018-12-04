//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datahandler.h"

#include <iostream>
#include <math.h>
#include <numeric>

namespace NangaParbat
{
  //_________________________________________________________________________________
  DataHandler::DataHandler(std::string const& name, YAML::Node const& datafile):
    _name(name)
  {
    // Retrieve kinematics
    for (auto const& dv : datafile["dependent_variables"])
      {
	// Run over the qualifiers
	for (auto const& ql : dv["qualifiers"])
	  {
	    // Process
	    if (ql["name"].as<std::string>() == "process")
	      {
		if (ql["value"].as<std::string>() == "DY")
		  _proc = DY;
		else if (ql["value"].as<std::string>() == "SIDIS")
		  _proc = SIDIS;
		else
		  {
		    std::cout << "DataHandler: Unknown process" << std::endl;
		    exit(-10);
		  }
	      }

	    // Center of mass energy
	    if (ql["name"].as<std::string>() == "SQRT(S)")
	      _kin.Vs = ql["value"].as<double>();

	    // Invariant-mass interval
	    if (ql["name"].as<std::string>() == "Q")
	      {
		_kin.var1b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
		_kin.Intv1 = ql["integrate"].as<bool>();
	      }

	    // Rapidity interval interval
	    if (ql["name"].as<std::string>() == "y")
	      {
		_kin.var2b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
		_kin.Intv2 = ql["integrate"].as<bool>();
	      }
	  }

	// Run over the data point values and uncertainties
	for (auto const& vl : dv["values"])
	  {
	    // Read central values
	    _mean.push_back(vl["value"].as<double>());

	    // Read uncertainties
	    std::vector<double> c;
	    for (auto const& err : vl["errors"])
	      {
		if (err["label"].as<std::string>() == "unc")
		  _uncor.push_back(err["value"].as<double>());
		if (err["label"].as<std::string>() == "mult" || err["label"].as<std::string>() == "add")
		  c.push_back(err["value"].as<double>());
	      }
	    _corr.push_back(c);
	  }
      }

    // Transverse momentum bin bounds
    for (auto const& iv : datafile["independent_variables"])
      for (auto const& vl : iv["values"])
	{
	  _kin.ndata++;
	  if (vl["low"])
	    {
	      _kin.IntqT = true;
	      if(std::find(_kin.qTv.begin(), _kin.qTv.end(), vl["low"].as<double>()) == _kin.qTv.end())
		_kin.qTv.push_back(std::max(vl["low"].as<double>(), 1e-5));
	      if(std::find(_kin.qTv.begin(), _kin.qTv.end(), vl["high"].as<double>()) == _kin.qTv.end())
		_kin.qTv.push_back(vl["high"].as<double>());
	    }
	  else
	    {
	      _kin.IntqT = false;
	      if(std::find(_kin.qTv.begin(), _kin.qTv.end(), vl.as<double>()) == _kin.qTv.end())
		_kin.qTv.push_back(std::max(vl.as<double>(), 1e-5));
	    }
	}

    // Now construct the covariance matrix
    _covmat.resize(_kin.ndata, _kin.ndata);
    for (int i = 0; i < _kin.ndata; i++)
      for (int j = 0; j < _kin.ndata; j++)
	_covmat(i, j) = std::inner_product(_corr[i].begin(), _corr[i].end(), _corr[j].begin(), 0.) + (i == j ? pow(_uncor[i], 2) : 0);
  }
}
