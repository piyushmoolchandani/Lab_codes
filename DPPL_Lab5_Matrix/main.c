#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 2

void matrix_mul(int a[][N], int b[][N], int c[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void print_matrix(int a[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf(" %d ", a[i][j]);
        }
        printf("%s", "\n");
    }
}
int main()
{
    int a[][N] = {{1, 2}, {7, 3}};
    int b[][N] = {{2, 5}, {9, 8}};
    int c[N][N];
    matrix_mul(a, b, c);
    print_matrix(c);
}