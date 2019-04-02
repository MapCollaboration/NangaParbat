
      subroutine gridmaker
      use com,only: bmax,gE,ndatDY,ndatSD,fini,mu_b,
     &              target,hadron,experiment,name,
     &              sqrt_enS,enS,y,rapmin,rapmax,
     &              evchoose,npchoose,ord,bpresc,izx,Znorm,iflavindep,
     &              firstbin, errfrag,SDboole, DYboole, Zboole

      implicit none

      double precision bTstar,bT,bmin,mu,mu_b2,
     &     mub_Z(200),mub_FF(2000,200),
     &     q_SD(200),mub_SD(2000,200),revo_SD(200,200),
     &     mub_dy(200,200),revo_dy(200,200),alphaspdf
      double precision u,ub,d,db,s,sb,c,b,gl,zd1(-6:6)
      double precision Xleft,Xright,Xgauss(8),Wgauss(8),xg(8)
      double precision m,m2,tau,Qf,q2,xm,xr,dx
      double precision ymax,ymin !yE605(4)
      double precision cf_z(200,200,-6:6),cpdf(-6:6),cf_SD(200,200,-6:6)
      double precision xpdf(-6:6),Revo
      double precision xA,xB,x,z,xF,xtemp,x_z(2000),
     &     xa_dy(200),xtempSD(10000),xSD(200),Qtemp(10000),
     &     ztemp(10000),zSD(10000)
      double precision datamatDY0(6,2500),datamat0(11,25000)
      integer f,i,j,k,l,lz,nmu,nx,nmudy,nxdy,nmuSD,nxSD,nzSD
      integer ihad,ihadSD(10000),ihadtemp(10000),ifinihad,iexp,N!,finilz(10000)

c      common/integGridZ/x_z,mub_z,cf_z,nx,nmu

            DATA Xg
     1   / 0.9894009349916499325961541735D0,
     2     0.9445750230732325760779884155D0,
     3     0.8656312023878317438804678977D0,
     4     0.7554044083550030338951011948D0,
     5     0.6178762444026437484466717640D0,
     6     0.4580167776572273863424194430D0,
     7     0.2816035507792589132304605015D0,
     8     0.0950125098376374401853193354D0 /







c-------------------------------------------------------------
c lhapdf
c-------------------------------------------------------------
      N=0
      call SetPDFPath('/usr/local/share/LHAPDF/PDFsets')
      call InitPDFsetByName(name)
      call InitPDF(N)


  



c!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!     Here I create a (x,mu) grid for PDFs and kernel in Z production
      
c!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      if (Zboole) then
         open(unit=100,file='grid_Z')
      m = 91.1876d0

      i=0

      do j=1,15
         Xleft= (float(j)-1d0)*10d0/15d0
         Xright= (float(j))*10d0/15d0

         call DGSET(Xleft,Xright,6,Xgauss,Wgauss)

         do k=1,6

            i=i+1

            bT=Xgauss(k)
            bTstar=0d0
