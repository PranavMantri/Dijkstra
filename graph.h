#ifndef GRAPH_H
#define GRAPH_H
#include "data_structures.h"

/* called from main, and takes a filename, a binary value to indicate whether the graph is directed 
 * or not, a flag (either 1 or 2 inputted as an argument when the executable is run), and a pointer to the Graph struct.
 * then, it reads in the graph from the file edge by edge and creates the graph by initializing and populating fields 
 * in the Graph struct. 
 * */
void makeGraph(char *filename, int is_Direct, int flag, Graph *graph_);

/*
 *called by makeGraph, inserts the given edge in the appropriate locations for the adjacency lists in Graph struct. 
 * */
void insertEdge(Edge *in_edge, int is_Direct, int flag, Graph *graph_);

/*called from main, finds the shortest path from source to target. if target = -1, finds the shortest path to all nodes.
 * */
void findSP(Graph *graph_, int source, int target);

/*called from main, prints the graph in the form of adjacency lists for each vertex from 1->n.
 * */
void printGraph(Graph *graph_, int is_directed);

/*prints the path from the source to the target.
 * */
void printPath(Graph *graph_, int source, int target);

/*prints the length of the path from the source to target. 
 * */
void printLength(Graph *graph_, int source, int target);

/*handles the garbage collection and cleanUp of the program on stop
 * */
void graph_stop(Graph *graph_);
#endif
