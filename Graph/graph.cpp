#include<bits/stdc++.h>
using namespace std;


void scan_arr(int n, int a[])
{
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void print_arr(int n, int a[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void scan_mat(int n, int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

void print_mat(int n, int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}


int ** create(int n)
{
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(n * sizeof(int));
    
    return mat;
}

int find_index(int var, int size, int m[])
{
    for (int i = 0; i < size; i++)
    {
        if (m[i] == var)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int a;
    scanf("%d", &a);
    int arr[a];
    scan_arr(a, arr);
    print_arr(a, arr);
    int ** array = create(a);
    scan_mat(a, array);
    print_mat(a, array);
    printf("%d", 7);
}