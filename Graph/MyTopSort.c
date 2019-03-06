#include<stdio.h>
#include <stdlib.h>
#define MAXVERTEX 20

typedef struct edge
{
	int endpoint;
	struct edge * nextedge;
}Edge;

typedef struct graph
{
	int n;
	Edge *firstedge[MAXVERTEX];
}Graph;


typedef int QueueEntry;

typedef struct queuenode
{
	QueueEntry qe;
	struct queuenode *next;
}QueueNode;

typedef struct queue
{
	QueueNode *front;
	QueueNode *rear;
}Queue;


struct queue * createQueue(Queue *q1)
{
	Queue * q = (struct queue *)malloc(sizeof(struct queue));
	q->front=NULL;
	q->rear=NULL;
	q1 = q;
	return(q1);
}

int QueueEmpty(Queue *q)
{
	if((q->front != NULL)   && ( (q->rear)!= NULL))
	{	
			return(0);
	}	
	return(1);
}


Queue* enqueue(QueueNode *p, Queue *q)
{
	if((QueueEmpty(q)) == 1)
	{
		q->front=p;
		q->rear=p;
	}
	else
	{
		if(q->rear == q->front)
		{
			q->rear->next = p;
			q->rear=p;
			q->front->next = q->rear;
				
		}
		else
		{
			q->rear->next = p;
			q->rear=p;
		}
	}
	return(q);	
}


Queue * dequeue(struct queuenode **p,Queue *q)
{
	if(!(QueueEmpty(q)))
	{
		*p = q->front;
		q->front = q->front->next;
		if(q->front == NULL)
		{
			q->rear = NULL;
		}
	}
	return(q);
}

void topsort(Graph G, int T[])
{
	Queue *Q;
	int v, i;
	int succ;
	Edge *curredge;
	int place;
	int k;
	int predecessorcount[MAXVERTEX];
	Q = createQueue(Q);
	for(k = 0; k < G.n ;k++)
	{
		v = G.firstedge[k]->endpoint;
		predecessorcount[v] = 0;
		
	}
	for(k=0; k < G.n ;k++)
	{
		curredge = G.firstedge[k];
		while (curredge)
		{
			if(curredge->endpoint != k)
			{
						predecessorcount[curredge->endpoint]++;
			}
			curredge=curredge->nextedge;
		}
	}

	for(k=0;k<G.n;k++)
	{
		v= G.firstedge[k]->endpoint;
		if(predecessorcount[v] == 0)
		{
			QueueNode * qn = (QueueNode *)malloc(sizeof(QueueNode));
			if(qn!= NULL)
			{
				qn->qe = v;
				qn->next=NULL;
				Q = enqueue(qn, Q);
			}
			else
			{
				printf("Error");
			}
		}
	}
	place = -1;
	while(!(QueueEmpty(Q)))
	{
		struct queuenode *qr = (struct queuenode*)malloc(sizeof(struct queuenode));
		Q = dequeue(&qr, Q);
		place++;
		*(T+place) = qr->qe;
		curredge = G.firstedge[qr->qe];
				
		if(place == (G.n-1) )
		{
			break;
		}
		while(curredge)
		{
			succ = 	curredge->endpoint;
			predecessorcount[succ]--;
			if(predecessorcount[succ]==0)
			{
				struct queuenode * qn = (struct queuenode *)malloc(sizeof(struct queuenode));
				qn->qe = succ;
				qn->next=NULL;
		
				Q = enqueue(qn, Q);
			}
			curredge = curredge->nextedge;
		}
	}		
}


Graph createGraph(int vertices)
{
    Graph  g;
	int i;
	g.n =  vertices;
   
    for (i = 0; i < vertices; i++)
    {
    	g.firstedge[i] = (Edge *)malloc(sizeof(Edge));
		g.firstedge[i]->endpoint = i;
	    g.firstedge[i]->nextedge = NULL;	
	}
	return g;
}
 
void addEdge(Graph graph, int src, int dest)
{
	
	struct edge *temp1, *prev, *temp;
	temp = graph.firstedge[src]->nextedge;
	if(temp == NULL)
	{
		temp1 =(Edge *) malloc(sizeof(Edge));
		temp1->endpoint = dest;
		temp1->nextedge = NULL;
		graph.firstedge[src]->nextedge = temp1;
	}
	else
	{
		prev = graph.firstedge[src]->nextedge;
		while(temp != NULL)
		{
			prev = temp;
			temp = temp->nextedge;
		}
		temp1 =(Edge *) malloc(sizeof(Edge));
		temp1->endpoint = dest;
		temp1->nextedge = NULL;
		prev->nextedge = temp1;
	}
	
}
 
void printGraph(Graph g)
{
    int v;int flag = 0;
	for (v = 0; v < g.n; v++)
    {
        struct edge* temp = g.firstedge[v];
        flag = 0;
        while ((temp != NULL) && (flag ==0)) 
        {
            if(temp->nextedge != NULL)
            {
				temp = temp->nextedge;
			}
			else
			{
				flag = 1;
			}
        }
    }
}

int main()
{
    int toporder[6],i;
	Graph graph = createGraph(6);
	addEdge(graph, 2, 3); 
    addEdge(graph, 3, 1); 
	addEdge(graph, 4, 0); 
    addEdge(graph, 4, 1); 
    addEdge(graph, 5, 2); 
    addEdge(graph, 5, 0); 
    printGraph(graph);
    topsort(graph, &toporder[0]);
	printf("Top order is");
	for(i=0;i<6;i++)
	{
		printf("\n%d", toporder[i]);
	}
	
	
	int toporder1[10];
	graph = createGraph(10);
	addEdge(graph, 6, 0); 
    addEdge(graph, 6, 2); 
	addEdge(graph, 6, 5); 
    addEdge(graph, 4, 2); 
    addEdge(graph, 4, 5); 
    addEdge(graph, 5, 7); 
    addEdge(graph, 3, 7);
    addEdge(graph, 3, 1);
    addEdge(graph, 1, 9);
    
    
    topsort(graph, &toporder1[0]);
	printf("Top order is");
	for(i=0;i<10;i++)
	{
		printf("\n%d", toporder1[i]);
	}
	
	
	
	return(0);
}




