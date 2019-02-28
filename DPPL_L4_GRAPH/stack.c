#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node * next;
};

typedef struct node node;

node * create_stack()
{
    return NULL;
}

node * create_node (int key)
{
    node * temp = (node *)malloc(sizeof(node));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

void push(node ** root, int key)
{
    if (*root == NULL)
    {
        * root = create_node(key);
        return;
    }

    node * temp = create_node(key);
    temp -> next = *root;
    *root = temp;
    return;
}

int is_empty(node * root)
{
    if (root == NULL)
        return 1;
    return 0;
}

void pop(node ** root)
{
    if (!is_empty(*root))
    {
        node * temp_node = *root;
        *root = (*root) -> next;
        free(temp_node);
        return;
    }
}

int top(node ** root)
{
    if (!is_empty(*root))
    {
        int temp = (*root) -> key;
        return temp;
    }
}

int size(node * root)
{
    if (!is_empty(root))
    {
        node * temp = root;
        int count = 1;
        while(temp -> next != NULL)
        {
            count++;
            temp  = temp -> next;
        }
        return count;
    }
    return 0;
}

void print_stack(node * root)
{
    if (!is_empty(root))
    {
        node * temp = root;
        while (temp != NULL)
        {
            printf("%d\n", temp -> key);
            temp = temp -> next;
        }
        return;
    }
    printf("%s\n", "Stack Empty!");
}

int main()
{
    node * stack1 = create_stack();
    print_stack(stack1);
    push(&stack1, 27);
    print_stack(stack1);
    push(&stack1, 33);
    print_stack(stack1);
    printf("%d\t%d\n", top(&stack1), size(stack1));
    print_stack(stack1);
    pop(&stack1);
    print_stack(stack1);
    printf("%d\t%d\n", top(&stack1), size(stack1));
    print_stack(stack1);
    pop(&stack1);
    print_stack(stack1);
    pop(&stack1);
    print_stack(stack1);
    printf("%d\n", size(stack1));
}