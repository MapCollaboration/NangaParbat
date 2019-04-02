      subroutine chisquare(npar,grad,chi2,param,iflag,futil)
      use com
      use normaliz_bin
      use normal_firstbin
      use LeptonCutsDY
      implicit none
      integer iflag, npar,ir
      integer i
      integer ib,ib0
      integer ngauss
      real*8 qgauss
      real*8 integrand_css,integ
      double precision integrand_DY_sum, integ_DY,integ_Z
      double precision num,diffdsig,alphasPDF
      double precision t1, t2, errt1, errt2, dsigdptDIVsig
      double precision t10, dsigdptDIVsig0
      double precision  chi2,chi2SD,chi2DY,chi2ZB,chi20,
     &                  res, res0,chi2SD_0,chi2DY_0,chi2ZB_0,
     &                  chi2parSD(1:2,1:2,-2:2),
     &                  chi2parSD0(1:2,1:2,-2:2),
     &     chi2parDYZ(3:size(experiment)),
     &     chi2parDYZ_0(3:size(experiment))
      double precision  datamatDY(6,2500),
     &                  datamatZ(7,1000),datamatDY0(6,2500),
     &                  datamatZ0(7,1000)
      double precision  ymax,ymin
      double precision sigZ(7:size(experiment)),
     &    errsigZ(7:size(experiment)),NormZ(7:size(experiment))
      double precision xF, m2,mu,Edsigd3p,dsigdpt,errstatDY,
     &                 errsystDY, errsystDY0, errsigDY2, errsigDY20,
     &                 errstatZ,errsystZ,
     &                 errlumZ,errlumZ0,errsigZ2, errsigZ20,
     &                 Edsigd3p_0, dsigdpt_0, sigma0, v(2)
      double precision Dsig, dsig_q, Dsig_th, Hf,
     &     convF, convFZ,Qbini,Qbinf,Q
      double precision Pinteg_DY, Ninteg_DY
      double precision ulalem, aspi
      double precision mult,mult0,stat,sys,err2,err20
      double precision stat0,sys0
      double precision multtheo, errtheo2, numerrtheo2
      double precision elembin(3,100),elembin0(3,100)
      double precision norm,norm0
      double precision resbin,resbin0
      double precision Php2av(1:3)
      double precision xf1(-6:6)
      double precision dgmlt2
!      double precision,parameter :: eu2= 4.d0/9.d0,ed2=1.d0/9.d0

c parameters
      double precision Nktfv, Nktunfv,
     &     NktKs, NktKu, Nptc

c this is to include errors in the fragmentation functions
      double precision zbinning(9),favored(8),upion(6),dbpion(6),
     &     unfav(6), cpion(6), spion(6), sbkaon(6), ukaon(6),
     &     unfavkaon(6),ckaon(6)

      double precision integrand_sidis_fuu,integrand_sidis_fuu_cosphi,
     &     integrand_sidis_fuu_cos2phi


      external dgmlt2
      external ulalem
      external aspi
      external integrand_DY_sum
      external integZBy

      external integrand_sidis_fuu,integrand_sidis_fuu_cosphi,
     &     integrand_sidis_fuu_cos2phi

c the following are necessary for the calls to the minuit subroutine mnstat
      double precision grad(*),param(*),futil(*)
      double precision fmin, fedm, errdef, dof
      integer inpari, inparx, istat
      double precision covmat(100,100)

      integer is,ifinis
      common/FFset/is,ifinis



c-------------------------------------------------------------
c declaration of constants
c-------------------------------------------------------------
c     ifinihad is used to set fini=0 when had changes
c     in the beginning is set different from any hadron value
      ifinihad=10

!  save the value of iflag for common variables module
      ifl=iflag

c     Values of sigma and their errors for Z boson production
      sigZ = (/248d0,221d0,256.1d0,255.8d0,251.47d0,181.53d0,
     &     17.1d0,113.8d0,112.9d0,109.76d0,91.94d0,59.14d0,19.58d0,
     &  384.94d0,427.32d0,69.85d0,88.98d0,185.0d0,448.56d0,505.53d0/)
      errsigZ = (/11d0,11.2d0,15.1d0,16.7d0,0d0,0d0,0d0,
     &     0.06d0,0.08d0,0.08d0,0.06d0,0.04d0,0.02d0,0.17d0,
     &     0.53d0,0.3d0,0.40d0,0.09d0,0.19d0,0.21d0/)

      if (Znorm.eq.0) then
c        Values of the normalization theory/data, taken from D'Alesio et al.
         NormZ  =(/1.114d0,0.992d0,1.049d0,1.048d0,1.d0,1d0,
     &        1.d0,1.d0,1.d0,1.d0,1d0,1d0,1.d0,1.d0,
     &        1.d0,1.d0,1d0,1d0,1.d0,1.d0/)
      elseif (Znorm.eq.1) then
c        Values of the normalization theory/data, fitted with gaussian NP
         NormZ  = (/1.21d0,1.06d0,1.14d0,1.14d0,1.d0,1.d0,
     &        1.d0,1.d0,1.d0,1d0,
     &        1.d0,1.d0,1.d0,1.d0,1d0,1d0,1.d0,1.d0,1.d0,1.d0/)
      endif

c     these are necessary for the errors on the fragmentation functions
c     they are taken from 1209.3240
      zbinning=(/0d0, 0.2d0, 0.3d0, 0.4d0, 0.5d0,
     &     0.6d0, 0.7d0, 0.8d0, 1d0 /)


c     favored for pi+
      upion= (/0.13d0,0.04d0,0.04d0,0.04d0,0.05d0,0.05d0
     &       /)
      dbpion= (/0.08d0,0.04d0,0.04d0,0.04d0,0.04d0,0.05d0
     &       /)

