#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct tree_node {
   int key;
   struct tree_node *L, *R, *P;
}tree_node;

typedef tree_node * BST;

int size(BST T)
{
   if (T == NULL) return 0;
   return size(T -> L) + 1 + size(T -> R);
}

int height(BST T)
{
   int l, r;
   if (T == NULL) return -1;
   l = height(T -> L);
   r = height(T -> R);
   return 1 + ((l >= r) ? l : r);
}

void inorder(BST T)
{
   if (T == NULL) return;
   inorder(T -> L);
   printf("%d\t", T -> key);
   inorder(T -> R);
}

void destroy(BST T)
{
   if (T == NULL) return;
   destroy(T -> L);
   destroy(T -> R);
   free(T);
}

int get_in_array(BST T, int *A)
{
   int ls, rs;
   if (T == NULL) return 0;
   ls = get_in_array(T->L,A);
   A[ls] = T -> key;
   rs = get_in_array(T->R,A+ls+1);
   return ls + 1 + rs;
}

BST create_bst_from_array(int *A, int n)
{
   tree_node *T;
   int r;

   if (n == 0) return NULL;

   r = n / 2;
   T = (tree_node *)malloc(sizeof(tree_node));
   T -> key = A[r]; T -> P = NULL;

   if ((T -> L = create_bst_from_array(A,r))) T -> L -> P = T;
   if ((T -> R = create_bst_from_array(A+r+1,n-(r+1)))) T -> R -> P = T;
   return T;
}

BST rebuild(BST T, int n)
{
   int *A;
   A = (int *)malloc(n * sizeof(int));

   get_in_array(T,A);
   destroy(T);
   T = create_bst_from_array(A,n);
   free(A);

   return T;
}

BST insert(BST T, int x, int *n, int *m, int prnflag)
{
   tree_node *p, *q;
   int dp, sz, lsz, rsz;

   p = T; q = NULL; dp = 0;
   while (p) {
      if (x == p -> key) {
         if (prnflag) printf("       ");
         return T;
      }
      q = p;
      p = (x < p -> key) ? p -> L : p -> R;
      ++dp;
   }

   p = (tree_node *)malloc(sizeof(tree_node));
   p -> key = x; p -> L = p -> R = NULL; p -> P = q;
   if (T == NULL) T = p;
   else if (x < q -> key) q -> L = p;
   else q -> R = p;

   ++(*n); if (*n > *m) *m = *n;

   if (dp > 1 + (int)(log(*n)/log(1.5))) {  
      sz = 1;
      while (q) { 
         if (p == q -> L) {
            lsz = sz;
            rsz = size(q -> R);
         } else {
            lsz = size(q -> L);
            rsz = sz;
         }
         sz = lsz + 1 + rsz;

         p = q; q = q -> P;

         if ((lsz > (2.0 / 3.0) * sz) || (rsz > (2.0 / 3.0) * sz)) {

            if (prnflag) printf("[R %2d] ", sz);
            p = rebuild(p, sz);
            p -> P = q;
            if (q == NULL) return p;
            if (p -> key < q -> key) q -> L = p; else q -> R = p;
            return T;
         }
      }
   } else {
      if (prnflag) printf("       ");
   }
   return T;
}

BST delete ( BST T, int x, int *n, int *m, int prnflag )
{
   tree_node *p, *q, *r, *s;

   p = T; q = NULL;
   while (p) {
      if (p -> key == x) break;
      q = p;
      if (x < p -> key) p = p -> L; else p = p -> R;
   }

   if (p == NULL) {
      if (prnflag) printf("       ");
      return T;
   }

   if ((p -> L == NULL) || (p -> R == NULL)) { 
      r = (p -> L == NULL) ? p -> R : p -> L;
      if (r) r -> P = q;
      if (q == NULL) {
         free(T);
         T = r;
      } else {
         free(p);
         if (x < q -> key) q -> L = r; else q -> R = r;
      }
   } else {                                  
      q = p; s = p -> L;
      while (s -> R) { q = s; s = s -> R; }
      p -> key = s -> key;
      r = s -> L;
      free(s);
      if (q == p) q -> L = r; else q -> R = r;
      if (r) r -> P = q;
   }

   --(*n);
   if ((*n > 0) && (*n < (2.0 / 3.0) * (*m))) {
      if (prnflag) printf("[R %2d] ", *n);
      T = rebuild(T,*n);
      *m = *n;
   } else {
      if (prnflag) printf("       ");
   }

   return T;
}

int main()
{
    BST T = NULL;
    int nsml;
    scanf("%d", &nsml);
    int n = 0; int m = 1;

    int * temp = (int *)malloc(nsml * sizeof(int));
    for (int i = 0; i < nsml; i++)
    {
        int temp;
        scanf("%d", &temp);
        printf("Insert %4d: ", temp);
        T = insert(T,temp,&n,&m,1);
        printf("Height: %4d: ", height(T)); 
        inorder(T); 
        printf("\n");
    }

    for (int i = 0; i < nsml; i++)
    {
        int temp;
        scanf("%d", &temp);
        printf("Delete %4d:", temp);
        T = delete(T,temp,&n,&m,1);
        temp = 0;
        printf("Height: %4d: ", height(T)); 
        inorder(T); 
        printf("\n");
    }

    destroy(T);
    free(temp);

    int nins, ndel;
    scanf("%d", &nins);
    for (int i = 0; i <= nins; i++)
    {
        T = insert(T,rand()%(2*nins),&n,&m,0);

        if (i % 100 == 0)
            printf("Height after %d insertions: %d\n", i, height(T));
    }

    scanf("%d", &ndel);
    for (int i = 0; i < ndel; i++)
    {
        T = delete(T,i,&n,&m,0);

        if (i % 100 == 0)
            printf("Height after %d deletions: %d\n", i, height(T));
    }

    destroy(T);
    return 0;
}