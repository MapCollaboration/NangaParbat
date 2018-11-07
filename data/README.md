The data files contained in this folder are used by the code to compute the interpolation table and to obtaine the experimental information concerning the datasets included in the fit. They are written in the YAML format and follow as closely as possible the HEPData format (https://www.hepdata.net). However, due to a lack of standardisation of the current datafiles, they require a number of modifications that make them readable to to the code.

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
  - errors:
    - {symerror: 0.87}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 15.0
  - errors:
    - {symerror: 0.84}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 14.1
  - errors:
    - {symerror: 0.73}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 11.1
  - errors:
    - {symerror: 0.69}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 10.0
  - errors:
    - {symerror: 0.67}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 9.29
  - errors:
    - {symerror: 0.54}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 7.25
  - errors:
    - {symerror: 0.44}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 5.45
  - errors:
    - {symerror: 0.39}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 4.45
  - errors:
    - {symerror: 0.33}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 3.54
  - errors:
    - {symerror: 0.31}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 3.21
  - errors:
    - {symerror: 0.18}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 2.06
  - errors:
    - {symerror: 0.13}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 1.29
  - errors:
    - {symerror: 0.11}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.962
  - errors:
    - {symerror: 0.1}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.84
  - errors:
    - {symerror: 0.045}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.373
  - errors:
    - {symerror: 0.036}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.251
  - errors:
    - {symerror: 0.027}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.163
  - errors:
    - {symerror: 0.012}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.053
  - errors:
    - {symerror: 0.009}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.034
  - errors:
    - {symerror: 0.0013}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.005
  - errors:
    - asymerror: {minus: -0.0003, plus: 0.0004}
    - {label: 'sys,Overall normalization uncertainty', symerror: 4.4%}
    value: 0.0004
independent_variables:
- header: {name: PT, units: GEV}
  values:
  - {high: 1.0, low: 0.0}
  - {high: 2.0, low: 1.0}
  - {high: 3.0, low: 2.0}
  - {high: 4.0, low: 3.0}
  - {high: 5.0, low: 4.0}
  - {high: 6.0, low: 5.0}
  - {high: 7.0, low: 6.0}
  - {high: 8.0, low: 7.0}
  - {high: 9.0, low: 8.0}
  - {high: 10.0, low: 9.0}
  - {high: 12.0, low: 10.0}
  - {high: 14.0, low: 12.0}
  - {high: 16.0, low: 14.0}
  - {high: 18.0, low: 16.0}
  - {high: 20.0, low: 18.0}
  - {high: 25.0, low: 20.0}
  - {high: 30.0, low: 25.0}
  - {high: 35.0, low: 30.0}
  - {high: 40.0, low: 35.0}
  - {high: 50.0, low: 40.0}
  - {high: 60.0, low: 50.0}
  - {high: 70.0, low: 60.0}
  - {high: 85.0, low: 70.0}
  - {high: 100.0, low: 85.0}
  - {high: 200.0, low: 100.0}
  - {high: 300.0, low: 200.0}
```
