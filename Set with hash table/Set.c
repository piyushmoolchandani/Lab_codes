#include<stdio.h>
#include<stdlib.h>

// Create a structure that stores data and a link to next node.
typedef struct node
{
    int key;
    struct node * next;
}node;

// create_node(key) function: function to return a node with key value given and next pointer with NULL value.
node * create_node(int key)
{
    // Allocate memory for the node.
    node * new_node = (node *)malloc(sizeof(node));

    // Assign values to key and next
    new_node -> key = key;
    new_node -> next = NULL;

    return new_node;
}

// hashed(key) function: This function creates a hash function for a given key.
int hashed(int key, int hash_key)
{
    return key % hash_key;
}

// create_head() function: return null of a linked list
node * create_head()
{
    return NULL;
}

// return a hash table with n linked list heads with value NULL.
node ** create(int n)
{
    node ** set;
    for (int i = 0; i < n; i++)
        set[i] = create_head();
    return set;
}

// is_empty_entry(S) function: Checks whether the linked list is empty or not.
int is_empty_list(node * S)
{
    if (S == NULL)
        return 1;
    return 0;
}

// is_empty(S) function: checks whether the set data structure is empty;
int is_empty(node ** S, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!is_empty_list(S[i]))
        {
            return 0;
        }
    }
    return 1;
}

// is_element_of_list(key, S) function: checks whether the value key is in S list.
int is_element_of_list(int key, node * set)
{
    // If empty set sent, return 0.
    if (is_empty_list(set))
        return 0;

    // Traverse through set until key is found.
    node * temp_root = set;
    while(temp_root -> key != key)
    {
        // If reached end of set, return 0.
        if (temp_root -> next == NULL)
            return 0;
        temp_root = temp_root -> next;
    }

    // If key found return 1.
    return 1;
}

// is_element_of(x, S) function: checks whether the value x is in the set S.
int is_element_of(int x, node ** S, int n)
{
    if (is_empty(S, n))
        return 0;
    for (int i = 0; i < n; i++)
    {
        if (is_element_of_list(x, S[i]))
            return 1;
    }
    return 0;
}

// size_list(set) function: returns the number of elements in list.
int size_list(node * set)
{
    // If set is empty, return 0.
    if (set == NULL)
    {
        return 0;
    }
    int count = 0;

    // else return number of elements counted by traversing through the list.
    for (node * temp_root = set; temp_root != NULL; temp_root = temp_root -> next)
        count++;
    return count;
}

// size(set) function: returns the number of elements in the whole set.
int size(node ** set, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        count += size_list(set[i]);
    return count;
}

// enumerate_list(set) function: prints all the elements of the list in some arbitrary order.
void enumerate_list(node * set)
{
    node * temp_root = set;

    // If set is empty, return.
    if (temp_root == NULL)
    {
        return;
    }

    // print the elements
    for (temp_root = set; temp_root != NULL; temp_root = temp_root -> next)
    {
        printf("\n%d", temp_root -> key);
    }
    return;
}

// enumerate(set) function: prints all the elements of the set in some arbitrary order.
void enumerate(node ** set, int n)
{
    // if set is empty, return.
    if (is_empty(set, n))
    {
        printf("%s", "\nSet is empty\n");
        return;
    }

    // print the values one by one.
    printf("%s", "\nElements in the set are: ");
    for (int i = 0; i < n; i++)
        enumerate_list(set[i]);
    printf("\n");
    return;
}


int main()
{
    // Check for is_empty() and is_element_of()
    node ** set = create(10);
    printf("%d", is_empty(set, 10));
    printf("\n%d", is_element_of(5, set, 10));
    enumerate(set, 10);
    set[5] = create_node(5);
    printf("\n%d", is_empty(set, 10));
    printf("\n%d", is_element_of(5, set, 10));
    enumerate(set, 10);
    // Check for count and enumerate
    set[3] = create_node(9);
    printf("\n%d", size(set, 10));
    enumerate(set, 10);

}
