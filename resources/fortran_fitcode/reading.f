c-------------------------------------------------------------------------
c-------------------------------------------------------------------------
c     read SIDIS data
c-------------------------------------------------------------------------
c-------------------------------------------------------------------------
      subroutine readdata(irep,datamat,ipri,ir)
       use com, only: ndatSD, ndatparSD,totbin,
     &                target, hadron, experiment,
     &                itar, ihad, iexp,izx
       use bin
      implicit none

      integer :: i, j, k, totdat, idat, irep, ipri,ir,imaat
      double precision :: datamat(11,25000), datatemp(10,25000)
      character fname*82

      integer,dimension(1:2,1:2,-2:2) :: startdata,enddata



      i=0
      totdat=0
      idat=0
      ndatSD=0
      ntotbinSD=0


!      ir=mod(ir+1,2) !ir: 1 for replicated date, 0 for original

      do itar=1,2
         do ihad=-2,2
            do iexp=1,2
c-------------------------------------------------------------------------
c     building the filename 'fname'
c-------------------------------------------------------------------------
               if (irep.eq.0) then
                  if ((izx.eq.1).and.(iexp.eq.1).and.(ihad.ne.0)) then
c                     write(fname,'(a,a,a,a,a)')
c     &                    'data/hermes.',
c     &                    trim(target(itar)),
c     &                    '.zxpt-3D.zpt-proj.vmsub.mults_',
c     &                    trim(hadron(ihad+3)),
c     &                    '.list'
c                  the following two lines can be used to skip the deuteron K-
c                  else if ((ihad.eq.-2).and.(itar.eq.2)) then
c                     write(fname,'(a,a,a,a,a)') 'Skip'
                  else if ((iexp.eq.1).and.(ihad.ne.0)) then
                     write(fname,'(a,a,a,a,a)')
     &                    'data/hermes.'
     &                    ,trim(target(itar)),
     &                    '.zxpt-3D.vmsub.mults_',
     &                    trim(hadron(ihad+3)),
     &                    '.list'
                  else if ((iexp.eq.2).and.(itar.eq.2).and.
     &                    (abs(ihad).eq.1)) then
                     write(fname,'(a,a,a,a,a)')
     &                    'data/Compass17_',
     &                    trim(hadron(ihad+3)),
     &                    '.dat'
                  else
                     write(fname,'(a,a,a,a,a)') 'Skip'
                  end if
               else
                  if ((izx.eq.1).and.(iexp.eq.1).and.(ihad.ne.0)) then
c                     write(fname,'(a,a,a,a,a)')
c     &                    'data/hermes.',
c     &                    trim(target(itar)),
c     &                    '.zxpt-3D.zpt-proj.vmsub.mults_',
c     &                    trim(hadron(ihad+3)),
c     &                    '.list'
                  else if ((iexp.eq.1).and.(ihad.ne.0)) then
                     write(fname,'(a,a,a,a,a)')
     &                    'Rdata/Rhermes.',
     &                    trim(target(itar)),
     &                    '.zxpt-3D.vmsub.mults_',
     &                    trim(hadron(ihad+3)),
     &                    '.list'
                  else if ((iexp.eq.2).and.(itar.eq.2).and.
     &                    (abs(ihad).eq.1)) then
                     write(fname,'(a,a,a,a,a)')
     &                    'Rdata/RCompass17_',
     &                    trim(hadron(ihad+3)),
     &                    '.dat'
                  else
                     write(fname,'(a,a,a,a,a)') 'Skip'
                  end if
               end if

               if (irep.eq.0) then
                     imaat=23
               else if (irep.eq.1) then
                     imaat=24
               end if

c-------------------------------------------------------------------------
c     opening the file 'fname'
c-------------------------------------------------------------------------
      SKIPNAME: if (fname.ne.'Skip') then
                  open(unit=15,file=fname)
                  if (irep.eq.0) then
c                 skip the first 20 lines of HERMES data files
c                 not to be done for replica files
                     do k=1,19
                        READ(15,*)
                     end do
                  end if
                  ndatparSD(iexp,itar,ihad)=0
                  startdata(iexp,itar,ihad)=ndatSD+1
c-------------------------------------------------------------------------
c     recording selected data (user-defined cuts)
c-------------------------------------------------------------------------
                  do k=1,25000
c                    print data to output just to confirm that they are ok
                     if (k.eq.1) then
                        write(imaat,*) 'Reading data from file ',fname
                     end if

                     totdat=totdat+1
                     i=totdat
