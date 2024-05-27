#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include "data_structures.h"
using namespace std;


void heapify(Heap *h, int index)
{
    if(!h)
    {
        cerr<< "Heap is Null" << endl; 
        return; 
    }
    if(index<0)
        return;

    h->hcount+=1;
    int left = index*2+1; 
    int right = index*2+2;
    int min = index; 

    if(left < h->A.size() && h->A.at(left)->key < h->A.at(min)->key)
    {
        min = left; 
    }
    if(right < h->A.size() && h->A.at(right)->key < h->A.at(min)->key)
    {
        min = right; 
    }
    if(min != index) // we need to swap
    {
        auto mtemp = h->A.at(min); 
        h->A.at(min) = h->A.at(index); 
        h->A.at(index) = mtemp; 
        h->A.at(min)->position = min; 
        h->A.at(index)->position = index; 
        heapify(h, min); 
    }

}

void buildHeap(Heap *h)
{
    if(!h) 
    {
        cerr << "ERROR: Heap is Null" << endl;
        return; 
    }
    for(int i = (h->A.size()-1)/2; i>= 0; i--)
    {
        heapify(h, i); 
    }

}




//done
void init(Heap *h, int cap)
{
    h->capacity = cap; 
    h->hcount = 0;
}



// print out the heap level by level (in order of array)
void print(Heap *h, int phcount)
{
    if(!h)
    {
        cerr << "Heap is NULL" << endl; 
        return;
    }

    if(phcount)
        printf("Number of Heapify calls: %d\n", h->hcount);

    cout<< h->A.size() <<endl;
    if(h->A.size()>0)
    { 
        for(int i = 0; i<h->A.size(); i++)
            printf("%lf\n", h->A.at(i)->key);
    }
}


// open file and do print
void write(Heap *h, char *filename)
{
    if (!h)
    {
        cerr<< "Heap is NULL" << endl; 
        return; 
    }
    FILE* fp = fopen(filename, "wb");
    if(fp == NULL)
    {
        cerr<< "Invalid Filename" << endl; 
        return;
    }

    fprintf(fp, "%d\n", (int) h->A.size());
    if(h->A.size() >0)
    { 
        for(int i = 0; i<h->A.size(); i++)
            fprintf(fp, "%lf\n", h->A.at(i)->key);
    }
    fclose(fp); 
}


//open file and read in values through (insert)
void read(Heap *h, char *filename)
{
    //open file and basically create heap from that. call BuildHeap
    if(!h)
    {
        cout<< "Heap is Null" << endl; 
        return; 
    }
    FILE *fp = fopen(filename, "rb"); 
    if(fp == NULL)
    {
       cerr<< "Invalid filename" << endl; 
       return; 
    }
    h->A.clear();
    char buf[10] = {0}; 
    double tempK =0;
    fscanf(fp, "%s", buf); 
    memset(buf, 0, sizeof(buf));
    int poscount = 0; 
    while(fscanf(fp, "%s", buf)!= EOF)
    {
        tempK = atoi(buf);
        Element *in = new Element; 
        in->key = tempK;
        in->position = poscount++;  
        h->A.push_back(in); 
        memset(buf, 0, sizeof(buf)); 
    }
    buildHeap(h); 
    fclose(fp);     
}



void insertHelper(Heap *h, int index)
{
    if(index>0)
    {
        if(h->A.at(index)->key < h->A.at((index-1)/2)->key)
        {
            auto temp = h->A.at(index); 
            h->A.at(index) = h->A.at((index-1)/2); 
            h->A.at((index-1)/2) = temp;
            h->A.at(index)->position = index; 
            h->A.at((index-1)/2)->position = (index-1)/2; 
            insertHelper(h, (index-1)/2); 
        }
    }
}
void insert(Heap *h, double in_key)
{
    if(!h)
    {
        cerr<< "Error: Heap is NULL" << endl; 
        return; 
    }
    if(h->A.size() == h->capacity)
    {
        cerr << "Error: Heap is full" << endl;
        return; 
    }

    Element *in = new Element;
    in->key = in_key;
    in->position = h->A.size(); 
    h->A.push_back(in); 
    insertHelper(h, h->A.size()-1); 
}

void insertVertex(Heap *h, Vertex *in)
{
    if(!h)
    {
        cerr<< "Error: Heap is NULL" << endl; 
        return; 
    }
    if(h->A.size() == h->capacity)
    {
        cerr << "Error: Heap is full" << endl;
        return; 
    }

    in->position = h->A.size();
    h->A.push_back(in); 
    insertHelper(h, h->A.size()-1); 
}
void extractMin(Heap *h)
{
    if(!h)
    {
        cerr << "Error: Heap is NULL" << endl; 
        return; 
    }
    if(h->A.size() == 0)
    {
        cerr << "Error: Heap is Empty" << endl; 
        return; 
    }

    auto temp = h->A.at(0); 
    h->A.at(0) = h->A.at(h->A.size()-1); 
    h->A.at(h->A.size()-1) = temp;
    //fprintf(stdout, "ExtractMin: %lf\n", h->A.at(h->A.size()-1)->key);
    h->A.pop_back();
    heapify(h, 0);
}

void decreaseKey(Heap *h, int position, double newKey)
{
    if(!h)
    {
        cerr << "Error: Heap is NULL" << endl; 
        return; 
    }
    if(h->A.size() == 0)
    {
        cerr << "Error: Heap is Empty" << endl; 
        return; 
    }
   // position = position-1;// this is commented out since in a direct minheap implemenetation, position is 1-based
    if(position> h->A.size() || position < 0 || newKey >= h->A.at(position)->key)
    {
        cerr << "Error: Invalid call to DecreaseKey" << endl;
        return; 
    }
    h->A.at(position)->key = newKey; 
    insertHelper(h, position); 
     
}
void stop(Heap *h)
{
  h->A.clear();
  delete h;   
}
