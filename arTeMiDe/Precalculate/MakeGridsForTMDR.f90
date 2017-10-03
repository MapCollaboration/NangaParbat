!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe.precalculate 1.0
!
!	evaluates grids of renormalization group integrals and as(mu) for TMDR
!
!	ver 1.0: release (AV, 07.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
program MakeGridsForTMDR

  use UserDefinedAlphaS
  IMPLICIT NONE
      
  !This is internal parameter for Gaussian integral precision 16
  integer, parameter :: GaussOrder=16
  !Thse are weights and points for the Gaussian-Legandere integration procedure
      
  real*8 , parameter, dimension(1:GaussOrder) :: Wi = &
      (/0.027152459411958d0,0.0622535239381136d0,0.095158511682242d0,0.124628971255408d0,0.14959598881651d0,0.169156519395013d0,&
      0.182603415044924d0,0.189450610455068d0,0.189450610455068d0,0.18260341504492d0,0.169156519394984d0,0.149595988816574d0,&
      0.124628971255557d0,0.09515851168308d0,0.062253523939239d0,0.027152459411973d0/)
  real*8, parameter, dimension(1:GaussOrder) :: Xi= &
      (/-0.98940093499155d0,-0.94457502307378d0,-0.8656312023877d0,-0.75540440835508d0,-0.61787624440262d0,-0.45801677765722d0,&
     -0.28160355077925d0,-0.095012509837637d0,0.095012509837637d0,0.281603550779258d0,0.45801677765722d0,0.61787624440262d0,&
      0.7554044083550d0,0.86563120238764d0,0.94457502307317d0,0.98940093499154d0/)
      
      	!These are Gamma_Cusp (for quark) coefficients
	! Gamma_cusp_q(X,Nf) is for X=1,2,3 is pertrubative order, Nf=3,4,5 is number of flavours	
      real*8,parameter, dimension(1:3,3:5) :: Gamma_cusp_q= transpose(reshape((/&
		5.333333333333333d0, 5.333333333333333d0, 5.333333333333333d0, &
		48.69544319419009d0, 42.76951726826417d0, 36.84359134233824d0, &
		618.2248693918798d0, 429.5065747522099d0, 239.20803319895987d0 /), shape(Gamma_cusp_q)))
		
	!These are gamma_V (for quark) coefficients
	! gamma_V_q(X,Nf) is for X=1,2,3 is pertrubative order, Nf=3,4,5 is number of flavours	
      real*8,parameter, dimension(1:3,3:5) :: gamma_V_q= transpose(reshape((/&
		-8.0d0, -8.0d0, -8.0d0, &
		-29.243530284415503d0, -14.050795508138547d0, 1.1419392681384102d0, &
		-738.2562930508085d0, -491.96573445169145d0, -249.38756710544408d0 /), shape(gamma_V_q)))
	
	!These are gamma_V (for gluon) coefficients
	! gamma_V_g(X,Nf) is for X=1,2,3 is pertrubative order, Nf=3,4,5 is number of flavours	
      real*8,parameter, dimension(1:3,3:5) :: gamma_V_g= transpose(reshape((/&
		-18.0d0, -16.666666666666668d0, -15.333333333333334d0, &
		-227.8995118764504d0, -200.7014703660655d0, -173.50342885568062d0, &
		-3957.378545284555d0, -3206.1850399832547d0, -2485.5387880396356d0 /), shape(gamma_V_g)))
      
      
     integer:: i,z
     real*8:: mu,massCHARM,massBOTTOM
     character(30)::line
     real*8,parameter:: fourpi=12.566370614359172d0
     real*8,parameter::mu_ref=1d0
     
     call InitializeAs_byUser(massCHARM,massBOTTOM,line)
     
! The variable z=20*Log(2*mu), it runs from 0 to 200, that equal to range mu=0.5 GeV to 11 TeV (if needed build more)
! We build the table of 1/(alphas/(4 pi)), in variable Z=20 Log(2 mu)
! The table for I_Gamma is build as Exp(I_Gamma)    
     
     write(*,*) '----- arTeMiDe.precalculate ver 1.0 -----'
     write(*,*) '.. evaluating grids for TMDR'
     
     OPEN(UNIT=25, FILE="As_grid.dat", ACTION="write", STATUS="replace")
     
     WRITE(25,*) '# Loading AlphaStrong grids: '//trim(line)
     WRITE(25,*) '# z=20*Log(2*mu)'
     WRITE(25,*) '# number of points' 
     Write(25,*) 200
     WRITE(25,*) '# mu_ref' 
     Write(25,*) mu_ref
     WRITE(25,*) '	1/as			exp(Igamma,lo)		exp(Igamma,nlo)		exp(Igamma,nnlo)	&
	  exp(IgammaVq,lo)		exp(IgammaVq,nlo)		exp(IgammaVq,nnlo)	&
	  IgammaLog,lo		IgammaLog,nlo		IgammaLog,nnlo'
	  
     Do z=0,200
     mu=0.5d0*EXP(z/20.d0)
     WRITE(25,*) fourpi/alphaS_byUser(mu),&
		EXP(GammaEvolutor_q(mu,mu_ref,1)),EXP(GammaEvolutor_q(mu,mu_ref,2)),EXP(GammaEvolutor_q(mu,mu_ref,3)),&
		EXP(-Gamma_V_Evolutor_q(mu,mu_ref,1)),EXP(-Gamma_V_Evolutor_q(mu,mu_ref,2)),EXP(-Gamma_V_Evolutor_q(mu,mu_ref,3)),&
		EXP(-Gamma_V_Evolutor_g(mu,mu_ref,1)),EXP(-Gamma_V_Evolutor_g(mu,mu_ref,2)),EXP(-Gamma_V_Evolutor_g(mu,mu_ref,3)),&
		GammaLogEvolutor_q(mu,mu_ref,1),GammaLogEvolutor_q(mu,mu_ref,2),GammaLogEvolutor_q(mu,mu_ref,3)
		
     end do
     CLOSE ( 25, STATUS='KEEP')
     
     write(*,*) '.. evaluation finished.'
     write(*,*) '.. grids stored in As_grid.dat. (rename and copy to /Grids)'
     
     contains
     
     !!This is a Gaussian integration of as
  function a_s_INT_internal(Q, Q0, power)
    !use commonconst
    real*8::a_s_INT_internal
    real*8 :: Q,Q0
    integer :: power
  
    real*8 :: ba,ab !integration limits rescale constants
    real*8 :: value !partial sum
    integer :: iterator
  
    ba=(Q-Q0)*0.5d0
    ab=(Q+Q0)*0.5d0
  
    value=0.0d0
    do iterator=1, GaussOrder
      value=value+Wi(iterator)*(alphaS_byUser(ba*Xi(iterator)+ab)**power)/(ba*Xi(iterator)+ab)
    end do
  
    a_s_INT_internal=ba*value/fourpi**power
  
  end function a_s_INT_internal
  
  !_________________________________________________________________________________________________________________
!-----------------------------------------------------------
!Function evaluate a_s_INT(Q,Q0, power) = \int_{Q0}^Q a_s(mu)^power dmu/mu
! Q and Q0 in GeV
! power is integer
! It used the logarithmic decomposition of the carier for better accuracy (tested to be better then 0.01%)
!-----------------------------------------------------------
function a_s_INT(Q, Q0, power)
  real*8 :: a_s_INT,Q,Q0
  integer :: power
  
  real*8 :: value !partial sum
  real*8 :: quant
  integer :: n,i
  
  if(Q==Q0) then 
    value =0
  else if (Q>Q0) then
    quant=LOG(Q-Q0)
    n=8*FLOOR(quant)
    if (n>0) then
      value=a_s_INT_internal(Q0+EXP(quant/REAL(n)), Q0, power)
      do i=1,(n-1)
	value=value+a_s_INT_internal(Q0+EXP(quant*REAL(i+1)/REAL(n)), Q0+EXP(quant*REAL(i)/REAL(n)), power)
      end do
    else
      value=a_s_INT_internal(Q, Q0, power)
    end if
   else !Q0>Q
    quant=LOG(Q0-Q)
    n=8*FLOOR(quant)
    if (n>0) then
      value=a_s_INT_internal(Q+EXP(quant/REAL(n)), Q, power)
      do i=1,(n-1)
	value=value+a_s_INT_internal(Q+EXP(quant*REAL(i+1)/REAL(n)), Q+EXP(quant*REAL(i)/REAL(n)), power)
      end do
    else
      value=a_s_INT_internal(Q0, Q, power)
    end if
    value=-1.d0*value
  end if
  
  a_s_INT=value
  
end function a_s_INT

!-----------------------------------------------------------
!Function evaluate a_s_INTLOG(Q,Q0, power) = \int_{Q0}^Q a_s(mu,order)^power Log(mu^2) dmu/mu
! Q and Q0 in GeV
! power is integer
!-----------------------------------------------------------
function a_s_INTLOG(Q, Q0, power)
  real*8 :: a_s_INTLOG,Q,Q0
  integer :: power
  
  real*8 :: value !partial sum
  real*8 :: quant
  integer :: n,i
  
  if(Q==Q0) then 
    value =0
  else if (Q>Q0) then
    quant=LOG(Q-Q0)
    n=4*FLOOR(quant)
    if (n>0) then
      value=a_s_INTLOG_internal(Q0+EXP(quant/REAL(n)), Q0, power)
      do i=1,(n-1)
	value=value+a_s_INTLOG_internal(Q0+EXP(quant*REAL(i+1)/REAL(n)), Q0+EXP(quant*REAL(i)/REAL(n)), power)
      end do
    else
      value=a_s_INTLOG_internal(Q, Q0, power)
    end if
   else !Q0>Q
    quant=LOG(Q0-Q)
    n=4*FLOOR(quant)
    if (n>0) then
      value=a_s_INTLOG_internal(Q+EXP(quant/REAL(n)), Q, power)
      do i=1,(n-1)
	value=value+a_s_INTLOG_internal(Q+EXP(quant*REAL(i+1)/REAL(n)), Q+EXP(quant*REAL(i)/REAL(n)), power)
      end do
    else
      value=a_s_INTLOG_internal(Q0, Q, power)
    end if
    value=-1.d0*value
  end if
  
  a_s_INTLOG=value
  
end function a_s_INTLOG

function a_s_INTLOG_internal(Q, Q0, power)
  real*8 :: a_s_INTLOG_internal,Q,Q0
  integer :: power
  
  real*8 :: ba,ab !integration limits rescale constants
  real*8 :: value !partial sum
  integer :: iterator
  
  ba=(Q-Q0)*0.5d0
  ab=(Q+Q0)*0.5d0
  
  value=0.0d0
  do iterator=1, GaussOrder
    value=value+Wi(iterator)*(alphaS_byUser(ba*Xi(iterator)+ab)**power)*2.0d0*LOG((ba*Xi(iterator)+ab))/(ba*Xi(iterator)+ab)
  end do
  
  a_s_INTLOG_internal=ba*value/fourpi**power
  
end function a_s_INTLOG_internal
!_________________________________________________________________________________________________________________

!--------------------------------------------------------------------------------------------------------
! This function results \int_Q0^Q \Gamma_cusp (a) dmu/mu
! order=1,2,3 -- number of loops, Q,Q0 in GeV
! FOR QUARK
!--------------------------------------------------------------------------------------------------------
  function GammaEvolutor_q(Q,Q0,order)
    real*8 :: GammaEvolutor_q, Q,Q0
    integer :: order
    real*8 :: value
    real*8 :: M,M0 !limits of integration
    integer :: iterator
    
    value =0.0d0
    
    !if limits are inverse
    if (Q>Q0) then
      M=Q;M0=Q0;
    else if (Q<Q0) then
      M=Q0;M0=Q;
    else
      GammaEvolutor_q=0
      return
    end if
    
    !Evaluate accounting threasholds
    if (M0<massCHARM .and. M<massCharm) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,3)*a_s_INT(M,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,4)*a_s_INT(M,M0,iterator)
      end do
    else if (M0>=massBOTTOM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,5)*a_s_INT(M,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massCHARM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,4)*a_s_INT(M,massCHARM,iterator)+&
	      Gamma_cusp_q(iterator,3)*a_s_INT(massCHARM,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,5)*a_s_INT(M,massBOTTOM,iterator)+&
	      Gamma_cusp_q(iterator,4)*a_s_INT(massBOTTOM,massCHARM,iterator)+&
	      Gamma_cusp_q(iterator,3)*a_s_INT(massCHARM,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,5)*a_s_INT(M,massBOTTOM,iterator)+&
	      Gamma_cusp_q(iterator,4)*a_s_INT(massBOTTOM,M0,iterator)
      end do
    end if
    
    !if limits are inverse
    if (Q>Q0) then
      GammaEvolutor_q=value
    else if(Q<Q0) then
      GammaEvolutor_q=-1.0d0*value
    else
      GammaEvolutor_q=0.0d0      
    end if
    
  end function GammaEvolutor_q
 
 
 !--------------------------------------------------------------------------------------------------------