c                     i=ndatSD+k

                     READ(UNIT=15,FMT=200,END=999) (datatemp(j,i),j=3,9)
 200                 FORMAT(4x,7(1x,D13.6))

                     if (
     &                    (
     &                    (iexp.eq.1) !HERMES data
     &                    .or.
     &                    (
     &                    (iexp.eq.2) !COMPASS data with
     &                    .and.
     &                    (datatemp(6,i).gt.1.4d0) ! Q2 cut
     &                    .and.
     &                    (datatemp(8,i).lt.0.74d0) ! z cut
     &                    )
     &                    )
     &                    .and. !HERMES and COMPASS data with
     &                    (
     &                    (datatemp(4,i).gt.0d0) ! statistical error
     &                    .and.
     &                    (datatemp(8,i).gt.0.2d0) ! z cut
     &                    .and.
     &                    (datatemp(8,i).lt.0.74d0) ! z cut
     &                    .and.
     &                    (datatemp(6,i).gt.1.4d0) ! Q2 cut
     &                    .and.
     &                    (
     &                    (datatemp(9,i).lt.
     &                    (0.2d0*dsqrt(datatemp(6,i))+0.5d0))) ! Php < A*Q+B
     &                    .and.
     &                    (
     &                    (datatemp(9,i).lt.
     &                    (0.7d0*dsqrt(datatemp(6,i))*datatemp(8,i)
     &                    +0.5d0))))
     &                    ) then
                     idat=idat+1
                     datamat(1,idat)= dble(iexp)
                     datamat(2,idat)= dble(itar)
                     datamat(3,idat)= dble(ihad)
                     do j=3,9
                        datamat(j+1,idat)=datatemp(j,i)
                     end do
                ndatparSD(iexp,itar,ihad) = ndatparSD(iexp,itar,ihad)+1

c                    print just to confirm that data are ok
                     if (ipri.ne.0) then
                        write(imaat,300) idat, (datamat(j,idat),j=1,10)
 300                    FORMAT(I5,3(F4.0),7(1x,D13.6))
                     end if
                  else if (ipri.ne.0) then
C                     write(imaat,550) '   Warning: skipping dat', i,
C     &                    ' z =', datatemp(8,i),' Q2 =',datatemp(6,i),
C     &                    ' x =', datatemp(7,i),' Php =', datatemp(9,i)
C 550                 FORMAT(1X,A25,I6,4(A7,D13.6))
                  endif
               end do

 999           WRITE(imaat,*)'End of data. Ndat ', trim(target(itar)),
     &              ' ', trim(hadron(ihad+3)),
     &              ndatparSD(iexp,itar,ihad)

               ndatSD=ndatSD+ndatparSD(iexp,itar,ihad)
               enddata(iexp,itar,ihad)=ndatSD

             if (iexp.eq.2) then
               if (index(fname,"17").eq.0) then
                call binningSD(C_Q2bin_upb,C_Q2bin_lob,C_xbin_upb,
     &                          C_xbin_lob,C_zbin_upb,C_zbin_lob,
     &                          startdata(iexp,itar,ihad),
     &                          enddata(iexp,itar,ihad),datamat,ir)
               else
               call binningSD(C17_Q2bin_upb,C17_Q2bin_lob,C17_xbin_upb,
     &                        C17_xbin_lob,C17_zbin_upb,C17_zbin_lob,
     &                        startdata(iexp,itar,ihad),
     &                        enddata(iexp,itar,ihad),datamat,ir)
               end if
             else if (iexp.eq.1) then
               call binningSD(H_Q2bin_upb,H_Q2bin_lob,H_xbin_upb,
     &                        H_xbin_lob,H_zbin_upb,H_zbin_lob,
     &                        startdata(iexp,itar,ihad),
     &                        enddata(iexp,itar,ihad),datamat,ir)
              end if

            end if SKIPNAME

            close(unit=15)

         enddo
      enddo
      enddo


      WRITE(6,*)'Total num. of SIDIS data included:', ndatSD,
     &     ' out of ', i

      return
      end

c-------------------------------------------------------------------------
c-------------------------------------------------------------------------
c     read DY data
c-------------------------------------------------------------------------
c-------------------------------------------------------------------------
      subroutine readdataDY(irep, datamatDY, ipri,ir)
       use com, only : ndatSD, ndatparSD,ndatDY,ndatparDY,target,
     &                 hadron, experiment, iexp,totbin
       use bin
      integer i, j, k, totdat,imaat
     &          irep, ipri, idatDY,totdatDY
      integer :: startdata,enddata
      double precision datamatDY(6,2500), datatempDY(5,2500)
      character fname*82

      i=0
      totdat=0
      totdatDY=0
      idatDY=0
      ndatDY=0
      ntotbinDY=0


!      ir=mod(ir+1,2)

