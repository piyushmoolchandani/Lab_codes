#include <limits.h> 
#include <stdio.h> 
#include<stdlib.h>
#include <omp.h>
#include <sys/time.h>
#define V 1000

double timedifference(struct timeval t0, struct timeval t1)
{
    return ((t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f) * 1000;
}

double minDistance(double dist[], bool sptSet[]) 
{ 
    double min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
void dijkstra(double graph[V][V], int src) 
{ 
    double dist[V]; 
  
    bool sptSet[V];
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
  
    dist[src] = 0; 
  
    for (int count = 0; count < V - 1; count++) { 
        int u = minDistance(dist, sptSet); 
  
        sptSet[u] = true; 
  
        for (int v = 0; v < V; v++) 
  
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) 
                dist[v] = dist[u] + graph[u][v]; 
    }  
} 
  
void parallel_dijkstra(double graph[V][V], int src) 
{ 
    double dist[V]; 
  
    bool sptSet[V];
    #pragma omp parallel for
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
  
    dist[src] = 0; 
  
    for (int count = 0; count < V - 1; count++) { 
        int u = minDistance(dist, sptSet); 
  
        sptSet[u] = true; 
  
  		#pragma omp parallel for
        for (int v = 0; v < V; v++) 
  
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) 
                dist[v] = dist[u] + graph[u][v]; 
    }
    //printSolution(dist);
}
  
int main() 
{ 
    double graph[V][V];
    for (int i = 0; i < V; i++){
    	for (int j = 0; j < V; j++){
    		int edge = rand() % 2;
    		if (edge){
    			graph[i][j] = (double)(rand() % 100)/(double)(rand() % 20 + 1);
    		}
    		else{
    			graph[i][j] = 0.0;
    		}
    	}
    }
  	struct timeval start_time, end_time;
  	gettimeofday(&start_time, 0);
    dijkstra(graph, 0); 
    gettimeofday(&end_time, 0);
    printf("Linear Time: %f\n", timedifference(start_time, end_time));
    
    gettimeofday(&start_time, 0);
    parallel_dijkstra(graph, 0);
    gettimeofday(&end_time, 0);
    printf("Parallel Time: %f\n", timedifference(start_time, end_time));
    return 0; 
} 

