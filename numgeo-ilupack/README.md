# numgeo-ilupack

Program that solves a linear system of equations given in coordinate format using the ilupack library. This software is part of the numgeo software developed by Jan Machacek and Patrick Staubach.

---

## Dependencies

**numgeo-ilupack** depends on the ilupack library. 
ILUPACK [1] is a library for Multilevel Incomplete LU factorization, developed by Matthias Bollhoefer (TU Braunschweig). 

It is freely available for scientific (non-commercial) use as a set of precompiled libraries from [[http://ilupack.tu-bs.de/]]. 
Currently only the use on Linux Systems is supported by ILUPACK.

## Building numgeo-ilupack
1. Download the ILUPACK library from [[http://ilupack.tu-bs.de/]]
2. Copy the required libraries from ilupack/lib/XX/ to numgeo-ilupack/lib.
   Therein, XX is the directory correpsonding to you compiler.
3. Open the Terminal in the numgeo-ilupack directory
4. Use make to build the executable:
   ```make clean
      make all```

## TODO

* Extend interface [solve_using_ilupack] such that it takes the ILUPACK settings as arguments


## References

[1] | 2012/1 ILUPACK
| Invited Book Chapter in Springer Encyclopedia of Parallel Computing, David Padua (Ed.), Springer, pp. 917-926, 2012. ISBN: 978-0-387-09765-7 DOI:10.1007/978-0-387-09766-4
| Author(s): J.I. Aliaga, M. Bollhöfer, A. Martin and E. Quintana-Orti.
