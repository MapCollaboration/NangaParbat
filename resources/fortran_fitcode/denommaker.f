      program denommaker

      use com,only: ndatSD,name,
     &              enS,
     &              ord,charge2,datamat

      implicit none

      double precision q2, x, z, Php, q, den
      double precision xf1(-6:6)
      integer i, j, k, N
      integer iexp, ihad, ibin, itar

c AB apfel: variables
      double precision F2apfel, FTapfel, FLapfel, denapfel
      character*2 proc
      double precision StructureFunctionxQ
      double precision yy

c vector to store values of denom
      double precision denom(25000)


      open(unit=123,file='denom_full.dat')
      open(unit=124,file='denom.dat')
      open(unit=23,file='selected_data_denom.out')

c AB apfel
c note: if pert ord is 2, the mass scheme has to be specified
c if pert ord is 0, the setmassscheme calls must be commented

         call SetPerturbativeOrder(ord)
c         call SetMassScheme("ZM-VFNS")
c         call SetMassScheme("FONLL-C")

         call InitializeAPFEL_DIS

         call SetPDFSet(name)
!         call SetPDFSet("GJR08FFnloE.LHgrid")
!         call SetPDFSet("NNPDF30_nnlo_as_0118.LHgrid")
         call SetProcessDIS("EM")
         call EnableTargetMassCorrections(.false.)

c there should be no difference between electron and muon for EM processes
         call SetProjectileDIS("electron")


c-------------------------------------------------------------
c lhapdf
c-------------------------------------------------------------
         call SetPDFPath('/usr/local/share/LHAPDF/PDFsets')
         call InitPDFsetByName(name)
         call InitPDF(N)



         write(123,'(a3,2(2x,a3),2(a7),6(3x,a7))')
     &              'bin','exp','tar','x','Q2','den','denapfel',
     &              'ratio', 'FT/x', 'FL/x'


c-------------------------------------------------------------
c reading data
c-------------------------------------------------------------

      call readdata(0,datamat,0,0)

c------------------------------------------------------------
c AB apfel: first a run is done for the proton
         call SetTargetDIS("proton")

c if the starting scale is set to a negative value, apfel uses the
c lhapdf evolution
         call CacheStructureFunctionsAPFEL(-1.d0)

      SDLOOP: do i=1,ndatSD

         iexp=int(datamat(1,i))
         itar=int(datamat(2,i))
         ihad=int(datamat(3,i))
         ibin=int(datamat(11,i))
         q2 = datamat(7,i)
         x = datamat(8,i)
         z = datamat(9,i)
         Php = datamat(10,i)

         Q=dsqrt(q2)

         den=0d0
         F2apfel=0d0
         FTapfel=0d0
         FLapfel=0d0
         denapfel=0d0

c AB: this part is run only for the proton target
         if (itar.eq.1) then

         call evolvePDF(x, dsqrt(q2), xf1)

!--- calculate denominator at LO in the old way for cross-check
         do j=-6,6

           k=j

            den=den + charge2(j)*xf1(k)/x

         end do ! end of j loop

c using Cached structure functions

      F2apfel=StructureFunctionxQ("EM","F2","total",x,dsqrt(Q2))

      yy=q2/(x*enS(iexp))

      FLapfel=StructureFunctionxQ("EM","FL","total",x,dsqrt(Q2))

      FTapfel=-FLapfel+!(1d0+(2d0*0.938d0*x)**2/q2)*
     &        F2apfel

      denapfel=FTapfel/x+(1d0-yy)/(1d0-yy+yy**2/2d0)*FLapfel/x

      denom(i)=denapfel

         write(123,'(i3,2(2x,i3),8(3x,f8.4))')
     &              ibin,iexp,itar,x,Q2,den,denom(i),
     &              den/denom(i), FTapfel/x, FLapfel/x

         write(124,'(i5,4(1x,i3),8(3x,f8.4))')
     &              i,ibin,iexp,itar,ihad, Q2,x,z,Php, den, denom(i)

         end if !end of itar if

      end do  SDLOOP                !end of ndatSD



c------------------------------------------------------------
c AB apfel: second run is done for the deuteron
         call SetTargetDIS("isoscalar")

c if the starting scale is set to a negative value, apfel uses the
c lhapdf evolution
         call CacheStructureFunctionsAPFEL(-1.d0)

c AB apfel: end

      SDLOOP2: do i=1,ndatSD

         iexp=int(datamat(1,i))
         itar=int(datamat(2,i))
         ihad=int(datamat(3,i))
         ibin=int(datamat(11,i))
         q2 = datamat(7,i)
         x = datamat(8,i)
         z = datamat(9,i)
         Php = datamat(10,i)

         Q=dsqrt(q2)

         den=0d0
         F2apfel=0d0
         FTapfel=0d0
         FLapfel=0d0
         denapfel=0d0

c AB: this part is run only for the deuteron target
         if (itar.eq.2) then

         call evolvePDF(x, dsqrt(q2), xf1)

!--- calculate denominator at LO in the old way for cross-check
         do j=-6,6

           k=j

            den=den + charge2(j)*xf1(k)/x

!--- add neutron
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

               den=den + charge2(j)*xf1(k)/x

         end do ! end of j loop


c AB: the deuteron is 2* the isoscalar target

      F2apfel=2*StructureFunctionxQ("EM","F2","total",x,dsqrt(Q2))

      yy=q2/(x*enS(iexp))

      FLapfel=2*StructureFunctionxQ("EM","FL","total",x,dsqrt(Q2))

      FTapfel=-FLapfel+!(1d0+(2d0*0.938d0*x)**2/q2)*
     &        F2apfel

      denapfel=FTapfel/x+(1d0-yy)/(1d0-yy+yy**2/2d0)*FLapfel/x


      denom(i)=denapfel

         write(123,'(i3,2(2x,i3),8(3x,f8.4))')
     &              ibin,iexp,itar,x,Q2,den,denom(i),
     &              den/denom(i), FTapfel/x, FLapfel/x

         write(124,'(i5,4(1x,i3),8(3x,f8.4))')
     &              i,ibin,iexp,itar,ihad, Q2,x,z,Php, den, denom(i)

         end if !end of itar if

      end do  SDLOOP2                !end of ndatSD


      close(123)
      close(124)
      close(23)

      stop
      end
