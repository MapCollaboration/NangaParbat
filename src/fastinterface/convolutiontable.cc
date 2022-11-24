//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/convolutiontable.h"

#include <cmath>
#include <iostream>
#include <algorithm>

namespace NangaParbat
{
  //_________________________________________________________________________________
  ConvolutionTable::ConvolutionTable():
    _name("No name"),
    _proc(-1),
    _Vs(-1),
    _IntqT(false),
    _qTv({}),
  _qTmap({{}}),
  _qTfact({}),
  _prefact(1),
  _prefact2(1),
  _zOgata({}),
  _Qg({}),
  _xig({}),
  _xbg({}),
  _zg({}),
  _cutParam({}),
  _acc(1e-7),
  _cuts({}),
  _cutmask({}),
  _Hbeam("PR")
  {
  }

  //_________________________________________________________________________________
  //ConvolutionTable::ConvolutionTable(YAML::Node const& table, double const& qToQmax, std::vector<std::shared_ptr<Cut>> const& cuts, double const& acc):
  ConvolutionTable::ConvolutionTable(YAML::Node const& table, std::vector<double> const& cutParam, std::vector<std::shared_ptr<Cut>> const& cuts, double const& acc):
    _name(table["name"].as<std::string>()),
    _proc(table["process"].as<int>()),
    _Vs(table["CME"].as<double>()),
    _IntqT(table["qTintegrated"].as<bool>()),
    _qTv(table["qT_bounds"].as<std::vector<double>>()),
    _qTmap(table["qT_map"].as<std::vector<std::vector<double>>>()),
    _qTfact(table["bin_factors"].as<std::vector<double>>()),
    _prefact(table["prefactor"].as<double>()),
    _prefact2(table["prefactor2"] ? table["prefactor2"].as<double>() : 1),
    _zOgata(table["Ogata_coordinates"].as<std::vector<double>>()),
    _Qg(table["Qgrid"].as<std::vector<double>>()),
    _cutParam(cutParam),
    _acc(acc),
    _cuts(cuts),
    _Hbeam(table["hadron_beam"].as<std::string>())
  {
    // Compute total cut mask as a product of single masks
    _cutmask.resize(_qTfact.size(), true);
    for (auto const& c : cuts)
      _cutmask *= c->GetMask();
    switch (_proc)
      {
      case DataHandler::Process::DY:
        // Read grid in xi = exp(y)
        _xig = table["xigrid"].as<std::vector<double>>();

        // Read the phase-space reduction factors...
        for (auto const& qT : _qTv)
          _PSRed.insert({qT, table["PS_reduction_factor"][qT].as<std::vector<std::vector<double>>>()});
        // ... and their derivatives.
        for (auto const& qT : _qTv)
          _dPSRed.insert({qT, table["PS_reduction_factor_derivative"][qT].as<std::vector<std::vector<double>>>()});

        // Read weights
        for (auto const& qT : _qTv)
          _WDY.insert({qT, table["weights"][qT].as<std::vector<std::vector<std::vector<double>>>>()});
        break;
      case DataHandler::Process::SIDIS:
        _xbg = table["xbgrid"].as<std::vector<double>>();
        _zg  = table["zgrid"].as<std::vector<double>>();

        // Read weights
        for (auto const& qT : _qTv)
          _WSIDIS.insert({qT, table["weights"][qT].as<std::vector<std::vector<std::vector<std::vector<double>>>>>()});
        break;

      default:
        throw std::runtime_error("[ConvolutionTable::ConvolutionTable]: Unsupported process.");
      }
  }

  //_________________________________________________________________________________
  //ConvolutionTable::ConvolutionTable(std::string const& infile, double const& qToQmax, std::vector<std::shared_ptr<Cut>> const& cuts, double const& acc):
  //ConvolutionTable(YAML::LoadFile(infile), qToQmax, cuts, acc)
  ConvolutionTable::ConvolutionTable(std::string const& infile, std::vector<double> const& cutParam, std::vector<std::shared_ptr<Cut>> const& cuts, double const& acc):
    ConvolutionTable(YAML::LoadFile(infile), cutParam, cuts, acc)
  {
  }