c    unfavored: the values are the ones for ub
      unfav  = (/0.2d0,0.07d0,0.08d0,0.09d0,0.11d0,0.15d0
     &         /)

      spion  = (/0.4d0,0.2d0,0.17d0,0.2d0,0.26d0,0.31d0
     &         /)
      cpion= (/0.23d0,0.13d0,0.12d0,0.15d0,0.18d0,0.33d0
     &     /)
      ukaon  = (/0.19d0,0.09d0,0.08d0,0.08d0,0.07d0,0.07d0
     &         /)
      unfavkaon = (/0.5d0,0.17d0,0.18d0,0.15d0,0.24d0,0.47d0
     &      /)
      sbkaon = (/0.45d0,0.13d0,0.08d0,0.07d0,0.08d0,0.09d0
     &     /)
      ckaon = (/0.26d0,0.11d0,0.11d0,0.11d0,0.12d0,0.15d0
     &     /)
c-------------------------------------------------------------
c instructions for iflag=1
c-------------------------------------------------------------
      if(iflag.eq.1) then
c-------------------------------------------------------------
c lhapdf
c-------------------------------------------------------------
c         call SetPDFPath('/usr/local/share/LHAPDF')
         call InitPDFsetByName(name)
         call InitPDF(N)
c-------------------------------------------------------------
c reading experimental data
c-------------------------------------------------------------
c         call readdata(irepl,datamat,0,izx,1)
c         call readdataDY(irepl,datamatDY,0,0)
c         call readdataZ(irepl,datamatZ,0,1)
c         call readdata(0,datamat0,0,izx,0)
c         call readdataDY(0,datamatDY0,0,1)

c     here I read the random values necessary for the variation of D1
         open(unit=16,file='ffgrids/vard1.dat')
         READ(UNIT=16,FMT=217)
     &        (((vard1(ihad,j,izbin),izbin=1,10),j=-6,6),ihad=-2,2)
 217     FORMAT(10(D13.6,1x))
         close(unit=16)

!---read denominator
         den=0d0
         call readdenom


c     vectors for squared charge of partons

       charge2=(/eu2,ed2,eu2,ed2,eu2,ed2,0.d0,ed2,eu2,ed2,eu2,ed2,eu2/)

! stop if there are two conflicting norm active at the same time
       if ((normONOFF).eqv.(norm1binONOFF)) STOP

      end if
c-------------------------------------------------------------
c end iflag=1
c-------------------------------------------------------------
c-------------------------------------------------------------
c definition of parameters and normalizations
c-------------------------------------------------------------
c     assignment of parameters
      if (iflavindep.eq.0) then
c        for flavor-dependent analysis
         Npt(1)=param(1)        ! down valence
         Npt(2)=param(2)        ! up valence
         Npt(3)=param(3)        ! sea
      else if (iflavindep.eq.1) then
c        for flavor-independent analysis
         Npt(1)=param(1)        ! down valence
         Npt(2)=param(1)        ! up valence
         Npt(3)=param(1)        ! sea
      end if

      apt=param(4)
      bpt=param(5)

      Nktfv=0d0
      Nktunfv=0d0
      NktKs=0d0
      NktKu=0d0
      if (iflavindep.eq.0) then
         Nktfv=param(6)
         Nktunfv=param(7)
         NktKs=param(8)
         NktKu=param(9)
      else if (iflavindep.eq.1) then
         Nktfv=param(6)
         Nktunfv=param(6)
         NktKs=param(6)
         NktKu=param(6)
      end if
      bkt=param(10)
      ckt=param(11)
      gkt=param(12)
      g2=param(13)
      parb= param(16)
      Nptb=param(17)
      parc=param(18)
      Nptc=0d0

      if (iflavindep.eq.0) then
         apts = param(19)
         bpts = param(20)
      else if (iflavindep.eq.1) then
         apts = param(4)
         bpts = param(5)
      end if

c     trivial normalization
      do itar=1,2
         do ihad=-2,2
           do iexp=1,2
           normlz(iexp,itar,ihad)=1d0
           end do
         end do
      end do

c     assignment of Nkt parameter width for each different FF
      do i=-2,2
         do j=-6,6
            Nkt=Nktunfv
         end do
      end do

c     favored pi+
      Nkt(1,2)=Nktfv
      Nkt(1,-1)=Nktfv
c     favored pi-
      Nkt(-1,-2)=Nktfv
      Nkt(-1,1)=Nktfv
c     favored K+
      Nkt(2,2)=NktKu
      Nkt(2,-3)=NktKs
c     favored K-
      Nkt(-2,-2)=NktKu
      Nkt(-2,3)=NktKs

c$$$      if(iflag.eq.3) then
c$$$         write(8,*) '# tar had     Q2             x             z
c$$$     &   PhT            mult       multtheo         err       res'
c$$$      end if

      if(iflag.eq.1) then !write header of binned.out
        write(14,'(a30)',advance='no') '#bin  iexp   itar   ihad   '
        if (flagQbinSD) write(14,'(a20)',advance='no') 'Q2_low Q2_upp  '
        if (flagXbinSD) write(14,'(a20)',advance='no') 'x_low  x_upp   '
        if (flagZbinSD) write(14,'(a20)',advance='no') 'z_low  z_upp'
        write(14,*)
      end if
c-------------------------------------------------------------
c inizialization of variables
c-------------------------------------------------------------
      chi2=0d0
      chi20=0d0
      chi2SD=0d0
      chi2DY=0d0
      chi2ZB=0d0
      chi2SD_0=0d0
      chi2DY_0=0d0
      chi2ZB_0=0d0

      chi2parSD=0d0
      chi2parSD0=0d0
      chi2parDYZ=0d0
      chi2parDYZ_0=0d0

c     common initial scale for TMD evolution
      Q0=dsqrt(1.0d0)           !Q0=Q_i to be consistent with Hermes fit
      Qi=dsqrt(1.0d0)

!c AB change 2
      ndatSDin=0d0
      ndatparSDin=0d0
!c AB end of change 2

      prevXbin=0d0;prevQ2bin=0d0;prevZbin=0d0;
      index1bin=0

      ib=0; ib0=0

