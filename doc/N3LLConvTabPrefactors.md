# N3LL convolution tables - prefactors 
Note about the computation of the prefactors for the ``N3LL`` convolution tables. Those prefactors are read by ``tables/N3LL/IncludePrefactors.py`` from the file ``tables/N3LL/FiducialCrossSections.yaml`` and put into the header of the ``N3LL`` tables.
The experiments for which the observable is 
$$\frac{1}{\sigma_{\rm fid}}\frac{d\sigma}{dq_T}$$
and thus need the prefactor in the convolution table are the following.
## :lemon: Tevatron
### D0 RunII
Result from ``DY@NNLO`` for D0 RunII with ``MHT2014nnlo68cl`` at ``NNLO `` is:
$\sigma_{fid} = 253573.16201836051 \pm    191.21956302108154\quad\text{ fb}$
The integration interval in $y$ is fully specified in the data file: 
```c++
- {name: y, low: -3.4, high: 3.4, integrate: true}
```
so there is no need to multiply by 2 the final result. 
:lemon: So the prefactor for the table at ``N3LL`` is:

$$ \frac{1}{253.573} = 0.00394 $$

    0.00394
    
## :hibiscus: LHC    
### ATLAS 7 TeV

#### ATLAS 7TeV_y_0_1
Result from ``DY@NNLO`` for ATLAS 7 TeV with
$0<|y|<1$
at ``NNLO `` is:
$\sigma_{fid} = 253781.71862319650\pm 4901.5063557353706\quad\text{ fb}$
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

---
## CMS 
#### CMS 7TeV
Result from DY@NNLO for CMS 7 TeV at ``NNLO `` with the cuts:
  ``` Fortran
  c$$$C     Cuts for Z production (CMS)
  if(m34.lt.60d0.or.m34.gt.120d0) cuts=.true.

  if(ptmin.lt.20d0) cuts=.true.

  if(dabs(eta3).gt.2.1d0) cuts=.true.
  if(dabs(eta4).gt.2.1d0) cuts=.true.

  if(dabs(y34).gt.2.1d0) cuts=.true.
  ```
  is:
  
  ``
  Cross section is   398853.294 +/-  2137.997 fb
  ``
 :hibiscus: So the prefactor for the table at ``N3LL`` is: 
  $$ \frac{2}{398.853} = 0.005014 $$
  
    0.005014
  
#### CMS 8TeV  
Cuts applied in ``DY@NNLO`` for CMS 8 TeV at ``NNLO `` with the cuts:

  ``` Fortran
      if(m34.lt.60d0.or.m34.gt.120d0) cuts=.true.
     
      if(ptmin.lt.15d0) cuts=.true. !!for 8 TeV
   
      if(dabs(eta3).gt.2.1d0) cuts=.true.
      if(dabs(eta4).gt.2.1d0) cuts=.true.
      
      if(dabs(y34).gt.2.1d0) cuts=.true.
```        
`` Cross section is   473411.372 +/-  3035.719 fb ``
 :hibiscus: So the prefactor for the table at ``N3LL``    
 $$ \frac{2}{473.411} =  0.004225 $$
  
    0.004225
