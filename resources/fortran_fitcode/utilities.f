c-------------------------------------------------------------------------
c     running alpha_em
c-------------------------------------------------------------------------
      double precision FUNCTION ULALEM(QQ)
      implicit none
      double precision QQ 
      double precision AEMPI, RPIGG, pi 

C...Calculate real part of photon vacuum polarization.
C...For leptons simplify by using asymptotic (Q^2 >> m^2) expressions.
C...For hadrons use parametrization of H. Burkhardt et al.
C...See R. Kleiss et al, CERN 89-08, vol. 3, pp. 129-131.

      pi=dacos(-1.d0)
      AEMPI=(1.d0/137.0d0)/(3.*pi)
      IF(QQ.LT.2E-6) THEN
        RPIGG=0.
      ELSEIF(QQ.LT.0.09) THEN
        RPIGG=AEMPI*(13.4916+LOG(QQ))+0.00835*LOG(1.+QQ)
      ELSEIF(QQ.LT.9.) THEN
        RPIGG=AEMPI*(16.3200+2.*LOG(QQ))+0.00238*LOG(1.+3.927*QQ)
      ELSEIF(QQ.LT.1E4) THEN
        RPIGG=AEMPI*(13.4955+3.*LOG(QQ))+0.00165+0.00299*LOG(1.+QQ)
      ELSE
        RPIGG=AEMPI*(13.4955+3.*LOG(QQ))+0.00221+0.00293*LOG(1.+QQ)
      ENDIF
C...Calculate running alpha_em.
      ULALEM=(1.d0/137.0d0)/(1.-RPIGG)

      RETURN
      END

c-------------------------------------------------------------------------
c     runnning alpha_s/(4*pi) in terms of Lambda_QCD at NNLL
c-------------------------------------------------------------------------
      function aspi(Q)
       use com,only: c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5,ord
      implicit none
      integer nf
      real*8 aspi,Q,x,xlog
      real*8 b0,b1,b2,b1b0,b2b0
      real*8 lambda

      nf=0
      lambda=0d0
      aspi=0d0
      
      if(Q.lt.mc) then
        nf=3
        lambda=lambda3
      elseif(Q.ge.mc.and.Q.le.mb) then
        nf=4
        lambda=lambda4
      elseif(Q.gt.mb) then
        nf=5
        lambda=lambda5
      endif

      b0 = 11d0-2d0*nf/3d0
      b1 = 102d0-38d0*nf/3d0
      b2 = 1428.5d0-(5033d0*nf)/18d0+(325d0*nf**2d0)/54d0
      b1b0 = b1/(b0**2d0)
      b2b0 = b2/(b0*b0*b0)

      x = dlog(Q*Q/lambda/lambda)
      xlog = dlog(x)

      if (ord.eq.0) then
         aspi = 1d0/b0/x
      elseif (ord.eq.1) then
         aspi = 1d0/b0/x - b1b0/b0*(xlog/x/x)
      elseif (ord.eq.2) then
         aspi = 1d0/b0/x - b1b0/b0*(xlog/x/x)
     >        + b1b0*b1b0/b0*(xlog*xlog-xlog-1d0)/(x*x*x)
     >        + b2b0/b0/(x*x*x)
      endif
      
      return
      end
c-------------------------------------------------------------------------
c     8-point Gauss quadrature integral
c      
c               / xf
c               |
c       value = | dx func(x)         n > 1, number of divisions for xf-xi
c               |
c              / xi
c--------------------------------------------------------------------------
      function qgauss(func,xi,xf,n)
      implicit none
      integer i,n
      real*8 qgauss,func,xi,xf,xn,value,x1,x2,val
      external func

      if(n.le.1) then           ! same as n=1
         x1=xi
         x2=xf
         call gauss(func,x1,x2,val)
         qgauss=val
         return
      endif

      xn=(xf-xi)/float(n)
      value=0.d0
      x2=xi
      Do i=1,n
         x1=x2
         x2=x1+xn
         call gauss(func,x1,x2,val)
         value=value+val
      end do

      qgauss=value

      return
      end

c-------------------------------------------------
      subroutine gauss(func,xi,xf,value)
      implicit none
      integer j
      real*8 func,xi,xf,value,xm,xr,dx,x(8),w(8)
      real*8 eps
      data eps /1.0d-25/
      data w
     1   / 0.0271524594117540948517805725D0,
     2     0.0622535239386478928628438370D0,
     3     0.0951585116824927848099251076D0,
     4     0.1246289712555338720524762822D0,
     5     0.1495959888165767320815017305D0,
     6     0.1691565193950025381893120790D0,
     7     0.1826034150449235888667636680D0,
     8     0.1894506104550684962853967232D0 /
      DATA X
     1   / 0.9894009349916499325961541735D0,
     2     0.9445750230732325760779884155D0,
     3     0.8656312023878317438804678977D0,
     4     0.7554044083550030338951011948D0,
     5     0.6178762444026437484466717640D0,
     6     0.4580167776572273863424194430D0,
     7     0.2816035507792589132304605015D0,
     8     0.0950125098376374401853193354D0 /

      xm=0.5d0*(xf+xi)
      xr=0.5d0*(xf-xi)
      if (abs(xr).lt.eps) print *,
     $     'WARNING: Too high accuracy required for QGAUSS!'
 
      value=0.d0

      Do j=1,8
         dx=xr*x(j)
         value=value+w(j)*(func(xm+dx)+func(xm-dx))
      enddo
	
      value=xr*value

      return
      end
