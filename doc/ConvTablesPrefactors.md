# Convolution tables and their prefactors

This note reports how the convolution tables for normalised cross sections used in NangaParbat are produced. In ``NangaParbat/tables`` there are six folders, one for each perturbative order currently available. For some experiments, for which the observable is (1/σ<sub>fid</sub>)(dσ/d*q*<sub>T</sub>)<sub>fid</sub>,
it is necessary to add the prefactor (1/σ<sub>fid</sub>) in the header of the tables. The fiducial total cross section σ<sub>fid</sub> is calculated with ``DY@NNLO`` at the order specified in the table below:

| table | ``DY@NNLO`` at |
| --- | :---: |
| ``LL``   |  lo  |
| ``NLL``   |  lo  |
| ``NLLp``  |  nlo |
| ``NNLL``  |  nlo |
| ``NNLLp`` |  nnlo |
| ``N3LL``  |  nnlo|

The convolution tables are computed with ``NangaParbat/run/CreateTables.cc`` using the configuration file ``config.yaml`` present in each subfolder of ``NangaParbat/tables/``.

Once computed, the tables for the experiments whose observable is the normalized cross section need their prefactor (1/σ<sub>fid</sub>) (computed with ``DY@NNLO`` at the appropriate order) to be included. These prefactors are stored in the file ``FiducialCrossSections.yaml`` present in each subfolder of ``NangaParbat/tables/`` and included in the relevant tables through the script. This operation has alredy been done in the tables released with the code.

The experiments for which the observable is (1/σ<sub>fid</sub>)(dσ/d*q*<sub>T</sub>)<sub>fid</sub>
and thus need the prefactor in the convolution table are the following.

## :lemon: Tevatron
- ### D0 RunII
- ### D0 RunIImu

## :hibiscus: LHC
- ### CMS
  - #### CMS 7TeV
  - #### CMS 8TeV

- ### ATLAS 7 TeV
  - #### ATLAS 7TeV_y_0_1
  - #### ATLAS 7TeV_y_1_2
  - #### ATLAS 7TeV_y_2_2.4

- ### ATLAS 8 TeV
  - #### ATLAS 8 TeV y_0_0.4
  - #### ATLAS 8 TeV y_0.4_0.8
  - #### ATLAS 8 TeV y_0.8_1.2
  - #### ATLAS 8 TeV y_1.2_1.6
  - #### ATLAS 8 TeV y_1.6_2
  - #### ATLAS 8 TeV y_2_2.4
  - #### ATLAS 8 TeV Q_66_46
  - #### ATLAS 8 TeV Q_116_150
