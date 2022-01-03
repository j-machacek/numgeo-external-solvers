#ifndef _METIS_RENAME_OMP_H_
#define _METIS_RENAME_OMP_H_
/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * rename.h
 *
 * This file contains header files
 *
 * Started 10/2/97
 * George
 *
 * $Id: rename.h,v 1.1 2006-06-14 07:19:41 oschenk Exp $
 *
 */

#include "long_integer.h"


/* balance.c  */


/* bucketsort_omp.c  */
#define BucketSortKeysInc_ctrl		       METIS_BucketSortKeysInc_ctrl
#define BucketSortKeysInc_ctrl_omp	       METIS_BucketSortKeysInc_ctrl_omp


/* ccgraph.c  */
#define CreateCoarseGraph_modified             METIS_CreateCoarseGraph_modified	     
#define CreateCoarseGraph_modified_omp	       METIS_CreateCoarseGraph_modified_omp	     
#define CreateCoarseGraphNoMask_modified       METIS_CreateCoarseGraphNoMask_modified     
#define CreateCoarseGraphNoMask_modified_omp   METIS_CreateCoarseGraphNoMask_modified_omp 
#define SetUpCoarseGraph_modified              METIS_SetUpCoarseGraph_modified            


/* coarsen.c  */
#define Coarsen2Way_modified                   METIS_Coarsen2Way_modified


/* compress.c  */
#define CompressGraph_modified            METIS_CompressGraph_modified
#define CompressGraph_modified_omp        METIS_CompressGraph_modified_omp


/* debug.c  */


/* estmem.c  */
#define estmem_bisection                  METIS_estmem_bisection
#define estmem_pqueue                     METIS_estmem_pqueue
#define estmem_rdata                      METIS_estmem_rdata
#define estmem_subgraph                   METIS_estmem_subgraph
#define estmem_mlevelnesteddissection     METIS_estmem_mlevelnesteddissection
#define estmem_level1                     METIS_estmem_level1
#define estmem_graph                      METIS_estmem_graph
#define estmem_local                      METIS_estmem_local


/* fm.c  */


/* fortran.c  */
#define Change2CNumbering_modified        METIS_Change2CNumbering_modified     
#define Change2FNumberingOrder_modified	  METIS_Change2FNumberingOrder_modified


/* frename.c  */

/* graph.c  */
#define TestGraph          METIS_TestGraph	
#define TestPartition	   METIS_TestPartition	
#define TestCMap           METIS_TestCMap        


/* initpart.c  */
#define Init2WayPartition_modified   METIS_Init2WayPartition_modified
#define GrowBisection_modified       METIS_GrowBisection_modified    


/* kmetis.c  */


/* kvmetis.c  */


/* kwayfm.c  */


/* kwayrefine.c  */


/* kwayvolfm.c  */


/* kwayvolrefine.c  */


/* match.c  */
#define Match_RM_modified               METIS_Match_RM_modified	
#define Match_RM_modified_omp		METIS_Match_RM_modified_omp	
#define Match_SHEM_modified		METIS_Match_SHEM_modified	
#define Match_SHEM_modified_omp		METIS_Match_SHEM_modified_omp	
#define Match_SHEM_modified_omp2	METIS_Match_SHEM_modified_omp2


/* mbalance.c  */


/* mbalance2.c  */


/* mcoarsen.c  */


/* memory.c  */
#define graph_malloc                  METIS_graph_malloc	
#define idxgraph_malloc		      METIS_idxgraph_malloc	
#define graph_free		      METIS_graph_free	
#define idxgraph_free		      METIS_idxgraph_free	
#define idxgraph_realloc              METIS_idxgraph_realloc
#define allocate_memory 	      METIS_allocate_memory 
			


/* mesh.c  */


/* meshpart.c  */


/* mfm.c  */


/* mfm2.c  */


/* mincover.c  */


/* minitpart.c  */


/* minitpart2.c  */


/* mkmetis.c  */


/* mkwayfmh.c  */


/* mkwayrefine.c  */


/* mmatch.c  */


/* mmd.c  */


/* mpmetis.c  */


/* mrefine.c  */


/* mrefine2.c  */


/* mutil.c  */


/* myqsort.c  */
#define _pstack                 METIS__pstack 
#define pstack                  METIS_pstack
#define pstack_new              METIS_pstack_new
#define pstack_free             METIS_pstack_free
#define ikeysort_modified       METIS_ikeysort_modified
#define keybubblesort           METIS_keybubblesort
#define keyiqst_modified_queue  METIS_keyiqst_modified_queue
#define keyiqst_modified        METIS_keyiqst_modified


/* ometis.c  */
/* METIS_NodeND_modified
   METIS_NodeND_modified_ord */
#define MoveGraph                              METIS_MoveGraph				 
#define NodeND_modified_2		       METIS_NodeND_modified_2			
#define MoveGraph_omp			       METIS_MoveGraph_omp				
#define MlevelNestedDissection_modified_omp    METIS_MlevelNestedDissection_modified_omp	
#define MlevelNestedDissection_modified	       METIS_MlevelNestedDissection_modified		
#define MlevelNodeBisectionMultiple_modified   METIS_MlevelNodeBisectionMultiple_modified	
#define MlevelNodeBisection_modified	       METIS_MlevelNodeBisection_modified		
#define SplitGraphOrder_modified	       METIS_SplitGraphOrder_modified		
#define SplitGraphOrder_modified_omp	       METIS_SplitGraphOrder_modified_omp		


/* parmetis.c  */


/* pmetis.c  */
#define SetUpSplitGraph_modified       METIS_SetUpSplitGraph_modified


/* pqueue.c  */
#define PQueueInit_omp                  METIS_PQueueInit_omp
#define PQueueReset_omp                 METIS_PQueueReset_omp


/* refine_modified.c  */
#define Allocate2WayPartitionMemory_modified  METIS_Allocate2WayPartitionMemory_modified


/* separator.c  */
#define ConstructSeparator_modified           METIS_ConstructSeparator_modified


/* sfm.c  */
#define FM_2WayNodeRefine_OneSided_omp  METIS_FM_2WayNodeRefine_OneSided_omp
#define FM_2WayNodeBalance_omp          METIS_FM_2WayNodeBalance_omp
#define ComputeMaxNodeGain_omp          METIS_ComputeMaxNodeGain_omp


/* srefine.c  */
#define Compute2WayNodePartitionParams_omp       METIS_Compute2WayNodePartitionParams_omp
#define Refine2WayNode_modified                  METIS_Refine2WayNode_modified			 
#define Allocate2WayNodePartitionMemory_modified METIS_Allocate2WayNodePartitionMemory_modified 
#define Project2WayNodePartition_modified	 METIS_Project2WayNodePartition_modified	 
#define Project2WayNodePartition_modified_omp    METIS_Project2WayNodePartition_modified_omp    


/* stat.c  */


/* subdomains.c  */


/* timing.c  */
#define AddTimers			METIS_AddTimers
#define my_timer                        METIS_my_timer


/* util.c  */
#ifndef DMALLOC
#define idxsmalloc_omp           METIS_idxsmalloc_omp
#endif
#define idxset_omp               METIS_idxset_omp	 
#define idxsum_omp		 METIS_idxsum_omp	 
#define iincsort		 METIS_iincsort	 
#define incint			 METIS_incint		 
#define RandomPermute_omp	 METIS_RandomPermute_omp


/* ddecomp.c (new) */
#define ddecomp        METIS_ddecomp
#define MakeSymmetric  METIS_MakeSymmetric


#endif
