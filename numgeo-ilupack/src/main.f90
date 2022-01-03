!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
!                                          numgeo
!                     Copyright (C) 2022 Jan Machacek, Patrick Staubach
!=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~=~
!
! PROGRAM: numgeo-ilupack
!
!> author: Jan Machacek, jan-machacek@outlook.com
!
!
!>### SUMMARY: 
!> Program that solves a linear system of equations given in coordinate format using the
!> ILUPACK library. This software is part of the numgeo software developed by
!> Jan Machacek and Patrick Staubach.
!
!
!>### REVISION HISTORY
!> 03.01.2022, J. Machacek - Initial version
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
  integer, parameter, public  :: i4 = selected_int_kind(9)                !< Range \([-2^{31},+2^{31} - 1]\), 10 digits plus sign; 32 bits.
end module precision_

program main
  use precision_
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
  integer(i4)                            :: ndof     !! number of dofs of the system of equations (soe)
  integer(i4)                            :: nonzeros !! number of nonzero entreis in A
  real(r8)   , allocatable, dimension(:) :: A        !! Jacobian of the soe (left-hand-side)
  real(r8)   , allocatable, dimension(:) :: r        !! residual of the soe (right-hand-side)
  integer(i4), allocatable, dimension(:) :: ia
  integer(i4), allocatable, dimension(:) :: ja
  real(r8)   , allocatable, dimension(:) :: solution
  
  ! other variables
  integer(i8) :: ios
  
  
  !call get_command(command_line)
  !argument = command_line(18:len(command_line))

  argument = trim("test_ilupack")

  if (print_times) then
    ! get initial system time
    CALL system_clock(count_rate=cr)
    rate = REAL(cr)
  end if
  
  if (print_times) then
    call date_and_time(TIME=time)
    write(*,*) 'Start numgeo-ilupack: ' // time
    call system_clock(time_start)
  end if


  ! read solver settings and sizes (number of equations (degrees of freedom))
  open(newunit=ios, file='numgeo-ext-settings-'//trim(argument)//'.numgeo', form='formatted', access='sequential')
  read(ios,*) ndof
  read(ios,*) nonzeros
  close(ios)

  ! allocate solver variables
  allocate(r(ndof), ia(ndof+1), ja(nonzeros), A(nonzeros), solution(ndof))
    
  ! to evaluate time required by reading in the linear system
  if (print_times) call system_clock(time_start2)

  ! read in the left-hand-side
  open(newunit=ios, file='numgeo-ext-lhs-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) A
  close(ios)

  ! read in the right-hand-side
  open(newunit=ios, file='numgeo-ext-rhs-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) r
  close(ios)

  ! read in the index-array ja
  open(newunit=ios, file='numgeo-ext-ja-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) ja
  close(ios)

  ! read in the index-array ia
  open(newunit=ios, file='numgeo-ext-ia-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  read(ios) ia
  close(ios)
    
  ! to evaluate time required by reading in the linear system
  if (print_times) call system_clock(time_end2)

  ! now solve the system of equations using ilupack
  call solve_using_ilupack(A,r,ia,ja,ndof,nonzeros, solution)

  ! report the solution back to numgeo
  open(newunit=ios, file='numgeo-ext-solution-'//trim(argument)//'.numgeo', form='unformatted',access='stream')
  write(ios) solution
  close(ios)

  ! free memory
  deallocate(r, ia, ja, A)
  
  if (print_times) then
    call system_clock(time_end)
    write(*,*) '...took a total of seconds:', (time_end-time_start)/rate
    write(*,*) '...reading s.o.e.:', (time_end2-time_start2)/rate
    write(*,*) 'Exit numgeo-ilupack'
    write(*,*) ' '
  end if

  
  contains
  
  !=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~~=~
  !
  !> author: Jan Machacek, jan-machacek@outlook.com
  !> date: 03.01.2021
  !
  ! Solves the system of equations using the ilupack library
  !
  !>### History
  !>* 03.01.2021, J. Machacek - Initial version
  !
  subroutine solve_using_ilupack(A,r,ia,ja,ndof,nonzeros, solution)
    use precision_
    implicit none
    
    ! sparse matrix in compressed sparse row format
    integer(i4)                     , intent(inout) :: ndof      !! number of dofs of the system of equations (soe)
    integer(i4)                     , intent(inout) :: nonzeros  !! number of nonzero entreis in A
    real(r8)   , dimension(nonzeros), intent(inout) :: A         !! Jacobian of the soe (left-hand-side)
    real(r8)   , dimension(ndof)    , intent(inout) :: r         !! residual of the soe (right-hand-side)
    integer(i4), dimension(ndof+1)  , intent(inout) :: ia
    integer(i4), dimension(nonzeros), intent(inout) :: ja
    
    real(r8)   , dimension(ndof)    , intent(out)   :: solution 
    
    ! local variables
    real(r8)   , dimension(nonzeros) :: A_tmp
    integer(i4), dimension(ndof+1)   :: ia_tmp
    integer(i4), dimension(nonzeros) :: ja_tmp
    
    ! ILUPACK variables
    integer  DGNLAMGfactor
    integer  DGNLAMGsolver
    integer  DGNLAMGnnz             !! logical number of nonzero entries of ILU
  
    ! ILUPACK external functions
    external DGNLAMGinit            !! init default parameter  
    external DGNLAMGsol             !! solve a single linear system with `PREC'        
    external DGNLAMGdelete          !! release memory
    external DGNLAMGfactor          !! compute multilevel ILU `PREC'
    external DGNLAMGsolver          !! solve linear system Ax=b iteratively using the ILUPACK preconditioner
    external DGNLAMGnnz             !! logical number of nonzero entries of ILU
    external DGNLAMGinfo            !! display multilevel structure
  
    ! ILUPACK external parameters
    integer         :: matching, maxit, lfil, lfilS, nrestart, ierr, mixedprecision, ind(ndof)
    character       :: ordering*20
    doubleprecision :: droptol, droptolS, condest, restol, elbow
    integer*8       :: param, PREC
    
    ! compute a copy of a (there are situations where this might be required since ILUPACK alters the input matrix)
    ia_tmp = ia
    ja_tmp = ja
    A_tmp  = A  
    
    ! ----------------------------------------
    ! ILUPACK initialize default parameters 
    ! ----------------------------------------
    
    call DGNLAMGinit(ndof, ia_tmp, ja_tmp, A_tmp, matching, ordering, droptol, droptolS, condest, restol,  &
                     maxit, elbow, lfil, lfilS, nrestart, mixedprecision, ind)
                     
                     
    ! ----------------------------------------
    ! ILUPACK settings
    ! ----------------------------------------
    
    ! multilevel orderings
    ! 'amd' (default) Approximate Minimum Degree
    ! 'mmd'           Minimum Degree            
    ! 'rcm'           Reverse Cuthill-McKee
    ! 'metisn'        Metis multilevel nested dissection by nodes
    ! 'metise'        Metis multilevel nested dissection by edges
    ! 'pq'            ddPQ strategy by Saad
    ordering = 'amd'
    
    ! threshold for ILU, default: 1e-2
    droptol = 1d-10
    
    ! threshold for the approximate Schur complements, default: 0.1*droptol
    droptolS = 0.1*droptol
    
    ! norm bound for the inverse factors L^{-1}, U^{-1}, default: 10
    condest = 10d0
    
    ! relative error for the backward error (SPD case: relative energy norm) used during the iterative solver
    ! default: sqrt(eps)
    restol = 1d-6
    
    ! maximum number of iterative steps, default: 500
    maxit = 1000
    
    ! elbow space factor for the relative fill w.r.t. the given matrix, computed during the ILU, default: 10
    ! this value only gives a recommendation for the elbow space. ILUPACK will adapt this value automatically
    elbow = 10
    
    ! maximum number of nonzeros per column in L/ row in U, default: n+1
    ! lfil = 10 * (nnz/(1.0*n))
    
    ! maximum number of nonzeros per row in the approximate Schur complement, default: n+1
    ! lfilS = 10 * (nnz/(1.0*n))
    
    ! restart length for GMRES, default: 30
    nrestart = 40
    
    ! do you want to use a single precision preconditioner
    mixedprecision = 0
    
    ! underlying block structure, only partially supported. default: right now turn it off!
    ind(:) = 0
    
    
    ! ----------------------------------------
    ! ILUPACK compute multilevel ILU
    ! ----------------------------------------
    
    ! Note that the initial input matrix A will be rescaled by rows and by columns (powers of 2.0) and that the 
    ! order in the array might have been altered. If you do need the original matrix (ia,ja,a) in for different purposes,
    ! you should use a copy (ib,jb,b) instead compute multilevel ILU `PREC'
    ierr = DGNLAMGfactor(param, PREC, ndof, ia_tmp, ja_tmp, A_tmp, matching, ordering, droptol, droptolS,   &
                         condest, restol, maxit, elbow, lfil, lfilS, nrestart, mixedprecision, ind)
    
    ! print some information
    call DGNLAMGinfo(param, PREC, ndof, ia_tmp, ja_tmp, A_tmp)
    
    ! check for errors
    if (ierr /= 0) then
    
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) 'ERROR in numgeo-ilupack:'
      write(*,*) ''
    
      if (ierr == -1) then
        write (6,'(A)') 'Error. input matrix may be wrong.'
      elseif (ierr ==  -2) then
        write (6,'(A)') 'matrix L overflow, increase elbow and retry'
      elseif (ierr ==  -3) then
        write (6,'(A)') 'matrix U overflow, increase elbow and retry'
      elseif (ierr ==  -4) then
        write (6,'(A)') 'Illegal value for lfil'
      elseif (ierr ==  -5) then
        write (6,'(A)') 'zero row encountered'
      elseif (ierr ==  -6) then
        write (6,'(A)') 'zero column encountered'
      elseif (ierr ==  -7) then
        write (6,'(A)') 'buffers are too small'
      elseif (ierr.ne.0) then
        write (6,'(A,I3)') 'zero pivot encountered at step number', ierr
      endif
      
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) ''
      
      stop
      
    end if
    
    
    ! ----------------------------------------
    ! ILUPACK solve the linear system iteratively
    ! ----------------------------------------
    
    ! provide an initial solution, e.g. 0
    solution = 0.0_r8
    
    ! solve the system using the restartet GMRES solver build in in ILUPACK
    ierr = DGNLAMGsolver(param, PREC, r, solution, ndof, ia_tmp, ja_tmp, A_tmp, matching, ordering, &
                         droptol, droptolS, condest, restol, maxit, elbow, lfil, lfilS, nrestart,   &
                         mixedprecision, ind)
                         
    ! check for errors
    if (ierr /= 0) then
    
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) 'ERROR in numgeo-ilupack:'
      write(*,*) ''
    
      if (ierr ==  -1) then
         write (6,'(A)') 'too many iteration steps'
      elseif (ierr ==  -2) then
         write (6,'(A)') 'not enough work space'
      elseif (ierr ==  -3) then
         write (6,'(A)') 'algorithm breaks down'
      end if
      
      write(*,*) ''
      write(*,*) repeat('= ',20)
      write(*,*) ''
      
      stop
      
    end if
                         
                         
    ! ----------------------------------------
    ! ILUPACK release memory
    ! ----------------------------------------
    
    call DGNLAMGdelete(param, PREC)


  end subroutine solve_using_ilupack


end program main
