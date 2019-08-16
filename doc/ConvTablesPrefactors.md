``NangaParbat/doc``

# Convolution tables and their prefactors

This note reports how the convolution tables currently (15th august 2019) used in NangaParbat are produced and gathers some information about them.

In ``NangaParbat/tables`` there are six folders, one for each "*level*" of perturbative precision that we can reach. Here there is a summary:

|  | PDFs used| order|
| --- | --- | :---: |
| ``LL``   |  ``MMHT2014lo68cl `` |  0 |
| ``NLL``   |  ``MMHT2014lo68cl``  |  1|
| ``NLL'``  |  ``MMHT2014nlo68cl`` |  -1|
| ``NNLL``  |  ``MMHT2014nlo68cl`` |  2|
| ``NNLL'`` |  ``MMHT2014nnlo68cl`` |  -2|
| ``N3LL``  |  ``MMHT2014nnlo68cl``|  3|

For some experiments, for which the observable is
$$\frac{1}{\sigma_{\rm fid}}\frac{d\sigma}{dq_T}$$
it is necessary to add the prefactor  $\frac{1}{\sigma_{\rm fid}}$ in the header of the tables. The prefactor are calculated with ``DY@NNLO`` used at the order specified in the table:

| table | ``DY@NNLO`` at |
| --- | :---: |
| ``LL``   |  lo  |
| ``NLL``   |  lo  |
| ``NLLp``  |  nlo |
| ``NNLL``  |  nlo |
| ``NNLLp`` |  nnlo |
| ``N3LL``  |  nnlo|

Details and more information on the tables and how their prefactors are calculated follow in the sections below.

At the end of the notes an appendix with the details about ``DY@NNLO`` and how the fiducial cross sections were produced is also provided.

# NLL and LL convolution tables and their prefactors

The convolution tables at ``NLL`` are computed with ``NangaParbat/run/CreateTables.cc`` using the following configuration file (``NangaParbat/cards/config.yaml``), which is also copied in the folder ``NangaParbat/tables/NLL/``.

``` yaml
# Collinear PDF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
pdfset:
  name: "MMHT2014nlo68cl"
  member: 0

# Collinear FF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
ffset:
  name: "MMHT2014nlo68cl"
  member: 0

# Perturbative order of the computation. 0: LL, 1: NLL, 2: NNLL, 3:
# NNNLL, -1: NLL', -2: NNLL'
PerturbativeOrder: 1

# Initial and final scale-variation factors around mub = 2e^{-gamma_E}
# / b and Q, respectively.
TMDscales:
  Ci: 1
  Cf: 1

# Reference value of alpha_em.
alphaem:
  aref: 0.00776578395589
  Qref: 91.1876
  run: true

# Parameters of the x-space subgrids on which collinear PDFs are
# tabulated.
xgridpdf:
  - [60, 1e-4, 3]
  - [60, 1e-1, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Parameters of the x-space subgrids on which collinear FFs are
# tabulated.
xgridff:
  - [60, 1e-2, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Maximum number of Ogata-quadrature points (no more than 1000).
nOgata: 200

# Number of points, interpolation degree, and integration accuracy of
# the grid in Q.
Qgrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Number of points, interpolation degree, and integration accuracy of
# the grid in xi = exp(y) or xF (depending on the observable).
xigrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Maximum value allowed for the ratio qT / Q. This has to be intended
# as a "generation-level" cut meaning that only data points with qT /
# Q below this value are generated. Those above are simply set to
# zero. However, a more restrictive cut can still be applied at the
# fit level. This avoids computing predictions for points whose
# kinematics is such that TMD factorisation is not valid.
qToverQmax: 0.3
```

The convolution tables at ``LL`` are computed with ``NangaParbat/run/CreateTables.cc`` using the following configuration file (``NangaParbat/cards/config.yaml``), which is also copied in the folder ``NangaParbat/tables/LL/``.

