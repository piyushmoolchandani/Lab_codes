#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void factorize(double **matrix, int matrix_size){
	
	int pid, nprocs, i, j, k, row, min, max;
	
	#pragma omp parallel shared(matrix, matrix_size, nprocs) private(i, j, k, row, min, max, pid)
	{
		#ifdef _OPENMP
			nprocs = omp_get_num_threads();
			pid = omp_get_thread_num();
		#endif
		
		printf("nprocs: %d, pid: %d\n", nprocs, pid);
		
		row = matrix_size/nprocs;
		min = pid * row;
		max = min + row - 1;
		
		if (pid == nprocs - 1 && (matrix_size - (max + 1))>0)
			max = matrix_size - 1;
			
		for (k = 0; k < matrix_size; k++){
			if (k >= min && k <= max){
				for (j = k + 1; j < matrix_size; j++){
					matrix[k][j] = matrix[k][j] / matrix[k][k];
				}
			}
			
			#pragma omp barrier
			if ((k + 1) > min)
				i = k + 1;
			else i = min;
			
			for (;i <= max; i++){
				for (j = k + 1; j < matrix_size; j++){
					matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j];
				}
			}
		}
	}
}
	
int main(){

	int matrix_size;
	printf("Enter matrix size: ");
	scanf("%d", &matrix_size);
	
	double **matrix = (double**)malloc(matrix_size * sizeof(double*));
	for (int i = 0; i < matrix_size; i++){
		matrix[i] = (double *)malloc(matrix_size * sizeof(double));
	}
	
	printf("Enter matrix element: ");
	for (int i = 0; i < matrix_size; i++){
		for (int j = 0; j < matrix_size; j++){
			scanf("%lf", &matrix[i][j]);
		}
	}
	
	printf("Entered matrix: \n");
	for (int i = 0; i < matrix_size; i++){
		for (int j = 0; j < matrix_size; j++){
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	
	int num_threads;
	printf("Enter number of threads: ");
	scanf("%d", &num_threads);
	
	printf("\n");
	
	omp_set_num_threads(num_threads);
	
	printf("Starting factorization using %d threads\n", num_threads);
	
	factorize(matrix, matrix_size);
	printf("Resultant matrix: \n");
	
	printf("Matrix L: \n");
	for (int i = 0; i < matrix_size; i++){
		for (int j = 0; j < matrix_size; j++){
			if (j > i) printf("%lf ", 0.0);
			else printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
	
	printf("Matrix R: \n");
	for (int i = 0; i < matrix_size; i++){
		for (int j = 0; j < matrix_size; j++){
			if (i == j) printf("%lf ", 1.0);
			else if (i > j) printf("%lf ", 0.0);
			else printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

/**
Sample input for verification: 
int size = 3
matrix: 
	2.000000 2.000000 3.000000 
	5.000000 9.000000 10.000000 
	4.000000 1.000000 2.000000
	
expected output:
Matrix L: 
2.000000 0.000000 0.000000 
5.000000 4.000000 0.000000 
4.000000 -3.000000 -2.125000 

Matrix R: 
1.000000 1.000000 1.500000 
0.000000 1.000000 0.625000 
0.000000 0.000000 1.000000 
**/
