//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datahandler.h"
#include "NangaParbat/utilities.h"

#include <iostream>
#include <math.h>
#include <numeric>
#include <algorithm>

namespace NangaParbat
{
  //_________________________________________________________________________________
  DataHandler::Kinematics::Kinematics():
    ndata(0),
    Vs(0),
    qTv({}),
      qTmap({}),
      qTfact({}),
      var1b({0, 0}),
      var2b({0, 0}),
      IntqT(false),
      Intv1(false),
      Intv2(false),
      PSRed(false),
      pTMin(0),
      etaRange({-10, 10})
  {
  }

  //_________________________________________________________________________________
  bool DataHandler::Kinematics::empty() const
  {
    if (ndata == 0 || Vs == 0 || qTv.empty() || qTmap.empty() || qTfact.empty() ||
        ( var1b.first == 0 && var1b.second == 0 && var1b.first == 0 && var1b.second == 0 ))
      return true;
    else
      return false;
  }

  //_________________________________________________________________________________
  DataHandler::DataHandler(std::string const& name, YAML::Node const& datafile, int const& fluctuation, int const& seed):
    _name(name),
    _proc(UnknownProcess),
    _targetiso(1),
    _prefact(1),
    _kin(DataHandler::Kinematics{}),
    _labels({})
  {
    // Retrieve kinematics
    for (auto const& dv : datafile["dependent_variables"])
      {
        // Get labels
        _labels = dv["header"].as<std::map<std::string, std::string>>();

        // Run over the qualifiers and make sure that all necessary
        // parameters are found.
        for (auto const& ql : dv["qualifiers"])
          {
            // Process
            if (ql["name"].as<std::string>() == "process")
              {
                if (ql["value"].as<std::string>() == "DY")
                  _proc = DY;
                else if (ql["value"].as<std::string>() == "SIDIS")
                  _proc = SIDIS;
                else
                  throw std::runtime_error("[DataHandler::DataHandler]: Unknown process.");
              }

            // Isoscalarity
            if (ql["name"].as<std::string>() == "target_isoscalarity")
              _targetiso = ql["value"].as<double>();

            // Possible prefactor
            if (ql["name"].as<std::string>() == "prefactor")
              _prefact = ql["value"].as<double>();

            // Center of mass energy
            if (ql["name"].as<std::string>() == "Vs")
              _kin.Vs = ql["value"].as<double>();

            // Invariant-mass interval
            if (ql["name"].as<std::string>() == "Q")
              {
                _kin.var1b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
                _kin.Intv1 = ql["integrate"].as<bool>();
              }

            // Rapidity interval
            if (ql["name"].as<std::string>() == "y")
              {
                _kin.var2b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
                _kin.Intv2 = ql["integrate"].as<bool>();
              }

            // Lepton cuts
            if (ql["name"].as<std::string>() == "PS_reduction")
              {
                _kin.PSRed    = true;
                _kin.pTMin    = ql["pTmin"].as<double>();
                _kin.etaRange = std::make_pair(ql["etamin"].as<double>(), ql["etamax"].as<double>());
              }
          }

        // Run over the data-point values and uncertainties
        for (auto const& vl : dv["values"])
          {
            // Read central values
            _means.push_back(vl["value"].as<double>());

            // Read uncertainties
            double u = 0;
            std::vector<double> a;
            std::vector<double> m;
            for (auto const& err : vl["errors"])
              {
                // Sum in quadrature all uncurrelated uncertainties.
                if (err["label"].as<std::string>() == "unc")
                  u += pow(err["value"].as<double>(), 2);

                // Additive correlated uncertities
                if (err["label"].as<std::string>() == "add")
                  a.push_back(err["value"].as<double>());

                // Multiplicative correlated uncertities
                if (err["label"].as<std::string>() == "mult")
                  m.push_back(err["value"].as<double>());
              }
            _uncor.push_back(sqrt(u));
            _corra.push_back(a);
            _corrm.push_back(m);

            // Now concatenate vectors of additive and multiplicative
            // uncertainties and push it back into "_corr".
            std::vector<double> c = a;
            c.insert(c.end(), m.begin(), m.end());
            _corr.push_back(c);
          }
      }

    // Transverse-momentum bin bounds
    for (auto const& iv : datafile["independent_variables"])
      for (auto const& vl : iv["values"])
        {
          // Increment number of datapoints
          _kin.ndata++;

          // If the keys "low" and "high" are present the data-point
          // is integrated over the qT bin. If instead the key "value"
          // is found the bin is not integrated. Save in the "_qTv"
          // vector values of qT without repetitions. Don't allow for
          // values smaller than 10^{-5} GeV. Create a vector of pairs
          // to map the values of qT to the single data points. If the
          // data point is not integrate over qT the first entry of
          // the map pair is set to -1. Make also sure that all bins
          // are either all integrated or all are not by checking if
          // "_kin.IntqT" has changed after the first data
          // point. Finally, if the key "factor" is present, gather
          // the factors to be used to multiply the single bins in
          // qT. Set the factors to one be default.
          if (vl["low"] && vl["high"])
            {
              if (_kin.ndata > 1 and _kin.IntqT != true)
                throw std::runtime_error("[DataHandler::DataHandler]: Mixed qT integrated/non-integrated data points found");

              _kin.IntqT = true;
              const double qTl = vl["low"].as<double>();
              const double qTh = vl["high"].as<double>();
              if(std::find(_kin.qTv.begin(), _kin.qTv.end(), qTl) == _kin.qTv.end())
                _kin.qTv.push_back(std::max(vl["low"].as<double>(), 1e-5));
              if(std::find(_kin.qTv.begin(), _kin.qTv.end(), qTh) == _kin.qTv.end())
                _kin.qTv.push_back(vl["high"].as<double>());

              _kin.qTmap.push_back(std::make_pair(std::max(qTl, 1e-5), qTh));
            }
          else if (vl["value"])
            {
              if (_kin.ndata > 1 and _kin.IntqT != false)
                throw std::runtime_error("[DataHandler::DataHandler]: Mixed qT integrated/non-integrated data points found");

              _kin.IntqT = false;
              const double qTval = vl["value"].as<double>();
              if(std::find(_kin.qTv.begin(), _kin.qTv.end(), qTval) == _kin.qTv.end())
                _kin.qTv.push_back(std::max(vl["value"].as<double>(), 1e-5));

              _kin.qTmap.push_back(std::make_pair(-1, qTval));
            }
          else
            throw std::runtime_error("[DataHandler::DataHandler]: Invalid qT-bin structure");

          // Now fill in vector of bin-by-bin prefactors.
          if (vl["factor"])
            _kin.qTfact.push_back(vl["factor"].as<double>());
          else
            _kin.qTfact.push_back(1);
        }

    // Check that the "DataHandler" has been properly filled in
    if (_proc == UnknownProcess ||
        _kin.empty())
      throw std::runtime_error("[DataHandler::DataHandler]: Object not properly filled in. Probably one or more required keys are missing");

    // Now construct the covariance matrix
    _covmat.resize(_kin.ndata, _kin.ndata);
    for (int i = 0; i < _kin.ndata; i++)
      for (int j = 0; j < _kin.ndata; j++)
        _covmat(i, j) =
          std::inner_product(_corra[i].begin(), _corra[i].end(), _corra[j].begin(), 0.) * _means[i] * _means[j]    // Additive component
          + std::inner_product(_corrm[i].begin(), _corrm[i].end(), _corrm[j].begin(), 0.) * _means[i] * _means[j]  // Multiplicative component
          + (i == j ? pow(_uncor[i], 2) : 0);                                                                      // Uncorrelated component

    // Cholesky decomposition of the covariance matrix
    _CholL = CholeskyDecomposition(_covmat);

    // Fluctuate data given the replica ID and the random seed
    FluctuateData(fluctuation, seed);
  }

