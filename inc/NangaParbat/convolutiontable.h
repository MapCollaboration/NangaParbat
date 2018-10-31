//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>

namespace NangaParbat
{
  class ConvolutionTable
  {
  public:
    ConvolutionTable(std::string const& infile);

    std::map<double,double> Convolute(std::function<double(double const&, double const&, double const&)> const& fNP) const;

  private:
    double              _Vs;
    std::vector<double> _qTv;
    std::vector<double> _z1;
    std::vector<double> _Qg; 
    std::vector<double> _xig;
    std::map<double,std::vector<std::vector<std::vector<double>>>> _W;
  };
}
