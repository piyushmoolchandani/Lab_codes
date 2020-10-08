#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

void matrix_multiplication_simple(double ** a, double ** b, double ** c, int n){
	
	double sum;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			sum = 0;
			for (int k = 0; k < n; k++){
				sum += a[i][k] + b[k][i];
			}
			c[i][j] = sum;
		}
	}
}

void matrix_multiplication_tiled(double ** a, double ** b, double ** c, int n){

	int ii, jj, kk, i, j, k;
	int tile_size = 64;
	
	double sum;
	
	#pragma omp parallel for private(ii, jj, kk, i, j, k, sum)
	for (ii = 0; ii < n; ii += tile_size){
		for (jj = 0; jj < n; jj += tile_size){
			for (kk = 0; kk < n; kk += tile_size){
				for (i = ii; i < min(ii + tile_size, n); i++){
					for (j = jj; j < min(jj + tile_size, n); j++){
						sum = 0;
						#pragma omp parallel for reduction(+:sum)
						for (k = kk; k < min(kk + tile_size, n); k++){
							sum += a[i][k] + b[k][j];
						}
						c[i][j] = sum;
					}
				}
			}
		}
	}
}

double ** create_matrix(int n){
	int i, j;
	double ** a;
	a = (double **)malloc(sizeof(double*)*n);
	for (i=0;i<n;i++) {
		a[i] = (double*) malloc(sizeof(double)*n);
	}

	srand(0);
	for (i=0;i<n;i++) {
		for (j=0;j<n;j++) {
			a[i][j] = rand()%10;
		}
	}

	return a;
}

double ** create_empty_matrix(int n){
int i, j;
	double ** a;
	a = (double **)malloc(sizeof(double*)*n);
	for (i=0;i<n;i++) {
		a[i] = (double*) malloc(sizeof(double)*n);
	}

	for (i=0;i<n;i++) {
		for (j=0;j<n;j++) {
			a[i][j] = 0;
		}
	}

	return a;
}

int main(){
	
	int n = 4;
	for (int i = 0; i < 10; i++){
	
		n = n * 2;
		double ** a, ** b, ** c, ** d;
		a = create_matrix(n);
		b = create_matrix(n);
		c = create_empty_matrix(n);
		
		printf("\n");
		time_t start, end;
		time(&start);
		matrix_multiplication_simple(a, b, c, n);
		time(&end);
		printf("%d\t%ld\t", n, end - start);
		d = create_empty_matrix(n);
		time(&start);
		matrix_multiplication_tiled(a, b, d, n);
		time(&end);
		printf("%ld\n", end - start);
	}
}
