#ifndef HEAP_H
#define HEAP_H

/* takes a pointer to the heap and an index, and then modifies the heap such that
 * the given index roots a minheap. 
 * */
void heapify(Heap *h, int index);

/* takes a pointer to a heap, assuming it is unsorted, and performs the buildHeap operation to ensure a valid minHeap. 
 *
 * */
void buildHeap(Heap *h); 
/*
 * initializes a minheap with a capacity provided.
 * */
void init(Heap *h, int cap);

/*Prints the vector in sequentially (or level by level). 
 * phcount = 0 : don't print the number of heapify calls
 * phcount = 1 : print the number of heapify calls
 * */
void print(Heap *h, int phcount); 

 /*Given a char* to the name of the output file, prints out the heap vector sequentially (or level by level). 
  *
  * */
void write(Heap *h, char *filename);

/*Given a char* to the name of the input file, reads in heap capacity and heap elements and then calls buildHeap to
 * ensure a valid minHeap. 
 * */
void read(Heap *h, char *filename); 

/*Inserts an Element at the end of the heap vector with key = in_key, and then performs an insert operation to ensure the minHeap property remains: 
 *      acheived through recursively comparing the parent node with the current node until the minHeap rule is satisfied. 
 * */
void insert(Heap *h, double in_key);

/*Helper function for insert, which takes care of the recursive portion, checking the key of the Element at index, with Element's parent's key.  
 *
 */
void insertHelper(Heap *h, int index); 

/*behaves the same way as insert, but takes the vertex to be inserted instead of a key to be inserted into a new element created. 
 */
void insertVertex(Heap *h, Vertex *in);
/*
 * Extracts the min-value (the root) from the heap and then rebalances. this is achieved by placing the Element at the last position in the vector 
 * at the root position, and letting the Element sink to its valid position. 
 */
void extractMin(Heap *h);

/*Decreases the key of Element at position in heap iff position is valid and the new key is lesser than the current key.
 * */
void decreaseKey(Heap *h, int position, double newKey);

/*On calling stop, memory is cleared to ensure no memory leaks and program terminates.
 * */
void stop(Heap *h); 
#endif
