!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe 1.0
!
!	Evaluation of the TMD cross-section
!	Current version has only DY-like cross-sections
!	
!	if you use this module please, quote arXiv:1706.01473
!
!	ver 1.0: release (AV, 10.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
module TMDX

use TMDs
use LeptonCutsDY

implicit none
  private
  
	!!!!zeros of bessel function!!
    real*8,parameter,dimension(1:64) :: BesselJ0Zero=&
    (/2.404825557695773, 5.5200781102863115, 8.653727912911013, &
	11.791534439014281, 14.930917708487787, 18.071063967910924, &
	 21.21163662987926, 24.352471530749302, 27.493479132040253, &
 	30.634606468431976, 33.77582021357357, 36.917098353664045, &
 	40.05842576462824, 43.19979171317673, 46.341188371661815,& 
 	49.482609897397815, 52.624051841115, 55.76551075501998, &
 	58.90698392608094, 62.048469190227166, 65.18996480020687,& 
 	68.3314693298568, 71.47298160359374, 74.61450064370183, &
 	77.75602563038805, 80.89755587113763, 84.0390907769382, &
 	87.18062984364116, 90.32217263721049, 93.46371878194478, &
 	96.60526795099626, 99.7468198586806, 102.8883742541948, &
 	106.02993091645162, 109.17148964980538, 112.3130502804949, &
 	115.45461265366694, 118.59617663087253, 121.73774208795096, &
 	124.87930891323295, 128.02087700600833, 131.1624462752139, &
 	134.30401663830546, 137.44558802028428, 140.58716035285428, &
 	143.72873357368974, 146.87030762579664, 150.01188245695477, &
 	153.15345801922788, 156.29503426853353, 159.43661116426316, &
 	162.57818866894667, 165.71976674795502, 168.86134536923583, &
 	172.0029245030782, 175.14450412190274, 178.28608420007376, &
 	181.42766471373105, 184.5692456406387, 187.71082696004936, &
 	190.85240865258152, 193.99399070010912, 197.1355730856614, &
 	200.2771557933324/)
 	
 	real*8,parameter,dimension(1:64) :: OGATA_weights=&
 	(/0.9822341167218513, 0.996095171243873, 0.9983661220824326, &
 	0.9991115104807027, 0.9994434412453229, 0.9996191732821181, &
 	0.9997232113735499, 0.9997898172483115, 0.9998349989971018, &
 	0.9998670439582888, 0.9998905896964104, 0.9999083950665695, &
 	0.9999221843802542, 0.9999330801564746, 0.9999418385663339, &
 	0.9999489840430771, 0.9999548895439107, 0.9999598261634556, &
 	0.9999639947771565, 0.999967546784798, 0.9999705980425174, &
 	0.9999732384242627, 0.9999755385120204, 0.9999775543594231, &
 	0.9999793309376261, 0.9999809046641152, 0.9999823052831136, &
 	0.9999835572808426, 0.9999846809626194, 0.9999856932810783, &
 	0.99998660847913, 0.9999874385935336, 0.9999881938525907, &
 	0.9999888829926477, 0.9999895135118083, 0.9999900918747109, &
 	0.9999906236788553, 0.9999911137905217, 0.9999915664564617, &
 	0.9999919853961932, 0.9999923738786343, 0.9999927347860547, &
 	0.9999930706676811, 0.9999933837848324, 0.9999936761490745, &
 	0.9999939495546002, 0.9999942056058223, 0.9999944457409604, &
 	0.9999946712522773, 0.9999948833035018, 0.9999950829448677, &
 	0.9999952711261438, 0.9999954487079464, 0.9999956164715993, &
 	0.9999957751277381, 0.999995925323851, 0.9999960676508924, &
 	0.999996202649105, 0.9999963308131538, 0.9999964525966623, &
 	0.9999965684162345, 0.999996678655019, 0.9999967836658823, &
 	0.999996883774239/)
  
  !The variables for all parameters of the model!
   real*8:: Q_global,s_global,y_global,zetaA_global,zetaB_global,qT_global,xA_global,xB_global,prefactor_global
  !!other global parameters see SetXParameters
  integer:: process_global
  integer:: orderH_global
  logical:: IsySymmetric !! indicates that process y-symmetric
  logical:: includeCuts
  
  real*8::c2_global,muHard_global
  
  !!cut parameters
  real*8::pT_global, eta_max_global, eta_min_global
!  real*8, parameter :: C0_inv_const=0.890536208995099d0  !=Exp[gamma_E]/2
  
  public::TMDX_XSetup,TMDX_SetNPParameters,TMDX_Initialize,SetCuts,InitializeScaleVariations
  public::  CalculateXsection,&
    CalculateXsection_Yint,CalculateXsection_YintComplete,&
    CalculateXsection_Qint,CalculateXsection_Qint_Yint,&
    CalculateXsection_PTint_Yint,CalculateXsection_PTint_Qint_Yint,CalculateXsection_PTint_YintComplete
    
  interface CalculateXsection
    module procedure CalculateXsection_central,CalculateXsection_withErr
  end interface
 
 interface CalculateXsection_Yint
    module procedure CalculateXsection_Yint_central,CalculateXsection_Yint_withErr
  end interface
  
  interface CalculateXsection_YintComplete
    module procedure CalculateXsection_YintComplete_central,CalculateXsection_YintComplete_withErr
  end interface
  
  interface CalculateXsection_Qint
    module procedure CalculateXsection_Qint_central,CalculateXsection_Qint_withErr
  end interface
  
  interface CalculateXsection_Qint_Yint
    module procedure CalculateXsection_Qint_Yint_central,CalculateXsection_Qint_Yint_withErr
  end interface
  
  interface CalculateXsection_PTint_Yint
    module procedure CalculateXsection_PTint_Yint_central,CalculateXsection_PTint_Yint_withErr
  end interface
  
  interface CalculateXsection_PTint_YintComplete
    module procedure CalculateXsection_PTint_YintComplete_central,CalculateXsection_PTint_YintComplete_withErr
  end interface
  
  interface CalculateXsection_PTint_Qint_Yint
    module procedure CalculateXsection_PTint_Qint_Yint_central,CalculateXsection_PTint_Qint_Yint_withErr
  end interface
contains
  
  !!Just passes the initialization to subpackages
  !! This also set orders. Orders cannot be changes afterwards
  subroutine TMDX_Initialize(orderTMD,orderH)
  character(len=*)::orderTMD,orderH
  
  write(*,*) '--- arTeMiDe.TMDX ver 1.0: .... initialization'
  
  call TMDs_Initialize(orderTMD)  
     SELECT CASE(orderH)
      CASE ("LO")
	orderH_global=0
      CASE ("NLO")
	orderH_global=1
      CASE ("NNLO")
	orderH_global=2
      CASE DEFAULT
	write(*,*) 'WARNING arTeMiDe.TMDX:try to set unknown order. Switch to NLO.'
	orderH_global=1
     END SELECT
     
     includeCuts=.false.
     c2_global=1d0
     
   write(*,*) '--- arTeMiDe.TMDX ver 1.0: .... initialized'
  end subroutine TMDX_Initialize
  
  
  !!!!Call this after TMD initializetion but before NP, and X parameters
  subroutine InitializeScaleVariations(c1_in,c2_in,c3_in,c4_in)
    real*8::c1_in,c2_in,c3_in,c4_in
    
    call TMDs_SetScaleVariations(c1_in,c3_in,c4_in)
    
    if(c2_in<0.1d0 .or. c2_in>10.d0) then
    write(*,*) 'TMDX WARNING: variation in c2 is enourmous. c2 is set to 1'
    else
    c2_global=c2_in
    end if
    
    muHard_global=Q_global*c2_global
    call Xprefactor_byUser()
    
  end subroutine InitializeScaleVariations
  
  !!Just passes settting of NP parameters to subpackage
  subroutine TMDX_SetNPParameters(bmax,gK,lambda)
    real*8::bmax,gK
    real*8::lambda(:)
    call TMDs_SetNPParameters(bmax,gK,lambda)
  end subroutine TMDX_SetNPParameters
  
  !!sets the cuts
  !! argument includeCuts_in=logical, if .true. will add to calculation the evaluation of cut leptonic tensor
  !! call BEFORE SetXParameters
  subroutine SetCuts(include_arg,pT_arg,eta_min,eta_max)
  logical:: include_arg
  real*8:: pT_arg,eta_max,eta_min
  
  includeCuts=include_arg
  
  pT_global=pT_arg
  eta_max_global=eta_max
  eta_min_global=eta_min
  
  end subroutine SetCuts
  
  !sets the main parameters of cross-section (x,zeta,etc)
  !the variables process defines the type of process
  subroutine TMDX_XSetup(s,Q,y,process)
    real*8::s,Q,y
    integer::process
   
    s_global=s
    Q_global=Q
    y_global=y
    
    !for a moment we fix like that
    zetaA_global=Q**2
    zetaB_global=Q**2
    
    xA_global=Q/SQRT(s)*EXP(y)
    xB_global=Q/SQRT(s)*EXP(-y)
    
    process_global=process
    
    muHard_global=Q_global*c2_global
   
    call Xprefactor_byUser()
    
    if(includeCuts) then
      call SetCutParameters(Q_global,y_global,pT_global,eta_min_global,eta_max_global)
    end if
    
    
  end subroutine TMDX_XSetup


  !!! hard coefficeint taken from 1004.3653 up to 2-loop
  !!! it takes global values of Q,order
  !!! fro a moment mu=Q
  function HardCoefficientDY()
    real*8::HardCoefficientDY,LQ!=Log[Q^2/mu^2]=-2Log[c1]
    
    HardCoefficientDY=1.d0
    if(orderH_global>=1) then
      LQ=-2d0*LOG(c2_global)
      HardCoefficientDY=HardCoefficientDY+GetAs(muHard_global)*&
      (9.372102581166892d0 + 8d0*LQ-2.6666666666666665d0*LQ**2)
    end if
    
    if(orderH_global>=2) then
      HardCoefficientDY=HardCoefficientDY+GetAs(muHard_global)**2*&
      (379.42800778694584d0 + 19.871427703248656d0*LQ - 53.33999514687342d0*LQ**2 & 
      - 13.333333333333334d0*LQ**3 + 3.5555555555555554d0*LQ**4)
    end if    
  end function HardCoefficientDY
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !This is Fourier of F F e(-qT bt)/4pi
  !we evaluate here by OGATA quadrature
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  subroutine intXsec_OGATA(integral)
  real*8::integral,eps,inter
  integer::k
  real*8,parameter::hOGATA=0.001d0
  real*8::v1,v2,v3,v4
  integral=0d0
  
  if(qT_global<0.0000001d0) then
  
  integral=0d0
  
  else
  
  !!!in the case of lost convergence we return huge number (divergent xSec)
  if(TMDs_IsconvergenceLost()) then	
	integral=1d100		
  else
  
  v1=1d0
  v2=1d0
  v3=1d0
  v4=1d0
  do k=1,64!!! maximum of number of bessel roots preevaluated in the head
    inter=psi_OGATA(hOGATA*BesselJ0Zero(k))/hOGATA
    eps=OGATA_weights(k)*&
      inter*XIntegrand(inter/qT_global)*BESSEL_J0(inter)*psiPrime_OGATA(hOGATA*BesselJ0Zero(k))
    integral=integral+eps
    if(k>8) then
      v4=v3
      v3=v2
      v2=v1
      v1=ABS(eps)
      !write(*,*) k, eps
      if(v1+v2+v3+v4<0.0000001d0) exit
    end if
  end do
   if(k==64 .and. (v1+v2+v3+v4>0.001d0)) then	
    WRITE(*,*) 'WARNING arTeMiDe.TMDX: OGATA quadrature diverge. TMD decaing too slow? Last point bt= '&
	  ,inter/qT_global, 'W=',XIntegrand(inter/qT_global)
    call TMDs_convergenceISlost()    
   end if
   
  integral=integral*1.5707963267948966d0/(qT_global**2)*cutPrefactor_byUser(qT_global)
  
  
  end if
  
  end if
  
  end subroutine intXsec_OGATA
  
  !!!!!these are two additional functions for OGATA quadrature
  function psi_OGATA(t)
  real*8::t,psi_OGATA
  psi_OGATA=t*TANH(1.5707963267948966d0*SINH(t))
  end function psi_OGATA
  
  function psiPrime_OGATA(t)
  real*8::psiPrime_OGATA,t,inter
  if(t>20d0) then
  psiPrime_OGATA=1
  else
  inter=3.141592653589793d0*SINH(t)
  psiPrime_OGATA=(3.141592653589793d0*t*COSH(t)+SINH(inter))/(1d0+COSH(inter))
  end if
  end function psiPrime_OGATA
  
  
  !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  subroutine CalculateXsection_central(X_list,qt_List)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    integer :: i,length
    real*8 :: intermidiateVar 
    
    length=size(qt_list)
    
     do i=1,length
	!total_counter=0
	qT_global=qt_List(i)	
       call intXsec_OGATA(intermidiateVar)
       X_List(i)=prefactor_global*intermidiateVar
     end do
  
  end subroutine CalculateXsection_central
  
    !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  subroutine CalculateXsection_withErr(X_list,Xlow_list,Xup_list,qt_List)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, intent(out) :: Xlow_list(:)
    integer :: i,length
    real*8 :: intermidiateVar
    real*8, dimension(1:6) :: interErrors
    
    length=size(qt_list)
    
     do i=1,length
	!total_counter=0
	qT_global=qt_List(i)
       call intXsec_OGATA(intermidiateVar)
       X_List(i)=prefactor_global*intermidiateVar
       
       !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call intXsec_OGATA(intermidiateVar)
       interErrors(1)=prefactor_global*intermidiateVar
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call intXsec_OGATA(intermidiateVar)
       interErrors(2)=prefactor_global*intermidiateVar
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call intXsec_OGATA(intermidiateVar)
       interErrors(3)=prefactor_global*intermidiateVar
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call intXsec_OGATA(intermidiateVar)
       interErrors(4)=prefactor_global*intermidiateVar
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call intXsec_OGATA(intermidiateVar)
       interErrors(5)=prefactor_global*intermidiateVar
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call intXsec_OGATA(intermidiateVar)
       interErrors(6)=prefactor_global*intermidiateVar
       
       Xup_list(i)=MAXVAL(interErrors)
       Xlow_list(i)=MINVAL(interErrors)
     end do
     !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_withErr
  
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!FUNCTIONS CALCULATING CROSS-SECTIONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!PARTIALLY INEGRATED!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  !!!!Evaluate greed and calculate the list of cross-section points integrated over y in given range
  !!!!Automatically makes symmetric integration if sigma is y-symmetric
  !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  subroutine CalculateXsection_Yint_central(X_list,qt_List,ymin_in,ymax_in)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, dimension (:), allocatable :: inter_list
    real*8 :: ymin, ymax,ymin_in,ymax_in,h
    integer,parameter::num=8!!!number of devisions (such that it should be /4)
    integer :: i
    
    if(IsySymmetric .and. (ABS(ymax_in+ymin_in)<0.0001)) then!!! symetric integral
      !!! chech that y in the proper range      
      ymax=-1/2d0*LOG(Q_global**2/s_global)-0.000000001d0
      if(ymax_in < ymax) then
	ymax=ymax_in
      end if
      
      h=ymax/REAL(num/2d0)!!step
      
      allocate(inter_list(1:size(qt_list)))
    
      call TMDX_XSetup(s_global,Q_global,0d0,process_global)
      call CalculateXsection_central(inter_list,qt_List)
      X_list=inter_list
    
      do i=1,(num/2)-1
	call TMDX_XSetup(s_global,Q_global,REAL(i)*h,process_global)
	call CalculateXsection_central(inter_list,qt_List)
	if(MOD(i,2)==1) then
	  X_list=X_list+4d0*inter_list
	else
	  X_list=X_list+2d0*inter_list
	end if
      end do
      
      call TMDX_XSetup(s_global,Q_global,ymax,process_global)!last point
      call CalculateXsection_central(inter_list,qt_List)
      X_list=X_list+inter_list
      
      X_list=2d0*h/3d0*X_list!!!(factor 2 due to symmetry)
      
    else !!!non-symmetric integral!!!!!!!!
    
      !!! chech that y in the proper range
      ymin=1/2d0*LOG(Q_global**2/s_global)+0.000000001d0
      ymax=-1/2d0*LOG(Q_global**2/s_global)-0.000000001d0
      if(ymax_in < ymax) then
	ymax=ymax_in
      end if
      if(ymin_in > ymin) then
	ymin=ymin_in
      end if
      
      h=(ymax-ymin)/REAL(num)!!step
      
      allocate(inter_list(1:size(qt_list)))
    
      call TMDX_XSetup(s_global,Q_global,ymin,process_global)
      call CalculateXsection_central(inter_list,qt_List)
      X_list=inter_list
    
      do i=1,num-1
	call TMDX_XSetup(s_global,Q_global,ymin+REAL(i)*h,process_global)
	call CalculateXsection_central(inter_list,qt_List)
	if(MOD(i,2)==1) then
	  X_list=X_list+4d0*inter_list
	else
	  X_list=X_list+2d0*inter_list
	end if
      end do
      
      call TMDX_XSetup(s_global,Q_global,ymax,process_global)!last point
      call CalculateXsection_central(inter_list,qt_List)
      X_list=X_list+inter_list
    
      X_list=h/3d0*X_list
      
    end if
    
    deallocate(inter_list)
    
  end subroutine CalculateXsection_Yint_central
  
  subroutine CalculateXsection_Yint_withErr(X_list,Xlow_list,Xup_list,qt_List,ymin_in,ymax_in)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    real*8 :: ymin_in,ymax_in
    integer::length,i
    
    call CalculateXsection_Yint_central(X_list,qt_List,ymin_in,ymax_in)!central value
    
    length=size(qt_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_Yint_central(X1,qt_List,ymin_in,ymax_in)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_Yint_central(X2,qt_List,ymin_in,ymax_in)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_Yint_central(X3,qt_List,ymin_in,ymax_in)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_Yint_central(X4,qt_List,ymin_in,ymax_in)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_Yint_central(X5,qt_List,ymin_in,ymax_in)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_Yint_central(X6,qt_List,ymin_in,ymax_in)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_Yint_withErr
  
  !!!!Evaluate greed and calculate the list of  cross-section points integrated over y in the full range
  !!!!Automatically makes symmetric integration if sigma is y-symmetric
  !!!!The utmost points of integration are set to 0
  !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  subroutine CalculateXsection_YintComplete_central(X_list,qt_List)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, dimension (:), allocatable :: inter_list
    real*8 :: h,ymin, ymax
    integer,parameter::num=8!!!number of devisions (such that it can be /4)
    integer :: i
    
    if(IsySymmetric) then!!! symetric integral
      !!! chech that y in the proper range      
      ymax=-1/2d0*LOG(Q_global**2/s_global)-0.000000001d0
      
      h=ymax/REAL(num/2d0)!!step
      
      allocate(inter_list(1:size(qt_list)))
    
      call TMDX_XSetup(s_global,Q_global,0d0,process_global)
      call CalculateXsection_central(inter_list,qt_List)
      X_list=inter_list
    
      do i=1,(num/2)-1
	call TMDX_XSetup(s_global,Q_global,REAL(i)*h,process_global)
	call CalculateXsection_central(inter_list,qt_List)
	if(MOD(i,2)==1) then
	  X_list=X_list+4d0*inter_list
	else
	  X_list=X_list+2d0*inter_list
	end if
      end do
      
      !!!X_list=X_list+inter_list!!!utmost point is zero
      
      X_list=2d0*h/3d0*X_list!!!(factor 2 due to symmetry)
      
    else !!!non-symmetric integral!!!!!!!!
    
      !!! chech that y in the proper range
      ymin=1/2d0*LOG(Q_global**2/s_global)+0.000000001d0
      ymax=-1/2d0*LOG(Q_global**2/s_global)-0.000000001d0
      
      h=(ymax-ymin)/REAL(num)!!step
      
      allocate(inter_list(1:size(qt_list)))
    
      X_list=0d0*inter_list!!!utmost point is zero
    
      do i=1,num-1
	call TMDX_XSetup(s_global,Q_global,ymin+REAL(i)*h,process_global)
	call CalculateXsection_central(inter_list,qt_List)
	if(MOD(i,2)==1) then
	  X_list=X_list+4d0*inter_list
	else
	  X_list=X_list+2d0*inter_list
	end if
      end do
     
      !X_list=X_list+inter_list!!!utmost point is zero
    
      X_list=h/3d0*X_list
      
    end if
    
    deallocate(inter_list)
  
  end subroutine CalculateXsection_YintComplete_central
  
  subroutine CalculateXsection_YintComplete_withErr(X_list,Xlow_list,Xup_list,qt_List)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    integer::length,i
    
    call CalculateXsection_YintComplete_central(X_list,qt_List)!central value
    
    length=size(qt_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_YintComplete_central(X1,qt_List)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_YintComplete_central(X2,qt_List)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_YintComplete_central(X3,qt_List)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_YintComplete_central(X4,qt_List)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_YintComplete_central(X5,qt_List)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_YintComplete_central(X6,qt_List)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_YintComplete_withErr
  
  !!!!Evaluate greed and calculate the list of  cross-section points integrated over Q^2 (i.e. 2 Q dQ) in given range
  !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  !! The integration is done by Simson dividing onlt 4 parts
  subroutine CalculateXsection_Qint_central(X_list,qt_List,Q_min,Q_max)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, dimension (:), allocatable :: inter_list
    real*8 :: Q_min, Q_max,h
    integer,parameter:: num=4!!!number of steps
    integer::i
  
    h=(Q_max-Q_min)/REAL(num) !!step
    
    
    allocate(inter_list(1:size(qt_list)))
    
    call TMDX_XSetup(s_global,Q_min,y_global,process_global)
    call CalculateXsection_central(inter_list,qt_List)
    X_list=2d0*Q_min*inter_list
    !X_list=inter_list
    
    do i=1,num-1
	call TMDX_XSetup(s_global,Q_min+REAL(i)*h,y_global,process_global)
	call CalculateXsection_central(inter_list,qt_List)
	if(MOD(i,2)==1) then
	  X_list=X_list+8d0*(Q_min+REAL(i)*h)*inter_list
	else
	  X_list=X_list+4d0*(Q_min+REAL(i)*h)*inter_list
	end if
    end do
    
    call TMDX_XSetup(s_global,Q_max,y_global,process_global)
    call CalculateXsection_central(inter_list,qt_List)
    X_list=X_list+(2d0*Q_max)*inter_list
    
    X_list=h/3d0*X_list
    deallocate(inter_list)
  end subroutine CalculateXsection_Qint_central
  
  
  subroutine CalculateXsection_Qint_withErr(X_list,Xlow_list,Xup_list,qt_List,Q_min,Q_max)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    real*8 :: Q_min, Q_max
    integer::length,i
    
    call CalculateXsection_Qint_central(X_list,qt_List,Q_min,Q_max)!central value
    
    length=size(qt_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_Qint_central(X1,qt_List,Q_min,Q_max)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_Qint_central(X2,qt_List,Q_min,Q_max)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_Qint_central(X3,qt_List,Q_min,Q_max)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_Qint_central(X4,qt_List,Q_min,Q_max)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_Qint_central(X5,qt_List,Q_min,Q_max)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_Qint_central(X6,qt_List,Q_min,Q_max)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_Qint_withErr
  
  
  !!!!Evaluate greed and calculate cross-section
  !!!! integrated over everything(!!!!)
  !!!! integrate by simpsons dividing  (4 x 6)
  subroutine CalculateXsection_Qint_Yint_central(X_list,qt_List,Q_min,Q_max,ymin_in,ymax_in)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, dimension (:), allocatable :: inter_list
    real*8 :: Q_min, Q_max,h,ymax_in,ymin_in
    integer,parameter:: num=4!!!number of steps
    integer::i
  
   h=(Q_max-Q_min)/REAL(num) !!step
    
    allocate(inter_list(1:size(qt_list)))
    
    call TMDX_XSetup(s_global,Q_min,y_global,process_global)
    call CalculateXsection_Yint_central(inter_list,qt_List,ymin_in,ymax_in)
    X_list=2d0*Q_min*inter_list
    !X_list=inter_list
    
    do i=1,num-1
	call TMDX_XSetup(s_global,Q_min+REAL(i)*h,y_global,process_global)
	call CalculateXsection_Yint_central(inter_list,qt_List,ymin_in,ymax_in)
	if(MOD(i,2)==1) then
	  X_list=X_list+8d0*(Q_min+REAL(i)*h)*inter_list
	else
	  X_list=X_list+4d0*(Q_min+REAL(i)*h)*inter_list
	end if
    end do
    
    call TMDX_XSetup(s_global,Q_max,y_global,process_global)
    call CalculateXsection_Yint_central(inter_list,qt_List,ymin_in,ymax_in)
    X_list=X_list+(2d0*Q_max)*inter_list
    
    X_list=h/3d0*X_list
    deallocate(inter_list)
  
  end subroutine CalculateXsection_Qint_Yint_central
  
  
   subroutine CalculateXsection_Qint_Yint_withErr(X_list,Xlow_list,Xup_list,qt_List,Q_min,Q_max,ymin_in,ymax_in)
    real*8, intent(out) :: qt_list(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    real*8 :: Q_min, Q_max,ymax_in,ymin_in
    integer::length,i
    
    call CalculateXsection_Qint_Yint_central(X_list,qt_List,Q_min,Q_max,ymin_in,ymax_in)!central value
    
    length=size(qt_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_Qint_Yint_central(X1,qt_List,Q_min,Q_max,ymin_in,ymax_in)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_Qint_Yint_central(X2,qt_List,Q_min,Q_max,ymin_in,ymax_in)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_Qint_Yint_central(X3,qt_List,Q_min,Q_max,ymin_in,ymax_in)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_Qint_Yint_central(X4,qt_List,Q_min,Q_max,ymin_in,ymax_in)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_Qint_Yint_central(X5,qt_List,Q_min,Q_max,ymin_in,ymax_in)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_Qint_Yint_central(X6,qt_List,Q_min,Q_max,ymin_in,ymax_in)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_Qint_Yint_withErr
  
  !!!!Evaluate greed and calculate the list of  cross-section points integrated over PT-bins/size of bin
  !! Evaluates y-avaraged in given region
  !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  !! The integration is done by Simson dividing onlt 4 parts
  subroutine CalculateXsection_PTint_Yint_central(X_list,qtLow_List,qtHigh_List,ymin_in,ymax_in)
  real*8, intent(out) :: X_list(:)
  real*8, intent(out) :: qtLow_List(:)
  real*8, intent(out) :: qtHigh_List(:)
  real*8, dimension (:), allocatable :: inter_list,h_list,qt_list_to_integrate
  real*8::ymin_in,ymax_in
  integer::i
  
  allocate(inter_list(1:(5*size(qtLow_List))))!!! list of cross-sections is 5 times longer for integration
  allocate(qt_list_to_integrate(1:(5*size(qtLow_List))))!!! list of qt's is 5 times longer for integration
  allocate(h_list(1:size(qtLow_List)))!!!list of steps
  
  call TMDX_XSetup(s_global,Q_global,y_global,process_global)
  
  h_list=(qtHigh_List-qtLow_List)/4d0 !!steps
    
  do i=1,size(qtLow_List)
    qt_list_to_integrate((i-1)*5+1)=qtLow_List(i)
    qt_list_to_integrate((i-1)*5+2)=qtLow_List(i)+h_list(i)
    qt_list_to_integrate((i-1)*5+3)=qtLow_List(i)+2*h_list(i)
    qt_list_to_integrate((i-1)*5+4)=qtLow_List(i)+3*h_list(i)
    qt_list_to_integrate((i-1)*5+5)=qtLow_List(i)+4*h_list(i)
  end do

    call CalculateXsection_Yint_central(inter_list,qt_list_to_integrate,ymin_in,ymax_in)
  
  inter_list=2.d0*qt_list_to_integrate*inter_list
  
  do i=1,size(qtLow_List)
    X_list(i)=inter_list((i-1)*5+1)&
	+4d0*inter_list((i-1)*5+2)&
	+2d0*inter_list((i-1)*5+3)&
	+4d0*inter_list((i-1)*5+4)&
	+inter_list((i-1)*5+5)
  end do

    X_list=h_list/3d0*X_list
    
    deallocate(h_list)
    deallocate(qt_list_to_integrate)
    deallocate(inter_list)
  end subroutine CalculateXsection_PTint_Yint_central
  
  
   subroutine CalculateXsection_PTint_Yint_withErr(X_list,Xlow_list,Xup_list,qtLow_List,qtHigh_List,ymin_in,ymax_in)
    real*8, intent(out) :: qtLow_List(:)
    real*8, intent(out) :: qtHigh_List(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    real*8 :: ymax_in,ymin_in
    integer::length,i
    
    call CalculateXsection_PTint_Yint_central(X_list,qtLow_List,qtHigh_List,ymin_in,ymax_in)!central value
    
    length=size(qtLow_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_PTint_Yint_central(X1,qtLow_List,qtHigh_List,ymin_in,ymax_in)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_PTint_Yint_central(X2,qtLow_List,qtHigh_List,ymin_in,ymax_in)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_PTint_Yint_central(X3,qtLow_List,qtHigh_List,ymin_in,ymax_in)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_PTint_Yint_central(X4,qtLow_List,qtHigh_List,ymin_in,ymax_in)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_PTint_Yint_central(X5,qtLow_List,qtHigh_List,ymin_in,ymax_in)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_PTint_Yint_central(X6,qtLow_List,qtHigh_List,ymin_in,ymax_in)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_PTint_Yint_withErr
  
  
  !!!!Evaluate greed and calculate the list of  cross-section points integrated over PT-bins/size of bin
  !! Evaluates y-avaraged in over all region
  !!qt_list is the list of requred qt -point,
  !! X_list is variable to store results (should be of the same dimension as qt_list)
  !! The integration is done by Simson dividing onlt 4 parts
  subroutine CalculateXsection_PTint_YintComplete_central(X_list,qtLow_List,qtHigh_List)
  real*8, intent(out) :: X_list(:)
  real*8, intent(out) :: qtLow_List(:)
  real*8, intent(out) :: qtHigh_List(:)
  real*8, dimension (:), allocatable :: inter_list,h_list,qt_list_to_integrate
  integer::i
  
  allocate(inter_list(1:(5*size(qtLow_List))))!!! list of cross-sections is 5 times longer for integration
  allocate(qt_list_to_integrate(1:(5*size(qtLow_List))))!!! list of qt's is 5 times longer for integration
  allocate(h_list(1:size(qtLow_List)))!!!list of steps
  
  call TMDX_XSetup(s_global,Q_global,y_global,process_global)
  
  h_list=(qtHigh_List-qtLow_List)/4d0 !!steps
    
  do i=1,size(qtLow_List)
    qt_list_to_integrate((i-1)*5+1)=qtLow_List(i)
    qt_list_to_integrate((i-1)*5+2)=qtLow_List(i)+h_list(i)
    qt_list_to_integrate((i-1)*5+3)=qtLow_List(i)+2*h_list(i)
    qt_list_to_integrate((i-1)*5+4)=qtLow_List(i)+3*h_list(i)
    qt_list_to_integrate((i-1)*5+5)=qtLow_List(i)+4*h_list(i)
  end do


    call CalculateXsection_YintComplete_central(inter_list,qt_list_to_integrate)

  inter_list=2.d0*qt_list_to_integrate*inter_list
  
  do i=1,size(qtLow_List)
    X_list(i)=inter_list((i-1)*5+1)&
	+4d0*inter_list((i-1)*5+2)&
	+2d0*inter_list((i-1)*5+3)&
	+4d0*inter_list((i-1)*5+4)&
	+inter_list((i-1)*5+5)
  end do

    X_list=h_list/3d0*X_list
    
    deallocate(h_list)
    deallocate(qt_list_to_integrate)
    deallocate(inter_list)
  end subroutine CalculateXsection_PTint_YintComplete_central

  
   subroutine CalculateXsection_PTint_YintComplete_withErr(X_list,Xlow_list,Xup_list,qtLow_List,qtHigh_List)
    real*8, intent(out) :: qtLow_List(:)
    real*8, intent(out) :: qtHigh_List(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    integer::length,i
    
    call CalculateXsection_PTint_YintComplete_central(X_list,qtLow_List,qtHigh_List)!central value
    
    length=size(qtLow_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_PTint_YintComplete_central(X1,qtLow_List,qtHigh_List)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_PTint_YintComplete_central(X2,qtLow_List,qtHigh_List)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_PTint_YintComplete_central(X3,qtLow_List,qtHigh_List)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_PTint_YintComplete_central(X4,qtLow_List,qtHigh_List)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_PTint_YintComplete_central(X5,qtLow_List,qtHigh_List)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_PTint_YintComplete_central(X6,qtLow_List,qtHigh_List)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_PTint_YintComplete_withErr
  
  
  !!!!Evaluate greed and calculate cross-section
  !!!! integrated over everything(!!!!)
  !!!! integrate by simpsons dividing  (4 x 6)
  subroutine CalculateXsection_PTint_Qint_Yint_central(X_list,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
  real*8, intent(out) :: X_list(:)
  real*8, intent(out) :: qtLow_List(:)
  real*8, intent(out) :: qtHigh_List(:)
  real*8, dimension (:), allocatable :: inter_list,h_list,qt_list_to_integrate
  real*8::ymax_in,Qmin,Qmax,ymin_in
  integer::i
  
  allocate(inter_list(1:(5*size(qtLow_List))))!!! list of cross-sections is 5 times longer for integration
  allocate(qt_list_to_integrate(1:(5*size(qtLow_List))))!!! list of qt's is 5 times longer for integration
  allocate(h_list(1:size(qtLow_List)))!!!list of steps
  
  call TMDX_XSetup(s_global,Q_global,y_global,process_global)
  
  h_list=(qtHigh_List-qtLow_List)/4d0 !!steps
  
  do i=1,size(qtLow_List)
    qt_list_to_integrate((i-1)*5+1)=qtLow_List(i)
    qt_list_to_integrate((i-1)*5+2)=qtLow_List(i)+h_list(i)
    qt_list_to_integrate((i-1)*5+3)=qtLow_List(i)+2*h_list(i)
    qt_list_to_integrate((i-1)*5+4)=qtLow_List(i)+3*h_list(i)
    qt_list_to_integrate((i-1)*5+5)=qtLow_List(i)+4*h_list(i)
  end do
  call CalculateXsection_Qint_Yint_central(inter_list,qt_list_to_integrate,Qmin,Qmax,ymin_in,ymax_in)
  inter_list=2.d0*qt_list_to_integrate*inter_list
  
  do i=1,size(qtLow_List)
    X_list(i)=inter_list((i-1)*5+1)&
	+4d0*inter_list((i-1)*5+2)&
	+2d0*inter_list((i-1)*5+3)&
	+4d0*inter_list((i-1)*5+4)&
	+inter_list((i-1)*5+5)
  end do

    X_list=h_list/3d0*X_list
    
    deallocate(h_list)
    deallocate(qt_list_to_integrate)
    deallocate(inter_list)
  end subroutine CalculateXsection_PTint_Qint_Yint_central
 
 subroutine CalculateXsection_PTint_Qint_Yint_withErr(X_list,Xlow_list,Xup_list,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
    real*8, intent(out) :: qtLow_List(:)
    real*8, intent(out) :: qtHigh_List(:)
    real*8, intent(out) :: X_list(:)
    real*8, intent(out) :: Xlow_list(:)
    real*8, intent(out) :: Xup_list(:)
    real*8, allocatable :: X1(:),X2(:),X3(:),X4(:),X5(:),X6(:)
    real*8::Qmin,Qmax,ymin_in,ymax_in
    integer::length,i
    
    call CalculateXsection_PTint_Qint_Yint_central(X_list,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)!central value
    
    length=size(qtLow_list)
    allocate(X1(1:length))
    allocate(X2(1:length))
    allocate(X3(1:length))
    allocate(X4(1:length))
    allocate(X5(1:length))
    allocate(X6(1:length))
    
        !vary c1=0.5
       call InitializeScaleVariations(0.5d0,1d0,1d0,1d0)
       call CalculateXsection_PTint_Qint_Yint_central(X1,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
       !vary c1=2
       call InitializeScaleVariations(2d0,1d0,1d0,1d0)
       call CalculateXsection_PTint_Qint_Yint_central(X2,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
       !vary c2=0.5
       call InitializeScaleVariations(1d0,0.5d0,1d0,1d0)
       call CalculateXsection_PTint_Qint_Yint_central(X3,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
       !vary c2=2
       call InitializeScaleVariations(1d0,2d0,1d0,1d0)
       call CalculateXsection_PTint_Qint_Yint_central(X4,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
       !vary c3=0.5
       call InitializeScaleVariations(1d0,1d0,0.5d0,1d0)
       call CalculateXsection_PTint_Qint_Yint_central(X5,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
       !vary c3=2
       call InitializeScaleVariations(1d0,1d0,2d0,1d0)
       call CalculateXsection_PTint_Qint_Yint_central(X6,qtLow_List,qtHigh_List,Qmin,Qmax,ymin_in,ymax_in)
       
       do i=1, length
	Xlow_list(i)=MINVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
	Xup_list(i)=MAXVAL((/X1(i),X2(i),X3(i),X4(i),X5(i),X6(i)/))
       end do
    
    deallocate(X1)
    deallocate(X2)
    deallocate(X3)
    deallocate(X4)
    deallocate(X5)
    deallocate(X6)
    !release constants
    call InitializeScaleVariations(1d0,1d0,1d0,1d0)
  end subroutine CalculateXsection_PTint_Qint_Yint_withErr
 
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   
function XIntegrandForDYwithZ(bt_arg)
     real*8::XIntegrandForDYwithZ,bt_arg
    !!cross-seciton parameters
    real*8,dimension(-3:3):: FA,FB
     real*8,parameter::MZ2=(91.d0)**2
     real*8,parameter::GammaZ2=(2.5d0)**2
     FA=uTMDPDF_30(xA_global,bt_arg,muHard_global,zetaA_global)
     FB=uTMDPDF_30(xB_global,bt_arg,muHard_global,zetaB_global)
     
     XIntegrandForDYwithZ=&
     (4d0/9d0*FA(2)*FB(-2)+1d0/9d0*FA(1)*FB(-1)+1d0/9d0*FA(3)*FB(-3)&!gamma-part
     +4d0/9d0*FA(-2)*FB(2)+1d0/9d0*FA(-1)*FB(1)+1d0/9d0*FA(-3)*FB(3))/Q_global**2&
     +&!gamma-Z interference
     (0.00673418d0*FA(2)*FB(-2)+0.00607571d0*FA(1)*FB(-1)-0.00270862d0*FA(3)*FB(-3)+&
     0.00673418d0*FA(-2)*FB(2)+0.00607571d0*FA(-1)*FB(1)-0.00270862d0*FA(-3)*FB(3))*&
     2d0*(Q_global**2-MZ2)/((Q_global**2-MZ2)**2+GammaZ2*MZ2)&
     +&!ZZ-contributions
     (0.403213d0*FA(2)*FB(-2)+0.519741d0*FA(1)*FB(-1)+0.0334255d0*FA(3)*FB(-3)+&
     0.403213d0*FA(-2)*FB(2)+0.519741d0*FA(-1)*FB(1)+0.0334255d0*FA(-3)*FB(3))*&
     0.353536d0*Q_global**2/((Q_global**2-MZ2)**2+GammaZ2*MZ2)
end function XIntegrandForDYwithZ

function XIntegrandForDYwithZ5(bt_arg)
     real*8::XIntegrandForDYwithZ5,bt_arg
    !!cross-seciton parameters
    real*8,dimension(-5:5):: FA,FB
     real*8,parameter::MZ2=(91.d0)**2
     real*8,parameter::GammaZ2=(2.5d0)**2
     FA=uTMDPDF_50(xA_global,bt_arg,muHard_global,zetaA_global)
     FB=uTMDPDF_50(xB_global,bt_arg,muHard_global,zetaB_global)
     XIntegrandForDYwithZ5=&
     (4d0/9d0*FA(2)*FB(-2)+1d0/9d0*FA(1)*FB(-1)+1d0/9d0*FA(3)*FB(-3)&!gamma-part
     +4d0/9d0*FA(4)*FB(-4)+1d0/9d0*FA(5)*FB(-5)&
     +4d0/9d0*FA(-2)*FB(2)+1d0/9d0*FA(-1)*FB(1)+1d0/9d0*FA(-3)*FB(3)&
     +4d0/9d0*FA(-4)*FB(4)+1d0/9d0*FA(-5)*FB(5)&
     )/Q_global**2&
     +&!gamma-Z interference
     (0.00673418d0*FA(2)*FB(-2)+0.00607571d0*FA(1)*FB(-1)-0.00270862d0*FA(3)*FB(-3)&
     -0.0108345d0*FA(4)*FB(-4)-0.00270862d0*FA(5)*FB(-5)+&
     0.00673418d0*FA(-2)*FB(2)+0.00607571d0*FA(-1)*FB(1)-0.00270862d0*FA(-3)*FB(3)&
     -0.0108345d0*FA(-4)*FB(4)-0.00270862d0*FA(-5)*FB(5))*&
     2d0*(Q_global**2-MZ2)/((Q_global**2-MZ2)**2+GammaZ2*MZ2)&
     +&!ZZ-contributions
     (0.403213d0*FA(2)*FB(-2)+0.519741d0*FA(1)*FB(-1)+0.0334255d0*FA(3)*FB(-3)&
     +0.133702d0*FA(4)*FB(-4)+0.0334255d0*FA(5)*FB(-5)+&
     0.403213d0*FA(-2)*FB(2)+0.519741d0*FA(-1)*FB(1)+0.133702d0*FA(-3)*FB(3)&
     +0.133702d0*FA(-4)*FB(4)+0.0334255d0*FA(-5)*FB(5))*&
     0.353536d0*Q_global**2/((Q_global**2-MZ2)**2+GammaZ2*MZ2)
     !+&!gamma-Z interference
     !(0.00673418d0*FA(2)*FB(-2)+0.00607571d0*FA(1)*FB(-1)+0.00607571d0*FA(3)*FB(-3)&
     !+0.00673418d0*FA(4)*FB(-4)+0.00607571d0*FA(5)*FB(-5)&
     !+0.00673418d0*FA(-2)*FB(2)+0.00607571d0*FA(-1)*FB(1)+0.00607571d0*FA(-3)*FB(3)&
     !+0.00673418d0*FA(-4)*FB(4)+0.00607571d0*FA(-5)*FB(5))*&
     !2d0*(Q_global**2-MZ2)/((Q_global**2-MZ2)**2+GammaZ2*MZ2)&
     !+&!ZZ-contributions
     !(0.403213d0*FA(2)*FB(-2)+0.519741d0*FA(1)*FB(-1)+0.519741d0*FA(3)*FB(-3)&
     !+0.403213d0*FA(4)*FB(-4)+0.519741d0*FA(5)*FB(-5)&
     !+0.403213d0*FA(-2)*FB(2)+0.519741d0*FA(-1)*FB(1)+0.519741d0*FA(-3)*FB(3)&
     !+0.403213d0*FA(-4)*FB(4)+0.519741d0*FA(-5)*FB(5))*&
     !0.353536d0*Q_global**2/((Q_global**2-MZ2)**2+GammaZ2*MZ2)
end function XIntegrandForDYwithZ5
 
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!USER DEFINED FUNCITONS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
subroutine Xprefactor_byUser()
    real*8::aEM
      !alpha EM (normalized at MZ as 127^{-1}
    aEM=1/127.91d0/(1-0.00167092d0*LOG(Q_global/91.d0))
    
    SELECT CASE(process_global)
      CASE (1) !DY->gamma (pp) (e.g R209,ATLAS)
	!4 pi aEm^2/3 /Nc/Q^2/s
	prefactor_global=1.3962634015954636d0*aEM*aEM/(s_global*Q_global**2)*&
	    HardCoefficientDY()*&
	    0.3893379d9!from GeV to pb
	IsySymmetric=.true.
      CASE (2) !Zboson from pp (e.g.LHC) in the narrow-width approximation
	!4 pi^2 aem/Ns/s Br(z->ee+mumu)
	prefactor_global=13.15947253478581d0*aEM/s_global*&
	    HardCoefficientDY()*&
	    0.3893379d9*&!from GeV to pb
	    0.03645d0!Br from PDG, ee+mumu 
	IsySymmetric=.true.
      CASE (3) !Zboson from ppbar (e.g. Tevatron)
	!4 pi^2 aem/Ns/s Br(z->ll)
	prefactor_global=13.15947253478581d0*aEM/s_global*&
	    HardCoefficientDY()*&
	    0.3893379d9*&!from GeV to pb
	    0.0363d0!Br from PDG, ee Tevatron measures only electrons
	IsySymmetric=.true.
      CASE (4) !Drell-Yan on Cu (for E288)
	prefactor_global=1.3962634015954636d0*aEM*aEM/(s_global*Q_global**2)*&
	    HardCoefficientDY()*&
	    0.3893379d9!from GeV to pb
	IsySymmetric=.false.
      CASE (5) !Drell-Yan including the Z-boson peak from pp
	prefactor_global=1.3962634015954636d0*aEM*aEM/s_global*&
	    HardCoefficientDY()*&
	    0.3893379d9!from GeV to pb
	IsySymmetric=.true.
      CASE (6) !Drell-Yan on 2H (for E772)
	prefactor_global=1.3962634015954636d0*aEM*aEM/(s_global*Q_global**2)*&
	    HardCoefficientDY()*&
	    0.3893379d9!from GeV to pb
	IsySymmetric=.false.
      CASE (7)
	prefactor_global=1d0
	IsySymmetric=.false.
      CASE DEFAULT
      process_global=1
	write(*,*) 'WARNING arTeMiDe.TMDX: the requested process does not exist. All set to zero'
    END SELECT
end subroutine Xprefactor_byUser
 
  !function that evaluate the Integrand for a given set of global parameters and at given bt
  !This integrand is \sum_q z_q F x F.
function XIntegrand(bt_arg)
  real*8::XIntegrand,bt_arg
  real*8,dimension(-3:3):: FA,FB
  real*8,dimension(-5:5):: FA5,FB5
  !!cross-seciton parameters
  real*8,parameter:: paramU=0.40321312240043d0 !! ((1-2|eq|sw^2)^2+4eq^2sw^4)/(8sw^2cw^2) for eq=2/3
  real*8,parameter:: paramD=0.51974146748459d0 !! ((1-2|eq|sw^2)^2+4eq^2sw^4)/(8sw^2cw^2) for eq=1/3
  real*8,parameter:: paramS=0.13370219088667d0 !! (4eq^2sw^2)/(cw^2) for eq=1/3
  real*8,parameter:: paramC=0.53480876354668d0 !! (4eq^2sw^2)/(cw^2) for eq=2/3
  real*8,parameter:: paramB=0.13370219088667d0 !! (4eq^2sw^2)/(cw^2) for eq=1/3
  
  SELECT CASE(process_global)
      CASE (1) !DY->gamma
         ! e_q^2 *F_q(A)*F_qbar(B)
	FA=uTMDPDF_30(xA_global,bt_arg,muHard_global,zetaA_global)
	FB=uTMDPDF_30(xB_global,bt_arg,muHard_global,zetaB_global)
	
	XIntegrand=FA(1)*FB(-1)/9.d0&
	  +FA(2)*FB(-2)*4.d0/9.d0&
	  +FA(3)*FB(-3)/9.d0&
	  +FA(-1)*FB(1)/9.d0&
	  +FA(-2)*FB(2)*4.d0/9.d0&
	  +FA(-3)*FB(3)/9.d0
      CASE (2) !Zboson
	!((1-2|eq|sw^2)^2+4eq^2sw^4)/(8sw^2cw^2) *F_q(A)*F_qbar(B)
	
! 	FA=uTMDPDF_30(xA_global,bt_arg,muHard_global,zetaA_global)
! 	FB=uTMDPDF_30(xB_global,bt_arg,muHard_global,zetaB_global)
! 	
! 	XIntegrand=FA(1)*FB(-1)*paramD&
! 	  +FA(2)*FB(-2)*paramU&
! 	  +FA(3)*FB(-3)*paramS&
! 	  +FA(-1)*FB(1)*paramD&
! 	  +FA(-2)*FB(2)*paramU&
! 	  +FA(-3)*FB(3)*paramS
	FA5=uTMDPDF_50(xA_global,bt_arg,muHard_global,zetaA_global)
	FB5=uTMDPDF_50(xB_global,bt_arg,muHard_global,zetaB_global)
	
	XIntegrand=&
	  FA5(1)*FB5(-1)*paramD&
	  +FA5(2)*FB5(-2)*paramU&
	  +FA5(3)*FB5(-3)*paramS&
	  +FA5(4)*FB5(-4)*paramC&
	  +FA5(5)*FB5(-5)*paramB&
	  +FA5(-1)*FB5(1)*paramD&
	  +FA5(-2)*FB5(2)*paramU&
	  +FA5(-3)*FB5(3)*paramS&
	  +FA5(-4)*FB5(4)*paramC&
	  +FA5(-5)*FB5(5)*paramB
	
      CASE (3) !Zboson from ppbar
      !FOR A+B -> Z in PPBAR (so all q->anti q)::    ((1-2|eq|sw^2)^2+4eq^2sw^4)/(8sw^2cw^2) *F_q(A)*F_q(B)
	FA=uTMDPDF_30(xA_global,bt_arg,muHard_global,zetaA_global)
	FB=uTMDPDF_30(xB_global,bt_arg,muHard_global,zetaB_global)
! 	FA5=uTMDPDF_50(xA_global,bt_arg,muHard_global,zetaA_global)
! 	FB5=uTMDPDF_50(xB_global,bt_arg,muHard_global,zetaB_global)
	
	XIntegrand=FA(1)*FB(1)*paramD&
	  +FA(2)*FB(2)*paramU&
	  +FA(3)*FB(3)*paramS&
	  +FA(-1)*FB(-1)*paramD&
	  +FA(-2)*FB(-2)*paramU&
	  +FA(-3)*FB(-3)*paramS	  
!       XIntegrand=&
! 	  FA5(1)*FB5(1)*paramD&
! 	  +FA5(2)*FB5(2)*paramU&
! 	  +FA5(3)*FB5(3)*paramS&
! 	  +FA5(4)*FB5(4)*paramC&
! 	  +FA5(5)*FB5(5)*paramB&
! 	  +FA5(-1)*FB5(-1)*paramD&
! 	  +FA5(-2)*FB5(-2)*paramU&
! 	  +FA5(-3)*FB5(-3)*paramS&
! 	  +FA5(-4)*FB5(-4)*paramC&
! 	  +FA5(-5)*FB5(-5)*paramB


      CASE (4) !!this is for E288
	 FA=uTMDPDF_30(xA_global,bt_arg,muHard_global,zetaA_global)
	 FB=uTMDPDF_30(xB_global,bt_arg,muHard_global,zetaB_global)
	 XIntegrand=116d0/567d0*(FA(2)*FB(-2)+FA(-2)*FB(2))+136d0/567d0*(FA(-2)*FB(1)+FA(2)*FB(-1))&
	      +34d0/567d0*(FA(-1)*FB(2)+FA(1)*FB(-2))+29d0/567d0*(FA(-1)*FB(1)+FA(1)*FB(-1))&
	      +1d0/9d0*(FA(-3)*FB(3)+FA(3)*FB(-3))
      CASE (5)
	 XIntegrand=XIntegrandForDYwithZ5(bt_arg)
      CASE (6)
	FA=uTMDPDF_30(xA_global,bt_arg,muHard_global,zetaA_global)
	FB=uTMDPDF_30(xB_global,bt_arg,muHard_global,zetaB_global)
	 XIntegrand=2d0/9d0*(FA(2)*FB(-2)+FA(-2)*FB(2))+2d0/9d0*(FA(-2)*FB(1)+FA(2)*FB(-1))&
	      +1d0/18d0*(FA(-1)*FB(2)+FA(1)*FB(-2))+1d0/18d0*(FA(1)*FB(-1)+FA(-1)*FB(1))&
	      +1d0/9d0*(FA(3)*FB(-3)+FA(-3)*FB(3))
      CASE (7) !DY->gamma
         ! e_q^2 *F_q(A)*F_qbar(B)
	FA5=uTMDPDF_50(xA_global,bt_arg,muHard_global,zetaA_global)
	FB5=uTMDPDF_50(xB_global,bt_arg,muHard_global,zetaB_global)
	
	XIntegrand=FA5(1)*FB5(-1)/9.d0&
	  +FA5(2)*FB5(-2)*4.d0/9.d0&
	  +FA5(3)*FB5(-3)/9.d0&
	  +FA5(4)*FB5(-4)*4.d0/9.d0&
	  +FA5(5)*FB5(-5)/9.d0&
	  +FA5(-1)*FB5(1)/9.d0&
	  +FA5(-2)*FB5(2)*4.d0/9.d0&
	  +FA5(-3)*FB5(3)/9.d0&
	  +FA5(-4)*FB5(4)*4.d0/9.d0&
	  +FA5(-5)*FB5(5)/9.d0
      CASE DEFAULT !SOMETHING WRONG
	write(*,*) 'WARNING: the requested process does not exist.'
	XIntegrand=0.d0
	return
    END SELECT
  
end function XIntegrand

function cutPrefactor_byUser(qT)
  real*8::cutPrefactor_byUser,qT
  
  if(includeCuts) then
       !!! here include cuts onf lepton tensor
       cutPrefactor_byUser=CutFactor3(qT)
  else
	!!! this is uncut lepton tensor
       cutPrefactor_byUser=(1+0.5d0*(qT/Q_global)**2)
  end if  

end function cutPrefactor_byUser


end module TMDX



program example

use TMDX
use uTMDPDF
use TMDs
use TMDR

!use LeptonCutsDY

implicit none

real*8,dimension(1:10)::xSec,pt_list,xSecMin,xSecMax
real*8,dimension(-5:5)::tmds
real*8 t1,t2
integer i,nb
real*8 Vs,Q,y,x1,x2,muf,zetaf,bmin,bmax,bstep,b

pt_list=(/1d0,2d0,3d0,4d0,5d0,10d0,15d0,20d0,25d0,30d0/)

!initialize all at NNLO

call TMDX_Initialize('NNLO','NNLO')

! state $b_{\max}=1$, $g_k=0$, $\lambda_1=0.18$ and $\lambda_2=0.0024$.  

call TMDX_SetNPParameters(1d0,0d0,(/0.156d0,-0.0379d0/))

! ATLAS cuts: $p_T>20$, $-2.4<\eta<2.4$

call SetCuts(.false.,20d0,-2.4d0,2.4d0)

! let $Q=91$GeV and $\sqrt{s}=13$TeV, mid-rapidity, process=2.  

call TMDX_XSetup(8000d0**2,91.2d0,0d0,5)

! Evaluate cross-section

call cpu_time(t1)
!call CalculateXsection(xSec,xSecMin,xSecMax,pt_list)
call CalculateXsection(xSec,pt_list)
!call CalculateXsection_Qint_Yint(xSec,pt_list,86d0,116d0,-2.4d0,2.4d0)
call cpu_time(t2)
write(6,*) "Computation time = ",t2 - t1," s"

Vs    = 8000d0
Q     = 91.2d0
y     = 0d0
x1    = Q * dexp(-y) / Vs
x2    = Q * dexp(y) / Vs
muf   = Q
zetaf = Q * Q

nb    = 10
bmin  = 0.1d0
bmax  = 10d0
bstep = ( bmax - bmin ) / ( nb - 1 )

b = bmin
do i=1,nb
   tmds = uTMDPDF_50(x2,b,muf,zetaf)
   write(6,*) b,tmds(0),&
        tmds(1) + tmds(-1) + tmds(2) + tmds(-2) + tmds(3) + tmds(-3) + tmds(4) + tmds(-4) + tmds(5) + tmds(-5),&
        tmds(1) - tmds(-1) + tmds(2) - tmds(-2) + tmds(3) - tmds(-3) + tmds(4) - tmds(-4) + tmds(5) - tmds(-5),&
        tmds(2) + tmds(-2) - tmds(1) - tmds(-1)
   b = b + bstep
enddo
write(6,*)

do i=1,10
write(*,*) pt_list(i), xSec(i)!, xSecMin(i)-xSec(i),xSecMax(i)-xSec(i)
end do
write(6,*)


end program example
