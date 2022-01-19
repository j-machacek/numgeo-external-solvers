# numgeo-pastix

Program that solves a linear system of equations given in coordinate format using the PaStiX library (see https://gitlab.inria.fr/solverstack/pastix).

> Many thanks to Mathieu Faverge (mathieu.faverge@inria.fr) from INRIA helping us setting up PaStiX! 

This software is part of the numgeo software developed by Jan Machacek and Patrick Staubach.

---

## Dependencies

**numgeo-pastix** depends on the PaStiX library. 

PaStiX (Parallel Sparse matriX package) is a scientific library that provides a high performance parallel solver for very large sparse linear systems based on direct methods.  
Numerical algorithms are implemented in single or double precision (real or complex) using LLt, LDLt and LU with static pivoting (for non symmetric matrices having a symmetric pattern).
This solver also provides some low-rank compression methods to reduce the memory footprint and/or the time-to-solution.

## Building numgeo-pastix
1. Get PaStiX from [https://gitlab.inria.fr/solverstack/pastix]
2. Build the PaStix library following the instruction given in [https://solverstack.gitlabpages.inria.fr/pastix/md_docs_doxygen_chapters_Pastix_Install.html]
	* We used the following flags:
	    * CMAKE_BUILD_TYPE=Release
	    * DPASTIX_INT64=OFF
		* DPASTIX_WITH_FORTRAN=ON
		* DPASTIX_ORDERING_SCOTCH=ON
	* For the StarPU-version, you require the StarPU-library. On debian-based distributions StarPU can be installed from the repository:
		```
		apt-cache search starpu
		sudo apt-get install libstarpu-1.3 libstarpu-dev
		```
3. Copy the PaStiX library to numgeo-pastix/lib
4. Copy the files "pastix_enums.F90" and "pastixf.f90" from pastix/wrappers/fortran90/src/ to numgeo-pastix/Dir/src/ and replace the old ones
5. Copy the files "spm_enums.F90" and "spmf.f90" from pastix/spm/fortran90/src/ to numgeo-pastix/Dir/src/ and replace the old ones
6. Open the Terminal in the numgeo-pastix directory
7. Use make to build the executable:
   ```
   make clean
   make all
   ```

>Note: Dir corresponds to the version of numgeo-pastix you want to build: the serial version (Dir=serial) or the StarPU-version (Dir=starpu)

## Known Bugs

* Currently PaStiX can't be used in calculations where all degrees of freedoms are constraint, e.g. if you want to simulate a "Geostatic step" with all nodes fixed in space. In such cases, this particular analysis step has to be solved using another solver, e.g. MUMPS. All other steps in the analysis can then be solved using PaStiX.


## PaStiX with runtime support

We testet three versions of PasTiX:
1. Serial version of PaStiX
2. PaStiX with runtime support based on StarPU with openMP (MPI diabled)

### PaStiX with runtime support based on StarPU with openMP

When configuring StarPU use the following command: ```../configure --prefix=${STARPU_DIR} --enable-openmp --disable-mpi```


## TODO

* Create GPU-Version of the library


## References

[1] Pascal Hénon, Pierre Ramet, Jean Roman. Pascal Hénon, Pierre Ramet, Jean Roman. PaStiX: A High-Performance Parallel Direct Solver for Sparse Symmetric Definite Systems. Parallel Computing, Elsevier, 2002, 28 (2), pp.301--321. INRIA HAL

[2] Pascal Hénon, Pierre Ramet, Jean Roman. On finding approximate supernodes for an efficient ILU(k) factorization. Parallel Computing, Elsevier, 2008, 34, pp.345--362. INRIA HAL

[3] Grégoire Pichon, Mathieu Faverge, Pierre Ramet, Jean Roman. Reordering Strategy for Blocking Optimization in Sparse Linear Solvers. SIAM Journal on Matrix Analysis and Applications, Society for Industrial and Applied Mathematics, 2017, SIAM Journal on Matrix Analysis and Applications, 38 (1), pp.226 - 248. INRIA HAL

[4] Grégoire Pichon, Eric Darve, Mathieu Faverge, Pierre Ramet, Jean Roman. Sparse supernodal solver using block low-rank compression: Design, performance and analysis. International Journal of Computational Science and Engineering, Inderscience, 2018, 27, pp.255 - 270. 10.1016/J.JOCS.2018.06.007 Inria HAL
