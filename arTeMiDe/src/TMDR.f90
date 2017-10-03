!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe 1.0
!
!	Evaluation of the TMD evolution kernel
!	
!	if you use this module please, quote arXiv:1706.01473
!
!	ver 1.0: release (AV, 09.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
module TMDR

implicit none

  private
  
  public :: TMDR_Initialize,TMDR_SetgK,TMDR_report
  public :: TMDR_As,IgammaLog,Igamma,IgammaVg,IgammaVq
  public :: TMDR_R,TMD_R_short,TMDR_zetaP,TMDR_full_zetaP,zetaMU,TMDEvolutor,TMDD_boundary
  real*8, public, parameter ::C0_inv_const=0.890536208995099d0
  real*8, public, parameter :: C0_const=1.1229189671337703
  
  integer :: zMax !Length of grid
  real*8:: mu_ref!reference mu-point
  
  real*8, dimension(:), allocatable :: As_grid
  real*8, dimension(:,:), allocatable :: I_gamma_grid
  real*8, dimension(:,:), allocatable :: I_gamma_Vq_grid
  real*8, dimension(:,:), allocatable :: I_gamma_Vg_grid
  real*8, dimension(:,:), allocatable :: I_gammaLog_grid
  
  !! These are orders of gammaCUSP and the other anomalous dimension
  !it is SET from external, by calling subroutine SetOrderForR
  integer :: orderCUSP_global, orderAD_global, orderZETA_global
  !!non-pertrubative parameter
  !it is SET from external, by calling subroutine SetgK
  real*8:: gK_global
  
  !!!Threashold parameters
  real*8,parameter :: mCHARM=1.4d0
  real*8,parameter :: mBOTTOM=4.75d0
  
  !These are The coefficeints d(n,k) for TMD rapidity evolution at NF=3 for quarks
  ! ddTMD_q(X,Y) is for X=1,2,3 is pertrubative order, Y=0,1,2,3 the power of LOG
  real*8,parameter, dimension(1:3,0:3) :: ddTMD3_q= reshape((/&
	0.0d0, -15.759631021381722d0, -260.5342569653856d0,&
	2.6666666666666665d0, 24.347721597095045d0, 25.439076311068938d0,&
	0.0d0, 12.0d0, 304.4628277071887d0,&
	0.0d0,  0.0d0, 72.0d0 /), shape(ddTMD3_q))
	
  !These are The coefficeints d(n,k) for TMD rapidity evolution at NF=4 for quarks
  real*8,parameter, dimension(1:3,0:3) :: ddTMD4_q= reshape((/&
	0.0d0, -18.525063120147152d0, -305.8365169792602d0,&
	2.6666666666666665d0, 21.384758634132083d0, -93.99776462634762d0,&
	0.0d0, 11.11111111111111d0, 246.65076639554516d0,&
	0.0d0,  0.0d0, 61.72839506172839d0 /), shape(ddTMD4_q))
	
 !These are The coefficeints d(n,k) for TMD rapidity evolution at NF=4 for quarks
  real*8,parameter, dimension(1:3,0:3) :: ddTMD5_q= reshape((/&
	0.0d0, -21.290495218912582d0, -342.0455323786133d0,&
	2.6666666666666665d0, 18.42179567116912d0, -206.85024342384636d0,&
	0.0d0, 10.222222222222221d0, 192.78932236785215d0,&
	0.0d0,  0.0d0, 52.24691358024691d0 /), shape(ddTMD5_q))
  
  real*8,parameter, dimension(3:5) :: beta0=(/9d0,8.33333333d0,7.66666667d0 /)
  real*8,parameter, dimension(3:5) :: beta1=(/64d0,51.33333333d0,38.66666667d0 /)
  real*8,parameter, dimension(3:5) :: beta2=(/643.83333333333d0,406.351851851852d0,180.907407407407d0/)
  
  contains
  

!!! Initializing routing
!!! Filles the prebuiled arrays
  subroutine TMDR_Initialize(orderAs,orderCUSP,orderAD,orderZETA)
    character(len=*)::orderCUSP,orderAD,orderZETA,orderAs
    character (len=50) :: line
    integer ::i
    
    write(*,*) '----- arTeMiDe.TMDR ver 1.0: .... initialization'
    
    OPEN(UNIT=51, FILE='../paths', ACTION="read", STATUS="old")
    
    !!!!search for TMDR entry
    do
    read(51,'(A)') line    
    if(line(1:3)=='*1 ') exit
    end do
    
    !!!!search for TMDR.as entry
    do
    read(51,'(A)') line
    if(line(1:3)=='*A ') exit
    end do
     SELECT CASE(orderAs)
      CASE ("LO")
	read(51,'(A)') line
	OPEN(UNIT=50, FILE="../"//line(7:), ACTION="read", STATUS="old")	
      CASE ("NLO")
	read(51,'(A)') line
	read(51,'(A)') line
	OPEN(UNIT=50, FILE="../"//line(7:), ACTION="read", STATUS="old")	
      CASE ("NNLO")
        read(51,'(A)') line
        read(51,'(A)') line
        read(51,'(A)') line
	OPEN(UNIT=50, FILE="../"//line(7:), ACTION="read", STATUS="old")	
      CASE DEFAULT
	write(*,*) 'WARNING: arTeMiDe.TMDR_Initialize: unknown order for alpha_strong. Switch to NLO.'
	read(51,'(A)') line
	read(51,'(A)') line
	OPEN(UNIT=50, FILE="../"//line(7:), ACTION="read", STATUS="old")	
     END SELECT    
    
    CLOSE (51, STATUS='KEEP') 
    
    !!! Read the grid header
    READ(50,'(A75)') line !!!! Read header and print it
    write (*,*) line
    
    READ(50,*) line    !!!! Skip 2 technical lines
    READ(50,*) line
    
    READ(50,*) zMax 	!!length of grid    
    READ(50,*) line    !!!! Skip 1 technical lines    
    READ(50,*) mu_ref  !!!! refenrece point
    READ(50,*) line    !!!! Skip 1 technical lines
    
    !allocate the arrays of greed acording to the readed file
    allocate(As_grid(0:zMax))
    allocate(I_gamma_grid(0:zMax,1:3))
    allocate(I_gamma_Vq_grid(0:zMax,1:3))
    allocate(I_gamma_Vg_grid(0:zMax,1:3))
    allocate(I_gammaLog_grid(0:zMax,1:3))
    
    
    !fill the grid arrays
    do i=0,zMax
      READ(50,*) As_grid(i),&
	I_gamma_grid(i,1),I_gamma_grid(i,2),I_gamma_grid(i,3),&
	I_gamma_Vq_grid(i,1),I_gamma_Vq_grid(i,2),I_gamma_Vq_grid(i,3),&
	I_gamma_Vg_grid(i,1),I_gamma_Vg_grid(i,2),I_gamma_Vg_grid(i,3),&
	I_gammaLog_grid(i,1),I_gammaLog_grid(i,2),I_gammaLog_grid(i,3)
    end do
    
!      do i=0,zMax
!       write(*,*) As_grid(i+1)
!     end do
    
    CLOSE (50, STATUS='KEEP') 
    
    SELECT CASE(orderCUSP)
      CASE ("LO")
	write(*,*) 'arTeMiDe.TMDR_Initialize:the 0-loop gammaCUSP does not exist! Switch to NLO.'
	orderCUSP_global=1
      CASE ("NLO")
	orderCUSP_global=1
      CASE ("NNLO")
	orderCUSP_global=2
      CASE ("NNNLO")
	orderCUSP_global=3
      CASE ("NNNNLO")
	write(*,*) 'arTeMiDe.TMDR_Initialize:the four-loop gammaCUSP is not known yet :(. Switch to NNNLO.'
	orderCUSP_global=3
      CASE DEFAULT
	write(*,*) 'arTeMiDe.TMDR_Initialize:try to set unknown gammaCUSP order. Switch to NLO.'
	orderCUSP_global=1
     END SELECT
     
     SELECT CASE(orderAD)
      CASE ("LO")
	write(*,*) 'arTeMiDe.TMDR_Initialize:the 0-loop ADs do not exist! Switch to NLO.'
	orderAD_global=1
      CASE ("NLO")
	orderAD_global=1
      CASE ("NNLO")
	orderAD_global=2
      CASE ("NNNLO")
	orderAD_global=3
      CASE ("NNNNLO")
	write(*,*) 'arTeMiDe.TMDR_Initialize:the four-loop ADs are unknown :( ! Switch to NNNLO.'
	orderAD_global=3
      CASE DEFAULT
	write(*,*) 'arTeMiDe.TMDR_Initialize:try to set unknown ADs orders. Switch to NLO.'
	orderAD_global=1
     END SELECT
     SELECT CASE(orderZETA)
      CASE ("LO")
	write(*,*) 'arTeMiDe.TMDR_Initialize:try to set LO gammaZETA order. Switch to NLL.'
	orderZETA_global=0
      CASE ("NLL")
	orderZETA_global=0
      CASE ("NLO")
	orderZETA_global=1
      CASE ("NNLL")
	orderZETA_global=2
      CASE ("NNLO")
	orderZETA_global=3
      CASE ("NNNLL")
	orderZETA_global=4
      CASE DEFAULT
	write(*,*) 'arTeMiDe.TMDR_Initialize:try to set unknown gammaZETA order. Switch to NLL.'
	orderZETA_global=0
     END SELECT
     
     gK_global=0d0
     
     write(*,*) '----- arTeMiDe.TMDR ver 1.0: .... initialized'
     
  end subroutine TMDR_Initialize

  
  !Just set gK
  subroutine TMDR_SetgK(gK)
    real*8::gK
    gK_global=gK
  end subroutine TMDR_SetgK
  
  !report the set variables
  subroutine TMDR_report()
    character(len=7)::printorderCUSP,printorderAD,printorderZETA
    
    SELECT CASE(orderCUSP_global)
      CASE (0)
	printorderCUSP="LO"
      CASE (1)
	printorderCUSP="NLO"
      CASE (2)
	printorderCUSP="NNLO"
      CASE (3)
	printorderCUSP="NNNLO"
      CASE (4)
	printorderCUSP="NNNNLO"
      CASE DEFAULT
	printorderCUSP="unknown"
     END SELECT
    SELECT CASE(orderAD_global)
      CASE (0)
	printorderAD="LO"
      CASE (1)
	printorderAD="NLO"
      CASE (2)
	printorderAD="NNLO"
      CASE (3)
	printorderAD="NNNLO"
      CASE (4)
	printorderAD="NNNNLO"
      CASE DEFAULT
	printorderAD="unknown"
     END SELECT
     
    SELECT CASE(orderZETA_global)
      CASE (0)
	printorderZETA="LO"
      CASE (1)
	printorderZETA="NLO"
      CASE (2)
	printorderZETA="NNLO"
      CASE DEFAULT
	printorderZETA="unknown"
     END SELECT
    
    write(*,*) 'TMDR module report : GammaCusp is ',printorderCUSP,', other ADs is ',&
	printorderAD, 'zeta_mu is at ', printorderZETA, ' gK=',gK_global
  end subroutine TMDR_report
  
  !!! Function interpolate the value of as, using grids  
  function As(mu)
  
    real*8:: As,mu
    integer :: zInt
    real*8::zReal,zFrac   
    
    zReal=20.d0*LOG(2.d0*mu)
    zInt=INT(zReal)
    zFrac=zReal-zInt
    
    !The linear interpolation is used, since as~1/Log[mu] more-or-less
    !It gives accuracy better then 10^{-6} in comparison to exact values
    If (zReal<1) then
      WRITE(*,*) 'WARNING arTeMiDe.TMDR: Generic large value evaluated for As (mu=',mu,' is too close to Landau pole.)'
      As=1.d8
    else if(zInt>zMax) then
      !WRITE(*,*) 'TMDR WARNING: Logarithmical extrapolation is used for As (values of mu outside of grid)'
      As=1/(As_grid(zMax)-(As_grid(zMax)-As_grid(zMax+1))*zFrac)
    else
      As=1/(As_grid(zInt)-(As_grid(zInt)-As_grid(zInt+1))*zFrac)
    end if
  
  end function As
  
  !!!! just external interface to As
  function TMDR_As(mu)
    real*8::TMDR_As,mu
    TMDR_As=As(mu)
  end function TMDR_As

  !!! Function interpolate the value of Igamma, using grids
  !!! Integral over Gamma_cusp
  function Igamma(mu)  
    real*8:: Igamma,mu
    integer :: zInt
    real*8::zReal,zFrac   
    
    zReal=20.d0*LOG(2.d0*mu)
    zInt=INT(zReal)
    zFrac=zReal-zInt
    
    !The linear interpolation is used, since as~1/Log[mu] more-or-less
    !It gives accuracy better then 10^{-6} in comparison to exact values
    If (zReal<1) then
      WRITE(*,*) 'TMDR WARNING: Generic large value evaluated for Igamma (mu=',mu,' is too close to Landau pole.)'
      Igamma=1.d8
    else if(zInt>zMax) then
      !WRITE(*,*) 'TMDR WARNING: Logarithmical extrapolation is used for Igamma (values of mu outside of grid)'
      Igamma=LOG(I_gamma_grid(zMax,orderCUSP_global)-(I_gamma_grid(zMax,orderCUSP_global)&
						  -I_gamma_grid(zMax+1,orderCUSP_global))*zFrac)
    else
      Igamma=LOG(I_gamma_grid(zInt,orderCUSP_global)-(I_gamma_grid(zInt,orderCUSP_global)&
						  -I_gamma_grid(zInt+1,orderCUSP_global))*zFrac)
    end if
  
  end function Igamma
  
  !!! Function interpolate the value of IgammaLog, using grids
  !!! Integral over Gamma_cusp log(mu)
  function IgammaLog(mu)  
    real*8:: IgammaLog,mu
    integer :: zInt
    real*8::zReal,zFrac   
    
    zReal=20.d0*LOG(2.d0*mu)
    zInt=INT(zReal)
    zFrac=zReal-zInt
    
    !The linear interpolation is used, since as~1/Log[mu] more-or-less
    !It gives accuracy better then 10^{-6} in comparison to exact values
    If (zReal<1) then
      WRITE(*,*) 'TMDR WARNING: Generic large value evaluated for IgammaLog (mu=',mu,' is too close to Landau pole.)'
      IgammaLog=1.d8
    else if(zInt>zMax) then
      !WRITE(*,*) 'TMDR WARNING: Logarithmical extrapolation is used for IgammaLog (values of mu outside of grid)'
      IgammaLog=I_gammaLog_grid(zMax,orderCUSP_global)-(I_gammaLog_grid(zMax,orderCUSP_global)&
							    -I_gammaLog_grid(zMax+1,orderCUSP_global))*zFrac
    else
      IgammaLog=I_gammaLog_grid(zInt,orderCUSP_global)-(I_gammaLog_grid(zInt,orderCUSP_global)&
							    -I_gammaLog_grid(zInt+1,orderCUSP_global))*zFrac
    end if
  end function IgammaLog
  
    !!! Function interpolate the value of IgammaV (for QUARK), using grids
    !!! Integral over gamma_V
  function IgammaVq(mu)
  
    real*8:: IgammaVq,mu
    integer :: zInt
    real*8::zReal,zFrac   
    
    zReal=20.d0*LOG(2.d0*mu)
    zInt=INT(zReal)
    zFrac=zReal-zInt
    
    !The linear interpolation is used, since as~1/Log[mu] more-or-less
    !It gives accuracy better then 10^{-6} in comparison to exact values
    If (zReal<1) then
      WRITE(*,*) 'TMDR WARNING:: Generic large value evaluated for IgammaVq (mu is close to Landau pole.)'
      IgammaVq=1.d8
    else if(zInt>zMax) then
      !WRITE(*,*) 'TMDR WARNING:: Logarithmical extrapolation is used for IgammaVq (values of mu outside of grid)'
      IgammaVq=LOG(I_gamma_Vq_grid(zMax,orderAD_global)-(I_gamma_Vq_grid(zMax,orderAD_global)&
						  -I_gamma_Vq_grid(zMax+1,orderAD_global))*zFrac)
    else
      IgammaVq=LOG(I_gamma_Vq_grid(zInt,orderAD_global)-(I_gamma_Vq_grid(zInt,orderAD_global)&
						-I_gamma_Vq_grid(zInt+1,orderAD_global))*zFrac)
    end if
  
  end function IgammaVq
  
      !!! Function interpolate the value of IgammaV (for GLUON), using grids
    !!! Integral over gamma_V
  function IgammaVg(mu)
  
    real*8:: IgammaVg,mu
    integer :: zInt
    real*8::zReal,zFrac   
    
    zReal=20.d0*LOG(2.d0*mu)
    zInt=INT(zReal)
    zFrac=zReal-zInt
    
    !The linear interpolation is used, since as~1/Log[mu] more-or-less
    !It gives accuracy better then 10^{-6} in comparison to exact values
    If (zReal<1) then
      WRITE(*,*) 'Warning: Generic large value evaluated for IgammaVg (mu is close to Landau pole.)'
      IgammaVg=1.d8
    else if(zInt>zMax) then
      !WRITE(*,*) 'Warning: Logarithmical extrapolation is used for IgammaVg (values of mu outside of grid)'
      IgammaVg=LOG(I_gamma_Vg_grid(zMax,orderAD_global)-(I_gamma_Vg_grid(zMax,orderAD_global)&
					-I_gamma_Vg_grid(zMax+1,orderAD_global))*zFrac)
    else
      IgammaVg=LOG(I_gamma_Vg_grid(zInt,orderAD_global)-(I_gamma_Vg_grid(zInt,orderAD_global)&
					-I_gamma_Vg_grid(zInt+1,orderAD_global))*zFrac)
    end if
  
  end function IgammaVg
  
  
  !!! A part of the TMD evolution kernel
  ! EXP (\int_mui^muf gamma_f(mu,zeta)dmu/mu
  ! f is flavour
  function TMDEvolutor(zeta,muf,mui,f)
    real*8:: TMDEvolutor, zeta,muf,mui
    integer:: f
    
    
    !common part of evolutor (for quark)
    TMDEvolutor=IgammaLog(muf)-IgammaLog(mui)-(Igamma(muf)-Igamma(mui))*LOG(zeta)
    
    if(f==0) then !gluon
      !we also rescale the common part by casimir
      TMDEvolutor=9d0*TMDEvolutor/4d0+IgammaVg(muf)-IgammaVg(mui)
    else ! quark
      TMDEvolutor=TMDEvolutor+IgammaVq(muf)-IgammaVq(mui)
    end if
    
    TMDEvolutor=EXP(TMDEvolutor)
  end function TMDEvolutor
  
  
  ! The TMD evolution kernel Rapidity
  function TMDD(bT,mu,mu0,f)
    real*8 :: TMDD,bT,mu,mu0
    integer:: f
    
    ! calculate the boundary value
    real*8 :: Dboundary,LL,astrong
    
    LL=2*LOG(bt*mu0*C0_inv_const)
    astrong=As(mu0)
    
  if(mu<=mCHARM) then!!Nf=3
      Dboundary=ddTMD3_q(1,1)*astrong*LL !at any order the leading term is like that
      if(orderAD_global>1) then
	Dboundary=Dboundary+astrong*astrong*(ddTMD3_q(2,2)*LL*LL+ddTMD3_q(2,1)*LL+ddTMD3_q(2,0))
      end if    
      if(orderAD_global>2) then
	Dboundary=Dboundary+astrong*astrong*astrong*(ddTMD3_q(3,3)*LL*LL*LL+ddTMD3_q(3,2)*LL*LL+ddTMD3_q(3,1)*LL+ddTMD3_q(3,0))
      end if
    else if(mu<=mBOTTOM) then!!Nf=4
      Dboundary=ddTMD4_q(1,1)*astrong*LL !at any order the leading term is like that
      if(orderAD_global>1) then
	Dboundary=Dboundary+astrong*astrong*(ddTMD4_q(2,2)*LL*LL+ddTMD4_q(2,1)*LL+ddTMD4_q(2,0))
      end if    
      if(orderAD_global>2) then
	Dboundary=Dboundary+astrong*astrong*astrong*(ddTMD4_q(3,3)*LL*LL*LL+ddTMD4_q(3,2)*LL*LL+ddTMD4_q(3,1)*LL+ddTMD4_q(3,0))	
      end if
    else !!Nf=5
      Dboundary=ddTMD5_q(1,1)*astrong*LL !at any order the leading term is like that
      if(orderAD_global>1) then
	Dboundary=Dboundary+astrong*astrong*(ddTMD5_q(2,2)*LL*LL+ddTMD5_q(2,1)*LL+ddTMD5_q(2,0))
      end if    
      if(orderAD_global>2) then
	Dboundary=Dboundary+astrong*astrong*astrong*(ddTMD5_q(3,3)*LL*LL*LL+ddTMD5_q(3,2)*LL*LL+ddTMD5_q(3,1)*LL+ddTMD5_q(3,0))
      end if
    end if
    
    if(f==0) then !gluon
     TMDD=(Igamma(mu)-Igamma(mu0)+Dboundary)*9.d0/4.d0
    else !quark
      TMDD=Igamma(mu)-Igamma(mu0)+Dboundary
    end if
  end function TMDD
  
    ! The TMD evolution kernel Rrapidity (only boundary)
    ! at threasholds it "jumps"
  function TMDD_boundary(bT,mu,f)
    real*8 :: TMDD_boundary,bT,mu
    integer:: f
    
    ! calculate the boundary value
    real*8 :: Dboundary,LL,astrong
    
    LL=2*LOG(bt*mu*C0_inv_const)
    astrong=As(mu)
    
    if(mu<=mCHARM) then!!Nf=3
      Dboundary=ddTMD3_q(1,1)*astrong*LL !at any order the leading term is like that
      if(orderAD_global>1) then
	Dboundary=Dboundary+astrong*astrong*(ddTMD3_q(2,2)*LL*LL+ddTMD3_q(2,1)*LL+ddTMD3_q(2,0))
      end if    
      if(orderAD_global>2) then
	Dboundary=Dboundary+astrong*astrong*astrong*(ddTMD3_q(3,3)*LL*LL*LL+ddTMD3_q(3,2)*LL*LL+ddTMD3_q(3,1)*LL+ddTMD3_q(3,0))
      end if
    else if(mu<=mBOTTOM) then!!Nf=4
      Dboundary=ddTMD4_q(1,1)*astrong*LL !at any order the leading term is like that
      if(orderAD_global>1) then
	Dboundary=Dboundary+astrong*astrong*(ddTMD4_q(2,2)*LL*LL+ddTMD4_q(2,1)*LL+ddTMD4_q(2,0))
      end if    
      if(orderAD_global>2) then
	Dboundary=Dboundary+astrong*astrong*astrong*(ddTMD4_q(3,3)*LL*LL*LL+ddTMD4_q(3,2)*LL*LL+ddTMD4_q(3,1)*LL+ddTMD4_q(3,0))	
      end if
    else !!Nf=5
      Dboundary=ddTMD5_q(1,1)*astrong*LL !at any order the leading term is like that
      if(orderAD_global>1) then
	Dboundary=Dboundary+astrong*astrong*(ddTMD5_q(2,2)*LL*LL+ddTMD5_q(2,1)*LL+ddTMD5_q(2,0))
      end if
      if(orderAD_global>2) then
	Dboundary=Dboundary+astrong*astrong*astrong*(ddTMD5_q(3,3)*LL*LL*LL+ddTMD5_q(3,2)*LL*LL+ddTMD5_q(3,1)*LL+ddTMD5_q(3,0))
      end if
    end if
    
    if(f==0) then !gluon
      TMDD_boundary=Dboundary*9.d0/4.d0
    else !quark
      TMDD_boundary=Dboundary
    end if
  end function TMDD_boundary
  
  !The TMD evolution kernel R
  ! In full glory
  function TMDR_R(bT,zetaf,muf,zetai,mui,mu0,f)
    real*8::TMDR_R, bT,zetaf,zetai,muf,mui,mu0
    integer:: f
    
    if(bT<0.000001d0) then
    	TMDR_R=0.d0
    else
      TMDR_R=TMDEvolutor(zetaf,muf,mui,f)*(zetaf/zetai)**(-TMDD(bT,mui,mu0,f)-gK_global*bT*bT)
    end if
  end function TMDR_R
  
  !The TMD evolution kernel R at specific parameters
  ! zeta_i=C0^2/bT^2, mui=mu0
  function TMD_R_short(bT,zeta,mu,mu0,f)
    real*8::TMD_R_short, bT,zeta,mu,mu0
    integer:: f
    
    if(bT<0.000001d0) then
      TMD_R_short=0d0
    else
      TMD_R_short=TMDEvolutor(zeta,mu,mu0,f)*&
	      (zeta*bT*bT*C0_inv_const*C0_inv_const)**(-TMDD_boundary(bT,mu0,f)-gK_global*bT*bT)
    end if
  end function TMD_R_short
  
  
  function zetaMU(mu,bT,f)
  real*8:: zetaMU,mu,b,val,alpha,bT,Lmu
  integer::f
  
  val=0d0
      if(f==0) then !gluon
      if(orderZETA_global>=1) then !! NLO+	
	if(mu<mCHARM) then
	val=-1.5d0
	else if (mu<mBOTTOM) then
	val=-25d0/18d0
	else
	val=-23d0/18d0
	end if	
      end if
      if(orderZETA_global>=2) then !!NNLL+
	Lmu=2*LOG(mu*bt*C0_inv_const)
	alpha=As(mu)
	if(mu<mCHARM) then
	val=val+alpha*(3d0/4d0*Lmu**2)
	else if (mu<mBOTTOM) then
	val=val+alpha*(25d0/36d0*Lmu**2)
	else
	val=val+alpha*(23d0/36d0*Lmu**2)
	end if	
      end if
      if(orderZETA_global>=3) then !!NNLO+	
	if(mu<mCHARM) then
	val=val+alpha*(-8.2509634078473d0)
	else if (mu<mBOTTOM) then
	val=val+alpha*(-9.06067674358926d0)
	else
	val=val+alpha*(-9.62347649908429d0)
	end if
      end if
      else !quark
      if(orderZETA_global>=1) then !! NLO+	
	Lmu=2*LOG(mu*bt*C0_inv_const)
	val=-1.5d0!+0.322467033424/Lmu	
      end if
      if(orderZETA_global>=2) then !!NNLL+	
	alpha=As(mu)
	if(mu<mCHARM) then
	val=val+alpha*(3d0/4d0*Lmu**2)
	else if (mu<mBOTTOM) then
	val=val+alpha*(25d0/36d0*Lmu**2)
	else
	val=val+alpha*(23d0/36d0*Lmu**2)
	end if	
      end if
      if(orderZETA_global>=3) then !!NNLO+	
	if(mu<mCHARM) then
	val=val+alpha*(5.25750065352898d0)
	else if (mu<mBOTTOM) then
	val=val+alpha*(5.920953238895728d0)
	else
	val=val+alpha*(6.58440582426247d0)
	end if
      end if
      if(orderZETA_global>=4) then !!NNNLL+	
	if(mu<mCHARM) then
	val=val+alpha**2*(-22.161981123818d0*Lmu + 13.847796699183d0*Lmu**2 + 1.6875d0*Lmu**3)
	else if (mu<mBOTTOM) then
	val=val+alpha**2*(-24.121175937692d0*Lmu + 12.068947560972d0*Lmu**2 + 1.4467592592593d0*Lmu**3)
	else
	val=val+alpha**2*(-25.504239064322d0*Lmu + 10.413555212884d0*Lmu**2 + 1.224537037037d0*Lmu**3)
	end if
      end if
      end if
      zetaMU=mu*C0_const/bT*EXP(-val)
      !Lmu=2*LOG(mu*bt*C0_inv_const)
      !zetaMU=C0_const*C0_const/bT/bT*EXP(Lmu/2d0-val)
  end function zetaMU
  
  !The TMD evolution kernel R at 
  !\zeta=\zeta_\mu,
  !\mu_0=\mu_i
  function TMDR_full_zetaP(bT,zetaf,muf,mui,mu0,f)
    real*8::TMDR_full_zetaP, bT,zetaf,muf,mui,mu0
    integer:: f
    
    if(bT<0.000001d0) then
    	TMDR_full_zetaP=0.d0
    else
      
      TMDR_full_zetaP=TMDEvolutor(zetaf,muf,mui,f)*(zetaf/zetaMU(mui,bT,f))**(-TMDD(bT,mui,mu0,f)-gK_global*bT*bT)
    end if
  end function TMDR_full_zetaP
  
  
    !The TMD evolution kernel R at 
  !\zeta=\zeta_\mu,
  !\mu_0=\mu_i
  function TMDR_zetaP(bT,zetaf,muf,mui,f)
    real*8::TMDR_zetaP, bT,zetaf,muf,mui
    integer:: f
        
    if(bT<0.000001d0) then
    	TMDR_zetaP=0.d0
    else 
    
      TMDR_zetaP=TMDEvolutor(zetaf,muf,mui,f)*&
	      (zetaf/zetaMU(mui,bT,f))**(-TMDD_boundary(bT,mui,f)-gK_global*bT*bT)
    end if
  end function TMDR_zetaP
  
end module TMDR


! program test
! 
! use TMDR
! 
! implicit none
!   
!   call TMDR_Initialize('NNLO',"NNNLO","NNLO",'NNLO')
!   
!   write(*,*) TMDR_zetaP(0.1d0,91d0**2,91d0,5d0,1)
! 
! end program test
