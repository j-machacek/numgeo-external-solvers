/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * proto.h
 *
 * This file contains header files
 *
 * Started 10/19/95
 * George
 *
 * $Id: proto.h,v 1.2 2006-10-31 13:17:06 oschenk Exp $
 *
 */

/* balance.c  */


/* bucketsort.c  */
void BucketSortKeysInc_ctrl(CtrlType *, integer, integer, idxtype *, idxtype *, idxtype *);
void BucketSortKeysInc_ctrl_omp(CtrlType *, integer, integer, idxtype *, idxtype *, idxtype *);


/* ccgraph.c  */
integer CreateCoarseGraph_modified(CtrlType *, GraphType *, integer, idxtype *, idxtype *);
integer CreateCoarseGraph_modified_omp(CtrlType *, GraphType *, integer, idxtype *, idxtype *);
integer CreateCoarseGraphNoMask_modified(CtrlType *, GraphType *, integer, idxtype *, idxtype *);
integer CreateCoarseGraphNoMask_modified_omp(CtrlType *, GraphType *, integer, idxtype *, idxtype *);
GraphType *SetUpCoarseGraph_modified(CtrlType *, GraphType *, integer, integer);
void ReAdjustMemory_modified(CtrlType *, GraphType *graph, GraphType *cgraph, integer dovsize);


/* coarsen.c  */
GraphType *Coarsen2Way_modified(CtrlType *, GraphType *, integer *);


/* compress.c  */
integer CompressGraph_modified(CtrlType *, GraphType *, integer, idxtype *, idxtype *, idxtype *, idxtype *, integer, integer);
integer CompressGraph_modified_omp(CtrlType *, GraphType *, integer, idxtype *, idxtype *, idxtype *, idxtype *, integer, integer);


/* debug.c  */


/* estmem.c  */
integer estmem_bisection( integer nvtxs, integer nedges, double vfactor, double efactor );
integer estmem_pqueue( integer nvtxs );
integer estmem_rdata( integer nvtxs );
integer estmem_subgraph( integer nvtxs, integer nedges );
integer estmem_mlevelnesteddissection( integer nvtxs, integer nedges, double vfactor, double efactor );
integer estmem_level1( integer nvtxs, integer nedges, integer compressed );
integer estmem_graph( integer nvtxs, integer nedges, integer nproc, 
		      double vfactor, double efactor, integer compressed ) ;
integer estmem_local( integer nvtxs, integer nedges, integer nproc, double vfactor);


/* fm.c  */


/* fortran.c  */
void Change2CNumbering_modified(integer, idxtype *, idxtype *);
void Change2FNumberingOrder_modified(integer, idxtype *, idxtype *, idxtype *, idxtype *);


/* frename.c  */
void METIS_NODEND_modified_ord(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize, integer* ordering, integer* mmdswitch, integer *error, float* ubfactor);
void metis_nodend_modified_ord(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize,  integer* ordering, integer* mmdswitch, integer *error, float* ubfactor);
void metis_nodend_modified_ord_(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize,  integer* ordering, integer* mmdswitch, integer *error, float* ubfactor);
void metis_nodend_modified_ord__(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize,  integer* ordering, integer* mmdswitch, integer *error, float* ubfactor);
void METIS_NODEND_MODIFIED(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize, integer *error);
void METIS_NODEND_modified(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize, integer *error);
void metis_nodend_modified(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize, integer *error);
void metis_nodend_modified_(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize, integer *error);
void metis_nodend_modified__(integer *nvtxs, idxtype *xadj, idxtype *adjncy, integer *numflag, integer *options, idxtype *perm, idxtype *iperm, integer *nproc, integer *ddist, integer *ddistsize, integer *error);


/* graph.c  */
void TestGraph( GraphType *, char * );
void TestPartition( GraphType *, char * );
void TestCMap( GraphType *graph, integer cnvtxs, char *msg );


/* initpart.c  */
integer Init2WayPartition_modified(CtrlType *, GraphType *, integer *, float);
integer GrowBisection_modified(CtrlType *, GraphType *, integer *, float);


/* kmetis.c  */


/* kvmetis.c  */

/* kwayfm.c  */


/* kwayrefine.c  */


/* kwayvolfm.c  */


/* kwayvolrefine.c  */


/* match.c  */
integer Match_RM_modified(CtrlType *, GraphType *, integer *);
integer Match_RM_modified_omp(CtrlType *, GraphType *, integer *);
integer Match_SHEM_modified(CtrlType *, GraphType *, integer *);
integer Match_SHEM_modified_omp(CtrlType *, GraphType *, integer *);
integer Match_SHEM_modified_omp2(CtrlType *ctrl, GraphType *graph, integer *numthreads);


/* mbalance.c  */


/* mbalance2.c  */


/* mcoarsen.c  */


/* memory.c  */
void    *graph_malloc(CtrlType *, integer);
idxtype *idxgraph_malloc(CtrlType *, integer);
void    graph_free(CtrlType *, integer);
void    idxgraph_free(CtrlType *, integer);
void    idxgraph_realloc(CtrlType *, integer, integer);
integer allocate_memory(CtrlType *, integer, integer, integer, 
			double, double, integer);


