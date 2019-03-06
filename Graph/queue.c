#include<stdio.h>
#include<stdlib.h>

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

int main() 
{ 
    Queue *q = create_Queue(); 
    enQueue(q, 10); 
    enQueue(q, 20); 
    deQueue(q); 
    printf("%d\n", deQueue(q)); 
    enQueue(q, 30); 
    enQueue(q, 40); 
    enQueue(q, 50);
    int n = deQueue(q);
    printf("%d\n", n);
}