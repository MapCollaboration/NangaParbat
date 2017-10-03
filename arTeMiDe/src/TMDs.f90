!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe 1.0
!
!	Evaluation of the TMDs
!	
!	if you use this module please, quote arXiv:1706.01473
!
!	ver 1.0: release (AV, 10.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
module TMDs
  use TMDR
  use uTMDPDF
  implicit none

  private
  
  real*8::bmax
  !!! This parameter indicate that for a given set of NP parameters convergent lost!
  !!! Check it by function IsConvergenceLost
  !!! set it to the lost value by function TMDconvergenceISlost
  logical::convergenceLOST
  integer::started=0
  
  public::TMDs_SetNPParameters,TMDs_SetScaleVariations,TMDs_convergenceISlost,TMDs_Initialize,TMDs_report
  logical,public::TMDs_IsConvergenceLost
  real*8,public:: GetAs
  real*8,dimension(-3:3),public:: uTMDPDF_3,uTMDPDF_30
  real*8,dimension(-5:5),public:: uTMDPDF_5,uTMDPDF_50
  
  !!!parameters for the uncertanty estimation
  real*8::c1_global,c3_global,c4_global
  
  contains 
  
    !sets the NP parameters of TMD model (bmax,gB,etc)
  subroutine TMDs_SetNPParameters(bmax_in,gK,lambda)
    real*8::bmax_in,gK
    real*8 :: lambda(:)
    
    bmax=bmax_in
    
    call uTMDPDF_SetLambdaNP(lambda)
    call TMDR_SetGk(gK)

    convergenceLOST=.false.
    
  end subroutine TMDs_SetNPParameters

  !! check by this functio nthe loss of convergence
  function TMDs_IsConvergenceLost()
    TMDs_IsConvergenceLost=convergenceLOST
  end function TMDs_IsConvergenceLost
  
  !! call this function if for a given set of NP parameters convergence is lost
  !! Unset the flag convergenceLOST reset NP parameters.
  subroutine TMDs_convergenceISlost()
    convergenceLOST=.true.
  end subroutine TMDs_convergenceISlost
  
  !print the report of current TMD state
  subroutine TMDs_report()
    write(*,*) '----------------------TMD package status report ------------------------------'
    call TMDR_report()
    call uTMDPDF_Report()
    write(*,'(A,F8.4)') 'b_max=',bmax
    write(*,*) '----------------------TMD package end of report ------------------------------'
  end subroutine TMDs_report
  
   !!! This subroutine can be called only ones per programm run in the very beginning
  !!! It initializes TMDRm abd TMDconvolution subpackages
  !!! It set the pertrubative orders(!), so pertrubative orders cannot be changed afterwards.
  !!! It also set the paths forPDF and As greeds according to orderPDF (NLO or NNLO).
  subroutine TMDs_Initialize(orderTMD)
    character(len=*)::orderTMD
    write(*,*) '---- arTeMiDe.TMDs ver 1.0: .... initialization'
    if(started==0) then
    
      
    
      SELECT CASE(orderTMD)
      CASE ("NLL")
	call uTMDPDF_Initialize('LO','NLO','NLO')
	call TMDR_Initialize('NLO','NNLO','NLO','NLL')
      CASE ("NLO")
	call uTMDPDF_Initialize('NLO','NLO','NLO')
	call TMDR_Initialize('NLO','NNLO','NLO','NLO')
      CASE ("NNLL")
	call uTMDPDF_Initialize('NLO','NNLO','NNLO')
	call TMDR_Initialize('NNLO','NNNLO','NNLO','NNLL')
      CASE ("NNLO")
	call uTMDPDF_Initialize('NNLO','NNLO','NNLO')
	call TMDR_Initialize('NNLO','NNNLO','NNLO','NNLO')
      CASE ("NNLO+")
	call uTMDPDF_Initialize('NNLO','NNLO','NNLO')
	call TMDR_Initialize('NNLO','NNNLO','NNNLO','NNNLL')
      CASE DEFAULT
	write(*,*) 'WARNING: arTeMiDe.TMDs_Initialize: unknown order . Switch to NLO.'
	call uTMDPDF_Initialize('NLO','NLO','NLO')
	call TMDR_Initialize('NLO','NNLO','NLO','NLO')
     END SELECT
    
    
      started=1
      
      c1_global=1d0
      c3_global=1d0
      c4_global=1d0!!!!not yet used
      
      bmax=1d0
      
      write(*,*) '---- arTeMiDe.TMDs ver 1.0: .... initialized'
    end if
  end subroutine TMDs_Initialize

    
  !!Returns the as(mu) from the package TMDR
  !! Only for incapsulation
   function GetAs(mu)
    real*8::mu
    GetAs=TMDR_as(mu)
   end function GetAs
  
  !!!! this routine set the variations of scales
  !!!! it is used for the estimation of errors
  subroutine TMDs_SetScaleVariations(c1_in,c3_in,c4_in)
    real*8::c1_in,c3_in,c4_in
    
    if(c1_in<0.1d0 .or. c1_in>10.d0) then
    write(*,*) 'WARNING: arTeMiDe.TMDs: variation in c1 is enourmous. c1 is set to 1'
    c1_global=1d0
    else
    c1_global=c1_in
    end if
    
    if(c3_in<0.1d0 .or. c3_in>10.d0) then
    write(*,*) 'WARNING: arTeMiDe.TMDs : variation in c3 is enourmous. c3 is set to 1'
    c3_global=1d0
    else
    c3_global=c3_in
    end if
    
    if(c4_in<0.1d0 .or. c4_in>10.d0) then
    write(*,*) 'WARNING: arTeMiDe.TMDs: variation in c1 is enourmous. c4 is set to 1'
    c4_global=1d0
    else
    c4_global=c4_in
    end if
    
  end subroutine TMDs_SetScaleVariations
  
  
  !!!!!!!! upolarized TMDPDF
  ! vector (sbar,ubar,dbar,??,d,u,s)
  function uTMDPDF_3(x,bt,muf,zetaf)
    real*8:: x,bt,muf,zetaf
    real*8:: mui,Rkernel    
    
    mui=c3_global*mu_LOW(bt)
    
   
    if(ABS(1d0-c1_global)<0.000001d0)	then
    
      Rkernel=TMDR_zetaP(bt,zetaf,muf,mui,1)
    else
      Rkernel=TMDR_full_zetaP(bt,zetaf,muf,mui,c1_global*mui/c3_global,1)
    end if
    uTMDPDF_3=Rkernel*uTMDPDF_lowScale3(x,bT,mui)
    
  end function uTMDPDF_3

    !!!!!!!! upolarized TMDPDF
  ! vector (sbar,ubar,dbar,g,d,u,s)
  function uTMDPDF_30(x,bt,muf,zetaf)
    real*8:: x,bt,muf,zetaf
    real*8:: mui,Rkernel    
    
    mui=c3_global*mu_LOW(bt)
    
   
    if(ABS(1d0-c1_global)<0.000001d0)	then
    
      Rkernel=TMDR_zetaP(bt,zetaf,muf,mui,1)
    else
      Rkernel=TMDR_full_zetaP(bt,zetaf,muf,mui,c1_global*mui/c3_global,1)
    end if
    uTMDPDF_30=Rkernel*uTMDPDF_lowScale30(x,bT,mui)
    
  end function uTMDPDF_30
  
    !!!!!!!! upolarized TMDPDF
  ! vector (bbar,cbar,sbar,ubar,dbar,??,d,u,s,c,b)
  function uTMDPDF_5(x,bt,muf,zetaf)
    real*8:: x,bt,muf,zetaf
    real*8:: mui,Rkernel    
    
    mui=c3_global*mu_LOW(bt)
    
   
    if(ABS(1d0-c1_global)<0.000001d0)	then
    
      Rkernel=TMDR_zetaP(bt,zetaf,muf,mui,1)
    else
      Rkernel=TMDR_full_zetaP(bt,zetaf,muf,mui,c1_global*mui/c3_global,1)
    end if
    uTMDPDF_5=Rkernel*uTMDPDF_lowScale5(x,bT,mui)
    
  end function uTMDPDF_5
  
  
      !!!!!!!! upolarized TMDPDF
  ! vector (bbar,cbar,sbar,ubar,dbar,??,d,u,s,c,b)
  function uTMDPDF_50(x,bt,muf,zetaf)
    real*8:: x,bt,muf,zetaf
    real*8:: mui,Rkernelq,Rkernelg
    real*8,dimension(-5:5):: lstmds

    mui=c3_global*mu_LOW(bt)
    
   
    if(ABS(1d0-c1_global)<0.000001d0)	then 
      Rkernelg=TMDR_zetaP(bt,zetaf,muf,mui,0)   
      Rkernelq=TMDR_zetaP(bt,zetaf,muf,mui,1)
    else
      Rkernelg=TMDR_full_zetaP(bt,zetaf,muf,mui,c1_global*mui/c3_global,0)
      Rkernelq=TMDR_full_zetaP(bt,zetaf,muf,mui,c1_global*mui/c3_global,1)
    end if
    lstmds = Rkernelq*uTMDPDF_lowScale50(x,bT,mui)
    lstmds(0) = lstmds(0) * Rkernelg / Rkernelq 
    uTMDPDF_50=lstmds

  end function uTMDPDF_50
  
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!USER DEFINED FUNCTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!This function is the mu(b)
  function mu_LOW(bt)
  real*8::bt,mu_LOW
  mu_LOW=C0_const*SQRT(1+bT**2/(bmax**2))/bT+1d0
  end function mu_LOW

end module TMDs

! program example
! use TMDs
!   implicit none
!   
!   call TMDs_Initialize('NNLO')
!   
!   write(*,*) uTMDPDF_3(0.1d0,0.1d0,911d0,91d0**2)
!   
!   call TMDs_SetNPParameters(1d0,0.1d0,(/0.001d0,-0.2d0/))
!   
!   write(*,*) uTMDPDF_3(0.1d0,1d0,911d0,91d0**2)
!   write(*,*) uTMDPDF_30(0.1d0,1d0,911d0,91d0**2)
!   write(*,*) uTMDPDF_5(0.1d0,1d0,911d0,91d0**2)
!   write(*,*) uTMDPDF_50(0.1d0,1d0,911d0,91d0**2)
! 
! end program example 
