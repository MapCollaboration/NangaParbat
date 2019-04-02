module bin
  use com,only: totbin,ifl,NtotbinSD,NtotbinZ,NtotbinDY,iexp,itar,ihad, &
                flagQbinSD,flagXbinSD,flagZbinSD,flagMbinDY,experiment
  implicit none
!--- COMPASS bins
    ! Q
    double precision, dimension(23) :: C_Q2bin_lob =(/ 1.d0,1.d0,1.3d0,1.d0,1.5d0,1.d0,1.5d0,2.5d0, &
           1.d0,1.5d0,2.5d0,3.5d0,1.d0,1.2d0,1.5d0,2.5d0,3.5d0,1.5d0,2.5d0,3.5d0,6.0d0,3.5d0,6.d0/)
    double precision, dimension(23) :: C_Q2bin_upb = (/ 1.25d0,1.3d0,1.7d0,1.5d0,2.1d0,1.50d0,  &
           2.5d0,3.5d0,1.5d0,2.5d0,3.5d0,5.d0,1.2d0,1.50d0,2.5d0,3.5d0,6.d0,2.5d0,3.5d0,6.d0,10.d0,6.d0,10.d0/)
    ! x
    double precision, dimension(23) :: C_xbin_lob=(/ 0.0045d0,0.006d0,0.006d0,0.008d0,0.008d0,  &
           0.012d0,0.012d0,0.012d0,0.018d0,0.018d0,0.018d0,0.018d0,0.025d0,0.025d0,0.025d0,0.025d0,0.025d0,    &
           0.04d0,0.04d0,0.04d0,0.04d0,0.07d0,0.07d0/)
    double precision, dimension(23) :: C_xbin_upb=(/ 0.006d0,0.008d0,0.008d0,0.012d0,0.012d0,   &
           0.018d0,0.018d0,0.018d0,0.025d0,0.025d0,0.025d0,0.025d0,0.035d0,0.04d0,0.04d0,0.04d0,0.04d0,0.05d0, &
           0.07d0,0.07d0,0.07d0,0.12d0,0.12d0/)
    ! z
    double precision, dimension(8) :: C_zbin_lob= (/0.20d0, 0.25d0,0.3d0, 0.35d0, 0.4d0, 0.5d0, 0.6d0, 0.7d0/)
    double precision, dimension(8) :: C_zbin_upb= (/0.25d0, 0.3d0,0.35d0, 0.4d0, 0.5d0, 0.6d0, 0.7d0, 0.8d0/)

!--- New COMPASS 17 bins

double precision, dimension(5) :: C17_Q2bin_lob = (/ 1.d0,1.7d0,3.d0,7.d0,16.d0/)
double precision, dimension(5) :: C17_Q2bin_upb = (/ 1.7d0,3.d0,7.d0,16.d0,81.d0/)
! x
double precision, dimension(9) :: C17_xbin_lob=(/ 0.003d0, 0.008d0, 0.013d0, 0.02d0, 0.032d0, 0.055d0, &
                                                   0.055d0, 0.1d0, 0.21d0/)
double precision, dimension(9) :: C17_xbin_upb=(/ 0.008d0, 0.013d0, 0.02d0, 0.032d0, 0.055d0, &
                                                   0.055d0, 0.1d0, 0.21d0, 0.4d0/)
! z
double precision, dimension(4) :: C17_zbin_lob= (/ 0.2d0 ,0.3d0, 0.4d0, 0.6d0 /)
double precision, dimension(4) :: C17_zbin_upb= (/ 0.3d0, 0.4d0, 0.6d0, 0.8d0 /)