``` yaml
# Collinear PDF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
pdfset:
  name: "MMHT2014nlo68cl"
  member: 0

# Collinear FF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
ffset:
  name: "MMHT2014nlo68cl"
  member: 0

# Perturbative order of the computation. 0: LL, 1: NLL, 2: NNLL, 3:
# NNNLL, -1: NLL', -2: NNLL'
PerturbativeOrder: 0

# Initial and final scale-variation factors around mub = 2e^{-gamma_E}
# / b and Q, respectively.
TMDscales:
  Ci: 1
  Cf: 1

# Reference value of alpha_em.
alphaem:
  aref: 0.00776578395589
  Qref: 91.1876
  run: true

# Parameters of the x-space subgrids on which collinear PDFs are
# tabulated.
xgridpdf:
  - [60, 1e-4, 3]
  - [60, 1e-1, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Parameters of the x-space subgrids on which collinear FFs are
# tabulated.
xgridff:
  - [60, 1e-2, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Maximum number of Ogata-quadrature points (no more than 1000).
nOgata: 200

# Number of points, interpolation degree, and integration accuracy of
# the grid in Q.
Qgrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Number of points, interpolation degree, and integration accuracy of
# the grid in xi = exp(y) or xF (depending on the observable).
xigrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Maximum value allowed for the ratio qT / Q. This has to be intended
# as a "generation-level" cut meaning that only data points with qT /
# Q below this value are generated. Those above are simply set to
# zero. However, a more restrictive cut can still be applied at the
# fit level. This avoids computing predictions for points whose
# kinematics is such that TMD factorisation is not valid.
qToverQmax: 0.3
```
---

Once computed, the tables for the experiments whose observable is the normalized cross section need their prefactor (to take the $\frac{1}{\sigma_{\rm fid}}$ into account).

This section is about the computation of the prefactors for the ``NLL`` (and the ``LL``)  convolution tables. Those prefactors are then read by ``tables/NNLL/IncludePrefactors.py`` from the file ``tables/NNLL/FiducialCrossSections.yaml`` and put into the header of the ``NLL`` and ``LL`` tables.

To see how the fiducial cross sections are computed with ``DY@NNLO`` and the lepton cuts that were applied see the section **Observables, cuts and relevant kinematical info for DY@NNLO fiducial cross sections** below.

The experiments for which the observable is
$$\frac{1}{\sigma_{\rm fid}}\frac{d\sigma}{dq_T}$$
and thus need the prefactor in the convolution table are the following.

## :lemon: Tevatron
### D0 RunII
The result from ``DY@NNLO`` for D0 RunII with ``MHT2014nlo68cl`` at ``order = 0 `` (which is `` lo ``) is:
`` Cross-section is:    170332.76191439579      +/-   13.918136517821676 ``

The integration interval in $y$ is fully specified in the data file:
```c++
- {name: y, low: -3.4, high: 3.4, integrate: true}
```
so there is no need to multiply by 2 the final result.
:lemon: So the prefactor for the table at ``NLL`` (and  ``LL``) is:

$$ \frac{1}{170.332} = 0.00587 $$

    0.00587

---

## CMS
#### CMS 7TeV
The result from DY@NNLO for CMS 7 TeV at ``lo `` (and  ``LL``) is:
``  Cross-section is:    291977.71184868366      +/-   50.019209452415701  ``

:hibiscus: So the prefactor for the table at ``NLL`` is:
  $$ \frac{2}{291.977} = 0.00685 $$

    0.00685

#### CMS 8TeV
The result from DY@NNLO for CMS 7 TeV at ``lo ``(and ``LL``)  is:
``  Cross-section is:    340132.04360900715      +/-   56.587087071662047``

:hibiscus: So the prefactor for the table at ``NLL``
 $$ \frac{2}{340.132} = 0.00588  $$

    0.00588

---

## :hibiscus: LHC
### ATLAS 7 TeV
#### ATLAS 7TeV_y_0_1
The result from ``DY@NNLO`` for ATLAS 7 TeV $0/le |y|<1$ at ``lo `` is:
 ``  Cross-section is:    196457.71541872955      +/-   28.139984287136862 ``

:hibiscus: So the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{196.457} = 0.01018 $$

    0.01018

#### ATLAS 7TeV_y_1_2
The result from ``DY@NNLO`` for ATLAS 7 TeV for $1/le|y|<2$
 `` Cross-section is:    135511.78919594214      +/-   24.839343833442506 ``
:hibiscus: the prefactor for the table at ``NLL`` (and ``LL``) is:
$$ \frac{2}{135.511} = 0.01476 $$

     0.01476

#### ATLAS 7TeV_y_2_2.4
The result from ``DY@NNLO`` for ATLAS 7 TeV for $2/le|y|<2.4$
 `` Cross-section is:    12568.935572630720      +/-   2.8146503776667231 ``

:hibiscus: the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{12.568} = 0.15913 $$

    0.15913

### ATLAS 8 TeV
#### ATLAS 8 TeV y_0_0.4
``DY@NNLO`` at ``lo`` gives:
`` Cross-section is:    89531.829341860619      +/-   11.609456518709898``