c-------------------------------------------------------------
c beginning of multiplicities
c-------------------------------------------------------------
      BOOLSD: if (SDboole) then

      if(iflag.eq.3) then
      write(8,*) '# tar had     Q2             x             z
     &   PhT            mult       multtheo         err       res'
      end if
c-------------------------------------------------------------
c calculation of chi2: experimental data
c-------------------------------------------------------------
      if (iflag.eq.1) then
         call readdata(irepl,datamat,1,1) !read repl data
         call readdata(0,datamat0,1,0)    !read orig data
      end if

      SDLOOP: do i=1,ndatSD

         iexp=int(datamat(1,i))
         itar=int(datamat(2,i))
         ihad=int(datamat(3,i))
         ibin=int(datamat(11,i))
         mult=datamat(4,i)
         stat=datamat(5,i)
         sys=datamat(6,i)
         mult0=datamat0(4,i)
         stat0=datamat0(5,i)
         sys0=datamat0(6,i)
         q2 = datamat(7,i)
         x = datamat(8,i)
         z = datamat(9,i)
         Php = datamat(10,i)
         if (ibin.ne.bindenom(i)) then  !check that data and denom do correspond
           write(*,*) "ERROR: denominator does not correspond to data"
           STOP
         end if

         write(122,*) i,bindenom(i),den(i)
         write(122,*)

         if (norm1binONOFF) then

!  AB change 3 to normalize to first bin
           call norm1bins(x,q2,z,mult,stat,sys,1)     !repl data
           call norm1bins(x,q2,z,mult0,stat0,sys0,0)  !orig data

!  the contribution to chi2 is 0, but we must take care of not increasing the n. of degrees of freedom
           call norm1bin_count_dof

         end if

c-------------------------------------------------------------
c calculation of chi2: theoretical predictions
c-------------------------------------------------------------
         Qf=dsqrt(q2)
c         Qi2=Qi*Qi
c         Qf2=Qf*Qf

c        assignement of errors on fragmentation functions
         do j=1,8
            if ((z.gt.zbinning(j)).and.(z.lt.zbinning(j+1))) then
               izbin=j
            end if
         end do

c        about 50% error by default
         do j=-2,2
            do k=-6,6
               deltazd1(j,k)=0.5d0
            end do
         end do

c        favored pi+
         deltazd1(1,2)=upion(izbin)
         deltazd1(1,-1)=dbpion(izbin)

c        unfavored pi+
         deltazd1(1,1)=unfav(izbin)
         deltazd1(1,-2)=unfav(izbin)

c        strange to pi+
         deltazd1(1,3)=spion(izbin)
         deltazd1(1,-3)=spion(izbin)

c        charm to pi+
         deltazd1(1,4)=cpion(izbin)
         deltazd1(1,-4)=cpion(izbin)

c        favored pi-
         deltazd1(-1,-2)=upion(izbin)
         deltazd1(-1,1)=dbpion(izbin)

c        unfavored pi-
         deltazd1(-1,-1)=unfav(izbin)
         deltazd1(-1,2)=unfav(izbin)

c        strange to pi-
         deltazd1(-1,3)=spion(izbin)
         deltazd1(-1,-3)=spion(izbin)

c        charm to pi-
         deltazd1(-1,4)=cpion(izbin)
         deltazd1(-1,-4)=cpion(izbin)

c        u to K
         deltazd1(2,2)=ukaon(izbin)
         deltazd1(-2,-2)=ukaon(izbin)

c        unfav to kaon (as s to K)
         deltazd1(2,1)=unfavkaon(izbin)
         deltazd1(-2,1)=unfavkaon(izbin)

         deltazd1(2,-1)=unfavkaon(izbin)
         deltazd1(-2,-1)=unfavkaon(izbin)

         deltazd1(2,-2)=unfavkaon(izbin)
         deltazd1(-2,2)=unfavkaon(izbin)

         deltazd1(2,3)=unfavkaon(izbin)
         deltazd1(-2,-3)=unfavkaon(izbin)

c        sb to kaon
         deltazd1(2,-3)=sbkaon(izbin)
         deltazd1(-2,3)=sbkaon(izbin)

c        charm to kaon
         deltazd1(2,4)=ckaon(izbin)
         deltazd1(-2,4)=ckaon(izbin)

         deltazd1(2,-4)=ckaon(izbin)
         deltazd1(-2,-4)=ckaon(izbin)

c     calculate Hard factor
         mu=Qf
         Hf=1d0
     &    +ascorr*alphasPDF(mu)*2d0/3d0/pi*(-(dlog(Qf**2/mu**2))**2
     &   +3d0*dlog(Qf**2/mu**2)-8d0)

         num=0d0
        ! den=0d0
         numerrtheo2=0d0

         call evolvePDF(x, dsqrt(q2), xf1)

         do j=-4,4
c           parametrization of <kT2> in HERMES MC
c           the third and fourth lines are just to have Nkt representing the
c           normalization at z=0.5
            kt2av = Nkt(ihad,j)/z**2
     &           *(z**bkt + gkt)*(1.-z)**ckt
     &           *0.5d0**2
     &           /((0.5d0**bkt + gkt)*(1.-0.5d0)**ckt)
            kt2bv = Nptb/z**2
     &           *(z**bkt + gkt)*(1.-z)**ckt
     &           *0.5d0**2
     &           /((0.5d0**bkt + gkt)*(1.-0.5d0)**ckt)


            k=j

c           parametrization of pT distribution including everything except D1(z)
c           the second line is to normalized Npt so that it corresponds to the
c           average transverse mom. square at x=0.1
            pt2av(3)= Npt(3)*x**bpts*(1d0-x)**apts
     &           /(0.1d0**bpts*(1d0-0.1d0)**apts)
            Php2av(3) =z**2*(pt2av(3)+kt2av)
            if ((j.eq.1).or.(j.eq.2)) then
               pt2av(j)= Npt(j)*x**bpt*(1d0-x)**apt
     &              /(0.1d0**bpt*(1d0-0.1d0)**apt)
               Php2av(j) =z**2*(pt2av(j)+kt2av)
            end if

