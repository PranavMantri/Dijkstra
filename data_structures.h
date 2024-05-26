#ifndef _data_structures_h
#define _data_structures_h
#include <vector>
using namespace std;

typedef struct TAG_VERTEX{
    int index;
    int color;
    double key; 
    int pi; 
    int position; 
}Vertex; 
typedef Vertex Element;

typedef struct TAG_HEAP {
    int capacity; /* capacity of the heap */
    vector<Element *> A; /* array of pointers to ELEMENT */
    int hcount; 
    // other fields as you see fit
}Heap;


typedef struct TAG_EDGE{
    int index; 
    int u;
    int v; 
    double w; 
}Edge; 

typedef struct TAG_GRAPH {
    vector <vector<Edge *>*> *adj_list; 
    vector <Vertex *> *vertex_list;
    vector <int> *path; 
    int source; 
    int target;
    int created; 
}Graph; 
#endif
