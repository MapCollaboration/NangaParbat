//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/tmdgrid.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  TMDGrid::TMDGrid(YAML::Node const& grid):
    _xg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double>
  {
    grid["xg"].as<std::vector<double>>(), 3
  })),
  _qToQg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {grid["qToQg"].as<std::vector<double>>(), 3})),
  _Qg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {grid["Qg"].as<std::vector<double>>(), 3})),
  _tmds(grid["TMDs"].as<std::map<int, std::vector<std::vector<std::vector<double>>>>>())
  {
  }

  //_________________________________________________________________________________
  std::map<int, double> TMDGrid::Evaluate(double const& x, double const& qT, double const& Q) const
  {
    // Get summation bounds
    const std::tuple<int, int, int> xbounds    = _xg->SumBounds(x);
    const std::tuple<int, int, int> qToQbounds = _qToQg->SumBounds(qT/Q);
    const std::tuple<int, int, int> Qbounds    = _Qg->SumBounds(Q);

    // Compute interpolating functions singularly to minimise the
    // number of calls due to the the nesting of the interpolation.
    // Q grid
    const int inQ = std::get<1>(Qbounds);
    const int nQ  = std::get<2>(Qbounds) - inQ;
    std::vector<double> IQ(nQ);
    for (int iQ = 0; iQ < nQ; iQ++)
      IQ[iQ] = _Qg->Interpolant(std::get<0>(Qbounds), inQ + iQ, Q);

    // x grid
    const int inx = std::get<1>(xbounds);
    const int nx  = std::get<2>(xbounds) - inx;
    std::vector<double> Ix(nx);
    for (int ix = 0; ix < nx; ix++)
      Ix[ix] = _xg->Interpolant(std::get<0>(xbounds), inx + ix, x);

    const int inqT = std::get<1>(qToQbounds);
    const int nqT  = std::get<2>(qToQbounds) - inqT;
    std::vector<double> IqT(nqT);
    for (int iqT = 0; iqT < nqT; iqT++)
      IqT[iqT] = _qToQg->Interpolant(std::get<0>(qToQbounds), inqT + iqT, qT/Q);

    // Initialise output map to zero
    std::map<int, double> result;
    for (auto const& tmd : _tmds)
      result.insert({tmd.first, 0});

    // Do the interpolation
    for (auto const& tmd : _tmds)
      for (int iQ = 0; iQ < nQ; iQ++)
        for (int ix = 0; ix < nx; ix++)
          for (int iqT = 0; iqT < nqT; iqT++)
            result[tmd.first] += IQ[iQ] * Ix[ix] * IqT[iqT] * tmd.second[inQ + iQ][inx + ix][inqT + iqT];

    return result;
  }
}