!--- Hermes bins
    !Q
    double precision, dimension(6) :: H_Q2bin_lob =(/1.2, 1.5, 1.8, 2.9, 5.2, 9.2/)
    double precision, dimension(6) :: H_Q2bin_upb =(/1.5, 1.8, 2.9, 5.2, 9.2,10.0/)
    !x
    double precision, dimension(6) :: H_xbin_lob =(/0.023d0, 0.047d0, 0.075d0, 0.12d0, 0.20d0, 0.35d0/)
    double precision, dimension(6) :: H_xbin_upb =(/0.047d0, 0.075d0, 0.120d0, 0.20d0, 0.35d0, 0.60d0/)
    !z
    double precision, dimension(8) :: H_zbin_lob =(/0.1d0, 0.2d0, 0.25d0, 0.3d0, 0.375d0, 0.475d0, 0.6d0, 0.8d0/)
    double precision, dimension(8) :: H_zbin_upb =(/0.2d0, 0.25d0, 0.3d0, 0.375d0, 0.475d0, 0.6d0, 0.8d0, 1.1d0/)
!--- E288 bins
    double precision, dimension(10) :: E288_mbin =(/4.5d0,5.5d0,6.5d0,7.5d0,8.5d0,9.5d0,10.5d0,11.5d0,12.5d0,13.5d0/)
!--- E605 bins
    double precision, dimension(5)   :: E605_mbin =(/7.5d0,8.5d0,11.d0,12.5d0,15.8d0/)


  SAVE
  CONTAINS

   SUBROUTINE binningSD(Qhb,Qlb,xhb,xlb,zhb,zlb,initdat,enddat,datalist,ir)
      implicit none
      double precision, dimension(:),intent(in) :: Qhb,Qlb,xhb,xlb,zhb,zlb !(l)ower and (h)igher bounds of Q,x,z bins
      double precision,intent(inout) :: datalist(11,25000)
      integer,intent(in) :: initdat,enddat
      integer :: ir,id,iw,jbz,jbq,jbx
      integer,allocatable :: ordbin(:,:,:) !store bin numbers
!      integer:: ordbin(2,2,-2:2,23,8) !store bin numbers

      allocate ( ordbin(size(xhb),size(Qhb),size(zhb))) !determine size of ordbin, matrix #Q bins*#z bins

      ordbin=0 !initialize ordbin

      DAT: do id=initdat,enddat     !loop on data from the same datafile
        !loop on x bin values
        XBIN: do jbx=1,size(xhb) !SIDIS bin are determined by Q2,x,z
          if ((datalist(8,id).gt.xlb(jbx)).and.(datalist(8,id).lt.xhb(jbx)).or..not.flagXbinSD) then

             QBIN: do jbq=1,size(Qhb)
               if (((datalist(7,id).gt.Qlb(jbq)).and.(datalist(7,id).lt.Qhb(jbq)).or..not.flagQbinSD) &
                   .or.(datalist(1,id).eq.1)) then !ignore x interval for Hermes (only Q2 and z relevant)

                 !loop on z bin values
                ZBIN: do jbz=1,size(zhb)
                if ((datalist(9,id).gt.zlb(jbz)).and.(datalist(9,id).lt.zhb(jbz)).or..not.flagZbinSD) then

                  if (ordbin(jbx,jbq,jbz).ne.0) then           !check if the bin has already an assigned number
                        datalist(11,id)=ordbin(jbx,jbq,jbz)
                  else                                      !if not assign the next number available
                        totbin(ir)=totbin(ir)+1
                        NtotbinSD(iexp,itar,ihad)=NtotbinSD(iexp,itar,ihad)+1
                        ordbin(jbx,jbq,jbz) = totbin(ir)
                        datalist(11,id)=totbin(ir)

                        if ((ifl.eq.1).and.(ir.eq.1)) then     !take note of bin numbers