! This function results \int_Q0^Q \Gamma_cusp (a) dmu/mu
! order=1,2,3 -- number of loops, Q,Q0 in GeV
! FOR QUARK
!--------------------------------------------------------------------------------------------------------
  function GammaLogEvolutor_q(Q,Q0,order)
    real*8 :: GammaLogEvolutor_q, Q,Q0
    integer :: order
    real*8 :: value
    real*8 :: M,M0 !limits of integration
    integer :: iterator
    
    value =0.0d0
    
    !if limits are inverse
    if (Q>Q0) then
      M=Q;M0=Q0;
    else if (Q<Q0) then
      M=Q0;M0=Q;
    else
      GammaLogEvolutor_q=0
      return
    end if
    
    !Evaluate accounting threasholds
    if (M0<massCHARM .and. M<massCharm) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,3)*a_s_INTLOG(M,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,4)*a_s_INTLOG(M,M0,iterator)
      end do
    else if (M0>=massBOTTOM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,5)*a_s_INTLOG(M,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massCHARM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,4)*a_s_INTLOG(M,massCHARM,iterator)+&
	      Gamma_cusp_q(iterator,3)*a_s_INTLOG(massCHARM,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,5)*a_s_INTLOG(M,massBOTTOM,iterator)+&
	      Gamma_cusp_q(iterator,4)*a_s_INTLOG(massBOTTOM,massCHARM,iterator)+&
	      Gamma_cusp_q(iterator,3)*a_s_INTLOG(massCHARM,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM) then
      do iterator=1,order
	value=value+Gamma_cusp_q(iterator,5)*a_s_INTLOG(M,massBOTTOM,iterator)+&
	      Gamma_cusp_q(iterator,4)*a_s_INTLOG(massBOTTOM,M0,iterator)
      end do
    end if
    
    !if limits are inverse
    if (Q>Q0) then
      GammaLogEvolutor_q=value
    else if(Q<Q0) then
      GammaLogEvolutor_q=-1.0d0*value
    else
      GammaLogEvolutor_q=0.0d0      
    end if
    
  end function GammaLogEvolutor_q
 
 !--------------------------------------------------------------------------------------------------------
