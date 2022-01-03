#ifndef _METIS_RENAME_H_
#define _METIS_RENAME_H_

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
 * $Id: rename.h,v 1.1 1998/11/27 17:59:29 karypis Exp $
 *
 */

#include "long_integer.h"


/* balance.c */
#define Balance2Way			METIS_Balance2Way
#define Bnd2WayBalance			METIS_Bnd2WayBalance
#define General2WayBalance		METIS_General2WayBalance


/* bucketsort.c */
#define BucketSortKeysInc		METIS_BucketSortKeysInc


/* ccgraph.c */
#define CreateCoarseGraph		METIS_CreateCoarseGraph
#define CreateCoarseGraphNoMask		METIS_CreateCoarseGraphNoMask
#define CreateCoarseGraph_NVW 		METIS_CreateCoarseGraph_NVW
#define SetUpCoarseGraph		METIS_SetUpCoarseGraph
#define ReAdjustMemory			METIS_ReAdjustMemory


/* coarsen.c */
#define Coarsen2Way			METIS_Coarsen2Way


/* compress.c */
#define CompressGraph			METIS_CompressGraph
#define PruneGraph			METIS_PruneGraph


/* debug.c */
#define ComputeCut			METIS_ComputeCut
#define CheckBnd			METIS_CheckBnd
#define CheckBnd2			METIS_CheckBnd2
#define CheckNodeBnd			METIS_CheckNodeBnd
#define CheckRInfo			METIS_CheckRInfo
#define CheckNodePartitionParams	METIS_CheckNodePartitionParams
#define IsSeparable			METIS_IsSeparable


/* estmem.c */
#define EstimateCFraction		METIS_EstimateCFraction
#define ComputeCoarseGraphSize		METIS_ComputeCoarseGraphSize


/* fm.c */
#define FM_2WayEdgeRefine		METIS_FM_2WayEdgeRefine


/* fortran.c */
#define Change2CNumbering		METIS_Change2CNumbering
#define Change2FNumbering		METIS_Change2FNumbering
#define Change2FNumbering2		METIS_Change2FNumbering2
#define Change2FNumberingOrder		METIS_Change2FNumberingOrder
#define ChangeMesh2CNumbering		METIS_ChangeMesh2CNumbering
#define ChangeMesh2FNumbering		METIS_ChangeMesh2FNumbering
#define ChangeMesh2FNumbering2		METIS_ChangeMesh2FNumbering2


/* graph.c */
#define SetUpGraph			METIS_SetUpGraph
#define SetUpGraphKway 			METIS_SetUpGraphKway
#define SetUpGraph2			METIS_SetUpGraph2
#define VolSetUpGraph			METIS_VolSetUpGraph
#define RandomizeGraph			METIS_RandomizeGraph
#define IsConnectedSubdomain		METIS_IsConnectedSubdomain
#define IsConnected			METIS_IsConnected
#define IsConnected2			METIS_IsConnected2
#define FindComponents			METIS_FindComponents


/* initpart.c */
#define Init2WayPartition		METIS_Init2WayPartition
#define InitSeparator			METIS_InitSeparator
#define GrowBisection			METIS_GrowBisection
#define GrowBisectionNode		METIS_GrowBisectionNode
#define RandomBisection			METIS_RandomBisection


/* kmetis.c */
#define MlevelKWayPartitioning		METIS_MlevelKWayPartitioning


/* kvmetis.c */
#define MlevelVolKWayPartitioning	METIS_MlevelVolKWayPartitioning


/* kwayfm.c */
#define Random_KWayEdgeRefine		METIS_Random_KWayEdgeRefine
#define Greedy_KWayEdgeRefine		METIS_Greedy_KWayEdgeRefine
#define Greedy_KWayEdgeBalance		METIS_Greedy_KWayEdgeBalance


/* kwayrefine.c */
#define RefineKWay			METIS_RefineKWay
#define AllocateKWayPartitionMemory	METIS_AllocateKWayPartitionMemory
#define ComputeKWayPartitionParams	METIS_ComputeKWayPartitionParams
#define ProjectKWayPartition		METIS_ProjectKWayPartition
#define IsBalanced			METIS_IsBalanced
#define ComputeKWayBoundary		METIS_ComputeKWayBoundary
#define ComputeKWayBalanceBoundary	METIS_ComputeKWayBalanceBoundary


