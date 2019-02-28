#include<stdio.h>
#include<conio.h>

struct node
{
    int key;
    struct node * next;
};

typedef struct node node;

node * create_node (int key)
{
    node * temp = (node *)malloc(sizeof(node));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

