# Structure of the data files

The data files contained in this folder are used by the code to compute the interpolation tables and obtain the experimental information required to compute the χ<sup>2</sup> during the fit. They are written in YAML format and follow as closely as possible the **HEPData** format (https://www.hepdata.net) when data is available in this format. However, due to a lack of standardisation of the current data files, they require a number of modifications that make them readable to the code. Each data file has to contain all the necessary information to carry out the calculation. Specifically, each data file needs to the encode all the information required to instantiate an object of the `DataHandler` class.

With the goal of sticking as close as possible to the original **HEPData** YAML format, we use the same syntax suggested here: https://github.com/HEPData/hepdata-submission, but adapting it to our needs. A typical data file looks like this:
```Shell
dependent_variables:
  - header: {name: Combination Born}
    qualifiers:
      - {name: process, value: DY}
      - {name: target_isoscalarity, value: 1}
      - {name: prefactor, value: 1}
      - {name: Vs, value: 8000}
      - {name: Q, low: 66, high: 116, integrate: true}
      - {name: y, low: 0.4, high: 0.8, integrate: true}
      - {name: PS_reduction, pTmin: 20, etamin: -2.4, etamax: 2.4}
    values:
      - errors:
          - {label: unc, value: 9.6989329e-05}
          - {label: add, value: 0.008}
        value: 0.0269
      - errors:
          - {label: unc, value: 0.00012466079}
          - {label: add, value: 0.003}
        value: 0.05575
      - errors:
          - {label: unc, value: 0.00012615896}
          - {label: add, value: 0.003}
        value: 0.05642
      - errors:
          - {label: unc, value: 0.00015564731}
          - {label: add, value: 0.004}
        value: 0.04922
      - errors:
          - {label: unc, value: 0.00012873632}
          - {label: add, value: 0.004}
        value: 0.04071
...
independent_variables:
  - header: "{name: 'PT(P=3 4,RF=CM)', units: GEV}"
    values:
      - {high: 2, low: 1e-05}
      - {high: 4, low: 2}
      - {high: 6, low: 4}
      - {high: 8, low: 6}
      - {high: 10, low: 8}
      - {high: 13, low: 10}
      - {high: 16, low: 13}
      - {high: 20, low: 16}
...
```
This YAML document has two main blocks: `dependent_variables` and `independent_variables`. 

While most of the entries in the `dependent_variables` should be self-explanatory, the `value:` sub-block requires some clarifications. For instance, the item:
```Shell
  - errors:
    - {label: 'unc', symerror: 0.53}
    - {label: 'add', symerror: 0.05}
    - {label: 'mult', symerror: 0.044}
    value: 6.04
```
contains information on the uncertanties (`errors`). There can be more uncertainties of three different kinds:
- `unc`: *uncorrelated* uncertainty that contributes to the diagonal of the covariance matrix, typically the statistical uncertainty but can also be systematic.
- `add`: relative *additive correlated* uncertainty.
- `mult`: relative *multiplicative correlated* uncertainty (typically, the luminosity uncertainty).

Distinguishing between additive and multiplicative uncertainties is required when implementing some prescription to avoid the so-called *D'Agostini bias* induced by correlated multiplicative uncertainties.

The `independent_variables` block, instead, provides infomation on the binning in *q*<sub>T</sub> (notice that the number of items in the `value` sub-block in the `independent_variables` block has to match the number of items in the `value` sub-block in the `dependent_variables` block discussed above).

In the particular case displayed above, the corresponding `value` sub-block contains the upper (`high`) and lower (`low`) bounds of each bin in *q*<sub>T</sub>. This implies that the cross section has to be integrated over the *q*<sub>T</sub> bins. In case no integration in *q*<sub>T</sub> is required, the `independent_variables` block would look like this:
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
where only the central value in *q*<sub>T</sub> is reported.