c-------------------------------------------------------------------------
c     building the filename 'fname'
c-------------------------------------------------------------------------
      do iexp=3,6               !select DY experiment datasets
         if (irep.eq.0) then   !uncomment to consider also replica case
            write(fname,'(a,a,a,a,a)')
     &           'data/DY.',
     &           trim(experiment(iexp)),
     &           '.list'
         elseif (irep.eq.1) then !lines to be used for replica case
            write(fname,'(a,a,a,a,a)')'Rdata/RDY.',
     &           trim(experiment(iexp)),'.list'
         end if

         if (irep.eq.0) then
               imaat=23
         else if (irep.eq.1) then
               imaat=24
         end if
c-------------------------------------------------------------------------
c     opening the file 'fname'
c-------------------------------------------------------------------------
         open(unit=15,file=fname)
         if (irep.eq.0) then
c          skip the first 15 lines of E288 data files
c           not to be done for replica files
            do k=1,15
               READ(15,*)
            end do
         end if

         ndatparDY(iexp)=0
         startdata=ndatDY+1
c-------------------------------------------------------------------------
c     recording selected data (user-defined cuts)
c-------------------------------------------------------------------------
         do k=1,2500            !reading loop
c           print data to output just to confirm that they are ok
            if (k.eq.1) then
               write(imaat,*) 'Reading data from file ',fname
            end if

            totdatDY=totdatDY+1
            i=totdatDY

            READ(UNIT=15,FMT=202,END=999) (datatempDY(j,i),j=1,4)
 202        FORMAT(8x,D4.1,8x,D4.1,9x,D10.2,9x,D10.2)
            datatempDY(5,i)= dble(iexp)

            if(
     &           (
     &           (
     &           (
     &           (datatempDY(1,i).gt.4d0).and.(datatempDY(1,i).lt.9d0) ! m cut
     &           .and.       ! only for
     &           (iexp.ne.6) ! E288_* experiments
     &           )
     &           .or.
     &           (
     &           (
     &           (datatempDY(1,i).gt.4d0).and.(datatempDY(1,i).lt.9d0) ! 1st m cut
     &           )
     &           .or. ! or
     &           (
     &           (datatempDY(1,i).gt.11d0).and.(datatempDY(1,i).lt.14d0) ! 2nd m cut
     &           )
     &           .and.          ! only for
     &           (iexp.eq.3)    ! E288_400 experiment
     &           )
     &           ).or.
     &           (
     &           (
     &           (
     &           (datatempDY(1,i).gt.7d0).and.(datatempDY(1,i).lt.9d0) ! 1st m cut
     &           )
     &           .or. ! or
     &           (
     &           (datatempDY(1,i).gt.10d0).and.(datatempDY(1,i).lt.12d0) ! 2nd m cut
     &           )
     &           )
     &           .and.          ! only for
     &           (iexp.eq.6)    ! E605 experiment
     &           )
     &           )
     &           .and.
     &           (datatempDY(2,i).le.(0.2d0*datatempDY(1,i)+0.5d0) ! pT<=AQ+B
     &           )
     &           ) then

               idatDY=idatDY+1
               datamatDY(1,idatDY)= dble(iexp)
               do j=1,4
                  datamatDY(j+1,idatDY)=datatempDY(j,i)
               end do

c              print just to confirm that data are ok
               if (ipri.ne.0) then
                  write(imaat,302) i, (datamatDY(j,idatDY),j=1,5)
               end if
 302           FORMAT(I3,2(4x,F4.1),3(4x,D13.6))

               ndatparDY(iexp)=ndatparDY(iexp)+1

            else if (ipri.ne.0) then
               write(imaat,501) '   Warning: skipping bin', i,
     &              ' m =', datatempDY(1,i),
     &              ' pT =',datatempDY(2,i)
 501           FORMAT(1X,A25,I6,2(A7,D13.6))
            end if              !end of condition 4<m<9 GeV

         end do                 !end of reading loop (k=...)
 999     WRITE(imaat,*)'End of data. Nbin ',trim(experiment(iexp)),
     &        ndatparDY(iexp)
         ndatDY=ndatDY+ndatparDY(iexp)
         enddata=ndatDY

        if ((iexp.ge.3).and.(iexp.le.5)) then
         call binningDY(E288_mbin,startdata,enddata,datamatDY,ir)
        else if (iexp.eq.6) then
         call binningDY(E605_mbin,startdata,enddata,datamatDY,ir)
        end if

         close(unit=15)
      enddo

      WRITE(6,*)'Total num. of Drell-Yan data included:', ndatDY,
     &     ' out of ', i

      return
      end

c-------------------------------------------------------------------------
c-------------------------------------------------------------------------
c     read Z data
c-------------------------------------------------------------------------
c-------------------------------------------------------------------------
      subroutine readdataZ(irep, datamatZ, ipri,ir)
      use com,only: ndatZ,ndatparZ,
     &              target, hadron, experiment,iexp,expBoole
       use bin
      implicit none
      integer i, j, k,ir, irep, ipri, idatZ, totdatZ,imaat
      integer :: startdata,enddata
      double precision datamatZ(7,1000), datatempZ(6,1000)
      character fname*82
