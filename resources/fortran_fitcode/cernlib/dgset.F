*
* $Id: dgset.F,v 1.1.1.1 1996/04/01 15:02:15 mclareni Exp $
*
* $Log: dgset.F,v $
* Revision 1.1.1.1  1996/04/01 15:02:15  mclareni
* Mathlib gen
*
*
c#include "gen/pilot.h"
c#if defined(CERNLIB_DOUBLE)
      SUBROUTINE DGSET(A,B,N,X,W)
C
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
C
      EXTERNAL DGQUAD
      DIMENSION X(*),W(*)

      CALL D107D1(2,DGQUAD,A,B,N,X,W)
      RETURN
      END
C#endif
