# Structure of the data files

The data files contained in this folder are used by the code to compute the interpolation table and to obtaine the experimental information concerning the datasets included in the fit. They are written in the YAML format and follow as closely as possible the HEPData format (https://www.hepdata.net). However, due to a lack of standardisation of the current datafiles, they require a number of modifications that make them readable to the code. Each data file has to contain all required information to carry out the calculation. Specifically, each data file needs to the encode all the information required to instantiate an object of the "datahandler" class. The relevant attributes of this class are:
```Shell
std::string           _name;
Process               _proc;
std::vector<double>   _mean;
std::vector<double>   _unc;
apfel::matrix<double> _cov;
Kinematics            _kin;
```
where `_name` is the identifier name of the dataset, `_proc` is a process enumerator that can take the values `DY` for Drell-Yan and `SIDIS` for semi-inclusive DIS. `_mean` is a vector containing the central values of of the measurements, `_unc` is the sum in quadrature of all the uncorrelated uncertainties (therefore each entry corresponds to the square of the total uncorrelated uncertainty), and `_cov` is the covariance matrix constructed out of the correlated uncertainties only. Therefore, adding `_unc` to the diagonal of `_cov` produces the full covariance matrix. Finally, `_kin` is an object of the structure `Kinematics`:
```Shell
struct Kinematics
{
  int                      ndata;
  double                   Vs;
  std::vector<double>      qTv;
  std::pair<double,double> var1b;
  std::pair<double,double> var2b;
  bool                     IntqT;
  bool                     Intv1;
  bool                     Intv2;
};
```
Here `ndata` corresponds to the number of measurements, `Vs` is the center of mass energy in GeV, `qTv` is the vector of transverse momentum points. Denpending on whether `IntqT` is `true` or `false`, the entries of the `qTv` vector will be interpreted as the bounds of bins in transverse momentum or as the values at which the cross section has to be computed. In other words, if `IntqT` is `true` the code will compute the *primitive* in *q*<sub>T</sub> of the cross section, such that the integrated cross section in *q*<sub>T</sub> is computed by taking the difference between the upper and the lower bound. `var1b` and `var2b` correspond to two additional kinematic variables (*e.g.* the invariant mass *Q* and the rapidity *y* of the lepton pair in Drell-Yan). They are given as `std::pair`'s containing the lower and upper bound of the respective allowed region. According to whether `Intv1`(`Intv2`) is `true` or `false`, the cross section will be integrated over or computed in the center of the allowed region.
```Shell
dependent_variables:
- header: {name: D(SIG)/DPT, units: NB/GEV}
  qualifiers:
  - {name: RE, value: PBAR P --> Z0 < E+ E- > X}
  - {name: SQRT(S), units: GeV, value: '1800.0'}
  - {name: SQRT(S), units: GeV, value: '1800.0'}
  values:
  - errors:
    - {symerror: 0.53}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 6.04
  - errors:
    - {symerror: 0.96}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 16.2
  - errors:
    - {symerror: 1.1}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 20.4
  - errors:
    - {symerror: 1.1}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 19.7
  - errors:
    - {symerror: 0.92}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 16.2
...
independent_variables:
- header: {name: PT, units: GEV}
  values:
  - {high: 1.0, low: 0.0}
  - {high: 2.0, low: 1.0}
  - {high: 3.0, low: 2.0}
  - {high: 4.0, low: 3.0}
  - {high: 5.0, low: 4.0}
...
```
