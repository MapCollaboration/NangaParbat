

integer,parameter :: ord = 1, &       ! <ord>: 0 LL, 1 NLL, 2 NNLL
  izx=2, &					        ! <izx>: 1 x-integrated analysis, 2 x-binned analysis
  iflavindep=1, &	          	    ! <iflavindep>: 0 flavor-dep, 1 flavor-indep
  Znorm=0,	    &	         		! <NormZ>: 0 D Alesio et al., 1 "by eye"
  irepl=0,      &	         	    ! <irepl>: 0 without replicas, 1 one replica
  firstbin=2,   &	        		! <firstbin>: 0 both, 1 HERMES only, 2 COMPASS only
  errfrag=1,    &			        ! <errfrag>: 0 exclude error in fragmentation, 1 include error in fragmentation
  evchoose=6,   &			      	! <evchoose>: 1 hybrid, 2 css, 3 eis0, 4 eislin, 5 eislog, 6 numerical css
  bpresc=3,	    &		       		! <bpresc>: 1 common bstar, 2 exponential, 3 modified exponential
  npchoose=1,      &  		   		! <npchoose>: 1 gauss, 2 log
  ascorr=1    		   		        ! <ascorr>: alphas corrections -hard factor and wilsons- 0=exclude,1=include

!choose datafile for LHApdf
character(len=82),parameter :: name= 'MMHT2014nlo68cl'     !'GJR08FFnloE'   ! LHAPDF: gridfile  !   'MSTW2008nlo90cl'
integer,parameter :: N=0                                   ! LHAPDF: setmember of grid

!these should not be true at the same time
logical :: normONOFF = .true. , &    ! turn on or off normalization in chi2
       norm1binONOFF = .false.         ! 1st bin normalization

!choose which processes will be included in the analysis
logical :: SDboole=.false. , &      ! SIDIS boolean, if false skip channel
           DYboole=.true. , &      ! DY boolean, " " " "
           Zboole =.false.          ! Z boolean, " " " "

!choose which experiment will be included in the analysis
logical,parameter,dimension(26) :: expBoole = &
              (/.false.,  & !Hermes
                .false.,  & !Compass
                .true.,  & !E288_400
                .true.,  & !E288_300
                .true.,  & !E288_200
                .true.,  & !E605
                .false.,  & !CDF_1
                .false.,  & !D0_1
                .false.,  & !CDF_2
                .false.,  & !D0_2
                .false.,  & !ATLAS7TeV_y0_1
                .false.,  & !ATLAS7Tev_y1_2
                .false.,  & !ATLAS7TeV_y2_2.4
                .false.,  & !ATLAS_8TeV_y0_0.4
                .false.,  & !ATLAS_8TeV_y0.4_0.8
                .false.,  & !ATLAS_8TeV_y0.8_1.2
                .false.,  & !ATLAS_8TeV_y1.2_1.6
                .false.,  & !ATLAS_8TeV_y1.6_2.0
                .false.,  & !ATLAS_8TeV_y2.0_2.4
                .false.,  & !CMS7
                .false.,  & !CMS8
                .false.,  & !LHCb7
                .false.,  & !LHCb8
                .false.,  & !LHCb13
                .false.,  & !ATLAS_7TeV
                .false. /)  !ATLAS_8TeV
! choose binning conditions

logical,parameter :: flagXbinSD=.true. , &
                     flagQbinSD=.true. , &
                     flagZbinSD=.true. , &
                     flagMbinDY=.true.
