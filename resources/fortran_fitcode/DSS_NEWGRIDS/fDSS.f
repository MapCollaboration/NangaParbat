
*************************************************************************
*                                                                                     
*        fDSS  UNPOLARIZED FRAGMENTATION FUNCTIONS                 
*                                                                                                                                                 
*  D.de Florian, R.Sassot, M.Stratmann   Phys.Rev.D75 114010 2007       
*                                *and*   Phys.Rev.D76 074033 2007                           
*  D.de Florian, M. Epele, R. Hernadez Pinto R.Sassot, M.Stratmann         
*                                        Phys.Rev.D91 014035 2014    
*  D.de Florian, M. Epele, R. Hernadez Pinto R.Sassot, M.Stratmann         
*                                                 arXiv:1702.06353  
c             
*                                                                                                                 
*     CALL fDSS (IS,IH,IC,IO, X, Q2, U, UB, D, DB, S, SB, C, B, GL)               
*                                                                                                                 
*  INPUT:    
*  IS = SET VERSION    1: DSS07  WARNING!!!!!!  MX HAS TO BET SET 35 FOR OLD DSS SETS  

*                      2: DSS14 (pion)/ DSS17(kaon) MX HAS TO BET SET 47 FOR NEW DSS
*
*  IH = hadron type    1: PION                                                       
*                      2: KAON                                  
*                                 3: PROTON           (only for DSS07)                               
*                                 4: CHARGED HADRONS  (only for DSS07)                           
*                                                                                                    
*  IC = Hadron Charge  0: 0 (as average of + and -)                    
*                      1: +                                        
*                     -1: -                                        
*                                                                  
*  IO= Order           0: LO       (only for DSS07)                                
*                      1: NLO                                      
*                                                                  
*             X                    (between  0.05   and  1.0)       
*            Q2 = scale in GeV**2 (between  1.0    and  1.D5)      
*             (for values outside the allowed range the program    
*              writes a warning and extrapolates to the x and      
*              Q2 values requested)                                
*                                                                  
*   OUTPUT: U, UB, D, DB, S, SB,   C,           B,       GL        
*           U Ubar D Dbar S Sbar Charm=Cbar Bottom=Bbar Gluon      
*           Always X times the distribution is returned            
*                                                                  
*                                                                  
*   COMMON:  The main program or the calling routine has to have   
*            a common block  COMMON / FRAGINI / FINI , and  FINI   
*            has always to be zero when DSS is called for the      
*            first time or when the SET has been changed.          
*                                                                  
********************************************************************

      SUBROUTINE fDSS (IS,IH,IC,IO, X, Q2, U, UB, D, DB, S, SB,C,B,GL)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      INTEGER FINI,NX,I,IS
      
c    WARNING!!!!!!    MX HAS TO BET SET 47 FOR THE NEW SETS  OR 35 FOR OLD DSS   
      PARAMETER (NPART=9, MX=47, NQ=24, NARG=2)
c      PARAMETER (NPART=9, MX=35, NQ=24, NARG=2)
      DIMENSION XUTOTF(MX,NQ), XDTOTF(MX,NQ), XSTOTF(MX,NQ)
      DIMENSION XUVALF(MX,NQ), XDVALF(MX,NQ), XSVALF(MX,NQ)
      DIMENSION XCTOTF(MX,NQ), XBTOTF(MX,NQ)
      DIMENSION XGF(MX,NQ), PARTON (NPART,NQ,MX-1)
      DIMENSION QS(NQ), XB(MX), XT(NARG), NA(NARG), ARRF(MX+NQ) 
      DIMENSION    XB01(35),XB02(47)   
      COMMON / FRAGINI / FINI
      SAVE XUTOTF, XDTOTF, XSTOTF, XCTOTF, XBTOTF, XGF, NA, ARRF
      SAVE XUVALF, XDVALF, XSVALF
*...BJORKEN-X AND Q**2 VALUES OF THE GRID :
       DATA QS / 1.d0, 1.25D0, 1.5D0, 2.5D0, 
     1           4.0D0, 6.4D0, 1.0D1, 1.5D1, 2.5D1, 4.0D1, 6.4D1,
     2           1.0D2, 1.8D2, 3.2D2, 5.8D2, 1.0D3, 1.8D3,
     3           3.2D3, 5.8D3, 1.0D4, 1.8D4, 3.2D4, 5.8D4, 1.0D5/
       DATA XB01 /0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
     4        0.095, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25, 0.275,
     5        0.3, 0.325, 0.35, 0.375, 0.4, 0.45,  0.5, 0.55,
     6        0.6, 0.65,  0.7,  0.75,  0.8, 0.85,  0.9 , 0.93, 1.0/
       DATA XB02  /0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09,
     4        0.095, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25, 0.275,
     5        0.3, 0.325, 0.35, 0.375, 0.4, 0.425, 0.45, 0.475,  0.5, 
     6        0.525, 0.55, 0.575, 0.6, 0.625, 0.65, 0.675, 0.7,
     7        0.725, 0.75, 0.775, 0.8, 0.825, 0.85, 0.875, 0.9, 
     8        0.925, 0.95, 0.975, 1.0/     
