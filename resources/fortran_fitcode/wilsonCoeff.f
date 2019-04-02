c-----Wilson coefficient*PDF                                           
      subroutine WCPDF(x,mub,cpdf)
      use com, only: ascorr
      implicit none
      integer i,f,ngauss
      double precision cpdf(-6:6),pi
      double precision x,xb,mub,mu,qgauss,intWC
      double precision alphasPDF
      external alphasPDF
      common /xes/ xb,mu,i
      external intWC
      data Pi/3.141592654d0/

      do f = -6,6
         i = f
         xb = x
         mu = mub
         ngauss=20
         cpdf(f)=ascorr*alphasPDF(mub)*qgauss(intWC,x,1.d0,ngauss)/pi
      end do
      return
      end


c-----integrand for WC * PDF                                                                                         
      double precision function intWC(k)
c      use com,only: N,name 
      implicit none
      double precision xb,mu,k,xpdf(-6:6)
      integer i
      common /xes/ xb,mu,i

      call evolvePDF(k,mu,xpdf)

      if(i.eq.0) then
         intWC=0d0
      else
         if(xpdf(i).eq.0d0) then
            intWC=0d0
         else
            intWC=xpdf(i)/k**2*(1-xb/k)*2d0/3d0
     &           +xpdf(0)/k**3*(1-xb/k)*xb/2d0
         end if
      end if
      return
      end


c-----Wilson coefficient * FF                                                                  


      subroutine WCFF(h,z,mub,cpdf)
      use com, only: ascorr
      implicit none
      integer i,f,h,ih
      double precision upv,pdf(-6:6),cpdf(-6:6),pi
      double precision z,zb,b,bT,mub,mu,qgauss,intWCFF
      double precision fr2,mur,asmur,mc,mb,mt,alphas,alphasPDF
      integer ngauss,iord
      common /zs/ zb,mu,i,ih
      external intWCFF
      data Pi/3.141592654d0/

      do f = -6,6
         i = f
         ih = h
         zb = z
         mu = mub
         ngauss=20
         cpdf(f)=ascorr*alphasPDF(mub)*qgauss(intWCFF,z,1d0,ngauss)/pi
      end do
      return
      end

c-----integrand for WC * FF                                                                                                          
      double precision function intWCFF(k)
      use com,only: fini
      implicit none
      double precision z,zb,bT,mu,mu_b2,k,bessel0,diquarkTMD,Pi
      double precision u,ub,d,db,s,sb,c,b,gl,zd1(-6:6),Cqq,Cgq
      integer i,ih
      common /zs/ zb,mu,i,ih
      mu_b2=mu*mu
      select case(ih)

          case (1)
*           call fDSS(1,1,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)                                                                                          
            call fDSSH(0,1,1,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)

          case (0)
*           call fDSS(1,0,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)                                                                                          
            call fDSSH(0,1,0,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)

          case (-1)
*           call fDSS(1,-1,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)                                                                                         
            call fDSSH(0,1,-1,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)

          case (2)
            call fDSSH17(0,1,1,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)

          case (-2) 
            call fDSSH17(0,1,-1,1,k,mu_b2,u,ub,d,db,s,sb,c,b,gl)

          case default
            write(*,*) 'Hadron type undefined! Stop!'
            stop

        end select

        zd1(-6)=0.d0
        zd1(-5)=b
        zd1(-4)=c
        zd1(-3)=sb
        zd1(-2)=ub
        zd1(-1)=db
        zd1(0)=gl
        zd1(1)=d
        zd1(2)=u
        zd1(3)=s
        zd1(4)=c
        zd1(5)=b
        zd1(6)=0.d0

        z=zb/k

        Cqq=(2d0/3d0)/z**2*(1-z+2*dlog(z)*(1+z**2)/(1-z))
        Cgq=(2d0/3d0)/z**2*(z+2*dlog(z)*(1+(1-z)**2)/z)
      
      if(i.eq.0) then
         intWCFF=0d0
      else
         if(zd1(i).eq.0d0) then
            intWCFF=0d0
         else
            intWCFF=1d0/k**3*(Cqq*zd1(i)/k+Cgq*zd1(0)/k)
         end if
      end if
      return
      end