!      integer :: len_skip(7:14) = (/20,20,20,20,102,28,34,32/)
      
      i=0
      totdatZ=0
      idatZ=0
      ndatZ=0
      ntotbinZ=0

!      ir=mod(ir+1,2)

c-------------------------------------------------------------------------
c     building the filename 'fname'
c-------------------------------------------------------------------------
      do iexp=7,size(experiment)     !select Z experiment datasets
       BOOL: if (expBoole(iexp)) then
         if (irep.eq.0) then   !uncomment to consider also replica case
            write(fname,'(a,a,a,a,a)')
     &           'data/DY.',
     &           trim(experiment(iexp)),
     &           '.list'
         elseif (irep.eq.1) then !lines to be used for replica case
            write(fname,'(a,a,a,a,a)')'Rdata/RDY.',
     &           trim(experiment(iexp)),'.list'
      end if

      if (irep.eq.0) then
            imaat=23
      else if (irep.eq.1) then
            imaat=24
      end if
c-------------------------------------------------------------------------
c     opening the file 'fname'
c-------------------------------------------------------------------------
         open(unit=15,file=fname)

         if (irep.eq.0) then
c           skip the first 20 lines of Z production data files
c           not to be done for replica files

            do k=1,20!len_skip(iexp)
               READ(15,*)
            end do
         end if

         ndatparZ(iexp)=0
         startdata=ndatZ+1
c-------------------------------------------------------------------------
c     recording selected data (user-defined cuts)
c-------------------------------------------------------------------------
         do k=1,250
c           print data to output just to confirm that they are ok
            if (k.eq.1) then
               write(imaat,*) 'Reading data from file ',fname
            end if

            totdatZ=totdatZ+1
            i=totdatZ
            if(iexp.le.8.or.iexp.eq.20.or.iexp.eq.21) then
               datatempZ(6,i)=0d0
               READ(UNIT=15,FMT=*,END=999) (datatempZ(j,i),j=3,5)
            else
               READ(UNIT=15,FMT=*,END=999) (datatempZ(j,i),j=3,6)
            end if
 !!           READ(UNIT=15,FMT=222,END=999) (datatempZ(j,i),j=3,6)
 222        FORMAT(6x,f6.2,6x,g12.0,3x,g12.0,1x,g12.0)
            datatempZ(1,i)= dble(iexp)
            datatempZ(2,i)= 91.1876d0 !VALORE MASSA

            if (datatempZ(3,i).le.18.7d0) then
!     the limit on qT is based on our magic formula 0.2*Q + 0.5 = 18.7 GeV
               
               
               idatZ=idatZ+1
               datamatZ(1,idatZ)= dble(iexp)
               do j=2,6
                  datamatZ(j,idatZ)=datatempZ(j,i)
               end do
               
               
               if (ipri.ne.0) then
                  write(imaat,303) i, (datamatZ(j,idatZ),j=1,6)
               end if
 303           FORMAT(I3,2(4x,F4.1),4(4x,D13.6))
               
               ndatparZ(iexp)=ndatparZ(iexp)+1
               
            else if (ipri.ne.0) then
               write(imaat,501) '   Warning: skipping bin', i, ' m =',
     &              datatempZ(2,i),' pT =',datatempZ(3,i)
 501           FORMAT(1X,A25,I6,2(A7,D13.6))
               
            end if              !end of qT condition
         end do
 999     WRITE(imaat,*)'End of data. Nbin ',trim(experiment(iexp)),
     &        '         number of selected data: ',ndatparZ(iexp)
         
         ndatZ=ndatZ+ndatparZ(iexp)
         enddata=ndatZ
         
         call binningZ(startdata,enddata,datamatZ,ir)
         
         close(unit=15)

      end if BOOL
      enddo

      WRITE(6,*)'Total num. of Z boson prod. data included:', ndatZ,
     &     ' out of ', i

      return
      end

!--- Subroutine to read the denominator file

      subroutine readdenom
       use com, only: den,bindenom,ascorr
       implicit none
       integer :: k

       open(unit=151,file="./denom.dat")

       if(ascorr.eq.0) then !LO
          do k=1,25000

             READ(UNIT=151,FMT=207,END=993) bindenom(k),den(k)
 207         FORMAT(5x,i4,56x,g10.0)
             write(911,*) bindenom(k),den(k)
          end do
       elseif(ascorr.eq.1) then !NLO
          do k=1,25000

             READ(UNIT=151,FMT=208,END=993) bindenom(k),den(k)
 208         FORMAT(5x,i4,67x,g10.0)
             write(911,*) bindenom(k),den(k)
          end do
       else
          write(*,*) 'Error: wrong value for ascorr'
          STOP
       end if
993     close(151)

      end subroutine readdenom