:hibiscus: So the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{89.531} =  0.02234 $$

    0.02234

#### ATLAS 8 TeV y_0.4_0.8
``DY@NNLO`` at ``lo`` gives:
``  Cross-section is:    89120.870781926060      +/-   14.603439817670228  ``

:hibiscus: So the prefactor for the table at ``NLL`` (and ``LL``) is:
$$ \frac{2}{89.120} = 0.02244 $$

    0.02244
#### ATLAS 8 TeV y_0.8_1.2
``DY@NNLO`` at ``lo`` gives:
`` Cross-section is:    85499.349246517595      +/-   14.149315496840137``

:hibiscus: So the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{85.499} = 0.02339 $$

    0.02339
#### ATLAS 8 TeV y_1.2_1.6
``DY@NNLO`` at ``lo`` gives:
`` Cross-section is:    69018.103147680959      +/-   11.282831795380023``
:hibiscus: So the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{69.018} = 0.02900 $$

    0.02900
#### ATLAS 8 TeV y_1.6_2
``DY@NNLO`` at ``lo`` gives:
`` Cross-section is:    43597.700716316125      +/-   7.7678302609150638``

:hibiscus: So the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{43.597} = 0.04587 $$

    0.04587
#### ATLAS 8 TeV y_2_2.4
``DY@NNLO`` at ``lo`` gives:
`` Cross-section is:    14398.840103992896      +/-   3.1852533684358848``

:hibiscus: So the prefactor for the table at ``NLL``(and ``LL``)  is:
$$ \frac{2}{14.398} = 0.13891 $$

    0.13891


# NNLL and NLL' convolution tables and their prefactors

The convolution tables at ``NNLL`` are computed with ``NangaParbat/run/CreateTables.cc`` using the following configuration file (``NangaParbat/cards/config.yaml``), which is also copied in the folder ``NangaParbat/tables/NNLL/``.

``` yaml
# Collinear PDF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
pdfset:
  name: "MMHT2014nlo68cl"
  member: 0

# Collinear FF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
ffset:
  name: "MMHT2014nlo68cl"
  member: 0

# Perturbative order of the computation. 0: LL, 1: NLL, 2: NNLL, 3:
# NNNLL, -1: NLL', -2: NNLL'
PerturbativeOrder: 2

# Initial and final scale-variation factors around mub = 2e^{-gamma_E}
# / b and Q, respectively.
TMDscales:
  Ci: 1
  Cf: 1

# Reference value of alpha_em.
alphaem:
  aref: 0.00776578395589
  Qref: 91.1876
  run: true

# Parameters of the x-space subgrids on which collinear PDFs are
# tabulated.
xgridpdf:
  - [60, 1e-4, 3]
  - [60, 1e-1, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Parameters of the x-space subgrids on which collinear FFs are
# tabulated.
xgridff:
  - [60, 1e-2, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Maximum number of Ogata-quadrature points (no more than 1000).
nOgata: 200

# Number of points, interpolation degree, and integration accuracy of
# the grid in Q.
Qgrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Number of points, interpolation degree, and integration accuracy of
# the grid in xi = exp(y) or xF (depending on the observable).
xigrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Maximum value allowed for the ratio qT / Q. This has to be intended
# as a "generation-level" cut meaning that only data points with qT /
# Q below this value are generated. Those above are simply set to
# zero. However, a more restrictive cut can still be applied at the
# fit level. This avoids computing predictions for points whose
# kinematics is such that TMD factorisation is not valid.
qToverQmax: 0.3
```

The convolution tables at ``NLL'`` are computed with ``NangaParbat/run/CreateTables.cc`` using the following configuration file (``NangaParbat/cards/config.yaml``), which is also copied in the folder ``NangaParbat/tables/NLLp/``.

