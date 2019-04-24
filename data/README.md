# Structure of the data files

The data files contained in this folder are used by the code to compute the interpolation tables and to obtain the experimental information required to compute the χ<sup>2</sup> during the fit. They are written in YAML format and follow as closely as possible the **HEPData** format (https://www.hepdata.net). However, due to a lack of standardisation of the current datafiles, they require a number of modifications that make them readable to the code. Each data file has to contain all the necessary information to carry out the calculation. Specifically, each data file needs to the encode all the information required to instantiate an object of the `DataHandler` class. The relevant attributes of this class are:
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
Here `ndata` corresponds to the number of data points, `Vs` is the center-of-mass energy in GeV, `qTv` is the vector of transverse momentum (*q*<sub>T</sub>) points. Denpending on whether `IntqT` is `true` or `false`, the entries of the `qTv` vector will be interpreted as the bounds of bins in *q*<sub>T</sub> or as the values at which the cross section has to be computed. In other words, if `IntqT` is `true` the code will compute the *primitive* in *q*<sub>T</sub> of the cross section, such that the integrated cross section in *q*<sub>T</sub> over some interval is computed by taking the difference between the upper and the lower bound. It is thus possible that the size of `qTv` does not coincide with `ndata`. `var1b` and `var2b` correspond to two additional kinematic variables (*e.g.* the invariant mass *Q* and the rapidity *y* of the lepton pair in Drell-Yan) that are considered "fixed" during the calculation of the cross section. They are given as `std::pair`'s containing the lower and upper bound of the respective allowed region. According to whether `Intv1`(`Intv2`) is `true` or `false`, the cross section will be integrated over or computed in the geometric center of the allowed region.

With the goal of sticking as close as possible to the original **HEPData** YAML format, we use the same syntax suggested here: https://github.com/HEPData/hepdata-submission, but adapting it to our needs. A typical data file looks like this:
```Shell
dependent_variables:
- header:
  qualifiers:
  - {name: process, value: DY}
  - {name: observable, value: d(sigma)/dydQdqT}
  - {name: target_isoscalarity, value: -1 }
  - {name: Vs, value: 1800}
  - {name: Q, low: 66, high: 116, integrate: true}
  - {name: y, low: -2.75, high: 2.75, integrate: true}
  values:
  - errors:
    - {label: 'unc', symerror: 0.53}
    - {label: 'add', symerror: 5.0%}
    - {label: 'mult', symerror: 4.4%}
    value: 6.04
  - errors:
    - {label: 'unc', symerror: 0.96}
    - {label: 'add', symerror: 5.0%}
    - {label: 'mult', symerror: 4.4%}
    value: 16.2
  - errors:
    - {label: 'unc', symerror: 1.1}
    - {label: 'add', symerror: 5.0%}
    - {label: 'mult', symerror: 4.4%}
    value: 20.4
  - errors:
    - {label: 'unc', symerror: 1.1}
    - {label: 'add', symerror: 5.0%}
    - {label: 'mult', symerror: 4.4%}
    value: 19.7
  - errors:
    - {label: 'unc', symerror: 0.92}
    - {label: 'corr', symerror: 5.0%}
    - {label: 'mult', symerror: 4.4%}
    value: 16.2
...
independent_variables:
- header: {name: PT}
  values:
  - {high: 1.0, low: 0.0}
  - {high: 2.0, low: 1.0}
  - {high: 3.0, low: 2.0}
  - {high: 4.0, low: 3.0}
  - {high: 5.0, low: 4.0}
...
```
This YAML document has two main blocks: `dependent_variables` and `independent_variables`. 

While most of the entries in the `dependent_variables` should be self-explanatory, the `value:` sub-block requires some clarifications. For instance, the item:
```Shell
  - errors:
    - {label: 'unc', symerror: 0.53}
    - {label: 'add', symerror: 5.0%}
    - {label: 'mult', symerror: 4.4%}
    value: 6.04
```
contains information on the uncertanties (`errors`). There can be more uncertainties of three different kinds:
- `unc`: *uncorrelated* uncertainty that contributes to the diagonal of the covariance matrix, typically the statistical uncertainty but can also be systematic.
- `add`: *additive correlated* uncertainty.
- `mult`: *multiplicative correlated* uncertainty (typically, the luminosity uncertainty).

Distinguishing between additive and multiplicative uncertainties is required when implementing some prescription to avoid the so-called *D'Agostini bias* induced by correlated multiplicative uncertainties. The information contained in the `error` blocks should be sufficient to construct the `_unc` and `_cov` blocks of the `DataHandler` class. Finally, the `value` block of `errors` contains the central value of the experimental point and will be stored in the `_mean` vector.

The `independent_variables` block, instead, provides infomation on the binning in *q*<sub>T</sub> (notice that the number of items in the `value` sub-block in the `independent_variables` block has to match the number of items in the `value` sub-block in the `dependent_variables` block discussed above).

In the particular case displayed above, the corresponding `value` sub-block contains the upper (`high`) and lower (`low`) bounds of each bin in *q*<sub>T</sub>. This implies that the cross section has to be integrated over the *q*<sub>T</sub> bins causing the `IntqT` flag to be `true`. In case no integration in *q*<sub>T</sub> is required, the `independent_variables` block may look like this:
```Shell
independent_variables:
- header: {name: PT, units: GEV}
  values:
  - {value: 0.1}
  - {value: 0.3}
  - {value: 0.5}
  - {value: 0.7}
  - {value: 0.9}
  ...
```
where only the central value in *q*<sub>T</sub> is reported, implying that the `IntqT` flag is to be `false`.
