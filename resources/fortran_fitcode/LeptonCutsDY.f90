!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe 1.0
!
!	Evaluation of the leptonic cuts for the DrellYan
!	
!	if you use this module please, quote 1706.01473
!
!	ver 1.0: release (AV, 10.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
module LeptonCutsDY
implicit none
private

!!!Parameters of cut and cross-section
real*8::pTlim,etaMaxExp,etaMinExp,Q,y,etaMax,etaMin
!!! These are l^+ l^- l'^+ l'^- for lepton pair
real*8,dimension(3)::lp,llp,lm,llm

!!Number of maximum iterations in adptive Simpson
integer,parameter::maxIteration=10
!!! number of divisions in Simpsons
integer,parameter::num=16!!
!! Tolerance (absolute)
real*8,parameter::tolerance=0.000001d0

real*8::Z_global,qT_global,Q2_global,QQ_global

public:: SetCutParameters
public:: CutFactor,CutFactor2,CutFactor3

  !This is internal parameter for Gaussian integral precision (can be 8, 12 or 16)
  !Thse are weights and points for the Gaussian-Legandere integration procedure
!   integer, parameter :: GaussOrder=12
!   real*8, parameter, dimension(1:GaussOrder) :: Xi= &
!       (/-0.98156063424671d0,-0.90411725637047d0,-0.76990267419430d0,-0.58731795428661d0,-0.367831498998180d0,-0.12523340851146d0,&
!       0.12523340851146d0,0.36783149899818d0,0.58731795428661d0,0.76990267419430d0,0.90411725637047d0,0.98156063424671d0/)
!   
!   real*8, parameter, dimension(1:GaussOrder) :: Wi = &
!       (/0.0471753363865208d0,0.10693932599531d0,0.16007832854332d0,0.20316742672306d0,0.233492536538353d0,0.249147045813402d0,&
!       0.249147045813402d0,0.23349253653835d0,0.203167426723072d0,0.160078328543352d0,0.10693932599537d0,0.047175336386521d0/)
      
!    integer, parameter :: GaussOrder=15
!    real*8, parameter, dimension(1:GaussOrder) :: Xi= &
!    (/-0.9879925180204854,-0.937273392400706,-0.8482065834104272,-0.7244177313601701,-0.5709721726085388,-0.3941513470775634,&
!      -0.20119409399743451,0.,0.20119409399743451,0.3941513470775634,0.5709721726085388,0.7244177313601701,0.8482065834104272,&
!      0.937273392400706,0.9879925180204854/)
!    real*8, parameter, dimension(1:GaussOrder) :: Wi = &
!    (/0.030753241996180732,0.07036604748811874,0.10715922046683254,0.13957067792619823,0.16626920581701898,0.18616100001556024,&
!      0.19843148532711158,0.2025782419255613,0.19843148532711158,0.18616100001556024,0.16626920581701898,0.13957067792619823,&
!      0.10715922046683254,0.07036604748811874,0.030753241996180732/)
     
     integer, parameter :: GaussOrder=7
  real*8, parameter, dimension(1:GaussOrder) :: Xi= &
      (/-0.9491079123427585,-0.7415311855993945,-0.4058451513773972,0.,0.4058451513773972,0.7415311855993945,0.9491079123427585/)
  
  real*8, parameter, dimension(1:GaussOrder) :: Wi = &
      (/0.12948496616886973,0.27970539148927703,0.3818300505051188,0.4179591836734694,0.3818300505051188,0.27970539148927703,&
      0.12948496616886973/)
   
! real*8::Qmin_grid,Qmax_grid,ymin_grid,ymax_grid,qt_grid
! integer::Qsize,ysize,qtSize
! 
! public:: MakeGrid
contains


!SEt parameters of cut 
subroutine SetCutParameters(pT_in,etaMin_in,etaMax_in)
  real*8::pT_in,etaMax_in,etaMin_in
  
  pTlim=pT_in**2
  etaMax=etaMax_in+tolerance
  etaMin=etaMin_in-tolerance
  etaMaxExp=EXP(2*etaMax)
  etaMinExp=EXP(2*etaMin)
  
end subroutine SetCutParameters


!!!!! Integration by 2d adaptive Simpson in eta-\phi plane (not very good)
function CutFactor2(qT,Q_in,y_in)
  real*8:: qT,CutFactor2,Q_in,y_in
  
  Q=Q_in
  y=y_in
  
  qT_global=qT
  Z_global=qT**2/(Q**2+qT**2)
  Q2_global=Q**2
  QQ_global=SQRT(Q2_global+qT_global**2)
  
  if(etaMin<etaMax) then
  CutFactor2=SimpsonsA2(etaMin,etaMax,0d0,3.141592653589793d0,1)
  else
  CutFactor2=0d0
  end if
  
end function CutFactor2


!!!!integrand in teh coordinates rapidity-angle
function Integrand2(h1,p1)
  real*8:: h1,p1,Integrand2
  real*8::cosp1,chhy,l1square,l2square,exp2h2,l1
  
  cosp1=COS(p1)
  chhy=COSH(h1-y)
  
  l1=Q2_global/2d0/(QQ_global*COSH(h1-y)-qT_global*Cos(p1))
  l1square=l1**2
  
  l2square=qT_global**2+l1square-2d0*qT_global*l1*COS(p1)
  exp2h2=(EXP(2d0*y+h1)*QQ_global-EXP(y+2d0*h1)*l1)/(EXP(h1)*QQ_global-EXP(y)*l1)
  
    
  If((l1square>pTlim).and.(l2square>pTlim).and.&
    (etaMax>h1).and.(etaMaxExp>exp2h2).and.&
    (h1>etaMin).and.(exp2h2>etaMinExp)) then
    
    Integrand2=2d0*l1square*(Q2_global-(l1square+l2square)*(1-Z_global))/Q2_global/(1-Z_global)*0.238732d0*2d0/Q2_global
    else
    Integrand2=0d0
   end if  
end function Integrand2

!!!!the theta (0 or 1) funciton of the integrand in teh coordinates rapidity-angle
function Integrand2THETA(h1,p1)
  real*8:: h1,p1
  integer::Integrand2THETA
  real*8::cosp1,chhy,l1square,l2square,exp2h2,l1
  
  cosp1=COS(p1)
  chhy=COSH(h1-y)
  
  l1=Q2_global/2d0/(QQ_global*COSH(h1-y)-qT_global*Cos(p1))
  l1square=l1**2
  
  l2square=qT_global**2+l1square-2d0*qT_global*l1*COS(p1)
  exp2h2=(EXP(2d0*y+h1)*QQ_global-EXP(y+2d0*h1)*l1)/(EXP(h1)*QQ_global-EXP(y)*l1)
  
    
  If((l1square>pTlim).and.(l2square>pTlim).and.&
    (etaMax>h1).and.(etaMaxExp>exp2h2).and.&
    (h1>etaMin).and.(exp2h2>etaMinExp)) then
    Integrand2THETA=1
    else
    Integrand2THETA=0
   end if  
end function Integrand2THETA

!!!!! Integration by 2d adaptive Simpson in theta-\phi plane (not very good (worse))
!!!evluate the cut factor for a particular value of qT
function CutFactor(qT,Q_in,y_in)
  real*8::CutFactor,qT,pT,etaMax,etaMin,Q_in,y_in
  real*8::Z,W,f
  
  Q=Q_in
  y=y_in
  
  Z=qT**2/(Q**2+qT**2)
  W=SQRT(Z+sinh(y)**2)
  f=Q/Sqrt(8d0)
  
  !define components  
  lp(1)=f*EXP(-y)/SQRT(1-Z)
  lp(2)=-f*SQRT(Z)/W
  lp(3)=-f*(Z-EXP(-y)*Sinh(y))/SQRT(1-Z)/W
  
  lm(1)=f*EXP(y)/SQRT(1-Z)
  lm(2)=-lp(2)
  lm(3)=-f*(Z+EXP(y)*Sinh(y))/SQRT(1-Z)/W
  
  llp(1)=lp(1)
  llp(2)=-lp(2)
  llp(3)=-lp(3)
  
  llm(1)=lm(1)
  llm(2)=lp(2)
  llm(3)=-lm(3)  
  CutFactor=SimpsonsA(0d0,3.141592653589793d0,0d0,3.141592653589793d0,1)
  
end function CutFactor

!! Evaluate adaptive simpsons
recursive function SimpsonsA2(t1,t2,p1,p2,iter) RESULT(SA)
  real*8::t1,t2,p1,p2,SA
  integer::iter,i,j,num2
  real*8::dt,dp,S0,S1
  real*8,dimension(0:num,0:num)::M
  
  dt=(t2-t1)/num
  dp=(p2-p1)/num  
  num2=num/2
  
  S0=0d0
  do i=0,num
    do j=0,num
    M(i,j)=Integrand2(t1+REAL(i)*dt,p1+REAL(j)*dp)
    S0=S0+M(i,j)*Simp(i,num)*Simp(j,num)
    end do
  end do
  
  S1=0d0
  do i=0,num2
    do j=0,num2
    S1=S1+(M(i,j)+M(i+num2,j)+M(i,j+num2)+M(i+num2,j+num2))*Simp(i,num2)*Simp(j,num2)
    end do
  end do
  
  S0=dt*dp/9d0*S0
  S1=dt*dp/9d0*S1
  
  if(S0-S1<tolerance) then
    SA=S0
  else
    if(iter<maxIteration) then
      SA=SimpsonsA2(t1,(t2+t1)/2d0,p1,(p2+p1)/2d0,iter+1)+&
		SimpsonsA2((t2+t1)/2d0,t2,p1,(p2+p1)/2d0,iter+1)+&
		SimpsonsA2(t1,(t2+t1)/2d0,(p2+p1)/2d0,p2,iter+1)+&
		SimpsonsA2((t2+t1)/2d0,t2,(p2+p1)/2d0,p2,iter+1)
    else
      write(*,*) 'WARNING: PHASE INTEGRATION REACH LIMIT OF ITERATION: with ERROR: ', S0-S1
      SA=S0
    end if
  end if
end function SimpsonsA2

!! Evaluate adaptive simpsons
recursive function SimpsonsA(t1,t2,p1,p2,iter) RESULT(SA)
  real*8::t1,t2,p1,p2,SA
  integer::iter,i,j,num2
  real*8::dt,dp,S0,S1
  real*8,dimension(0:num,0:num)::M
  
  dt=(t2-t1)/num
  dp=(p2-p1)/num  
  num2=num/2
  
  S0=0d0
  do i=0,num
    do j=0,num
    M(i,j)=Integrand(t1+REAL(i)*dt,p1+REAL(j)*dp)
    S0=S0+M(i,j)*Simp(i,num)*Simp(j,num)
    end do
  end do
  
  S1=0d0
  do i=0,num2
    do j=0,num2
    S1=S1+(M(i,j)+M(i+num2,j)+M(i,j+num2)+M(i+num2,j+num2))*Simp(i,num2)*Simp(j,num2)
    end do
  end do
  
  S0=dt*dp/9d0*S0
  S1=dt*dp/9d0*S1
  
  if(S0-S1<tolerance) then
    SA=S0
  else
    if(iter<maxIteration) then
      SA=SimpsonsA(t1,(t2+t1)/2d0,p1,(p2+p1)/2d0,iter+1)+&
		SimpsonsA((t2+t1)/2d0,t2,p1,(p2+p1)/2d0,iter+1)+&
		SimpsonsA(t1,(t2+t1)/2d0,(p2+p1)/2d0,p2,iter+1)+&
		SimpsonsA((t2+t1)/2d0,t2,(p2+p1)/2d0,p2,iter+1)
    else
      write(*,*) 'WARNING: PHASE INTEGRATION REACH LIMIT OF ITERATION: with ERROR: ', S0-S1
      SA=S0
    end if
  end if
end function SimpsonsA

function Simp(i,n)
  integer::i,n
  real*8::Simp
  if((i==0).or.(i==n)) then
  Simp=1d0
  else 
    if(MOD(i,2)==1) then
    Simp=4d0
    else
    Simp=2d0
    end if
  end if
end function Simp


function Integrand(t1,p1)
  real*8:: kp,km,kkp,kkm,A,B,t1,p1,Integrand
  
  A=Cos(p1)*Sin(t1)
  B=Cos(t1)
  kp=lp(1)+lp(2)*A+lp(3)*B
  kkp=llp(1)+llp(2)*A+llp(3)*B
  km=lm(1)+lm(2)*A+lm(3)*B
  kkm=llm(1)+llm(2)*A+llm(3)*B
    
  If((kp*km>(pTlim/2d0)).and.(kkm*kkp>(pTlim/2d0)).and.&
    (etaMaxExp>km/kp).and.(etaMaxExp>kkm/kkp).and.&
    (km/kp>etaMinExp).and.(kkm/kkp>etaMinExp)) then
    
    Integrand=(kp*kkm+kkp*km)*sin(t1)*0.238732d0*2d0/Q**2
    else
    Integrand=0d0
   end if  
end function Integrand


!!!we fix phi and integrate accurately over eta. First we find boundaries, then integrate
!!! In the following we assume that Q>pT,and Q>qT (more then 2?)
!!! then there is a contribution at h=y
function IntegralOverEtaFixedPhi(phi)
  real*8:: IntegralOverEtaFixedPhi,phi
  real*8::eta1,eta2
  real*8::xm,xr,value
  integer::j
  
  if(Integrand2THETA(y,phi)==0) then
  !!!! Here is the point of assumption!! because if Q~qT the integration region is difficult and the boundaries may be inproper
  IntegralOverEtaFixedPhi=0d0
  else
  !!lower boundary
  eta1=FindBoundary(etaMin-0.0001d0,y,phi)
  !!upper boundary
  eta2=FindBoundary(y,etaMax+0.0001d0,phi)
  !write(*,*) eta1,eta2
  
   xm=0.5d0*(eta1+eta2)
   xr=0.5d0*ABS(eta1-eta2)
      
   value=0.d0
   Do j=1,GaussOrder
         value=value+Wi(j)*Integrand2(xm+xr*Xi(j),phi)
   end do	
   IntegralOverEtaFixedPhi=xr*value
   end if
end function IntegralOverEtaFixedPhi

!! Search for the boundary of integration between t1 and t2 at fixed phi
!! by devision on 2
function FindBoundary(eta1_in,eta2_in,phi)
  real*8::FindBoundary,eta1,eta2,phi,eta3,eta1_in,eta2_in
  integer:: v1,v2,v3,i
  
  eta1=eta1_in
  eta2=eta2_in
  v1=Integrand2THETA(eta1,phi)
  v2=Integrand2THETA(eta2,phi)
  
  if(v1==v2) then
    write(*,*) 'ERROR LeptonCuts: problem with boundary evaluation. Probably Q is too close to qT. EVALUATION STOP'
    write(*,*) 'Problematic values:'
    write(*,*) 'Kinematic:  Q=',SQRT(Q2_global), 'qT=',qT_global,'y=',y
    write(*,*) 'Cut params: pT=',SQRT(pTlim),'eta -(',etaMin,etaMax,')'
    stop
    FindBoundary=(eta1+eta2)/2d0
  else
    do 
      eta3=(eta1+eta2)/2d0
      v3=Integrand2THETA(eta3,phi)
      if(v3==v1) then 
	eta1=eta3
      else	
	eta2=eta3
      end if
      i=i+1
      if (ABS(eta1-eta2)<tolerance) exit
    end do 
    FindBoundary=(eta1+eta2)/2d0
  end if
end function FindBoundary


!!!! Integration is done by more accurate method. Secting the phi-plane, and define the boundaries of eta
!!!! Unfortunately works only for large enough Q.
!!!! Gives very precise result 10^-5 accurasy
function CutFactor3(qT,Q_in,y_in)
  real*8:: qT,CutFactor3,Q_in,y_in
  real*8:: dphi
  integer :: i
  
  Q=Q_in
  y=y_in  
  
  qT_global=qT
  Z_global=qT**2/(Q**2+qT**2)
  Q2_global=Q**2
  QQ_global=SQRT(Q2_global+qT_global**2)
  
  if(etaMin<etaMax) then
  if(y<etaMin .or. y>etaMax) then
    CutFactor3=0d0
  else
    CutFactor3=0d0
    dphi=3.14159265358979d0/num
    do i=0,num
      CutFactor3=CutFactor3+Simp(i,num)*IntegralOverEtaFixedPhi(i*dphi)
    end do
      CutFactor3=CutFactor3*dphi/3d0    
  end if
  else
    CutFactor3=0d0
  end if
  
end function CutFactor3

end module LeptonCutsDY
! 
!  program example
!  use LeptonCutsDY
!  implicit none
!  integer::i
!  
! 
!  
!  call SetCutParameters(20d0,-2.1d0,2.1d0)
!  
!  write(*,*) CutFactor3(15d0,91d0,0.34d0),CutFactor3(15d0,91d0,1.9d0)
!  end program example