        PROGRAM GRIDCHECK
        IMPLICIT DOUBLE PRECISION (A-H,J-Z)
        INTEGER IL,IS,ISS,J,IC,IO,IH       
        COMMON / FRAGINI / INITF
 
         INITF=0 
 
         open(unit=4, file='distrika_chk.dat',status='unknown') !D(z,Q2)*z ka
 
 

 
         is = 2   ! 2 = 2014/2017    1 = 2007    
         ih = 2   ! 2 = kaon
         ic = 1   ! 1 = charge plus      -1 = charge minus    
         io=1     ! nlo




        Q2=91.2d0*91.2d0
         DO  i=1,40 
           z=10.d0**(-3.d0+i*3.d0/40.1)
         call fDSS(IS,IH,IC,IO,Z,Q2,U,UB,D,DB,S,SB,C,B,GL) 
         WRITE(4,900) Q2, z,(U+UB),(UB),(S+SB),
     .   C,B,GL,SB,D
         


         ENDDO


         Q2=10.0d0
        DO i=1,40 
        z=10.d0**(-3.d0+i*3.d0/40.1)
        call fDSS(IS,IH,IC,IO,Z,Q2,U,UB,D,DB,S,SB,C,B,GL) 
       WRITE(4,900) Q2, z,(U+UB),(UB),(S+SB),
     .   2*C,2*B,GL,SB,D
     
   
        ENDDO

 900           FORMAT (10(1PE10.3,X))

        END