/* kwayvolfm.c */
#define Random_KWayVolRefine		METIS_Random_KWayVolRefine
#define Random_KWayVolRefineMConn	METIS_Random_KWayVolRefineMConn
#define Greedy_KWayVolBalance		METIS_Greedy_KWayVolBalance
#define Greedy_KWayVolBalanceMConn	METIS_Greedy_KWayVolBalanceMConn
#define KWayVolUpdate			METIS_KWayVolUpdate
#define ComputeKWayVolume		METIS_ComputeKWayVolume
#define ComputeVolume			METIS_ComputeVolume
#define CheckVolKWayPartitionParams	METIS_CheckVolKWayPartitionParams
#define ComputeVolSubDomainGraph	METIS_ComputeVolSubDomainGraph
#define EliminateVolSubDomainEdges	METIS_EliminateVolSubDomainEdges


/* kwayvolrefine.c */
#define RefineVolKWay			METIS_RefineVolKWay
#define AllocateVolKWayPartitionMemory	METIS_AllocateVolKWayPartitionMemory
#define ComputeVolKWayPartitionParams	METIS_ComputeVolKWayPartitionParams
#define ComputeKWayVolGains		METIS_ComputeKWayVolGains
#define ProjectVolKWayPartition		METIS_ProjectVolKWayPartition
#define ComputeVolKWayBoundary		METIS_ComputeVolKWayBoundary
#define ComputeVolKWayBalanceBoundary	METIS_ComputeVolKWayBalanceBoundary


/* match.c */
#define Match_RM			METIS_Match_RM
#define Match_RM_NVW			METIS_Match_RM_NVW
#define Match_HEM			METIS_Match_HEM
#define Match_SHEM			METIS_Match_SHEM


/* mbalance.c */
#define MocBalance2Way			METIS_MocBalance2Way
#define MocGeneral2WayBalance		METIS_MocGeneral2WayBalance


/* mbalance2.c */
#define MocBalance2Way2			METIS_MocBalance2Way2
#define MocGeneral2WayBalance2		METIS_MocGeneral2WayBalance2
#define SelectQueue3			METIS_SelectQueue3


/* mcoarsen.c */
#define MCCoarsen2Way			METIS_MCCoarsen2Way


/* memory.c */
#define AllocateWorkSpace		METIS_AllocateWorkSpace
#define FreeWorkSpace			METIS_FreeWorkSpace
#define WspaceAvail			METIS_WspaceAvail
#define idxwspacemalloc			METIS_idxwspacemalloc
#define idxwspacefree			METIS_idxwspacefree
#define fwspacemalloc			METIS_fwspacemalloc
#define CreateGraph			METIS_CreateGraph
#define InitGraph			METIS_InitGraph
#define FreeGraph			METIS_FreeGraph


/* mesh.c */
#define TRIDUALMETIS			METIS_TRIDUALMETIS
#define TETDUALMETIS			METIS_TETDUALMETIS
#define HEXDUALMETIS			METIS_HEXDUALMETIS
#define TRINODALMETIS			METIS_TRINODALMETIS
#define TETNODALMETIS			METIS_TETNODALMETIS
#define HEXNODALMETIS			METIS_HEXNODALMETIS


/* mfm.c */
#define MocFM_2WayEdgeRefine		METIS_MocFM_2WayEdgeRefine
#define SelectQueue			METIS_SelectQueue
#define BetterBalance			METIS_BetterBalance
#define Compute2WayHLoadImbalance	METIS_Compute2WayHLoadImbalance
#define Compute2WayHLoadImbalanceVec	METIS_Compute2WayHLoadImbalanceVec


/* mfm2.c */
#define MocFM_2WayEdgeRefine2		METIS_MocFM_2WayEdgeRefine2
#define SelectQueue2			METIS_SelectQueue2
#define IsBetter2wayBalance		METIS_IsBetter2wayBalance


/* mincover.c */
#define MinCover			METIS_MinCover
#define MinCover_Augment		METIS_MinCover_Augment
#define MinCover_Decompose		METIS_MinCover_Decompose
#define MinCover_ColDFS			METIS_MinCover_ColDFS
#define MinCover_RowDFS			METIS_MinCover_RowDFS


/* minitpart.c */
#define MocInit2WayPartition		METIS_MocInit2WayPartition
#define MocGrowBisection		METIS_MocGrowBisection
#define MocRandomBisection		METIS_MocRandomBisection
#define MocInit2WayBalance		METIS_MocInit2WayBalance
#define SelectQueueoneWay		METIS_SelectQueueoneWay


/* minitpart2.c */
#define MocInit2WayPartition2		METIS_MocInit2WayPartition2
#define MocGrowBisection2		METIS_MocGrowBisection2
#define MocGrowBisectionNew2		METIS_MocGrowBisectionNew2
#define MocInit2WayBalance2		METIS_MocInit2WayBalance2
#define SelectQueueOneWay2		METIS_SelectQueueOneWay2