!--- calculate denominator and numerator of multiplicities

            ngauss=6
            !den=den + charge2(j)*xf1(k)/x !denominator LO
            integ=qgauss(integrand_sidis_fuu,0.d0,20.d0,ngauss)
c           normlz is a fit parameter for normalization, now fixed at 1(fitinput)
            num=num+Hf*normlz(iexp,itar,ihad)*charge2(j)
     &           *2d0*pi*Php
     &           *(1d0+vard1(ihad,j,izbin)*deltazd1(ihad,j))
     &           *integ

            numerrtheo2=numerrtheo2  !theoretical value
     &           +(Hf*normlz(iexp,itar,ihad)*charge2(j)
     &           *2d0*pi*Php
     &           *deltazd1(ihad,j)
     &           *integ
     &           )**2

            if (itar.eq.2) then !valence case
               if (j.eq.1) then
                  k=2
               else if (j.eq.2) then
                  k=1
               else if (j.eq.-1) then
                  k=-2
               else if (j.eq.-2) then
                  k=-1
               else
                  k=j
               end if

c              parametrization of pT distribution including everything except D1(z)
c              the second line is to normalized Npt so that it corresponds to the
c              average transverse mom. square at x=0.1
               pt2av(3)= Npt(3)*x**bpts*(1d0-x)**apts
     &              /(0.1d0**bpts*(1d0-0.1d0)**apts)
               Php2av(3) =z**2*(pt2av(3)+kt2av)

               if ((j.eq.1).or.(j.eq.2)) then
                  pt2av(k)= Npt(k)*x**bpt*(1d0-x)**apt
     &                 /(0.1d0**bpt*(1d0-0.1d0)**apt)
                  Php2av(k) =z**2*(pt2av(k)+kt2av)
               end if

               ngauss=6
               !den=den + charge2(j)*xf1(k)/x !denominator LO
          integ=qgauss(integrand_sidis_fuu,0.d0,20.d0,ngauss)
c              normlz is a fit parameter for normalization, now fixed at 1(fitinput)
               num=num +Hf*normlz(iexp,itar,ihad)*charge2(j)
     &              *2d0*pi*Php
     &              *(1d0+vard1(ihad,j,izbin)*deltazd1(ihad,j))
     &              *integ
               numerrtheo2=numerrtheo2
     &              +(Hf*normlz(iexp,itar,ihad)*charge2(j)
     &              *2d0*pi*Php
     &              *deltazd1(ihad,j)
     &              *integ
     &              )**2
            end if ! end of deuteron if
         end do ! end of j loop

         multtheo=num/den(i)
         errtheo2= numerrtheo2/den(i)**2

! AB change 4 to normalize to first bin
         if (norm1binONOFF) then
              call norm1bins_theo(x,q2,z,multtheo,errtheo2)
         end if

         err2=0d0
         err20=0d0
         if (errfrag.eq.0) then
            err2=stat**2+sys**2
            err20=stat0**2+sys0**2
         elseif (errfrag.eq.1) then
            err2=stat**2+sys**2+errtheo2
            err20=stat0**2+sys0**2+errtheo2
         endif

!c-------------------------------------------------------------
!c  Calculate bin normalization and chi2
!c-------------------------------------------------------------

      if (normONOFF) then

         call create_bin_elem_array(ib,multtheo,mult,err2,elembin)
         call create_bin_elem_array(ib0,multtheo,mult0,err20,elembin0)

       if (ibin.ne.int(datamat(11,i+1))) then
C
         call normbin(ib,elembin,norm)
         !call normbin(ib0,elembin0,norm0)
         norm0=norm !use same normaliz for original and repl data

         if (iflag.eq.3) write(25,'(i3,3(2x,i3),3(f7.4),5x,f7.4)')
     &                              ibin,iexp,itar,ihad,x,Q2,z,norm

         call calc_chi2_bin(ib,norm,elembin,resbin)
         chi2SD=chi2SD+resbin
         chi2parSD(iexp,itar,ihad)=chi2parSD(iexp,itar,ihad)+resbin

         call calc_chi2_bin(ib0,norm0,elembin0,resbin0)
         chi2SD_0=chi2SD_0+resbin0
         chi2parSD0(iexp,itar,ihad)=chi2parSD0(iexp,itar,ihad)+resbin0

         ib=0; ib0=0
C
       end if
      end if


!c-------------------------------------------------------------
!c calculation of chi2: putting all together
!c-------------------------------------------------------------

       if (.NOT. normONOFF) then

         res=(mult-multtheo)**2/err2
         chi2SD=chi2SD+res
         chi2parSD(iexp,itar,ihad)=chi2parSD(iexp,itar,ihad)+res

         res0=(mult0-multtheo)**2/err20
         chi2SD_0=chi2SD_0+res0
         chi2parSD0(iexp,itar,ihad)=chi2parSD0(iexp,itar,ihad)+res0

       end if

!--- save x,q,z values of current bin
                prevXbin=x
                prevQ2bin=q2
                prevZbin=z
                index1bin=0
!         if (norm1binONOFF) call save_bin_values(x,z,q2)


         if(iflag.eq.3) then
            write(8,411) itar, ihad, Q2, x, z, Php, mult, multtheo,
     &           dsqrt(err2), res
 411        FORMAT(2(1x,I3),8(1x,E13.6),(1x,I3))
         end if
      end do  SDLOOP            !end of ndatSD

      if (normONOFF) then
        ndatparSDin=ndatparSD-NtotbinSD
        ndatSDin=ndatSD-SUM(NtotbinSD)
      end if
! ndatparSDin and ndatSDin are counted in norm.f90 for norm1bin normaliz.

      end if BOOLSD


c-------------------------------------------------------------
c beginning of DRELL--YAN
c-------------------------------------------------------------
      if (DYboole) then

      if(iflag.eq.3) then
         write(8,*) '# iexp   m        pT             Dsig_th
     &   Edsigd3p         dsqrt(errsigDY2)'
      end if
