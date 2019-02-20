#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int ** create(int n)
{

    int **arr = (int **)malloc(n * sizeof(int *)); 
    for (int i=0; i<n; i++) 
         arr[i] = (int *)malloc(n * sizeof(int)); 
    return arr;
}

void add(int n, int ** a, int ** b, int ** c)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

void copy(int temp, int temp2, int n, int ** a, int ** r)
{
	for (int i = 0; i < n/2; i++)
	{
		for (int j = 0; j < n/2; j++)
		{
			r[i][j] = a[temp + i][temp2 + j];
		}
	}
}

void scan(int n, int ** a)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
		}
	}
}

void print(int N, int ** a)
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

void matrix_mul(int N, int ** a, int ** b, int ** c)
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

void matrix_mul_dc(int n, int **a, int **b, int **c)
{
	if (n/2 == 1)
	{
		matrix_mul(n/2, a, b, c);
		return;
	}
	
	int ** A11 = create(n/2);
	int ** A12 = create(n/2);
	int ** A21 = create(n/2);
	int ** A22 = create(n/2);
	int ** B11 = create(n/2);
	int ** B12 = create(n/2);
	int ** B21 = create(n/2);
	int ** B22 = create(n/2);
	int ** R11 = create(n/2);
	int ** R12 = create(n/2);
	int ** R21 = create(n/2);
	int ** R22 = create(n/2);
	
	copy(0, 0, n, a, A11);
	copy(0, n/2, n, a, A12);
	copy(n/2, 0, n, a, A21);
	copy(n/2, n/2, n, a, A22);
	copy(0, 0, n, b, B11);
	copy(0, n/2, n, b, B12);
	copy(n/2, 0, n, b, B21);
	copy(n/2, n/2, n, b, B22);
	
	int ** temp = create(n/2);
	int ** temp_2 = create(n/2);
	matrix_mul_dc(n/2, A11, B11, temp);
	matrix_mul_dc(n/2, A12, B21, temp_2);
	add(n/2, temp, temp_2, R11);
	matrix_mul_dc(n/2, A11, B12, temp);
	matrix_mul_dc(n/2, A12, B22, temp_2);
	add(n/2, temp, temp_2, R12);
	matrix_mul_dc(n/2, A21, B11, temp);
	matrix_mul_dc(n/2, A22, B21, temp_2);
	add(n/2, temp, temp_2, R21);
	matrix_mul_dc(n/2, A21, B12, temp);
	matrix_mul_dc(n/2, A22, B22, temp_2);
	add(n/2, temp, temp_2, R22);
	
	int ** R = create(n);
	copy(0, 0, n, a, R);
	copy(0, n/2, n, a, R);
	copy(n/2, 0, n, a, R);
	copy(n/2, n/2, n, a, R);
}

int main()
{
	int m;
	scanf("%d", &m);
   	int ** a = create(m);
   	int ** b = create(m);
   	scan(m, a);
   	scan(m, b);
   	int ** c = create(m);
   	matrix_mul(m, a, b, c);
   	print(m, c);
	matrix_mul_dc(m, a, b, c);
	print(m, c);
}
