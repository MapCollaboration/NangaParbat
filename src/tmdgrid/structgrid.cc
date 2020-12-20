//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
//

#include "NangaParbat/structgrid.h"

namespace NangaParbat
{
  //_________________________________________________________________________________
  StructGrid::StructGrid(YAML::Node const& info, YAML::Node const& grid):
    _info(info),
    _xg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double>
  {
    grid["xg"].as<std::vector<double>>(), 3
  })),
    _zg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double>
  {
    grid["zg"].as<std::vector<double>>(), 3
  })),
  _qToQg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {grid["qToQg"].as<std::vector<double>>(), 3})),
  _Qg(std::unique_ptr<apfel::QGrid<double>>(new apfel::QGrid<double> {grid["Qg"].as<std::vector<double>>(), 3})),
  _stfunc(grid["StructureFunction"].as<std::vector<std::vector<std::vector<std::vector<double>>>>>())
  {
  }

  //_________________________________________________________________________________
  double StructGrid::Evaluate(double const& x, double const& z, double const& qT, double const& Q) const
  {
    // If qT/Q < the first point of the grid, put qT/Q  equal to it.
    // Do not compute below the first point of the grid.
    const double qToQ = std::max(qT / Q, _qToQg->GetQGrid().front());


    // Get summation bounds
    const std::tuple<int, int, int> xbounds    = _xg->SumBounds(x);
    const std::tuple<int, int, int> zbounds    = _zg->SumBounds(z);
    const std::tuple<int, int, int> qToQbounds = _qToQg->SumBounds(qToQ);
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

    // z grid
    const int inz = std::get<1>(zbounds);
    const int nz  = std::get<2>(zbounds) - inz;
    std::vector<double> Iz(nz);
    for (int iz = 0; iz < nz; iz++)
      Iz[iz] = _zg->Interpolant(std::get<0>(zbounds), inz + iz, z);

    // qT grid
    const int inqT = std::get<1>(qToQbounds);
    const int nqT  = std::get<2>(qToQbounds) - inqT;
    std::vector<double> IqT(nqT);
    for (int iqT = 0; iqT < nqT; iqT++)
      IqT[iqT] = _qToQg->Interpolant(std::get<0>(qToQbounds), inqT + iqT, qToQ);

    // Initialise output to zero
    double result = 0;

    // Do the interpolation
    for (int iQ = 0; iQ < nQ; iQ++)
      for (int ix = 0; ix < nx; ix++)
        for (int iz = 0; iz < nz; iz++)
          for (int iqT = 0; iqT < nqT; iqT++)
            result += IQ[iQ] * Ix[ix] * Iz[iz] * IqT[iqT] * _stfunc[inQ + iQ][inx + ix][inz + iz][inqT + iqT];

    return result;
  }
}
