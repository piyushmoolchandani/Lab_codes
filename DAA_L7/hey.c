#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
struct Edge 
{ 
    int src, dest, weight; 
}; 
 
struct Graph 
{ 
    int V, E; 
  
    struct Edge* edge; 
}; 
  
struct Graph* createGraph(int V, int E) 
{ 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
  
    graph->edge = new Edge[E]; 
  
    return graph; 
} 
