#ifndef _METIS_MACROS_OMP_H_
#define _METIS_MACROS_OMP_H_
/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * macros.h
 *
 * This file contains macros used in multilevel
 *
 * Started 9/25/94
 * George
 *
 * $Id: macros.h,v 1.1 1998/11/27 17:59:18 karypis Exp $
 *
 */

#include "long_integer.h"

/*************************************************************************
* The following macro returns a random number in the specified range
**************************************************************************/
#ifdef __VC__
#define RandomInRange_OMP(u) ((rand()>>3)%(u))    
#define RandomInRangeFast_OMP(u) ((rand()>>3)%(u))
/* #define RandomInRange_OMP(u) ((1234567890>>3)%(u))       */
/* #define RandomInRangeFast_OMP(u) ((1234567890>>3)%(u))   */
#else
#define RandomInRange_OMP(u) ((integer)(drand48()*((double)(u))))
#define RandomInRangeFast_OMP(u) ((rand()>>3)%(u))		 
/* #define RandomInRange_OMP(u) ((1234567890>>3)%(u))       */
/* #define RandomInRangeFast_OMP(u) ((1234567890>>3)%(u))   */
#endif

#endif