  //_________________________________________________________________________
  void DataHandler::FluctuateData(int const& fluctuation, int const& seed)
  {
    if (fluctuation <= 0)
      _fluctuations = _means;
    else
      {
        // The size of the fluctuated-data vector has to be the same
        // as the vector of mean values.
        _fluctuations.resize(_means.size());

        // Initialise random-number generator

        // Fluctuate the full data-set "fluctuation" times and keep
        // only the last fluctuation. This is non efficient but allows
        // one to identify a given random replica by its ID and the
        // random seed.
        for (int irep = 0; irep < fluctuation; irep++)
          for (int i = 0; i < (int) _means.size(); i++)
            {
              _fluctuations[i] = _means[i];
            }
        //_fluctuations = _means;
      }
  }

  //_________________________________________________________________________
  std::ostream& operator << (std::ostream &os, DataHandler const& DH)
  {
    os << "\nDataHandler report:\n";

    os << "- name: " << DH._name << "\n";

    if (DH._proc == DataHandler::Process::DY)
      os << "- Process: Drell-Yan\n";
    else if (DH._proc == DataHandler::Process::SIDIS)
      os << "- Process: SIDIS\n";
    else
      os << "- Process: Unknown\n";

    os << "- Target isoscalarity: " << DH._targetiso << "\n";
    os << "- Overall prefactor: " << DH._prefact << "\n";
    os << "- Number of points: " << DH._kin.ndata << "\n";
    os << "- Center-of-mass energy: " << DH._kin.Vs << " GeV\n";

    os << "- qT bin-bounds: [ ";
    for (auto const& qTp : DH._kin.qTmap)
      {
        os << "(" << qTp.first;
        if (qTp.second > 0)
          os << ", " << qTp.second;
        os << ") ";
      }
    os << "] GeV\n";

    os << "- qT bin factors: [ ";
    for (auto const& qTf : DH._kin.qTfact)
      os << qTf << " ";
    os << "]\n";

    if (DH._kin.Intv1)
      os << "- Integration bounds of the first kinematic variable: [" << DH._kin.var1b.first << ": " << DH._kin.var1b.second << "]\n";
    else
      os << "- Value of the first kinematic variable: " << ( DH._kin.var1b.first + DH._kin.var1b.second ) / 2 << "\n";

    if (DH._kin.Intv2)
      os << "- Integration bounds of the second kinematic variable: [" << DH._kin.var2b.first << ": " << DH._kin.var2b.second << "]\n";
    else
      os << "- Value of the second kinematic variable: " << ( DH._kin.var2b.first + DH._kin.var2b.second ) / 2 << "\n";

    if (DH._kin.PSRed)
      {
        os << "- Lepton minimun pT: " << DH._kin.pTMin << " GeV \n";
        os << "- Lepton range in eta: [" << DH._kin.etaRange.first << ": " << DH._kin.etaRange.second << "]\n";
      }
    os << "\n";

    return os;
  }
}