!                        write(14,'(I5,3(2x,I2),3(2x,f6.3))') int(datalist(11,id)),&
!                                    ( int(datalist(iw,id)), iw=1,3 ), &
!                                    ( datalist(iw,id), iw=7,9 )
                          write(14,'(I5,3(2x,I2),3(2x,2(2x,f6.3)))',advance='no') int(datalist(11,id)),&
                                      ( int(datalist(iw,id)), iw=1,3 )
                          if (flagQbinSD) write(14,'(2x,2(2x,f6.3))',advance='no')  Qlb(jbq),Qhb(jbq)
                          if (flagXbinSD) write(14,'(2x,2(2x,f6.3))',advance='no')  xlb(jbx),xhb(jbx)
                          if (flagZbinSD) write(14,'(2x,2(2x,f6.3))',advance='no')  zlb(jbz),zhb(jbz)
                          write(14,*)
                        end if


                    !end if !ordbin
                  end if !ZBIN
                  EXIT XBIN

                end if
                end do ZBIN
            end if
            end do QBIN
         end if
         end do XBIN

         if(datalist(11,id).eq.0) write(9,*) 'SD WARNING: NO BIN assigned',id, &
            datalist(7,id),datalist(8,id),datalist(9,id)

      end do DAT

      deallocate (ordbin)

   end subroutine binningSD


   SUBROUTINE binningDY(mbin,initdat,enddat,datalist,ir)
      implicit none
      double precision, dimension(:),intent(in) :: mbin
      double precision,intent(inout) :: datalist(6,2500)
      integer,intent(in) :: initdat,enddat
      integer :: ir,id,iw,jbm
      integer,allocatable :: ordbin(:)


      allocate ( ordbin(size(mbin)))

      ordbin=0

      DAT: do id=initdat,enddat      !loop on data from the same datafile

        MB: do jbm=1,size(mbin)
         if (( datalist(2,id).eq.mbin(jbm) ).or..not.flagMbinDY) then

                  if (ordbin(jbm).ne.0) then       !check if the bin has already an assigned number
                        datalist(6,id)=ordbin(jbm)
                  else                             !if not assign the next number available
                        totbin(ir)=totbin(ir)+1            !increase total number of bin of one unit
                        NtotbinDY(iexp)=NtotbinDY(iexp)+1  !increase bin number of iexp of one unit
                        ordbin(jbm) = totbin(ir)           !save current number of bin
                        datalist(6,id)=totbin(ir)          !assign bin number to data point

!                        if ((ifl.eq.1).and.(ir.eq.1)) then     !take note of bin numbers in output file
                          write(14,'(I5,2x,I2,12x,f5.2)') int(datalist(6,id)), &
                          int(datalist(1,id)),mbin(jbm)
!                        end if
                        !end if
                  end if
                  EXIT MB
         end if
        end do MB

        if(datalist(6,id).eq.0) write(9,*) 'DY WARNING: NO BIN assigned',id

      end do DAT

      deallocate (ordbin)

   end subroutine binningDY

   SUBROUTINE binningZ(initdat,enddat,datalist,ir)
      implicit none
      double precision,intent(inout) :: datalist(7,1000)
      integer,intent(in) :: initdat,enddat
      integer :: ir,id,jbe,j
      integer,dimension(7:size(experiment)) :: ordbin

      ordbin=0

      DAT: do id=initdat,enddat     !loop on data from the same datafile

       EXPBIN:do jbe=7,size(experiment)      !bin for Z are determined by the type of experiment

                if (int(datalist(1,id)).eq.jbe) then
                    if (ordbin(jbe).ne.0) then      !check if the bin has already an assigned number
                        datalist(7,id)=ordbin(jbe)
                    else                            !if not assign the next number available
                        totbin(ir)=totbin(ir)+1             !increase total number of bin of one unit
                        NtotbinZ(iexp)=NtotbinZ(iexp)+1   !increase bin number of iexp of one unit
                        ordbin(jbe) = totbin(ir)            !save current number of bin
                        datalist(7,id)=totbin(ir)           !assign bin number to data point

                        if ((ifl.eq.1).and.(ir.eq.1)) then     !take note of bin numbers in output file
                          write(14,'(I5,2x,I2)') int(datalist(7,id)), &
                          int(datalist(1,id))
                        end if
                        !end if
                    end if
                end if
        end do EXPBIN

        if(datalist(7,id).eq.0) write(9,*) 'Z WARNING: NO BIN assigned',id

      end do DAT
   end subroutine binningZ

end module
