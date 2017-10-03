module UserDefinedAlphaS

real*8,public::alphaS_byUser
public::InitializeAs_byUser

 contains

!***********************************************************************************************
!	Write the initialization code for As
!	
!	do not forget to define variables massCHARM and massBOTTOM!
!	line is the name of grid (30 characters max)
!***********************************************************************************************
subroutine InitializeAs_byUser(massCHARM,massBOTTOM,line)

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!This ugly part is needed just to load the alpha s from MSTW
! stealed from MSTW examples.
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      INTEGER iset,ieigen,neigen,ix,nx,iq,nq,flav,alphaSorder,alphaSnfmax,lentrim
      PARAMETER(neigen=20)      ! number of eigenvectors
      DOUBLE PRECISION x,q,upv,dnv,usea,dsea,str,sbar,&
          chm,cbar,bot,bbar,glu,phot,upv1,dnv1,usea1,dsea1,str1,sbar1,&
          chm1,cbar1,bot1,bbar1,glu1,phot1,xphoton,&
          xpdf(-6:6),xf,xfp,xfm,xmin,xmax,q2min,q2max,&
          summin,summax,sum,distance,tolerance,&
          mCharm,mBottom,alphaSQ0,alphaSMZ
      CHARACTER prefix*50,prefix1*55,flavours(-5:5)*10, xfilename*50,qfilename*50
      COMMON/mstwCommon/distance,tolerance, mCharm,mBottom,alphaSQ0,alphaSMZ,alphaSorder,alphaSnfmax
      DATA flavours /"bbar","cbar","sbar","ubar","dbar","glu",&
          "dn","up","str","chm","bot"/
          
      real*8:: massCHARM
      real*8:: massBOTTOM
      CHARACTER(30)::line
      real*8::ALPHAS,GetOnePDF

      prefix = "MMHT2014/mmht2014nlo118" ! prefix for the grid files
      iset = 0
      
      
    write(*,*) '----------------initialization of MHT2014 --------------------------'
!C--   Specify the momentum fraction "x" and scale "q".
      x = 1.d-3
      q = 1.d1
      WRITE(6,*) "x = ",x,", q = ",q

      upv1 = GetOnePDF(prefix,iset,x,q,8)
! C----------------------------------------------------------------------
      WRITE(6,*) "mCharm = ",mCharm,", mBottom = ",mBottom
      WRITE(6,*) "alphaS(Q0) = ",alphaSQ0,", alphaS(MZ) = ",alphaSMZ,", alphaSorder = ",alphaSorder,&
          ", alphaSnfmax = ",alphaSnfmax

! C--   Call the initialisation routine with alpha_S(Q_0).
      CALL INITALPHAS(alphaSorder,1.D0,1.D0,alphaSQ0,mCharm,mBottom,1.D10)
! C--   Check calculated value of alpha_S(M_Z) matches stored value.
      WRITE(6,'(" alphaS(MZ) = ",F7.5," = ",F7.5)') ALPHAS(91.1876D0),alphaSMZ

! C--   Alternatively, call the initialisation routine with alpha_S(M_Z).
!      CALL INITALPHAS(alphaSorder,1.D0,91.1876D0,alphaSMZ, mCharm,mBottom,1.D10)
! C--   Check calculated value of alpha_S(Q_0) matches stored value.
!      WRITE(6,'(" alphaS(Q0) = ",F7.5," = ",F7.5)') ALPHAS(1.D0),alphaSQ0      
      
    write(*,*) '----------------initialization of MHT2014 finished --------------------------'    
    
    massCHARM=mCharm
    massBOTTOM=mBottom
    line='MMHT2014nlo'
end subroutine InitializeAs_byUser

!***********************************************************************************************
!	Write the code for alphas(mu)
!       alphas(mu)=g(mu)^2/4\pi
!***********************************************************************************************
function alphaS_byUser(mm)
  real*8::mm
  real*8::ALPHAS
  
  alphaS_byUser=ALPHAS(mm)
end function

end module UserDefinedAlphaS