*...CHECK OF X AND Q2 VALUES : 
       IF ( (X.LT.0.05D0) .OR. (X.GT.1.0D0) ) THEN
           WRITE(6,91) 
  91       FORMAT (2X,'PARTON INTERPOLATION: X OUT OF RANGE')
C          STOP
       ENDIF
       IF ( (Q2.LT.1.D0) .OR. (Q2.GT.1.D5) ) THEN
           WRITE(6,92) 
  92       FORMAT (2X,'PARTON INTERPOLATION: Q2 OUT OF RANGE')
       ENDIF
*...INITIALIZATION :
*    SELECTION AND READING OF THE GRID :
       IF (IS.EQ.2)   THEN
       NX=47
       DO 1 I=1,47
       XB(I)=XB02(I)
 1    CONTINUE     
       ELSE
       NX=35
       DO 2 I=1,35
       XB(I)=XB01(I)
 2    CONTINUE                  
       ENDIF
       IF (FINI.NE.0) GOTO 16

       
      IF ((IS.EQ.2).and.(IH.EQ.1).and.(IO.EQ.1)) THEN
       IIREAD=10
       OPEN(IIREAD,FILE='PI_DSS14.GRID') 
      ELSEIF ((IS.EQ.2).and.(IH.EQ.2).and.(IO.EQ.1)) THEN
       IIREAD=10         
       OPEN(IIREAD,FILE='KA_2017.GRID')             
      ELSEIF ((IH.EQ.1).and.(IO.EQ.1)) THEN
       IIREAD=11  
       OPEN(IIREAD,FILE='PINLO.GRID')
      ELSEIF ((IH.EQ.1).and.(IO.EQ.0)) THEN
       IIREAD=12  
       OPEN(IIREAD,FILE='PILO.GRID')
      ELSEIF ((IH.EQ.2).and.(IO.EQ.1)) THEN
       IIREAD=11       
       OPEN(IIREAD,FILE='KANLO.GRID')
       ELSEIF ((IH.EQ.2).and.(IO.EQ.0)) THEN
       IIREAD=12       
       OPEN(IIREAD,FILE='KALO.GRID')
      ELSEIF ((IH.EQ.3).and.(IO.EQ.1)) THEN
       IIREAD=11       
       OPEN(IIREAD,FILE='PRONLO.GRID')       
      ELSEIF ((IH.EQ.3).and.(IO.EQ.0)) THEN
       IIREAD=12       
       OPEN(IIREAD,FILE='PROLO.GRID')       
      ELSEIF ((IH.EQ.4).and.(IO.EQ.1)) THEN
       IIREAD=11       
       OPEN(IIREAD,FILE='HNLO.GRID')       
      ELSEIF ((IH.EQ.4).and.(IO.EQ.0)) THEN
       IIREAD=12       
       OPEN(IIREAD,FILE='HLO.GRID')       
	ELSE
         WRITE(6,93)
 93      FORMAT (2X,' WRONG SET')
         STOP
      END IF


C
       DO 15 M = 1, NX-1 
       DO 15 N = 1, NQ
       READ(IIREAD,90) PARTON(1,N,M), PARTON(2,N,M), PARTON(3,N,M), 
     1                 PARTON(4,N,M), PARTON(5,N,M), PARTON(6,N,M),
     2                 PARTON(7,N,M), PARTON(8,N,M), PARTON(9,N,M)
  90   FORMAT (9(1PE10.3))
  15   CONTINUE
       CLOSE(IIREAD)
C
      FINI = 1
*....ARRAYS FOR THE INTERPOLATION SUBROUTINE :
      DO 10 IQ = 1, NQ
      DO 20 IX = 1, NX-1
        XB0 = XB(IX) 
        XB1 = 1.D0-XB(IX)
        XUTOTF(IX,IQ) = PARTON(1,IQ,IX) / (XB1**4 * XB0**0.5)
        XDTOTF(IX,IQ) = PARTON(2,IQ,IX) / (XB1**4 * XB0**0.5)
        XSTOTF(IX,IQ) = PARTON(3,IQ,IX) / (XB1**4 * XB0**0.5) 
        XCTOTF(IX,IQ) = PARTON(4,IQ,IX) / (XB1**7 * XB0**0.3) 
        XBTOTF(IX,IQ) = PARTON(5,IQ,IX) / (XB1**7 * XB0**0.3)
        XGF(IX,IQ)    = PARTON(6,IQ,IX) / (XB1**4 * XB0**0.3)
        XUVALF(IX,IQ) = PARTON(7,IQ,IX) / (XB1**4 * XB0**0.5)
        XDVALF(IX,IQ) = PARTON(8,IQ,IX) / (XB1**4 * XB0**0.5)
        XSVALF(IX,IQ) = PARTON(9,IQ,IX) / (XB1**4 * XB0**0.5)
  20  CONTINUE
        XUTOTF(NX,IQ) = 0.D0
        XDTOTF(NX,IQ) = 0.D0
        XSTOTF(NX,IQ) = 0.D0
        XCTOTF(NX,IQ) = 0.D0
        XBTOTF(NX,IQ) = 0.D0
        XGF(NX,IQ)    = 0.D0
        XUVALF(NX,IQ) = 0.D0
        XDVALF(NX,IQ) = 0.D0
        XSVALF(NX,IQ) = 0.D0
  10  CONTINUE  
      NA(1) = NX
      NA(2) = NQ
      DO 30 IX = 1, NX
        ARRF(IX) = DLOG(XB(IX))
  30  CONTINUE
      DO 40 IQ = 1, NQ
        ARRF(NX+IQ) = DLOG(QS(IQ))
  40  CONTINUE
  16  CONTINUE