``` yaml
# Collinear PDF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
pdfset:
  name: "MMHT2014nlo68cl"
  member: 0

# Collinear FF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
ffset:
  name: "MMHT2014nlo68cl"
  member: 0

# Perturbative order of the computation. 0: LL, 1: NLL, 2: NNLL, 3:
# NNNLL, -1: NLL', -2: NNLL'
PerturbativeOrder: -1

# Initial and final scale-variation factors around mub = 2e^{-gamma_E}
# / b and Q, respectively.
TMDscales:
  Ci: 1
  Cf: 1

# Reference value of alpha_em.
alphaem:
  aref: 0.00776578395589
  Qref: 91.1876
  run: true

# Parameters of the x-space subgrids on which collinear PDFs are
# tabulated.
xgridpdf:
  - [60, 1e-4, 3]
  - [60, 1e-1, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Parameters of the x-space subgrids on which collinear FFs are
# tabulated.
xgridff:
  - [60, 1e-2, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Maximum number of Ogata-quadrature points (no more than 1000).
nOgata: 200

# Number of points, interpolation degree, and integration accuracy of
# the grid in Q.
Qgrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Number of points, interpolation degree, and integration accuracy of
# the grid in xi = exp(y) or xF (depending on the observable).
xigrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Maximum value allowed for the ratio qT / Q. This has to be intended
# as a "generation-level" cut meaning that only data points with qT /
# Q below this value are generated. Those above are simply set to
# zero. However, a more restrictive cut can still be applied at the
# fit level. This avoids computing predictions for points whose
# kinematics is such that TMD factorisation is not valid.
qToverQmax: 0.3
```
---

Once computed, the tables for the experiments whose observable is the normalized cross section need their prefactor (to take the $\frac{1}{\sigma_{\rm fid}}$ into account).

This section is about the computation of the prefactors for the ``NNLL`` and the ``NLL'`` convolution tables. Those prefactors are then read by ``tables/NNLL/IncludePrefactors.py`` from the file ``tables/NNLL/FiducialCrossSections.yaml`` and put into the header of the ``NNLL`` and the ``NLL'`` tables.

To see how the fiducial cross sections are computed with ``DY@NNLO`` and the lepton cuts that were applied see the section **Observables, cuts and relevant kinematical info for DY@NNLO fiducial cross sections** below.

The experiments for which the observable is
$$\frac{1}{\sigma_{\rm fid}}\frac{d\sigma}{dq_T}$$
and thus need the prefactor in the convolution table are the following.

## :lemon: Tevatron
### D0 RunII
The result from ``DY@NNLO`` for D0 RunII with ``MHT2014nlo68cl`` at ``order = 1 `` (which is `` nlo ``) is:
`` Cross-section is:    242077.97189658415      +/-   64.532617297543922 ``

The integration interval in $y$ is fully specified in the data file:
```c++
- {name: y, low: -3.4, high: 3.4, integrate: true}
```
so there is no need to multiply by 2 the final result.
:lemon: The prefactor for the table at ``NNLL`` is:

$$ \frac{1}{242.077} = 0.00413 $$

    0.00413

---

## CMS
#### CMS 7TeV
The result from DY@NNLO for CMS 7 TeV at ``nlo `` is:
`` Cross-section is:    384569.70296986873      +/-   173.23232473578139 ``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
  $$ \frac{2}{384.569} = 0.00520 $$

    0.00520

#### CMS 8TeV
The result from DY@NNLO for CMS 7 TeV at ``nlo `` is:

``  Cross-section is:    456337.24784068606      +/-   200.59595538030723``

:hibiscus: So the prefactor for the table at ``NNLL``
 $$ \frac{2}{456.337} =  0.00438 $$

    0.00438

---

## :hibiscus: LHC
### ATLAS 7 TeV
#### ATLAS 7TeV_y_0_1
The result from ``DY@NNLO`` for ATLAS 7 TeV $0/le |y|<1$ at ``nlo `` is:
 `` Cross-section is:    251296.70723697136      +/-   112.79274880543350 ``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{251.296} = 0.00796 $$

    0.00796

#### ATLAS 7TeV_y_1_2
The result from ``DY@NNLO`` for ATLAS 7 TeV for $1\le|y|<2$
`` Cross-section is:    181267.67724295272      +/-   101.62628778480448``

:hibiscus: the prefactor for the table at ``N3LL`` is:
$$ \frac{2}{181.267} = 0.01103 $$

     0.01103
#### ATLAS 7TeV_y_2_2.4
The result from ``DY@NNLO`` for ATLAS 7 TeV for $2\le|y|<2.4$ is:
``Cross-section is:    17091.649067092476      +/-   13.736230145209442``

:hibiscus: the prefactor for the table at ``N3LL`` is:
$$ \frac{2}{17.091} = 0.11702 $$

    0.11702

### ATLAS 8 TeV
#### ATLAS 8 TeV y_0_0.4
``DY@NNLO`` at ``nlo`` gives:
`` Cross-section is:    113650.21487349906      +/-   64.962234235938112``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{113.650} =  0.01760 $$

    0.01760

