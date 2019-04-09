#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 10

typedef struct tree_node {
   unsigned int EOS;
   struct tree_node *L, *R;
}tree_node;

typedef tree_node * binary_tree;

void find_binary(char *S, unsigned int a)
{
    int i, len;
    char T[Max];

    i = 0;
    while (a) 
    {
        T[i] = '0' + (a & 1); 
        a >>= 1;
        ++i;
    }
    --i; 
    S[i] = '\0';    
    --i; len = i;
    while (i >= 0) {
        S[len-i] = T[i];
        --i;
    }
}

int print_tree_(binary_tree T, unsigned int a, int index)
{
    char S[Max+1];
    if (T == NULL) 
        return index;
    if (T -> EOS) 
    {
        find_binary(S,a);
        printf("%s\t", S);
        ++index;
    }
    index = print_tree_(T->L,(a<<1),index);
    index = print_tree_(T->R,((a<<1)|1),index);
    return index;
}

void print_tree(binary_tree T)
{
   int index;
   index = print_tree_(T,1,0);
   printf("\n");
}

binary_tree insert(binary_tree T, unsigned int a)
{
    tree_node *p;
    int i, l;
    char S[Max+1];

    if (a == 0) return T;

    if (T == NULL) {
        T = (tree_node *)malloc(sizeof(tree_node));
        T -> L = T -> R = NULL; T -> EOS = 0;
    }

    find_binary(S,a); l = strlen(S);

    p = T;
    for (i=0; i<l; ++i) 
    {
        if (S[i] == '0') 
        {
            if (p -> L == NULL) {
                p -> L = (tree_node *)malloc(sizeof(tree_node));
                p -> L -> L = p -> L -> R = NULL; p -> L -> EOS = 0;
            }
            p = p -> L;
        } 
        else {
            if (p -> R == NULL) {
                p -> R = (tree_node *)malloc(sizeof(tree_node));
                p -> R -> L = p -> R -> R = NULL; p -> R -> EOS = 0;
            }
            p = p -> R;
        }
   }
   p -> EOS = 1;
   return T;
}

binary_tree delete_(binary_tree T, char *S, int l, int i)
{
    if (i <= l-1) 
    {
        if (S[i] == '0') 
            T -> L = delete_(T->L,S,l,i+1);
        else 
            T -> R = delete_(T->R,S,l,i+1);
    }

    if ((T -> EOS == 0) && (T -> L == NULL) && (T -> R == NULL)) {
        free(T); return NULL;
    }
    return T;
}

binary_tree delete(binary_tree T, unsigned int a)
{
    char S[Max+1];
    int i, l;
    tree_node *p;

    if ((a == 0) || (T == NULL)) 
        return T;

    find_binary(S,a); 
    l = strlen(S);

    p = T;
    for (i=0; i<l; ++i) 
    {
        if (S[i] == '0')
        {
            if (p -> L == NULL) return T; 
            p = p -> L;
        }
        else
        {
            if (p -> R == NULL) return T;
            p = p -> R;
        }
    }

    if (p -> EOS == 0) return T;

    p -> EOS = 0;

    if ((p -> L == NULL) && (p -> R == NULL)) 
        T = delete_(T,S,l,0);

    return T;
}

int count_nodes(binary_tree T)
{
    if (T == NULL) 
        return 0;
    return 1 + count_nodes(T->L) + count_nodes(T->R);
}

void print_ints(binary_tree T)
{
    tree_node **Q;
    int *A, n;
    int F, B;

    if (T == NULL) 
        return;

    n = count_nodes(T);
    Q = (tree_node **)malloc(n * sizeof(tree_node *));
    A = (int *)malloc(n * sizeof(int));

    F = B = 0; Q[0] = T; A[0] = 1;

    while (F <= B) 
    {
        if (Q[F] -> EOS){
            printf("%d\t", A[F]); fflush(stdout);
        }

        if (Q[F] -> L) {
            ++B; Q[B] = Q[F] -> L; A[B] = (A[F] << 1);
        }

        if (Q[F] -> R) {
            ++B; Q[B] = Q[F] -> R; A[B] = (A[F] << 1) + 1;
        }
        ++F;
    }
    free(Q); 
    free(A);
}

void destroy(binary_tree T)
{
    if (T == NULL) 
        return;
    destroy(T->L);
    destroy(T->R);
    free(T);
}

int main()
{
    int nins;
    scanf("%d", &nins);

    binary_tree T = NULL;
    unsigned int to_be_inserted[nins];
    for (int i = 0; i < nins; i++)
    {
        scanf("%d", &to_be_inserted[i]);
        T = insert(T, to_be_inserted[i]);
    }
    printf("After Insertion: \n");
    print_tree(T);

    int ndel;
    scanf("%d", &ndel);
    unsigned int to_be_deleted[ndel];
    for (int i = 0; i < ndel; i++)
    {
        scanf("%d", &to_be_deleted[i]);
        T = delete(T, to_be_deleted[i]);
    }
    printf("After Deletion: \n");
    print_tree(T);

    printf("\n");
    printf("Part 4 of main: \n");
    for (int i = 0; i < nins; i++)
    {
        scanf("%d", &to_be_inserted[i]);
        T = insert(T, to_be_inserted[i]);
        print_ints(T);
        printf("\n");
    }

    printf("Part 5 of main: \n");
    for (int i = 0; i < ndel; i++)
    {
        scanf("%d", &to_be_deleted[i]);
        T = delete(T, to_be_deleted[i]);
        print_ints(T);
        printf("\n");
    }
}