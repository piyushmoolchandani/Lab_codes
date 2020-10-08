#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#define n 40000

int main(){
	
	time_t start_time, end_time;
	
	//create matrix
	double ** a;
	a = (double **)malloc(sizeof(double*)*n);
	for (int i=0;i<n;i++) {
		a[i] = (double*) malloc(sizeof(double)*n);
	}

	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			a[i][j] = i + j;
		}
	}
	
	double * b, * c;
	b = (double *)malloc(sizeof(double) * n);
	c = (double *)malloc(sizeof(double) * n);
	for (int i = 0; i < n; i++){
		b[i] = i * 2;
		c[i] = i;
	}
	
	// Example 1
	puts("Example 1");
	
	// Before Interchange
	time(&start_time);
	for (int i = 1; i < n/5; i++){
		for (int j = 0; j < n/5; j++){
			a[i][j] = a[i - 1][j];
		}
	}
	time(&end_time);
	printf("Simple Loop: %ld\n", end_time - start_time);
	
	// After Interchange
	time(&start_time);
	#pragma omp parallel shared(a)
	{
		#pragma omp for nowait
		for (int j = 0; j < n/5; j++){
			for (int i = 1; i < n/5; i++){
				a[i][j] = a[i - 1][j];
			}
		}
	}
	time(&end_time);
	printf("After Interchange: %ld\n", end_time - start_time);
	
	// Example 2
	puts("Example 2");
	
	// Before Interchange
	time(&start_time);
	for (int i = 1; i < n; i++){
		for (int j = 0; j < n; j++){
			b[i] = i * 3;
			c[j] = b[i - 1];
		}
	}
	time(&end_time);
	printf("Simple Loop: %ld\n", end_time - start_time);

	// After Interchange
	time(&start_time);
	#pragma omp parallel shared(b, c)
	{ 
		#pragma omp for nowait
		for (int j = 1; j < n; j++){
			for (int i = 1; j < n; j++){
				b[i] = i * 3;
				c[j] = c[i - 1];
			}
		}
	}
	time(&end_time);
	printf("After Interchange: %ld\n", end_time - start_time);
	
	
	// Example 3
	puts("Example 3");
	
	// Before Interchange
	time(&start_time);
	for (int i = 1; i < n; i++){
		for (int j = 0; j < n; j++){
			a[j][i] = a[j][i - 1];
		}
	}
	time(&end_time);
	printf("Simple Loop: %ld\n", end_time - start_time);
	
	// After Interchange
	time(&start_time);
	#pragma omp parallel shared(a)
	{
		#pragma omp for nowait
		for (int j = 0; j < n; j++){
			for (int i = 1; i < n; i++){
				a[j][i] = a[j][i - 1];
			}
		}
	}
	time(&end_time);
	printf("After Interchange: %ld\n", end_time - start_time);
	
}
