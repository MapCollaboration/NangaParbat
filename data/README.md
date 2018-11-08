The data files contained in this folder are used by the code to compute the interpolation table and to obtaine the experimental information concerning the datasets included in the fit. They are written in the YAML format and follow as closely as possible the HEPData format (https://www.hepdata.net). However, due to a lack of standardisation of the current datafiles, they require a number of modifications that make them readable to the code. Each data file has to contain all required information to carry out the calculation. Specifically, each data file needs to the encode all the information required to instantiate an object of the "datahandler" class. The relevant attributes of this class are:

```Shell
std::string           _name;
Process               _proc;
Kinematics            _kin;
std::vector<double>   _mean;
std::vector<double>   _unc;
apfel::matrix<double> _cov;
```


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