c     choose bstar prescription
            if (bpresc.eq.1) then
               bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
            elseif (bpresc.eq.2) then
               bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
            elseif (bpresc.eq.3) then
               bmin = bmax * 1d0/m
               bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &              (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
            endif

            mub_z(i) = 2d0*dexp(-gE)/bTstar
            nmu=i

         end do
      end do

     
      i=0                     
      
      do l=7,10 ! for CDF, D0     
         if(enS(l-1).ne.enS(l)) then
            tau=(m**2)/enS(l)

            ymax= -0.5d0*dlog(tau)

         do j=1,5

            Xleft= -ymax + (float(j)-1)*2d0*ymax/5d0
            Xright= -ymax + (float(j))*2d0*ymax/5d0

            call DGSET(Xleft,Xright,6,Xgauss,Wgauss)

                 do k=1,6

                    i=i+1

                    x_z(i) = dsqrt(tau)*dexp(Xgauss(k))
                    nx=i

                 end do
         end do
          end if
       end do  ! end of the do for CDF, D0 


      do l=11,21 ! ATLAS_7Tev, ATLAS_8TeV, CMS_7TeV, CMS_8TeV

           tau=(m**2)/enS(l)

          ymin=rapmin(l-10)
          ymax=rapmax(l-10)

         do j=1,5

            Xleft= ymin + (float(j)-1)*(ymax-ymin)/5d0
            Xright= ymin + (float(j))*(ymax-ymin)/5d0

            call DGSET(Xleft,Xright,6,Xgauss,Wgauss)

            do k=1,6

               i=i+1

               x_z(i) = dsqrt(tau)*dexp(Xgauss(k))

               i=i+1
               x_z(i) = dsqrt(tau)*dexp(-Xgauss(k))
               nx=i

            end do
         end do

         
      end do ! end of the do for ATLAS_7Tev, ATLAS_8TeV, CMS_7TeV, CMS_8TeV
         
      do l=22,24 ! LHCb_7TeV, LHCb_8TeV, LHCb_13TeV

           tau=(m**2)/enS(l)

          ymin=rapmin(l-10)
          ymax=rapmax(l-10)

         do j=1,5

            Xleft= ymin + (float(j)-1)*(ymax-ymin)/5d0
            Xright= ymin + (float(j))*(ymax-ymin)/5d0

            call DGSET(Xleft,Xright,6,Xgauss,Wgauss)

            do k=1,6

               i=i+1

               x_z(i) = dsqrt(tau)*dexp(Xgauss(k))

               
               i=i+1
               x_z(i) = dsqrt(tau)*dexp(-Xgauss(k))
               
               nx=i

            end do
         end do

         
      end do !end do for LHCb_7TeV, LHCb_8TeV, LHCb_13TeV

      do l=25,26 ! ATLAS_7Tev, ATLAS_8TeV

           tau=(m**2)/enS(l)

          ymin=rapmin(l-10)
          ymax=rapmax(l-10)

         do j=1,5

            Xleft= ymin + (float(j)-1)*(ymax-ymin)/5d0
            Xright= ymin + (float(j))*(ymax-ymin)/5d0

            call DGSET(Xleft,Xright,6,Xgauss,Wgauss)

            do k=1,6

               i=i+1

               x_z(i) = dsqrt(tau)*dexp(Xgauss(k))

               i=i+1
               x_z(i) = dsqrt(tau)*dexp(-Xgauss(k))
               nx=i

            end do
         end do

         
      end do ! end of the do for ATLAS_7Tev, ATLAS_8TeV

      
      write(100,*) nmu,nx
C -----------------------------------------------------------
      do j=1,nmu
         mu_b=mub_Z(j)
c     choose evolution kernel
         if (evchoose.eq.2) then
         call kernel_css(m,Revo)
      elseif (evchoose.eq.6) then
         call kernel_css_num(m,Revo)
      endif

         do i=1,nx

            call evolvePDF(x_z(i),mub_z(j),xpdf)

            call WCPDF(x_z(i),mub_z(j),cpdf)
                    write(100,*) mub_z(j),x_z(i),cpdf,xpdf,Revo

c                  do f=-6,6
c                     cf_z(i,j,f)=cpdf(f)
c                  end do
         end do
      end do
      close(100)
      end if


C-------------------------------------------------------------
C$$$     Here I create a (x,mu) grid for PDFs and kernel in DY
C-------------------------------------------------------------
      if (DYboole) then
         call readdataDY(0,datamatDY0,0,0)
         open(unit=101,file='grid_DY')
      xtemp=0d0
      l=1
      do i=1,ndatDY             !loop on bins of DY data
c     assign variables read from txt files
         iexp = int(datamatDY0(1,i))
         m = datamatDY0(2,i)
         m2 = m**2
         tau=m2/enS(iexp)
         xA = dsqrt(tau)*dexp(y(iexp))
         xB = dsqrt(tau)*dexp(-y(iexp))
         if (iexp.eq.6) then
            xF = 0.1d0
            xA = (sqrt_enS(iexp)*xF
     &           + dsqrt(4d0*m2 + enS(iexp)*xF**2))/(2d0*sqrt_enS(iexp))
            xB = xA - xF
         end if
         if(xB.ne.xtemp) then
            xa_dy(l)=xA
            n=0

            do j=1,10

               Xleft= (j-1)*20d0/10d0
               Xright= (j)*20d0/10d0
               xm=0.5d0*(xright+xleft)
               xr=0.5d0*(xright-xleft)

               do k=1,8

                  dx=xr*xg(k)

                  bT=xm+dx
                  n=n+1

                  bTstar=0d0
c     choose bstar prescription
                  if (bpresc.eq.1) then
                     bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
                  elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
                  elseif (bpresc.eq.3) then
                     bmin = bmax * 1d0/m
                     bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                    (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
                  endif
                  mub_dy(l,n) = 2d0*dexp(-gE)/bTstar

                  mu_b=mub_dy(l,n)
c     choose evolution kernel
                  if (evchoose.eq.2) then
                     call kernel_css(m,Revo_DY(l,n))
                  elseif (evchoose.eq.6) then
                     call kernel_css_num(m,Revo_DY(l,n))
                  endif

                  bT=xm-dx
                  n=n+1

                  bTstar=0d0
c     choose bstar prescription
                  if (bpresc.eq.1) then
                     bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
                  elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
                  elseif (bpresc.eq.3) then
                     bmin = bmax * 1d0/m
                     bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                    (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
                  endif
                  mub_dy(l,n) = 2d0*dexp(-gE)/bTstar

                  mu_b=mub_dy(l,n)
c     choose evolution kernel
                  if (evchoose.eq.2) then
                     call kernel_css(m,Revo_DY(l,n))
                  elseif (evchoose.eq.6) then
                     call kernel_css_num(m,Revo_DY(l,n))
                  endif

                  nmudy=n
               end do
            end do


            nxDY=l

            l=l+1
         end if
         xtemp=xB
      end do

      xtemp=0d0
      do i=1,ndatDY             !loop on bins of DY data
c     assign variables read from txt files
         iexp = int(datamatDY0(1,i))
         m = datamatDY0(2,i)
         m2 = m**2
         tau=m2/enS(iexp)
         xA = dsqrt(tau)*dexp(y(iexp))
         xB = dsqrt(tau)*dexp(-y(iexp))
         if (iexp.eq.6) then
            xF = 0.1d0
            xA = (sqrt_enS(iexp)*xF
     &           + dsqrt(4d0*m2 + enS(iexp)*xF**2))/(2d0*sqrt_enS(iexp))
            xB = xA - xF
         end if
         if(xB.ne.xtemp) then
            xa_dy(l)=xB
            n=0

            do j=1,10

               Xleft= (j-1)*20d0/10d0
               Xright= (j)*20d0/10d0
               xm=0.5d0*(xright+xleft)
               xr=0.5d0*(xright-xleft)

               do k=1,8

                  dx=xr*xg(k)

                  bT=xm+dx
                  n=n+1

                  bTstar=0d0
c     choose bstar prescription
                  if (bpresc.eq.1) then
                     bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
                  elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
                  elseif (bpresc.eq.3) then
                     bmin = bmax * 1d0/m
                     bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                    (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
                  endif
                  mub_dy(l,n) = 2d0*dexp(-gE)/bTstar

                  mu_b=mub_dy(l,n)
c     choose evolution kernel
                  if (evchoose.eq.2) then
                     call kernel_css(m,Revo_DY(l,n))
                  elseif (evchoose.eq.6) then
                     call kernel_css_num(m,Revo_DY(l,n))
                  endif

                  bT=xm-dx
                  n=n+1

                  bTstar=0d0

c     choose bstar prescription
                  if (bpresc.eq.1) then
                     bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
                  elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
                  elseif (bpresc.eq.3) then
                     bmin = bmax * 1d0/m
                     bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                    (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
                  endif
                  mub_dy(l,n) = 2d0*dexp(-gE)/bTstar

                  mu_b=mub_dy(l,n)
c     choose evolution kernel
                  if (evchoose.eq.2) then
                     call kernel_css(m,Revo_DY(l,n))
                  elseif (evchoose.eq.6) then
                     call kernel_css_num(m,Revo_DY(l,n))
                  endif

                  nmudy=n
               end do
            end do


            nxDY=l

            l=l+1
         end if
         xtemp=xB
      end do
      write(101,*) nxDY,nmuDY


      do n=1,nmuDY
      do l=1,nxDY


            call evolvePDF(xa_DY(l),mub_dy(l,n),xpdf)
            call WCPDF(xa_DY(l),mub_dy(l,n),cpdf)
            write(101,*) xa_DY(l),mub_dy(l,n),cpdf,xpdf,revo_dy(l,n)


         end do
      end do

      close(101)
      end if



C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
C$$$  Here I create a (x,mu) grid for PDFs and kernel in SIDIS
C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      if (SDboole) then
         call readdata(0,datamat0,0,0)
         open(unit=102,file='grid_SD')
      l=1
      do i=1,ndatSD             !loop on bins of SIDIS
c     assign variables read from txt files
         xtempSD(i) = datamat0(8,i)
         ihad=int(datamat0(3,i))
         x = datamat0(8,i)
         z = datamat0(9,i)
         q2 = datamat0(7,i)
         Qf=dsqrt(q2)
         Qtemp(i)=Qf

         do j=1,i-1
            if((x.eq.xtempSD(j)).and.(Qf.eq.Qtemp(j))) then
               go to 102
            end if
         end do
         xSD(l)=x
         q_SD(l)=Qf
         n=0

         do j=1,6

            Xleft= (j-1)*20d0/6d0
            Xright= (j)*20d0/6d0
            xm=0.5d0*(xright+xleft)
            xr=0.5d0*(xright-xleft)

            do k=1,8

               dx=xr*xg(k)

               bT=xm+dx
               n=n+1
               bTstar=0d0
c     choose bstar prescription
               if (bpresc.eq.1) then
                  bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
               elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
               elseif (bpresc.eq.3) then
                  bmin = bmax * 1d0/Qf
                  bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                 (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
               endif
               mub_SD(l,n) = 2d0*dexp(-gE)/bTstar

               mu_b=mub_SD(l,n)
c     choose evolution kernel
               if (evchoose.eq.2) then
                  call kernel_css(Qf,Revo_SD(l,n))
               elseif (evchoose.eq.6) then
                  call kernel_css_num(Qf,Revo_SD(l,n))
               endif

               bT=xm-dx
               n=n+1
               bTstar=0d0
c     choose bstar prescription
               if (bpresc.eq.1) then
                  bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
               elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
               elseif (bpresc.eq.3) then
                  bmin = bmax * 1d0/Qf
                  bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                 (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
               endif
               mub_SD(l,n) = 2d0*dexp(-gE)/bTstar
               mu_b=mub_SD(l,n)
c     choose evolution kernel
               if (evchoose.eq.2) then
                  call kernel_css(Qf,Revo_SD(l,n))
               elseif (evchoose.eq.6) then
                  call kernel_css_num(Qf,Revo_SD(l,n))
               endif

               nmuSD=n
            end do
         end do

         nxSD=l

         l=l+1

 102  end do

      write(102,*) nxSD,nmuSD
      do l=1,nxSD
         do n=1,nmuSD
            call WCPDF(xSD(l),mub_SD(l,n),cpdf)
            call evolvePDF(xSD(l),mub_SD(l,n),xpdf)
            write(102,*) xSD(l),q_SD(l),mub_SD(l,n),
     &     cpdf,xpdf,Revo_SD(l,n)

         end do
      end do
      close(102)
 



C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
C      Here I create a (z,mu) grid for fragmentation in SIDIS
C!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
c$$$      do l=1,10000
c$$$         finilz(l) =1
c$$$      end do


      open(unit=103,file='grid_FF')
      lz=1
      do i=1,ndatSD             !loop on bins of SIDIS
c     assign variables read from txt files
         ihad=int(datamat0(3,i))
         ihadtemp(i)=ihad

         z = datamat0(9,i)
         ztemp(i)=z

         q2 = datamat0(7,i)
         Qf=dsqrt(q2)
         Qtemp(i)=Qf
         do j=1,i-1

            if((z.eq.ztemp(j)).and.(ihad.eq.ihadtemp(j))
     &           .and.(Qf.eq.Qtemp(j))) then
               go to 10
            end if
         end do
         zSD(lz)=z
         ihadSD(lz)=ihad

c         if(z.eq.0.22388430000000001d0) write(*,*) z
c$$$         if(ihad.ne.ihadtemp(i-1)) then
c$$$            finilz(lz)=0
c$$$         end if
         n=0

         do j=1,6

            Xleft= (j-1)*20d0/6d0
            Xright= (j)*20d0/6d0
            xm=0.5d0*(xright+xleft)
            xr=0.5d0*(xright-xleft)

            do k=1,8

               dx=xr*xg(k)

               bT=xm+dx
               n=n+1
               bTstar=0d0
c     choose bstar prescription
               if (bpresc.eq.1) then
                  bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
               elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
               elseif (bpresc.eq.3) then
                  bmin = bmax * 1d0/Qf
                  bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                 (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
               endif
               mub_FF(lz,n) = 2d0*dexp(-gE)/bTstar
               bT=xm-dx
               n=n+1
               bTstar=0d0
c     choose bstar prescription
               if (bpresc.eq.1) then
                  bTstar = bT/dsqrt(1+(bT*bT/bmax/bmax))
               elseif (bpresc.eq.2) then
                  bTstar = bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)
               elseif (bpresc.eq.3) then
                  bmin = bmax * 1d0/Qf
                  bTstar=bmax*(1d0-dexp(-(bT/bmax)**4d0))**(1d0/4d0)/
     &                 (1d0-dexp(-(bT/bmin)**4d0))**(1d0/4d0)
               endif
               mub_FF(lz,n) = 2d0*dexp(-gE)/bTstar

               nmuSD=n
            end do
         end do

         nzSD=lz
         lz=lz+1
 10   end do

      write(103,*) nzSD,nmuSD
      fini = 0
      do l=1,nzSD
c$$$  if(finilz(l).eq.0) then
c$$$  fini = 0
c$$$  end if
         do n=1,nmuSD

            call WCFF(ihadSD(l),zSD(l),mub_FF(l,n),cpdf)

            mu_b2=mub_FF(l,n)**2d0

            select case(ihadSD(l))

            case (-1,0,1)          !PIONS
               if (ifinihad.ne.ihadSD(l)) fini=0
c     call fDSS(1,1,1,z,mu_b2,u,ub,d,db,s,sb,c,b,gl)
               call fDSSH(0,1,ihadSD(l),1,zSD(l),
     &              mu_b2,u,ub,d,db,s,sb,c,b,gl)
            case (-2,2)         !KAONS
               if (ifinihad.ne.ihadSD(l)) fini=0
               call fDSSH17(0,1,sign(1,ihadSD(l)),1,zSD(l),
     &              mu_b2,u,ub,d,db,s,sb,c,b,gl)
            case default
               write(*,*) 'Hadron type undefined! Stop!'
               stop
            end select

            zd1=(/ 0.d0,b,c,sb,ub,db,gl,d,u,s,c,b,0.d0 /)

            ifinihad=ihadSD(l)

            write(103,*) ihadSD(l),zSD(l),mub_FF(l,n),cpdf,zd1
         end do
      end do
      close(103)
      end if

 
 349  return
      end





!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!     Here I read the grids
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


      subroutine PreCalc_Z(x,mub,xpdf,cpdf,revo)
      use com, only: iexp
      implicit none
      double precision x,mub,cfA_dy(200,200,-6:6),
     &     cfB_dy(200,200,-6:6),cpdf(-6:6),xpdf(-6:6),revo

      double precision mub_z(200),x_z(2000),cf_z(2000,200,-6:6),
     &     xpdf_z(2000,200,-6:6),revo_z(200),
     &     mub_dy(200,200),xa_dy(200),xb_dy(200)

      integer nx,nmu,nxDY,nmuDY,f,i,j,k,l,ix,imu,itemp


      common/integGridZ/x_z,mub_z,cf_z,xpdf_z,revo_z,nx,nmu


      do i=1,nx
         if(real(x).eq.real(x_z(i))) then
            ix=i

            go to 10
         end if
      end do

      write(*,*) iexp,'PreCalc_Z: ERROR: wrong integration grid for x'
      do k=-6,6
         xpdf(k)=-1d30
      end do
      STOP
 

 10   do i=1,nmu
         if(real(mub).eq.real(mub_z(i))) then
            imu=i
            go to 11
         end if

      end do

      write(*,*) 'PreCalc_Z: ERROR: wrong integration grid for mu'
      do k=-6,6
         xpdf(k)=-1d30
      end do
      STOP

 11   do k=-6,6
         xpdf(k)=xpdf_z(ix,imu,k)
         cpdf(k)=cf_z(ix,imu,k)
      end do
      revo=revo_z(imu)



      return
      end

      subroutine PreCalc_DY(x,mub,xpdf,cpdf,revo)
      double precision x,mub,
     &     xpdf(-6:6),cpdf(-6:6),revo

      double precision  mub_dy(200,200),xa_dy(200),cfA_dy(200,200,-6:6),
     &                 xfA_dy(200,200,-6:6),revo_DY(200,200)

      integer nxDY,nmuDY,i,k,ix,imu,itemp

      common/integGridDY/xa_dy,mub_dy,
     &     cfA_dy,xfA_dy,revo_dy,nxDY,nmuDY


      itemp=0
      do i=1,nxdy
         if(x.eq.xa_dy(i)) then
            ix=i
            itemp=1
         end if
      end do

      if(itemp.ne.1) then
         write(*,*) 'PreCalc_DY: ERROR: wrong integration grid for x'
         do k=-6,6
            xpdf(k)=-1d30
         end do
         go to 101
      end if

      itemp=0
      do i=1,nmuDY
         if(mub.eq.mub_dy(ix,i)) then
            imu=i
            itemp=1
         end if
      end do

      if(itemp.ne.1) then
         write(*,*) 'PreCalc_DY: ERROR: wrong integration grid for mu'
         do k=-6,6
            xpdf(k)=-1d30
         end do
         STOP
      end if

      revo=revo_dy(ix,imu)
      do k=-6,6
         xpdf(k)=xfa_dy(ix,imu,k)

         cpdf(k)=cfa_dy(ix,imu,k)
      end do

 101    return
      end

      subroutine PreCalc_SD(x,mub,Qf,cpdf,xpdf,revo)

      double precision x,mub,cpdf(-6:6),xpdf(-6:6),revo,Qf,
     &     q_SD(200),mub_SD(200,200),x_SD(200),cf_SD(200,200,-6:6),
     &     xf_SD(200,200,-6:6),revo_SD(200,200)
      integer nx,nmu,nxSD,nmuSD,f,i,j,k,l,ix,imu,itemp

      common/integGridSD/x_SD,q_SD,mub_SD,cf_SD,xf_SD,revo_SD,nxSD,nmuSD

      do i=1,nxSD
         if(x.eq.x_SD(i).and.Qf.eq.q_SD(i)) then
            ix=i
            do j=1,nmuSD
               if(mub.eq.mub_SD(ix,j)) then
                  imu=j
                  go to 103
               end if
            end do

         end if
      end do

      write(*,*) 'PreCalc_SD: ERROR: wrong integration grid for x,mu'
      write(*,*) 'x =',x,', mu=',mub,' does not exist'
      do k=-6,6
         cpdf(k)=-1d30
         xpdf(k)=-1d30
      end do
      STOP

 103  do k=-6,6
         cpdf(k)=cf_SD(ix,imu,k)
         xpdf(k)=xf_SD(ix,imu,k)
      end do
      revo=revo_SD(ix,imu)
 102  return
      end

      subroutine PreCalc_FF(ihad,z,mub,cpdf,zd1)
      use com,only: Qf
      double precision z,mub,cpdf(-6:6),zd1(-6:6),cFF(2000,200,-6:6),
     &     zFF(2000,200,-6:6),z_SD(2000),mub_FF(2000,200)

      integer nx,nmu,nzSD,nmuFF,f,i,j,k,l,ix,imu,
     &     itemp,ihad,ihad_SD(2000)

      common/integGridFF/z_SD,mub_FF,cFF,zFF,nzSD,nmuFF,ihad_SD

      do i=1,nzSD
         if(ihad.eq.ihad_SD(i)) then

               if(z.eq.z_SD(i)) then
                  ix=i
                  do j=1,nmuFF
                     if(mub.eq.mub_FF(ix,j)) then
                        imu=j
                        go to 103
                     end if
                  end do
               end if

         end if
      end do

      write(*,*) 'PreCalc_FF: ERROR: wrong integration grid for z,mu'
      write(*,*) 'z =',z,', mu=',mub,' does not exist'
      do k=-6,6
         cpdf(k)=-1d30
         zd1(k)=-1d30
      end do
      STOP

 103  do k=-6,6
         cpdf(k)=cFF(ix,imu,k)
         zd1(k)=zFF(ix,imu,k)
      end do

 102  return
      end



      subroutine gridreader
      use com, only: SDboole, Zboole, DYboole
      implicit none
      double precision mub_z(200),x_z(2000),cf_z(2000,200,-6:6),
     &     xpdf_z(2000,200,-6:6),revo_z(200),
     &     mub_dy(200,200),xa_dy(200),cfA_dy(200,200,-6:6),
     &     xfA_dy(200,200,-6:6),revo_DY(200,200),
     &    q_SD(200),mub_SD(200,200),x_SD(200),cf_SD(200,200,-6:6),
     &     xf_SD(200,200,-6:6),revo_SD(200,200),
     &     z_SD(2000),mub_FF(2000,200),
     &     cff(2000,200,-6:6),zff(2000,200,-6:6)
      integer i,j,l,n,nmu,nx,nxDY,nmuDY,nxSD,
     &     nmuSD,nzSD,nmuFF,ihad_SD(2000)

      common/integGridZ/x_z,mub_z,cf_z,xpdf_z,revo_z,nx,nmu
      common/integGridDY/xa_dy,mub_dy,
     &     cfA_dy,xfA_DY,revo_DY,nxDY,nmuDY

      common/integGridSD/x_SD,q_SD,mub_SD,cf_SD,xf_SD,revo_SD,nxSD,nmuSD
      common/integGridFF/z_SD,mub_FF,cFF,zFF,nzSD,nmuFF,ihad_SD

       if (Zboole) then

      open(unit=100,file='grid_Z',status='old')
      read(100,*) nmu,nx
      do j=1,nmu
         do i=1,nx
            read(100,*) mub_z(j),x_z(i),cf_z(i,j,:),
     &       xpdf_z(i,j,:),revo_z(j)
         end do
      end do

      close(100)
      end if
      
      if (DYboole) then
      open(unit=101,file='grid_DY',status='old')
      read(101,*) nxDY,nmuDY
      do n=1,nmuDY
         do l=1,nxDY
            read(101,*) xa_DY(l),mub_dy(l,n),cfA_dy(l,n,:),
     &       xfa_DY(l,n,:),revo_DY(l,n)
         end do
      end do


      close(101)
      end if

      if (SDboole) then
      open(unit=102,file='grid_SD',status='old')
      read(102,*) nxSD,nmuSD
      do l=1,nxSD
         do n=1,nmuSD
            read(102,*) x_SD(l),q_SD(l),mub_SD(l,n),cf_SD(l,n,:),
     &       xf_SD(l,n,:),revo_SD(l,n)
         end do
      end do

      close(102)

      open(unit=103,file='grid_FF',status='old')
      read(103,*) nzSD,nmuFF
      do l=1,nzSD
         do n=1,nmuFF
            read(103,*) ihad_SD(l),z_SD(l),mub_FF(l,n),
     &           cff(l,n,:),zff(l,n,:)
         end do
      end do

      close(103)

      endif

      return
      end
