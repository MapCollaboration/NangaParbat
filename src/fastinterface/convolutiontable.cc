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

    // Process index
    _proc = table["process"].as<int>();

    // Observable index
    _obs = table["observable"].as<int>();

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

    // Read the phase-space reduction factors...
    for (auto const& qT : _qTv)
      _PSRed.insert({qT, table["PS_reduction_factor"][qT].as<std::vector<std::vector<double>>>()});

    // ... and their derivatives.
    for (auto const& qT : _qTv)
      _dPSRed.insert({qT, table["PS_reduction_factor_derivative"][qT].as<std::vector<std::vector<double>>>()});

    // Read weights
    for (auto const& qT : _qTv)
      _W.insert({qT, table["weights"][qT].as<std::vector<std::vector<std::vector<double>>>>()});
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
    for (int iqT = 0; iqT < _qTv.size(); iqT++)
      {
	double cs = 0;
	for (int tau = 0; tau < (int) _Qg.size(); tau++)
	  {
	    const double Q    = _Qg[tau];
	    const double zeta = Q * Q;
	    const double Vtau = Q / _Vs;
	    for (int alpha = 0; alpha < (int) _xig.size(); alpha++)
	      {
		const double xi = _xig[alpha];
		for (int n = 0; n < (int) _z.size(); n++)
		  {
		    const double b = _z[n] / _qTv[iqT];
		    const double f1 = fNP1(Vtau * xi, b, zeta);
		    const double f2 = fNP2(Vtau / xi, b, zeta);
		    cs += _W.at(_qTv[iqT])[n][tau][alpha] * f1 * f2;
		  }
	      }
	  }
	pred.insert({_qTv[iqT], cs});
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
	vpred[i] = ( pred.at(_qTv[i+1]) - pred.at(_qTv[i]) ) / ( _qTv[i+1] - _qTv[i] );
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

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const
  {
    // Drell-Yan
    if (_proc == 0)
      {
	const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
	return GetPredictions(fNP1, fNP1);
      }
    // SIDIS
    else if (_proc == 1)
      {
	const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
	const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
	return GetPredictions(fNP1, fNP2);
      }
    // e+e- annihilation
    if (_proc == 0)
      {
	const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
	return GetPredictions(fNP2, fNP2);
      }
    // Generic
    else
      {
	const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
	const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
	return GetPredictions(fNP1, fNP2);
      }
  }
}
