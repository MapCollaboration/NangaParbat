//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datahandler.h"

#include <iostream>

namespace NangaParbat
{
  //_________________________________________________________________________________
  DataHandler::DataHandler(std::string const& name, std::string const& datafolder):
    _datafolder(datafolder),
    _name(name)
  {




  // std::vector<Kinematics> RetrieveKinematics(YAML::Node const& datalist)
  // {
  //   // Initialise output container
  //   std::vector<Kinematics> KinVect;

  //   // Loop over the dataset list. Each dataset may have more than one
  //   // distribution. Threfore, loop also over the distributions.
  //   for (auto const& dl : datalist)
  //     for (auto const& dist : dl.second)
  // 	{
  // 	  // Open HEPData datafile name
  // 	  const YAML::Node df = YAML::LoadFile("../Data/" + dl.first.as<std::string>() + "/" + dist.as<std::string>());

  // 	  // Initialise a "Kinematics" object
  // 	  Kinematics kin;

  // 	  // Assing to the "kin" structure the name of the data file
  // 	  // along with its folder.
  // 	  kin.name = dl.first.as<std::string>() + "_" + dist.as<std::string>();

  // 	  // Retrieve kinematics
  // 	  for (auto const& dv : df["dependent_variables"])
  // 	    for (auto const& ql : dv["qualifiers"])
  // 	      {
  // 		// We assume that each table contains one single bin
  // 		// in rapidity and one single bin in invariant mass
  // 		// that need to be integrated over. In addition we
  // 		// interpret the qT vector as a vector o bounds of the
  // 		// bins that also need to be integrated over.
  // 		kin.IntqT = true;

  // 		// Rapidity interval interval
  // 		if (ql["name"].as<std::string>() == "ABS(ETARAP)")
  // 		  {
  // 		    std::string tmp;
  // 		    std::stringstream ss(ql["value"].as<std::string>());
  // 		    ss >> tmp >> kin.yb.second;
  // 		    kin.yb.first = - kin.yb.second;
  // 		  }

  // 		// Invariant-mass interval
  // 		if (ql["name"].as<std::string>() == "M(P=3_4)")
  // 		  {
  // 		    std::string tmp;
  // 		    std::stringstream ss(ql["value"].as<std::string>());
  // 		    ss >> kin.Qb.first >> tmp >> kin.Qb.second;
  // 		  }

  // 		// Center-of-mass energy
  // 		if (ql["name"].as<std::string>() == "SQRT(S)")
  // 		  kin.Vs = ql["value"].as<double>();
  // 	      }

  // 	  // Transverse momentum bin bounds
  // 	  std::vector<double> qTv;
  // 	  for (auto const& iv : df["independent_variables"])
  // 	    for (auto const& vl : iv["values"])
  // 	      {
  // 		if(std::find(kin.qTv.begin(), kin.qTv.end(), vl["low"].as<double>()) == kin.qTv.end())
  // 		  kin.qTv.push_back(std::max(vl["low"].as<double>(), 1e-5));
  // 		if(std::find(kin.qTv.begin(), kin.qTv.end(), vl["high"].as<double>()) == kin.qTv.end())
  // 		  kin.qTv.push_back(vl["high"].as<double>());
  // 	      }

  // 	  // Push "Kinematics" object into the container
  // 	  KinVect.push_back(kin);
  // 	}
  //   return KinVect;
  // }




  }
}