/* mkmetis.c */
#define MCMlevelKWayPartitioning	METIS_MCMlevelKWayPartitioning


/* mkwayfmh.c */
#define MCRandom_KWayEdgeRefineHorizontal	METIS_MCRandom_KWayEdgeRefineHorizontal
#define MCGreedy_KWayEdgeBalanceHorizontal	METIS_MCGreedy_KWayEdgeBalanceHorizontal
#define AreAllHVwgtsBelow			METIS_AreAllHVwgtsBelow
#define AreAllHVwgtsAbove			METIS_AreAllHVwgtsAbove
#define ComputeHKWayLoadImbalance		METIS_ComputeHKWayLoadImbalance
#define MocIsHBalanced				METIS_MocIsHBalanced
#define IsHBalanceBetterFT			METIS_IsHBalanceBetterFT
#define IsHBalanceBetterTT			METIS_IsHBalanceBetterTT


/* mkwayrefine.c */
#define MocRefineKWayHorizontal		METIS_MocRefineKWayHorizontal
#define MocAllocateKWayPartitionMemory	METIS_MocAllocateKWayPartitionMemory
#define MocComputeKWayPartitionParams	METIS_MocComputeKWayPartitionParams
#define MocProjectKWayPartition		METIS_MocProjectKWayPartition
#define MocComputeKWayBalanceBoundary	METIS_MocComputeKWayBalanceBoundary


/* mmatch.c */
#define MCMatch_RM			METIS_MCMatch_RM
#define MCMatch_HEM			METIS_MCMatch_HEM
#define MCMatch_SHEM			METIS_MCMatch_SHEM
#define MCMatch_SHEBM			METIS_MCMatch_SHEBM
#define MCMatch_SBHEM			METIS_MCMatch_SBHEM
#define BetterVBalance			METIS_BetterVBalance
#define AreAllVwgtsBelowFast		METIS_AreAllVwgtsBelowFast


/* mmd.c */
#define genmmd				METIS_genmmd
#define mmdelm				METIS_mmdelm
#define mmdint				METIS_mmdint
#define mmdnum				METIS_mmdnum
#define mmdupd				METIS_mmdupd


/* mpmetis.c */
#define MCMlevelRecursiveBisection	METIS_MCMlevelRecursiveBisection
#define MCHMlevelRecursiveBisection	METIS_MCHMlevelRecursiveBisection
#define MCMlevelEdgeBisection		METIS_MCMlevelEdgeBisection
#define MCHMlevelEdgeBisection		METIS_MCHMlevelEdgeBisection


/* mrefine.c */
#define MocRefine2Way			METIS_MocRefine2Way
#define MocAllocate2WayPartitionMemory	METIS_MocAllocate2WayPartitionMemory
#define MocCompute2WayPartitionParams	METIS_MocCompute2WayPartitionParams
#define MocProject2WayPartition		METIS_MocProject2WayPartition


/* mrefine2.c */
#define MocRefine2Way2			METIS_MocRefine2Way2


/* mutil.c */
#define AreAllVwgtsBelow		METIS_AreAllVwgtsBelow
#define AreAnyVwgtsBelow		METIS_AreAnyVwgtsBelow
#define AreAllVwgtsAbove		METIS_AreAllVwgtsAbove
#define ComputeLoadImbalance		METIS_ComputeLoadImbalance
#define AreAllBelow			METIS_AreAllBelow


/* myqsort.c */
#define iidxsort			METIS_iidxsort
#define iintsort			METIS_iintsort
#define ikeysort			METIS_ikeysort
#define ikeyvalsort			METIS_ikeyvalsort


/* ometis.c */
#define MlevelNestedDissection		METIS_MlevelNestedDissection
#define MlevelNestedDissectionCC	METIS_MlevelNestedDissectionCC
#define MlevelNodeBisectionMultiple	METIS_MlevelNodeBisectionMultiple
#define MlevelNodeBisection		METIS_MlevelNodeBisection
#define SplitGraphOrder			METIS_SplitGraphOrder
#define MMDOrder			METIS_MMDOrder
#define RCMOrder			METIS_RCMOrder
#define AMDOrder			METIS_AMDOrder
#define CAMDOrder			METIS_CAMDOrder
#define SplitGraphOrderCC		METIS_SplitGraphOrderCC
#define metis_rcm_impl                  METIS_metis_rcm_impl                           
#define metis_quicksort_int_int         METIS_metis_quicksort_int_integer		


/* parmetis.c */
#define MlevelNestedDissectionP		METIS_MlevelNestedDissectionP


