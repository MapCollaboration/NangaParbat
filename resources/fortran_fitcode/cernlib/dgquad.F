*
* $Id: dgquad.F,v 1.1.1.1 1996/04/01 15:02:15 mclareni Exp $
*
* $Log: dgquad.F,v $
* Revision 1.1.1.1  1996/04/01 15:02:15  mclareni
* Mathlib gen
*
*
*         Double Prec. version only on 32 bit machines.
c#include "gen/pilot.h"
c#if defined(CERNLIB_DOUBLE)
      FUNCTION DGQUAD(F,A,B,N)
c#include "gen/imp64.inc"
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION X(1),W(1)
      EXTERNAL F

      CALL D107D1(1,F,A,B,N,X,W)
      DGQUAD=X(1)
      RETURN
      END
c#endif
