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
  /**
   * @brief The "ConvolutionTable" constructor.
   * @param infile: the interpolation table in YAML format
   */
    ConvolutionTable(std::string const& infile);

  /**
   * @brief This functions convolute the input convolution table with
   * a user-given non-perturbative function.
   * @param fNP: the non-perturbative input function
   * @return a map that associates each value of qT to a prediction.
   */
    std::map<double,double> Convolute(std::function<double(double const&, double const&, double const&)> const& fNP) const;

  private:
    double                                                         _Vs;   //!< Center of mass energy
    std::vector<double>                                            _qTv;  //!< Vector of qT
    std::vector<double>                                            _z;    //!< Unscaled Ogata coordinate
    std::vector<double>                                            _Qg;   //!< Grid in Q
    std::vector<double>                                            _xig;  //!< Grid in xi
    std::map<double,std::vector<std::vector<std::vector<double>>>> _W;    //!< The weights
  };
}
