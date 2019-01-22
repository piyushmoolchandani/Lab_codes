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

void remove_(node ** set, int key)
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

bool is_empty(node * S)
{
    if (S == NULL)
        return true;
    return false;
}

bool is_element_of(int key, node * set)
{
    if (is_empty(set))
        return false;
    node * temp_root = set;
    while(temp_root -> key != key)
    {
        if (temp_root -> key == key)
            return true;
        if (temp_root -> next == NULL)
            return false;
        temp_root = temp_root -> next;
    }
}

node * build(int a[], int n)
{
    node * new_root = create();
    for (int i = 1; i <= n; i++)
    {
        add(&new_root, a[n - i]);
    }
    return new_root;
}

// Union Function: returns the union of sets S and T
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
                // If not already not present in the set, insert the element.
                if (!is_element_of(temp -> key, or_set))
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

// Intersection Function: returns the intersection of sets S and T
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

            // Return union of two sets.
            return and_set;
    }
}


int main()
{
   /* printf("%s", "Output:");
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
    printf("\n%d", is_element_of(5, set1));
    printf("\n%d", is_element_of(33, set1));
    printf("\n%d", is_element_of(9, set1));
    printf("\n%d", is_element_of(4, set1));
    int a[9] = {1, 3, 5, 8, 3, 6, 27, 89, 52};
    node * new_set = build(a, 9);
    enumerate(new_set);
    int b[5] = {1, 5, 8, 2, 5};
    node * new_set2 = build(b, 5);
    enumerate(new_set2);
    node * union_set = union_(new_set, new_set2);
    enumerate(union_set);*/

}
