!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!			arTeMiDe 1.0
!
! The package for reading the alphaStrong grid files and interpolating it
! It is the same routine as in TMDR, but only for alphaStrong
!
!	ver 1.0: release (AV, 07.05.2017)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


module ReadAs

implicit none

  private
  
  public :: InitializeAlphaStrong
  public :: As
  
  integer :: zMax !Length of grid
  real*8:: mu_ref!reference mu-point
  
  real*8, dimension(:), allocatable :: As_grid
  
  contains
!!! Initializing routing
!!! Filles the prebuiled arrays
  subroutine InitializeAlphaStrong(path)
    character (len=*) :: path
    character (len=50) :: line
    integer ::i
    real*8,dimension(1:12)::dummy
    
    
    OPEN(UNIT=50, FILE="../"//path, ACTION="read", STATUS="old")
    
    !!! Read the grid header
    READ(50,'(A75)') line !!!! Read header and print it
    write (*,*) line
    
    READ(50,*) line    !!!! Skip 2 technical lines
    READ(50,*) line
    
    READ(50,*) zMax 	!!length of grid    
    READ(50,*) line    !!!! Skip 1 technical lines    
    READ(50,*) mu_ref  !!!! refenrece point
    READ(50,*) line    !!!! Skip 1 technical lines
    
    !allocate the arrays of greed acording to the readed file
    allocate(As_grid(0:zMax))
    
    
    !fill the grid arrays
    do i=0,zMax
      READ(50,*) As_grid(i),&
	dummy(1),dummy(2),dummy(3),dummy(4),dummy(5),dummy(6),&
	dummy(7),dummy(8),dummy(9),dummy(10),dummy(11),dummy(12)
    end do
    
    CLOSE (50, STATUS='KEEP') 
    
  end subroutine InitializeAlphaStrong
 
  !!! Function interpolate the value of as, using grids  
  function As(mu)
  
    real*8:: As,mu
    integer :: zInt
    real*8::zReal,zFrac   
    
    zReal=20.d0*LOG(2.d0*mu)
    zInt=INT(zReal)
    zFrac=zReal-zInt
    !The linear interpolation is used, since as~1/Log[mu] more-or-less
    !It gives accuracy better then 10^{-6} in comparison to exact values
    If (zReal<1) then
      WRITE(*,*) 'TMDR WARNING: Generic large value evaluated for As (mu is close to Landau pole.)'
      As=1.d8
    else if(zInt>zMax) then
      !WRITE(*,*) 'readAS WARNING: Logarithmical extrapolation is used for As (values of mu outside of grid)'
      As=1/(As_grid(zMax)-(As_grid(zMax)-As_grid(zMax+1))*zFrac)
    else
      As=1/(As_grid(zInt)-(As_grid(zInt)-As_grid(zInt+1))*zFrac)
    end if
  
  end function As

end module ReadAs