*...INTERPOLATION :
      XT(1) = DLOG(X)
      XT(2) = DLOG(Q2)
      UTOT = FINT(NARG,XT,NA,ARRF,XUTOTF) * (1.D0-X)**4 * X**0.5
      DTOT = FINT(NARG,XT,NA,ARRF,XDTOTF) * (1.D0-X)**4 * X**0.5 
      STOT = FINT(NARG,XT,NA,ARRF,XSTOTF) * (1.D0-X)**4 * X**0.5
      CTOT = FINT(NARG,XT,NA,ARRF,XCTOTF) * (1.D0-X)**7 * X**0.3
      BTOT = FINT(NARG,XT,NA,ARRF,XBTOTF) * (1.D0-X)**7 * X**0.3
      GL   = FINT(NARG,XT,NA,ARRF,XGF)    * (1.D0-X)**4 * X**0.3
      UVAL = FINT(NARG,XT,NA,ARRF,XUVALF) * (1.D0-X)**4 * X**0.5
      DVAL = FINT(NARG,XT,NA,ARRF,XDVALF) * (1.D0-X)**4 * X**0.5 
      SVAL = FINT(NARG,XT,NA,ARRF,XSVALF) * (1.D0-X)**4 * X**0.5
       
       Up  = (UTOT+UVAL)/2.
       UBp = (UTOT-UVAL)/2.
       Dp  = (DTOT+DVAL)/2.
       DBp = (DTOT-DVAL)/2.
       Sp  = (STOT+SVAL)/2.
       SBp = (STOT-SVAL)/2.
       Cp  =  CTOT/2.
       Bp  =  BTOT/2.
              
       IF (IC.EQ.1) THEN
       U  = Up
       UB = UBp
       D  = Dp 
       DB = DBp
       S  = Sp
       SB = SBp
       C  = Cp
       B  = Bp
       ELSEIF (IC.EQ.-1) THEN
       U  = UBp
       UB = Up
       D  = DBp 
       DB = Dp
       S  = SBp
       SB = Sp
       C  = Cp
       B  = Bp
       ELSEIF (IC.EQ.0) THEN
       U  = (UBp+Up)/2.
       UB =  U
       D  = (DBp+Dp)/2. 
       DB =  D
       S  = (SBp+Sp)/2.
       SB =  S
       C  =  Cp
       B  =  Bp 
       ELSE
         WRITE(6,94)
 94      FORMAT (2X,' WRONG CHARGE')
         STOP
       END IF 
 60   RETURN
       END
*
*...CERN LIBRARY ROUTINE E104 (INTERPOLATION) :
*
      FUNCTION FINT(NARG,ARG,NENT,ENT,TABLE)
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
CMS      DIMENSION ARG(5),NENT(5),ENT(63),TABLE(882)
      DIMENSION ARG(2),NENT(2),ENT(59),TABLE(840)
      DIMENSION D(5),NCOMB(5),IENT(5)
      KD=1
      M=1
      JA=1
         DO 5 I=1,NARG
      NCOMB(I)=1
      JB=JA-1+NENT(I)
         DO 2 J=JA,JB
      IF (ARG(I).LE.ENT(J)) GO TO 3
    2 CONTINUE
      J=JB
    3 IF (J.NE.JA) GO TO 4
      J=J+1
    4 JR=J-1
      D(I)=(ENT(J)-ARG(I))/(ENT(J)-ENT(JR))
      IENT(I)=J-JA
      KD=KD+IENT(I)*M
      M=M*NENT(I)
    5 JA=JB+1
      FINT=0.D0
   10 FAC=1.D0
      IADR=KD
      IFADR=1
         DO 15 I=1,NARG
      IF (NCOMB(I).EQ.0) GO TO 12
      FAC=FAC*(1.D0-D(I))
      GO TO 15
   12 FAC=FAC*D(I)
      IADR=IADR-IFADR
   15 IFADR=IFADR*NENT(I)
      FINT=FINT+FAC*TABLE(IADR)
      IL=NARG
   40 IF (NCOMB(IL).EQ.0) GO TO 80
      NCOMB(IL)=0
      IF (IL.EQ.NARG) GO TO 10
      IL=IL+1
         DO 50  K=IL,NARG
   50 NCOMB(K)=1
      GO TO 10
   80 IL=IL-1
      IF(IL.NE.0) GO TO 40
      RETURN
      END
      
