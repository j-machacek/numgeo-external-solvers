# numgeo-mumps-mpi

Program that solves a linear system of equations given in coordinate format using the mpi-version of the mumps solver. This software is part of the numgeo software developed by Jan Machacek and Patrick Staubach.

---

## Dependencies

**numgeo-mumps-mpi** depends on the MUMPS solver library. However in order to build the mpi version of the MUMPS solver, additional libraries are required:

1. MUMPS --> <http://mumps.enseeiht.fr/>
1. BLAS/LAPACK 
2. Scalapack
3. Scotch

### MPI

To build this application you need one of the MPI libraries. So far we have used openmpi and recommend it as well.

```shell
sudo apt-get update
sudo apt-get install openmpi-bin
```

### Building MUMPS

#### BLAS/LAPACK

For this purpose we use the OpenBLAS library (any other Blas/Lapack library is possible, e.g. ATLAS), which can be obtained from the repository

```shell
sudo apt-get install libopenblas-serial-dev
```
	
#### Scalapack

On Ubuntu you can obtain a precompiled version of Scalapack for openmpi from the repository:

```shell
sudo apt-get install libscalapack-openmpi-dev
```

This version comes with its own BLACS library.

## Building numgeo-mumps-mpi

Use the make file to build numgeo-mumps-mpi
