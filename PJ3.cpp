#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include "data_structures.h"
#include "heap.h"
#include "graph.h"

using namespace std; 

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        cout << "./PJ3 <InputFile> <GraphType> <Flag>" << endl; 
        exit(1); 
    }
    int is_directed = strcmp("DirectedGraph", argv[2]) == 0;
    Graph *graph_ = new Graph;
    graph_->adj_list  = new vector<vector<Edge*>*>; 
    graph_->vertex_list  = new vector<Vertex*>;
    graph_->path = new vector<int>;  
    makeGraph(argv[1], is_directed, atoi(argv[3]), graph_);
    char buf[100] = {0}; 
    while(fgets(buf, sizeof(buf), stdin))
    {
        // here, buf holds the request line
        char *inst = strtok(buf, " \n");
        if(strcmp(inst, "Stop") == 0)
            return 0; 
        else if(strcmp(inst, "SingleSource") == 0)
        {
            char *num1 = strtok(NULL, " \n");
            if(num1 == NULL)
                cout<< "Invalid Call to Single Source. Enter a source";
            else
                findSP(graph_, atoi(num1));
        }
        else if(strcmp(inst, "SinglePair") == 0)
        {
            char *num1 = strtok(NULL, " \n"); 
            if(num1 == NULL)
                cout << "Invalid Call to Single Pair. Enter source and target." << endl; 
            else
            {
                char *num2 = strtok(NULL, " \n");
                if(num2 == NULL)
                    cout << "Invalid Call to Single Pair. Enter source and target." << endl; 
                else
                {
                    findSP(graph_, atoi(num1)); 
                }
            }
        }
        else if(strcmp(inst, "PrintADJ") == 0)
        {
            printGraph(graph_, is_directed);
        }
        else if(strcmp(inst, "PrintPath") == 0)
        {
            char *num1 = strtok(NULL, " \n");
            if(num1 == NULL)
                cout << "Invalid call to PrintPath. Enter source and target." << endl;
            else
            {
                char *num2 = strtok(NULL, " \n"); 
                if(num2 == NULL)
                    cout << "Invalid call to PrintPath. Enter source and target." << endl;
                else
                    printPath(graph_, atoi(num1), atoi(num2));
            }                        
        }
        else if(strcmp(inst, "PrintLength") == 0)
        {
            char *num1 = strtok(NULL, " \n");
            if(num1 == NULL)
                cout << "Invalid call to PrintPath. Enter source and target." << endl;
            else
            {
                char *num2 = strtok(NULL, " \n"); 
                if(num2 == NULL)
                    cout << "Invalid call to PrintPath. Enter source and target." << endl;
                else
                    printLength(graph_, atoi(num1), atoi(num2));
            }                        

        }
        else
            cout << "Invalid Instruction:"  <<  endl;
    }
}


    /*
     *
    printGraph(graph_, is_directed);
    findSP(graph_, 1);
    printPath(graph_, 1, 2);
    printLength(graph_, 1, 2);  
     *
     *
     * */
