# Structure of the data files

The data files contained in this folder are used by the code to compute the interpolation tables and obtain the experimental information required to compute the χ<sup>2</sup> during the fit. They are written in YAML format and follow as closely as possible the **HEPData** format (https://www.hepdata.net) when data is available in this format. However, due to a lack of standardisation of the current data files, they require a number of modifications that make them readable to the code. Each data file has to contain all the necessary information to carry out the calculation. Specifically, each data file needs to the encode all the information required to instantiate an object of the `DataHandler` class.

With the goal of sticking as close as possible to the original **HEPData** YAML format, we use the same syntax suggested here: https://github.com/HEPData/hepdata-submission, but adapting it to our needs. A typical data file looks like this:
```Shell
dependent_variables:
  - header: {title: "LHCb at 7 TeV, 60 GeV < Q < 120 GeV, 2 < #it{y} < 4.5", titlepy: "LHCb at 7 TeV, 60 GeV < Q < 120 GeV, 2 < $y$ < 4.5", xlabel: "#it{q}_{T} [GeV]", xlabelpy: "$q_T\\rm{ [GeV]}$", ylabel: "#frac{d#it{#sigma}}{d#it{q}_{T}}  [pb GeV^{-1}]", ylabelpy: "$\\frac{d\\sigma}{dq_{T}}[\\rm{pb GeV}^{-1}]$"}
    qualifiers:
      - {name: process, value: DY}
      - {name: target_isoscalarity, value: 1}
      - {name: prefactor, value: 1}
      - {name: Vs, value: 7000}
      - {name: Q, low: 60, high: 120, integrate: true}
      - {name: y, low: 2, high: 4.5, integrate: true}
      - {name: PS_reduction, pTmin: 20, etamin: 2, etamax: 4.5}
    values:
      - errors:
          - {label: unc, value: 0.047727273}
          - {label: unc, value: 0.1072395}
          - {label: add, value: 0.019987605}
          - {label: mult, value: 0.021262408}
        value: 2.9336364
      - errors:
          - {label: unc, value: 0.088333333}
          - {label: unc, value: 0.1772165}
          - {label: add, value: 0.023006135}
          - {label: mult, value: 0.021262408}
        value: 5.4333333
      - errors:
          - {label: unc, value: 0.085}
          - {label: unc, value: 0.1498764}
          - {label: add, value: 0.035593493}
          - {label: mult, value: 0.021262408}
        value: 5.1741667
      - errors:
          - {label: unc, value: 0.0825}
          - {label: unc, value: 0.1259156}
          - {label: add, value: 0.035446489}
          - {label: mult, value: 0.021262408}
        value: 4.89
      - errors:
          - {label: unc, value: 0.07}
          - {label: unc, value: 0.09527062}
          - {label: add, value: 0.026787267}
          - {label: mult, value: 0.021262408}
        value: 4.1064286
      - errors:
          - {label: unc, value: 0.065333333}
          - {label: unc, value: 0.07937898}
          - {label: add, value: 0.014802925}
          - {label: mult, value: 0.021262408}
        value: 3.738
      - errors:
          - {label: unc, value: 0.054444444}
          - {label: unc, value: 0.06094111}
          - {label: add, value: 0.0095795636}
          - {label: mult, value: 0.021262408}
        value: 3.1316667
      - errors:
          - {label: unc, value: 0.04173913}
          - {label: unc, value: 0.04242867}
          - {label: add, value: 0.014663287}
          - {label: mult, value: 0.021262408}
        value: 2.4017391
      - errors:
          - {label: unc, value: 0.035384615}
          - {label: unc, value: 0.03199605}
          - {label: add, value: 0.012989531}
          - {label: mult, value: 0.021262408}
        value: 1.9838462
      - errors:
          - {label: unc, value: 0.024166667}
          - {label: unc, value: 0.02030595}
          - {label: add, value: 0.010679025}
          - {label: mult, value: 0.021262408}
        value: 1.3786111
      - errors:
          - {label: unc, value: 0.016}
          - {label: unc, value: 0.01351139}
          - {label: add, value: 0.0099691862}
          - {label: mult, value: 0.021262408}
        value: 1.0030909
      - errors:
          - {label: unc, value: 0.0089473684}
          - {label: unc, value: 0}
          - {label: add, value: 0.012259835}
          - {label: mult, value: 0.021262408}
        value: 0.57526316
      - errors:
          - {label: unc, value: 0.0029310345}
          - {label: unc, value: 0}
          - {label: add, value: 0.013128347}
          - {label: mult, value: 0.021262408}
        value: 0.19962069
      - errors:
          - {label: unc, value: 0.00020772947}
          - {label: unc, value: 0}
          - {label: add, value: 0.029023747}
          - {label: mult, value: 0.021262408}
        value: 0.0073236715
independent_variables:
  - header: "{name: PT, units: GEV}"
    values:
      - {high: 2.2, low: 1e-05}
      - {high: 3.4, low: 2.2}
      - {high: 4.6, low: 3.4}
      - {high: 5.8, low: 4.6}
      - {high: 7.2, low: 5.8}
      - {high: 8.7, low: 7.2}
      - {high: 10.5, low: 8.7}
      - {high: 12.8, low: 10.5}
      - {high: 15.4, low: 12.8}
      - {high: 19, low: 15.4}
      - {high: 24.5, low: 19}
      - {high: 34, low: 24.5}
      - {high: 63, low: 34}
      - {high: 270, low: 63}
...
```
This YAML document has two main blocks: `dependent_variables` and `independent_variables`. 

While most of the entries in the `dependent_variables` should be self-explanatory, the `value:` sub-block requires some clarifications. For instance, the item:
```Shell
      - errors:
          - {label: unc, value: 0.047727273}
          - {label: unc, value: 0.1072395}
          - {label: add, value: 0.019987605}
          - {label: mult, value: 0.021262408}
        value: 2.9336364
```
contains information on the uncertanties (`errors`). There can be more uncertainties of three different kinds:
- `unc`: *uncorrelated* uncertainty that contributes to the diagonal of the covariance matrix, typically the statistical uncertainty but can also be systematic. This uncertainty is *absolute* in value.
- `add`: relative *additive correlated* uncertainty. This uncertainty is *relative* to the central value.
- `mult`: relative *multiplicative correlated* uncertainty (typically, the luminosity uncertainty). Also this uncertainty is *relative* to the central value.

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
