#include<stdio.h>
#include<stdlib.h>
#define n 4


/** Queue ----------------------------------------------------------------------------------------------**/
struct qnode
{
    int key;
    struct qnode * next;
};

typedef struct qnode qnode;

qnode * create_node (int key)
{
    qnode * temp = (qnode *)malloc(sizeof(qnode));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

typedef struct Queue 
{ 
    struct qnode *front, *rear; 
}Queue;

Queue *create_Queue() 
{ 
    Queue *q = (Queue*)malloc(sizeof(Queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 
  
void enQueue(Queue *q, int k) 
{ 
    qnode *temp = create_node(k); 
   
    if (q->rear == NULL) 
    { 
       q->front = q->rear = temp; 
       return; 
    } 
   
    q->rear->next = temp; 
    q->rear = temp; 
} 

int is_emptyq(Queue *q)
{
    if (q -> front == NULL)
        return 1;
    return 0;
} 

int deQueue(Queue *q) 
{ 
    if (!is_emptyq(q))
    {
        qnode *temp = q->front;
        int temp_int = temp -> key;
        q->front = q->front->next;
   
        if (q->front == NULL) 
            q->rear = NULL; 
        free(temp);
        return temp_int;
    }
} 
/** -------------------------------------------------------------------------------------------------------**/

void scan_arr(int a[])
{
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void print_arr(int a[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void scan_mat(int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

void print_mat(int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int ** create()
{
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(n * sizeof(int));
    
    return mat;
}

int find_index(int var, int m[])
{
    for (int i = 0; i < n; i++)
    {
        if (m[i] == var)
        {
            return i;
        }
    }
    return -1;
}

void bfs(int a[], int ** adj, int index)
{
    Queue* p = create_Queue();
    int visited[n] = {0};
    enQueue(p, a[index]);
    while(!is_emptyq(p))
    {
        int temp = deQueue(p);
        int temp_index = find_index(temp, a);
        if (visited[temp_index] == 1)
            continue;

        printf("%d\t", temp);
        visited[temp_index] = 1;
        
        for (int i = 0; i < n; i++)
        {
            if (adj[temp_index][i] != 0)
            {
                if (visited[i] != 1)
                {
                    enQueue(p, a[i]);
                }
            }
        }
    }
}

int main()
{
    int arr[n];
    scan_arr(arr);
    print_arr(arr);
    int ** mat = create();
    scan_mat(mat);
    print_mat(mat);
    bfs(arr, mat, 2);
}