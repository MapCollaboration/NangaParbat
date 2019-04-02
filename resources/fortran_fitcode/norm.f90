 module normaliz_bin
   implicit none

 contains

!--- create an array for a specific bin, contatining all elements necessary to normalization
   subroutine create_bin_elem_array(ib,sigthi,sigexpi,err2i,binelem)
!     integer,intent(in) :: ib !counter for elements in bin
     double precision,intent(in) :: sigthi,sigexpi,err2i !sigma theo and exp, errors for each point in bin
     double precision,dimension(:,:),intent(out) :: binelem
     integer,intent(inout) :: ib

     ib = ib+1 !counter for elements in bin

     binelem(:,ib) = (/sigthi, sigexpi,err2i/)

   end subroutine create_bin_elem_array

   subroutine normbin(jb,binelem,norm)
     use com,only: ibin
     integer,intent(in) :: jb !number of data points in bin
     double precision, dimension(jb) :: oexp,oth,Deltao2
     double precision :: numnorm,dennorm
     double precision,intent(out) :: norm
     double precision,dimension(3,100),intent(in) :: binelem

     oth   = binelem(1,1:jb)
     oexp    = binelem(2,1:jb)
     Deltao2 = binelem(3,1:jb)

       numnorm = SUM(oexp*oth/(Deltao2))

       dennorm = SUM(oth**2/(Deltao2))

      norm=numnorm/dennorm

   end subroutine normbin

   subroutine calc_chi2_bin(jb,norm,binelem,res_bin)
      integer,intent(in) :: jb !number of data points in bin
      double precision, dimension(jb) :: oexp,oth,Deltao2
      double precision, intent(in) :: norm
      double precision, intent(out) :: res_bin
      double precision,dimension(3,100),intent(in) :: binelem

       oth   = binelem(1,1:jb)
       oexp    = binelem(2,1:jb)
       Deltao2 = binelem(3,1:jb)

       res_bin = SUM((norm*oth-oexp)**2/Deltao2)

   end subroutine calc_chi2_bin




 end module normaliz_bin

 module normal_firstbin
  use com,only: prevXbin,prevQ2bin,prevZbin, index1bin, &
                iexp,itar,ihad
  implicit none


  !  AB change 3 to normalize COMPASS to first bin
  !  to normalize also HERMES, comment the second if statements and also
  !  the   if ((iexp.eq.1).... statement below

  contains

  subroutine norm1bins(x,q2,z,mult,stat,sys,rep)
    use com,only: mult1bin, stat1bin, sys1bin
    double precision,intent(in) :: x,q2,z
    integer,intent(in) :: rep !0 for original date, 1 for replicas
    double precision, intent(inout) :: mult,stat,sys
    double precision :: multA

      if (((x.ne.prevXbin).or.   &
         (q2.ne.prevQ2bin)).or.  &
         (z.ne.prevZbin)) then
            mult1bin(rep)=mult
            stat1bin(rep)=stat
            sys1bin(rep)=sys
            index1bin=1
       end if

      if (iexp.eq.2) then
          multA=mult
          mult=multA*(1d0/mult1bin(rep))
          stat=mult*dsqrt(stat**2/multA**2+ stat1bin(rep)**2/mult1bin(rep)**2)
          sys=mult*dsqrt(sys**2/multA**2+ sys1bin(rep)**2/mult1bin(rep)**2)
      endif

  end subroutine norm1bins



  !  the contribution to chi2 is 0, but we must take care of not increasing the
  !  n. of degrees of freedom
  subroutine norm1bin_count_dof
    use com,only : ndatSDin, ndatparSDin
    implicit none


         if ((iexp.eq.1).or.((iexp.eq.2).and.(index1bin.eq.0))) then
             ndatSDin=ndatSDin+1
             ndatparSDin(iexp,itar,ihad)=ndatparSDin(iexp,itar,ihad)+1
         end if
  !  AB end of change 3
  end subroutine norm1bin_count_dof



! AB change 4 to normalize COMPASS to first bin
! to normalize also HERMES, comment the second if statements
 subroutine norm1bins_theo(x,q2,z,multtheo,errtheo2)
  use com,only: multtheo1bin,errtheo21bin
  double precision,intent(in) :: x,q2,z
  double precision, intent(inout) :: multtheo,errtheo2
  double precision ::  multtheoA

        if (((x.ne.prevXbin).or.    &
             (q2.ne.prevQ2bin)).or. &
             (z.ne.prevZbin)) then

                multtheo1bin=multtheo
                errtheo21bin=errtheo2
         end if

         if (iexp.eq.2) then
          multtheoA=multtheo
          multtheo=multtheoA*(1d0/multtheo1bin)
          errtheo2=multtheo**2*(errtheo2/multtheoA**2  &
                      + errtheo21bin/multtheo1bin**2)
         endif
  end subroutine norm1bins_theo
  !  AB end of change 4

  subroutine save_bin_values(x,z,q2)
      double precision,intent(in) :: x,z,q2

!--- save x,q,z values of current bin
               prevXbin=x
               prevQ2bin=q2
               prevZbin=z
               index1bin=0
  end subroutine save_bin_values

 end module normal_firstbin
