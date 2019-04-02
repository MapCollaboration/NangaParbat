      module integrand_sidis
      use com
      implicit none
      double precision :: Revo,aspi
      double precision :: D1NP_FT,f1_sea,f1_val
      double precision :: u,ub,d,db,s,sb,c,b,gl
      double precision :: bTstar,mu_b2
      double precision :: bmin
      double precision, dimension(-6:6) :: zd1,xf1
      external aspi,f1_sea,f1_val,D1NP_FT
      save
      contains
c-------------------------------------------------------------------------
c     integrand for SIDIS
c-------------------------------------------------------------------------

      subroutine init_integrand_sidis(bT)
      implicit none
      double precision,intent(in) :: bT
      double precision cpdf(-6:6),cff(-6:6)

      bTstar=0d0
c     choose bstar prescription
      if (bpresc.eq.1) then
         bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
      elseif (bpresc.eq.2) then
         bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
      elseif (bpresc.eq.3) then
         bmin = bmax * 1d0/Qf
         bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &        (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
      endif

      mu_b = 2d0*dexp(-gE)/bTstar
      mu_b2 = mu_b*mu_b

c     identify number of flavours
      if(mu_b.le.mc) then
         nf=3
      elseif(mu_b.gt.mc.and.mu_b.le.mb) then
         nf=4
      elseif(mu_b.gt.mb) then
         nf=5
      endif

      alf2 = aspi(mu_b)*aspi(mu_b)

c     choose NP parametrization
      if (npchoose.eq.1) then
         npvar = 1d0/4d0*g2*bT*bT
      elseif (npchoose.eq.2) then
         npvar = (1d0/4d0)*g2*4d0*dlog(1d0+bT*bT/4d0)
      endif
      call PreCalc_SD(x,mu_b,Qf,cpdf,xf1,revo)
      xf1=xf1+ascorr*x*cpdf
      call PreCalc_FF(ihad,z,mu_b,cff,zd1)
      zd1=zd1+ascorr*cff*(z**3)
c$$$c     choose evolution kernel
c$$$      if (evchoose.eq.1) then
c$$$         call kernel_hyb(bT,Qi,Qf,Revo)
c$$$      elseif (evchoose.eq.2) then
c$$$         call kernel_css(Qf,Revo)
c$$$      elseif (evchoose.eq.3) then
c$$$         call kernel_eis(bT,Qi,Qf,Revo,1)
c$$$      elseif (evchoose.eq.4) then
c$$$         call kernel_eis(bT,Qi,Qf,Revo,2)
c$$$      elseif (evchoose.eq.5) then
c$$$         call kernel_eis(bT,Qi,Qf,Revo,3)
c$$$      endif
c$$$
c$$$c     choose final state
c$$$      select case(ihad)
c$$$
c$$$      case (-1,0,1) !PIONS
c$$$         if (ifinihad.ne.ihad) fini=0
c$$$c         call fDSS(1,1,1,z,mu_b2,u,ub,d,db,s,sb,c,b,gl)
c$$$         call fDSSH(0,1,ihad,1,z,mu_b2,u,ub,d,db,s,sb,c,b,gl)
c$$$
c$$$      case (-2,2)   !KAONS
c$$$         if (ifinihad.ne.ihad) fini=0
c$$$         call fDSSH17(0,1,sign(1,ihad),1,z,mu_b2,u,ub,d,db,s,sb,c,b,gl)
c$$$      case default
c$$$         write(*,*) 'Hadron type undefined! Stop!'
c$$$         stop
c$$$      end select
c$$$
c$$$      zd1=(/ 0.d0,b,c,sb,ub,db,gl,d,u,s,c,b,0.d0 /)
c$$$
c$$$      ifinihad=ihad
c$$$
c$$$      call evolvePDF(x, mu_b, xf1)

      return
      end

      double precision function sidis_fuu(bT)
      implicit none
      double precision,intent(in) :: bT
      integer is,ifinis
      common/FFset/is,ifinis

      if ((j.eq.1).or.(j.eq.2)) then
c     ... input:  gaussian + par * pt2* gaussian' both in the TMDs
         sidis_fuu=bT*dbesj0(bT*Php/z)
     &        *Revo*Revo
     &        *(1/(2d0*pi))
     &        *(1/(z**2))
     &        *(zd1(j)/z)*D1NP_FT(bT)   !FF
     &        *f1_val(x,xf1,k,bT,pt2av) !valence tPDF
     &        *(Qf/Q0)**(-4d0*npvar)
      else
         sidis_fuu=bT*dbesj0(bT*Php/z)
     &        *Revo*Revo
     &        *(1/(2d0*pi))
     &        *(1/(z**2))
     &        *(zd1(j)/z)*D1NP_FT(bT)   !FF
     &        *f1_sea(x,xf1,k,bT,pt2av) !sea tPDF
     &        *(Qf/Q0)**(-4d0*npvar)
      end if

      return
      end

      double precision function sidis_fuu_cosphi(bT)
      implicit none
      double precision,intent(in) :: bT
      if ((j.eq.1).or.(j.eq.2)) then
c     ... input:  gaussian + par * pt2* gaussian' both in the TMDs
         sidis_fuu_cosphi=2d0/Qf*bT**2*dbesj1(bT*Php/z)
     &        *Revo*Revo
     &        *(1/(2d0*pi))
     &        *(1/(z**2))
     &        *(zd1(j)/z)*D1NP_FT(bT)   !FF
     &        *f1_val(x,xf1,k,bT,pt2av) !valence tPDF
     &        *(Qf/Q0)**(-4d0*npvar)*
     &        (-2d0*aspi(Qf)*
     &        (2d0*CF*dlog(bT**2*Qf**2/(4d0*dexp(-2d0*gE)))
     &        -3d0*CF)/bT**2)
      else
         sidis_fuu_cosphi=2d0/Qf*bT**2*dbesj1(bT*Php/z)
     &        *Revo*Revo
     &        *(1/(2d0*pi))
     &        *(1/(z**2))
     &        *(zd1(j)/z)*D1NP_FT(bT)   !FF
     &        *f1_sea(x,xf1,k,bT,pt2av) !sea tPDF
     &        *(Qf/Q0)**(-4d0*npvar)*
     &        (-2d0*aspi(Qf)*
     &        (2d0*CF*dlog(bT**2*Qf**2/(4d0*dexp(-2d0*gE)))
     &        -3d0*CF)/bT**2)
      end if

      return
      end

      double precision function sidis_fuu_cos2phi(bT)
      implicit none
      double precision,intent(in) :: bT
      if ((j.eq.1).or.(j.eq.2)) then
c     ... input:  gaussian + par * pt2* gaussian' both in the TMDs
         sidis_fuu_cos2phi=1d0/Qf**2*bT**3*dbesjN(2,bT*Php/z)
     &        *Revo*Revo
     &        *(1/(2d0*pi))
     &        *(1/(z**2))
     &        *(zd1(j)/z)*D1NP_FT(bT)   !FF
     &        *f1_val(x,xf1,k,bT,pt2av) !valence tPDF
     &        *(Qf/Q0)**(-4d0*npvar)*
     &        (2d0*aspi(Qf)*
     &        (4d0*CF*dlog(bT**2*Qf**2/(4d0*dexp(-2d0*gE)))
     &        -10d0*CF)/bT**4)
      else
         sidis_fuu_cos2phi=1d0/Qf**2*bT**3*dbesjN(2,bT*Php/z)
     &        *Revo*Revo
     &        *(1/(2d0*pi))
     &        *(1/(z**2))
     &        *(zd1(j)/z)*D1NP_FT(bT)   !FF
     &        *f1_sea(x,xf1,k,bT,pt2av) !sea tPDF
     &        *(Qf/Q0)**(-4d0*npvar)*
     &        (2d0*aspi(Qf)*
     &        (4d0*CF*dlog(bT**2*Qf**2/(4d0*dexp(-2d0*gE)))
     &        -10d0*CF)/bT**4)
      end if

      return
      end

      end module integrand_sidis

      double precision function integrand_sidis_fuu(bT)
      use integrand_sidis
      implicit none
      double precision,intent(in) :: bT

      integer is,ifinis
      common/FFset/is,ifinis

      call init_integrand_sidis(bT)
      integrand_sidis_fuu=sidis_fuu(bT)

      return
      end

      double precision function integrand_sidis_fuu_cosphi(bT)
      use integrand_sidis
      implicit none
      double precision,intent(in) :: bT

      call init_integrand_sidis(bT)
      integrand_sidis_fuu_cosphi=sidis_fuu_cosphi(bT)

      return
      end

      double precision function integrand_sidis_fuu_cos2phi(bT)
      use integrand_sidis
      implicit none
      double precision,intent(in) :: bT

      call init_integrand_sidis(bT)
      integrand_sidis_fuu_cos2phi=sidis_fuu_cos2phi(bT)

      return
      end

c-------------------------------------------------------------------------
c     integrand for DY
c-------------------------------------------------------------------------

      double precision function integrand_DY_sum(bT)
      use com
      implicit none
      double precision ::  Revo,aspi !using the function besj0 from cernlib
      double precision :: bmin,Ninteg_DY,Pinteg_DY,integrand_DY
      double precision :: bT,bTstar,mu_b2
      double precision, dimension(-6:6) :: xfaa, xfbb,cpdfa,cpdfb
      double precision alphasPDF
      external alphasPDF
      common /evo/ Revo,xfaa,xfbb
      external aspi,f1_sea,f1_val

      bTstar=0d0
c     choose bstar prescription
      if (bpresc.eq.1) then
         bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
      elseif (bpresc.eq.2) then
         bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
      elseif (bpresc.eq.3) then
         bmin = bmax * 1d0/m
         bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &        (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
      endif


      mu_b = 2d0*dexp(-gE)/bTstar
      mu_b2 = mu_b*mu_b

c     identify number of flavours
      if(mu_b.le.mc) then
         nf=3
      elseif(mu_b.gt.mc.and.mu_b.le.mb) then
         nf=4
      elseif(mu_b.gt.mb) then
         nf=5
      endif

      alf2 = aspi(mu_b)*aspi(mu_b)

c     choose NP parametrization
      if (npchoose.eq.1) then
         npvar = 1d0/4d0*g2*bT*bT
      elseif (npchoose.eq.2) then
         npvar = (1d0/4d0)*g2*4d0*dlog(1d0+bT*bT/4d0)
      endif


c$$$c     choose evolution kernel
c$$$      if (evchoose.eq.1) then
c$$$         call kernel_hyb(bT,Qi,m,Revo)
c$$$      elseif (evchoose.eq.2) then
c$$$         call kernel_css(m,Revo)
c$$$      elseif (evchoose.eq.3) then
c$$$         call kernel_eis(bT,Qi,m,Revo,1)
c$$$      elseif (evchoose.eq.4) then
c$$$         call kernel_eis(bT,Qi,m,Revo,2)
c$$$      elseif (evchoose.eq.5) then
c$$$         call kernel_eis(bT,Qi,m,Revo,3)
c$$$      elseif (evchoose.eq.6) then
c$$$         call kernel_css_num(m,Revo)
c$$$      end if

C     --- call to read the grids

      call PreCalc_DY(xA,mu_b,xfaa,cpdfa,Revo)
      call PreCalc_DY(xB,mu_b,xfbb,cpdfb,Revo)

c$$$C     --- call in order to have the evolved PDFs
c$$$
c$$$      call evolvePDF(xA, mu_b, xfaa)
c$$$      call evolvePDF(xB, mu_b, xfbb)
c$$$
c$$$C     --- call to the Wilson coefficient
c$$$
c$$$      call WCPDF(xA,mu_b,cpdfa)
c$$$      call WCPDF(xB,mu_b,cpdfb)

C     --- this is to correct our Wilsons to match the prescription used in NangaParbat

      xfaa=xfaa+ascorr*(xA*cpdfa - alphasPDF(mu_b)*pi/18d0*xfaa)
      xfbb=xfbb+ascorr*(xB*cpdfb - alphasPDF(mu_b)*pi/18d0*xfbb)

c$$$      xfaa=xfaa+ascorr*xA*cpdfa
c$$$      xfbb=xfbb+ascorr*xB*cpdfb

C     --- calculate integrand_DY_sum

      integrand_DY_sum=0.d0

      do jq=-5,5
         pnflag=1
         integrand_DY_sum = integrand_DY_sum + charge2(jq)*
     &    integrand_DY(bT)
      end do

C     --- original integrand_DY_sum

c$$$      integrand_DY_sum=0.d0
c$$$
c$$$      do jq=-5,5
c$$$         pnflag=1
c$$$         Pinteg_DY=charge2(jq)*integrand_DY(bT)
c$$$         pnflag=2
c$$$         Ninteg_DY=charge2(jq)*integrand_DY(bT)
c$$$         if (iexp.ne.6) then
c$$$            integrand_DY_sum= integrand_DY_sum +
c$$$     &           0.6d0*Ninteg_DY+0.4d0*Pinteg_DY !Pt or Cu -> "average" neutron 60% n 40% p
c$$$         else
c$$$            integrand_DY_sum= integrand_DY_sum +
c$$$     &           0.547d0*Ninteg_DY+0.453d0*Pinteg_DY
c$$$         end if
c$$$
c$$$      end do

      return
      end


      double precision function integrand_DY(bT)
      use com
      implicit none
      double precision ::  bT,Revo,aspi,f1_sea,f1_val,f1NP_FT_mod !using the function besj0 from cernlib
      double precision, dimension(-6:6) :: xfaa, xfbb
      integer :: jf
      common /evo/ Revo,xfaa,xfbb
      external aspi,f1_sea,f1_val,f1NP_FT_mod


      kt2avA(3)= Npt(3)*xA**bpts*(1d0-xA)**apts
     &     /(0.1d0**bpts*(1d0-0.1d0)**apts)
      kt2avB(3)= Npt(3)*xB**bpts*(1d0-xB)**apts
     &     /(0.1d0**bpts*(1d0-0.1d0)**apts)



      if ((abs(jq).eq.1).or.(abs(jq).eq.2)) then
         do jf=1,2
         kt2avA(jf)= Npt(jf)*xA**bpt*(1d0-xA)**apt
     &        /(0.1d0**bpt*(1d0-0.1d0)**apt)
         kt2avB(jf)= Npt(jf)*xB**bpt*(1d0-xB)**apt
     &        /(0.1d0**bpt*(1d0-0.1d0)**apt)
         end do
      end if



      if (pnflag.eq.2) then
         if (jq.eq.1) then
            k=2
         else if (jq.eq.2) then
            k=1
         else if (jq.eq.-1) then
            k=-2
         else if (jq.eq.-2) then
            k=-1
         else
            k=jq
         end if
      else if (pnflag.eq.1) then
         k=jq
      end if

C     --- integrand for comparison with NangaParbat

         integrand_DY =
     &         1/(2d0)*bT*dbesj0(pT*bT)
     &     * Revo * Revo
     &     * xfaa(k)/xA * xfbb(-k)/xB
     &     * f1NP_FT_mod(bT) * f1NP_FT_mod(bT)


C     ---  these are the original integrand_DY

c$$$c     if ((jq .eq. 1) .or. (jq.eq.2)) then
c$$$
c$$$         integrand_DY = 1/(2d0)*bT*dbesj0(pT*bT)
c$$$     &        *Revo*Revo
c$$$     &        *f1_val(xA,xfaa,k,bT,kt2avA)  ! valence PDF for A nucleon
c$$$     &        *f1_sea(xB,xfbb,-k,bT,kt2avB) ! qbar sea PDF for B nucleon
c$$$     &        *(m/Q0)**(-4d0*npvar)
c$$$
c$$$      else if ((jq .eq. -1) .or. (jq.eq.-2)) then
c$$$
c$$$         integrand_DY =
c$$$     &        1/(2d0)*bT*dbesj0(pT*bT)
c$$$     &        *Revo*Revo*
c$$$     &        f1_sea(xA,xfaa,k,bT,kt2avA)   ! q sea PDF for A nucleon
c$$$     &        *f1_val(xB,xfbb,-k,bT,kt2avB)   ! valence PDF for B nucleon
c$$$     &        *(m/Q0)**(-4d0*npvar)
c$$$
c$$$      else
c$$$
c$$$         integrand_DY =
c$$$     &        1/(2d0)*bT*dbesj0(pT*bT)
c$$$     &        *Revo*Revo*
c$$$     &        f1_sea(xA,xfaa,k,bT,kt2avA)    ! q sea PDF for A nucleon
c$$$     &        *f1_sea(xB,xfbb,-k,bT,kt2avB)   ! qbar sea PDF for B nucleon
c$$$     &        *(m/Q0)**(-4d0*npvar)
c$$$
c$$$      end if

      return
      end
c-------------------------------------------------------------------------
c     integrand for Z production
c-------------------------------------------------------------------------
      SUBROUTINE integZBy(w,U2,F2,v)
      use LeptonCutsDY
      use com
      implicit none
      integer w,l
      double precision integZBbT, dgmlt1
      double precision U2(*),F2(*),v(2)
      external integZBbT
      external dgmlt1

      DO L = 1,w
         v(2)=U2(L)
         if(iexp.le.10) then    !Tevatron: no cuts
            F2(L)= DGMLT1(integZBbT,0d0,10d0,15,6,v)

         else                   !LHC: include cuts
            F2(L)=CutFactor3(pT,m,v(2))*
     &           DGMLT1(integZBbT,0d0,10d0,15,6,v)/
     &           (1+0.5d0*(pT/m)**2)
         end if

      end do

      RETURN
      END
c-------------------------------------------------------------
      SUBROUTINE integZBbT(w,U1,F1,v)
      use com
      implicit none
      integer :: w, L
      double precision :: U1(*),F1(*),v(2)
      double precision :: Revo,aspi,f1_sea,f1_val,g1,f1NP_FT_mod ! f1NP_FT_mod added for the comparison with NangaParbat
      double precision :: bmin, bT
      double precision :: bTstar,mu_b2,sigma0,ulalem
      double precision,dimension(1:3)  :: kt2avAZ, kt2avBZ
      double precision,dimension(-6:6) :: xfaa, xfbb,cpdfa,cpdfb

      double precision alphasPDF
      external alphasPDF

      external aspi,f1_sea,f1_val,g1,ulalem,f1NP_FT_mod  ! f1NP_FT_mod added

      DO L=1,w
         v(1)=U1(L)
         F1(L)=0.d0
         bTstar=0d0

C     --- choose bstar prescription and calculate mu_b

         if (bpresc.eq.1) then
            bTstar = v(1)/dsqrt(1d0+(v(1)*v(1)/bmax/bmax))
         elseif (bpresc.eq.2) then
            bTstar = bmax*(1d0-dexp(-(v(1)/bmax)**4d0))**(1d0/4d0)
         elseif (bpresc.eq.3) then
            bmin = bmax * 1d0/m
            bTstar=bmax*(1d0-dexp(-(v(1)/bmax)**4d0))**(1d0/4d0)/
     &           (1d0-dexp(-(v(1)/bmin)**4d0))**(1d0/4d0)
         endif

         mu_b = 2d0*dexp(-gE)/bTstar
         mu_b2 = mu_b*mu_b

         alf2 = aspi(mu_b)*aspi(mu_b)

C     --- identify number of flavours

         if(mu_b.le.mc) then
            nf=3
         elseif(mu_b.gt.mc.and.mu_b.le.mb) then
            nf=4
         elseif(mu_b.gt.mb) then
            nf=5
         endif


c        choose NP parametrization
         if (npchoose.eq.1) then
            npvar = 1d0/4d0*g2*v(1)*v(1)
         elseif (npchoose.eq.2) then
            npvar = (1d0/4d0)*g2*4d0*dlog(1d0+v(1)*v(1)/4d0)
         endif

C     --- choose the kernel (not needed if we read from the grids)

c$$$C --- choose evolution kernel
c$$$         if (evchoose.eq.1) then
c$$$            call kernel_hyb(v(1),Qi,m,Revo)
c$$$         elseif (evchoose.eq.2) then
c$$$            call kernel_css(m,Revo)
c$$$         elseif (evchoose.eq.3) then
c$$$            call kernel_eis(v(1),Qi,m,Revo,1)
c$$$         elseif (evchoose.eq.4) then
c$$$            call kernel_eis(v(1),Qi,m,Revo,2)
c$$$         elseif (evchoose.eq.5) then
c$$$           call kernel_eis(v(1),Qi,m,Revo,3)
c$$$         elseif (evchoose.eq.6) then
c$$$            call kernel_css_num(m,Revo)
c$$$         endif

         xA = dsqrt(tau)*dexp(v(2))
         xB = dsqrt(tau)*dexp(-v(2))


C     --- call in order to have the evolved PDFs (if not read form the grids)

c$$$        call evolvePDF(xA, mu_b, xfaa)
c$$$        call evolvePDF(xB, mu_b, xfbb)


C     --- call to read the grids

         call PreCalc_Z(xA,mu_b,xfaa,cpdfa,revo)
         call PreCalc_Z(xB,mu_b,xfbb,cpdfb,revo)


C     --- this is to correct our Wilsons to match the prescription used in NangaParbat

         xfaa=xfaa+ascorr*(xA*cpdfa - alphasPDF(mu_b)*pi/18d0*xfaa)
         xfbb=xfbb+ascorr*(xB*cpdfb - alphasPDF(mu_b)*pi/18d0*xfbb)

C          xfaa=xfaa+ascorr*xA*cpdfa
C          xfbb=xfbb+ascorr*xB*cpdfb


         kt2avAZ(3)= Npt(3)*xA**bpts*(1d0-xA)**apts
     &        /(0.1d0**bpts*(1d0-0.1d0)**apts)
         kt2avBZ(3)= Npt(3)*xB**bpts*(1d0-xB)**apts
     &        /(0.1d0**bpts*(1d0-0.1d0)**apts)

C     --- loop over the flavours

         do jq=-5,5

            if ((jq.eq.1).or.(jq.eq.2)) then
               kt2avAZ(jq)= Npt(jq)*xA**bpt*(1d0-xA)**apt
     &              /(0.1d0**bpt*(1d0-0.1d0)**apt)
               kt2avBZ(jq)= Npt(jq)*xB**bpt*(1d0-xB)**apt
     &              /(0.1d0**bpt*(1d0-0.1d0)**apt)
            end if

C     --- calculate sigma0

            if (jq.eq.0) then   ! skip gluons
               sigma0=0d0

            else
               sigma0 =
     &              (4d0*pi**2*ulalem(m**2))/(3d0*enS(iexp))
     &              *((1d0-2d0*dsqrt(charge2(jq))*0.23126d0)**2+
     &              4d0*charge2(jq)*0.0534812d0)/ !value of sin2(thetaW)=0.23126
     &              (8d0*0.23126d0*0.76874d0)*0.033658d0 !branching ratio Z->l+l- 3.3658%
            end if


C           --- for comparison with NangaParbat --------------------------------

            if(iexp.le.10) then !  --- Tevatron
C ---     ppbar collision: sea and valence role inverted for antiproton

                  F1(l) = F1(l) + sigma0*1d0/(2d0)*v(1)*dbesj0(pT*v(1))
     &                 * Revo * Revo
     &                 * xfaa(jq)/xA * xfbb(jq)/xB
     &                 * f1NP_FT_mod(v(1)) * f1NP_FT_mod(v(1))
C     &                 *f1_val(xA,xfaa,jq,v(1),kt2avAZ) !nucleon A
C     &                 *f1_val(xB,xfbb,jq,v(1),kt2avBZ) !nucleon B

C             --- end of comparison with NangaParbat ---------------------------

C               if(iexp.le.10) then !Tevatron
C!     ppbar collision: sea and valence role inverted for antiproton
C!     valence
C
C               if ((jq .eq. 1) .or. (jq.eq.2)) then
C                  F1(l) = F1(l) + sigma0*1d0/(2d0)*v(1)*dbesj0(pT*v(1))
C     &                 *Revo*Revo
C     &                 *f1_val(xA,xfaa,jq,v(1),kt2avAZ) !nucleon A
C     &                 *f1_val(xB,xfbb,jq,v(1),kt2avBZ) !nucleon B
C     &                 *(m/Q0)**(-4d0*npvar)
C!     sea
C              else
C                  F1(l) = F1(l) + sigma0*1d0/(2d0)*v(1)*dbesj0(pT*v(1))
C     &                 *Revo*Revo
C     &                 *f1_sea(xA,xfaa,jq,v(1),kt2avAZ) !nucleon A
C     &                 *f1_sea(xB,xfbb,jq,v(1),kt2avBZ) !nucleon B
C     &                 *(m/Q0)**(-4d0*npvar)
C              end if

c$$$            else !LHC
c$$$               if ((jq .eq. 1) .or. (jq.eq.2)) then
c$$$                  F1(l) = F1(l) + sigma0*1d0/(2d0)*v(1)*dbesj0(pT*v(1))
c$$$     &                 *Revo*Revo
c$$$     &                 *f1_val(xA,xfaa,jq,v(1),kt2avAZ) !nucleon A
c$$$     &                 *f1_sea(xB,xfbb,-jq,v(1),kt2avBZ) !nucleon B
c$$$     &                 *(m/Q0)**(-4d0*npvar)
c$$$
c$$$               else if ((jq .eq.-1) .or. (jq.eq.-2)) then
c$$$                  F1(l) = F1(l) + sigma0*1d0/(2d0)*v(1)*dbesj0(pT*v(1))
c$$$     &                 *Revo*Revo
c$$$     &                 *f1_sea(xA,xfaa,jq,v(1),kt2avAZ) !nucleon A
c$$$     &                 *f1_val(xB,xfbb,-jq,v(1),kt2avBZ) !nucleon B
c$$$     &                 *(m/Q0)**(-4d0*npvar)
c$$$
c$$$               else  !sea
c$$$                  F1(l) = F1(l) + sigma0*1d0/(2d0)*v(1)*dbesj0(pT*v(1))
c$$$     &                 *Revo*Revo
c$$$     &                 *f1_sea(xA,xfaa,jq,v(1),kt2avAZ) !nucleon A
c$$$     &                 *f1_sea(xB,xfbb,-jq,v(1),kt2avBZ) !nucleon B
c$$$     &                 *(m/Q0)**(-4d0*npvar)
c$$$
c$$$               end if !flavor
            end if ! Experiment
         end do                 !jq
      END DO                    !l
      RETURN
      END ! C --- end subroutine integZBbT



c! Fourier Transform of non-perturbative PDF
      double precision function f1NP_FT(bT,g1a)

      use com,only: parc
      implicit none
      integer fl
      double precision bT,g1a

c      f1NP_FT=dexp(-g1a*bT)
      f1NP_FT=dexp(-g1a*bT*bT/(4d0))
     &        *(
     &          1d0-bT*bT/4d0*parc*g1a*g1a
     &          /(1d0+parc*g1a)
     &         )


      end function f1NP_FT

C     ----------------------------------------------------------------------
C     f1NP for the cross check with Valerio's NangaParbat code
C     Fourier Transform of non-perturbative PDF

C     --- Valerio's f1NP is
C     return exp( ( - g1 - g2 * log( sqrt(zetaf) / Q0 / 2 ) ) * b * b / 2 );

C     ----------------------------------------------------------------------

      double precision function f1NP_FT_mod(bT)
      use com, only: m, iexp
      implicit none

      double precision bT,Q0,g1,g2

C     --- values from NangaParbat

      g1 = 0.02d0
      g2 = 0.2d0
      Q0 = 1.6d0

      f1NP_FT_mod = dexp(
     &     (-g1-g2*dlog(m/(2d0*Q0)))*bT*bT/2d0
     &     )

      end function f1NP_FT_mod

C     ---------------------------------------------------------------------------

c! Fourier Transform of non-perturbative FF
      double precision function D1NP_FT(bT)

      use com,only: kt2av,kt2bv,parb
      implicit none
      double precision bT

      D1NP_FT=(kt2av*dexp(-kt2av*bT*bT/(4d0))+  !controlla 1/2pi davanti, diviso per z^2
     &         (parb*kt2bv*kt2bv)*
     &           (1d0-bT*bT/4d0*kt2bv)*dexp(-kt2bv*bT*bT/(4d0)))
     &         /(kt2av+parb*kt2bv*kt2bv)

      end function D1NP_FT

C     --- modified!
      double precision function f1_val(x,xf1,fl,bT,parg1)
       implicit none
       integer, intent(in) :: fl
       double precision,intent(in) :: x,xf1(-6:6),bt
       double precision :: parg1(1:3),f1NP_FT,f1NP_FT_mod      ! C --- I added f1NP_FT_mod
       external f1NP_FT,f1NP_FT_mod                            ! C --- I added f1NP_FT_mod

c$$$          f1_val = (xf1(fl)/x-xf1(-fl)/x)*f1NP_FT(bT,parg1(fl))
c$$$     &      +xf1(-fl)/x*f1NP_FT(bT,parg1(3))

          f1_val = (xf1(fl)/x)*f1NP_FT_mod(bT)


      end function f1_val


C     --- modified!
      double precision function f1_sea(x,xf1,fl,bT,parg1)
       implicit none
       integer,intent(in) :: fl
       double precision,intent(in) :: x,xf1(-6:6),bT
       double precision :: parg1(1:3),f1NP_FT,f1NP_FT_mod        ! C --- I added f1NP_FT_mod
       external f1NP_FT,f1NP_FT_mod                              ! C --- I added f1NP_FT_mod

c$$$            f1_sea=xf1(fl)/x*f1NP_FT(bT,parg1(3))
            f1_sea=xf1(fl)/x*f1NP_FT_mod(bT)

      end function f1_sea

c           parametrization of <pT2> distribution
c           the second line is to normalized Npt so that it corresponds to the
c           average transverse mom. square at x=0.1

      double precision function g1(fl,x)
       use com,only: Npt,bkt,apt,bpt,apts,bpts
       implicit none
       double precision,intent(in) :: x
       integer,intent(in) :: fl

        if ((fl.eq.1).or.(fl.eq.2)) then
                   g1= Npt(fl)*x**bpt*(1d0-x)**apt
     &                  /(0.1d0**bpt*(1d0-0.1d0)**apt)
        else
                   g1= Npt(3)*x**bpts*(1d0-x)**apts
     &                 /(0.1d0**bpts*(1d0-0.1d0)**apts)
        end if

      end function g1




c           parametrization of <kT2> in HERMES MC
c           the third and fourth lines are just to have Nkt representing the
c           normalization at z=0.5

      double precision function g3(ihad,j,z)
      use com,only: Nkt,bkt,gkt,ckt
      implicit none
      double precision z
      integer ihad,j

            g3 = Nkt(ihad,j)/z**2
     &           *(z**bkt + gkt)*(1.-z)**ckt
     &           *0.5d0**2
     &           /((0.5d0**bkt + gkt)*(1.-0.5d0)**ckt)

      end function g3


      double precision function g4(z)
      use com,only: Nptb,bkt,gkt,ckt
      implicit none
      double precision z

            g4 = Nptb/z**2
     &           *(z**bkt + gkt)*(1.-z)**ckt
     &           *0.5d0**2
     &           /((0.5d0**bkt + gkt)*(1.-0.5d0)**ckt)

      end function g4
