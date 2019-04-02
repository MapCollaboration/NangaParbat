c--------------------------------------------------------------
c     HYBRID EVOLUTION KERNEL:
c     S_pert(\mu_i=Qi,\mu_f=Qf) * D_R à la CSS
c     using 4 different prescriptions
c--------------------------------------------------------------
c     Resummed D for fixed scale \mu_i=Qi evaluated à la CSS:
c     D(bT*;\mu_b) + \int_{\mu_b}^{Qi} G_cusp + high-bT model
c     we use different prescriptions for
c     separate pert and non-pert bT values (b* and exp)
c     parametrize the high-bT tail (gaussian and log)
c
c     gauss ==> BLNY model hep-ph/0212159
c     log ==> Aidala&co. arXiv/1401.2654 with bNP=2GeV-1
c     in each of the 4 configurations bmax,g2 play a role
c--------------------------------------------------------------
      subroutine kernel_hyb(b,Qi,Qf,kernel)
       use com,only : c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5,
     &                ord,mu_b,alf2,zeta3,nf !aggiunto nf nel kernel
      implicit none

      real*8 D_hyb,b,Qi,Qf,kernel
      real*8 d20,res,res1

      d20 = CF*CA*(404d0/27d0-14d0*zeta3)
     >     -112d0/27d0*CF*nf/2d0

      call expgammaF(Qi,Qf,res1)
      call intcusp(b,Qi,res)

      D_hyb=0d0
      if((ord.eq.0).or.(ord.eq.1)) then ! LL or NLL
         D_hyb = 0 + res
      elseif(ord.eq.2) then     ! NNLL
         D_hyb = d20*alf2 + res
      endif

      kernel = res1*dexp(-2d0*dlog(Qf/Qi)*D_hyb)

      return
      end

c--------------------------------------------------------------
c     NEW COLLINS EVOLUTION KERNEL:
c     S_pert(\mu_i=mub,\mu_f=Qf) * D à la Collins (D+high-bT model)
c     using 4 different prescriptions
c--------------------------------------------------------------
      subroutine kernel_css(Qf,kernel)
       use com,only : c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5,
     &                ord,mu_b,alf2,zeta3,nf
      implicit none
      real*8 Qf,kernel,d20,res

      d20 = CF*CA*(404d0/27d0-14d0*zeta3)
     >     -112d0/27d0*CF*nf/2d0

      call expgammaF(mu_b,Qf,res)

      if((ord.eq.0).or.(ord.eq.1)) then
         kernel = res
      elseif(ord.eq.2) then
         kernel = res*dexp(-2d0*dlog(Qf/mu_b)*(
     >        d20*alf2))
      endif

      return
      end

c--------------------------------------------------------------
c     NEW COLLINS EVOLUTION KERNEL:
c     S_pert(\mu_i=mub,\mu_f=Qf) * D à la Collins (D+high-bT model)
c     using 4 different prescriptions
c     with the NUMERICAL SUDAKOV
c--------------------------------------------------------------
      subroutine kernel_css_num(Qf,kernel)
       use com,only : c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5,
     &                ord,mu_b,alf2,zeta3,nf
      implicit none
      real*8 Qf,kernel,d20,res

      d20 = CF*CA*(404d0/27d0-14d0*zeta3)
     >     -112d0/27d0*CF*nf/2d0

      call NumSudakov(mu_b,Qf,res)

      if((ord.eq.0).or.(ord.eq.1)) then
         kernel = res
      elseif(ord.eq.2) then
         kernel = res*dexp(-2d0*dlog(Qf/mu_b)*(
     >        d20*alf2))
      endif

      return
      end
c--------------------------------------------------------------
c     EIS EVOLUTION KERNEL (arXiv: 1208.1281)
c     S_pert(\mu_i=Qi,\mu_f=Qf) * D_R (without high-bT model)
c     3 different prescriptions
c--------------------------------------------------------------
      subroutine kernel_eis(b,Qi,Qf,kernel,eisflag)
       use com, only: bmax,g2
      implicit none

      integer eisflag
      real*8 b,Qi,Qf,kernel,linmodel,logmodel
      real*8 res,resDR,bc

c     convergence radius
      bc=3.0d0

      call expgammaF(Qi,Qf,res)

      if(b.lt.bc) then
         call DR(b,Qi,resDR)
         kernel = res*dexp(-2d0*dlog(Qf/Qi)*resDR)
      elseif(b.ge.bc) then
         if (eisflag.eq.1) then
            kernel=0d0
         elseif (eisflag.eq.2) then
            call DR(bc,Qi,resDR)
            linmodel = resDR*(1d0 + 1d0/4d0*g2*(b-bc)**2d0)
            kernel = res*dexp(-2d0*dlog(Qf/Qi)*linmodel)
         elseif (eisflag.eq.3) then
            call DR(bc,Qi,resDR)
            logmodel=resDR*(1d0
     >           +1d0/4d0*g2*4d0*dlog(1d0+(b-bc)*(b-bc)/4d0))
            kernel = res*dexp(-2d0*dlog(Qf/Qi)*logmodel)
         endif
      endif

      return
      end

c--------------------------------------------------------------
c     Resummed D function ala EIS
c--------------------------------------------------------------
      subroutine DR(b,mu,res)
       use com,only : c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5,
     &                ord,zeta3,nf
      implicit none

      real*8 res,b,mu,pi2,cusp0,cusp1,cusp2
      real*8 beta0,beta1,beta2,X,alf,alf2,aspi,d20

      external aspi

      pi2=pi*pi

c     equations (C6)
      beta0 = 11d0-2d0/3d0*nf
      beta1 = 102d0-38d0/3d0*nf
      beta2 = 2857d0/54d0*CA*CA*CA
     $     +(2d0*CF*CF-205d0/9d0*CF*CA-1415d0/27d0*CA*CA)*nf/2d0
     $     +(44d0/9d0*CF+158d0/27d0*CA)*nf*nf/4d0

c     equations (C4)
      cusp0=4d0*CF
      cusp1=4d0*CF*((67d0/9d0-pi2/3d0)*CA-10d0/9d0*nf)
      cusp2=4d0*CF*(CA*CA*(245d0/6d0-134d0*pi2/27d0+11d0*pi2*pi2/45d0
     $     +22d0/3d0*zeta3)+CA*nf/2d0*(-418d0/27d0+40d0*pi2/27d0
     $     -56d0*zeta3/3)+CF*nf/2d0*(-55d0/3d0+16d0*zeta3)
     $     -16d0/27d0*nf*nf/4d0)

c     equation (16)
      if(ord.eq.0) then         ! LL
         alf = aspi(mu)
         X = alf*beta0*dlog(mu*mu*b*b/c02)
         res = -cusp0/2d0/beta0*dlog(1d0-X)
      elseif(ord.eq.1) then     ! NLL
         alf = aspi(mu)
         X = alf*beta0*dlog(mu*mu*b*b/c02)
         res = -cusp0/2d0/beta0*dlog(1d0-X)+1d0/2d0*alf/(1d0-X)*(-beta1
     $        /beta0/beta0*cusp0*(X+dlog(1d0-X))+cusp1/beta0*X)
      elseif(ord.eq.2) then     ! NNLL
         alf = aspi(mu)
         alf2 = alf*alf
         X = alf*beta0*dlog(mu*mu*b*b/c02)

c     equation (12)
         d20 = CF*CA*(404d0/27d0-14d0*zeta3)-112d0/27d0*CF*nf/2d0
         res = -cusp0/2d0/beta0*dlog(1d0-X)+1d0/2d0*alf/(1d0-X)*(-beta1
     $        /beta0/beta0*cusp0*(X+dlog(1d0-X))+cusp1/beta0*X)
     $        +1d0/2d0*alf2/(1d0-X)/(1d0-X)*(2d0*d20
     $        +cusp2/2d0/beta0*(X*(2d0-X))+beta1*cusp1/2d0/beta0/beta0*
     $        (X*(X-2d0)-2d0*dlog(1d0-X))+beta2*cusp0/2d0/beta0/beta0*
     $        X*X+beta1*beta1*cusp0/2d0/beta0/beta0/beta0*(dlog(1d0-X)*
     $        dlog(1d0-X)-X*X))
      endif

      return
      end

c--------------------------------------------------------------
c     Calculation of exp{-S_pert}
c     Qi,Qf stay for \mu_i,\mu_f (more general)
c--------------------------------------------------------------

