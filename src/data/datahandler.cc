//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datahandler.h"
#include "NangaParbat/utilities.h"

#include <iostream>
#include <math.h>
#include <numeric>

namespace NangaParbat
{
  //_________________________________________________________________________________
  DataHandler::Kinematics::Kinematics():
    ndata(0),
    Vs(0),
    qTv({}),
    var1b(std::pair<double,double>{0, 0}),
    var2b(std::pair<double,double>{0, 0}),
    IntqT(false),
    Intv1(false),
    Intv2(false),
    PSRed(false),
    pTMin(0),
    etaRange(std::pair<double,double>{-10, 10})
  {
  }

  //_________________________________________________________________________________
  bool DataHandler::Kinematics::empty() const
  {
    if (ndata == 0 || Vs == 0 || qTv.empty())
      return true;
    else
      return false;
  }

  //_________________________________________________________________________________
  DataHandler::DataHandler(std::string const& name, YAML::Node const& datafile):
    _name(name),
    _proc(UnknownProcess),
    _obs(UnknownObservable),
    _targetiso(1),
    _prefact(1),
    _kin(DataHandler::Kinematics{})
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
		  throw std::runtime_error("[DataHandler::DataHandler]: Unknown process.");
	      }

	    // Observable
	    if (ql["name"].as<std::string>() == "observable")
	      {
		if (ql["value"].as<std::string>() == "d(sigma)/dydQdqT")
		  _obs = dydQdqT;
		else if (ql["value"].as<std::string>() == "d(sigma)/dxFdQdqT")
		  _obs = dxFdQdqT;
		else
		  throw std::runtime_error("[DataHandler::DataHandler]: Unknown observable.");
	      }

	    // Isoscalarity
	    if (ql["name"].as<std::string>() == "target_isoscalarity")
	      _targetiso = ql["value"].as<double>();

	    // Possible prefactor
	    if (ql["name"].as<std::string>() == "prefactor")
	      _prefact = ql["value"].as<double>();

	    // Center of mass energy
	    if (ql["name"].as<std::string>() == "Vs")
	      _kin.Vs = ql["value"].as<double>();

	    // Invariant-mass interval
	    if (ql["name"].as<std::string>() == "Q")
	      {
		_kin.var1b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
		_kin.Intv1 = ql["integrate"].as<bool>();
	      }

	    // Rapidity interval
	    if (ql["name"].as<std::string>() == "y" || ql["name"].as<std::string>() == "xF")
	      {
		_kin.var2b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
		_kin.Intv2 = ql["integrate"].as<bool>();
	      }

	    // Lepton cuts
	    if (ql["name"].as<std::string>() == "PS_reduction")
	      {
		_kin.PSRed    = true;
		_kin.pTMin    = ql["pTmin"].as<double>();
		_kin.etaRange = std::make_pair(ql["etamin"].as<double>(), ql["etamax"].as<double>());
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

    _kin.ndata = 0;
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
	      if(std::find(_kin.qTv.begin(), _kin.qTv.end(), vl["value"].as<double>()) == _kin.qTv.end())
		_kin.qTv.push_back(std::max(vl["value"].as<double>(), 1e-5));
	    }
	}

    // Check that the "DataHandler" has been properly filled in
    if (_proc == UnknownProcess ||
	_obs  == UnknownObservable ||
	_kin.empty())
      throw std::runtime_error("[DataHandler::DataHandler]: Object not properly filled in. Probably some required key is missing");

    // Now construct the covariance matrix
    _covmat.resize(_kin.ndata, _kin.ndata);
    for (int i = 0; i < _kin.ndata; i++)
      for (int j = 0; j < _kin.ndata; j++)
	_covmat(i, j) = std::inner_product(_corr[i].begin(), _corr[i].end(), _corr[j].begin(), 0.) * _mean[i] * _mean[j]
	  + (i == j ? pow(_uncor[i], 2) : 0);

    // Cholesky decomposition of the covariance matrix
    _CholL = CholeskyDecomposition(_covmat);
  }

  //_________________________________________________________________________
  std::ostream& operator << (std::ostream &os, DataHandler const& DH)
  {
    os << "\nDataHandler report:\n";

    os << "- name: " << DH._name << "\n";

    if (DH._proc == DataHandler::Process::DY)
      os << "- Process: Drell-Yan\n";
    else if (DH._proc == DataHandler::Process::SIDIS)
      os << "- Process: SIDIS\n";
    else
      os << "- Process: Unknown\n";

    if (DH._obs == DataHandler::Observable::dydQdqT)
      os << "- Observable: d(sigma)/dydQdqT\n";
    else if (DH._obs == DataHandler::Observable::dxFdQdqT)
      os << "- Observable: d(sigma)/dxFdQdqT\n";
    else
      os << "- Observable: Unknown\n";
    os << "- Target isoscalarity: " << DH._targetiso << "\n";
    os << "- Overall prefactor: " << DH._prefact << "\n";

    os << "- Number of points: " << DH._kin.ndata << "\n";
    os << "- Center-of-mass energy: " << DH._kin.Vs << " GeV\n";
    if (DH._kin.IntqT)
      os << "- qT bin-bounds: [ ";
    else
      os << "qT values: [ ";
    for (auto const& qT : DH._kin.qTv)
      os << qT << " ";
    os << "] GeV\n";

    if (DH._kin.Intv1)
      os << "- Integration bounds of the first kinematic variable: [" << DH._kin.var1b.first << ": " << DH._kin.var1b.second << "]\n";
    else
      os << "- Value of the first kinematic variable: " << ( DH._kin.var1b.first + DH._kin.var1b.second ) / 2 << "\n";

    if (DH._kin.Intv2)
      os << "- Integration bounds of the second kinematic variable: [" << DH._kin.var2b.first << ": " << DH._kin.var2b.second << "]\n";
    else
      os << "- Value of the second kinematic variable: " << ( DH._kin.var2b.first + DH._kin.var2b.second ) / 2 << "\n";

    if (DH._kin.PSRed)
      {
	os << "- Lepton minimun pT: " << DH._kin.pTMin << " GeV \n";
	os << "- Lepton range in eta: [" << DH._kin.etaRange.first << ": " << DH._kin.etaRange.second << "]\n";
      }

    os << "\n";

    return os;
  }
}