c-------------------------------------------------------------
c calculation of chi2: experimental data
c-------------------------------------------------------------
      if (iflag.eq.1) then
        call readdataDY(irepl,datamatDY,1,1)
        call readdataDY(0,datamatDY0,1,0)
      end if

      DYLOOP: do i=1,ndatDY


         iexp=int(datamatDY(1,i))
         ibin=int(datamatDY(6,i))
         m=datamatDY(2,i)
         m2=m**2
         pT=datamatDY(3,i)
         Edsigd3p=datamatDY(4,i)
         Edsigd3p_0=datamatDY0(4,i)
         errstatDY=datamatDY(5,i)
         errsystDY=0.25d0*Edsigd3p
         errsystDY0=0.25d0*Edsigd3p_0
         if(iexp.eq.6) then
            errsystDY=0.15d0*Edsigd3p
            errsystDY0=0.15d0*Edsigd3p_0
         end if

c-------------------------------------------------------------
c calculation of chi2: theoretical predictions
c-------------------------------------------------------------
c        define kinematical variables
         tau=m2/enS(iexp)
         xA = dsqrt(tau)*dexp(y(iexp))
         xB = dsqrt(tau)*dexp(-y(iexp))
         if (iexp.eq.6) then
            xF=0.1d0
            xA=(sqrt_enS(iexp)*xF
     &           + dsqrt(4d0*m2+enS(iexp)*xF**2))/(2d0*sqrt_enS(iexp))
            xB=xA-xF
         end if

         Q=m
         Qbini=m-0.5d0 ! initial value of M bin
         Qbinf=m+0.5d0 ! final value of M bin

         Dsig=0d0

C     --- calculate Hard factor

         mu=Q

C     --- Hard factor of our fit in newcode

c$$$         Hf=1d0
c$$$     &    +ascorr*alphasPDF(mu)*2d0/3d0/pi*(-(dlog(Q**2/mu**2))**2
c$$$     &        +3d0*dlog(Q**2/mu**2)-8d0+pi**2)

C     --- Hard factor corrected with the prescription for the Wilson used in NangaParbat

         Hf=1d0
     &    +ascorr*alphasPDF(mu)*2d0/3d0/pi*(-(dlog(Q**2/mu**2))**2
     &        +3d0*dlog(Q**2/mu**2)-8d0+pi**2*7d0/6d0)

C     --- calculate Dsig

         sigma0 = (4*ulalem(m2)**2)/(3*3*enS(iexp))
         ngauss=10

         Dsig = sigma0*qgauss(integrand_DY_sum,0.d0,20d0,ngauss)

c        conversion factor to change from 1/GeV^4 to cm^2/GeV^2 (unit of E288 exp data)
c        initial conversion factor for 1/GeV^2 to picobarn (natural units)
         convF=0.389379d9       ![(hbar*c)^2 * 10^9)]
c        next steps
c         pbarn-->barn:  *10^-12
c         barn-->m^2 :  *10^-28
c         m^2-->cm^2:  *10^4
c        total conversion factor
c         0.389379*10^(9-12-28+4)
!         convF= 0.389379d-27

C     --- calculate Dsig_th

         Dsig_th = 1.d0/m2*Hf*Dsig*convF

C     original Dsig_th
!        Dsig_th=dlog((Qbinf**2)/(Qbini**2))*Hf*Dsig*convF


C     --- check with NangaParbat for E288_200

c$$$         if(iexp.eq.5.and.m.eq.5.5d0) then
c$$$
c$$$          open(unit = 581, file = 'checkNP.out')
c$$$            do j = -2,1
c$$$               write(581,*) 10d0**j, integrand_DY_sum(10d0**j)
c$$$            end do
c$$$          close(unit = 581)
c$$$
c$$$         end if

C     --- calculate errors

         errsigDY2=errstatDY**2+errsystDY**2
         errsigDY20=errstatDY**2+errsystDY0**2


!--- Calculate bin normalization

      if (normONOFF) then

       call create_bin_elem_array(ib,Dsig_th,Edsigd3p,errsigDY2,elembin)
       call create_bin_elem_array(ib0,Dsig_th,Edsigd3p_0,
     &                            errsigDY20,elembin0)

      if (ibin.ne.int(datamatDY(6,i+1))) then


          call normbin(ib,elembin,norm)
!          call normbin(ib0,elembin0,norm0)
          norm0=norm !use same normaliz for original and repl data


          if (iflag.eq.3) write(25,'(i3,2x,i3,2x,f7.4,5x,f7.4)')
     &                                        ibin,iexp,m,norm

          call calc_chi2_bin(ib,norm,elembin,resbin)
          chi2DY=chi2DY+resbin
          chi2parDYZ(iexp)=chi2parDYZ(iexp)+resbin

          call calc_chi2_bin(ib0,norm0,elembin0,resbin0)
          chi2DY_0=chi2DY_0+resbin0
          chi2parDYZ_0(iexp)=chi2parDYZ_0(iexp)+resbin0

          ib=0; ib0=0
      end if
      end if


c-------------------------------------------------------------
c calculation of chi2: putting all together
c------------------------------------------------------------

      if (.NOT. normONOFF) then
         res=(((Edsigd3p-Dsig_th)*10d40)**2)/((errstatDY*10d40)**2
     &        +(errsystDY*10d40)**2)
         chi2DY=chi2DY+res
         chi2parDYZ(iexp)=chi2parDYZ(iexp)+res

         res0=(Edsigd3p_0-Dsig_th)**2/(errsigDY20)
         chi2DY_0= chi2DY_0+res0
         chi2parDYZ_0(iexp)=chi2parDYZ_0(iexp)+res0

      end if

         diffDsig=Edsigd3p-Dsig_th
         if(iflag.eq.3) then
            write(8,410) iexp, m, pT, Dsig_th, Edsigd3p,
     &           dsqrt(errsigDY2)!, res
 410        FORMAT(1x,I3,6(1x,E13.6))
         end if

         if (normONOFF) then
           ndatparDYin=ndatparDY-NtotbinDY
           ndatDYin=ndatDY-SUM(NtotbinDY)
         else
           ndatparDYin=ndatparDY
           ndatDYin=ndatDY
         end if

      end do DYLOOP ! end of ndatDY loop

      end if
