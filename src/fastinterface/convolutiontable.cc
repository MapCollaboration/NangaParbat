//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/convolutiontable.h"

#include <iostream>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ConvolutionTable::ConvolutionTable(YAML::Node const& table)
  {
    // Name
    _name = table["name"].as<std::string>();

    // Process
    _proc = table["process"].as<int>();

    // C.M.E.
    _Vs = table["CME"].as<double>();

    // qT bin bounds
    _IntqT = table["qTintegrated"].as<bool>();

    // qT bin bounds
    _qTv = table["qT_bounds"].as<std::vector<double>>();

    // Ogata unscaled coordinates
    _z = table["Ogata_coordinates"].as<std::vector<double>>();

    // Q grid
    _Qg = table["Qgrid"].as<std::vector<double>>();

    // xi grid
    _xig = table["xigrid"].as<std::vector<double>>();

    for (auto const& qT : _qTv)
      _W.insert({qT, table[qT].as<std::vector<std::vector<std::vector<double>>>>()});
  }

  //_________________________________________________________________________________
  ConvolutionTable::ConvolutionTable(std::string const& infile):
    ConvolutionTable(YAML::LoadFile(infile))
  {
  }

  //_________________________________________________________________________________
  std::map<double,double> ConvolutionTable::Convolute(std::function<double(double const&, double const&, double const&)> const& fNP1,
						      std::function<double(double const&, double const&, double const&)> const& fNP2) const
  {
    std::map<double,double> pred;
    for (auto const& qT : _qTv)
      {
	double cs = 0;
	for (int n = 0; n < (int) _z.size(); n++)
	  {
	    const double b = _z[n] / qT;
	    for (int tau = 0; tau < (int) _Qg.size(); tau++)
	      {
		const double Q    = _Qg[tau];
		const double zeta = Q * Q;
		const double Vtau = Q / _Vs;
		for (int alpha = 0; alpha < (int) _xig.size(); alpha++)
		  {
		    const double xi = _xig[tau];
		    cs += _W.at(qT)[n][tau][alpha] * fNP1(Vtau * xi, b, zeta) * fNP2(Vtau / xi, b, zeta);
		  }
	      }
	  }
	pred.insert({qT, cs});
      }
    return pred;
  }

  //_________________________________________________________________________________
  std::map<double,double> ConvolutionTable::Convolute(std::function<double(double const&, double const&, double const&)> const& fNP) const
  {
    return Convolute(fNP, fNP);
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
						       std::function<double(double const&, double const&, double const&)> const& fNP2) const
  {
    std::map<double,double> pred = Convolute(fNP1, fNP2);
    const int npred = pred.size() - (_IntqT ? 1 : 0);
    std::vector<double> vpred(npred);
    if (_IntqT)
      for (int i = 0; i < npred; i++)
	vpred[i] = pred.at(_qTv[i+1]) - pred.at(_qTv[i]);
    else
      for (int i = 0; i < npred; i++)
	vpred[i] = pred.at(_qTv[i]);

    return vpred;
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP) const
  {
    return GetPredictions(fNP, fNP);
  }
}
