//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/utilities.h"

#include <iostream>
#include <cmath> 
#include <apfel/messages.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  double bstar(double const& b, double const& bmax)
  {
    return b / sqrt( 1 + pow(b / bmax, 2) );
  }

  //_________________________________________________________________________________
  std::vector<double> GenerateQGrid(int const& n, double const& min, double const& max)
  {
    std::vector<double> grid(n+1);
    const double step = ( max - min ) / ( n - 1 );
    for (int i = 0; i < n + 1; i++)
      grid[i] = min + i * step;
    return grid;
  }

  //_________________________________________________________________________________
  void RetrieveKinematics(YAML::Node const& df, double& Vs, double& Qmin, double& Qmax, double& ymin, double& ymax, std::vector<double>& qTv)
  {
    // Fiducial region
    for (auto const& dv : df["dependent_variables"])
      for (auto const& ql : dv["qualifiers"])
	{
	  // Rapidity interval
	  if (ql["name"].as<std::string>() == "ABS(ETARAP)")
	    {
	      std::string tmp;
	      std::stringstream ss(ql["value"].as<std::string>());
	      ss >> tmp >> ymax;
	      ymin = - ymax;
	    }

	  // Invariant-mass interval
	  if (ql["name"].as<std::string>() == "M(P=3_4)")
	    {
	      std::string tmp;
	      std::stringstream ss(ql["value"].as<std::string>());
	      ss >> Qmin >> tmp >> Qmax;
	    }

	  // Center-of-mass energy
	  if (ql["name"].as<std::string>() == "SQRT(S)")
	    Vs = ql["value"].as<double>();
	}

    // Stop the program if some of the required information is not
    // found.
    if (Vs < - 100 || ymin < - 100 || ymax < - 100 || Qmin < - 100 || Qmax < - 100)
      {
	std::cout << apfel::error("RetrieveKinematics", "Kinematics not fully found.");
	exit(-1);
      }

    // Transverse momentum bin bounds
    for (auto const& iv : df["independent_variables"])
      for (auto const& vl : iv["values"])
	{
	  if(std::find(qTv.begin(), qTv.end(), vl["low"].as<double>()) == qTv.end())
	    qTv.push_back(std::max(vl["low"].as<double>(), 1e-5));
	  if(std::find(qTv.begin(), qTv.end(), vl["high"].as<double>()) == qTv.end())
	    qTv.push_back(vl["high"].as<double>());
	}

    // Stop the program if the qT vector has less than two entries.
    if (qTv.size() < 2)
      {
	std::cout << apfel::error("RetrieveKinematics", "qT-bound vector has too few entries.");
	exit(-1);
      }
  }
}
