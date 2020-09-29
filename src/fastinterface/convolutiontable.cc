//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/convolutiontable.h"

#include <cmath>
#include <iostream>
#include <algorithm>

#include <root/TCanvas.h>
#include <root/TStyle.h>
#include <root/TH2.h>
#include <root/TRandom.h>

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
  _z({}),
  _Qg({}),
  _xig({}),
  _qToQmax(1000),
  _acc(1e-7),
  _cuts({}),
  _cutmask({})
  {
  }

  //_________________________________________________________________________________
  ConvolutionTable::ConvolutionTable(YAML::Node const& table, double const& qToQmax, std::vector<std::shared_ptr<Cut>> const& cuts, double const& acc):
    _name(table["name"].as<std::string>()),
    _proc(table["process"].as<int>()),
    _Vs(table["CME"].as<double>()),
    _IntqT(table["qTintegrated"].as<bool>()),
    _qTv(table["qT_bounds"].as<std::vector<double>>()),
    _qTmap(table["qT_map"].as<std::vector<std::vector<double>>>()),
    _qTfact(table["bin_factors"].as<std::vector<double>>()),
    _prefact(table["prefactor"].as<double>()),
    _z(table["Ogata_coordinates"].as<std::vector<double>>()),
    _Qg(table["Qgrid"].as<std::vector<double>>()),
    _xig(table["xigrid"].as<std::vector<double>>()),
    _qToQmax(qToQmax),
    _acc(acc),
    _cuts(cuts)
  {
    // Compute total cut mask as a product of single masks
    _cutmask.resize(_qTfact.size(), true);
    for (auto const& c : cuts)
      _cutmask *= c->GetMask();

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
  ConvolutionTable::ConvolutionTable(std::string const& infile, double const& qToQmax, std::vector<std::shared_ptr<Cut>> const& cuts, double const& acc):
    ConvolutionTable(YAML::LoadFile(infile), qToQmax, cuts, acc)
  {
  }

  //_________________________________________________________________________________
  std::map<double, double> ConvolutionTable::Convolute(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                                       std::function<double(double const&, double const&, double const&)> const& fNP2) const
  {
    // Compute predictions
    std::map<double, double> pred;
    for (int iqT = 0; iqT < (int) _qTv.size(); iqT++)
      {
        if (_qTv[iqT] / _Qg.front() > _qToQmax)
          {
            pred.insert({_qTv[iqT],  0});
            pred.insert({-_qTv[iqT], 0});
            continue;
          }
        const auto wgt  = _W.at(_qTv[iqT]);
        const auto psf  = _PSRed.at(_qTv[iqT]);
        const auto dpsf = _dPSRed.at(_qTv[iqT]);
        double cs  = 0;
        double dcs = 0;
        for (int n = 0; n < (int) _z.size(); n++)
          {
            double csn  = 0;
            double dcsn = 0;
            const double b = _z[n] / _qTv[iqT];
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
  std::map<double, double> ConvolutionTable::Convolute(std::function<double(double const&, double const&, double const&)> const& fNP) const
  {
    return Convolute(fNP, fNP);
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&)> const& fNP1,
                                                       std::function<double(double const&, double const&, double const&)> const& fNP2) const
  {
    std::map<double,double> pred = Convolute(fNP1, fNP2);
    const int npred = _qTmap.size();
    std::vector<double> vpred(npred);
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
    // Drell-Yan (two PDFs)
    if (_proc == 0)
      {
        const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        return GetPredictions(fNP1, fNP1);
      }
    // SIDIS (one PDF and one FF)
    else if (_proc == 1)
      {
        const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        return GetPredictions(fNP1, fNP2);
      }
    // e+e- annihilation (two FFs)
    else if (_proc == 2)
      {
        const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        return GetPredictions(fNP2, fNP2);
      }
    // Generic (one PDF and one FF)
    else
      {
        const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        return GetPredictions(fNP1, fNP2);
      }
  }

  //_________________________________________________________________________________
  std::vector<double> ConvolutionTable::GetPredictions(std::function<double(double const&, double const&, double const&, int const&)> const& fNP,
                                                       std::function<double(double const&, double const&, double const&, int const&)> const& dNP) const
  {

    // Drell-Yan (two PDFs)
    if (_proc == 0)
      {
        const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        const auto dNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 0); };
        std::vector<double> p1 = GetPredictions(fNP1, dNP1);
        const std::vector<double> p2 = GetPredictions(dNP1, fNP1);
        std::transform(p1.begin(), p1.end(), p2.begin(), p1.begin(), std::plus<double>());
        return p1;
      }
    // SIDIS (one PDF and one FF)
    else if (_proc == 1)
      {
        const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        const auto dNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 0); };
        const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        const auto dNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 1); };
        std::vector<double> p1 = GetPredictions(fNP1, dNP2);
        const std::vector<double> p2 = GetPredictions(dNP1, fNP2);
        std::transform(p1.begin(), p1.end(), p2.begin(), p1.begin(), std::plus<double>());
        return p1;
      }
    // e+e- annihilation (two FFs)
    else if (_proc == 2)
      {
        const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        const auto dNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return 2 * dNP(x, b, zeta, 1); }; // Factor 2 for due to the derivative
        std::vector<double> p1 = GetPredictions(fNP2, dNP2);
        const std::vector<double> p2 = GetPredictions(dNP2, fNP2);
        std::transform(p1.begin(), p1.end(), p2.begin(), p1.begin(), std::plus<double>());
        return p1;
      }
    // Generic (one PDF and one FF)
    else
      {
        const auto fNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 0); };
        const auto dNP1 = [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 0); };
        const auto fNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return fNP(x, b, zeta, 1); };
        const auto dNP2 = [=] (double const& x, double const& b, double const& zeta) -> double{ return dNP(x, b, zeta, 1); };
        std::vector<double> p1 = GetPredictions(fNP1, dNP1);
        const std::vector<double> p2 = GetPredictions(fNP2, dNP2);
        std::transform(p1.begin(), p1.end(), p2.begin(), p1.begin(), std::plus<double>());
        return p1;
      }
  }

  //_________________________________________________________________________________
  void ConvolutionTable::PlotWeights() const
  {
    TCanvas *c2 = new TCanvas("c2", "c2", 600, 400);
    const int nx = 50;
    const double xmin = 1e-4;//0.95 * _Qg[0] * _xig[0] / _Vs ;
    const double xmax = 1;//_Qg.back() / _xig[0] / _Vs ;
    std::cout << xmin << "  " << xmax << std::endl;
    const double xstep = exp( std::abs( log( xmax / xmin ) ) / ( nx - 1 ) );
    double xbins[nx+1];
    xbins[0] = xmin;
    for (int i = 1; i <= nx; i++)
      xbins[i] = xbins[i-1] * xstep;
    TH2F *hlego2 = new TH2F("statistics", _name.c_str(), 20, 0, 70 / _Qg[0], nx, xbins);
    hlego2->GetXaxis()->SetTitle("b_{T}");
    hlego2->GetYaxis()->SetTitle("x_{1,2}");
    c2->SetLogy();
    for (int iqT = 0; iqT < (int) _qTv.size(); iqT++)
      for (int tau = 0; tau < (int) _Qg.size(); tau++)
        for (int alpha = 0; alpha < (int) _xig.size(); alpha++)
          {
            const double x1 = _Qg[tau] / _Vs * _xig[alpha];
            const double x2 = _Qg[tau] / _Vs / _xig[alpha];
            for (int n = 0; n < (int) _z.size(); n++)
              {
                hlego2->Fill(_z[n] / _qTv[iqT], x1, std::abs(_W.at(_qTv[iqT])[n][tau][alpha]));
                hlego2->Fill(_z[n] / _qTv[iqT], x2, std::abs(_W.at(_qTv[iqT])[n][tau][alpha]));
              }
          }
    gStyle->SetPalette(kBird);
    hlego2->Draw("SURF7");
    //gPad->SetTheta(60); // default is 30
    gPad->SetPhi(60); // default is 30
    gPad->Update();
    c2->SaveAs((_name + "_3D" + ".pdf").c_str());
    delete hlego2;
    delete c2;
  }

  //_________________________________________________________________________________
  void ConvolutionTable::NumericalAccuracy(std::function<double(double const&, double const&, double const&, int const&)> const& fNP) const
  {
    // Compute accuracies
    for (int iqT = 0; iqT < (int) _qTv.size(); iqT++)
      {
        // Get weights
        const auto wgt = _W.at(_qTv[iqT]);

        // Get phase-space reduction factors
        const auto psf = _PSRed.at(_qTv[iqT]);

        // Perform the convolution
        double cs  = 0;
        double csn = 0;
        for (int n = 0; n < (int) _z.size(); n++)
          {
            csn = 0;
            const double b = _z[n] / _qTv[iqT];
            for (int tau = 0; tau < (int) _Qg.size(); tau++)
              {
                const double Q    = _Qg[tau];
                const double zeta = Q * Q;
                const double Vtau = Q / _Vs;
                for (int alpha = 0; alpha < (int) _xig.size(); alpha++)
                  {
                    const double x1 = Vtau * _xig[alpha];
                    const double x2 = pow(Vtau, 2) / x1;
                    csn += psf[tau][alpha] * wgt[n][tau][alpha] * fNP(x1, b, zeta, 0) * fNP(x2, b, zeta, 1);
                  }
              }
            cs += csn;
          }
        if (std::abs(cs) > 1e-10)
          std::cout << std::scientific <<"qT = " << _qTv[iqT] << " GeV, relative accuracy = " << csn / cs << std::endl;
      }
  }
}
