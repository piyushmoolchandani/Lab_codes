#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Create a structure data structure that stores data and a link to next node.
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

// create() function: Creates a new, initially empty set structure.
node * create()
{
    // As set is empty, return NULL.
    return NULL;
}

// add(&set, key) function: adds the element key to &set, if it is not present already.
void add(node ** set, int key)
{
    // If set is initially empty.
    if (*set == NULL)
    {
        *set = create_node(key);
        return;
    }

    bool presence_flag = false;
    node * temp_root;

    // Traverse through the list, check if it is already present in the list.
    for (temp_root = *set; temp_root != NULL; temp_root = temp_root -> next)
    {
        // if key found, return.
        if (temp_root -> key == key)
        {
            presence_flag = true;
            break;
        }
    }

    // If key wasn't there, add the key.
    if (!presence_flag)
    {
        node * new_node = create_node(key);
        new_node -> next = *set;
        *set = new_node;
    }

    return;
}

// enumerate(set) function: prints all the elements of the set in some arbitrary order.
void enumerate(node * set)
{
    node * temp_root = set;
    int count = 0;

    // If set is empty, return.
    if (temp_root == NULL)
    {
        printf("\n%s", "Set is empty.");
        return;
    }

    // print the elements
    printf("%s", "\nElements in the set are: ");
    for (temp_root = set; temp_root != NULL; temp_root = temp_root -> next)
    {
        printf("\n%d", temp_root -> key);
        count ++;
    }

    // print total key count.
    printf("\nTotal keys present: %d", count);
    return;
}

// size(set) function: returns the number of elements in set.
int size(node * set)
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

// remove_(&set, key) function: removes the elements key from &set, if it is present.
void remove_(node ** set, int key)
{
    node * temp_root = *set;
    node * backward_pointer;

    // If key if first element, remove it.
    if (temp_root != NULL && temp_root -> key == key)
    {
        *set = temp_root -> next;
        free(temp_root);
        return;
    }

    // Otherwise traverse through the list, and find the previous node of that key.
    while (temp_root != NULL && temp_root -> key != key)
    {
        backward_pointer = temp_root;
        temp_root = temp_root -> next;
    }

    // If element not present, or set is empty, return same set.
    if (temp_root == NULL)
    {
        printf("\n%s", "Key not found in the given set.");
        return;
    }

    // Delete the key.
    backward_pointer -> next = temp_root -> next;
    free(temp_root);
    return;
}

// is_empty(S) function: Checks whether the set is empty or not.
bool is_empty(node * S)
{
    if (S == NULL)
        return true;
    return false;
}

// is_element_of(key, S) function: checks whether the value key is in S.
int is_element_of(int key, node * set)
{
    // If empty set sent, return 0.
    if (is_empty(set))
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

// build(a, n) function: creates a set structure with n values sent through array a.
node * build(int a[], int n)
{
    node * new_root = create();

    // Add elements to new set through add function that checks for repeated inputs as well.
    for (int i = 1; i <= n; i++)
    {
        add(&new_root, a[n - i]);
    }

    return new_root;
}

// union_(S, T) Function: returns the union of sets S and T
node * union_(node * S, node * T)
{
    // Return NULL if both the sets are empty.
    if (is_empty(S) && is_empty(T))
    {
        printf("%s", "\nBoth the sets given for union operation are empty.");
        return NULL;
    }

    // If one of the set is empty return other set.
    else if (is_empty(S))
        return T;
    else if (is_empty(T))
        return S;

    // If none of the sets is empty then
    else
    {
            // Initiate set for union operation
            node * or_set = create();

            for (node * temp = S; temp != NULL; temp = temp -> next)
            {
                // Insert all the elements.
                    add(&or_set, temp -> key);
            }

            for (node * temp = T; temp != NULL; temp = temp -> next)
            {
                // If not already not present in the set, insert the element.
                if (!is_element_of(temp -> key, or_set))
                    add(&or_set, temp -> key);
            }

            // Return union of two sets.
            return or_set;
    }
}

// intersection(S, T) Function: returns the intersection of sets S and T
node * intersection(node * S, node * T)
{
    // Return NULL if both the sets are empty.
    if (is_empty(S) && is_empty(T))
    {
        printf("%s", "\nBoth the sets given for Intersection operation are empty.");
        return NULL;
    }

    // If one of the set is empty return empty set.
    else if (is_empty(S))
        return NULL;
    else if (is_empty(T))
        return NULL;
    else
    {
            node * and_set = create();
            for (node * temp = S; temp != NULL; temp = temp -> next)
            {
                // If also present in the T, insert the element.
                if (is_element_of(temp -> key, T))
                    add(&and_set, temp -> key);
            }

            // Return intersection of two sets.
            return and_set;
    }
}

// difference(S, T) function: return the difference of sets S and T
node * difference(node * S, node * T)
{
    // Return NULL if set S is empty.
    if (is_empty(S))
    {
        printf("%s", "\nFirst set given for difference operation are empty.");
        return NULL;
    }

    // If set T is empty return original S
    else if (is_empty(T))
        return S;

    else
    {
            // Initiate set for Difference pointer.
        node * diff_set = create();
        for (; S != NULL; S = S -> next)
        {
            // If present in S but not in T, insert the element.
            if (!is_element_of(S -> key, T))
                add(&diff_set, S -> key);
        }

        // Return difference of two sets.
        return diff_set;
    }
}

// subset(S, T) function: a predicate that tests whether the set S is a subset of set T
int subset(node * S, node * T)
{
    // Traverse through subset to be checked
    for (node * temp = S; temp -> next != NULL; temp = temp -> next)
    {
        // If element not present in set T return false/0.
        if (!is_element_of(temp -> key, T))
            return 0;
    }
    // If all elements of S are in T, then return True/1.
    return 1;
}

int main()
{
    int a[] = {3, 5, 9, 6, 23442, 34958, 343};
    int b[] = {5, 343, 6};
    int c[] = {9, 5, 344, 6};
    enumerate(build(a, 7));
    enumerate(build(b, 3));
    enumerate(build(c, 4));

    enumerate(union_(build(a, 7), build(b, 3)));
    enumerate(intersection(build(a, 7), build(b, 3)));
    enumerate(difference(build(a, 7), build(b, 3)));
    enumerate(difference(build(a, 7), build(c, 4)));
    enumerate(difference(build(b, 3), build(a, 7)));
    printf("\na subset b: %d\nb subset a: %d\nc subset a: %d", subset(build(a, 7), build(b, 3)), subset(build(b, 3), build(a, 7)), subset(build(c, 4), build(a, 7)));
}
