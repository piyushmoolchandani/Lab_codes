#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    int key;
    struct node * next;
}node;

node * create_node(int key)
{
    node * new_node = (node *)malloc(sizeof(node));
    new_node -> key = key;
    new_node -> next = NULL;
    return new_node;
}

node * create()
{
   return NULL;
}

void add(node ** set, int key)
{
    if (*set == NULL)
    {
        *set = create_node(key);
        return;
    }

    bool presence_flag = false;
    node * temp_root;

    for (temp_root = *set; temp_root != NULL; temp_root = temp_root -> next)
    {
        if (temp_root -> key == key)
        {
            printf("\n%d is already present in the set.", key);
            presence_flag = true;
            break;
        }
    }

    if (!presence_flag)
    {
        node * new_node = create_node(key);
        new_node -> next = *set;
        *set = new_node;
    }
    return;
}

void enumerate(node * set)
{
    node * temp_root = set;
    int count = 0;

    if (temp_root == NULL)
    {
        printf("\ns", "Set is empty.");
        return;
    }

    printf("%s", "\nElements in the set are: ");
    for (temp_root = set; temp_root != NULL; temp_root = temp_root -> next)
    {
        printf("\n%d", temp_root -> key);
        count ++;
    }

    printf("\nTotal keys present: %d", count);
    return;
}

int size(node * set)
{
    if (set == NULL)
    {
        return 0;
    }
    int count = 0;
    for (node * temp_root = set; temp_root != NULL; temp_root = temp_root -> next)
        count++;
    return count;
}

void removekey(node ** set, int key)
{
    node * temp_root = *set;
    node * backward_pointer;

    if (temp_root != NULL && temp_root -> key == key)
    {
        *set = temp_root -> next;
        free(temp_root);
        return;
    }

    while (temp_root != NULL && temp_root -> key != key)
    {
        backward_pointer = temp_root;
        temp_root = temp_root -> next;
    }

    if (temp_root == NULL)
    {
        printf("\n%s", "Key not found in the given set.");
        return;
    }

    backward_pointer -> next = temp_root -> next;
    free(temp_root);
    return;
}

int main()
{
    printf("%s", "Output:");
    node * set1 = create();
    add(&set1, 5);
    add(&set1, 4);
    add(&set1, 7);
    add(&set1, 5);
    add(&set1, 7);
    add(&set1, 9);
    add(&set1, 4);
    printf("\nSize : %d", size(set1));
    enumerate(set1);
    add(&set1, 33);
    add(&set1, 27);
    enumerate(set1);
    removekey(&set1, 6);
    removekey(&set1, 27);
    removekey(&set1, 7);
    removekey(&set1, 5);
    enumerate(set1);
}
