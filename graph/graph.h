#ifndef GRAPH_H
#define GRAPH_H
#include "data_structures.h"
void makeGraph(char *filename, int is_Direct, int flag, Graph *graph_);
void insertEdge(Edge *in_edge, int is_Direct, int flag, Graph *graph_);
void findSP(Graph *graph_, int source);
void printGraph(Graph *graph_, int is_directed);
void printPath(Graph *graph_, int source, int target);
void printLength(Graph *graph_, int source, int target);
#endif