#### ATLAS 8 TeV y_0.4_0.8
``DY@NNLO`` at ``nlo`` gives:
`` Cross-section is:    112853.37298334284      +/-   76.109083385576156 ``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{112.853} = 0.01772 $$

    0.01772
#### ATLAS 8 TeV y_0.8_1.2
``DY@NNLO`` at ``nlo`` gives:
`` Cross-section is:    109800.62398383966      +/-   77.616460329298533 ``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{109.800} = 0.01821 $$

    0.01821
#### ATLAS 8 TeV y_1.2_1.6
``DY@NNLO`` at ``nlo`` gives:
`` Cross-section is:    91884.352790554753      +/-   64.831284669144978``
:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{91.884} = 0.02177 $$

    0.02177
#### ATLAS 8 TeV y_1.6_2
``DY@NNLO`` at ``nlo`` gives:
`` Cross-section is:    59114.406514563336      +/-   41.768610027424231``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{59.114} = 0.03383 $$

    0.03383
#### ATLAS 8 TeV y_2_2.4
``DY@NNLO`` at ``nlo`` gives:
``Cross-section is:    19574.892053620617      +/-   16.315328670562156 ``

:hibiscus: So the prefactor for the table at ``NNLL`` is:
$$ \frac{2}{19.574} = 0.10218 $$

    0.10218


# N3LL and NNLL' convolution tables and their prefactors

The convolution tables at ``N3LL`` are computed with ``NangaParbat/run/CreateTables.cc`` using the following configuration file (``NangaParbat/cards/config.yaml``), which is also copied in the folder ``NangaParbat/tables/N3LL/``.

``` yaml
# Collinear PDF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
pdfset:
  name: "MMHT2014nnlo68cl"
  member: 0

# Collinear FF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
ffset:
  name: "MMHT2014nlo68cl"
  member: 0

# Perturbative order of the computation. 0: LL, 1: NLL, 2: NNLL, 3:
# NNNLL, -1: NLL', -2: NNLL'
PerturbativeOrder: 3

# Initial and final scale-variation factors around mub = 2e^{-gamma_E}
# / b and Q, respectively.
TMDscales:
  Ci: 1
  Cf: 1

# Reference value of alpha_em.
alphaem:
  aref: 0.00776578395589
  Qref: 91.1876
  run: true

# Parameters of the x-space subgrids on which collinear PDFs are
# tabulated.
xgridpdf:
  - [60, 1e-4, 3]
  - [60, 1e-1, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Parameters of the x-space subgrids on which collinear FFs are
# tabulated.
xgridff:
  - [60, 1e-2, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Maximum number of Ogata-quadrature points (no more than 1000).
nOgata: 200

# Number of points, interpolation degree, and integration accuracy of
# the grid in Q.
Qgrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Number of points, interpolation degree, and integration accuracy of
# the grid in xi = exp(y) or xF (depending on the observable).
xigrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Maximum value allowed for the ratio qT / Q. This has to be intended
# as a "generation-level" cut meaning that only data points with qT /
# Q below this value are generated. Those above are simply set to
# zero. However, a more restrictive cut can still be applied at the
# fit level. This avoids computing predictions for points whose
# kinematics is such that TMD factorisation is not valid.
qToverQmax: 0.3
```

The convolution tables at ``NNLL'`` are computed with ``NangaParbat/run/CreateTables.cc`` using the following configuration file (``NangaParbat/cards/config.yaml``), which is also copied in the folder ``NangaParbat/tables/NNLLp/``.

``` yaml
# Collinear PDF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
pdfset:
  name: "MMHT2014nnlo68cl"
  member: 0

# Collinear FF set and member to be used for the generation of the
# tables. They are assumed to be in the LHAPDF format.
ffset:
  name: "MMHT2014nlo68cl"
  member: 0

# Perturbative order of the computation. 0: LL, 1: NLL, 2: NNLL, 3:
# NNNLL, -1: NLL', -2: NNLL'
PerturbativeOrder: -2

# Initial and final scale-variation factors around mub = 2e^{-gamma_E}
# / b and Q, respectively.
TMDscales:
  Ci: 1
  Cf: 1

# Reference value of alpha_em.
alphaem:
  aref: 0.00776578395589
  Qref: 91.1876
  run: true

# Parameters of the x-space subgrids on which collinear PDFs are
# tabulated.
xgridpdf:
  - [60, 1e-4, 3]
  - [60, 1e-1, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Parameters of the x-space subgrids on which collinear FFs are
# tabulated.
xgridff:
  - [60, 1e-2, 3]
  - [50, 6e-1, 3]
  - [50, 8e-1, 3]

# Maximum number of Ogata-quadrature points (no more than 1000).
nOgata: 200

# Number of points, interpolation degree, and integration accuracy of
# the grid in Q.
Qgrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Number of points, interpolation degree, and integration accuracy of
# the grid in xi = exp(y) or xF (depending on the observable).
xigrid:
  n: 10
  InterDegree: 3
  eps: 1e-3

# Maximum value allowed for the ratio qT / Q. This has to be intended
# as a "generation-level" cut meaning that only data points with qT /
# Q below this value are generated. Those above are simply set to
# zero. However, a more restrictive cut can still be applied at the
# fit level. This avoids computing predictions for points whose
# kinematics is such that TMD factorisation is not valid.
qToverQmax: 0.3
```
---