c-------------------------------------------------------------
c beginning of Z boson
c-------------------------------------------------------------
      if (Zboole) then

         if(iflag.eq.3) then
         write(8,*) 'Z boson production'
         write(8,*) '#iexp     pT          Dsig_th      dsig_exp
     & err         (rel.err)^2'

         end if
c-------------------------------------------------------------
c calculation of chi2: experimental data
c-------------------------------------------------------------

      if (iflag.eq.1) then
         call readdataZ(irepl,datamatZ,1,1)
         call readdataZ(0,datamatZ0,1,0)
      end if

      ZLOOP: do i=1,ndatZ

         iexp=int(datamatZ(1,i))
         ibin=int(datamatZ(7,i))
         m=91.1876d0
         m2=m**2
         pT=datamatZ(3,i)
         dsigdpt=datamatZ(4,i)
         dsigdpt_0=datamatZ0(4,i)
         errstatZ=datamatZ(5,i)
         errsystZ=datamatZ(6,i)
         errlumZ=0d0
         errlumZ0=0d0
         if (iexp.eq.7) then    ! luminosity error for CDF_RunI
            errlumZ=0.039*dsigdpt
            errlumZ0=0.039*dsigdpt_0
         else if (iexp.eq.8) then ! luminosity error for D0_RunI
            errlumZ=0.044*dsigdpt
            errlumZ0=0.044*dsigdpt_0
         else if (iexp.eq.9) then ! luminosity error for CDF_RunII
            errlumZ=0.058*dsigdpt
            errlumZ0=0.058*dsigdpt_0
         end if
c        data published for D0 Run II as (1/sig)dsig/dpt, we need dsig/dpt
         dsigdptDIVsig=0d0
         dsigdptDIVsig0=0d0
         if (iexp.eq.10) then
            dsigdpt=datamatZ(4,i)*sigZ(iexp)
            dsigdptDIVsig=datamatZ(4,i) !used later for error propag.
            dsigdpt_0=datamatZ0(4,i)*sigZ(iexp)
            dsigdptDIVsig0=datamatZ0(4,i) !used later for error propag.
         end if


         !!!!CUTS!!!!
         if(iexp.ge.11.and.iexp.le.19) then !binned ATLAS
            call SetCutParameters(20d0,-2.4d0,2.4d0)
         else if(iexp.ge.20.and.iexp.le.21) then !CMS
           call SetCutParameters(20d0,-2.1d0,2.1d0)
         else if(iexp.ge.22.and.iexp.le.24) then !LHCb
            call SetCutParameters(20d0,2d0,4.5d0)
         else if(iexp.ge.25) then !ATLAS allY
            call SetCutParameters(20d0,-2.4d0,2.4d0)
         end if


c-------------------------------------------------------------
c calculation of chi2: theoretical predictions
c-------------------------------------------------------------
c     define kinematical variables
         Q=m
         Dsig=0d0
         mu=Q

C     --- calculate Hard Factor

C          --- as in newcode_LHC

C        Hf=1d0
C     &    +ascorr*alphasPDF(mu)*2d0/3d0/pi*(-(dlog(Q**2/mu**2))**2
C     &        +3d0*dlog(Q**2/mu**2)-8d0+pi**2)

C          --- hard factor corrected with the prescription used in NangaParbat

         Hf=1d0
     &    +ascorr*alphasPDF(mu)*2d0/3d0/pi*(-(dlog(Q**2/mu**2))**2
     &        +3d0*dlog(Q**2/mu**2)-8d0+pi**2*7d0/6d0)

C     --- Conversion factor, from 1/GeV^2 to picobarn (natural units)

         convFZ= 0.389379d9

C     --- calculate Dsig_th

         tau=m2/enS(iexp)

         if(iexp.le.10)then ! Tevatron

          ymax=-0.5d0*dlog(tau)

          integ_Z = dgmlt2(integZBy,-ymax,ymax,5,6,v)

          Dsig = convFZ*2d0*pT*integ_Z

         else if(iexp.ge.11.and.iexp.le.21)then ! ATLAS binned in y & CMS

           ymin=rapmin(iexp-10)
           ymax=rapmax(iexp-10)

           integ_Z=2d0*(dgmlt2(integZBy,ymin,ymax,5,6,v))

           Dsig = convFZ*2d0*pT*integ_Z/sigZ(iexp)

         else if(iexp.ge.22.and.iexp.le.24) then ! LHCb

           ymin=rapmin(iexp-10)
           ymax=rapmax(iexp-10)

           integ_Z=dgmlt2(integZBy,ymin,ymax,5,6,v)

           Dsig = convFZ*2d0*pT*integ_Z

         else if(iexp.ge.25) then ! ATLAS 7 and 8 TeV not binned in rapidity

           ymin=rapmin(iexp-10)
           ymax=rapmax(iexp-10)

           integ_Z=2d0*(dgmlt2(integZBy,ymin,ymax,5,6,v))

           Dsig = convFZ*2d0*pT*integ_Z/sigZ(iexp)

          end if

          Dsig_th=Hf*NormZ(iexp)*Dsig

C     ------------------------------------------------------------------------

!--- errors2 for chi2

         errsigZ2=0d0
         errsigZ20=0d0
         if ((iexp.eq.7).or.(iexp.eq.8)) then