! This function results \int_Q0^Q \gamma_V (a) dmu/mu
! order=1,2,3 -- number of loops, Q,Q0 in GeV
! FOR QUARK
!--------------------------------------------------------------------------------------------------------
  function Gamma_V_Evolutor_q(Q,Q0,order) 
    real*8 :: Gamma_V_Evolutor_q, Q,Q0
    integer :: order
    real*8 :: value
    real*8 :: M,M0 !limits of integration
    integer :: iterator
    
    value =0.0d0
    
    !if limits are inverse
    if (Q>Q0) then
      M=Q;M0=Q0;
    else if (Q<Q0) then
      M=Q0;M0=Q;
    else
      Gamma_V_Evolutor_q=0
      return
    end if
    
    !Evaluate accounting threasholds
    if (M0<massCHARM .and. M<massCharm) then
      do iterator=1,order
	value=value+gamma_V_q(iterator,3)*a_s_INT(M,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_q(iterator,4)*a_s_INT(M,M0,iterator)
      end do
    else if (M0>=massBOTTOM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_q(iterator,5)*a_s_INT(M,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massCHARM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_q(iterator,4)*a_s_INT(M,massCHARM,iterator)+&
	      gamma_V_q(iterator,3)*a_s_INT(massCHARM,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_q(iterator,5)*a_s_INT(M,massBOTTOM,iterator)+&
	      gamma_V_q(iterator,4)*a_s_INT(massBOTTOM,massCHARM,iterator)+&
	      gamma_V_q(iterator,3)*a_s_INT(massCHARM,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_q(iterator,5)*a_s_INT(M,massBOTTOM,iterator)+&
	      gamma_V_q(iterator,4)*a_s_INT(massBOTTOM,M0,iterator)
      end do
    end if
    
    !if limits are inverse
    if (Q>Q0) then
      Gamma_V_Evolutor_q=value
    else if(Q<Q0) then
      Gamma_V_Evolutor_q=-1.0d0*value
    else
      Gamma_V_Evolutor_q=0.0d0      
    end if
    
  end function Gamma_V_Evolutor_q

!--------------------------------------------------------------------------------------------------------
! This function results \int_Q0^Q \gamma_V (a) dmu/mu
! order=1,2,3 -- number of loops, Q,Q0 in GeV
! FOR GLUON
!--------------------------------------------------------------------------------------------------------
  function Gamma_V_Evolutor_g(Q,Q0,order) 

    real*8 :: Gamma_V_Evolutor_g, Q,Q0
    integer :: order
    real*8 :: value
    real*8 :: M,M0 !limits of integration
    integer :: iterator
    
    value =0.0d0
    
    !if limits are inverse
    if (Q>Q0) then
      M=Q;M0=Q0;
    else if (Q<Q0) then
      M=Q0;M0=Q;
    else
      Gamma_V_Evolutor_g=0
      return
    end if
    
    !Evaluate accounting threasholds
    if (M0<massCHARM .and. M<massCharm) then
      do iterator=1,order
	value=value+gamma_V_g(iterator,3)*a_s_INT(M,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_g(iterator,4)*a_s_INT(M,M0,iterator)
      end do
    else if (M0>=massBOTTOM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_g(iterator,5)*a_s_INT(M,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massCHARM .and. M<massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_g(iterator,4)*a_s_INT(M,massCHARM,iterator)+&
	      gamma_V_g(iterator,3)*a_s_INT(massCHARM,M0,iterator)
      end do
    else if (M0<massCHARM .and. M>=massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_g(iterator,5)*a_s_INT(M,massBOTTOM,iterator)+&
	      gamma_V_g(iterator,4)*a_s_INT(massBOTTOM,massCHARM,iterator)+&
	      gamma_V_g(iterator,3)*a_s_INT(massCHARM,M0,iterator)
      end do
    else if (M0>=massCHARM .and. M>=massCHARM .and. M0<massBOTTOM) then
      do iterator=1,order
	value=value+gamma_V_g(iterator,5)*a_s_INT(M,massBOTTOM,iterator)+&
	      gamma_V_g(iterator,4)*a_s_INT(massBOTTOM,M0,iterator)
      end do
    end if
    
    !if limits are inverse
    if (Q>Q0) then
      Gamma_V_Evolutor_g=value
    else if(Q<Q0) then
      Gamma_V_Evolutor_g=-1.0d0*value
    else
      Gamma_V_Evolutor_g=0.0d0      
    end if
    
  end function Gamma_V_Evolutor_g

end program MakeGridsForTMDR