  //_________________________________________________________________________________
  std::map<double, double> ConvolutionTable::ConvoluteDY(std::function<double(double const&, double const&, double const&)> const& fNP1, std::function<double(double const&, double const&, double const&)> const& fNP2) const
  {

    double DYqToQmax = 0;

    // Compute cut qT / Q as same as MAP22
    if (_Hbeam == "PR")
       DYqToQmax = std::min(_cutParam[0], _cutParam[1]);
    // Compute cut qT / Q as same as MAP22Pion
    if (_Hbeam == "PI")
       DYqToQmax =_cutParam[0] + _cutParam[1] /  _Qg.front();

    // Compute predictions
    std::map<double, double> pred;
    for (int iqT = 0; iqT < (int) _qTv.size(); iqT++)
      {
        if (_qTv[iqT] / _Qg.front() > DYqToQmax)   //_qToQmax
          {
            pred.insert({_qTv[iqT],  0});
            pred.insert({-_qTv[iqT], 0});
            continue;
          }
        const auto wgt  = _WDY.at(_qTv[iqT]);
        const auto psf  = _PSRed.at(_qTv[iqT]);
        const auto dpsf = _dPSRed.at(_qTv[iqT]);
        double cs  = 0;
        double dcs = 0;
        for (int n = 0; n < (int) _zOgata.size(); n++)
          {
            double csn  = 0;
            double dcsn = 0;
            const double b = _zOgata[n] / _qTv[iqT];
            for (int tau = 0; tau < (int) _Qg.size(); tau++)
              {
                const double Q    = _Qg[tau];
                const double zeta = Q * Q;
                const double Vtau = Q / _Vs;
                for (int alpha = 0; alpha < (int) _xig.size(); alpha++)
                  {
                    const double x1 = Vtau * _xig[alpha];
                    const double x2 = pow(Vtau, 2) / x1;
                    const double wf = wgt[n][tau][alpha] * fNP1(x1, b, zeta) * fNP2(x2, b, zeta);
                    csn  += wf * psf[tau][alpha];
                    dcsn += wf * dpsf[tau][alpha];
                  }
              }
            cs  += csn;
            dcs += dcsn;
            // Break the loop if the accuracy is satisfied (assuming
            // convergence).
            if (std::abs(csn/cs) < _acc)
              break;
          }
        // Positive values of qT correspond to the non-derivative part
        // while the negative ones to the derivative part of the
        // phase-space reduction factor.
        pred.insert({_qTv[iqT],  cs});
        pred.insert({-_qTv[iqT], dcs});
      }
    return pred;
  }