/* pmetis.c */
#define MlevelRecursiveBisection	METIS_MlevelRecursiveBisection
#define MlevelEdgeBisection		METIS_MlevelEdgeBisection
#define SplitGraphPart			METIS_SplitGraphPart
#define SetUpSplitGraph			METIS_SetUpSplitGraph


/* pqueue.c */
#define PQueueInit			METIS_PQueueInit
#define PQueueReset			METIS_PQueueReset
#define PQueueFree			METIS_PQueueFree
#define PQueueInsert			METIS_PQueueInsert
#define PQueueDelete			METIS_PQueueDelete
#define PQueueUpdate			METIS_PQueueUpdate
#define PQueueUpdateUp			METIS_PQueueUpdateUp
#define PQueueGetMax			METIS_PQueueGetMax
#define PQueueSeeMax			METIS_PQueueSeeMax
#define CheckHeap			METIS_CheckHeap


/* refine.c */
#define Refine2Way			METIS_Refine2Way
#define Allocate2WayPartitionMemory	METIS_Allocate2WayPartitionMemory
#define Compute2WayPartitionParams	METIS_Compute2WayPartitionParams
#define Project2WayPartition		METIS_Project2WayPartition


/* separator.c */
#define ConstructSeparator		METIS_ConstructSeparator
#define ConstructMinCoverSeparator0	METIS_ConstructMinCoverSeparator0
#define ConstructMinCoverSeparator	METIS_ConstructMinCoverSeparator


/* sfm.c */
#define FM_2WayNodeRefine		METIS_FM_2WayNodeRefine
#define FM_2WayNodeRefineEqWgt		METIS_FM_2WayNodeRefineEqWgt
#define FM_2WayNodeRefine_OneSided	METIS_FM_2WayNodeRefine_OneSided
#define FM_2WayNodeBalance		METIS_FM_2WayNodeBalance
#define ComputeMaxNodeGain		METIS_ComputeMaxNodeGain


/* srefine.c */
#define Refine2WayNode			METIS_Refine2WayNode
#define Allocate2WayNodePartitionMemory	METIS_Allocate2WayNodePartitionMemory
#define Compute2WayNodePartitionParams	METIS_Compute2WayNodePartitionParams
#define Project2WayNodePartition	METIS_Project2WayNodePartition


/* stat.c */
#define ComputePartitionInfo		METIS_ComputePartitionInfo
#define ComputePartitionBalance		METIS_ComputePartitionBalance
#define ComputeElementBalance		METIS_ComputeElementBalance


/* subdomains.c */
#define Random_KWayEdgeRefineMConn	METIS_Random_KWayEdgeRefineMConn
#define Greedy_KWayEdgeBalanceMConn	METIS_Greedy_KWayEdgeBalanceMConn
#define PrintSubDomainGraph		METIS_PrintSubDomainGraph
#define ComputeSubDomainGraph		METIS_ComputeSubDomainGraph
#define EliminateSubDomainEdges		METIS_EliminateSubDomainEdges
#define MoveGroupMConn			METIS_MoveGroupMConn
#define EliminateComponents		METIS_EliminateComponents
#define MoveGroup			METIS_MoveGroup


/* timing.c */
#define InitTimers			METIS_InitTimers
#define PrintTimers			METIS_PrintTimers
#define seconds				METIS_seconds


/* util.c */
#define errexit				METIS_errexit
#define GKfree				METIS_GKfree
#ifndef DMALLOC
#define imalloc				METIS_imalloc
#define idxmalloc			METIS_idxmalloc
#define fmalloc				METIS_fmalloc
#define ismalloc			METIS_ismalloc
#define idxsmalloc			METIS_idxsmalloc
#define GKmalloc			METIS_GKmalloc
#endif
#define iset				METIS_iset
#define idxset				METIS_idxset
#define sset				METIS_sset
#define iamax				METIS_iamax
#define idxamax				METIS_idxamax
#define idxamax_strd			METIS_idxamax_strd
#define samax				METIS_samax
#define samax2				METIS_samax2
#define idxamin				METIS_idxamin
#define samin				METIS_samin
#define idxsum				METIS_idxsum
#define idxsum_strd			METIS_idxsum_strd
#define idxadd				METIS_idxadd
#define charsum				METIS_charsum
#define isum				METIS_isum
#define ssum				METIS_ssum
#define ssum_strd			METIS_ssum_strd
#define sscale				METIS_sscale
#define snorm2				METIS_snorm2
#define sdot				METIS_sdot
#define saxpy			        METIS_saxpy
#define RandomPermute			METIS_RandomPermute
#define ispow2				METIS_ispow2
#define InitRandom			METIS_InitRandom
#define log2				METIS_log2





#endif
