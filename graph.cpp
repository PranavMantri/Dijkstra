#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cfloat>
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
using namespace std;
void die(string s){ cerr<< s << endl; exit(1);}
void makeGraph(char *filename, int is_Direct, int flag, Graph *graph_)
{
    FILE *fp = fopen(filename, "rb"); 
    if(fp == NULL)
        die("Bad Filename");
    char buf[100] = {0}; 
    fgets(buf, sizeof(buf), fp); 
    char tok [10] = {0}; 
    int num_i = 0;
    double num_d = 0; 
    char delimit[] = " \n"; 
    int num_vtx = atoi(strtok(buf, delimit)); 
    int num_edg = atoi(strtok(NULL, delimit));

    for(int i = 0; i<num_vtx; i++)
    {
        Vertex *x = new Vertex;
        x->index = x->position = i;
        x->pi = -1; 
        x->color = 0;
        x->key = DBL_MAX;   
        vector<Edge*> *vec_e = new vector<Edge*>;  
        graph_->adj_list->push_back(vec_e); 
        graph_->vertex_list->push_back(x); 

    }
    memset(buf, 0, sizeof(buf)); 
    while(fgets(buf, sizeof(buf), fp))
    {
        Edge *in_edge = new Edge; 
        in_edge->index = atoi(strtok(buf, delimit))-1;
        in_edge->u = atoi(strtok(NULL, delimit))-1; 
        in_edge->v = atoi(strtok(NULL, delimit))-1; 
        in_edge->w = atof(strtok(NULL, delimit));
        insertEdge(in_edge, is_Direct, flag, graph_);
        memset(buf, 0, sizeof(buf)); 
    }
    fclose(fp); 
       
}
void insertEdge(Edge *in_edge, int is_Direct, int flag, Graph *graph_)
{
    int u = in_edge->u; 
    auto list_u = graph_->adj_list->at(u);
   
    if(is_Direct)
    {
        if(flag == 1)
        {
            list_u->insert(list_u->begin(), in_edge);
        }
        else if (flag == 2)
        {
            list_u->push_back(in_edge);
        }
    }
    else 
    {
        int v = in_edge->v; 
        auto list_v = graph_->adj_list->at(v);
        if(flag == 1)
        {
            list_u->insert(list_u->begin(), in_edge);
            list_v->insert(list_v->begin(), in_edge);
        }
        else if (flag ==2)
        {
            list_u->push_back(in_edge);
            list_v->push_back(in_edge);
        }
    }
}

void findSP(Graph *graph_, int source, int target)
{
    source = source -1;
    target = target -1; 
    if(source > graph_->vertex_list->size()|| source<0)
    {
        cout << "source DNE" << endl; return;
    }

    for(int i =0; i< graph_->vertex_list->size(); i++)
    {
        graph_->vertex_list->at(i)->key = DBL_MAX;
        graph_->vertex_list->at(i)->pi = -1;
        graph_->vertex_list->at(i)->color = 0;  
    }
    Heap *h = new Heap; 
    init(h, graph_->vertex_list->size());
    graph_->vertex_list->at(source)->key = 0;
    insertVertex(h, graph_->vertex_list->at(source)); 
    Vertex *currnode ; 

    while(h->A.size() !=0)
    {
        currnode = h->A.at(0);
        currnode->color = 2;
        extractMin(h);
        if(currnode->index == target)
        {
            stop(h); 
            return;
        }
        double sumDist = currnode->key; 
        auto adj_list = graph_->adj_list->at(currnode->index);

        for(int i =0; i<adj_list->size(); i++)
        { 
            if(adj_list->at(i)->u != currnode->index)
            {
                auto in = graph_->vertex_list->at(adj_list->at(i)->u);
               // cerr << in->color << endl; 
                if(in->color == 0)
                {
                    in->key = sumDist + adj_list->at(i)->w; 
                    in->color = 1;
                    in->pi = currnode->index; 
                    insertVertex(h, in);
                }
                else if(in->color == 1)
                {
                    if(sumDist + adj_list->at(i)->w < in->key)
                    {
                        in->pi = currnode->index; 
                        decreaseKey(h, find(h->A.begin(), h->A.end(), in)- h->A.begin(), sumDist + adj_list->at(i)->w); 
                    }
                } 
            }
            else
            {
                auto in = graph_->vertex_list->at(adj_list->at(i)->v);
               // cerr << in->color << endl;
                if(in->color == 0)
                {
                    in->key = sumDist + adj_list->at(i)->w; 
                    in->color = 1;
                    in->pi = currnode->index; 
                    insertVertex(h, in);
                }
                else if(in->color == 1)
                {
                    if(sumDist + adj_list->at(i)->w < in->key)
                    {
                        in->pi = currnode->index;
                        decreaseKey(h, find(h->A.begin(), h->A.end(), in)- h->A.begin(), sumDist + adj_list->at(i)->w); 
                    }
                } 
            }
        }
    }
    stop(h); 

}

void printGraph(Graph *graph_, int is_directed)
{
    int u = 0;
    int v = 0; 
    double w = 0;
    for(int i =0; i<graph_->adj_list->size(); i++)
    {
        if(graph_->adj_list->at(i)->size() >0)
            printf("ADJ[%d]:", i+1); 
        for(int j =0; j<graph_->adj_list->at(i)->size(); j++)
        {
            v = graph_->adj_list->at(i)->at(j)->v+1;
            u = graph_->adj_list->at(i)->at(j)->u+1; 
            w = graph_->adj_list->at(i)->at(j)->w;

            if (v == i+1)
            {
                int temp = u; 
                u = v; 
                v = temp; 
            }
            printf("-->[%d %d: %.2f]", u, v, w);
        }

        if(graph_->adj_list->at(i)->size() >0)
            cout << endl;
    }
}
void printPath(Graph *graph_, int source, int target)
{
    if(graph_->vertex_list->at(target-1)->pi == -1)
        cout << "There is no path from " << source << " to " << target << "." <<endl; 
    else
    {
        int p = graph_->vertex_list->at(target-1)->pi; 
        int loc = target-1;
        graph_->path->clear(); 
        while(p!=-1)
        {
       //     cerr << p << endl;
            graph_->path->insert(graph_->path->begin(), loc);
            loc = p; 
            p = graph_->vertex_list->at(loc)->pi;

        }
        cout << "The shortest path from " << source << " to " << target << " is:" << endl;
        printf("[%d: %7.2f]", source, graph_->vertex_list->at(source-1)->key);
        for(int i = 0; i<graph_->path->size(); i++)
            printf("-->[%d: %7.2f]", graph_->path->at(i)+1, graph_->vertex_list->at(graph_->path->at(i))->key);
        cout <<"."<<  endl; 

    } 
}
void printLength(Graph *graph_, int source, int target)
{
    if(graph_->vertex_list->at(target-1)->pi == -1)
        cout << "There is no path from " << source << " to " << target << "." << endl; 
    else
        printf("The length of the shortest path from %d to %d is: %8.2f\n", source, target, graph_->vertex_list->at(target-1)->key);
}

void graph_stop(Graph *graph_)
{
    graph_->adj_list->clear();
    graph_->vertex_list->clear();
    graph_->path->clear(); 
    delete graph_;
}