Once computed, the tables for the experiments whose observable is the normalized cross section need their prefactor (to take the $\frac{1}{\sigma_{\rm fid}}$ into account).

This section is about the computation of the prefactors for the ``N3LL`` and the ``NNLL'`` convolution tables. Those prefactors are then read by ``tables/N3LL/IncludePrefactors.py`` from the file ``tables/N3LL/FiducialCrossSections.yaml`` and put into the header of the ``N3LL``  and the ``NNLL'`` tables.

The prefactors for the ``NNLL'`` convolution tables are the same as the ``N3LL`` ones, as their cross sections are both computed with ``MHT2014nnlo68cl``, and the process though which those prefactors are put into the header of the ``NNLL'`` tables is the same as in the ``N3LL`` case: in the ``tables/NNLLp/`` folder there are a copy of ``Includeprefactors.py`` and of  ``FiducialCrossSections.yaml``.

To see how the fiducial cross sections are computed with ``DY@NNLO`` and the lepton cuts that were applied see the section **Observables, cuts and relevant kinematical info for DY@NNLO fiducial cross sections** below.

The experiments for which the observable is
$$\frac{1}{\sigma_{\rm fid}}\frac{d\sigma}{dq_T}$$
and thus need the prefactor in the convolution table are the following.

## :lemon: Tevatron
### D0 RunII
Result from ``DY@NNLO`` for D0 RunII with ``MHT2014nnlo68cl`` at ``NNLO `` is:
`` Cross section  = 253573.16201836051  +/-   191.21956302108154 fb ``

The integration interval in $y$ is fully specified in the data file:
```c++
- {name: y, low: -3.4, high: 3.4, integrate: true}
```
so there is no need to multiply by 2 the final result.
:lemon: The prefactor for the table at ``N3LL``  is:

$$ \frac{1}{253.573} = 0.00394 $$

    0.00394

## :hibiscus: LHC

## CMS
#### CMS 7TeV
The result from ``DY@NNLO`` for CMS 7 TeV at ``NNLO `` is:
  ``Cross section is   398853.294 +/-  2137.997 fb``

:hibiscus: The prefactor for the table at ``N3LL`` is:
  $$ \frac{2}{398.853} = 0.005014 $$

    0.005014

#### CMS 8TeV
The result from  ``DY@NNLO`` for CMS 8 TeV at ``NNLO `` is:
`` Cross section is   473411.372 +/-  3035.719 fb ``

:hibiscus: The prefactor for the table at ``N3LL``
 $$ \frac{2}{473.411} =  0.004225 $$

    0.004225

---

### ATLAS 7 TeV

#### ATLAS 7TeV_y_0_1
Result from ``DY@NNLO`` for ATLAS 7 TeV with $0<|y|<1$ at ``NNLO `` is:
`` Cross section 253781.71862319650 +/- 4901.5063557353706 fb ``

:hibiscus: So the prefactor for the table at ``N3LL`` is:
$$ \frac{2}{253.781} = 0.00788 $$

    0.00788
#### ATLAS 7TeV_y_1_2
Result from ``DY@NNLO`` (Fulvio, cluster) for ATLAS 7 TeV with
$1<|y|<2$
:hibiscus: the prefactor for the table at ``N3LL`` is:
$$ \frac{2}{181.466} = 0.01102 $$

     0.01102
#### ATLAS 7TeV_y_2_2.4
Result from ``DY@NNLO`` (Fulvio, cluster) for ATLAS 7 TeV with
$2<|y|<2.4$
:hibiscus: the prefactor for the table at ``N3LL`` is:
$$ \frac{2}{17.104} = 0.1169 $$

    0.1169
    1.