  //_________________________________________________________________________________
  std::map<double, double> ConvolutionTable::ConvoluteSIDIS(std::function<double(double const&, double const&, double const&)> const& fNP,
                                                            std::function<double(double const&, double const&, double const&)> const& DNP) const
  {
    // Compute cut qT / Q as in PV17
    double SIDISqToQmax = std::min(std::min(_cutParam[0] / _zg.front(), _cutParam[1]) + _cutParam[2] / _Qg.front() / _zg.front(), 1.0);
    // double SIDISqToQmax = std::min(_cutParam[0] / _zg.front(), _cutParam[1]) + _cutParam[2] / _Qg.front() / _zg.front();

    // Compute predictions
    std::map<double, double> pred;
    for (int iqT = 0; iqT < (int) _qTv.size(); iqT++)
      {
        if (_qTv[iqT] / _Qg.front() / _zg.front() > SIDISqToQmax)
          {
            pred.insert({_qTv[iqT],  0});
            continue;
          }
        const auto wgt = _WSIDIS.at(_qTv[iqT]);
        double cs  = 0;
        for (int n = 0; n < (int) _zOgata.size(); n++)
          {
            double csn  = 0;
            for (int tau = 0; tau < (int) _Qg.size(); tau++)
              {
                const double Q    = _Qg[tau];
                const double zeta = Q * Q;
                for (int alpha = 0; alpha < (int) _xbg.size(); alpha++)
                  for (int beta = 0; beta < (int) _zg.size(); beta++)
                    {
                      const double b = _zg[beta] * _zOgata[n] / _qTv[iqT];
                      csn += wgt[n][tau][alpha][beta] * fNP(_xbg[alpha], b, zeta) * DNP(_zg[beta], b, zeta);
                    }
              }
            cs += csn;
            // Break the loop if the accuracy is satisfied (assuming
            // convergence).
            if (std::abs(csn/cs) < _acc)
              break;
          }
        pred.insert({_qTv[iqT], cs});
      }
    return pred;
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                                       std::function<double(double const&, double const&, double const&)> const& fNP2) const
  {
    const int npred = _qTmap.size();
    std::vector<double> vpred(npred);
    std::map<double, double> pred;

    switch (_proc)
      {
      // Drell-Yan: two PDFs
      case DataHandler::Process::DY:
        pred = ConvoluteDY(fNP1, fNP2);
        if (_IntqT)
          for (int i = 0; i < npred; i++)
            {
              vpred[i]  = ( pred.at(_qTmap[i][1]) - pred.at(_qTmap[i][0]) ) / ( _qTmap[i][1] - _qTmap[i][0] );
              vpred[i] -= ( pred.at(-_qTmap[i][1]) + pred.at(-_qTmap[i][0]) ) / 2;
              vpred[i] *= _prefact * _qTfact[i];
            }
        else
          for (int i = 0; i < npred; i++)
            vpred[i] = _prefact * _qTfact[i] * pred.at(_qTmap[i][1]);
        break;

      // SIDIS: one PDF and one FF
      case DataHandler::Process::SIDIS:
        pred = ConvoluteSIDIS(fNP1, fNP2);
        if (_IntqT)
          for (int i = 0; i < npred; i++)
            vpred[i] = _prefact * _prefact2 * _qTfact[i] * (pred.at(_qTmap[i][1]) - pred.at(_qTmap[i][0])) / ( _qTmap[i][1] - _qTmap[i][0]);
        else
          for (int i = 0; i < npred; i++)
            vpred[i] = _prefact * _prefact2 * _qTfact[i] * pred.at(_qTmap[i][1]);
        break;

      // e+e- annihilation into two hadrons: two FFs (Not present
      // yet)
      case DataHandler::Process::DIA:
        break;
      }
    return vpred;
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const
  {
    std::function<double(double const& x, double const& b, double const& zeta)> fNP1;
    std::function<double(double const& x, double const& b, double const& zeta)> fNP2;
    switch (_proc)
      {
      // Drell-Yan: two PDFs
      case DataHandler::Process::DY:
        fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        break;

      // SIDIS: one PDF and one FF
      case DataHandler::Process::SIDIS:
        fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 2); };
        break;

      // e+e- annihilation into two hadrons: two FFs (Not present
      // yet)
      case DataHandler::Process::DIA:
        fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 2); };
        fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 3); };
        break;

      default:
        fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 2); };
        break;
      }

    return GetPredictions(fNP1, fNP2);
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP,
                                                       std::function<double(double const&, double const&, double const&, int const&)> const& dNP) const
  {
    std::vector<double> p1;
    std::vector<double> p2;
    switch (_proc)
      {
      // Drell-Yan: two PDFs
      case DataHandler::Process::DY:
        p1 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 1); });
        p2 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 0); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); });
        break;

      // SIDIS: one PDF and one FF
      case DataHandler::Process::SIDIS:
        p1 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 2); });
        p2 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 0); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 2); });
        break;

      // e+e- annihilation into two hadrons: two FFs (Not present
      // yet)
      case DataHandler::Process::DIA:
        p1 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 2); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 3); });
        p2 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 2); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 3); });
        break;

      default:
        p1 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 2); });
        p2 = GetPredictions([=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 0); }, [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 2); });
        break;
      }
    std::transform(p1.begin(), p1.end(), p2.begin(), p1.begin(), std::plus<double>());
    return p1;
  }
}