c--------------------------------------------------------------
c     \exp[ - \int_{\mu_i}^{\mu_f} ( A \ln(Q^2/mubar^2) + B ) ]
c     Inputs: \mu_i,\mu_f, which can be Qi,Qf or \mu_b,Qf
c     The integrand is taken consistently at LL,NLL,NNLL depending on
c     the value of the common variable ord: 0,1,2 for LL,NLL,NNLL
c     Output: Revo
c--------------------------------------------------------------
      subroutine expgammaF(Qi,Qf,Revo)
       use com,only : c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5 !aggiunto nf nel common
      implicit none

      integer nf
      real*8 Qi,Qf,Revo
      real*8 funcsp
      real*8 xq,xup,xlow,xuplog,xlowlog,sp1,sp2,sp3,sp,lambda

      sp=0d0

      if(Qi.le.mc) then
         if(Qf.le.mc) then
            nf = 3              ! Integrate from Qi to Qf
            lambda = lambda3
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
         elseif(Qf.gt.mc.and.Qf.le.mb) then
            nf = 3              ! Integrate from Qi to mc
            lambda = lambda3
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0 * dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mc to Qf
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         elseif(Qf.gt.mb) then
            nf = 3              ! Integrate from Qi to mc
            lambda = lambda3
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mc to mb
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 5              ! Integrate from mb to Qf
            lambda = lambda5
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp3 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2 + sp3
         endif
      elseif(Qi.gt.mc.and.Qi.le.mb) then
         if(Qf.le.mc) then
            nf = 4              ! Integrate from Qi to mc
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 3              ! Integrate from mc to Qf
            lambda = lambda3
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         elseif(Qf.gt.mc.and.Qf.le.mb) then
            nf = 4              ! Integrate from Qi to Qf
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
         elseif(Qf.gt.mb) then
            nf = 4              ! Integrate from Qi to mb
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 5              ! Integrate from mb to Qf
            lambda = lambda5
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         endif
      elseif(Qi.gt.mb) then
         if(Qf.le.mc) then
            nf = 5              ! Integrate from Qi to mb
            lambda = lambda5
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mb to mc
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 3              ! Integrate from mc to Qf
            lambda = lambda3
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp3 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2 + sp3
         elseif(Qf.gt.mc.and.Qf.le.mb) then
            nf = 5              ! Integrate from Qi to mb
            lambda = lambda5
            xq = 2d0*dlog(Qf/lambda)
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mb to Qf
            lambda = lambda4
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         elseif(Qf.gt.mb) then
            nf = 5              ! Integrate from Qi to Qf
            lambda = lambda5
            xq = 2d0*dlog(Qf/lambda)
            xup = xq
            xlow = 2d0*dlog(Qi/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp = funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
         endif
      endif

      Revo = dexp( -sp )

      return
      end

c--------------------------------------------------------------
c     accuracy&summary
c--------------------------------------------------------------
c     Integrand to solve analytically:
c     \int_{Qi}^{Qf} [ A \ln(Q^2/mu^2) + B  ]
c     ord=0,1,2 for LL,NLL,NNLL
c--------------------------------------------------------------
      function funcsp(xq,xup,xuplog,xlow,xlowlog,nf)
       use com,only : ord
      implicit none
      integer nf
      real*8 funcsp,xq,xup,xuplog,xlow,xlowlog
      real*8 funcspLL,funcspNLL,funcspNNLL
      external funcspLL,funcspNLL,funcspNNLL

      funcsp=0d0
      if(ord.eq.0) then
         funcsp=funcspLL(xq,xup,xuplog,xlow,xlowlog,nf)
      elseif(ord.eq.1) then
         funcsp=funcspNLL(xq,xup,xuplog,xlow,xlowlog,nf)
      elseif(ord.eq.2) then
         funcsp=funcspNNLL(xq,xup,xuplog,xlow,xlowlog,nf)
      endif

      return
      end

c--------------------------------------------------------------
c   Integrand of the S_pert ;
c   Qi,Qf stay for \mu_i,\mu_f (more general)
c--------------------------------------------------------------

c--------------------------------------------------------------
c     Integrand to solve analytically at LL:
c     \int_{Qi}^{Qf} [ A \ln(Q^2/mu^2) + B ]
c     A = cusp. We take A0
c     B = non-cusp. At LL it is 0.
c--------------------------------------------------------------
      function funcspLL(xq,xup,xuplog,xlow,xlowlog,nf)
       use com,only : c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5
      implicit none
      integer nf
      real*8 funcspLL,xq,xup,xuplog,xlow,xlowlog
      real*8 b0,G0
      real*8 CG0

      G0 = 4d0*CF
      b0 = 11d0-2d0*nf/3d0
      CG0 = G0/(2d0*b0)*(-xup+xq*xuplog)
     >     -G0/(2d0*b0)*(-xlow+xq*xlowlog)

      funcspLL = CG0

      return
      end


c--------------------------------------------------------------
c     Integrand to solve analytically at NLL:
c     \int_{Qi}^{Qf} [ A \ln(Q^2/mu^2) + B ]
c     A = cusp. We take A0 and A1.
c     B = non-cusp. We take B0.
c--------------------------------------------------------------
      function funcspNLL(xq,xup,xuplog,xlow,xlowlog,nf)
       use com,only: zeta3,c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5
      implicit none
      integer nf
      real*8 funcspNLL,xq,xup,xuplog,xlow,xlowlog
      real*8 b0,b1,b1b0,b1b02,G0,G1,gV0
      real*8 CG0,CG1,CgV0
      real*8 xup2,xup3
      real*8 xlow2,xlow3
      real*8 xuplog2,xlowlog2


      G0 = 4d0*CF
      G1 = 4d0*CF*( (67d0/9d0 - pi*pi/3d0)*CA - 10d0/9d0*nf )
      gV0 = -6d0*CF

      b0 = 11d0-2d0*nf/3d0
      b1 = 102d0-38d0*nf/3d0

      b1b0  = b1/(b0**2d0)
      b1b02 = b1b0*b1b0

      xup2=xup*xup
      xup3=xup2*xup

      xuplog2=xuplog*xuplog

      xlow2=xlow*xlow
      xlow3=xlow2*xlow

      xlowlog2=xlowlog*xlowlog

      CgV0 = gV0/(2d0*b0)*(xuplog-b1b0*((-1d0-xuplog)/xup))
     >     - gV0/(2d0*b0)*(xlowlog-b1b0*((-1d0-xlowlog)/xlow))

      CG0 = G0/(2d0*b0)*(-xup+xq*xuplog-b1b0*(-xq/xup-xq*xuplog/xup
     >     -xuplog*xuplog/2d0))
     >     -G0/(2d0*b0)*(-xlow+xq*xlowlog-b1b0*(-xq/xlow
     >     -xq*xlowlog/xlow-xlowlog*xlowlog/2d0))

      CG1 = G1/(2d0*b0*b0)*(-xq/xup-xuplog
     >     +b1b02*(1d0/4d0/xup2-2d0*xq/27d0/xup3+xuplog/2d0/xup2
     >     -2d0*xq*xuplog/9d0/xup3+xuplog2/2d0/xup2
     >     -xq*xuplog2/3d0/xup3)
     >     -2d0*b1b0*(1d0/xup-xq/4d0/xup2+xuplog/xup
     >     -xq*xuplog/2d0/xup2))
     >     -G1/(2d0*b0*b0)*(-xq/xlow-xlowlog
     >     +b1b02*(1d0/4d0/xlow2-2d0*xq/27d0/xlow3+xlowlog/2d0/xlow2
     >     -2d0*xq*xlowlog/9d0/xlow3+xlowlog2/2d0/xlow2
     >     -xq*xlowlog2/3d0/xlow3)
     >     -2d0*b1b0*(1d0/xlow-xq/4d0/xlow2+xlowlog/xlow
     >     -xq*xlowlog/2d0/xlow2))

      funcspNLL = CgV0 + CG0 + CG1

      return
      end

c--------------------------------------------------------------
c     Integrand to solve analytically at NNLL:
c     \int_{Qi}^{Qf} [ A \ln(Q^2/mu^2) + B ]
c     A = cusp. We take A0, A1 and A2.
c     B = non-cusp. We take B0 and B1.
c--------------------------------------------------------------
      function funcspNNLL(xq,xup,xuplog,xlow,xlowlog,nf)
       use com,only: zeta3,c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5
      implicit none
      integer nf
      real*8 funcspNNLL,xq,xup,xuplog,xlow,xlowlog
      real*8 b0,b1,b2,b1b0,b2b0,G0,G1,G2,gV0,gV1
      real*8 CG0,CG1,CG2,CgV0,CgV1
      real*8 b1b02,b1b03,b1b04,b1b05,b1b06,b2b02,b2b03
      real*8 xup2,xup3,xup4,xup5,xup6,xup7,xup8
      real*8 xlow2,xlow3,xlow4,xlow5,xlow6,xlow7,xlow8
      real*8 xuplog2,xuplog3,xuplog4,xuplog5,xuplog6
      real*8 xlowlog2,xlowlog3,xlowlog4,xlowlog5,xlowlog6


      G0 = 4d0*CF
      G1 = 4d0*CF*( (67d0/9d0 - pi*pi/3d0)*CA - 10d0/9d0*nf )
      G2 = 16d0/3d0*( -4d0/27d0*nf*nf + 3d0/2d0*nf*(-418d0/27d0
     >     + 40d0*pi*pi/27d0-56d0*zeta3/3d0) + 9d0*(245d0/6d0
     >     - 134d0*pi*pi/27d0 + 11d0*pi*pi*pi*pi/45d0
     >     + 22d0*zeta3/3d0) + 2d0/3d0*nf*(-55d0/3d0+16d0*zeta3) )
      gV0 = -6d0 * CF
      gV1 = 2d0/3d0*nf*(260d0/27d0+pi*pi/2d0)
     >     + 16d0/9d0*(-3d0+4*pi*pi-48d0*zeta3)
     >     + 4d0*(-961d0/27d0-11d0*pi*pi/3d0+52d0*zeta3)
      b0 = 11d0-2d0*nf/3d0
      b1 = 102d0-38d0*nf/3d0
      b2 = 1428.5d0-(5033d0*nf)/18d0+(325d0*nf**2d0)/54d0

      b1b0  = b1/(b0**2d0)
      b1b02 = b1b0*b1b0
      b1b03 = b1b02*b1b0
      b1b04 = b1b03*b1b0
      b1b05 = b1b04*b1b0
      b1b06 = b1b05*b1b0

      b2b0  = b2/(b0*b0*b0)
      b2b02 = b2b0*b2b0
      b2b03 = b2b02*b2b0

      xup2=xup*xup
      xup3=xup2*xup
      xup4=xup3*xup
      xup5=xup4*xup
      xup6=xup5*xup
      xup7=xup6*xup
      xup8=xup7*xup

      xuplog2=xuplog*xuplog
      xuplog3=xuplog2*xuplog
      xuplog4=xuplog3*xuplog
      xuplog5=xuplog4*xuplog
      xuplog6=xuplog5*xuplog

      xlow2=xlow*xlow
      xlow3=xlow2*xlow
      xlow4=xlow3*xlow
      xlow5=xlow4*xlow
      xlow6=xlow5*xlow
      xlow7=xlow6*xlow
      xlow8=xlow7*xlow

      xlowlog2=xlowlog*xlowlog
      xlowlog3=xlowlog2*xlowlog
      xlowlog4=xlowlog3*xlowlog
      xlowlog5=xlowlog4*xlowlog
      xlowlog6=xlowlog5*xlowlog

      CgV0 = gV0/(2d0*b0)*(xuplog-b1b0*((-1d0-xuplog)/xup)
     >     + b1b0*b1b0*((1d0-xuplog*xuplog)/(2d0*xup*xup))
     >     - b2b0/(2d0*xup*xup))
     >     - gV0/(2d0*b0)*(xlowlog-b1b0*((-1d0-xlowlog)/xlow)
     >     + b1b0*b1b0*((1d0-xlowlog*xlowlog)/(2d0*xlow*xlow))
     >     - b2b0/(2d0*xlow*xlow))

      CgV1 = gV1/(2d0*b0*b0)*(-1d0/xup+b1b02*(-2d0/27d0/xup3
     >     -xuplog2/3d0/xup3-2d0*xuplog/9d0/xup3)
     >     +b1b04*(-789d0/3125d0/xup5-xuplog4/5d0/xup5
     >     +6d0*xuplog3/25d0/xup5+43d0*xuplog2/125d0/xup5
     >     -164d0*xuplog/625d0/xup5)
     >     +b2b02*(-1d0/5d0/xup5) - 2d0*b1b0*(-1d0/4d0/xup2
     >     -xuplog/2d0/xup2)
     >     +2d0*b1b02*(10d0/27/xup3-xuplog2/3d0/xup3
     >     +xuplog/9d0/xup3) + 2d0*b2b0*(-1d0/xup3)
     >     -2d0*b1b03*(9d0/128d0/xup4-xuplog3/4d0/xup4
     >     +xuplog2/16d0/xup4+9d0*xuplog/32d0/xup4)
     >     -b1b0*b2b0*(-1d0/16d0/xup4-xuplog/4d0/xup4)
     >     +2d0*b1b02*b2b0*(28d0/125d0/xup5-xuplog2/5d0/xup5
     >     +3d0*xuplog/25d0/xup5))
     >     -gV1/(2d0*b0*b0)*(-1d0/xlow+b1b02*(-2d0/27d0/xlow3
     >     -xlowlog2/3d0/xlow3-2d0*xlowlog/9d0/xlow3)
     >     +b1b04*(-789d0/3125d0/xlow5-xlowlog4/5d0/xlow5
     >     +6d0*xlowlog3/25d0/xlow5+43d0*xlowlog2/125d0/xlow5
     >     -164d0*xlowlog/625d0/xlow5)
     >     +b2b02*(-1d0/5d0/xlow5) - 2d0*b1b0*(-1d0/4d0/xlow2
     >     -xlowlog/2d0/xlow2)
     >     +2d0*b1b02*(10d0/27/xlow3-xlowlog2/3d0/xlow3
     >     +xlowlog/9d0/xlow3) + 2d0*b2b0*(-1d0/xlow3)
     >     -2d0*b1b03*(9d0/128d0/xlow4-xlowlog3/4d0/xlow4
     >     +xlowlog2/16d0/xlow4+9d0*xlowlog/32d0/xlow4)
     >     -b1b0*b2b0*(-1d0/16d0/xlow4-xlowlog/4d0/xlow4)
     >     +2d0*b1b02*b2b0*(28d0/125d0/xlow5-xlowlog2/5d0/xlow5
     >     +3d0*xlowlog/25d0/xlow5))

      CG0 = G0/(2d0*b0)*(-xup+xq*xuplog-b1b0*(-xq/xup-xq*xuplog/xup
     >     -xuplog*xuplog/2d0)+b1b0*b1b0*(((1d0+xuplog)
     >     *(xq+(2d0*xup-xq)*xuplog))/(2d0*xup*xup))
     >     +b2b0*(1d0/xup-xq/(2d0*xup*xup)))
     >     -G0/(2d0*b0)*(-xlow+xq*xlowlog-b1b0*(-xq/xlow
     >     -xq*xlowlog/xlow-xlowlog*xlowlog/2d0)+b1b0*b1b0
     >     *(((1d0+xlowlog)*(xq+(2d0*xlow-xq)*xlowlog))
     >     /(2d0*xlow*xlow))+b2b0*(1d0/xlow-xq/(2d0*xlow*xlow)))

      CG1 = G1/(2d0*b0*b0)*(-xq/xup-xuplog
     >     +b1b02*(1d0/4d0/xup2-2d0*xq/27d0/xup3+xuplog/2d0/xup2
     >     -2d0*xq*xuplog/9d0/xup3+xuplog2/2d0/xup2
     >     -xq*xuplog2/3d0/xup3)
     >     +b1b04/(400000d0*xup5)*(20000d0*(5d0*xup-4d0*xq)*xuplog4
     >     -4000d0*(25d0*xup-24d0*xq)*xuplog3
     >     -200d0*(875d0*xup-688d0*xq)*xuplog2
     >     +20d0*(5625d0*xup-5248d0*xq)*xuplog+128125d0*xup
     >     -100992*xq)
     >     +b2b03*(1d0/4d0/xup4-xq/5d0/xup5)
     >     -2d0*b1b0*(1d0/xup-xq/4d0/xup2+xuplog/xup
     >     -xq*xuplog/2d0/xup2)
     >     +2d0*b1b02*(9d0*(3d0*xup-2d0*xq)*xuplog2+6d0*xq*xuplog
     >     -27d0*xup+20d0*xq)/(54d0*xup3)
     >     +2d0*b2b0*(1d0/2d0/xup2-xq/3d0/xup3)
     >     -2d0*b1b03*(96d0*(4d0*xup-3d0*xq)*xuplog3
     >     +72d0*xq*xuplog2+(324d0*xq-384d0*xup)*xuplog
     >     -128d0*xup+81d0*xq)/(1152d0*xup4)
     >     -2d0*b1b0*b2b0*(-xq/16d0/xup4-xq*xuplog/4d0/xup4
     >     +1d0/9d0/xup3+xuplog/3d0/xup3)
     >     +2d0*b1b02*b2b0*(200d0*(5d0*xup-4d0*xq)*xuplog2
     >     +(480d0*xq-500d0*xup)*xuplog-1125d0*xup+896d0*xq)
     >     /(4000d0*xup5))
     >     -G1/(2d0*b0*b0)*(-xq/xlow-xlowlog
     >     +b1b02*(1d0/4d0/xlow2-2d0*xq/27d0/xlow3+xlowlog/2d0/xlow2
     >     -2d0*xq*xlowlog/9d0/xlow3+xlowlog2/2d0/xlow2
     >     -xq*xlowlog2/3d0/xlow3)
     >     +b1b04/(400000d0*xlow5)*(20000d0*(5d0*xlow-4d0*xq)*xlowlog4
     >     -4000d0*(25d0*xlow-24d0*xq)*xlowlog3
     >     -200d0*(875d0*xlow-688d0*xq)*xlowlog2
     >     +20d0*(5625d0*xlow-5248d0*xq)*xlowlog+128125d0*xlow
     >     -100992*xq)
     >     +b2b03*(1d0/4d0/xlow4-xq/5d0/xlow5)
     >     -2d0*b1b0*(1d0/xlow-xq/4d0/xlow2+xlowlog/xlow
     >     -xq*xlowlog/2d0/xlow2)
     >     +2d0*b1b02*(9d0*(3d0*xlow-2d0*xq)*xlowlog2+6d0*xq*xlowlog
     >     -27d0*xlow+20d0*xq)/(54d0*xlow3)
     >     +2d0*b2b0*(1d0/2d0/xlow2-xq/3d0/xlow3)
     >     -2d0*b1b03*(96d0*(4d0*xlow-3d0*xq)*xlowlog3
     >     +72d0*xq*xlowlog2+(324d0*xq-384d0*xlow)*xlowlog
     >     -128d0*xlow+81d0*xq)/(1152d0*xlow4)
     >     -2d0*b1b0*b2b0*(-xq/16d0/xlow4-xq*xlowlog/4d0/xlow4
     >     +1d0/9d0/xlow3+xlowlog/3d0/xlow3)
     >     +2d0*b1b02*b2b0*(200d0*(5d0*xlow-4d0*xq)*xlowlog2
     >     +(480d0*xq-500d0*xlow)*xlowlog-1125d0*xlow+896d0*xq)
     >     /(4000d0*xlow5))

      CG2 = G2/(2d0*b0*b0*b0)*(
     >     -b1b03*(3d0/(128d0*xup4)-(6d0*xq)/(625d0*xup5)
     >     +(3d0*xuplog)/(32d0*xup4)-(6d0*xq*xuplog)/(125d0*xup5)
     >     +(3d0*xuplog2)/(16d0*xup4)-(3d0*xq*xuplog2)/(25d0*xup5)
     >     +xuplog3/(4d0*xup4)-(xq*xuplog3)/(5d0*xup5))
     >     +b1b06*(-159580d0/(823543d0*xup7)
     >     +(21703d0*xq)/(131072d0*xup8)
     >     -(41931d0*xuplog)/(117649d0*xup7)
     >     +(5319d0*xq*xuplog)/(16384d0*xup8)
     >     +(4245d0*xuplog2)/(16807d0*xup7)
     >     -(825d0*xq*xuplog2)/(4096d0*xup8)
     >     +(1415d0*xuplog3)/(2401d0*xup7)
     >     -(275d0*xq*xuplog3)/(512d0*xup8)
     >     -(75d0*xuplog4)/(343d0*xup7)
     >     +(45d0*xq*xuplog4)/(256d0*xup8)
     >     -(15d0*xuplog5)/(49d0*xup7)
     >     +(9d0*xq*xuplog5)/(32d0*xup8)+xuplog6/(7d0*xup7)
     >     -(xq*xuplog6)/(8d0*xup8))
     >     +b2b03*(1d0/(7d0*xup7)-xq/(8d0*xup8))
     >     +1d0/xup-xq/(2d0*xup2)
     >     -3d0*b1b0*(1d0/(4d0*xup2)-xq/(9d0*xup3)+xuplog/(2d0*xup2)
     >     -(xq*xuplog)/(3d0*xup3))
     >     +3d0*b1b02*(2d0/(27d0*xup3)-xq/(32d0*xup4)
     >     +(2d0*xuplog)/(9d0*xup3)-(xq*xuplog)/(8d0*xup4)
     >     +xuplog2/(3d0*xup3)-(xq*xuplog2)/(4d0*xup4))
     >     +3d0*b1b02*(-10d0/(27d0*xup3)+(9d0*xq)/(32d0*xup4)
     >     -xuplog/(9d0*xup3)+(xq*xuplog)/(8d0*xup4)
     >     +xuplog2/(3d0*xup3)-(xq*xuplog2)/(4d0*xup4))
     >     -6d0*b1b03*(-9d0/(128d0*xup4)+(29d0*xq)/(625d0*xup5)
     >     -(9d0*xuplog)/(32d0*xup4)+(29d0*xq*xuplog)/(125d0*xup5)
     >     -xuplog2/(16d0*xup4)+(2d0*xq*xuplog2)/(25d0*xup5)
     >     +xuplog3/(4d0*xup4)-(xq*xuplog3)/(5d0*xup5))
     >     +3d0*b1b04*(-56d0/(3125d0*xup5)+(7d0*xq)/(648d0*xup6)
     >     -(56d0*xuplog)/(625d0*xup5)+(7d0*xq*xuplog)/(108d0*xup6)
     >     -(28d0*xuplog2)/(125d0*xup5)
     >     +(7d0*xq*xuplog2)/(36d0*xup6)-xuplog3/(25d0*xup5)
     >     +(xq*xuplog3)/(18d0*xup6)+xuplog4/(5d0*xup5)
     >     -(xq*xuplog4)/(6d0*xup6))
     >     +3d0*b1b04*(789d0/(3125d0*xup5)-(67d0*xq)/(324d0*xup6)
     >     +(164d0*xuplog)/(625d0*xup5)-(13d0*xq*xuplog)/(54d0*xup6)
     >     -(43d0*xuplog2)/(125d0*xup5)+(5d0*xq*xuplog2)/(18d0*xup6)
     >     -(6d0*xuplog3)/(25d0*xup5)+(2d0*xq*xuplog3)/(9d0*xup6)
     >     +xuplog4/(5d0*xup5)-(xq*xuplog4)/(6d0*xup6))
     >     -3d0*b1b05*(37d0/(972d0*xup6)-(3263d0*xq)/(117649d0*xup7)
     >     +(37d0*xuplog)/(162d0*xup6)
     >     -(3263d0*xq*xuplog)/(16807d0*xup7)
     >     +(5d0*xuplog2)/(27d0*xup6)
     >     -(431d0*xq*xuplog2)/(2401d0*xup7)
     >     -(8d0*xuplog3)/(27d0*xup6)
     >     +(85d0*xq*xuplog3)/(343d0*xup7)
     >     -(7d0*xuplog4)/(36d0*xup6)+(9d0*xq*xuplog4)/(49d0*xup7)
     >     +xuplog5/(6d0*xup6)-(xq*xuplog5)/(7d0*xup7))
     >     +3d0*b2b0*(1d0/(3d0*xup3)-xq/(4d0*xup4))
     >     -6d0*b1b0*b2b0*(1d0/(16d0*xup4)-xq/(25d0*xup5)
     >     +xuplog/(4d0*xup4)-(xq*xuplog)/(5d0*xup5))
     >     +3d0*b1b02*b2b0*(2d0/(125d0*xup5)-xq/(108d0*xup6)
     >     +(2d0*xuplog)/(25d0*xup5)-(xq*xuplog)/(18d0*xup6)
     >     +xuplog2/(5d0*xup5)-(xq*xuplog2)/(6d0*xup6))
     >     +6d0*b1b02*b2b0*(-28d0/(125d0*xup5)+(5d0*xq)/(27d0*xup6)
     >     -(3d0*xuplog)/(25d0*xup5)+(xq*xuplog)/(9d0*xup6)
     >     +xuplog2/(5d0*xup5)-(xq*xuplog2)/(6d0*xup6))
     >     -6d0*b1b03*b2b0*(-7d0/(216d0*xup6)
     >     +(57d0*xq)/(2401d0*xup7)
     >     -(7d0*xuplog)/(36d0*xup6)+(57d0*xq*xuplog)/(343d0*xup7)
     >     -xuplog2/(12d0*xup6)+(4d0*xq*xuplog2)/(49d0*xup7)
     >     +xuplog3/(6d0*xup6)-(xq*xuplog3)/(7d0*xup7))
     >     +3d0*b1b04*b2b0*(2929d0/(16807d0*xup7)
     >     -(615d0*xq)/(4096d0*xup8)
     >     +(528d0*xuplog)/(2401d0*xup7)
     >     -(103d0*xq*xuplog)/(512d0*xup8)
     >     -(79d0*xuplog2)/(343d0*xup7)
     >     +(25d0*xq*xuplog2)/(128d0*xup8)
     >     -(10d0*xuplog3)/(49d0*xup7)+(3d0*xq*xuplog3)/(16d0*xup8)
     >     +xuplog4/(7d0*xup7)-(xq*xuplog4)/(8d0*xup8))
     >     +3d0*b2b02*(1d0/(5d0*xup5)-xq/(6d0*xup6))
     >     -3d0*b1b0*b2b02*(1d0/(36d0*xup6)-xq/(49d0*xup7)
     >     +xuplog/(6d0*xup6)-(xq*xuplog)/(7d0*xup7))
     >     +3d0*b1b02*b2b02*(-54d0/(343d0*xup7)
     >     +(35d0*xq)/(256d0*xup8)
     >     -(5d0*xuplog)/(49d0*xup7)+(3d0*xq*xuplog)/(32d0*xup8)
     >     +xuplog2/(7d0*xup7)-(xq*xuplog2)/(8d0*xup8)))
     >     -G2/(2d0*b0*b0*b0)*(
     >     -b1b03*(3d0/(128d0*xlow4)-(6d0*xq)/(625d0*xlow5)
     >     +(3d0*xlowlog)/(32d0*xlow4)
     >     -(6d0*xq*xlowlog)/(125d0*xlow5)
     >     +(3d0*xlowlog2)/(16d0*xlow4)
     >     -(3d0*xq*xlowlog2)/(25d0*xlow5)
     >     +xlowlog3/(4d0*xlow4)-(xq*xlowlog3)/(5d0*xlow5))
     >     +b1b06*(-159580d0/(823543d0*xlow7)
     >     +(21703d0*xq)/(131072d0*xlow8)
     >     -(41931d0*xlowlog)/(117649d0*xlow7)
     >     +(5319d0*xq*xlowlog)/(16384d0*xlow8)
     >     +(4245d0*xlowlog2)/(16807d0*xlow7)
     >     -(825d0*xq*xlowlog2)/(4096d0*xlow8)
     >     +(1415d0*xlowlog3)/(2401d0*xlow7)
     >     -(275d0*xq*xlowlog3)/(512d0*xlow8)
     >     -(75d0*xlowlog4)/(343d0*xlow7)
     >     +(45d0*xq*xlowlog4)/(256d0*xlow8)
     >     -(15d0*xlowlog5)/(49d0*xlow7)
     >     +(9d0*xq*xlowlog5)/(32d0*xlow8)+xlowlog6/(7d0*xlow7)
     >     -(xq*xlowlog6)/(8d0*xlow8))
     >     +b2b03*(1d0/(7d0*xlow7)-xq/(8d0*xlow8))
     >     +1d0/xlow-xq/(2d0*xlow2)
     >     -3d0*b1b0*(1d0/(4d0*xlow2)
     >     -xq/(9d0*xlow3)+xlowlog/(2d0*xlow2)
     >     -(xq*xlowlog)/(3d0*xlow3))
     >     +3d0*b1b02*(2d0/(27d0*xlow3)-xq/(32d0*xlow4)
     >     +(2d0*xlowlog)/(9d0*xlow3)-(xq*xlowlog)/(8d0*xlow4)
     >     +xlowlog2/(3d0*xlow3)-(xq*xlowlog2)/(4d0*xlow4))
     >     +3d0*b1b02*(-10d0/(27d0*xlow3)+(9d0*xq)/(32d0*xlow4)
     >     -xlowlog/(9d0*xlow3)+(xq*xlowlog)/(8d0*xlow4)
     >     +xlowlog2/(3d0*xlow3)-(xq*xlowlog2)/(4d0*xlow4))
     >     -6d0*b1b03*(-9d0/(128d0*xlow4)+(29d0*xq)/(625d0*xlow5)
     >     -(9d0*xlowlog)/(32d0*xlow4)
     >     +(29d0*xq*xlowlog)/(125d0*xlow5)
     >     -xlowlog2/(16d0*xlow4)+(2d0*xq*xlowlog2)/(25d0*xlow5)
     >     +xlowlog3/(4d0*xlow4)-(xq*xlowlog3)/(5d0*xlow5))
     >     +3d0*b1b04*(-56d0/(3125d0*xlow5)+(7d0*xq)/(648d0*xlow6)
     >     -(56d0*xlowlog)/(625d0*xlow5)
     >     +(7d0*xq*xlowlog)/(108d0*xlow6)
     >     -(28d0*xlowlog2)/(125d0*xlow5)
     >     +(7d0*xq*xlowlog2)/(36d0*xlow6)-xlowlog3/(25d0*xlow5)
     >     +(xq*xlowlog3)/(18d0*xlow6)+xlowlog4/(5d0*xlow5)
     >     -(xq*xlowlog4)/(6d0*xlow6))
     >     +3d0*b1b04*(789d0/(3125d0*xlow5)-(67d0*xq)/(324d0*xlow6)
     >     +(164d0*xlowlog)/(625d0*xlow5)
     >     -(13d0*xq*xlowlog)/(54d0*xlow6)
     >     -(43d0*xlowlog2)/(125d0*xlow5)
     >     +(5d0*xq*xlowlog2)/(18d0*xlow6)
     >     -(6d0*xlowlog3)/(25d0*xlow5)
     >     +(2d0*xq*xlowlog3)/(9d0*xlow6)
     >     +xlowlog4/(5d0*xlow5)-(xq*xlowlog4)/(6d0*xlow6))
     >     -3d0*b1b05*(37d0/(972d0*xlow6)
     >     -(3263d0*xq)/(117649d0*xlow7)
     >     +(37d0*xlowlog)/(162d0*xlow6)
     >     -(3263d0*xq*xlowlog)/(16807d0*xlow7)
     >     +(5d0*xlowlog2)/(27d0*xlow6)
     >     -(431d0*xq*xlowlog2)/(2401d0*xlow7)
     >     -(8d0*xlowlog3)/(27d0*xlow6)
     >     +(85d0*xq*xlowlog3)/(343d0*xlow7)
     >     -(7d0*xlowlog4)/(36d0*xlow6)
     >     +(9d0*xq*xlowlog4)/(49d0*xlow7)
     >     +xlowlog5/(6d0*xlow6)-(xq*xlowlog5)/(7d0*xlow7))
     >     +3d0*b2b0*(1d0/(3d0*xlow3)-xq/(4d0*xlow4))
     >     -6d0*b1b0*b2b0*(1d0/(16d0*xlow4)-xq/(25d0*xlow5)
     >     +xlowlog/(4d0*xlow4)-(xq*xlowlog)/(5d0*xlow5))
     >     +3d0*b1b02*b2b0*(2d0/(125d0*xlow5)-xq/(108d0*xlow6)
     >     +(2d0*xlowlog)/(25d0*xlow5)-(xq*xlowlog)/(18d0*xlow6)
     >     +xlowlog2/(5d0*xlow5)-(xq*xlowlog2)/(6d0*xlow6))
     >     +6d0*b1b02*b2b0*(-28d0/(125d0*xlow5)
     >     +(5d0*xq)/(27d0*xlow6)
     >     -(3d0*xlowlog)/(25d0*xlow5)+(xq*xlowlog)/(9d0*xlow6)
     >     +xlowlog2/(5d0*xlow5)-(xq*xlowlog2)/(6d0*xlow6))
     >     -6d0*b1b03*b2b0*(-7d0/(216d0*xlow6)
     >     +(57d0*xq)/(2401d0*xlow7)
     >     -(7d0*xlowlog)/(36d0*xlow6)
     >     +(57d0*xq*xlowlog)/(343d0*xlow7)
     >     -xlowlog2/(12d0*xlow6)+(4d0*xq*xlowlog2)/(49d0*xlow7)
     >     +xlowlog3/(6d0*xlow6)-(xq*xlowlog3)/(7d0*xlow7))
     >     +3d0*b1b04*b2b0*(2929d0/(16807d0*xlow7)
     >     -(615d0*xq)/(4096d0*xlow8)
     >     +(528d0*xlowlog)/(2401d0*xlow7)
     >     -(103d0*xq*xlowlog)/(512d0*xlow8)
     >     -(79d0*xlowlog2)/(343d0*xlow7)
     >     +(25d0*xq*xlowlog2)/(128d0*xlow8)
     >     -(10d0*xlowlog3)/(49d0*xlow7)
     >     +(3d0*xq*xlowlog3)/(16d0*xlow8)
     >     +xlowlog4/(7d0*xlow7)-(xq*xlowlog4)/(8d0*xlow8))
     >     +3d0*b2b02*(1d0/(5d0*xlow5)-xq/(6d0*xlow6))
     >     -3d0*b1b0*b2b02*(1d0/(36d0*xlow6)-xq/(49d0*xlow7)
     >     +xlowlog/(6d0*xlow6)-(xq*xlowlog)/(7d0*xlow7))
     >     +3d0*b1b02*b2b02*(-54d0/(343d0*xlow7)
     >     +(35d0*xq)/(256d0*xlow8)
     >     -(5d0*xlowlog)/(49d0*xlow7)
     >     +(3d0*xq*xlowlog)/(32d0*xlow8)
     >     +xlowlog2/(7d0*xlow7)-(xq*xlowlog2)/(8d0*xlow8)))

      funcspNNLL = CgV0 + CgV1 + CG0 + CG1 + CG2

      return
      end

c--------------------------------------------------------------
c     RG evolution via G_cusp for the D function
c     relies on the previous objects
c--------------------------------------------------------------
c     \int_{mub}^{Qi} [ A ]
c     Inputs: b,Qi
c     Order: 0,1,2 for LL,NLL,NNLL
c     Output: Revo
c--------------------------------------------------------------
      subroutine intcusp(b,Qi,res)
       use com,only: c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5,
     &               bmax,g2
      implicit none
      integer nf
      real*8 b,Qi,res
      real*8 funccusp,bstar,mub
      real*8 xup,xlow,xuplog,xlowlog,sp,sp1,sp2,sp3,lambda
      external funccusp

      bstar = b/dsqrt(1+(b*b/bmax/bmax))
      mub = c0/bstar
      sp=0d0

      if(mub.le.mc) then
         if(Qi.le.mc) then
            nf = 3              ! Integrate from mub to Qi
            lambda = lambda3
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp = funccusp(xup,xuplog,xlow,xlowlog,nf)
         elseif(Qi.gt.mc.and.Qi.le.mb) then
            nf = 3              ! Integrate from mub to mc
            lambda = lambda3
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mc to Qi
            lambda = lambda4
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         elseif(Qi.gt.mb) then
            nf = 3              ! Integrate from mub to mc
            lambda = lambda3
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mc to mb
            lambda = lambda4
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 5              ! Integrate from mb to Qi
            lambda = lambda5
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp3 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2 + sp3
         endif
      elseif(mub.gt.mc.and.mub.le.mb) then
         if(Qi.le.mc) then
            nf = 4              ! Integrate from mub to mc
            lambda = lambda4
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 3              ! Integrate from mc to Qi
            lambda = lambda3
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         elseif(Qi.gt.mc.and.Qi.le.mb) then
            nf = 4              ! Integrate from mub to Qi
            lambda = lambda4
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp = funccusp(xup,xuplog,xlow,xlowlog,nf)
         elseif(Qi.gt.mb) then
            nf = 4              ! Integrate from mub to mb
            lambda = lambda4
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 5              ! Integrate from mb to Qi
            lambda = lambda5
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         endif
      elseif(mub.gt.mb) then
         if(Qi.le.mc) then
            nf = 5              ! Integrate from mub to mb
            lambda = lambda5
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mb to mc
            lambda = lambda4
            xup = 2d0*dlog(mc/lambda)
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 3              ! Integrate from mc to Qi
            lambda = lambda3
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mc/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp3 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2 + sp3
         elseif(Qi.gt.mc.and.Qi.le.mb) then
            nf = 5              ! Integrate from mub to mb
            lambda = lambda5
            xup = 2d0*dlog(mb/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp1 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            nf = 4              ! Integrate from mb to Qi
            lambda = lambda4
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mb/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp2 = funccusp(xup,xuplog,xlow,xlowlog,nf)
            sp = sp1 + sp2
         elseif(Qi.gt.mb) then
            nf = 5              ! Integrate from mub to Qi
            lambda = lambda5
            xup = 2d0*dlog(Qi/lambda)
            xlow = 2d0*dlog(mub/lambda)
            xuplog = dlog(xup)
            xlowlog = dlog(xlow)
            sp = funccusp(xup,xuplog,xlow,xlowlog,nf)
         endif
      endif

      res = sp

      return
      end

c--------------------------------------------------------------
c     accuracy&summary
c--------------------------------------------------------------
c     Integrand to solve analytically:
c     \int_{mub}^{Qi} [ A ]
c     ord=0,1,2 for LL,NLL,NNLL
c--------------------------------------------------------------
      function funccusp(xup,xuplog,xlow,xlowlog,nf)
       use com,only: ord
      implicit none
      integer nf
      real*8 funccusp,xup,xuplog,xlow,xlowlog
      real*8 funccuspLL,funccuspNLL,funccuspNNLL
      external funccuspLL,funccuspNLL,funccuspNNLL

      funccusp=0d0
      if(ord.eq.0) then
         funccusp=funccuspLL(xuplog,xlowlog,nf)
      elseif(ord.eq.1) then
         funccusp=funccuspNLL(xup,xuplog,xlow,xlowlog,nf)
      elseif(ord.eq.2) then
         funccusp=funccuspNNLL(xup,xuplog,xlow,xlowlog,nf)
      endif

      return
      end

c--------------------------------------------------------------
c     Integrand of \int Gamma_cusp to evolve D
c     in this case {\mu_i=mub,\mu_f=Qi}
c--------------------------------------------------------------

c--------------------------------------------------------------
c     Integrand to solve analytically at LL:
c     \int_{mub}^{Qi} [ A ]
c     A = cusp. We take A0.
c--------------------------------------------------------------
      function funccuspLL(xuplog,xlowlog,nf)
       use com,only: c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5
      implicit none
      integer nf
      real*8 funccuspLL,xuplog,xlowlog
      real*8 b0,G0
      real*8 CG0

      G0 = 4d0*CF
      b0 = 11d0-2d0*nf/3d0

      CG0 = G0/(2d0*b0)*(xuplog)
     >     - G0/(2d0*b0)*(xlowlog)

      funccuspLL = CG0

      return
      end

c--------------------------------------------------------------
c     Integrand to solve analytically at NLL:
c     \int_{mub}^{Qi} [ A ]
c     A = cusp. We take A0 and A1.
c--------------------------------------------------------------
      function funccuspNLL(xup,xuplog,xlow,xlowlog,nf)
       use com,only: zeta3,c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5
      implicit none
      integer nf
      real*8 funccuspNLL,xup,xuplog,xlow,xlowlog
      real*8 b0,b1,b1b0,G0,G1
      real*8 CG0,CG1
      real*8 b1b02
      real*8 xup2,xup3
      real*8 xlow2,xlow3
      real*8 xuplog2
      real*8 xlowlog2


      G0 = 4d0*CF
      G1 = 4d0*CF*( (67d0/9d0 - pi*pi/3d0)*CA - 10d0/9d0*nf )

      b0 = 11d0-2d0*nf/3d0
      b1 = 102d0-38d0*nf/3d0

      b1b0  = b1/(b0**2d0)
      b1b02 = b1b0*b1b0

      xup2=xup*xup
      xup3=xup2*xup

      xuplog2=xuplog*xuplog

      xlow2=xlow*xlow
      xlow3=xlow2*xlow

      xlowlog2=xlowlog*xlowlog

      CG0 = G0/(2d0*b0)*(xuplog-b1b0*((-1d0-xuplog)/xup))
     >     - G0/(2d0*b0)*(xlowlog-b1b0*((-1d0-xlowlog)/xlow))

      CG1 = G1/(2d0*b0*b0)*(-1d0/xup+b1b02*(-2d0/27d0/xup3
     >     -xuplog2/3d0/xup3-2d0*xuplog/9d0/xup3)
     >     -2d0*b1b0*(-1d0/4d0/xup2
     >     -xuplog/2d0/xup2))
     >     -G1/(2d0*b0*b0)*(-1d0/xlow+b1b02*(-2d0/27d0/xlow3
     >     -xlowlog2/3d0/xlow3-2d0*xlowlog/9d0/xlow3)
     >     -2d0*b1b0*(-1d0/4d0/xlow2
     >     -xlowlog/2d0/xlow2))

      funccuspNLL = CG0 + CG1

      return
      end

c--------------------------------------------------------------
c     Integrand to solve analytically at NNLL:
c     \int_{mub}^{Qi} [ A ]
c     A = cusp. We take A0, A1 and A2.
c--------------------------------------------------------------
      function funccuspNNLL(xup,xuplog,xlow,xlowlog,nf)
       use com,only: zeta3,c0,c02,pi,CF,CA,mc,mb,lambda3,lambda4,lambda5
      implicit none
      integer nf
      real*8 funccuspNNLL,xup,xuplog,xlow,xlowlog
      real*8 b0,b1,b2,b1b0,b2b0,G0,G1,G2
      real*8 CG0,CG1,CG2
      real*8 b1b02,b1b03,b1b04,b1b05,b1b06,b2b02,b2b03
      real*8 xup2,xup3,xup4,xup5,xup6,xup7,xup8
      real*8 xlow2,xlow3,xlow4,xlow5,xlow6,xlow7,xlow8
      real*8 xuplog2,xuplog3,xuplog4,xuplog5,xuplog6
      real*8 xlowlog2,xlowlog3,xlowlog4,xlowlog5,xlowlog6


      G0 = 4d0*CF
      G1 = 4d0*CF*( (67d0/9d0 - pi*pi/3d0)*CA - 10d0/9d0*nf )
      G2 = 16d0/3d0*( -4d0/27d0*nf*nf + 3d0/2d0*nf*(-418d0/27d0
     >     + 40d0*pi*pi/27d0-56d0*zeta3/3d0) + 9d0*(245d0/6d0
     >     - 134d0*pi*pi/27d0 + 11d0*pi*pi*pi*pi/45d0
     >     + 22d0*zeta3/3d0) + 2d0/3d0*nf*(-55d0/3d0+16d0*zeta3) )

      b0 = 11d0-2d0*nf/3d0
      b1 = 102d0-38d0*nf/3d0
      b2 = 1428.5d0-(5033d0*nf)/18d0+(325d0*nf**2d0)/54d0

      b1b0  = b1/(b0**2d0)
      b1b02 = b1b0*b1b0
      b1b03 = b1b02*b1b0
      b1b04 = b1b03*b1b0
      b1b05 = b1b04*b1b0
      b1b06 = b1b05*b1b0

      b2b0  = b2/(b0*b0*b0)
      b2b02 = b2b0*b2b0
      b2b03 = b2b02*b2b0

      xup2=xup*xup
      xup3=xup2*xup
      xup4=xup3*xup
      xup5=xup4*xup
      xup6=xup5*xup
      xup7=xup6*xup
      xup8=xup7*xup

      xuplog2=xuplog*xuplog
      xuplog3=xuplog2*xuplog
      xuplog4=xuplog3*xuplog
      xuplog5=xuplog4*xuplog
      xuplog6=xuplog5*xuplog

      xlow2=xlow*xlow
      xlow3=xlow2*xlow
      xlow4=xlow3*xlow
      xlow5=xlow4*xlow
      xlow6=xlow5*xlow
      xlow7=xlow6*xlow
      xlow8=xlow7*xlow

      xlowlog2=xlowlog*xlowlog
      xlowlog3=xlowlog2*xlowlog
      xlowlog4=xlowlog3*xlowlog
      xlowlog5=xlowlog4*xlowlog
      xlowlog6=xlowlog5*xlowlog

      CG0 = G0/(2d0*b0)*(xuplog-b1b0*((-1d0-xuplog)/xup)
     >     +b1b0*b1b0*((1d0-xuplog*xuplog)/(2d0*xup*xup))
     >     -b2b0/(2d0*xup*xup))
     >     -G0/(2d0*b0)*(xlowlog-b1b0*((-1d0-xlowlog)/xlow)
     >     +b1b0*b1b0*((1d0-xlowlog*xlowlog)/(2d0*xlow*xlow))
     >     -b2b0/(2d0*xlow*xlow))

      CG1 = G1/(2d0*b0*b0)*(-1d0/xup+b1b02*(-2d0/27d0/xup3
     >     -xuplog2/3d0/xup3-2d0*xuplog/9d0/xup3)
     >     +b1b04*(-789d0/3125d0/xup5-xuplog4/5d0/xup5
     >     +6d0*xuplog3/25d0/xup5+43d0*xuplog2/125d0/xup5
     >     -164d0*xuplog/625d0/xup5)
     >     +b2b02*(-1d0/5d0/xup5) - 2d0*b1b0*(-1d0/4d0/xup2
     >     -xuplog/2d0/xup2)
     >     +2d0*b1b02*(10d0/27/xup3-xuplog2/3d0/xup3
     >     +xuplog/9d0/xup3) + 2d0*b2b0*(-1d0/xup3)
     >     -2d0*b1b03*(9d0/128d0/xup4-xuplog3/4d0/xup4
     >     +xuplog2/16d0/xup4+9d0*xuplog/32d0/xup4)
     >     -b1b0*b2b0*(-1d0/16d0/xup4-xuplog/4d0/xup4)
     >     +2d0*b1b02*b2b0*(28d0/125d0/xup5-xuplog2/5d0/xup5
     >     +3d0*xuplog/25d0/xup5))
     >     -G1/(2d0*b0*b0)*(-1d0/xlow+b1b02*(-2d0/27d0/xlow3
     >     -xlowlog2/3d0/xlow3-2d0*xlowlog/9d0/xlow3)
     >     +b1b04*(-789d0/3125d0/xlow5-xlowlog4/5d0/xlow5
     >     +6d0*xlowlog3/25d0/xlow5+43d0*xlowlog2/125d0/xlow5
     >     -164d0*xlowlog/625d0/xlow5)
     >     +b2b02*(-1d0/5d0/xlow5) - 2d0*b1b0*(-1d0/4d0/xlow2
     >     -xlowlog/2d0/xlow2)
     >     +2d0*b1b02*(10d0/27/xlow3-xlowlog2/3d0/xlow3
     >     +xlowlog/9d0/xlow3) + 2d0*b2b0*(-1d0/xlow3)
     >     -2d0*b1b03*(9d0/128d0/xlow4-xlowlog3/4d0/xlow4
     >     +xlowlog2/16d0/xlow4+9d0*xlowlog/32d0/xlow4)
     >     -b1b0*b2b0*(-1d0/16d0/xlow4-xlowlog/4d0/xlow4)
     >     +2d0*b1b02*b2b0*(28d0/125d0/xlow5-xlowlog2/5d0/xlow5
     >     +3d0*xlowlog/25d0/xlow5))

      CG2 = G2/(2d0*b0*b0*b0)*(
     >     -b1b03*(3d0/(128d0*xup4)
     >     -(6d0*xuplog)/(125d0*xup5)
     >     -(3d0*xuplog2)/(25d0*xup5)
     >     -(xuplog3)/(5d0*xup5))
     >     +b1b06*(
     >     +(21703d0)/(131072d0*xup8)
     >     +(5319d0*xuplog)/(16384d0*xup8)
     >     -(825d0*xuplog2)/(4096d0*xup8)
     >     -(275d0*xuplog3)/(512d0*xup8)
     >     +(45d0*xuplog4)/(256d0*xup8)
     >     +(9d0*xuplog5)/(32d0*xup8)
     >     -(xuplog6)/(8d0*xup8))
     >     +b2b03*(-1d0/(8d0*xup8))
     >     -1d0/(2d0*xup2)
     >     -3d0*b1b0*(-1d0/(9d0*xup3)
     >     -(xuplog)/(3d0*xup3))
     >     +3d0*b1b02*(-1d0/(32d0*xup4)
     >     -(xuplog)/(8d0*xup4)
     >     -(xuplog2)/(4d0*xup4))
     >     +3d0*b1b02*(+(9d0)/(32d0*xup4)
     >     +(xuplog)/(8d0*xup4)
     >     -(xuplog2)/(4d0*xup4))
     >     -6d0*b1b03*(+(29d0)/(625d0*xup5)
     >     +(29d0*xuplog)/(125d0*xup5)
     >     +(2d0*xuplog2)/(25d0*xup5)
     >     -(xuplog3)/(5d0*xup5))
     >     +3d0*b1b04*(+(7d0)/(648d0*xup6)
     >     +(7d0*xuplog)/(108d0*xup6)
     >     +(7d0*xuplog2)/(36d0*xup6)
     >     +(xuplog3)/(18d0*xup6)
     >     -(xuplog4)/(6d0*xup6))
     >     +3d0*b1b04*(-(67d0)/(324d0*xup6)
     >     -(13d0*xuplog)/(54d0*xup6)
     >     +(5d0*xuplog2)/(18d0*xup6)
     >     +(2d0*xuplog3)/(9d0*xup6)
     >     -(xuplog4)/(6d0*xup6))
     >     -3d0*b1b05*(-(3263d0)/(117649d0*xup7)
     >     -(3263d0*xuplog)/(16807d0*xup7)
     >     -(431d0*xuplog2)/(2401d0*xup7)
     >     +(85d0*xuplog3)/(343d0*xup7)
     >     +(9d0*xuplog4)/(49d0*xup7)
     >     -(xuplog5)/(7d0*xup7))
     >     +3d0*b2b0*(-1d0/(4d0*xup4))
     >     -6d0*b1b0*b2b0*(-1d0/(25d0*xup5)
     >     -(xuplog)/(5d0*xup5))
     >     +3d0*b1b02*b2b0*(-1d0/(108d0*xup6)
     >     -(xuplog)/(18d0*xup6)
     >     -(xuplog2)/(6d0*xup6))
     >     +6d0*b1b02*b2b0*(+(5d0)/(27d0*xup6)
     >     +(xuplog)/(9d0*xup6)
     >     -(xuplog2)/(6d0*xup6))
     >     -6d0*b1b03*b2b0*(
     >     +(57d0)/(2401d0*xup7)
     >     +(57d0*xuplog)/(343d0*xup7)
     >     +(4d0*xuplog2)/(49d0*xup7)
     >     -(xuplog3)/(7d0*xup7))
     >     +3d0*b1b04*b2b0*(
     >     -(615d0)/(4096d0*xup8)
     >     -(103d0*xuplog)/(512d0*xup8)
     >     +(25d0*xuplog2)/(128d0*xup8)
     >     +(3d0*xuplog3)/(16d0*xup8)
     >     -(xuplog4)/(8d0*xup8))
     >     +3d0*b2b02*(-1d0/(6d0*xup6))
     >     -3d0*b1b0*b2b02*(-1d0/(49d0*xup7)
     >     -(xuplog)/(7d0*xup7))
     >     +3d0*b1b02*b2b02*(
     >     +(35d0)/(256d0*xup8)
     >     +(3d0*xuplog)/(32d0*xup8)
     >     -(xuplog2)/(8d0*xup8)))
     >     -G2/(2d0*b0*b0*b0)*(
     >     -b1b03*(-(6d0)/(625d0*xlow5)
     >     -(6d0*xlowlog)/(125d0*xlow5)
     >     -(3d0*xlowlog2)/(25d0*xlow5)
     >     -(xlowlog3)/(5d0*xlow5))
     >     +b1b06*(
     >     +(21703d0)/(131072d0*xlow8)
     >     +(5319d0*xlowlog)/(16384d0*xlow8)
     >     -(825d0*xlowlog2)/(4096d0*xlow8)
     >     -(275d0*xlowlog3)/(512d0*xlow8)
     >     +(45d0*xlowlog4)/(256d0*xlow8)
     >     +(9d0*xlowlog5)/(32d0*xlow8)
     >     -(xlowlog6)/(8d0*xlow8))
     >     +b2b03*(-1d0/(8d0*xlow8))
     >     -1d0/(2d0*xlow2)
     >     -3d0*b1b0*(
     >     -1d0/(9d0*xlow3)
     >     -(xlowlog)/(3d0*xlow3))
     >     +3d0*b1b02*(-1d0/(32d0*xlow4)
     >     -(xlowlog)/(8d0*xlow4)
     >     -(xlowlog2)/(4d0*xlow4))
     >     +3d0*b1b02*(+(9d0)/(32d0*xlow4)
     >     +(xlowlog)/(8d0*xlow4)
     >     -(xlowlog2)/(4d0*xlow4))
     >     -6d0*b1b03*(+(29d0)/(625d0*xlow5)
     >     +(29d0*xlowlog)/(125d0*xlow5)
     >     +(2d0*xlowlog2)/(25d0*xlow5)
     >     -(xlowlog3)/(5d0*xlow5))
     >     +3d0*b1b04*(+(7d0)/(648d0*xlow6)
     >     +(7d0*xlowlog)/(108d0*xlow6)
     >     +(7d0*xlowlog2)/(36d0*xlow6)
     >     +(xlowlog3)/(18d0*xlow6)
     >     -(xlowlog4)/(6d0*xlow6))
     >     +3d0*b1b04*(-(67d0)/(324d0*xlow6)
     >     -(13d0*xlowlog)/(54d0*xlow6)
     >     +(5d0*xlowlog2)/(18d0*xlow6)
     >     +(2d0*xlowlog3)/(9d0*xlow6)
     >     -(xlowlog4)/(6d0*xlow6))
     >     -3d0*b1b05*(
     >     -(3263d0)/(117649d0*xlow7)
     >     -(3263d0*xlowlog)/(16807d0*xlow7)
     >     -(431d0*xlowlog2)/(2401d0*xlow7)
     >     +(85d0*xlowlog3)/(343d0*xlow7)
     >     +(9d0*xlowlog4)/(49d0*xlow7)
     >     -(xlowlog5)/(7d0*xlow7))
     >     +3d0*b2b0*(-1d0/(4d0*xlow4))
     >     -6d0*b1b0*b2b0*(-1d0/(25d0*xlow5)
     >     -(xlowlog)/(5d0*xlow5))
     >     +3d0*b1b02*b2b0*(-1d0/(108d0*xlow6)
     >     -(xlowlog)/(18d0*xlow6)
     >     -(xlowlog2)/(6d0*xlow6))
     >     +6d0*b1b02*b2b0*(
     >     +(5d0)/(27d0*xlow6)
     >     +(xlowlog)/(9d0*xlow6)
     >     -(xlowlog2)/(6d0*xlow6))
     >     -6d0*b1b03*b2b0*(
     >     +(57d0)/(2401d0*xlow7)
     >     +(57d0*xlowlog)/(343d0*xlow7)
     >     +(4d0*xlowlog2)/(49d0*xlow7)
     >     -(xlowlog3)/(7d0*xlow7))
     >     +3d0*b1b04*b2b0*(
     >     -(615d0)/(4096d0*xlow8)
     >     -(103d0*xlowlog)/(512d0*xlow8)
     >     +(25d0*xlowlog2)/(128d0*xlow8)
     >     +(3d0*xlowlog3)/(16d0*xlow8)
     >     -(xlowlog4)/(8d0*xlow8))
     >     +3d0*b2b02*(-1d0/(6d0*xlow6))
     >     -3d0*b1b0*b2b02*(-1d0/(49d0*xlow7)
     >     -(xlowlog)/(7d0*xlow7))
     >     +3d0*b1b02*b2b02*(
     >     +(35d0)/(256d0*xlow8)
     >     +(3d0*xlowlog)/(32d0*xlow8)
     >     -(xlowlog2)/(8d0*xlow8)))

      funccuspNNLL = CG0 + CG1 + CG2

      return
      end

c------------------------------------------------------------

      subroutine NumSudakov(mu,Qf,Revo)
      
      implicit none

      double precision  qgauss,integS,Sudakov
      double precision mu,Qf,Revo,Q,massc,massb
      integer ngauss
      external Sudakov
      common/masses/massc,massb
      common /qu/ Q
      Q=Qf
      call GetQmass(4,massc)
      call GetQmass(5,massb)
       ngauss=6
       integS=qgauss(Sudakov,mu,Qf,ngauss)

       Revo= dexp(integS)

      return
      end

c---------------------------------------------------------------

      double precision function Sudakov(mu)

      implicit none

      double precision alphasPDF,aspi
      double precision A_1,A_2,B_1,Cf,Ca,nfQ,Q,mu,massc,massb
      double precision, parameter :: pi=dacos(-1.d0)

      external aspi
      common/masses/massc,massb
      common /qu/ Q



      Cf=4d0/3d0
      Ca=3d0


      if(mu.le.massc)then
         nfQ=3d0
      elseif(mu.gt.massc.and.mu.le.massb)then
         nfQ=4d0
      elseif(mu.gt.massb)then
         nfQ=5d0
      end if

      A_1=Cf
      B_1=-3d0/2d0*Cf
      A_2=1d0/2d0*Cf*(Ca*(67d0/18d0-(pi**2d0)/6d0)-5d0/9d0*nfQ)

        Sudakov=
     1      -(1/(mu))*(
     2         dlog(Q**2d0/mu**2d0)*(
     3           A_1*(1d0/pi*alphasPDF(mu))+
     4           A_2*(1d0/pi*alphasPDF(mu))**2d0)+
     5     B_1*(1d0/pi*alphasPDF(mu)))

c  ---------- This is the formula of the numerical Sudakov woth the analytical alpha

c$$$                Sudak=
c$$$     1      -(1/(mu))*(
c$$$     2         dlog(Q**2d0/mu**2d0)*(
c$$$     3           A_1*(4d0*aspi(mu))+
c$$$     4           A_2*(4d0*aspi(mu))**2d0)+
c$$$  5     B_1*(4d0*aspi(mu)))

        return
        end