c           stat errors already accounted for in *Run_I published data
            errsigZ2=errstatZ**2+errlumZ**2
            errsigZ20=errstatZ**2+errlumZ0**2
         else if (iexp.eq.9) then
            errsigZ2=errstatZ**2+errsystZ**2+errlumZ**2
            errsigZ20=errstatZ**2+errsystZ**2+errlumZ0**2
         else
            errsigZ2=errstatZ**2+errsystZ**2
            errsigZ20=errstatZ**2+errsystZ**2
         end if

         if (iexp.eq.10) then ! error propagation for D0_RunII
            t1=dsigdptDIVsig
            t10=dsigdptDIVsig0
            t2=sigZ(iexp)
            errt1=dsqrt(errsigZ2)
            errt2=errsigZ(iexp)
            errsigZ2=(t1**2)*(errt2**2)+(t2**2)*(errt1**2)
            errsigZ20=(t10**2)*(errt2**2)+(t2**2)*(errt1**2)
         end if

!--- Calculate bin normalization

      if (normONOFF) then

      call create_bin_elem_array(ib,Dsig_th,dsigdpt,errsigZ2,elembin)
      call create_bin_elem_array(ib0,Dsig_th,dsigdpt_0,
     &                           errsigZ20,elembin0)

      if (ibin.ne.int(datamatZ(7,i+1))) then

          call normbin(ib,elembin,norm)
C          call normbin(ib0,elembin0,norm0)
          norm0=norm !use same normaliz for original and repl data

          if (iflag.eq.3) write(25,'(i3,2x,i3,5x,f7.4)') ibin,iexp,norm

          call calc_chi2_bin(ib,norm,elembin,resbin)
          chi2ZB=chi2ZB+resbin
          chi2parDYZ(iexp)=chi2parDYZ(iexp)+resbin

          call calc_chi2_bin(ib0,norm0,elembin0,resbin0)
          chi2ZB_0=chi2ZB_0+resbin0
          chi2parDYZ_0(iexp)=chi2parDYZ_0(iexp)+resbin0

          ib=0;ib0=0
       end if
      end if

c-------------------------------------------------------------
c calculation of chi2: putting all together
c-------------------------------------------------------------

      if (.NOT. normONOFF) then
         res=((dsigdpt-Dsig_th)**2)/errsigZ2
         chi2ZB=chi2ZB+res
         chi2parDYZ(iexp)=chi2parDYZ(iexp)+res

         res0=(dsigdpt_0-Dsig_th)**2/errsigZ20
         chi2ZB_0=chi2ZB_0+res0
         chi2parDYZ_0(iexp)=chi2parDYZ_0(iexp)+res0

      end if

         diffDsig=dsigdpt-Dsig_th
         if(iflag.eq.3) then
            write(8,400) iexp,pT,!dsqrt(tau)*dexp(-ymax),
     &       Dsig_th,
     &       dsigdpt,dsqrt(errsigZ2),
     &       ((dsigdpt-Dsig_th)**2)/errsigZ2
 400        FORMAT(1x,I3,7(1x,E13.6))
         end if

         if (normONOFF) then
           ndatparZin=ndatparZ-NtotbinZ
           ndatZin=ndatZ-SUM(NtotbinZ)
         else
           ndatparZin=ndatparZ
           ndatZin=ndatZ
         end if


      end do ZLOOP! end of ndatZ loop

      endif

      chi2=chi2SD+chi2DY+chi2ZB
      chi20=chi2SD_0+chi2DY_0+chi2ZB_0

c-------------------------------------------------------------
c write out output at the end of minimization
c-------------------------------------------------------------
      if(iflag.eq.3) then

c        this subroutine gives the number of free parameters, inpari,
c        and total number of parameters including fixed ones, inparx
         call mnstat(fmin,fedm,errdef,inpari,inparx,istat)

c        write the values of the parameters to unit 11 (parameters.out)
c        and unit 7 (parameters_save.out)
         write(7,*) (param(i),i=1,inparx)
         write(11,FMT='(20(1x,E13.6))') (param(i),i=1,inparx)

c        write the value of chi2/d.o.f., Kappa and L, to unit 6
         dof=dble(ndatSDin+ndatDYin+ndatZin- npar)

         write(6,*) 'chi2 = ',chi2
         write(6,*) 'd.o.f = ',ndatSDin+ndatDYin+ndatZin,
     &   ' bins - ',npar,
     +        ' params  = ',int(dof)
         write(6,*) 'chi2/d.o.f.                     = ',chi2/dof
         write(6,*) 'chi2/d.o.f. w.r.t. original data= ',
     &        chi20/dof
         write(6,*)
      SDWRITE: if (SDboole) then
         write(6,*) 'HERMES'
         iexp=1
         do itar=1,2
            do ihad=-2,2
               if (ihad.ne.0) then
                  write(6,*) trim(target(itar)), ' ',
     &                 trim(hadron(ihad+3))
                  write(6,*) 'chi2 = ', chi2parSD(iexp,itar,ihad)
                  write(6,*) 'ndats = ', ndatparSDin(iexp,itar,ihad)
                  write(6,*) 'chi2/d.o.f.                     = ',
     &                 chi2parSD(iexp,itar,ihad)/
     &                 dble(ndatparSDin(iexp,itar,ihad))
                  write(6,*) 'chi2/d.o.f. w.r.t. original data= ',
     &                 chi2parSD0(iexp,itar,ihad)/
     &                 dble(ndatparSDin(iexp,itar,ihad))
                  write(6,*)
               end if
            end do
          end do
         write(6,*)  'COMPASS'
         iexp=2
         do itar=2,2
            do ihad=-1,1
               if (ihad.ne.0) then
                  write(6,*) trim(target(itar)), ' ',
     &                 trim(hadron(ihad+3))
                  write(6,*) 'chi2 = ', chi2parSD(iexp,itar,ihad)
                  write(6,*) 'ndats = ', ndatparSDin(iexp,itar,ihad)
                  write(6,*) 'chi2/d.o.f. =                     ',
     &                 chi2parSD(iexp,itar,ihad)/
     &                 dble(ndatparSDin(iexp,itar,ihad))
                  write(6,*) 'chi2/d.o.f. w.r.t. original data= ',
     &                 chi2parSD0(iexp,itar,ihad)/
     &                 dble(ndatparSDin(iexp,itar,ihad))
                  write(6,*)
               end if
            end do
         end do

