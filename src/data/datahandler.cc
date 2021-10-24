//
// Authors: Valerio Bertone: valerio.bertone@cern.ch
//          Chiara Bissolotti: chiara.bissolotti01@universitadipavia.it
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
  //_________________________________________________________________________
  DataHandler::Kinematics::Kinematics():
    ndata(0),
    Vs(0),
    qTv({}),
    qTmap({}),
    qTfact({}),
    var1b({0, 0}),
    var2b({0, 0}),
    var3b({0, 0}),
    IntqT(false),
    Intv1(false),
    Intv2(false),
    Intv3(false),
    PSRed(false),
    pTMin(0),
    etaRange({-10, 10})
  {
  }

  //_________________________________________________________________________
  DataHandler::Binning::Binning():
    zmin(-1),
    zmax(-1),
    zav(-1),
    Intz(true),
    xmin(-1),
    xmax(-1),
    xav(-1),
    Intx(true),
    Qmin(-1),
    Qmax(-1),
    Qav(-1),
    IntQ(true),
    ymin(-1),
    ymax(-1),
    yav(-1),
    Inty(true)
  {
  }

  //_________________________________________________________________________
  bool DataHandler::Kinematics::empty() const
  {
    if (ndata == 0 || Vs == 0 || qTv.empty() || qTmap.empty() || qTfact.empty() ||
        ( var1b.first == 0 && var1b.second == 0 &&
          var2b.first == 0 && var2b.second == 0 &&
          var3b.first == 0 && var3b.second == 0 ))
      return true;
    else
      return false;
  }

  //_________________________________________________________________________________
  DataHandler::DataHandler(DataHandler const& DH)
  {
    _name         = DH._name;
    _datafile     = DH._datafile;
    _proc         = DH._proc;
    _obs          = DH._obs;
    _targetiso    = DH._targetiso;
    _hadron       = DH._hadron;
    _charge       = DH._charge;
    _tagging      = DH._tagging;
    _prefact      = DH._prefact;
    _kin          = DH._kin;
    _means        = DH._means;
    _uncor        = DH._uncor;
    _corra        = DH._corra;
    _corrm        = DH._corrm;
    _corr         = DH._corr;
    _covmat       = DH._covmat;
    _CholL        = DH._CholL;
    _labels       = DH._labels;
    _fluctuations = DH._fluctuations;
    _t0           = DH._t0;
    _bins         = DH._bins;
  }

  //_________________________________________________________________________________
  DataHandler::DataHandler(std::string const& name, YAML::Node const& datafile, gsl_rng* rng, int const& fluctuation, std::vector<double> const& t0):
    _name(name),
    _datafile(datafile),
    _proc(UnknownProcess),
    _obs(UnknownObservable),
    _targetiso(1),
    _hadron("NONE"),
    _charge(0),
    _tagging({apfel::QuarkFlavour::TOTAL}),
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
                else if (ql["value"].as<std::string>() == "SIA")
                  _proc = SIA;
                else
                  throw std::runtime_error("[DataHandler::DataHandler]: Unknown process.");
              }

            // Observable
            if (ql["name"].as<std::string>() == "observable")
              {
                if (ql["value"].as<std::string>() == "dsigma/dxdydz")
                  _obs = dsigma_dxdydz;
                else if (ql["value"].as<std::string>() == "dsigma/dxdQdz")
                  _obs = dsigma_dxdQdz;
                else if (ql["value"].as<std::string>() == "multiplicity")
                  _obs = multiplicity;
                else if (ql["value"].as<std::string>() == "(dsigma/dxdzdQ2dPhT2)/dsigmaDIS")
                  _obs = multiplicity;
                else if (ql["value"].as<std::string>() == "FUUT")
                  _obs = F_uut;
                else if (ql["value"].as<std::string>() == "opposite_sign_ratio")
		  _obs = opposite_sign_ratio;
                else
                  throw std::runtime_error("[DataHandler::DataHandler]: Unknown observable.");
              }

            // Isoscalarity
            if (ql["name"].as<std::string>() == "target_isoscalarity")
              _targetiso = ql["value"].as<double>();

            // Hadron species
            if (ql["name"].as<std::string>() == "hadron")
              _hadron = ql["value"].as<std::string>();

            // Final state charge
            if (ql["name"].as<std::string>() == "charge")
              _charge = ql["value"].as<int>();

            // Quark-tagging
            if (ql["name"].as<std::string>() == "tagging")
              {
                _tagging.clear();
                for (std::string t : ql["value"].as<std::vector<std::string>>())
                  if (t == "d")
                    _tagging.push_back(apfel::QuarkFlavour::DOWN);
                  else if (t == "u")
                    _tagging.push_back(apfel::QuarkFlavour::UP);
                  else if (t == "s")
                    _tagging.push_back(apfel::QuarkFlavour::STRANGE);
                  else if (t == "c")
                    _tagging.push_back(apfel::QuarkFlavour::CHARM);
                  else if (t == "b")
                    _tagging.push_back(apfel::QuarkFlavour::BOTTOM);
                  else if (t == "t")
                    _tagging.push_back(apfel::QuarkFlavour::TOP);
                  else
                    throw std::runtime_error("[DataHandler::DataHandler]: Unknown quark-flavour tag");
              }

            // Possible prefactor
            if (ql["name"].as<std::string>() == "prefactor")
              _prefact = ql["value"].as<double>();

            // Center of mass energy
            if (ql["name"].as<std::string>() == "Vs")
              _kin.Vs = ql["value"].as<double>();

            // Invariant-mass (DY) or virtuality (SIDIS) interval
            if (ql["name"].as<std::string>() == "Q")
              {
                _kin.var1b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
                _kin.Intv1 = ql["integrate"].as<bool>();
              }

            // Rapidity (DY) or Bjorken-x (SIDIS) interval
            if (ql["name"].as<std::string>() == "y" || ql["name"].as<std::string>() == "x")
              {
                _kin.var2b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
                _kin.Intv2 = ql["integrate"].as<bool>();
              }

            // z interval (SIDIS and SIA)
            if (ql["name"].as<std::string>() == "z")
              {
                _kin.var3b = std::make_pair(ql["low"].as<double>(), ql["high"].as<double>());
                _kin.Intv3 = ql["integrate"].as<bool>();
              }

            // Phase-space reductions (lepton cuts for DY and W, y cuts for SIDIS)
            if (ql["name"].as<std::string>() == "PS_reduction")
              {
                _kin.PSRed    = true;
                _kin.pTMin    = (_proc == DY ? ql["pTmin"].as<double>(): ql["W"].as<double>()) ;
                _kin.etaRange = std::make_pair((_proc == DY ? ql["etamin"].as<double>(): ql["ymin"].as<double>()), (_proc == DY ? ql["etamax"].as<double>(): ql["ymax"].as<double>()));
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
                // Sum in quadrature all uncorrelated uncertainties
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
    for (auto const& vl : datafile["independent_variables"][0]["values"])
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
    if (_proc == UnknownProcess || _kin.empty())
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
    FluctuateData(rng, fluctuation);

    // Resize vector of bins according to the number of data
    // point. The following code is currently used only by the
    // FF_SIDIS project and need to be better integrated.
    _bins.resize(_kin.ndata);

    // Fill in binning
    for (auto const& iv : datafile["independent_variables"])
      {
        int i = 0;

        // z
        if (iv["header"]["name"].as<std::string>() == "z")
          for (auto const& vl : iv["values"])
            {
              if (vl["low"])
                _bins[i].zmin = vl["low"].as<double>();
              if (vl["high"])
                _bins[i].zmax = vl["high"].as<double>();
              if (vl["value"])
                _bins[i].zav = vl["value"].as<double>();
              _bins[i].Intz = _kin.Intv3;
              i++;
            }

        // x
        if (iv["header"]["name"].as<std::string>() == "x")
          for (auto const& vl : iv["values"])
            {
              if (vl["low"])
                _bins[i].xmin = vl["low"].as<double>();
              if (vl["high"])
                _bins[i].xmax = vl["high"].as<double>();
              if (vl["value"])
                _bins[i].xav = vl["value"].as<double>();
              _bins[i].Intx = _kin.Intv2;
              i++;
            }

        // y
        if (iv["header"]["name"].as<std::string>() == "y")
          for (auto const& vl : iv["values"])
            {
              if (vl["low"])
                _bins[i].ymin = vl["low"].as<double>();
              if (vl["high"])
                _bins[i].ymax = vl["high"].as<double>();
              if (vl["value"])
                _bins[i].yav = vl["value"].as<double>();
              i++;
            }

        // Q
        if (iv["header"]["name"].as<std::string>() == "Q2")
          for (auto const& vl : iv["values"])
            {
              if (vl["low"])
                _bins[i].Qmin = sqrt(vl["low"].as<double>());
              if (vl["high"])
                _bins[i].Qmax = sqrt(vl["high"].as<double>());
              if (vl["value"])
                _bins[i].Qav = sqrt(vl["value"].as<double>());
              _bins[i].IntQ = _kin.Intv1;
              i++;
            }
      }
  }
  /*
    //_________________________________________________________________________
    void DataHandler::FluctuateData(gsl_rng *rng, int const &fluctuation)
    {
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
        // random seed. This is useful when running fits on different
        // computation nodes.
        for (int irep = 0; irep < fluctuation; irep++)
        {
          // Additive correlation random numbers
          std::vector<double> radd(_corra[0].size());
          for (int j = 0; j < (int)_corra[0].size(); j++)
            radd[j] = gsl_ran_gaussian(rng, 1);

          // Multiplicative correlation random numbers
          std::vector<double> rmult(_corrm[0].size());
          for (int j = 0; j < (int)_corrm[0].size(); j++)
            rmult[j] = gsl_ran_gaussian(rng, 1);

          for (int i = 0; i < (int)_means.size(); i++)
          {
            // Uncorrelated uncertainty fluctuation
            const double Func = _uncor[i] * gsl_ran_gaussian(rng, 1) / _means[i];

            // Additive correlated uncertainty fluctuation
            double Fadd = 0;
            for (int j = 0; j < (int)_corra[i].size(); j++)
              Fadd += _corra[i][j] * radd[j];

            // Mulplicative correlated uncertainty fluctuation
            double Fmult = 1;
            for (int j = 0; j < (int)_corrm[i].size(); j++)
              Fmult *= sqrt(1 + _corrm[i][j] * rmult[j]);
              //Fmult *= 1 + _corrm[i][j] * rmult[j];

            // Generate fluctuation
            _fluctuations[i] = _means[i] * Fmult * (1 + Func + Fadd);
          }
        }
      }
    }

    //_________________________________________________________________________
    void DataHandler::FluctuateData(gsl_rng *rng, int const &fluctuation)
    {
      // Now construct the covariance matrix with only uncorrelated and
      // additive correlated uncertainties.
      apfel::matrix<double> covmatuc(_kin.ndata, _kin.ndata);
      for (int i = 0; i < _kin.ndata; i++)
        for (int j = 0; j < _kin.ndata; j++)
          covmatuc(i, j) =
            + (i == j ? pow(_uncor[i], 2) : 0)                                                                         // Uncorrelated component (diagonal)
            + std::inner_product(_corra[i].begin(), _corra[i].end(), _corra[j].begin(), 0.) * _means[i] * _means[j];   // Additive component

      // Get Cholesky decomposition
      const apfel::matrix<double> cholLuc = CholeskyDecomposition(covmatuc);

      // Fluctuate data given the replica ID and the random-number
      // generator.
      _fluctuations = _means;
      if (fluctuation > 0 && rng != NULL)
        {
          // Multiplicative correlation random numbers
          std::vector<double> rmult(_corrm[0].size());
          for (int j = 0; j < (int)_corrm[0].size(); j++)
            rmult[j] = gsl_ran_gaussian(rng, 1);

          for (int irep = 0; irep < fluctuation; irep++)
            {
              // Collect random numbers
              std::vector<double> z(_means.size());
              for (int i = 0; i < (int) _means.size(); i++)
                z[i] = gsl_ran_gaussian(rng, 1);

              // Include fluctuations on top of the mean values only
              // using uncorrelated and correlated uncertainties.
              _fluctuations = _means;
              for (int i = 0; i < (int) _means.size(); i++)
                for (int j = 0; j < (int) _means.size(); j++)
                  _fluctuations[i] += cholLuc(i, j) * z[j];

  	    for (int i = 0; i < (int)_means.size(); i++)
  	      {
  		// Mulplicative correlated uncertainty fluctuations
  		double Fmult = 1;
  		for (int j = 0; j < (int) _corrm[i].size(); j++)
  		  Fmult *= 1 + _corrm[i][j] * rmult[j];

  		// Include multiplicative uncertainties
  		_fluctuations[i] *= Fmult;
  	      }
            }
        }
    }
  */
  //_________________________________________________________________________
  void DataHandler::FluctuateData(gsl_rng *rng, int const &fluctuation)
  {
    // Fluctuate data given the replica ID and the random-number
    // generator.
    _fluctuations = _means;
    if (fluctuation > 0 && rng != NULL)
      {
        // Fluctuate the full data-set "fluctuation" times and keep
        // only the last fluctuation. This is non efficient but allows
        // one to identify a given random replica by its ID and the
        // random seed. This is useful when running fits on different
        // computation nodes.
        for (int irep = 0; irep < fluctuation; irep++)
          {
            // Collect random numbers
            std::vector<double> z(_means.size());
            for (int i = 0; i < (int) _means.size(); i++)
              z[i] = gsl_ran_gaussian(rng, 1);

            // Include fluctuations on top of the mean values
            _fluctuations = _means;
            for (int i = 0; i < (int) _means.size(); i++)
              for (int j = 0; j < (int) _means.size(); j++)
                _fluctuations[i] -= _CholL(i, j) * z[j];
          }
      }
  }

  //_________________________________________________________________________
  void DataHandler::SetMeans(std::vector<double> const& means, gsl_rng* rng, int const& fluctuation)
  {
    // Reset mean values
    _means = means;

    // Fluctuate data as required
    FluctuateData(rng, fluctuation);

    // Now set means equal to fluctuations
    _means = _fluctuations;

    // Change also the central values in the datafile
    int i = 0;
    for (auto dv : _datafile["dependent_variables"])
      for (auto vl : dv["values"])
        vl["value"] = _means[i++];
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

    os << "- Target isoscalarity: "   << DH._targetiso << "\n";
    os << "- Overall prefactor: "     << DH._prefact   << "\n";
    os << "- Number of points: "      << DH._kin.ndata << "\n";
    os << "- Center-of-mass energy: " << DH._kin.Vs    << " GeV\n";

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

    if (DH._proc == DataHandler::Process::SIDIS)
      {
        if (DH._kin.Intv3)
          os << "- Integration bounds of the third kinematic variable: [" << DH._kin.var3b.first << ": " << DH._kin.var3b.second << "]\n";
        else
          os << "- Value of the third kinematic variable: " << ( DH._kin.var3b.first + DH._kin.var3b.second ) / 2 << "\n";
      }

    if (DH._kin.PSRed)
      {
        if (DH._proc == DataHandler::Process::DY)
          {
            os << "- Lepton minimum pT: " << DH._kin.pTMin << " GeV \n";
            os << "- Lepton range in eta: [" << DH._kin.etaRange.first << ": " << DH._kin.etaRange.second << "]\n";
          }
        else if (DH._proc == DataHandler::Process::SIDIS)
          {
            os << "- Minimum W: " << DH._kin.pTMin << " GeV \n";
            os << "- Range in y: [" << DH._kin.etaRange.first << ": " << DH._kin.etaRange.second << "]\n";
          }

      }
    os << "\n";

    return os;
  }
}
