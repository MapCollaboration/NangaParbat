module com
 implicit none

 include 'input_choices.h' !this file include all our fit choices

! minuit iflag value
 integer :: ifl

 logical :: sdwr=.false.
 logical :: dywr=.false.
 logical :: zwr=.false.

! constants
 double precision, parameter :: pi=dacos(-1.d0),gE=0.57721
 double precision, parameter :: eu2= 4.d0/9.d0,ed2=1.d0/9.d0

! vectors for squared charge of partons

double precision :: charge2(-6:6)  &
        =(/eu2,ed2,eu2,ed2,eu2,ed2,0.d0,ed2,eu2,ed2,eu2,ed2,eu2/)


! kernel constants  & parameters
 double precision, parameter :: bmax=1.122919d0
 double precision, parameter :: c0=1.122919d0,c02=1.260947d0! c02=c0^2, c0=2*exp(-\gamma_E)
 double precision, parameter :: CF=4/3d0,CA=3d0
 double precision, parameter :: lambda3=0.340d0,lambda4=0.297d0,lambda5=0.214d0 ! From PDG2013
 double precision, parameter :: mc=1.5d0,mb=4.7d0
 double precision, parameter :: zeta3=1.20205690316d0

 double precision :: g2

! flags
 integer :: fini
 integer :: ifinihad,izbin
 integer :: ihad,itar,iexp,ibin
 integer :: nf
 integer :: pnflag

! common variables
 double precision :: Php,x,z,pt2av(1:3)
 double precision :: Q0, Qi, Qf, Q02, Qi2, Qf2, q2
 double precision :: parb,kt2bv,parc,kt2cv
 double precision :: mu_b,npvar,alf2
 double precision :: xA,xB,m,pT,tau

 double precision,dimension(11,25000) :: datamat, datamat0
 double precision,dimension(10000) :: den
 integer,dimension(10000) :: bindenom
 double precision :: normlz(1:2,1:2,-2:2)
 double precision :: deltazd1(-2:2,-6:6),vard1(-2:2,-6:6,1:10)
 integer :: ndatSD,ndatDY,ndatZ
 integer :: ndatparSD(1:2,1:2,-2:2),ndatparDY(3:6)
 integer :: totbin(0:1) = 0
 integer :: j,k,jq

 double precision :: Npt(1:3),Nkt(-2:2,-6:6),Nptb
 double precision :: apt,bpt,bkt,gkt,ckt,apts,bpts
 double precision :: kt2av
 double precision, dimension(1:3)  :: kt2avA, kt2avB

 double precision,parameter :: precgaus=1.d-5

! names
!     identification of target and final hadron
!     itar=1 proton, itar=2 deuteron
!     ihad=1,0,-1 pi+,pi0,pi-
!     ihad=2,-2  K+,K-
 character(len=8),dimension(2)  :: target = (/ 'proton  ' ,'deuteron' /)
 character(len=7),dimension(5)  :: hadron= (/ 'kminus ','piminus' ,'pi0    ','piplus ' ,'kplus  '/)
 character(len=19),dimension(26) :: experiment = (/ 'Hermes             ','Compass            ','E288_400           ', &
      'E288_300           ','E288_200           ','E605               ','CDF_RunI           ','D0_RunI            ', &
      'CDF_RunII          ','D0_RunII           ','ATLAS_7TeV_y0_1    ','ATLAS_7TeV_y1_2    ','ATLAS_7TeV_y2_2.4  ', &
      'ATLAS_8TeV_y0_0.4  ','ATLAS_8TeV_y0.4_0.8','ATLAS_8TeV_y0.8_1.2','ATLAS_8TeV_y1.2_1.6','ATLAS_8TeV_y1.6_2.0', &
      'ATLAS_8TeV_y2.0_2.4','CMS_7TeV           ','CMS_8TeV           ','LHCb_7TeV          ','LHCb_8TeV          ', &
      'LHCb13TeV          ','ATLAS_7TeV_allY    ','ATLAS_8TeV_allY    '/)

 ! energy of reaction
 !     Values of "sqrt(s)", "s" and "y" for the experiment considered
 double precision,dimension(26),parameter ::  sqrt_enS = (/ 7.3d0, 17.3d0, 27.4d0, 23.8d0, 19.4d0, & 
 38.8d0, 1800d0, 1800d0, 1960d0, 1960d0,7d3,7d3,7d3,8d3,8d3,8d3,8d3,8d3,8d3,7d3,8d3,7d3,8d3,13d3,7d3,8d3 /)
 double precision,dimension(26),parameter ::  enS = (/ 52.7d0, 301d0, 750.76d0, 566.44d0, 376.36d0, 1505.4d0, & 
 32.4d5, 32.4d5, 38.416d5, 38.416d5,49d6,49d6,49d6,64d6,64d6,64d6,64d6,64d6,64d6,49d6,64d6,49d6,64d6,169d6,49d6,64d6 /)
 double precision,dimension(6),parameter :: y= (/0d0, 0d0, 0.03d0, 0.21d0, 0.4d0, 0d0/)

 ! vettori rapmin (ymin) e rapmax (ymax) per rapidità dei nuovi dati
 double precision,dimension(16),parameter :: rapmin = (/0.0d0,1.0d0,2.0d0,0.0d0,0.4d0,0.8d0,1.2d0,1.6d0,2.0d0, &
                                                        0.0d0,0.0d0,2.0d0,2.0d0,2.0d0,0d0,0d0/)
 double precision,dimension(16),parameter :: rapmax = (/1.0d0,2.0d0,2.4d0,0.4d0,0.8d0,1.2d0,1.6d0,2.0d0,2.4d0, &
                                                        2.1d0,2.1d0,4.34d0,4.47d0,4.5d0,2.4d0,2.4d0/)


! variables for norm of first bin
  integer ::  ndatSDin = 0d0, ndatDYin = 0d0, ndatZin = 0d0
  integer,dimension(1:2,1:2,-2:2) :: ndatparSDin =0, NtotbinSD=0
  integer :: ndatparDYin(3:6),ndatparZin(7:size(experiment)),ndatparZ(7:size(experiment))
  integer :: NtotbinDY(3:6),NtotbinZ(7:size(experiment))
  double precision,dimension(0:1) :: mult1bin=0d0, stat1bin=0d0, sys1bin=0d0
  double precision :: multtheo1bin=0d0,errtheo21bin=0d0
  double precision :: prevXbin=0d0,prevQ2bin=0d0,prevZbin=0d0, &
                      index1bin=0

end module com
