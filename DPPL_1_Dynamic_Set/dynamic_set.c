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

node * add(node * set, int key)
{
    if (set == NULL)
    {
        set = create_node(key);
        return set;
    }

    bool presence_flag = false;
    node * temp_root;

    for (temp_root = set; temp_root != NULL; temp_root = temp_root -> next)
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
        new_node -> next = set;
        set = new_node;
    }
    return set;
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

    printf("\nTotal %d keys are present.", count);
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

node * removekey(node * set, int key)
{
    node * temp_root = set; node * backward_pointer;
    if (set != NULL && temp_root -> key == key)
    {
        set = temp_root -> next;
        free(temp_root);
        return set;
    }
    while (temp_root != NULL || temp_root -> key != key)
    {
        backward_pointer = temp_root;
        temp_root = temp_root -> next;
    }

    if (temp_root == NULL)
        printf("\n%s", "Key not found in the given set.");
        return set;

    backward_pointer -> next = temp_root -> next;
    free(temp_root);
    return set;
}

int main()
{
    printf("%s", "Output:");
    node * set1 = create();
    set1 = add(set1, 5);
    set1 = add(set1, 4);
    set1 = add(set1, 7);
    set1 = add(set1, 5);
    set1 = add(set1, 7);
    set1 = add(set1, 9);
    set1 = add(set1, 4);
    //printf("%d", size(set1));
    enumerate(set1);
    set1 = add(set1, 33);
    set1 = add(set1, 27);
    set1 = removekey(set1, 6);
    set1 = removekey(set1, 27);
    set1 = removekey(set1, 5);
    enumerate(set1);
}