### ATLAS 8 TeV
For ATLAS 8 TeV all the fiducial cross section come from ``DY@NNLO`` (Fulvio computed them on the cluster Neowulf), with  NNPDF30nnlo_118 .

#### ATLAS 8 TeV y_0_0.4
:hibiscus: The prefactor for the table at ``N3LL`` is:

    0.01756
#### ATLAS 8 TeV y_0.4_0.8
:hibiscus: The prefactor for the table at ``N3LL`` is:

    0.01768
#### ATLAS 8 TeV y_0.8_1.2
:hibiscus: The prefactor for the table at ``N3LL`` is:

    0.01829
#### ATLAS 8 TeV y_1.2_1.6
:hibiscus: The prefactor for the table at ``N3LL`` is:

    0.02175
#### ATLAS 8 TeV y_1.6_2
:hibiscus: The prefactor for the table at ``N3LL`` is:

    0.0332984
#### ATLAS 8 TeV y_2_2.4
:hibiscus: The prefactor for the table at ``N3LL`` is:

    0.0990859

# Observables, cuts and relevant kinematical info for DY@NNLO fiducial cross sections

Here there is some useful information to run ``DY@NNLO`` (to obtain the fiducial cross section).

The observable for all the experiments listed here is:
$$\frac{1}{\sigma_{\rm fid}}\frac{d\sigma}{dq_T}$$
and those listed here are the only experiments with such an observable (all the others included in this fit done with NangaParbat have differential cross sections as observables, $\frac{d\sigma}{dq_T}$).

In ``Dy@nnlo``, the first part of the ``src/User/cuts.f`` file is always:
``` fortran
CC
      cuts=.false.

CC    Insert here cuts

      pt3=dsqrt(pjet(3,1)**2+pjet(3,2)**2)
      pt4=dsqrt(pjet(4,1)**2+pjet(4,2)**2)
      eta3=etarap(3,pjet)
      eta4=etarap(4,pjet)

      ptmin=min(pt3,pt4)

      pt34=dsqrt((pjet(3,1)+pjet(4,1))**2+(pjet(3,2)+pjet(4,2))**2)

      m34=dsqrt((pjet(3,4)+pjet(4,4))**2-(pjet(3,1)+pjet(4,1))**2
     &     -(pjet(3,2)+pjet(4,2))**2-(pjet(3,3)+pjet(4,3))**2)

      y34=yraptwo(3,4,pjet)

C     Transverse mass

      pt3dpt4=pjet(3,1)*pjet(4,1)+pjet(3,2)*pjet(4,2)

      tmass=dsqrt(2*(pt3*pt4-pt3dpt4))
```
Moreover, in the ``bin/input`` file, depending on which order we want to perform the calculation, two things should always go in pair:
```
1                             ! order
'MMHT2014nlo68cl.LHgrid'   0  ! set, member (LHAPDFs)
```
```
2                              ! order
'MMHT2014nnlo68cl.LHgrid'   0  ! set, member (LHAPDFs)
```
## Tevatron: D0 RunII
:lemon: The cuts and the relevant kinematical variables for D0 Run II are:
$$ \sqrt{s} = 1960 \text{ GeV} $$
$$70 < Q < 110 \text{ GeV} $$
:lemon: Tevatron has proton-antiproton collisions, so in the ``bin/infile`` there must be a $-1$ for ``ih2``:
```
1960d0                        ! sroot
1 -1                          ! ih1, ih2
3                             ! nproc
91.1876d0 91.1876d0           ! mur, muf
1                             ! order
'tota'                        ! part
.false.                       ! zerowidth
70d0 110d0                    ! mwmin, mwmax
15 10000000                   ! itmx1, ncall1
30 10000000                   ! itmx2, ncall2
581                           ! rseed
92 0                          ! set, member (native PDFs)
'MMHT2014nlo68cl.LHgrid'   0  ! set, member (LHAPDFs)
'nlo_D0_RunII'               ! runstring
```
There are no lepton cuts for ``Tevatron, D0 Run II``, and the ``src/User/cuts.f`` for the calculation looks like this:

``` fortran
C     Cuts for Z production - D0 Run II
      if(m34.lt.70d0.or.m34.gt.110d0) cuts=.true.
```
## CMS 7 TeV
:hibiscus: The kinematical cuts for CMS 7 TeV are:
$(M_{ll}$ range is $Q$)
$$60 < M_{ll} < 120 \text{ GeV} $$
$$ p_T > 20 \text{ GeV}$$
$$|\eta| < 2.1 \text{ GeV} $$
$$|y| < 2.1 \text{ GeV} $$

