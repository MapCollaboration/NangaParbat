# Convolution tables and their prefactors

This note reports how the convolution tables used in NangaParbat are produced and gathers some information about them.

In ``NangaParbat/tables`` there are six folders, one for each perturbative order currently available. In the following there is a summary of some relevant parameters used for the computation:

|  | PDFs used| order|
| --- | --- | :---: |
| ``LL``   |  ``MMHT2014lo68cl `` |  0 |
| ``NLL``   |  ``MMHT2014lo68cl``  |  1|
| ``NLL'``  |  ``MMHT2014nlo68cl`` |  -1|
| ``NNLL``  |  ``MMHT2014nlo68cl`` |  2|
| ``NNLL'`` |  ``MMHT2014nnlo68cl`` |  -2|
| ``N3LL``  |  ``MMHT2014nnlo68cl``|  3|

For some experiments, for which the observable is (1/σ<sub>fid</sub>)(dσ/d*q*<sub>T</sub>)<sub>fid</sub>
it is necessary to add the prefactor (1/σ<sub>fid</sub>) in the header of the tables. The fiducial total cross section σ<sub>fid</sub> is calculated with ``DY@NNLO`` at the order specified in the table below:

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

# Convolution tables and their prefactors

The convolution tables are computed with ``NangaParbat/run/CreateTables.cc`` using the configuration file ``config.yaml`` present in each subfolder of ``NangaParbat/tables/``.

Once computed, the tables for the experiments whose observable is the normalized cross section need their prefactor (1/σ<sub>fid</sub>) (computed with ``DY@NNLO`` at the appropriate order) to be included. These prefactors are stored in the file ``FiducialCrossSections.yaml`` present in each subfolder of ``NangaParbat/tables/`` and included in the relevant tables through the script. This operation has alredy been done in the tables released with the code.

To see how the fiducial cross sections are computed with ``DY@NNLO`` and the lepton cuts that were applied see the section **Observables, cuts and relevant kinematical info for DY@NNLO fiducial cross sections** below.

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
## Tevatron: D0 RunIImu
:lemon: The cuts and the relevant kinematical variables for D0 Run IImu are:
$$ \sqrt{s} = 1960 \text{ GeV} $$
$$65 < Q < 115 \text{ GeV} $$
:lemon: Tevatron has proton-antiproton collisions, so in the ``bin/infile`` there must be a $-1$ for ``ih2``:
```
1960d0                        ! sroot
1 -1                          ! ih1, ih2
3                             ! nproc
91.1876d0 91.1876d0           ! mur, muf
1                             ! order
'tota'                        ! part
.false.                       ! zerowidth
65d0 115d0                    ! mwmin, mwmax
15 10000000                   ! itmx1, ncall1
30 10000000                   ! itmx2, ncall2
581                           ! rseed
92 0                          ! set, member (native PDFs)
'MMHT2014nlo68cl.LHgrid'   0  ! set, member (LHAPDFs)
'nlo_D0_RunIImu'              ! runstring
```
There are no lepton cuts for ``Tevatron, D0 Run II``, and the ``src/User/cuts.f`` for the calculation looks like this:

``` fortran
C     ---- D0_RunIImu
      if(ptmin.le.15d0) cuts=.true.

      if(dabs(eta3).ge.1.7d0.or.dabs(eta4).ge.1.7d0) cuts=.true.
      if(dabs(y34).ge.1.7d0) cuts=.true.

      if(m34.lt.65d0.or.m34.gt.115d0) cuts=.true.
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

For ATLAS 8 TeV with $Q\in[46,66]$ and ATLAS 8 TeV with $Q\in[116,150]$, the bin is inclusive in rapidity:
$$46 < M_{ll} < 66 \text{ GeV} $$ or
$$66 < M_{ll} < 150 \text{ GeV} $$ and
$$ p_T > 20 \text{ GeV}$$
$$|\eta| < 2.4 \text{ GeV} $$
$$|y|< 2.4 \text{ GeV} $$
```
C     ---- ATLAS
      if(ptmin.le.20d0) cuts=.true.

      if(dabs(eta3).ge.2.4d0.or.dabs(eta4).ge.2.4d0) cuts=.true.

c$$$      if(dabs(y34).lt.0.0d0.or.dabs(y34).ge.1.0d0) cuts=.true.
c$$$      if(dabs(y34).lt.1.0d0.or.dabs(y34).ge.2.0d0) cuts=.true.
c$$$      if(dabs(y34).lt.2.0d0.or.dabs(y34).ge.2.4d0) cuts=.true.
c$$$
c$$$      if(dabs(y34).lt.0.0d0.or.dabs(y34).ge.0.4d0) cuts=.true.
c$$$      if(dabs(y34).lt.0.4d0.or.dabs(y34).ge.0.8d0) cuts=.true.
c$$$      if(dabs(y34).lt.0.8d0.or.dabs(y34).ge.1.2d0) cuts=.true.
c$$$      if(dabs(y34).lt.1.2d0.or.dabs(y34).ge.1.6d0) cuts=.true.
c$$$      if(dabs(y34).lt.1.6d0.or.dabs(y34).ge.2.0d0) cuts=.true.
c$$$      if(dabs(y34).lt.2.0d0.or.dabs(y34).ge.2.4d0) cuts=.true.

      if(dabs(y34).ge.2.4d0) cuts=.true.
      if(m34.lt.46d0.or.m34.gt.66d0) cuts=.true.                                                                                                                       
c$$$      if(m34.lt.116d0.or.m34.gt.150d0) cuts=.true.
```