c        global, PK-,Pp-,Pp+,PK+, DK-,Dp-,Dp+,DK+
         write(11,FMT='(2(1x,E13.6))') chi2,chi2/dof
         do itar=1,2
            do ihad=-2,2
               if (ihad.ne.0) then
                  write(11,FMT='(2(1x,E13.6))') chi2parSD(1,itar,ihad),
     &                 chi2parSD(1,itar,ihad)/
     &                 dble(ndatparSDin(1,itar,ihad))
               end if
            end do
         end do

         write(11,FMT='(2(1x,E13.6))') chi2SD_0,chi2SD_0/dof
         do itar=1,2
            do ihad=-2,2
               if (ihad.ne.0) then
                  write(11,FMT='(2(1x,E13.6))') chi2parSD0(1,itar,ihad),
     &                 chi2parSD0(1,itar,ihad)/
     &                 dble(ndatparSDin(1,itar,ihad))
               end if
            end do
         end do
      else !SDboole
         write(6,*) 'SIDIS data were not included in this analysis'
         write(6,*)
      end if SDWRITE

      DYWRITE: if (DYboole) then
c        write  Drell-Yan results
         write(6,*) 'DRELL-YAN'
         write(6,*) 'chi2 =', chi2DY
         write(6,*) 'chi2 w.r.t. orig. data =', chi2DY_0
         write(6,*) '       E288_400     E288_300    E288_200    E605'
         write(6,*) 'ndats= ',ndatparDYin(3),ndatparDYin(4)
     &        ,ndatparDYin(5),ndatparDYin(6)
         write(6,*) 'chi2/d.o.f. =                     ',
     &        chi2parDYZ(3)/dble(ndatparDYin(3)),
     &        chi2parDYZ(4)/dble(ndatparDYin(4)),
     &        chi2parDYZ(5)/dble(ndatparDYin(5)),
     &        chi2parDYZ(6)/dble(ndatparDYin(6))
         write(6,*) 'chi2/d.o.f. w.r.t. original data= ',
     &        chi2parDYZ_0(3)/dble(ndatparDYin(3)),
     &        chi2parDYZ_0(4)/dble(ndatparDYin(4)),
     &        chi2parDYZ_0(5)/dble(ndatparDYin(5)),
     &        chi2parDYZ_0(6)/dble(ndatparDYin(6))
         write(6,*)
      else
        write(6,*) 'DY data were not included in this analysis'
        write(6,*)
      end if DYWRITE

      ZWRITE: if (Zboole) then
         write(6,*) 'Z BOSON PROD.'
         write(6,*) 'chi2 =', chi2ZB
         write(6,*) 'chi2 w.r.t. orig. data =', chi2ZB_0
        if ( ANY( expBoole(7:10).eqv..true. ) ) then
         write(6,*) '       CDF_1     D0_1    CDF_2    D0_2'
         write(6,*) 'ndats= ',ndatparZin(7),ndatparZin(8)
     &        ,ndatparZin(9),ndatparZin(10)
         write(6,*) 'chi2/d.o.f. =                     ',
     &        chi2parDYZ(7)/dble(ndatparZin(7)),
     &        chi2parDYZ(8)/dble(ndatparZin(8)),
     &        chi2parDYZ(9)/dble(ndatparZin(9)),
     &        chi2parDYZ(10)/dble(ndatparZin(10))
         write(6,*) 'chi2/d.o.f. w.r.t. original data= ',
     &        chi2parDYZ_0(7)/dble(ndatparZin(7)),
     &        chi2parDYZ_0(8)/dble(ndatparZin(8)),
     &        chi2parDYZ_0(9)/dble(ndatparZin(9)),
     &        chi2parDYZ_0(10)/dble(ndatparZin(10))
         write(6,*)
        end if
        if ( ANY( expBoole(11:size(experiment)).eqv..true. ) ) then
         write(6,*) 'ATLAS7(3 bins) ATLAS8(6 bins)
     &  CMS7    CMS8   LHCb7   LHCb8   LHCb13  ATLAS7  ATLAS8'
         write(6,*) 'ndats= ',ndatparZin(11:size(experiment))
         write(6,*) 'chi2/d.o.f. =                   ',
     &        chi2parDYZ(11:size(experiment))/
     &        dble(ndatparZin(11:size(experiment)))
c$$$     &        chi2parDYZ(11)/dble(ndatparZin(11)),
c$$$     &        chi2parDYZ(12)/dble(ndatparZin(12)),
c$$$     &        chi2parDYZ(13)/dble(ndatparZin(13)),
c$$$     &        chi2parDYZ(14)/dble(ndatparZin(14)),
c$$$     &        chi2parDYZ(15)/dble(ndatparZin(15)),
c$$$     &        chi2parDYZ(16)/dble(ndatparZin(16))
         write(6,*) 'chi2/d.o.f. w.r.t. original data= ',
     &        chi2parDYZ_0(11:size(experiment))/
     &        dble(ndatparZin(11:size(experiment)))

         write(6,*)
        end if
       else
         write(6,*) 'Z data were not included in this analysis'
         write(6,*)
       end if ZWRITE

c        write the covariance matrix to unit 10 (covmat.out)
         call mnemat(covmat,100)
         do i=1,npar
            write(10,FMT='(100(E11.4,1x))')  (covmat(i,j),j=1,npar)
         end do

!--- write the chi2 value to unit 12 (chi2.out)

         write(12,*) 'chi2'
         write(12,*)  chi2
         write(12,*) 'chi2/dof'
         write(12,*)  chi2/dof
         write(12,*) '----'
         write(12,*) 'chi2orig'
         write(12,*)  chi20
         write(12,*) 'chi2orig/dof'
         write(12,*)  chi20/dof

      end if

      return
      end
