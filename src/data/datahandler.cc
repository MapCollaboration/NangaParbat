//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/datahandler.h"
#include "NangaParbat/linearsystems.h"

#include <iostream>
#include <math.h>
#include <numeric>
#include <algorithm>
#include <gsl/gsl_randist.h>

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
  DataHandler::DataHandler(std::string const& name, YAML::Node const& datafile, gsl_rng* rng, int const& fluctuation, std::vector<double> const& t0):
    _name(name),
    _proc(UnknownProcess),
    _targetiso(1),
    _prefact(1),
    _kin(DataHandler::Kinematics{}),
    _labels({}),
  _t0(t0)
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

    // Check that the t0 vector is either empty or contains exactly
    // "_kin.ndata" elements.
    if (!_t0.empty() && (int) _t0.size() != _kin.ndata)
      throw std::runtime_error("[DataHandler::DataHandler]: t0 vector has wrong size");

    // Now construct the covariance matrix. First include uncorrelated
    // and additive correlated uncertainties.
    _covmat.resize(_kin.ndata, _kin.ndata);
    for (int i = 0; i < _kin.ndata; i++)
      for (int j = 0; j < _kin.ndata; j++)
        _covmat(i, j) =
          + (i == j ? pow(_uncor[i], 2) : 0)                                                                         // Uncorrelated component (diagonal)
          + std::inner_product(_corra[i].begin(), _corra[i].end(), _corra[j].begin(), 0.) * _means[i] * _means[j];   // Additive component

    // Then include multiplicative uncertainties using the t0
    // prescription. If the t0 vector is empty or the fit is to the
    // central values, use the experimental central values.
    if (_t0.empty())
      for (int i = 0; i < _kin.ndata; i++)
        for (int j = 0; j < _kin.ndata; j++)
          _covmat(i, j) +=
            std::inner_product(_corrm[i].begin(), _corrm[i].end(), _corrm[j].begin(), 0.) * _means[i] * _means[j];
    else
      for (int i = 0; i < _kin.ndata; i++)
        for (int j = 0; j < _kin.ndata; j++)
          _covmat(i, j) +=
            std::inner_product(_corrm[i].begin(), _corrm[i].end(), _corrm[j].begin(), 0.) * _t0[i] * _t0[j];

    // Cholesky decomposition of the covariance matrix
    _CholL = CholeskyDecomposition(_covmat);

    // Fluctuate data given the replica ID and the random-number
    // generator. See Eqs. (13) and (14) of
    // https://arxiv.org/pdf/0808.1231.pdf for details.
    if (fluctuation <= 0 || rng == NULL)
      _fluctuations = _means;
    else
      {
        // The size of the fluctuated-data vector has to be the same
        // as the vector of mean values.
        _fluctuations.resize(_means.size());

        // Fluctuate the full data-set "fluctuation" times and keep
        // only the last fluctuation. This is non efficient but allows
        // one to identify a given random replica by its ID and the
        // random seed.
        for (int irep = 0; irep < fluctuation; irep++)
          {
            // Additive correlation random numbers
            std::vector<double> radd(_corra[0].size());
            for (int j = 0; j < (int) _corra[0].size(); j++)
              radd[j] = gsl_ran_gaussian(rng, 1);

            // Multiplicative correlation random numbers
            std::vector<double> rmult(_corrm[0].size());
            for (int j = 0; j < (int) _corrm[0].size(); j++)
              rmult[j] = gsl_ran_gaussian(rng, 1);

            for (int i = 0; i < (int) _means.size(); i++)
              {
                // Uncorrelated uncertainty fluctuation
                const double Func = _uncor[i] * gsl_ran_gaussian(rng, 1) / _means[i];

                // Additive correlated uncertainty fluctuation
                double Fadd = 0;
                for (int j = 0; j < (int) _corra[i].size(); j++)
                  Fadd += _corra[i][j] * radd[j];

                // Mulplicative correlated uncertainty fluctuation
                double Fmult = 1;
                for (int j = 0; j < (int) _corrm[i].size(); j++)
                  Fmult *= 1 + _corrm[i][j] * rmult[j];

                // Generate fluctuation
                _fluctuations[i] = _means[i] * Fmult * ( 1 + Func + Fadd );
              }
          }
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