The ``src/User/cuts.f`` is configured as:

``` fortran
C     ---- CMS 7 TeV
      if(ptmin.le.20d0) cuts=.true.

      if(dabs(eta3).ge.2.1d0.or.dabs(eta4).ge.2.1d0) cuts=.true.
      if(dabs(y34).ge.2.1d0) cuts=.true.

      if(m34.lt.60d0.or.m34.gt.120d0) cuts=.true.
```

## CMS 8 TeV
:hibiscus: The kinematical cuts for CMS 8 TeV are:
$(M_{ll}$ range is $Q$)
$$60 < M_{ll} < 120 \text{ GeV} $$
$$ p_T > 15 \text{ GeV}$$
$$|\eta| < 2.1 \text{ GeV} $$
$$|y| < 2.1 \text{ GeV} $$

The ``src/User/cuts.f`` is configured as:
``` fortran
C     ---- CMS 8 TeV
      if(ptmin.le.15d0) cuts=.true.

      if(dabs(eta3).ge.2.1d0.or.dabs(eta4).ge.2.1d0) cuts=.true.
      if(dabs(y34).ge.2.1d0) cuts=.true.

      if(m34.lt.60d0.or.m34.gt.120d0) cuts=.true.
```

## ATLAS 7 TeV

:hibiscus: The kinematical cuts for ATLAS 7 TeV are:
$(M_{ll}$ range is $Q$)

$$66 < M_{ll} < 116 \text{ GeV} $$
$$ p_T > 20 \text{ GeV}$$
$$|\eta| < 2.4 \text{ GeV} $$

and ``y`` has three bins:

$$ 0 \le|y|< 1 \text{ GeV} $$
$$ 1 \le|y|< 2 \text{ GeV} $$
$$ 2 \le|y|< 2.4 \text{ GeV} $$

For example for   $1\le |y|< 2$ ``src/User/cuts.f`` is configured as:
``` fortran
C     ---- ATLAS
      if(ptmin.le.20d0) cuts=.true.

      if(dabs(eta3).ge.2.4d0.or.dabs(eta4).ge.2.4d0) cuts=.true.

c$$$      if(dabs(y34).lt.0.0d0.or.dabs(y34).ge.1.0d0) cuts=.true.
      if(dabs(y34).lt.1.0d0.or.dabs(y34).ge.2.0d0) cuts=.true.
c$$$      if(dabs(y34).lt.2.0d0.or.dabs(y34).ge.2.4d0) cuts=.true.
c$$$
c$$$      if(dabs(y34).lt.0.0d0.or.dabs(y34).ge.0.4d0) cuts=.true.
c$$$      if(dabs(y34).lt.0.4d0.or.dabs(y34).ge.0.8d0) cuts=.true.
c$$$      if(dabs(y34).lt.0.8d0.or.dabs(y34).ge.1.2d0) cuts=.true.
c$$$      if(dabs(y34).lt.1.2d0.or.dabs(y34).ge.1.6d0) cuts=.true.
c$$$      if(dabs(y34).lt.1.6d0.or.dabs(y34).ge.2.0d0) cuts=.true.
c$$$      if(dabs(y34).lt.2.0d0.or.dabs(y34).ge.2.4d0) cuts=.true.

      if(m34.lt.66d0.or.m34.gt.116d0) cuts=.true.
```

## ATLAS 8 TeV

:hibiscus: The kinematical cuts for ATLAS 8 TeV are:
$(M_{ll}$ range is $Q$)
$$66 < M_{ll} < 116 \text{ GeV} $$
$$ p_T > 20 \text{ GeV}$$
$$|\eta| < 2.4 \text{ GeV} $$
and ``y`` has six bins:

$$ 0 \le|y|< 0.4 \text{ GeV} $$
$$ 0.4 \le|y|< 0.8 \text{ GeV} $$
$$ 0.8 \le|y|< 1.2 \text{ GeV} $$
$$ 1.2 \le|y|< 1.6 \text{ GeV} $$
$$ 1.6 \le|y|< 2 \text{ GeV} $$
$$ 2 \le|y|< 2.4 \text{ GeV} $$

The cuts in ``src/User/cuts.f`` work as in  ``ATLAS 7 TeV``, uncommenting one of the last six $y34$ interval at a time.
