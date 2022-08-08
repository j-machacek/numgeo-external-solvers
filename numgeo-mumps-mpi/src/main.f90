!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
!                                          numgeo
!                Copyright (C) 2018-2022 Jan Machacek, Patrick Staubach
!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
!
! PROGRAM: numgeo-mumps-mpi
!
!> author: Jan Machacek, jan-machacek@outlook.com
!
!
!>### SUMMARY: 
!> Program that solves a linear system of equations given in coordinate format using the
!> mpi-version of the mumps solver. This software is part of the numgeo software developed by
!> Jan Machacek and Patrick Staubach.
!
!
!>### REVISION HISTORY
!> 06.01.2021, J. Machacek - Initial version
!> 26.02.2021, P. Staubach - Added job-name to the reading and writing files to be able to perform several analyses in one folder
!> 20.04.2021, J. Machacek - Added format to read settings-file (mpi error on some architectures)
!> 23.12.2021, J. Machacek - Adapted to new numgeo output format
!> 11.03.2022, J. Machacek - Continue numgeo simulation if mumps returns an error
!
!>### DISCLAIMER
! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY, without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR PARTICULAR PURPOSE.
!
!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
program main
  use mpi
  implicit none

  ! include the derived type holding the internal mumps-structure for the double precision version
  ! Note, that 'dmumps_root.h' is needed herein
  include 'dmumps_struc.h'
  type(dmumps_struc) :: dmumps_par

  integer :: ios
  integer :: ierr, errcode
  integer :: myid
  integer :: nproc
  
  character(len=999) :: command_line,argument
  
  ! just to print some information...
  logical :: print_times = .true.
  integer :: time_start, time_start2
  integer :: time_end, time_end2
  integer :: cr
  real(8) :: rate
  character(10) :: time
  
  if (print_times) then
    ! get initial system time
    CALL system_clock(count_rate=cr)
    rate = REAL(cr)
  end if
  
  !prepare the usage of MPI
  call mpi_init(ierr)
  
  !determine the unique ID number of the current process
  call mpi_comm_rank(mpi_comm_world,myid,ierr)
  
  !determine the number of processes
  call mpi_comm_size(mpi_comm_world,nproc,ierr)

  call get_command(command_line)
  argument = command_line(18:len(command_line))

  !mp%comm_world = mpi_comm_world
  dmumps_par%COMM = mpi_comm_world
  
  ! initializes an instance of the package,
  ! must be called before other call to the package on the same instance
  dmumps_par%JOB = -1

  ! Matrix is unsymmetric (general case)
  dmumps_par%SYM = 0

  ! The host is not involved in the parallel steps of the factorization and solve phases
  ! -> serial version: self%dmumps_par%PAR = 1
  dmumps_par%PAR = nproc

  ! initialize MUMPS
  call DMUMPS(dmumps_par)


  ! define the problem on the host
  if (dmumps_par%MYID == 0) then
  
    if (print_times) then
      call date_and_time(TIME=time)
      write(*,*) 'Start numgeo-mumps-mpi: ' // time
      call system_clock(time_start)
    end if

    ! evaluate possible errors
    if (dmumps_par%INFOG(1) < 0) then
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) 'ERROR in numgeo-mumps-mpi:'
      write(*,*) ''
      write(*,*) 'Mumps returned errors during initialization: '
      write(*,*) 'INFOG(1) = ', dmumps_par%INFOG(1)
      write(*,*) ' and INFOG(2) = ', dmumps_par%INFOG(2)
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) ''
	  call mpi_finalize(ierr)
      stop
    end if

    ! read solver settings and sizes (number of equations (degrees of freedom))
    open(newunit=ios, file='numgeo-ext-settings-'//trim(argument)//'.numgeo', form='formatted', access='sequential')
    read(ios,*) dmumps_par%N
    read(ios,*) dmumps_par%NNZ
    close(ios)

    ! allocate solver variables
    allocate(dmumps_par%RHS(dmumps_par%N ))

    allocate(dmumps_par%IRN(dmumps_par%NNZ))
    allocate(dmumps_par%JCN(dmumps_par%NNZ))
    allocate(dmumps_par%A(dmumps_par%NNZ))
    
    ! to evaluate time required by reading in the linear system
    if (print_times) call system_clock(time_start2)

    ! read in the left-hand-side
    open(newunit=ios, file='numgeo-ext-lhs-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
    read(ios) dmumps_par%A
    close(ios)

    ! read in the right-hand-side
    open(newunit=ios, file='numgeo-ext-rhs-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
    read(ios) dmumps_par%RHS
    close(ios)

    ! read in the index-array ja
    open(newunit=ios, file='numgeo-ext-ja-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
    read(ios) dmumps_par%JCN
    close(ios)

    ! read in the index-array ja
    open(newunit=ios, file='numgeo-ext-iacoo-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
    read(ios) dmumps_par%IRN
    close(ios)
    
    ! to evaluate time required by reading in the linear system
    if (print_times) call system_clock(time_end2)

  endif

  ! process id to which output messages should be printed
  !self%dmumps_par%icntl(1) = 0 !! print error messages
  !self%dmumps_par%icntl(2) = 0 !! print diagnostic and statistics messages
  !self%dmumps_par%icntl(3) = 0 !! print global information
  dmumps_par%icntl(2) = 0
  dmumps_par%icntl(3) = 0
  
  ! level of printing for error, warning, and diagnostic messages
  ! 0 : No messages output
  ! 1 : Only error messages
  ! 2 : Errors, warnings, and main statistics
  ! 3 : Errors and warnings and terse diagnostics (only first ten entries of arrays)
  ! 4 : Errors, warnings and information on input, output parameters
  self%dmumps_par%icntl(4) = 0

  ! tell mumps to use the scotch ordering library
  ! scotch -> 3
  ! metis  -> 5
  self%dmumps_par%icntl(7) = 3

  ! Scaling strategy
  ! -1: Scaling provided by the user. Scaling arrays must be provided in COLSCA and ROWSCA on entry to the numerical factorization phase
  ! 0 : No scaling applied/computed.
  ! 1 : Diagonal scaling computed during the numerical factorization phase,
  ! 3 : Column scaling computed during the numerical factorization phase,
  ! 4 : Row and column scaling based on infinite row/column norms, computed during the numerical
  ! factorization phase,
  ! 7 : Simultaneous row and column iterative scaling based on [41] and [15] computed during the numerical factorization phase.
  ! 8 : Similar to 7 but more rigorous
  ! 77 : Automatic choice of the value of ICNTL(8) done during analysis -> default
  ! self%dmumps_par%icntl(8) = 7

  ! tell mumps to perform the following steps:
  !  - ordering
  !  - factorisation
  !  - solve
  dmumps_par%JOB = 6

  ! Perform iterative refinement
  ! 0  -> Default value (no iterative refinement)
  ! <0 -> if the convergence test should not be done, MUMPS recommends to set ICNTL(10) to -2 or -3.
  ! >0 -> run XX steps of iterative refinement with stopping criterium
  self%dmumps_par%icntl(10) = 0

  ! compute statistics?
  ! 2 -> compute main statistics
  ! 0 -> default
  dmumps_par%icntl(11) = 0

  ! drop tolerance of pivoting
  ! In general, a larger value of CNTL(1) increases fill-in but leads to a more accurate factorization.
  ! Default value is 0.01. Common values are 0.01 < cntl(1) < 0.1
  self%dmumps_par%cntl(1) = 0.01d0

  call DMUMPS(dmumps_par)


  if (dmumps_par%MYID == 0) then

    ! evaluate possible errors
    if (dmumps_par%INFOG(1) < 0) then
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) 'ERROR in numgeo-mumps-mpi:'
      write(*,*) ''
      write(*,*) 'Mumps returned errors after solve: '
      write(*,*) 'INFOG(1) = ', dmumps_par%INFOG(1)
      write(*,*) ' and INFOG(2) = ', dmumps_par%INFOG(2)
      write(*,*) ''
      write(*,*) repeat('= ',20)
      stop
    end if

    ! write out statistics if requested
    if (dmumps_par%icntl(11) == 2) then
      !write(*,*) '  >>> Infinite norm of the input matrix: ', dmumps_par%RINFOG(4)
      write(*,*) '  >>> Infinite norm of the computed solution: ', dmumps_par%RINFOG(5)
      write(*,*) '  >>> Scaled residual: ', dmumps_par%RINFOG(6)
    end if

    open(newunit=ios, file='numgeo-ext-solution-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
    write(ios) dmumps_par%RHS
    close(ios)

    ! free memory
    deallocate(dmumps_par%IRN)
    deallocate(dmumps_par%JCN)
    deallocate(dmumps_par%A)
    deallocate(dmumps_par%RHS)

  endif


  ! Termination flag
  dmumps_par%JOB = -2

  ! terminate mumps
  call DMUMPS(dmumps_par)


  if (dmumps_par%MYID == 0)then
  
    ! evaluate possible errors
    if (dmumps_par%INFOG(1) < 0) then
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) 'ERROR in numgeo-mumps-mpi:'
      write(*,*) ''
      write(*,*) 'Mumps returned errors after termination: '
      write(*,*) 'INFOG(1) = ', dmumps_par%INFOG(1)
      write(*,*) ' and INFOG(2) = ', dmumps_par%INFOG(2)
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) ''
    end if
	
	if (print_times) then
      call system_clock(time_end)
      write(*,*) '...took a total of seconds:', (time_end-time_start)/rate
      write(*,*) '...reading s.o.e.:', (time_end2-time_start2)/rate
      write(*,*) 'Exit numgeo-mumps-mpi'
      write(*,*) ' '
    end if
	
  end if


  call mpi_finalize(ierr)
  
  ! On some architectures, mpi_finalize does not always terminate all processes. 
  ! mpi_abort seems to be more reliable in this regard
  ! call MPI_Abort(MPI_COMM_WORLD, errcode, ierr)
  stop


end program main
