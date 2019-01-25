#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
    node * temp_head = NULL;
    return temp_head;
}

// return a hash table with n linked list heads with value NULL.
node ** create(int n)
{
    node ** set= (struct node **)malloc(n*sizeof(node*));
    for (int i = 0; i < n; i++)
    {
        node * temp = NULL;
        set[i] = temp;
    }
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

// add_list(&set, key) function: adds the element key to &set, if it is not present already.
void add_list(node ** set, int key)
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

// add(&set, key) function: adds the element key to the set passed, if it is not present already.
void add(node ** set, int key)
{
    int index = hashed(key, 10);
    add_list(&set[index], key);
}

// remove_list(&set, key) function: removes the elements key from list, if it is present.
void remove_list(node ** set, int key)
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

// remove_ function: removes the element key from given set, if it is present.
void remove_(node ** set, int key)
{
    int index = hashed(key, 10);
    remove_list(&set[index], key);
}

// union_(S, T) Function: returns the union of sets S and T
node ** union_(node ** S, node ** T, int n)
{
    // Return NULL if both the sets are empty.
    if (is_empty(S, n) && is_empty(T, n))
    {
        printf("%s", "\nBoth the sets given for union operation are empty.");
        return NULL;
    }

    // If one of the set is empty return other set.
    else if (is_empty(S, n))
        return T;
    else if (is_empty(T, n))
        return S;

    // If none of the sets is empty then
    else
    {
            // Initiate set for union operation
            node ** or_set = create(n);

            for (int i = 0; i < n; i++)
            {
                for (node * temp = S[i]; temp != NULL; temp = temp -> next)
                {
                    add(or_set, temp -> key);
                }
            }

            for (int i = 0; i < n; i++)
            {
                for (node * temp = T[i]; temp != NULL; temp = temp -> next)
                {
                    if(!is_element_of(temp -> key, or_set, 10))
                        add(or_set, temp -> key);
                }
            }

            // Return union of two sets.
            return or_set;
    }
}

// intersection(S, T) Function: returns the intersection of sets S and T
node ** intersection(node ** S, node ** T, int n)
{
    // Return NULL if both the sets are empty.
    if (is_empty(S, n) && is_empty(T, n))
    {
        printf("%s", "\nBoth the sets given for Intersection operation are empty.");
        return NULL;
    }

    // If one of the set is empty return empty set.
    else if (is_empty(S, n))
        return NULL;
    else if (is_empty(T, n))
        return NULL;
    else
    {
            node ** and_set = create(n);

            for (int i = 0; i < n; i++)
            {
                for (node * temp = S[i]; temp != NULL; temp = temp -> next)
                {
                    if(is_element_of(temp -> key, T, 10))
                        add(and_set, temp -> key);
                }
            }


            // Return intersection of two sets.
            return and_set;
    }
}

// difference(S, T) function: return the difference of sets S and T
node ** difference(node ** S, node ** T, int n)
{
    // Return NULL if set S is empty.
    if (is_empty(S, n))
    {
        printf("%s", "\nFirst set given for difference operation is empty.");
        return NULL;
    }

    // If set T is empty return original S
    else if (is_empty(T, n))
        return S;

    else
    {
            // Initiate set for Difference pointer.
        node ** diff_set = create(n);
        for (int i = 0; i < n; i++)
        {
            for (node * temp = S[i]; temp != NULL; temp = temp -> next)
            {
                // If present in S but not in T, insert the element.
                if (!is_element_of(temp -> key, T, n))
                    add(diff_set, temp -> key);
            }
        }

        // Return difference of two sets.
        return diff_set;
    }
}

// subset(S, T) function: a predicate that tests whether the set S is a subset of set T
int subset(node ** S, node ** T, int n)
{
    // Traverse through subset to be checked
    for (int i = 0; i < n; i++)
    {
        for (node * temp = S[i]; temp != NULL; temp = temp -> next)
        {
            // If element not present in set T return false/0.
            if (!is_element_of(temp -> key, T, 10))
                return 0;
        }
    }

    // If all elements of S are in T, then return True/1.
    return 1;
}

node ** build(int a[], int count, int n)
{
    node ** new_set = create(n);

    for (int i = 0; i < count; i++)
    {
        int index = hashed(a[i], 10);
        add_list( &new_set[index], a[i]);
    }
    return new_set;
}


int main()
{
    // Check for is_empty() and is_element_of()
    node ** set = create(10);
    printf("%d", is_empty(set, 10));
    printf("\n%d", is_element_of(5, set, 10));
    enumerate(set, 10);
    add(set, 5);
    printf("\n%d", is_empty(set, 10));
    printf("\n%d", is_element_of(5, set, 10));
    enumerate(set, 10);
    // Check for count and enumerate
    set[9] = create_node(9);
    printf("\n%d", size(set, 10));
    enumerate(set, 10);

    // Check for add function
    printf("%d", is_empty(set, 10));

    enumerate(set, 10);
    add(set, 18);
    add(set, 25);
    add(set, 28);
    enumerate(set, 10);
    printf("\n%d", is_element_of(35, set, 10));

    int a[9] = {3, 5, 6, 9, 3432, 2, 5, 3, 9};
    int b[3] = {3, 6, 2};
    node ** set2 = build(a, 9, 10);
    node ** set3 = build(b, 3, 10);
    enumerate(set3, 10);
    enumerate(set2, 10);

    /**remove_(set, 5);
    enumerate(set, 10);
    remove_(set, 18);
    enumerate(set, 10);
    remove_(set, 9);
    enumerate(set, 10);**/

    // check union
    enumerate(union_(set, set2, 10), 10);
    enumerate(intersection(set, set2, 10), 10);
    enumerate(difference(set2, set, 10), 10);
    printf("\na subset b: %d\nb subset a: %d\nc subset b: %d", subset(set, set2, 10), subset(set2, set, 10), subset(set3, set2, 10));
}
