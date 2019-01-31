#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Create a structure that contains a key, and a pointer to left and right subtrees.
typedef struct node
{
    int key;
    struct node * left;
    struct node * right;
}node;

// Create empty tree.
node * create()
{
    return NULL;
}

// Create a node with the given key.
node * create_node(int key) 
{
    node * new_node = (node *)malloc(sizeof(node));
    new_node -> key = key;
    new_node -> left = NULL;
    new_node -> right = NULL;
    return new_node;
}

// Insert a key in BST
node * insert(node * root, int key)
{
    if (root == NULL)
        return create_node(key);

    if (root->key > key)
        root -> left = insert(root -> left, key);
    else if (root->key < key)
        root -> right = insert(root -> right, key);
    
    return root;
}

// Inorder traversal of tree.
void inorder(node * root)
{
    if (root == NULL)
        return;
    
    inorder(root -> left);
    printf("%d \n", root -> key);
    inorder(root -> right);
}

// Preorder traversal of tree.
void preorder(node * root)
{
    if (root == NULL)
        return;
    
    printf("%d \n", root -> key);
    preorder(root -> left);
    preorder(root -> right);
}

// Postorder traversal of tree.
void postorder(node * root)
{
    if (root == NULL)
        return;
    
    postorder(root -> left);
    postorder(root -> right);
    printf("%d \n", root -> key);
}

// Question 1. are_exactly_identical(tree1, tree2) function: checks whether two trees are exactly identical.
bool are_exactly_identical(node * tree1, node * tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return true;
    if (tree1 == NULL || tree2 == NULL)
        return false;
    
    if (tree1 -> key == tree2 -> key)
        return are_exactly_identical(tree1 -> left, tree2 -> left) && are_exactly_identical(tree1 -> right, tree2 -> right);
    return false;
}

// Question 2. are_structurally_identical(tree1, tree2) function : checks whether two trees are structurally identical.
bool are_structurally_identical(node * tree1, node * tree2)
{
    if (tree1 == NULL && tree2 == NULL)
        return true;
    if (tree1 == NULL || tree2 == NULL)
        return false;

    if (tree1 != NULL &&  tree2 != NULL)
        return (are_structurally_identical(tree1 -> left, tree2 -> left) && are_structurally_identical(tree1 -> right, tree2 -> right));
    return false;
}

// Question 3 mirror_bst(root) function: return a mirror image of the bst.
node * mirror_bst(node * root)
{
    if (root == NULL)
        return NULL;

    root -> left = mirror_bst(root -> left);
    root -> right = mirror_bst(root -> right);

    node * temp = root -> left;
    root -> left = root -> right;
    root -> right = temp;

    return root;
}

// Question 4(Part 1): Actual checking of whether a given tree is bst or not.
int check_bst_real(node * root, node * left, node * right)
{
    if (root == NULL)
        return 1;
    
    if (left != NULL && left -> key > root -> key)
        return 0;
    if (right != NULL && right -> key < root -> key)
        return 0;
    
    return check_bst_real(root -> left, left, root) && check_bst_real(root -> right, root, right);
}

// Question 4(Part 2): Virtual check_bst(root) function that is availible for use of user.
int check_bst(node * root)
{
    return check_bst_real(root, NULL, NULL);
}

/* Question 5: distinct_bst(N) function: return total number of distinct bst's that can store N distinct values using recursion. */
int distinct_bst(int N)
{
    if (N == 1 || N == 0)
        return 1;

    int count = 0;
    
    for (int i = 0; i < N; i++)
    {
        count += distinct_bst(i) * (distinct_bst(N - 1 - i));
    }
    return count;
}

/* Question 6. path_sum(root, sum) function: checks whether there exist a path from root to any leaf node such that sum of elements along path is equal to sum argument passed. */
bool path_sum(node * root, int sum)
{
    if ((sum - root -> key == 0) && (root -> left == NULL && root -> right == NULL))
        return true;

    if (root -> left == NULL && root -> right == NULL)
        return false;

    sum -= root -> key;
    return (path_sum(root -> left, sum) || path_sum(root -> right, sum));
}

// Question 7. Part 1: Implements path_to_leaf function.
int path_to_leaf_implement(node * root, int path[], int count)
{
    if (root == NULL)
        return 0;
    if (root -> left == NULL && root -> right == NULL)
    {
        for (int i = 0; i < count; i++)
            printf("%d | ", path[i]);
        printf("%d\n", root -> key);
        return 0;
    }

    int new_path[count + 1];
    for (int i = 0; i < count; i++)
    {
        new_path[i] = path[i];
    }

    new_path[count] = root -> key;

    if (root -> left != NULL)
    {
        path_to_leaf_implement(root -> left, new_path, count + 1);
    }
    if (root -> right != NULL)
    {
        path_to_leaf_implement(root -> right, new_path, count + 1);
    }
    return 0;
}

// Question 7. (Part 2): path_to_leaf function that prints path of each leaf node from root node.
int path_to_leaf(node * root)
{
    int * path;
    return path_to_leaf_implement(root, path, 0);
}

// Question 8. (Part - Get depth of a given node in tree).
int get_depth(node * root, int key)
{
    int depth = -1;
    while (root != NULL)
    {
        depth++;
        if (root -> key == key)
            return depth;

        else if (root -> key > key)
            root = root -> left;

        else if (root -> key < key)
            root = root -> right;

    }
    return -1;
}

// Question 8. (Part - 1): prints elements of tree in asked pattern.
void print_pattern_implement(node * root, node * temp)
{
    if (temp == NULL || root == NULL)
        return;
    
    print_pattern_implement(root, temp -> right);
    for (int i = 0; i <= get_depth(root, temp -> key); i++)
    {
         printf("\t");
    }
    printf("%d", temp -> key);
    printf("\n");
    print_pattern_implement(root, temp -> left);
}

// Question 8. (Part - 2): Calling function to print tree in the specified pattern.
void print_pattern(node * root)
{
    print_pattern_implement(root, root);
}

int main()
{
     node * a = create();
    a = insert(a, 4);
    a = insert(a, 2);
    a = insert(a, 1);
    a = insert(a, 3);
    a = insert(a, 6);
    a = insert(a, 5);
    a = insert(a, 7);
    inorder(a);

    printf("%d\n", distinct_bst(4));
    printf("%d\n", get_depth(a, 4));
    printf("%d\n", check_bst(a));
    print_pattern(a);

    node * b = create();
    b = insert(b, 4);
    b = insert(b, 2);
    b = insert(b, 1);
    b = insert(b, 3);
    b = insert(b, 6);
    b = insert(b, 5);
    b = insert(b, 9);
    print_pattern(b);
    printf("Exactly identical: %d\n", are_exactly_identical(a, b));
    printf("Structurally identical: %d\n", are_structurally_identical(a, b));
    inorder(b);
    b = mirror_bst(b);
    inorder(b);
    b = mirror_bst(b);
    inorder(b);
    print_pattern(b);
    printf("For sum %d in tree a: %d\n", 15, path_sum(a, 15));
    path_to_leaf(a);
}