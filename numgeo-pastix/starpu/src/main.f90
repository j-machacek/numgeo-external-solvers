!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
!                                          numgeo
!                     Copyright (C) 2022 Jan Machacek, Patrick Staubach
!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
!
! PROGRAM: numgeo-pastix
!
!> author: Jan Machacek, jan-machacek@outlook.com
!
!
!>### SUMMARY:
!> Program that solves a linear system of equations given in coordinate format using the
!> PaStiX library (see https://gitlab.inria.fr/solverstack/pastix).
!> Many thanks to Mathieu Faverge (mathieu.faverge@inria.fr) from INRIA helping us setting up PaStiX!
!
!> numgeo-pastix software is part of the numgeo software developed by Jan Machacek and Patrick Staubach.
!
!
!>### REVISION HISTORY
!> 11.01.2022, J. Machacek - Initial version
!
!>### DISCLAIMER
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY, without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR PARTICULAR PURPOSE.
!
!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~

module precision_
  integer, parameter, public  :: r8 = selected_real_kind(15,307)         !< 15 digits, range \([10^{-307} , 10^{+307}  - 1]\); 64 bits.
  integer, parameter, public  :: i8 = selected_int_kind(18)              !< Range \([-2^{63},+2^{63} - 1]\), 19 digits plus sign; 64 bits.
  integer, parameter, public  :: i4 = selected_int_kind(9)               !< Range \([-2^{31},+2^{31} - 1]\), 10 digits plus sign; 32 bits.
end module precision_


program main
  use precision_
  use iso_c_binding
  use omp_lib
  use pastix_enums
  use spmf
  use pastixf
  implicit none

  character(len=999) :: command_line, argument

  ! just to print some information...
  logical       :: print_times = .true.
  integer       :: time_start, time_start2
  integer       :: time_end, time_end2
  integer       :: cr
  real(r8)      :: rate
  character(10) :: time

  ! sparse matrix in compressed sparse row format
  integer(kind=pastix_int_t)                                    :: ndof     !! number of dofs of the system of equations (soe)
  integer(kind=pastix_int_t)                                    :: nonzeros !! number of nonzero entreis in A
  real(kind=c_double)       , dimension(:), pointer             :: A        !! Jacobian of the soe (left-hand-side)
  real(kind=c_double)       , allocatable, dimension(:), target :: r        !! residual of the soe (right-hand-side)
  integer(kind=spm_int_t)   , dimension(:), pointer             :: ia
  integer(kind=spm_int_t)   , dimension(:), pointer             :: ja

  ! other variables
  integer(i8)    :: ios
  integer(c_int) :: nthreads

  ! PaStiX variables (taken from the example)
  type(pastix_data_t),        pointer                      :: pastix_data

  type(spmatrix_t),           pointer                      :: spm
  integer(kind=pastix_int_t), target                       :: iparm(iparm_size)
  real(kind=c_double),        target                       :: dparm(dparm_size)
  integer(c_int)                                           :: info
  integer(kind=pastix_int_t)                               :: nrhs

  real(kind=c_double), dimension(:,:), allocatable, target :: x
  real(kind=c_double), dimension(:,:), allocatable, target :: b
  type(c_ptr)                                              :: x_ptr
  type(c_ptr)                                              :: b_ptr
  type(c_ptr)                                              :: tmp

  ! define if you watn to use the "transpose-trick" for csr-matrices
  ! Note: it turned out, that this trick does not work for simulations
  !       including contact and two-phase flow. Reason until now unknown...
  logical :: use_transpose_trick = .false.

  ! If user define ordering is used
  ! type(pastix_order_t),       pointer                      :: order => null()
  ! integer(kind=pastix_int_t), dimension(:), pointer        :: permtab

  ! If initial guess of solution is provided
  ! real(kind=c_double), dimension(:,:), allocatable, target :: x0
  ! type(c_ptr)                                              :: x0_ptr

  ! To use the check matrix routine
  type(spmatrix_t),           pointer                      :: spm2

  ! other currently unused variables
  ! integer                                                  :: nfact, nsolv

  ! number of threads
  !nthreads = omp_get_max_threads()
  !write(*,*) 'threads = ', nthreads

  !write(*,*) 'set threads = 6'
  !call omp_set_num_threads(6)

  !nthreads = omp_get_max_threads()
  !write(*,*) 'threads are now = ', nthreads

  ! ----------------------------------------
  ! Evaluate command line and start timers
  ! ----------------------------------------

  call get_command(command_line)
  argument = command_line(24:len(command_line))

  ! for debugging
  ! argument = trim("terzaghi")

  if (print_times) then
    ! get initial system time
    CALL system_clock(count_rate=cr)
    rate = REAL(cr)
  end if

  if (print_times) then
    call date_and_time(TIME=time)
    write(*,*) 'Start numgeo-pastix: ' // time
    call system_clock(time_start)
  end if

  ! ----------------------------------------
  ! Read in properties of system of equations
  ! ----------------------------------------

  ! read solver settings and sizes (number of equations (degrees of freedom))
  open(newunit=ios, file='numgeo-ext-settings-'//trim(argument)//'.numgeo', form='formatted', access='sequential')
  read(ios,*) ndof
  read(ios,*) nonzeros
  close(ios)

  ! ----------------------------------------
  ! PaStiX: initialize the problem
  ! ----------------------------------------

  call pastixInitParam( iparm, dparm )
  call pastixInit( pastix_data, 0, iparm, dparm )

  allocate( spm )
  call spmInit( spm )

  spm%baseval = 1
  spm%mtxtype = SpmGeneral    ! general unsym. matrix
  spm%flttype = SpmDouble     ! double precision (c_double)
  spm%n       = ndof          ! number of equations (degrees of freedoms)
  spm%nnz     = nonzeros
  spm%dof     = 1

  ! MF: update some of the computed fields in order to
  ! correctly allocate all arrays
  call spmUpdateComputedFields( spm )

  ! MF: Now when you do have a CSR matrix, in order to avoid the
  ! CheckAndCorrect step, you can solve A^t x = b, instead of A x = b
  ! by lying to pastix about the matrix format
  if (use_transpose_trick) then
    spm%fmttype = SpmCSC                       ! Force matrix format to be CSC
    iparm(IPARM_TRANSPOSE_SOLVE) = PastixTrans ! Tell PaStiX to solve the transposed system
  else
    spm%fmttype = SpmCSR
  end if

  ! ----------------------------------------
  ! Allocate the matrix and initialize the pointers
  ! ----------------------------------------

  call spmAlloc( spm )

  if (use_transpose_trick) then
    ! MF: Here since you have a CSR or CSC, one of the array is of size
    ! ndof+1 and not nonzeros
    call c_f_pointer( spm%colptr, ia, [ndof+1] )
    call c_f_pointer( spm%rowptr, ja, [nonzeros] )
  else
    ! If you keep the CSR format
    call c_f_pointer( spm%rowptr, ia, [ndof+1] )
    call c_f_pointer( spm%colptr, ja, [nonzeros] )
  end if
  call c_f_pointer( spm%values, A,  [nonzeros] )

  ! ----------------------------------------
  ! Read in system of equations
  ! ----------------------------------------

  ! to evaluate time required by reading in the linear system
  if (print_times) call system_clock(time_start2)

  ! read in the left-hand-side
  open(newunit=ios, file='numgeo-ext-lhs-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) A
  close(ios)

  ! read in the index-array ja
  open(newunit=ios, file='numgeo-ext-ja-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) ja
  close(ios)

  ! read in the index-array ia
  open(newunit=ios, file='numgeo-ext-ia-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) ia
  close(ios)

  ! read in the right-hand-side
  allocate( r(ndof) )
  open(newunit=ios, file='numgeo-ext-rhs-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) r
  close(ios)

  ! to evaluate time required by reading in the linear system
  if (print_times) call system_clock(time_end2)

  ! ----------------------------------------
  ! PaStiX: check the matrix
  ! ----------------------------------------

  if (.not. use_transpose_trick) then
  ! MF: This stage is costly and needs to be done only if you do not
  ! make sure your matrix is in the right format
    allocate( spm2 )
    call spmCheckAndCorrect( spm, spm2, info )
    if ( info /= 0 ) then
      call spmExit( spm )
      spm = spm2
    end if
    deallocate( spm2 )
  end if

  call spmPrintInfo( spm )

  ! ----------------------------------------
  ! Read in right hand side
  ! ----------------------------------------

  nrhs = 1
  allocate(x (spm%n, nrhs))
  allocate(b (spm%n, nrhs))
  b(:,1) = r
  x_ptr  = c_loc(x)
  b_ptr  = c_loc(b)

  ! ----------------------------------------
  ! PaStiX: start solving
  ! ----------------------------------------

  ! 2- Analyze the problem
  call pastix_task_analyze( pastix_data, spm, info )

  ! Number of threads per process (-1 for auto detect) Default: -1
  iparm(IPARM_THREAD_NBR) = nthreads

  ! To reduce the number of static pivots
  dparm(DPARM_EPSILON_MAGN_CTRL) = real(1e-15)

  ! Maximum block size Default: 320 IN
  iparm(IPARM_MAX_BLOCKSIZE) = 2048

  ! Minimum block size Default: 160 IN
  iparm(IPARM_MIN_BLOCKSIZE) = 1024

  ! 2D splitting is only performed on column blocks larger than this threshhold
  iparm(IPARM_TASKS2D_LEVEL) = 128

  ! 3- Factorize the matrix
  call pastix_task_numfact( pastix_data, spm, info )

  ! 4- Solve the problem
  call pastix_task_solve( pastix_data, nrhs, x_ptr, spm%n, info )

  ! 5- Refine the solution
  call pastix_task_refine( pastix_data, spm%n, nrhs, b_ptr, spm%n, x_ptr, spm%n, info )

  ! 6- Destroy the C data structure
  call pastixFinalize( pastix_data )

  ! MF: The check does not know about the little trick with A^t, so we need to give the right info
  if (use_transpose_trick) then
    spm%fmttype = SpmCSR;
    tmp = spm%colptr;
    spm%colptr = spm%rowptr;
    spm%rowptr = tmp;
  end if

  ! ----------------------------------------
  ! PaStiX: check solution
  ! ----------------------------------------

  call spmCheckAxb( dparm(DPARM_EPSILON_REFINEMENT), nrhs, spm, c_null_ptr, spm%n, b_ptr, spm%n, x_ptr, spm%n, info )

  call spmExit( spm )
  deallocate(spm)
  deallocate(b)

  ! ----------------------------------------
  ! Report solution back to numgeo
  ! ----------------------------------------

  open(newunit=ios, file='numgeo-ext-solution-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  write(ios) x
  close(ios)

  ! ----------------------------------------
  ! Terminate
  ! ----------------------------------------

  deallocate(x, r)

  if (print_times) then
    call system_clock(time_end)
    write(*,*) '...took a total of seconds:', (time_end-time_start)/rate
    write(*,*) '...reading s.o.e.:', (time_end2-time_start2)/rate
    write(*,*) 'Exit numgeo-pastix'
    write(*,*) ' '
  end if


end program main
