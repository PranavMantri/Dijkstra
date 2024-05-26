#ifndef HEAP_H
#define HEAP_H

void heapify(Heap *h, int index);
void buildHeap(Heap *h); 
void init(Heap *h, int cap);
void print(Heap *h, int phcount); 
void write(Heap *h, char *filename);
void read(Heap *h, char *filename); 
void insert(Heap *h, double in_key);
void insertHelper(Heap *h, int index); 
void insertVertex(Heap *h, Vertex *in);
void extractMin(Heap *h); 
void decreaseKey(Heap *h, int position, double newKey); 
void stop(Heap *h); 
#endif