/* mesh.c  */


/* meshpart.c  */


/* mfm.c  */


/* mfm2.c  */


/* mincover.o  */


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


/* mutil. c */


/* myqsort.c  */
struct _pstack
{
    KeyValueType** start;
    KeyValueType** end;
    integer* weight;
    integer len;
    integer size;
};

typedef struct _pstack pstack;

static pstack* pstack_new( integer size );
static void pstack_free( pstack* stack );
void ikeysort_modified(integer n, KeyValueType *baseglobal, integer nproc);
static void keybubblesort(KeyValueType *base, KeyValueType *max);
static void keyiqst_modified_queue(KeyValueType *base, KeyValueType *max, pstack* stack); 
static void keyiqst_modified(KeyValueType *base, KeyValueType *max, pstack* stack);


/* ometis.c  */
void MoveGraph( CtrlType *ctrl, GraphType *graph, idxtype size );
void METIS_NodeND_modified(integer *, idxtype *, idxtype *, integer *, integer *, idxtype *, idxtype *, integer *, integer *, integer *, integer *); 
void METIS_NodeND_modified_ord(integer *, idxtype *, idxtype *, integer *, integer *, idxtype *, idxtype *, integer *, integer *, integer *, integer *, integer *, integer *, float*); 
integer NodeND_modified_2(integer *, idxtype *, idxtype *,  integer *, idxtype *, idxtype *, integer *, integer *, integer *, double , double, integer, integer, float,integer );
void MoveGraph_omp( CtrlType *ctrl, GraphType *graph, idxtype size );
integer MlevelNestedDissection_modified_omp(CtrlType *ctrl, GraphType *graph,
					    CtrlType ctrl_array[], GraphType graph_array[], 
					    integer *countnparts, idxtype *order, float ubfactor, 
					    integer lastvtx, integer *ddist, integer ddist_start, 
					    integer ddist_width, integer depth,
					    integer *memory_subgraphs, integer *pos_memory_subgraphs );
integer MlevelNestedDissection_modified(CtrlType *ctrl, GraphType *graph, idxtype *order, 
					float ubfactor, integer lastvtx, 
					integer *ddist, integer ddist_start, integer ddist_width);
integer MlevelNodeBisectionMultiple_modified(CtrlType *ctrl, GraphType *graph, integer *tpwgts, float ubfactor);
integer MlevelNodeBisection_modified(CtrlType *ctrl, GraphType *graph, integer *tpwgts, float ubfactor);
integer SplitGraphOrder_modified(CtrlType *ctrl, GraphType *graph, GraphType *lgraph, 
				 GraphType *rgraph, integer graphspace);
integer SplitGraphOrder_modified_omp(CtrlType *ctrl, GraphType *graph, 
				     GraphType *lgraph, GraphType *rgraph, integer graphspace);


/* parmetis.c  */


/* pmetis.c  */
integer SetUpSplitGraph_modified(CtrlType *, GraphType *, GraphType *, integer, integer, integer);


/* pqueue.c  */
void PQueueInit_omp(CtrlType *ctrl, PQueueType *queue, integer maxnodes, integer maxgain);
void PQueueReset_omp(PQueueType *queue);


/* refine_modified.c  */
integer Allocate2WayPartitionMemory_modified(CtrlType *, GraphType *);


/* separator.c  */
integer ConstructSeparator_modified(CtrlType *, GraphType *, float);


/* sfm.c  */
void FM_2WayNodeRefine_OneSided_omp(CtrlType *, GraphType *, float, integer);
void FM_2WayNodeBalance_omp(CtrlType *, GraphType *, float);
integer ComputeMaxNodeGain_omp(integer, idxtype *, idxtype *, idxtype *, integer);


/* srefine.c  */
integer Refine2WayNode_modified(CtrlType *, GraphType *, GraphType *, float);
integer Allocate2WayNodePartitionMemory_modified(CtrlType *, GraphType *);
void Compute2WayNodePartitionParams_omp(CtrlType *, GraphType *);
integer Project2WayNodePartition_modified(CtrlType *, GraphType *);
integer Project2WayNodePartition_modified_omp(CtrlType *, GraphType *);


/* stat.c  */


/* subdomains.c  */


/* timing.c  */
void AddTimers(CtrlType *, CtrlType *);
double my_timer(void);


/* util.c  */
#ifndef DMALLOC
idxtype *idxsmalloc_omp(integer, idxtype, char *);
#endif
/* void GKfree(void *, ...); */
idxtype *idxset_omp(integer n, idxtype val, idxtype *x);
integer idxsum_omp(integer, idxtype *, integer);
void iincsort(integer n, integer *a);
static int incint(const void *v1, const void *v2);
void RandomPermute_omp(integer n, idxtype *p, integer flag);


/* ddecomp.c (new) */
void ddecomp(integer *nrows, integer *rowptr, integer *colind, integer *nparts, integer *perm, integer *iperm, integer *ddist, integer *olcut);
void MakeSymmetric(integer nrows, integer *rowptr, integer *colind, integer **_xadj, integer **_adjncy);
