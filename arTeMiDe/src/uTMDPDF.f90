!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe 1.0
!
!	Evaluation of the unpolarized TMD PDF at low normalization point in zeta-prescription.
!	
!	if you use this module please, quote arXiv:1706.01473
!
!	ver 1.0: release (AV, 09.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
module uTMDPDF
use ReadAs
implicit none
!------------------------LOCALs -----------------------------------------------

 private 
  !This is internal parameter for Gaussian integral precision (can be 8, 12 or 16)
  integer, parameter :: GaussOrder=12
  !Thse are weights and points for the Gaussian-Legandere integration procedure

  real*8, parameter, dimension(1:GaussOrder) :: Xi= &
      (/-0.98156063424671d0,-0.90411725637047d0,-0.76990267419430d0,-0.58731795428661d0,-0.367831498998180d0,-0.12523340851146d0,&
      0.12523340851146d0,0.36783149899818d0,0.58731795428661d0,0.76990267419430d0,0.90411725637047d0,0.98156063424671d0/)
  
  real*8, parameter, dimension(1:GaussOrder) :: Wi = &
      (/0.0471753363865208d0,0.10693932599531d0,0.16007832854332d0,0.20316742672306d0,0.233492536538353d0,0.249147045813402d0,&
      0.249147045813402d0,0.23349253653835d0,0.203167426723072d0,0.160078328543352d0,0.10693932599537d0,0.047175336386521d0/)

  !this are locals for the exchange of parameters between functions
  real*8:: xCurrent,muCurrent,bT_current
  integer :: fCurrent
  
  real*8, parameter :: C0_const=1.1229189671337703d0  !=2Exp[-gamma_E]
  real*8, parameter :: C0_inv_const=0.890536208995099d0  !=Exp[gamma_E]/2
  real*8, parameter :: C2=1.2609470067487734d0  !=4Exp[-2gamma_E]
  real*8, parameter :: C2_inv=0.7930547395313627d0  !=Exp[2gamma_E]/4
  
  integer, parameter :: withMIX=1 !!! if 1 mixture is acounted, if 0 not
  !!! The global order which is used in programm
  ! it is set by SetOrderForC subroutine
  integer :: order_global
  !!!This parrameter is set with order
  !!!It should be of order ~20 for NNLO since there one has 1/x contributions which slower converge
  integer :: numberOfRecursion
  
  !! This is list of coefficeints for the encoding the regular part
  !! { 1, x, x^2, x^3, Log[1-x], Log[1-x]^2, Log[1-x]^3, Log[x], Log[x]^2, Log[x]^3, Log[1-x]Log[x], Log[1-x]Log[x]^2}
  real*8, dimension(1:12) :: regCoeff, CoeffReg_q_q,CoeffReg_q_qp,CoeffReg_q_qb,CoeffReg_g_q,CoeffReg_q_g,CoeffReg_g_g
  !! This is list of coefficeints for the encoding the regular part singular at x->0
  !! { 1/x, Log[x]/x}
  real*8, dimension(1:2) :: CoeffSingX_q_g,CoeffSingX_g_q,CoeffSingX_g_g,CoeffSingX_q_qp
  !! This is list of coefficeints for the encoding the singular at x->1
  !! { 1/(1-x), (Log[1-x]/(1-x))_+}
  real*8, dimension(1:2) :: CoeffSing1_q_q,CoeffSing1_g_g
  real*8,dimension(1:2)::regCoeffSing
  real*8,dimension(-3:3)::PDFatX_global
  real*8,dimension(-5:5)::PDFatX_global5
  real*8::FNPat1_global
  
  logical ::includeRenormalon
  integer::lambdaNPlength
  real*8,dimension(:),allocatable::lambdaNP
  
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!This are parameters to load mmht2014 grids
  INTEGER, parameter, private :: iset=0
  CHARACTER(50), private :: prefix
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  !!!Threashold parameters
  real*8,parameter :: mCHARM=1.4d0
  real*8,parameter :: mBOTTOM=4.75d0
  
  public::uTMDPDF_Initialize,uTMDPDF_SetLambdaNP,uTMDPDF_Report
  
  public::uTMDPDF_lowScale,uTMDPDF_lowScale3,uTMDPDF_lowScale30,&
	uTMDPDF_lowScale5,uTMDPDF_lowScale50,xPDF
  
  contains
  
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Interface subroutines!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !! Initialization of the package
  subroutine uTMDPDF_Initialize(orderC,orderAs,orderPDF)
    character(len=*)::orderC,orderAs,orderPDF
    character(100)::line
    integer:: orderIntemidiate,i
    
    
    write(*,*) '----- arTeMiDe.uTMDPDF ver 1.0: .... initialization'
    
    call ModelInitialization_byUser()
    
    
    if(lambdaNPlength<=0) then
    write(*,*) 'WARNING: arTeMiDe.uTMDPDF_Initialize: number of non-pertrubative &
		    parameters should be >=1. It is set to 1'
    lambdaNPlength=1
    else if(lambdaNPlength<2 .and. includeRenormalon) then
    write(*,*) 'WARNING: arTeMiDe.uTMDPDF_Initialize: inlusion of renomalon requares &
		  number of of non-pertrubative parameters be >=2. It is set to 2'
    lambdaNPlength=2
    end if
    
    allocate(lambdaNP(1:lambdaNPlength))
    
    do i=1,lambdaNPlength
      lambdaNP(i)=0d0
    end do
    
    SELECT CASE(orderC)
      CASE ("LO")
	order_global=0
	numberOfRecursion=4
      CASE ("NLO")
	order_global=1
	numberOfRecursion=5
      CASE ("NNLO")
	order_global=1
	numberOfRecursion=25
      CASE DEFAULT
	write(*,*) 'WARNING: arTeMiDe.uTMDPDF_Initialize: unknown order for coefficient function. Switch to NLO.'
	order_global=1
	numberOfRecursion=5
     END SELECT
    OPEN(UNIT=51, FILE='../paths', ACTION="read", STATUS="old")
    
    !!!!search for uTMDPDF entry
    do
    read(51,'(A)') line
    if(line(1:3)=='*2 ') exit
    end do
    
    !!!!search for uTMDPDF.as entry
    do
    read(51,'(A)') line
    if(line(1:3)=='*A ') exit
    end do
     SELECT CASE(orderAs)
      CASE ("LO")
	read(51,'(A)') line
	call InitializeAlphaStrong(line(7:)) !!! initialize the as evaluation
      CASE ("NLO")
	read(51,'(A)') line
	read(51,'(A)') line
	call InitializeAlphaStrong(line(7:)) !!! initialize the as evaluation
      CASE ("NNLO")
        read(51,'(A)') line
        read(51,'(A)') line
        read(51,'(A)') line
	call InitializeAlphaStrong(line(7:)) !!! initialize the as evaluation
      CASE DEFAULT
	write(*,*) 'WARNING: arTeMiDe.uTMDPDF_Initialize: unknown order for alpha_strong. Switch to NLO.'
	read(51,'(A)') line
	read(51,'(A)') line
	call InitializeAlphaStrong(line(7:)) !!! initialize the as evaluation
     END SELECT    
      !!!!search for uTMDPDF.PDFgrids entry
    do
    read(51,'(A)') line
    if(line(1:3)=='*B ') exit
    end do
     SELECT CASE(orderPDF)
      CASE ("LO")
	read(51,'(A)') line
	call InitializePDF_byUser(line(7:)) !!! initialize the as evaluation
      CASE ("NLO")
	read(51,'(A)') line
	read(51,'(A)') line
	call InitializePDF_byUser(line(7:)) !!! initialize the as evaluation
      CASE ("NNLO")
        read(51,'(A)') line
        read(51,'(A)') line
        read(51,'(A)') line
	call InitializePDF_byUser(line(7:)) !!! initialize the as evaluation
      CASE DEFAULT
	write(*,*) 'WARNING: arTeMiDe.uTMDPDF_Initialize: unknown order for PDF. Switch to NLO.'
	read(51,'(A)') line
	read(51,'(A)') line
	call InitializePDF_byUser(line(7:)) !!! initialize the as evaluation
     END SELECT    
    
    CLOSE (51, STATUS='KEEP') 
    write(*,*) '----- arTeMiDe.uTMDPDF ver 1.0: .... initialized'
    
  end subroutine uTMDPDF_Initialize
  
  !!!Sets the non-pertrubative parameters lambda
  subroutine uTMDPDF_SetLambdaNP(lambdaIN)
    real*8,dimension(1:lambdaNPlength)::lambdaIN  
    lambdaNP=lambdaIN  
  end subroutine uTMDPDF_SetLambdaNP
  
  !print report on constants
  subroutine uTMDPDF_Report()
      character(len=7)::printorder
      character(len=12)::renorIncl
    
    write(*,*)'----- arTeMiDe.uTMDPDF ver 1.0: .... reporting'
    
    SELECT CASE(order_global)
      CASE (0)
	printorder="LO"
      CASE (1)
	printorder="NLO"
      CASE (2)
	printorder="NNLO"
      CASE DEFAULT
	printorder="unknown"
     END SELECT
    
    if(includeRenormalon) then
      renorIncl='INCLUDED'
    else
      renorIncl='NOT INCLUDED'
    end if
    
    write(*,*) 'uTMDPDF module report : Coef.Func. is ',printorder 
    write(*,*) '                      : renomalon contribution is '//trim(renorIncl)
    write(*,*) 'lambda_NP=',lambdaNP
    
    write(*,*)'----- arTeMiDe.uTMDPDF ver 1.0: .... end of report'
  end subroutine uTMDPDF_Report
 
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!MAKING PDF VECTORS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!if your PDF library allows simultanious definition of pdf vector
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!you can speed up the calculation rewriting this part accordingly
  !!!! function that builds the vector of PDFs (-3...3) gluon=0
  !!!!
  function xPDFVECTOR3(x,Q)
      real*8 :: x,Q
      real*8, dimension(-3:3):: xPDFVECTOR3
      
      xPDFVECTOR3(-3)=xPDF(x,Q,-3)
      xPDFVECTOR3(-2)=xPDF(x,Q,-2)
      xPDFVECTOR3(-1)=xPDF(x,Q,-1)
      xPDFVECTOR3(0)=0d0
      xPDFVECTOR3(1)=xPDF(x,Q,1)
      xPDFVECTOR3(2)=xPDF(x,Q,2)
      xPDFVECTOR3(3)=xPDF(x,Q,3)
  end function xPDFVECTOR3
  
    !!!! function that builds the vector of PDFs (-3...3) gluon included
  !!!!
  function xPDFVECTOR30(x,Q)
      real*8 :: x,Q
      real*8, dimension(-3:3):: xPDFVECTOR30
      
      xPDFVECTOR30(-3)=xPDF(x,Q,-3)
      xPDFVECTOR30(-2)=xPDF(x,Q,-2)
      xPDFVECTOR30(-1)=xPDF(x,Q,-1)
      xPDFVECTOR30(0)=xPDF(x,Q,0)
      xPDFVECTOR30(1)=xPDF(x,Q,1)
      xPDFVECTOR30(2)=xPDF(x,Q,2)
      xPDFVECTOR30(3)=xPDF(x,Q,3)
  end function xPDFVECTOR30
  
      !!!! function that builds the vector of PDFs (-5...5) gluon=0
  !!!!
  function xPDFVECTOR5(x,Q)
      real*8 :: x,Q
      real*8, dimension(-5:5):: xPDFVECTOR5
      
      xPDFVECTOR5(-5)=xPDF(x,Q,-5)
      xPDFVECTOR5(-4)=xPDF(x,Q,-4)
      xPDFVECTOR5(-3)=xPDF(x,Q,-3)
      xPDFVECTOR5(-2)=xPDF(x,Q,-2)
      xPDFVECTOR5(-1)=xPDF(x,Q,-1)
      xPDFVECTOR5(0)=0d0
      xPDFVECTOR5(1)=xPDF(x,Q,1)
      xPDFVECTOR5(2)=xPDF(x,Q,2)
      xPDFVECTOR5(3)=xPDF(x,Q,3)
      xPDFVECTOR5(4)=xPDF(x,Q,4)
      xPDFVECTOR5(5)=xPDF(x,Q,5)
  end function xPDFVECTOR5
  
   !!!! function that builds the vector of PDFs (-5...5) gluon included
  !!!!
  function xPDFVECTOR50(x,Q)
      real*8 :: x,Q
      real*8, dimension(-5:5):: xPDFVECTOR50
      
      xPDFVECTOR50(-5)=xPDF(x,Q,-5)
      xPDFVECTOR50(-4)=xPDF(x,Q,-4)
      xPDFVECTOR50(-3)=xPDF(x,Q,-3)
      xPDFVECTOR50(-2)=xPDF(x,Q,-2)
      xPDFVECTOR50(-1)=xPDF(x,Q,-1)
      xPDFVECTOR50(0)=xPDF(x,Q,0)
      xPDFVECTOR50(1)=xPDF(x,Q,1)
      xPDFVECTOR50(2)=xPDF(x,Q,2)
      xPDFVECTOR50(3)=xPDF(x,Q,3)
      xPDFVECTOR50(4)=xPDF(x,Q,4)
      xPDFVECTOR50(5)=xPDF(x,Q,5)
  end function xPDFVECTOR50
  !-------------------------------------------------

  
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!numerics!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!Functions for Gaussian integration with extra n-division
  function qgauss(func,x_i,x_f,n)
  implicit none
      real*8 qgauss,func,x_i,x_f,xn,value,x1,x2
      integer i,n
      external func

      if(n.le.1) then           ! same as n=1
         x1=x_i
         x2=x_f
         qgauss=gauss(func,x1,x2)
         return
      end if

      xn=(x_f-x_i)/float(n)
      value=0.d0
      x2=x_i
      Do i=1,n
         x1=x2
         x2=x1+xn
         value=value+gauss(func,x1,x2)
      end do

      qgauss=value
  end function qgauss
!-------------------------------------------------
!!Functions for actual Gaussian integration
  function gauss(func,x0,x1)
      implicit none
      real*8 gauss, func,x0,x1,value,xm,xr
      real*8 eps
      integer j
      
      external func


      xm=0.5d0*(x1+x0)
      xr=0.5d0*(x1-x0)
      
      value=0.d0

      Do j=1,GaussOrder
         value=value+Wi(j)*func(xm+xr*Xi(j))
      end do
	
      gauss=xr*value

  end function gauss

  
  !-----Function for convolution with Exp[-gb*b^2 z](1+gb*b^2 z)/(1-z)_+
  function singZ(z)
  real*8 :: z
  real*8 :: singZ
!   singZ = (EXP(-gBbbCurrent*z)*(1+z*gBbbCurrent)*xPDF(xCurrent/z,muCurrent,fCurrent)&
!   -EXP(-gBbbCurrent)*(1+gBbbCurrent)*xPDF(xCurrent,muCurrent,fCurrent))/(1-z)
  singZ = (FNP(z,bT_current)*xPDF(xCurrent/z,muCurrent,fCurrent)&
    -FNP(1d0,bT_current)*xPDF(xCurrent,muCurrent,fCurrent))/(1-z)
  end function singZ

!-----Function for Convolution with Exp[-gb*b^2 z](1+gb*b^2 z)*(Log[1-z]/(1-z))_+
  function singZLOG(z)
  real*8 :: z
  real*8 :: singZLOG
  singZLOG = (FNP(z,bT_current)*xPDF(xCurrent/z,muCurrent,fCurrent)&
  -FNP(1d0,bT_current)*xPDF(xCurrent,muCurrent,fCurrent))*LOG(1-z)/(1-z)
  end function singZLOG

!-----Function for Convolution with Exp[-gb*b^2 z](1+gb*b^2 z)*(regular function)
!--- the function is coded by the list of regular coefficeints
  function regFunc(z)
  real*8 :: z
  real*8 :: regFunc
  regFunc = FNP(z,bT_current)*xPDF(xCurrent/z,muCurrent,fCurrent)*&
    (regCoeff(1)+regCoeff(2)*z+regCoeff(3)*z*z+regCoeff(4)*z*z*z+&
     regCoeff(5)*LOG(1-z)+regCoeff(6)*LOG(1-z)**2+regCoeff(7)*LOG(1-z)**3&
     +regCoeff(8)*LOG(z)+regCoeff(9)*LOG(z)**2+regCoeff(10)*LOG(z)**3+&
     regCoeff(11)*LOG(1-z)*Log(z)+regCoeff(12)*LOG(1-z)*Log(z)**2)
  end function regFunc

!-----Function for Convolution with Exp[-gb*b^2 z](1+gb*b^2 z)*(regular function)
!--- the function is coded by the list of regular coefficeints
!--- perform confolution with all quarks and anti-quarks
  function regFuncQ(z)
  real*8 :: z
  real*8 :: regFuncQ
  regFuncQ = FNP(z,bT_current)*( &
    xPDF(xCurrent/z,muCurrent,-3)+&
    xPDF(xCurrent/z,muCurrent,-2)+&
    xPDF(xCurrent/z,muCurrent,-1)+&
    xPDF(xCurrent/z,muCurrent,1)+&
    xPDF(xCurrent/z,muCurrent,2)+&
    xPDF(xCurrent/z,muCurrent,3))*&
    (regCoeff(1)+regCoeff(2)*z+regCoeff(3)*z*z+regCoeff(4)*z*z*z+&
     regCoeff(5)*LOG(1-z)+regCoeff(6)*LOG(1-z)**2+regCoeff(7)*LOG(1-z)**3&
     +regCoeff(8)*LOG(z)+regCoeff(9)*LOG(z)**2+regCoeff(10)*LOG(z)**3+&
     regCoeff(11)*LOG(1-z)*Log(z)+regCoeff(12)*LOG(1-z)*Log(z)**2)
  end function regFuncQ

!-----Function for Convolution with Exp[-gb*b^2 z](1+gb*b^2 z)*(regular function)
!--- the function is coded by the list of regular coefficeints singular at x->0
  function regFuncSing(z)
  real*8 :: z
  real*8 :: regFuncSing
  regFuncSing = FNP(z,bT_current)*xPDF(xCurrent/z,muCurrent,fCurrent)/z*&
    (regCoeffSing(1)+regCoeffSing(2)*LOG(z))
  end function regFuncSing

!-----Function for Convolution with Exp[-gb*b^2 z](1+gb*b^2 z)*(regular function)
!--- the function is coded by the list of regular coefficeints singular at x->0
!--- perform confolution with all quarks and anti-quarks
  function regFuncSingQ(z)
  real*8 :: z
  real*8 :: regFuncSingQ
  regFuncSingQ =FNP(z,bT_current)*(&
    xPDF(xCurrent/z,muCurrent,-3)+&
    xPDF(xCurrent/z,muCurrent,-2)+&
    xPDF(xCurrent/z,muCurrent,-1)+&
    xPDF(xCurrent/z,muCurrent,1)+&
    xPDF(xCurrent/z,muCurrent,2)+&
    xPDF(xCurrent/z,muCurrent,3))/z*&
    (regCoeffSing(1)+regCoeffSing(2)*LOG(z))
  end function regFuncSingQ

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!COEFFICIENT FUNCTIONS!!
    !!!!Each coefficient is split to delta, sing x->1, sing x->0, regular

  
  !!!!!coefficient function q<-q delta-part
  function C_q_q_delta(alpha,Nf,Lmu)
  real*8::C_q_q_delta,Nf,alpha,LLambda,Lmu
  
 C_q_q_delta=1d0
 
  if(order_global>=1) then
      C_q_q_delta=C_q_q_delta+alpha*(-2.193245422464302d0-4d0*Lmu)
  end if
  if(order_global>=2) then
     C_q_q_delta=C_q_q_delta+alpha*alpha*(&
     -19.413533328856175d0 + 7.5971237666274805d0*Nf&
     + Lmu**2*(-37.394617839619215d0 + 1.3333333333333333d0*Nf)&
     + Lmu*(-84.35261963606607d0 + 7.75526251932545d0*Nf))
  end if
  if(includeRenormalon) then
    if(order_global==0) then!!!bmax=1
    LLambda=2.d0*Log(bT_current*C0_inv_const*0.25d0)-0.5d0*LOG(1+bT_current**2)
    else
    LLambda=2.d0*Log(bT_current*C0_inv_const*0.25d0)-0.5d0*LOG(1+bT_current**2)+1.5d0
    end if
    C_q_q_delta=C_q_q_delta+(bT_current**2)*lambdaNP(2)*(-0.666666666666667d0 -LLambda)
  end if
  
  end function C_q_q_delta
  
  !!!!!coefficient function g<-g delta-part
  function C_g_g_delta(alpha,Nf,Lmu)
  real*8::C_g_g_delta,Nf,alpha,Lmu
  
  C_g_g_delta=1d0
 
  if(order_global>=1) then
      C_g_g_delta=C_g_g_delta+alpha*(-4.934802200544679d0-(11d0-2d0/3d0*Nf)*Lmu)
  end if
  if(order_global>=2) then
     C_g_g_delta=C_g_g_delta+alpha*alpha*(&
    -31.318428735417683d0 - 118.4352528130723d0*Lmu**2 + 17.30176886771455d0*Nf - 0.691358024691358d0*Nf**2&
    + Lmu*(-225.82214554123618d0 + 10.666666666666666d0*Nf))
  end if
  
  end function C_g_g_delta
  
  !!!!!coefficient function q<-q singular-part  (1/(1-x)_+,(Log(1-x)/(1-x))_+)
  subroutine Set_CoeffSing1_q_q(alpha,Nf,Lmu)
  real*8::Nf,alpha,LLambda,Lmu,s1,s2
    
  s1=0d0!!!coeff 1/(1-x)
  s2=0d0!!!coeff log(1-x)/(1-x)
 
  if(order_global>=1) then    
    s1=s1+alpha*(-5.333333333333333d0)*Lmu
  end if
  if(order_global>=2) then
    s1=s1+alpha*alpha*(&
     14.926669450170849 + 5.530864197530864*Nf&
     + Lmu**2*(-8. + 1.7777777777777777*Nf) &
     + Lmu*(-54.77591205215826 + 5.925925925925926*Nf))
    
     s2=s2+alpha*alpha*(28.444444444444443d0*(Lmu**2))
  end if
  
  if(includeRenormalon) then
    s1=s1+2d0*(bT_current**2)*lambdaNP(2)
  end if
  
  CoeffSing1_q_q=(/s1,s2/)
  
  end subroutine Set_CoeffSing1_q_q
  
  !!!!!coefficient function g<-g singular-part  (1/(1-x)_+,(Log(1-x)/(1-x))_+)
  subroutine Set_CoeffSing1_g_g(alpha,Nf,Lmu)
  real*8::Nf,alpha,Lmu,s1,s2
    
  s1=0d0!!!coeff 1/(1-x)
  s2=0d0!!!coeff log(1-x)/(1-x)
 
  if(order_global>=1) then    
    s1=s1+alpha*(-12.d0)*Lmu
  end if
  if(order_global>=2) then
    s1=s1+alpha*alpha*(&
    33.585006262884406d0 + Lmu**2*(66d0 - 4d0*Nf) + 12.444444444444445d0*Nf&
    + Lmu*(-90.34712078039155d0 + 13.333333333333334d0*Nf))
    
     s2=s2+alpha*alpha*144.d0*(Lmu**2)
  end if
  
  
  CoeffSing1_g_g=(/s1,s2/)
  
  end subroutine Set_CoeffSing1_g_g
  
  !!!!!coefficient function q<-q regular-part  
  subroutine Set_CoeffReg_q_q(alpha,Nf,Lmu)  
  real*8::alpha,Nf,Lmu
  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  CoeffReg_q_q=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  if(order_global>=1) then
    CoeffReg_q_q=CoeffReg_q_q+alpha*(/2.6666666666666665d0*(1.d0 + Lmu) , &
      2.6666666666666665d0*(-1.d0 + Lmu),&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
     CoeffReg_q_q=CoeffReg_q_q+alpha*alpha*(/ -15.591812729537994d0 + Lmu*(-11.163487946419748d0 - 1.17427604982747d0*Nf)&
	+ Lmu**2*(-3.26930133916432d0 - 0.8888888888888915d0*Nf) - 3.6403764478352265d0*Nf , & !1
	-26.19077732354684d0 + Lmu*(95.10974248029042d0 - 8.099031072233531d0*Nf) +&
	Lmu**2*(27.43946767802459d0 - 0.8888888888888175d0*Nf) - 4.035868117241033d0*Nf,&!x
	61.362896852454675d0 - 8.246261558344264d0*Lmu**2&
	+ Lmu*(-2.7461936919088763d0 - 0.12180817068026716d0*Nf) - 0.6181383623814728d0*Nf,&!x^2
	-18.603456697689623d0 + 6.258688854739294d0*Lmu**2 +&
	Lmu*(10.832476505223244d0 - 0.08299168008727677d0*Nf) - 0.19612093929051017d0*Nf,&!x^3
	22.22222222222222d0 - 28.444444444444443d0*Lmu - 28.444444444444443d0*Lmu**2,&!Log[1-x]
	-7.111111111111111d0,&!Log[1-x]^2
	0.d0,&!Log[1-x]^3
	-8.d0-16.88888888888889d0*Lmu-3.5555555555555554d0*Lmu**2+(1.4814814814814814d0+1.7777777777777777d0*Lmu)*Nf,&!Log[x]
	-2.d0 - 4.444444444444445d0*Lmu+0.4444444444444444d0*Nf,&!Log[x]^2
	- 0.7407407407407407d0,&!Log[x]^3
	32.70163574653397d0 - 13.557009694490377d0*Lmu**2 + &
	Lmu*(1.2279020846749857d0 - 0.10756049569892116d0*Nf) - 0.069575874398736d0*Nf,&!Log[1-x]Log[x]
	12.62916203247169d0 - 3.0781480084842623d0*Lmu**2 + &
	Lmu*(-1.5312398052695269d0 + 0.26430238504639214d0*Nf) - 0.17334865938082786d0*Nf/)!Log[1-x]Log[x]^2
    end if
    
    if(includeRenormalon) then
      CoeffReg_q_q=CoeffReg_q_q+(bT_current**2)*lambdaNP(2)*&
      (/-2.d0,0.d0,-2.d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
    end if  
!  write(*,*) 'regularPart=', regularPart/x
  end if
  end subroutine Set_CoeffReg_q_q
 
  !!!!!coefficient function q<-g regular-part  
  subroutine Set_CoeffReg_q_g(alpha,Nf,Lmu)  
  real*8::alpha,Nf,Lmu
  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  CoeffReg_q_g=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  if(order_global>=1) then
    CoeffReg_q_g=CoeffReg_q_g+alpha*(/ &
      -1.d0*Lmu,2.d0*(1.d0 + Lmu) , -2.d0*(1.d0 + Lmu),&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
     CoeffReg_q_g=CoeffReg_q_g+alpha*alpha*&
	(/ 5.32456247529479d0 + 21.88278164323522d0*Lmu + 2.9034047274633026d0*Lmu**2, & !1
	-37.8039790325823d0 - 32.81632753043152d0*Lmu - 33.585568265440244d0*Lmu**2,&!x
	55.939541231907775d0 + 115.49461764132799d0*Lmu + 69.0735251101123d0*Lmu**2,&!x^2
	-44.592546819513025d0 - 99.17827159275804d0*Lmu - 40.23411202317445d0*Lmu**2,&!x^3
	-1.6666666666666665d0 + 8.666666666666666d0*Lmu**2,&!Log[1-x]
	3.3333333333333335d0*Lmu,&!Log[1-x]^2
	0.5555555555555556d0,&!Log[1-x]^3
	11.333333333333332d0 - 7.333333333333333d0*Lmu + 4.666666666666666d0*Lmu**2,&!Log[x]
	-1.1666666666666667d0 + 4.666666666666667d0*Lmu,&!Log[x]^2
	0.7777777777777778d0,&!Log[x]^3
	-10.961736574029366d0 - 18.010682645644952d0*Lmu + 14.969260770883315d0*Lmu**2,&!Log[1-x]Log[x]
	-6.522774793663304d0 - 12.952035582269703d0*Lmu + 8.9055167380792d0*Lmu**2/)!Log[1-x]Log[x]^2
    end if
    
  end if
  end subroutine Set_CoeffReg_q_g
  
    !!!!!coefficient function g<-q regular-part  
  subroutine Set_CoeffReg_g_q(alpha,Nf,Lmu)  
  real*8::alpha,Nf,Lmu
  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  CoeffReg_g_q=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  if(order_global>=1) then
    CoeffReg_g_q=CoeffReg_g_q+alpha*(/&
      5.333333333333333d0*Lmu , 2.6666666666666665d0*(1.d0-Lmu), 0d0,&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
     CoeffReg_g_q=CoeffReg_g_q+alpha*alpha*&
	  (/ -43.40171996161091d0 + Lmu*(-15.384941545437362d0 - 18.997621043364244d0*Nf) -&
	  16.984343881161237d0*Nf + Lmu**2*(-93.12152058209985d0 + 7.111111111111107d0*Nf) , & !1
	  173.18374973344203d0 + Lmu**2*(174.51290647164947d0 - 3.555555555555584d0*Nf) +&
	  9.595722778694926d0*Nf + Lmu*(-176.54511114241444d0 + 21.88573014467843d0*Nf),&!x
	  -88.4323955556243d0 - 74.32672909762138d0*Lmu**2 +&
	  Lmu*(46.65650685993596d0 - 3.7613888930617256d0*Nf) - 2.1972189030825384d0*Nf,&!x^2
	  -8.718852731902624d0 + 21.877557382453286d0*Lmu**2 + &
	  Lmu*(-16.82241072757955d0 + 0.2522631342060394d0*Nf) + 1.1549244843223576d0*Nf,&!x^3
	  -20.444444444444443d0 - 69.33333333333333d0*Lmu + 23.11111111111111d0*Lmu**2 + &
	  (1.1851851851851851d0 + 3.5555555555555554d0*Lmu)*Nf,&!Log[1-x]
	  -4.888888888888888d0 - 8.88888888888889d0*Lmu + 0.8888888888888888d0*Nf,&!Log[1-x]^2
	  -1.4814814814814814d0,&!Log[1-x]^3
	  -66.66666666666667d0 + 49.77777777777778d0*Lmu - 24.88888888888889d0*Lmu**2,&!Log[x]
	  12.444444444444445d0 - 24.88888888888889d0*Lmu,&!Log[x]^2
	  -4.148148148148148d0,&!Log[x]^3
	  -40.28067793284879d0 - 9.027874907505533d0*Lmu**2 +&
	  Lmu*(-24.549944196197163d0 - 2.3301986963919976d0*Nf) - 0.552346106244215d0*Nf,&!Log[1-x]Log[x]
	  -35.36530647197912d0 - 9.839583296746131d0*Lmu**2 + &
	  Lmu*(28.839608382677707d0 - 0.5010653588627828d0*Nf) - 0.0627184829983808d0*Nf/)!Log[1-x]Log[x]^2
    end if
    
  end if
  end subroutine Set_CoeffReg_g_q
  
      !!!!!coefficient function g<-g regular-part  
  subroutine Set_CoeffReg_g_g(alpha,Nf,Lmu)  
  real*8::alpha,Nf,Lmu
  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  CoeffReg_g_g=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  if(order_global>=1) then
    CoeffReg_g_g=CoeffReg_g_q+alpha*12.d0*Lmu*(/2.d0 , -1.d0, 1.d0,&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
     CoeffReg_g_g=CoeffReg_g_g+3d0*alpha*alpha*(/ &
      160.3174084388d0 + Lmu*(-93.86731367674986d0 - 0.3478859503906679d0*Nf) +&
      1.8798838185664d0*Nf + Lmu**2*(-22.33119358450d0 + 3.5781454863079d0*Nf), & !1
      235.25958439812186d0 + Lmu*(206.5658942322319d0 - 11.039981761951772d0*Nf) +&
      Lmu**2*(229.49460308602036d0 - 4.249820063599023d0*Nf) - 13.729196847420008d0*Nf,&!x
      -77.67188779845978d0 - 0.6784851744787738d0*Nf + Lmu*(-248.2709033240857d0 + 2.951862176503661d0*Nf)&
      + Lmu**2*(-279.3458893794d0 + 3.1753665461175d0*Nf),&!x^2
      51.61266721115288d0 + Lmu*(146.14666803091404d0 - 5.005204928807868d0*Nf)&
      + Lmu**2*(139.36198018839758d0 - 1.011892350506719d0*Nf) - 1.3169890096131303d0*Nf,&!x^3
      2d0-0.6666666666667d0*Nf- 48.d0*Lmu - 48.d0*Lmu**2,&!Log[1-x]
      -12.d0,&!Log[1-x]^2
      0.d0,&!Log[1-x]^3
      -97.66666666666667d0 + 8.222222222222221d0*Nf +&
      Lmu**2*(-24.d0 + 1.7777777777777777d0*Nf) + Lmu*(4.d0 + 8.d0*Nf),&!Log[x]
      1d0 + 2d0*Nf + Lmu*(-24.d0 + 1.7777777777777777d0*Nf),&!Log[x]^2
      -4.d0 + 0.2962962962962963d0*Nf,&!Log[x]^3
      24.137288673188998d0- 1.0158393615503878d0*Nf + Lmu*(-41.46407843701748d0 - 1.0706081565674075d0*Nf)&
      + Lmu**2*(-76.3356964697226d0 - 0.305920830953362d0*Nf) ,&!Log[1-x]Log[x]
      -22.406633639406444d0+ 1.090527996849969d0*Nf + Lmu*(33.80963213436533d0 - 0.31231290343118673d0*Nf)&
      + Lmu**2*(-36.44244054512763d0 + 0.32913292320654053d0*Nf) /)!Log[1-x]Log[x]^2
    end if
    
  end if
  end subroutine Set_CoeffReg_g_g

   !!!!!coefficient function q<-qb regular-part  
  subroutine Set_CoeffReg_q_qb(alpha,Nf,Lmu)  
  real*8::alpha,Nf,Lmu
  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  CoeffReg_q_qb=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
     CoeffReg_q_qb=CoeffReg_q_qb+alpha*alpha*(/&
     -3.329144380448291d0 + 0.5585827973542465d0*Lmu, & !1
      5.852825050121677d0 + 2.138867851032283d0*Lmu,&!x
      -4.796244777535505d0 - 6.91755351450176d0*Lmu,&!x^2
      2.2557153775946435d0 + 4.179872732092321d0*Lmu,&!x^3
      0d0,&!Log[1-x]
      0d0,&!Log[1-x]^2
      0d0,&!Log[1-x]^3
      -1.3333333333333333d0 + 1.7777777777777777d0*Lmu,&!Log[x]
      0.8888888888888888d0*Lmu,&!Log[x]^2
      0.14814814814814814d0,&!Log[x]^3
      0.505971782717726d0 + 1.1053347792967274d0*Lmu,&!Log[1-x]Log[x]
      0.08759292525297521d0 + 0.3928222141213225d0*Lmu/)!Log[1-x]Log[x]^2
    end if
  end subroutine Set_CoeffReg_q_qb
  
     !!!!!coefficient function q<-qp regular-part  
  subroutine Set_CoeffReg_q_qp(alpha,Nf,Lmu)  
  real*8::alpha,Nf,Lmu
  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  CoeffReg_q_qp=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
     CoeffReg_q_qp=CoeffReg_q_qp+alpha*alpha*(/ &
     -3.54792360390173d0 + 10.587890419073132d0*Lmu + 1.3696041955297178d0*Lmu**2, & !1
      4.949994905325898d0 - 5.159332804285393d0*Lmu - 4.38542467394591d0*Lmu**2,&!x
      -11.357230229521692d0 + 3.4236263406397334d0*Lmu + 2.7441423797078066d0*Lmu**2,&!x^2
      7.2245197835090105d0 - 1.1771482881020585d0*Lmu - 1.4915471808634146d0*Lmu**2,&!x^3
      0d0,&!Log[1-x]
      0d0,&!Log[1-x]^2
      0d0,&!Log[1-x]^3
      2.6666666666666665d0 - 2.6666666666666665d0*Lmu + 2.6666666666666665d0*Lmu**2,&!Log[x]
      -0.6666666666666666d0 + 2.6666666666666665d0*Lmu,&!Log[x]^2
      0.4444444444444444d0,&!Log[x]^3
      2.255041649827519d0 + 1.075408552640387d0*Lmu - 0.4433475183382652d0*Lmu**2,&!Log[1-x]Log[x]
      0.7663091186642608d0 - 4.026402017684747d0*Lmu + 0.5028961532349057d0*Lmu**2/)!Log[1-x]Log[x]^2
    end if
  end subroutine Set_CoeffReg_q_qp
  
  
  !!!!!coefficient function q<-g singular-part  (1/x,Log(x)/x)
  subroutine Set_CoeffSingX_q_g(alpha,Nf,Lmu)
  real*8::Nf,alpha,Lmu
    
  CoeffSingX_q_g=(/0,0/)
  if(order_global>=2) then
    CoeffSingX_q_g=CoeffSingX_q_g+alpha*alpha*(/5.9516385763253d0 - 17.333333333333332d0*Lmu + 4.d0*Lmu**2,&
	      0d0/)
  end if
  
  
  end subroutine Set_CoeffSingX_q_g
  
    !!!!!coefficient function g<-q singular-part  (1/x,Log(x)/x)
  subroutine Set_CoeffSingX_g_q(alpha,Nf,Lmu)
  real*8::Nf,alpha,Lmu
    
  CoeffSingX_g_q=(/0,0/)
  if(order_global>=1) then
    CoeffSingX_g_q=CoeffSingX_g_q+alpha*(/-5.333333333333333d0*Lmu,0.d0/)
  if(order_global>=2) then
    CoeffSingX_g_q=CoeffSingX_g_q+alpha*alpha*&
	  (/-44.347625564647444d0 + Lmu**2*(34.666666666666664d0 - 7.111111111111111d0*Nf) +&
	  11.061728395061728d0*Nf + Lmu*(10.318945069571619d0 + 11.851851851851851d0),&
	  -32.d0*Lmu**2/)
  end if
  end if
  
  end subroutine Set_CoeffSingX_g_q
  
      !!!!!coefficient function g<-g singular-part  (1/x,Log(x)/x)
  subroutine Set_CoeffSingX_g_g(alpha,Nf,Lmu)
  real*8::Nf,alpha,Lmu
    
  CoeffSingX_g_g=(/0,0/)
  if(order_global>=1) then
    CoeffSingX_g_g=CoeffSingX_g_g+alpha*12.d0*Lmu*(/-1.d0,0.d0/)
  if(order_global>=2) then
    CoeffSingX_g_g=CoeffSingX_g_g+3d0*alpha*alpha*(/&
      -33.2607191734856d0 + 8.37037037037037d0*Nf+ Lmu**2*(-66.d0 - 0.148148d0*Nf) +&
      Lmu*(19.739208802178716d0 + 9.037037037037036d0*Nf),& !1/x
	      -24.d0*Lmu**2/)
  end if
  end if
  
  end subroutine Set_CoeffSingX_g_g
  
    !!!!!coefficient function q<-qp singular-part  (1/x,Log(x)/x)
  subroutine Set_CoeffSingX_q_qp(alpha,Nf,Lmu)
  real*8::Nf,alpha,Lmu
    
  CoeffSingX_q_qp=(/0,0/)
  if(order_global>=2) then
    CoeffSingX_q_qp=CoeffSingX_q_qp+alpha*alpha*(/&
      2.6451727005890224d0 - 7.703703703703703d0*Lmu + 1.7777777777777777d0*Lmu**2,&
	      0d0/)
	     
  end if
  
  
  end subroutine Set_CoeffSingX_q_qp
  
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Convolutions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
!---------------------------------------------------------------------
!- This is the uTMDPDF function for parton f (in zeta-prescription) at x,bT,mu
!- The non-pertrubative parameter gK is in the exponent (in GeV^2)
!--    f =   -6,  -5,  -4,  -3,  -2,  -1,0,1,2,3,4,5,6
!--      = tbar,bbar,cbar,sbar,ubar,dbar,g,d,u,s,c,b,t.
!- The order is accumulative pertrubative order of coefficient =0,1,2 (LO,NLO,NNLO)
!---------------------------------------------------------------------
!---------------------------------------------------------------------
! DESCRIPTION
!
! The convolution is devidet onto three parts
! 1) Delta-parton
! 2) Singular parton (plus-distribution)
! 3) Regular part
  function uTMDPDF_lowScale(f,x,bT,mu)
  real*8 :: uTMDPDF_lowScale, x, bT,mu
  integer :: f
  
  real*8 :: alpha
  real*8 :: singConvol, singConvolLog
  real*8 :: Lmu,Nf,LLambda
  
  real*8 :: deltaPart
  real*8 :: singularPart
  real*8 :: regularPart  
  real*8 :: deltaCoefficient
  
  fCurrent=f
  Lmu=2.d0*Log(bT*mu*C0_inv_const)
  xCurrent=x
  bT_current=bT
  muCurrent=mu
  alpha=As(mu)
  if(mu<=mCHARM) then
    Nf=3d0
  elseif(mu<=mBOTTOM) then
    Nf=4d0
  else 
    Nf=5d0
  end if
  
 !------------DELTA PART-------------------
 !Leading order is always here!! 
 ! NOTE: there are no mixture in this part
 deltaCoefficient=1d0
 
  if(order_global>=1) then
    if(f==0) then !gluon case
      deltaCoefficient=deltaCoefficient+alpha*(-4.934802200544679d0-(11d0-2d0/3d0*Nf)*Lmu)
    else !quark case
      deltaCoefficient=deltaCoefficient+alpha*(-2.193245422464302d0-4d0*Lmu)
    end if
  end if
  if(order_global>=2) then
    if (f==0) then!gluon case
    deltaCoefficient=deltaCoefficient+alpha*alpha*(&
    -31.318428735417683d0 - 118.4352528130723d0*Lmu**2 + 17.30176886771455d0*Nf - 0.691358024691358d0*Nf**2&
    + Lmu*(-225.82214554123618d0 + 10.666666666666666d0*Nf))
    else !quark
     deltaCoefficient=deltaCoefficient+alpha*alpha*(&
     -19.413533328856175d0 + 7.5971237666274805d0*Nf&
     + Lmu**2*(-37.394617839619215d0 + 1.3333333333333333d0*Nf)&
     + Lmu*(-84.35261963606607d0 + 7.75526251932545d0*Nf))
    end if 
  end if
  if(includeRenormalon) then
    LLambda=2.d0*Log(bT*C0_inv_const*0.25d0)
    deltaCoefficient=deltaCoefficient+(bT**2)*lambdaNP(2)*(-0.666666666666667d0 -LLambda)
  end if
  deltaPart=deltaCoefficient*FNP(1d0,bT_current)*xPDF(x,mu,f)
  

 ! write(*,*) 'Lmu=',Lmu
 ! write(*,*) 'exp=',EXP(-gBbbCurrent)
 ! write(*,*) 'deltaPart =', deltaPart/x
  
 !------------SINGULAR PART-------------------
 !Leading order is always zero!!
 ! NOTE: there are no mixture in this part
 ! NOTE2: the additional term comes from the integral (0,x) of the delta-part of()_+
  singularPart=0.d0
  !NLO
  if(order_global>=1) then
    !!!here we precalculate the convolution with 1/(1-x)
    singConvol=qgauss(singZ,x,1.0d0,3)+&
	   FNP(1d0,bT_current)*xPDF(xCurrent,muCurrent,fCurrent)*LOG(1-xCurrent)
	    
    !write(*,*) singConvol
    
    if(f==0) then !gluon case
      singularPart=singularPart+alpha*(-12.d0)*Lmu*singConvol
    else !quark case
      singularPart=singularPart+alpha*(-5.333333333333333d0)*Lmu*singConvol
    end if
  end if
  !NNLO
  if(order_global>=2) then
    !!!here we precalculate the convolution with log(1-x)/(1-x)
    singConvolLOG=qgauss(singZLOG,x,1.d0,3)+&
    FNP(1d0,bT_current)*xPDF(x,mu,f)*(Log(1-x)**2)/2.d0
    
    if (f==0) then!gluon case
    singularPart=singularPart+alpha*alpha*((&
    33.585006262884406d0 + Lmu**2*(66d0 - 4d0*Nf) + 12.444444444444445d0*Nf&
    + Lmu*(-90.34712078039155d0 + 13.333333333333334d0*Nf))*singConvol&
    + 144.d0*(Lmu**2)*singConvolLOG)
    else !quark
     singularPart=singularPart+alpha*alpha*((&
     14.926669450170849 + 5.530864197530864*Nf&
     + Lmu**2*(-8. + 1.7777777777777777*Nf) &
     + Lmu*(-54.77591205215826 + 5.925925925925926*Nf))*singConvol&
     +  28.444444444444443d0*(Lmu**2)*singConvolLOG)
    end if 
  end if
  
  if(includeRenormalon) then
    singularPart=singularPart+2d0*(bT**2)*lambdaNP(2)*singConvol
  end if

  
!  write(*,*) 'singularPart =', singularPart/x
  
   !------------REGULAR PART-------------------
   !First calculate without mixture then add
   !
   !In order to speed up the calculation we first evaluate the coefficient list (at 1/2 loop order)
   !and then calaculate the convolution
   !  
  !! the Leading order is always zero, therefore calculation should be done only for order >=1
  if(order_global>=1) then
  
    !! we precalculate the coefficeint lists
    if(f==0) then !gluon case
      regCoeff=alpha*12.d0*Lmu*(/2.d0 , -1.d0, 1.d0,&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      regCoeffSing=alpha*12.d0*Lmu*(/-1.d0,0.d0/)
    else !quark case
      regCoeff=alpha*(/2.6666666666666665d0*(1.d0 + Lmu) , &
      2.6666666666666665d0*(-1.d0 + Lmu),&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
    end if
  !------The kernels are calculated in mathematica
    if(order_global>=2) then
      if(f==0) then !gluon case

      regCoeff=regCoeff+3d0*alpha*alpha*(/ &
      160.3174084388d0 + Lmu*(-93.86731367674986d0 - 0.3478859503906679d0*Nf) +&
      1.8798838185664d0*Nf + Lmu**2*(-22.33119358450d0 + 3.5781454863079d0*Nf), & !1
      235.25958439812186d0 + Lmu*(206.5658942322319d0 - 11.039981761951772d0*Nf) +&
      Lmu**2*(229.49460308602036d0 - 4.249820063599023d0*Nf) - 13.729196847420008d0*Nf,&!x
      -77.67188779845978d0 - 0.6784851744787738d0*Nf + Lmu*(-248.2709033240857d0 + 2.951862176503661d0*Nf)&
      + Lmu**2*(-279.3458893794d0 + 3.1753665461175d0*Nf),&!x^2
      51.61266721115288d0 + Lmu*(146.14666803091404d0 - 5.005204928807868d0*Nf)&
      + Lmu**2*(139.36198018839758d0 - 1.011892350506719d0*Nf) - 1.3169890096131303d0*Nf,&!x^3
      2d0-0.6666666666667d0*Nf- 48.d0*Lmu - 48.d0*Lmu**2,&!Log[1-x]
      -12.d0,&!Log[1-x]^2
      0.d0,&!Log[1-x]^3
      -97.66666666666667d0 + 8.222222222222221d0*Nf +&
      Lmu**2*(-24.d0 + 1.7777777777777777d0*Nf) + Lmu*(4.d0 + 8.d0*Nf),&!Log[x]
      1d0 + 2d0*Nf + Lmu*(-24.d0 + 1.7777777777777777d0*Nf),&!Log[x]^2
      -4.d0 + 0.2962962962962963d0*Nf,&!Log[x]^3
      24.137288673188998d0- 1.0158393615503878d0*Nf + Lmu*(-41.46407843701748d0 - 1.0706081565674075d0*Nf)&
      + Lmu**2*(-76.3356964697226d0 - 0.305920830953362d0*Nf) ,&!Log[1-x]Log[x]
      -22.406633639406444d0+ 1.090527996849969d0*Nf + Lmu*(33.80963213436533d0 - 0.31231290343118673d0*Nf)&
      + Lmu**2*(-36.44244054512763d0 + 0.32913292320654053d0*Nf) /)!Log[1-x]Log[x]^2
      
      regCoeffSing=regCoeffSing+3d0*alpha*alpha*(/&
      -33.2607191734856d0 + 8.37037037037037d0*Nf+ Lmu**2*(-66.d0 - 0.148148d0*Nf) +&
      Lmu*(19.739208802178716d0 + 9.037037037037036d0*Nf),& !1/x
	      -24.d0*Lmu**2/)!log[x]/x
    else !quark case
	regCoeff=regCoeff+alpha*alpha*(/ -15.591812729537994d0 + Lmu*(-11.163487946419748d0 - 1.17427604982747d0*Nf)&
	+ Lmu**2*(-3.26930133916432d0 - 0.8888888888888915d0*Nf) - 3.6403764478352265d0*Nf , & !1
	-26.19077732354684d0 + Lmu*(95.10974248029042d0 - 8.099031072233531d0*Nf) +&
	Lmu**2*(27.43946767802459d0 - 0.8888888888888175d0*Nf) - 4.035868117241033d0*Nf,&!x
	61.362896852454675d0 - 8.246261558344264d0*Lmu**2&
	+ Lmu*(-2.7461936919088763d0 - 0.12180817068026716d0*Nf) - 0.6181383623814728d0*Nf,&!x^2
	-18.603456697689623d0 + 6.258688854739294d0*Lmu**2 +&
	Lmu*(10.832476505223244d0 - 0.08299168008727677d0*Nf) - 0.19612093929051017d0*Nf,&!x^3
	22.22222222222222d0 - 28.444444444444443d0*Lmu - 28.444444444444443d0*Lmu**2,&!Log[1-x]
	-7.111111111111111d0,&!Log[1-x]^2
	0.d0,&!Log[1-x]^3
	-8.d0-16.88888888888889d0*Lmu-3.5555555555555554d0*Lmu**2+(1.4814814814814814d0+1.7777777777777777d0*Lmu)*Nf,&!Log[x]
	-2.d0 - 4.444444444444445d0*Lmu+0.4444444444444444d0*Nf,&!Log[x]^2
	- 0.7407407407407407d0,&!Log[x]^3
	32.70163574653397d0 - 13.557009694490377d0*Lmu**2 + &
	Lmu*(1.2279020846749857d0 - 0.10756049569892116d0*Nf) - 0.069575874398736d0*Nf,&!Log[1-x]Log[x]
	12.62916203247169d0 - 3.0781480084842623d0*Lmu**2 + &
	Lmu*(-1.5312398052695269d0 + 0.26430238504639214d0*Nf) - 0.17334865938082786d0*Nf/)!Log[1-x]Log[x]^2
      end if
    end if
    
    if(includeRenormalon) then
      regCoeff=regCoeff+(bT**2)*lambdaNP(2)*&
      (/-2.d0,0.d0,-2.d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
    end if
  !!here we calculate the convolutions
    if(f==0) then
      regularPart=qgauss(regFunc,x,1.d0,3)+qgauss(regFuncSing,x,1.d0,25)
    else
      regularPart=qgauss(regFunc,x,1.d0,3)
    end if
    
  else !!! inteh case of leading order
      if(includeRenormalon.and.(f /= 0)) then
	regCoeff=(bT**2)*lambdaNP(2)*&
	(/-2.d0,0.d0,-2.d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
	regularPart=qgauss(regFunc,x,1.d0,3)
      else
	regularPart=0d0
      end if
  end if
!  write(*,*) 'regularPart=', regularPart/x
  
  !Second calculate mixture
  !for mixture we do the same procedure, first evaluate coeff.list then convolution
  ! mixing appears only for NLO and higher
  if(withMIX==1 .and. order_global>=1) then
    
    ! gluon case contains only mixing woth quarks
    if(f==0) then !gluon case
      regCoeff=alpha*(/5.333333333333333d0*Lmu , 2.6666666666666665d0*(1.d0-Lmu), 0d0,&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      regCoeffSing=alpha*(/-5.333333333333333d0*Lmu,0.d0/)
      
      if(order_global>=2) then !NNLO
	regCoeff=regCoeff+alpha*alpha*&
	  (/ -43.40171996161091d0 + Lmu*(-15.384941545437362d0 - 18.997621043364244d0*Nf) -&
	  16.984343881161237d0*Nf + Lmu**2*(-93.12152058209985d0 + 7.111111111111107d0*Nf) , & !1
	  173.18374973344203d0 + Lmu**2*(174.51290647164947d0 - 3.555555555555584d0*Nf) +&
	  9.595722778694926d0*Nf + Lmu*(-176.54511114241444d0 + 21.88573014467843d0*Nf),&!x
	  -88.4323955556243d0 - 74.32672909762138d0*Lmu**2 +&
	  Lmu*(46.65650685993596d0 - 3.7613888930617256d0*Nf) - 2.1972189030825384d0*Nf,&!x^2
	  -8.718852731902624d0 + 21.877557382453286d0*Lmu**2 + &
	  Lmu*(-16.82241072757955d0 + 0.2522631342060394d0*Nf) + 1.1549244843223576d0*Nf,&!x^3
	  -20.444444444444443d0 - 69.33333333333333d0*Lmu + 23.11111111111111d0*Lmu**2 + &
	  (1.1851851851851851d0 + 3.5555555555555554d0*Lmu)*Nf,&!Log[1-x]
	  -4.888888888888888d0 - 8.88888888888889d0*Lmu + 0.8888888888888888d0*Nf,&!Log[1-x]^2
	  -1.4814814814814814d0,&!Log[1-x]^3
	  -66.66666666666667d0 + 49.77777777777778d0*Lmu - 24.88888888888889d0*Lmu**2,&!Log[x]
	  12.444444444444445d0 - 24.88888888888889d0*Lmu,&!Log[x]^2
	  -4.148148148148148d0,&!Log[x]^3
	  -40.28067793284879d0 - 9.027874907505533d0*Lmu**2 +&
	  Lmu*(-24.549944196197163d0 - 2.3301986963919976d0*Nf) - 0.552346106244215d0*Nf,&!Log[1-x]Log[x]
	  -35.36530647197912d0 - 9.839583296746131d0*Lmu**2 + &
	  Lmu*(28.839608382677707d0 - 0.5010653588627828d0*Nf) - 0.0627184829983808d0*Nf/)!Log[1-x]Log[x]^2
	  
	regCoeffSing=regCoeffSing+alpha*alpha*&
	  (/-44.347625564647444d0 + Lmu**2*(34.666666666666664d0 - 7.111111111111111d0*Nf) +&
	  11.061728395061728d0*Nf + Lmu*(10.318945069571619d0 + 11.851851851851851d0),&
	  -32.d0*Lmu**2/)
      end if
      
      regularPart=regularPart+qgauss(regFuncQ,x,1.d0,3)+qgauss(regFuncSingQ,x,1.d0,25)
      
      !-------END OF GLUON CALCULATION
      
    else !quark case
      
      !first evaluate mix with gluon 
      fCurrent=0!MIX WITH GLUON
      !gBbbCurrent=gB_global(0)*bT2current
    
      regCoeff=alpha*(/ -1.d0*Lmu,2.d0*(1.d0 + Lmu) , -2.d0*(1.d0 + Lmu),&
      0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      
      if(order_global>=2) then
	regCoeff=regCoeff+alpha*alpha*&
	(/ 5.32456247529479d0 + 21.88278164323522d0*Lmu + 2.9034047274633026d0*Lmu**2, & !1
	-37.8039790325823d0 - 32.81632753043152d0*Lmu - 33.585568265440244d0*Lmu**2,&!x
	55.939541231907775d0 + 115.49461764132799d0*Lmu + 69.0735251101123d0*Lmu**2,&!x^2
	-44.592546819513025d0 - 99.17827159275804d0*Lmu - 40.23411202317445d0*Lmu**2,&!x^3
	-1.6666666666666665d0 + 8.666666666666666d0*Lmu**2,&!Log[1-x]
	3.3333333333333335d0*Lmu,&!Log[1-x]^2
	0.5555555555555556d0,&!Log[1-x]^3
	11.333333333333332d0 - 7.333333333333333d0*Lmu + 4.666666666666666d0*Lmu**2,&!Log[x]
	-1.1666666666666667d0 + 4.666666666666667d0*Lmu,&!Log[x]^2
	0.7777777777777778d0,&!Log[x]^3
	-10.961736574029366d0 - 18.010682645644952d0*Lmu + 14.969260770883315d0*Lmu**2,&!Log[1-x]Log[x]
	-6.522774793663304d0 - 12.952035582269703d0*Lmu + 8.9055167380792d0*Lmu**2/)!Log[1-x]Log[x]^2
	
	regCoeffSing=alpha*alpha*&
	      (/5.9516385763253d0 - 17.333333333333332d0*Lmu + 4.d0*Lmu**2,&
	      0d0/)
      end if
      
      regularPart=regularPart+qgauss(regFunc,x,1.d0,3)
      if(order_global>=2) then
	regularPart=regularPart+qgauss(regFuncSing,x,1.d0,25)
      end if
    !write(*,*) 'gluon mixture',f,qgauss(regFunc,x,1.d0,3)
    !if order >=2 we alos have mix with anti-quark and q-prime
    if(order_global>=2) then
      
      regCoeff=(/ -3.329144380448291d0 + 0.5585827973542465d0*Lmu, & !1
      5.852825050121677d0 + 2.138867851032283d0*Lmu,&!x
      -4.796244777535505d0 - 6.91755351450176d0*Lmu,&!x^2
      2.2557153775946435d0 + 4.179872732092321d0*Lmu,&!x^3
      0d0,&!Log[1-x]
      0d0,&!Log[1-x]^2
      0d0,&!Log[1-x]^3
      -1.3333333333333333d0 + 1.7777777777777777d0*Lmu,&!Log[x]
      0.8888888888888888d0*Lmu,&!Log[x]^2
      0.14814814814814814d0,&!Log[x]^3
      0.505971782717726d0 + 1.1053347792967274d0*Lmu,&!Log[1-x]Log[x]
      0.08759292525297521d0 + 0.3928222141213225d0*Lmu/)!Log[1-x]Log[x]^2
      
      fCurrent=-1d0*fCurrent !!with Anti-Particle Mix
      !gBbbCurrent=gB_global(fCurrent)*bT2current
      regularPart=regularPart+alpha*alpha*qgauss(regFunc,x,1.d0,3)
      
      regCoeff=(/ -3.54792360390173d0 + 10.587890419073132d0*Lmu + 1.3696041955297178d0*Lmu**2, & !1
      4.949994905325898d0 - 5.159332804285393d0*Lmu - 4.38542467394591d0*Lmu**2,&!x
      -11.357230229521692d0 + 3.4236263406397334d0*Lmu + 2.7441423797078066d0*Lmu**2,&!x^2
      7.2245197835090105d0 - 1.1771482881020585d0*Lmu - 1.4915471808634146d0*Lmu**2,&!x^3
      0d0,&!Log[1-x]
      0d0,&!Log[1-x]^2
      0d0,&!Log[1-x]^3
      2.6666666666666665d0 - 2.6666666666666665d0*Lmu + 2.6666666666666665d0*Lmu**2,&!Log[x]
      -0.6666666666666666d0 + 2.6666666666666665d0*Lmu,&!Log[x]^2
      0.4444444444444444d0,&!Log[x]^3
      2.255041649827519d0 + 1.075408552640387d0*Lmu - 0.4433475183382652d0*Lmu**2,&!Log[1-x]Log[x]
      0.7663091186642608d0 - 4.026402017684747d0*Lmu + 0.5028961532349057d0*Lmu**2/)!Log[1-x]Log[x]^2
      
      regCoeffSing=(/2.6451727005890224d0 - 7.703703703703703d0*Lmu + 1.7777777777777777d0*Lmu**2,&
	      0d0/)
      regularPart=regularPart+alpha*alpha*(qgauss(regFuncQ,x,1.d0,3) &
		  +qgauss(regFuncSingQ,x,1.d0,25))
		
    end if
  end if
    
  end if
  
  uTMDPDF_lowScale=(deltaPart+singularPart+regularPart)/x

  end function uTMDPDF_lowScale
  

  
!---------------------------------------------------------------------
!- This is the TMD function evaluated for all quarks simultaniously (-3..3) at x,bT,mu
!--    f =   -3,  -2,  -1,0,1,2,3
!--      = sbar,ubar,dbar,g,d,u,s
!!---Gluon contribution is undefined
!- The order is accumulative pertrubative order of coefficient =0,1,2 (LO,NLO,NNLO)
!---------------------------------------------------------------------
!---------------------------------------------------------------------
  function uTMDPDF_lowScale3(x,bT,mu)
  real*8,dimension(-3:3)::uTMDPDF_lowScale3
  real*8 :: x, bT,mu
  
  real*8 :: alpha
  real*8,dimension(-3:3) :: singConvol, singConvolLog
  real*8 :: Lmu,Nf,LLambda
  
  real*8,dimension(-3:3) :: deltaPart
  real*8,dimension(-3:3) :: convolutionPart
  
  Lmu=2.d0*Log(bT*mu*C0_inv_const)
  xCurrent=x
  bT_current=bT
  muCurrent=mu
  alpha=As(mu)
  if(mu<=mCHARM) then
    Nf=3d0
  elseif(mu<=mBOTTOM) then
    Nf=4d0
  else 
    Nf=5d0
  end if
  
  FNPat1_global=FNP(1d0,bT_current)
  PDFatX_global=xPDFVECTOR3(xCurrent,muCurrent)
  
 !------------DELTA PART-------------------
 !Leading order is always here!! 
 ! NOTE: there are no mixture in this part  
  deltaPart=FNPat1_global*C_q_q_delta(alpha,Nf,Lmu)*PDFatX_global
  
  if(order_global>=1 .or. includeRenormalon) then
 !!!!evaluate coefficients
  call Set_CoeffSing1_q_q(alpha,Nf,Lmu)
  call Set_CoeffReg_q_q(alpha,Nf,Lmu)
  
  if(order_global>=1) then
  
  call Set_CoeffReg_q_qb(alpha,Nf,Lmu)
  call Set_CoeffReg_q_qp(alpha,Nf,Lmu)
  call Set_CoeffReg_q_g(alpha,Nf,Lmu)
  
  call Set_CoeffSingX_q_g(alpha,Nf,Lmu)
  call Set_CoeffSingX_q_qp(alpha,Nf,Lmu)
  
  end if
  end if

    
  if(order_global>=1 .or. includeRenormalon) then
  convolutionPart=MellinConvolutionVector3(numberOfRecursion)
  else
  convolutionPart=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  end if
  
  !write(*,*) 'gluonMIXTUREPart =', gluonMIXTURE/x  
  !write(*,*) 'TDhat', (deltaPart+singularPart+regularPart)/x
  uTMDPDF_lowScale3=(deltaPart+convolutionPart)*(1d0/x)

  end function uTMDPDF_lowScale3
  
  
  function MellinConvolutionVector3(n)
    real*8,dimension(-3:3)::MellinConvolutionVector3
    real*8::xn,x1,x2
    integer::i,n
    
   ! write(*,*) 'INSIDE MELLIN CONVOLUTION'
    
    !write(*,*) regCoeff_q_q
    !write(*,*) regCoeff_q_qp
    !write(*,*) regCoeff_q_qb
    !write(*,*) regCoeffSing_q_qp
    
    if(n.le.1) then           ! same as n=1
         x1=xCurrent
         x2=1d0
         MellinConvolutionVector3=MellinConvolutionVectorPart3(x1,x2)
    else
      xn=(1-xCurrent)/float(n)
      MellinConvolutionVector3=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      x2=xCurrent
      Do i=1,n
         x1=x2
         x2=x1+xn
         MellinConvolutionVector3=MellinConvolutionVector3+MellinConvolutionVectorPart3(x1,x2)
      end do
    end if
    !!! subtract reast part of ()_+ distributions
    
    MellinConvolutionVector3=MellinConvolutionVector3+&
    (CoeffSing1_q_q(1)*LOG(1d0-xCurrent)+CoeffSing1_q_q(2)*(LOG(1d0-xCurrent))**2/2d0)*PDFatX_global*FNPat1_global    
    
  end function MellinConvolutionVector3
  
  
  !!! function evalute mellin convolution from x0 to x1 for VECTOR 
  !!!using coefficeint Cqq,Cqq',Cqqbar
  !!! Single Gaussian
  function MellinConvolutionVectorPart3(x0,x1)
    real*8,dimension(-3:3)::MellinConvolutionVectorPart3,PDFs,value
    
    real*8 :: x0,x1,xm,xr,z,PDFsum,CqMain,CqAnti,CqPrime,CqGluon
    integer :: j,i
    real*8,dimension(1:12):: var
    real*8,dimension(1:2)::varX

    xm=0.5d0*(x1+x0)
    xr=0.5d0*(x1-x0)
    
    MellinConvolutionVectorPart3=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
    
    Do j=1,GaussOrder
      z=xm+xr*Xi(j)
      
      !!! PDFs are together with non-perp func!
      PDFs=FNP(z,bT_current)*xPDFVECTOR30(xCurrent/z,muCurrent)
      
      PDFsum=PDFs(-3)+PDFs(-2)+PDFs(-1)+PDFs(1)+PDFs(2)+PDFs(3)
      
      var=(/1d0,z,z*z,z*z*z,LOG(1-z),LOG(1-z)**2,LOG(1-z)**3&
      ,LOG(z),LOG(z)**2,LOG(z)**3,LOG(1-z)*Log(z),LOG(1-z)*Log(z)**2/)
      
      varX=(/1d0/z,LOG(z)/z/)
      
      !! summing regular part
      CqMain=SUM(CoeffReg_q_q*var)
      CqPrime=SUM(CoeffReg_q_qp*var)
      CqAnti=SUM(CoeffReg_q_qb*var)
      CqGluon=SUM(CoeffReg_q_g*var)
      
      !! adding x->0 singular part
      CqPrime=CqPrime+SUM(CoeffSingX_q_qp*varX)
      CqGluon=CqGluon+SUM(CoeffSingX_q_g*varX)
     
      !!combingin with PDFs
      value=(/&
      CqMain*PDFs(-3)+CqAnti*PDFs(3)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-2)+CqAnti*PDFs(2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-1)+CqAnti*PDFs(1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      0d0,&
      CqMain*PDFs(1)+CqAnti*PDFs(-1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(2)+CqAnti*PDFs(-2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(3)+CqAnti*PDFs(-3)+CqPrime*PDFsum+CqGluon*PDFs(0)/)
      
      !!adding + part
      value=value+(CoeffSing1_q_q(1)/(1d0-z)+CoeffSing1_q_q(2)*LOG(1d0-z)/(1d0-z))*(PDFs-PDFatX_global*FNPat1_global)
      
      !write(*,*)CqMain,CqAnti,CqPrime,singCoeff,singCoeffLog      
       MellinConvolutionVectorPart3=MellinConvolutionVectorPart3+Wi(j)*value
    end do
      MellinConvolutionVectorPart3=xr*MellinConvolutionVectorPart3
      !write(*,*) MellinConvolutionVectorPart
  end function MellinConvolutionVectorPart3
  
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!---------------------------------------------------------------------
!- This is the TMD function evaluated for all quarks simultaniously (-5..5) at x,bT,mu
!--    f =   -3,  -2,  -1,0,1,2,3
!--      = sbar,ubar,dbar,g,d,u,s
!!---Gluon contribution is undefined
!- The order is accumulative pertrubative order of coefficient =0,1,2 (LO,NLO,NNLO)
!---------------------------------------------------------------------
!---------------------------------------------------------------------
  function uTMDPDF_lowScale5(x,bT,mu)
  real*8,dimension(-5:5)::uTMDPDF_lowScale5
  real*8 :: x, bT,mu
  
  real*8 :: alpha
  real*8,dimension(-5:5) :: singConvol, singConvolLog
  real*8 :: Lmu,Nf,LLambda
  
  real*8,dimension(-5:5) :: deltaPart
  real*8,dimension(-5:5) :: convolutionPart
  
  Lmu=2.d0*Log(bT*mu*C0_inv_const)
  xCurrent=x
  bT_current=bT
  muCurrent=mu
  alpha=As(mu)
  if(mu<=mCHARM) then
    Nf=3d0
  elseif(mu<=mBOTTOM) then
    Nf=4d0
  else 
    Nf=5d0
  end if
  
  FNPat1_global=FNP(1d0,bT_current)
  PDFatX_global5=xPDFVECTOR5(xCurrent,muCurrent)
  
 !------------DELTA PART-------------------
 !Leading order is always here!! 
 ! NOTE: there are no mixture in this part  
  deltaPart=FNPat1_global*C_q_q_delta(alpha,Nf,Lmu)*PDFatX_global5
  
  if(order_global>=1 .or. includeRenormalon) then
 !!!!evaluate coefficients
  call Set_CoeffSing1_q_q(alpha,Nf,Lmu)
  call Set_CoeffReg_q_q(alpha,Nf,Lmu)
  
  if(order_global>=1) then
  
  call Set_CoeffReg_q_qb(alpha,Nf,Lmu)
  call Set_CoeffReg_q_qp(alpha,Nf,Lmu)
  call Set_CoeffReg_q_g(alpha,Nf,Lmu)
  
  call Set_CoeffSingX_q_g(alpha,Nf,Lmu)
  call Set_CoeffSingX_q_qp(alpha,Nf,Lmu)
  
  end if
  end if

    
  if(order_global>=1 .or. includeRenormalon) then
  convolutionPart=MellinConvolutionVector5(numberOfRecursion)
  else
  convolutionPart=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  end if
  
  !write(*,*) 'gluonMIXTUREPart =', gluonMIXTURE/x  
  !write(*,*) 'TDhat', (deltaPart+singularPart+regularPart)/x
  uTMDPDF_lowScale5=(deltaPart+convolutionPart)*(1d0/x)

  end function uTMDPDF_lowScale5
  
  
  function MellinConvolutionVector5(n)
    real*8,dimension(-5:5)::MellinConvolutionVector5
    real*8::xn,x1,x2
    integer::i,n
    
   ! write(*,*) 'INSIDE MELLIN CONVOLUTION'
    
    !write(*,*) regCoeff_q_q
    !write(*,*) regCoeff_q_qp
    !write(*,*) regCoeff_q_qb
    !write(*,*) regCoeffSing_q_qp
    
    if(n.le.1) then           ! same as n=1
         x1=xCurrent
         x2=1d0
         MellinConvolutionVector5=MellinConvolutionVectorPart5(x1,x2)
    else
      xn=(1-xCurrent)/float(n)
      MellinConvolutionVector5=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      x2=xCurrent
      Do i=1,n
         x1=x2
         x2=x1+xn
         MellinConvolutionVector5=MellinConvolutionVector5+MellinConvolutionVectorPart5(x1,x2)
      end do
    end if
    !!! subtract reast part of ()_+ distributions
    
    MellinConvolutionVector5=MellinConvolutionVector5+&
    (CoeffSing1_q_q(1)*LOG(1d0-xCurrent)+CoeffSing1_q_q(2)*(LOG(1d0-xCurrent))**2/2d0)*PDFatX_global5*FNPat1_global    

  end function MellinConvolutionVector5
  
  
  !!! function evalute mellin convolution from x0 to x1 for VECTOR 
  !!!using coefficeint Cqq,Cqq',Cqqbar
  !!! Single Gaussian
  function MellinConvolutionVectorPart5(x0,x1)
    real*8,dimension(-5:5)::MellinConvolutionVectorPart5,PDFs,value
    
    real*8 :: x0,x1,xm,xr,z,PDFsum,CqMain,CqAnti,CqPrime,CqGluon
    integer :: j,i
    real*8,dimension(1:12):: var
    real*8,dimension(1:2)::varX

    xm=0.5d0*(x1+x0)
    xr=0.5d0*(x1-x0)
    
    MellinConvolutionVectorPart5=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
    
    Do j=1,GaussOrder
      z=xm+xr*Xi(j)
      
      !!! PDFs are together with non-perp func!
      PDFs=FNP(z,bT_current)*xPDFVECTOR50(xCurrent/z,muCurrent)
      
      PDFsum=PDFs(-5)+PDFs(-4)+PDFs(-3)+PDFs(-2)+PDFs(-1)+PDFs(1)+PDFs(2)+PDFs(3)+PDFs(4)+PDFs(5)
      
      var=(/1d0,z,z*z,z*z*z,LOG(1-z),LOG(1-z)**2,LOG(1-z)**3&
      ,LOG(z),LOG(z)**2,LOG(z)**3,LOG(1-z)*Log(z),LOG(1-z)*Log(z)**2/)
      
      varX=(/1d0/z,LOG(z)/z/)
      
      !! summing regular part
      CqMain=SUM(CoeffReg_q_q*var)
      CqPrime=SUM(CoeffReg_q_qp*var)
      CqAnti=SUM(CoeffReg_q_qb*var)
      CqGluon=SUM(CoeffReg_q_g*var)
      
      !! adding x->0 singular part
      CqPrime=CqPrime+SUM(CoeffSingX_q_qp*varX)
      CqGluon=CqGluon+SUM(CoeffSingX_q_g*varX)
     
      !!combingin with PDFs
      value=(/&
      CqMain*PDFs(-5)+CqAnti*PDFs(5)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-4)+CqAnti*PDFs(4)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-3)+CqAnti*PDFs(3)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-2)+CqAnti*PDFs(2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-1)+CqAnti*PDFs(1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      0d0,&
      CqMain*PDFs(1)+CqAnti*PDFs(-1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(2)+CqAnti*PDFs(-2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(3)+CqAnti*PDFs(-3)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(4)+CqAnti*PDFs(-4)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(5)+CqAnti*PDFs(-5)+CqPrime*PDFsum+CqGluon*PDFs(0)/)
      
      !!adding + part
      value=value+(CoeffSing1_q_q(1)/(1d0-z)+CoeffSing1_q_q(2)*LOG(1d0-z)/(1d0-z))*(PDFs-PDFatX_global5*FNPat1_global)
      
      !write(*,*)CqMain,CqAnti,CqPrime,singCoeff,singCoeffLog      
       MellinConvolutionVectorPart5=MellinConvolutionVectorPart5+Wi(j)*value
    end do
      MellinConvolutionVectorPart5=xr*MellinConvolutionVectorPart5
      !write(*,*) MellinConvolutionVectorPart
  end function MellinConvolutionVectorPart5


  !---------------------------------------------------------------------
!- This is the TMD function evaluated for all quarks simultaniously (-3..3) at x,bT,mu the GLUON INCLUDED
!--    f =   -3,  -2,  -1,0,1,2,3
!--      = sbar,ubar,dbar,g,d,u,s
!!---Gluon contribution is undefined
!- The order is accumulative pertrubative order of coefficient =0,1,2 (LO,NLO,NNLO)
!---------------------------------------------------------------------
!---------------------------------------------------------------------
  function uTMDPDF_lowScale30(x,bT,mu)
  real*8,dimension(-3:3)::uTMDPDF_lowScale30
  real*8 :: x, bT,mu
  
  real*8 :: alpha
  real*8,dimension(-3:3) :: singConvol, singConvolLog
  real*8 :: Lmu,Nf,LLambda
  
  real*8,dimension(-3:3) :: deltaPart
  real*8,dimension(-3:3) :: convolutionPart
  
  Lmu=2.d0*Log(bT*mu*C0_inv_const)
  xCurrent=x
  bT_current=bT
  muCurrent=mu
  alpha=As(mu)
  if(mu<=mCHARM) then
    Nf=3d0
  elseif(mu<=mBOTTOM) then
    Nf=4d0
  else 
    Nf=5d0
  end if
  
  FNPat1_global=FNP(1d0,bT_current)
  PDFatX_global=xPDFVECTOR30(xCurrent,muCurrent)
  
 !------------DELTA PART-------------------
 !Leading order is always here!! 
 ! NOTE: there are no mixture in this part  
  deltaPart=FNPat1_global*C_q_q_delta(alpha,Nf,Lmu)*PDFatX_global
  deltaPart(0)=FNPat1_global*C_g_g_delta(alpha,Nf,Lmu)*PDFatX_global(0)
  
  if(order_global>=1 .or. includeRenormalon) then
 !!!!evaluate coefficients
  call Set_CoeffSing1_q_q(alpha,Nf,Lmu)
  call Set_CoeffReg_q_q(alpha,Nf,Lmu)
  
  if(order_global>=1) then
  
  call Set_CoeffSing1_g_g(alpha,Nf,Lmu)
  
  call Set_CoeffReg_g_q(alpha,Nf,Lmu)
  call Set_CoeffReg_g_g(alpha,Nf,Lmu)
  
  call Set_CoeffReg_q_qb(alpha,Nf,Lmu)
  call Set_CoeffReg_q_qp(alpha,Nf,Lmu)
  call Set_CoeffReg_q_g(alpha,Nf,Lmu)
  
  call Set_CoeffSingX_g_q(alpha,Nf,Lmu)
  call Set_CoeffSingX_g_g(alpha,Nf,Lmu)  
  
  call Set_CoeffSingX_q_g(alpha,Nf,Lmu)  
  call Set_CoeffSingX_q_qp(alpha,Nf,Lmu)
  
  end if
  end if

    
  if(order_global>=1 .or. includeRenormalon) then
  convolutionPart=MellinConvolutionVector30(numberOfRecursion)
  else
  convolutionPart=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  end if
  
  uTMDPDF_lowScale30=(deltaPart+convolutionPart)*(1d0/x)

  end function uTMDPDF_lowScale30
  
  
  function MellinConvolutionVector30(n)
    real*8,dimension(-3:3)::MellinConvolutionVector30,addV
    real*8::xn,x1,x2
    integer::i,n
    
    if(n.le.1) then           ! same as n=1
         x1=xCurrent
         x2=1d0
         MellinConvolutionVector30=MellinConvolutionVectorPart30(x1,x2)
    else
      xn=(1-xCurrent)/float(n)
      MellinConvolutionVector30=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      x2=xCurrent
      Do i=1,n
         x1=x2
         x2=x1+xn
         MellinConvolutionVector30=MellinConvolutionVector30+MellinConvolutionVectorPart30(x1,x2)
      end do
    end if
    !!! subtract reast part of ()_+ distributions
    
    addV=(CoeffSing1_q_q(1)*LOG(1d0-xCurrent)+CoeffSing1_q_q(2)*(LOG(1d0-xCurrent))**2/2d0)*PDFatX_global*FNPat1_global
    addV(0)=(CoeffSing1_g_g(1)*LOG(1d0-xCurrent)+CoeffSing1_g_g(2)*(LOG(1d0-xCurrent))**2/2d0)*PDFatX_global(0)*FNPat1_global
    
    MellinConvolutionVector30=MellinConvolutionVector30+addV
    
  end function MellinConvolutionVector30
  
  
  !!! function evalute mellin convolution from x0 to x1 for VECTOR 
  !!!using coefficeint Cqq,Cqq',Cqqbar
  !!! Single Gaussian
  function MellinConvolutionVectorPart30(x0,x1)
    real*8,dimension(-3:3)::MellinConvolutionVectorPart30,PDFs,value,addV
    
    real*8 :: x0,x1,xm,xr,z,PDFsum,CqMain,CqAnti,CqPrime,CqGluon,CgMain,CgQuark
    integer :: j,i
    real*8,dimension(1:12):: var
    real*8,dimension(1:2)::varX

    xm=0.5d0*(x1+x0)
    xr=0.5d0*(x1-x0)
    
    MellinConvolutionVectorPart30=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
    
    Do j=1,GaussOrder
      z=xm+xr*Xi(j)
      
      !!! PDFs are together with non-perp func!
      PDFs=FNP(z,bT_current)*xPDFVECTOR30(xCurrent/z,muCurrent)
      
      PDFsum=PDFs(-3)+PDFs(-2)+PDFs(-1)+PDFs(1)+PDFs(2)+PDFs(3)
      
      var=(/1d0,z,z*z,z*z*z,LOG(1-z),LOG(1-z)**2,LOG(1-z)**3&
      ,LOG(z),LOG(z)**2,LOG(z)**3,LOG(1-z)*Log(z),LOG(1-z)*Log(z)**2/)
      
      varX=(/1d0/z,LOG(z)/z/)
      
      !! summing regular part
      CqMain=SUM(CoeffReg_q_q*var)
      CqPrime=SUM(CoeffReg_q_qp*var)
      CqAnti=SUM(CoeffReg_q_qb*var)
      CqGluon=SUM(CoeffReg_q_g*var)
      
      CgMain=SUM(CoeffReg_g_g*var)
      CgQuark=SUM(CoeffReg_g_q*var)
      
      !! adding x->0 singular part
      CqPrime=CqPrime+SUM(CoeffSingX_q_qp*varX)
      CqGluon=CqGluon+SUM(CoeffSingX_q_g*varX)
      
      CgMain=CgMain+SUM(CoeffSingX_g_g*varX)
      CgQuark=CgQuark+SUM(CoeffSingX_g_q*varX)
     
      !!combingin with PDFs
      value=(/&
      CqMain*PDFs(-3)+CqAnti*PDFs(3)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-2)+CqAnti*PDFs(2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-1)+CqAnti*PDFs(1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CgMain*PDFs(0)+CgQuark*PDFsum,&
      CqMain*PDFs(1)+CqAnti*PDFs(-1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(2)+CqAnti*PDFs(-2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(3)+CqAnti*PDFs(-3)+CqPrime*PDFsum+CqGluon*PDFs(0)/)
      
      !!adding + part
      addV=(CoeffSing1_q_q(1)/(1d0-z)+CoeffSing1_q_q(2)*LOG(1d0-z)/(1d0-z))*(PDFs-PDFatX_global*FNPat1_global)
      addV(0)=(CoeffSing1_g_g(1)/(1d0-z)+CoeffSing1_g_g(2)*LOG(1d0-z)/(1d0-z))*(PDFs(0)-PDFatX_global(0)*FNPat1_global)
      
      value=value+addV
      
      !write(*,*)CqMain,CqAnti,CqPrime,singCoeff,singCoeffLog      
       MellinConvolutionVectorPart30=MellinConvolutionVectorPart30+Wi(j)*value
    end do
      MellinConvolutionVectorPart30=xr*MellinConvolutionVectorPart30
      !write(*,*) MellinConvolutionVectorPart
  end function MellinConvolutionVectorPart30
  
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !---------------------------------------------------------------------
!- This is the TMD function evaluated for all quarks simultaniously (-5..5) at x,bT,mu the GLUON INCLUDED
!--    f =   -3,  -2,  -1,0,1,2,3
!--      = sbar,ubar,dbar,g,d,u,s
!!---Gluon contribution is undefined
!- The order is accumulative pertrubative order of coefficient =0,1,2 (LO,NLO,NNLO)
!---------------------------------------------------------------------
!---------------------------------------------------------------------
  function uTMDPDF_lowScale50(x,bT,mu)
  real*8,dimension(-5:5)::uTMDPDF_lowScale50
  real*8 :: x, bT,mu
  
  real*8 :: alpha
  real*8,dimension(-5:5) :: singConvol, singConvolLog
  real*8 :: Lmu,Nf,LLambda
  
  real*8,dimension(-5:5) :: deltaPart
  real*8,dimension(-5:5) :: convolutionPart
  
  Lmu=2.d0*Log(bT*mu*C0_inv_const)
  xCurrent=x
  bT_current=bT
  muCurrent=mu
  alpha=As(mu)
  if(mu<=mCHARM) then
    Nf=3d0
  elseif(mu<=mBOTTOM) then
    Nf=4d0
  else 
    Nf=5d0
  end if
  
  FNPat1_global=FNP(1d0,bT_current)
  PDFatX_global5=xPDFVECTOR50(xCurrent,muCurrent)
  
 !------------DELTA PART-------------------
 !Leading order is always here!! 
 ! NOTE: there are no mixture in this part  
  deltaPart=FNPat1_global*C_q_q_delta(alpha,Nf,Lmu)*PDFatX_global5
  deltaPart(0)=FNPat1_global*C_g_g_delta(alpha,Nf,Lmu)*PDFatX_global5(0)

  if(order_global>=1 .or. includeRenormalon) then
 !!!!evaluate coefficients
  call Set_CoeffSing1_q_q(alpha,Nf,Lmu)
  call Set_CoeffReg_q_q(alpha,Nf,Lmu)
  
  if(order_global>=1) then
  
  call Set_CoeffSing1_g_g(alpha,Nf,Lmu)
  
  call Set_CoeffReg_g_q(alpha,Nf,Lmu)
  call Set_CoeffReg_g_g(alpha,Nf,Lmu)
  
  call Set_CoeffReg_q_qb(alpha,Nf,Lmu)
  call Set_CoeffReg_q_qp(alpha,Nf,Lmu)
  call Set_CoeffReg_q_g(alpha,Nf,Lmu)
  
  call Set_CoeffSingX_g_q(alpha,Nf,Lmu)
  call Set_CoeffSingX_g_g(alpha,Nf,Lmu)  
  
  call Set_CoeffSingX_q_g(alpha,Nf,Lmu)  
  call Set_CoeffSingX_q_qp(alpha,Nf,Lmu)
  
  end if
  end if

    
  if(order_global>=1 .or. includeRenormalon) then
  convolutionPart=MellinConvolutionVector50(numberOfRecursion)
  else
  convolutionPart=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
  end if

  uTMDPDF_lowScale50=(deltaPart+convolutionPart)*(1d0/x)

  end function uTMDPDF_lowScale50
  
  
  function MellinConvolutionVector50(n)
    real*8,dimension(-5:5)::MellinConvolutionVector50,addV
    real*8::xn,x1,x2
    integer::i,n
    
    if(n.le.1) then           ! same as n=1
         x1=xCurrent
         x2=1d0
         MellinConvolutionVector50=MellinConvolutionVectorPart50(x1,x2)
    else
      xn=(1-xCurrent)/float(n)
      MellinConvolutionVector50=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)
      x2=xCurrent
      Do i=1,n
         x1=x2
         x2=x1+xn
         MellinConvolutionVector50=MellinConvolutionVector50+MellinConvolutionVectorPart50(x1,x2)
      end do
    end if
    !!! subtract reast part of ()_+ distributions
    
    addV=(CoeffSing1_q_q(1)*LOG(1d0-xCurrent)+CoeffSing1_q_q(2)*(LOG(1d0-xCurrent))**2/2d0)*PDFatX_global5*FNPat1_global
    addV(0)=(CoeffSing1_g_g(1)*LOG(1d0-xCurrent)+CoeffSing1_g_g(2)*(LOG(1d0-xCurrent))**2/2d0)*PDFatX_global5(0)*FNPat1_global

    MellinConvolutionVector50=MellinConvolutionVector50+addV
    
  end function MellinConvolutionVector50
  
  
  !!! function evalute mellin convolution from x0 to x1 for VECTOR 
  !!!using coefficeint Cqq,Cqq',Cqqbar
  !!! Single Gaussian
  function MellinConvolutionVectorPart50(x0,x1)
    real*8,dimension(-5:5)::MellinConvolutionVectorPart50,PDFs,value,addV
    
    real*8 :: x0,x1,xm,xr,z,PDFsum,CqMain,CqAnti,CqPrime,CqGluon,CgMain,CgQuark
    integer :: j,i,nf,iq
    real*8,dimension(1:12):: var
    real*8,dimension(1:2)::varX

    xm=0.5d0*(x1+x0)
    xr=0.5d0*(x1-x0)
    
    MellinConvolutionVectorPart50=(/0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0,0d0/)

    if(muCurrent<=mCHARM) then
       nf=3
    elseif(muCurrent<=mBOTTOM) then
       nf=4
    else 
       nf=5
    end if

    Do j=1,GaussOrder
      z=xm+xr*Xi(j)
      
      !!! PDFs are together with non-perp func!
      PDFs=FNP(z,bT_current)*xPDFVECTOR50(xCurrent/z,muCurrent)

      PDFsum=PDFs(-5)+PDFs(-4)+PDFs(-3)+PDFs(-2)+PDFs(-1)+PDFs(1)+PDFs(2)+PDFs(3)+PDFs(4)+PDFs(5)
      
      var=(/1d0,z,z*z,z*z*z,LOG(1-z),LOG(1-z)**2,LOG(1-z)**3&
      ,LOG(z),LOG(z)**2,LOG(z)**3,LOG(1-z)*Log(z),LOG(1-z)*Log(z)**2/)
      
      varX=(/1d0/z,LOG(z)/z/)
      
      !! summing regular part
      CqMain=SUM(CoeffReg_q_q*var)
      CqPrime=SUM(CoeffReg_q_qp*var)
      CqAnti=SUM(CoeffReg_q_qb*var)
      CqGluon=SUM(CoeffReg_q_g*var)
      
      CgMain=SUM(CoeffReg_g_g*var)
      CgQuark=SUM(CoeffReg_g_q*var)
      
      !! adding x->0 singular part
      CqPrime=CqPrime+SUM(CoeffSingX_q_qp*varX)
      CqGluon=CqGluon+SUM(CoeffSingX_q_g*varX)
      
      CgMain=CgMain+SUM(CoeffSingX_g_g*varX)
      CgQuark=CgQuark+SUM(CoeffSingX_g_q*varX)
     
      !!combingin with PDFs
      value=(/&
      CqMain*PDFs(-5)+CqAnti*PDFs(5)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-4)+CqAnti*PDFs(4)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-3)+CqAnti*PDFs(3)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-2)+CqAnti*PDFs(2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(-1)+CqAnti*PDFs(1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CgMain*PDFs(0)+CgQuark*PDFsum,&
      CqMain*PDFs(1)+CqAnti*PDFs(-1)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(2)+CqAnti*PDFs(-2)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(3)+CqAnti*PDFs(-3)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(4)+CqAnti*PDFs(-4)+CqPrime*PDFsum+CqGluon*PDFs(0),&
      CqMain*PDFs(5)+CqAnti*PDFs(-5)+CqPrime*PDFsum+CqGluon*PDFs(0)/)

      !!adding + part
      addV=(CoeffSing1_q_q(1)/(1d0-z)+CoeffSing1_q_q(2)*LOG(1d0-z)/(1d0-z))*(PDFs-PDFatX_global5*FNPat1_global)
      addV(0)=(CoeffSing1_g_g(1)/(1d0-z)+CoeffSing1_g_g(2)*LOG(1d0-z)/(1d0-z))*(PDFs(0)-PDFatX_global5(0)*FNPat1_global)

      value=value+addV

      ! Set to zero channels that should not contribute
      if(nf.lt.5)then
         do iq=nf+1,5
            value(iq) = 0d0
            value(-iq) = 0d0
         enddo
      endif
      
      !write(*,*)CqMain,CqAnti,CqPrime,singCoeff,singCoeffLog      
       MellinConvolutionVectorPart50=MellinConvolutionVectorPart50+Wi(j)*value
    end do
      MellinConvolutionVectorPart50=xr*MellinConvolutionVectorPart50
      !write(*,*) MellinConvolutionVectorPart
  end function MellinConvolutionVectorPart50
  
  
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! USER DEFINED FUNCTIONS   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  

  !!Initialization routine for PDFs
  !!pathPDF is path to the PDF grid file which is read from paths-file
  subroutine InitializePDF_byUser(pathPDF)
    character(*)::pathPDF
    real*8::qqq
    prefix=pathPDF ! prefix for the grid files
    qqq=xPDF(0.1d0,91.d0,1)!!! this initializes mstw
  end subroutine InitializePDF_byUser
  
  !!!! return x*PDF(x,mu)
  !!!! enumeration of flavors
  !!!!  f = -5,-4, -3,  -2,  -1,0,1,2,3,5,4
  !!!!     = bbar,cbar,sbar,ubar,dbar,g,d,u,s,c,b
  function xPDF(x,Q,flavour)
      integer :: flavour
      real*8 :: x,Q, xPDF
      real*8 :: GetOnePDF
      
      xPDF=GetOnePDF(prefix,iset,x,Q,flavour)
  end function xPDF
  
    !!!!!!
  subroutine ModelInitialization_byUser()  
  !!!!!do you want to include renormalon correction?
  includeRenormalon=.false.
  !!!!! number of non-pertrubative parameters
  lambdaNPlength=2  
  end subroutine ModelInitialization_byUser
  
  
  !!! This is (flavor-independent) non-pertrubative function
  !!! non=pertrubative parameters are lambdaNP()
  !!! if renormalon correction is on, the parameter lambdaNP(2) stays infront of it.
  function FNP(z,bT)
  real*8::z,bT,FNP
  real*8::y2

  FNP=EXP(-lambdaNP(1)*bT)*(1+lambdaNP(2)*bT**2) !! model 1
  
  !y2=(z*bT**2)  
  !FNP=EXP(-10*y2/SQRT(1+z*y2*100d0/(lambdaNP(1))**2)) !! model 2  with fixed lambdaq=10
  end function FNP
  
end module uTMDPDF

! program example
! use uTMDPDF
! implicit none
!   
!   
!   call uTMDPDF_Initialize('NNLO','NNLO','NNLO')
!   
!   call uTMDPDF_SetLambdaNP((/0.180d0,0.0024d0/))
!   
!   call uTMDPDF_Report()
!   
!   write(*,*) uTMDPDF_lowScale30(0.1d0,1d0,9d0)  
!   write(*,*) uTMDPDF_lowScale(0,0.1d0,1d0,9d0)
!   write(*,*) uTMDPDF_lowScale(2,0.1d0,1d0,9d0)
!   write(*,*) uTMDPDF_lowScale(3,0.1d0,1d0,9d0)
!   
!   write(*,*) uTMDPDF_lowScale50(0.1d0,1d0,9d0)
!   write(*,*) uTMDPDF_lowScale(4,0.1d0,1d0,9d0)
!   write(*,*) uTMDPDF_lowScale(5,0.1d0,1d0,9d0)
!   
! end program example
