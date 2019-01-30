#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

void mergeRecursive(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
        
    i = 0; 
    j = 0; 
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
 
void mergeSortRecursive(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
   
        mergeSortRecursive(arr, l, m); 
        mergeSortRecursive(arr, m+1, r); 
  
        mergeRecursive(arr, l, m, r); 
    } 
} 

void mergeIterative(int arr[], int l, int m, int r); 
  
int min(int x, int y) { return (x<y)? x :y; } 
  
void mergeSortIterative(int arr[], int n) 
{ 
   int curr_size;  
   int left_start; 
  
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) 
   { 
       for (left_start=0; left_start<n-1; left_start += 2*curr_size) 
       { 
           int mid = left_start + curr_size - 1; 
  
           int right_end = min(left_start + 2*curr_size - 1, n-1); 

           mergeIterative(arr, left_start, mid, right_end); 
       } 
   } 
} 

void mergeIterative(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
 
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("n");
}

int main(int argc, char * argv[]) 
{ 
	FILE *file_pointer;
	file_pointer = fopen("random_numbers.txt", "r");
	//int c;
	//fscanf(file_pointer, "%d ", &c);
	int count = atoi(argv[1]);
	/*while(c != EOF)
	{
		count ++;
		fscanf(file_pointer, "%ld", &c);
		printf("Came here %d\n", count);
	}
	printf("%d", count);
	fclose(file_pointer);*/
	
	file_pointer = fopen("random_numbers.txt", "r");
	int for_iterative[count];
	int for_recursive[count];
	for (int i = 0; i < count; i++)
	{
		fscanf(file_pointer, "%d ", &for_iterative[i]);
		for_recursive[i] = for_iterative[i];
	}
	
	clock_t t;
	t = clock();
	mergeSortIterative(for_iterative, count);
	t = clock() - t;
	printf("For Iterative quick sort on unsorted array of size %d time taken is %f\n", count, (double)t/CLOCKS_PER_SEC);
	
	clock_t q;
	q = clock();
	mergeSortIterative(for_iterative, count);
	q = clock() - q;
	printf("For Iterative quick sort on sorted array of size %d time taken is %f\n", count, (double)q/CLOCKS_PER_SEC);
	
	clock_t r;
	r = clock();
	mergeSortRecursive(for_recursive, 0, count - 1);
	r = clock() - r;
	printf("For Recursive quick sort on unsorted array of size %d time taken is %f\n", count, (double)r/CLOCKS_PER_SEC);
	
	clock_t s;
	s = clock();
	mergeSortRecursive(for_recursive, 0, count - 1);
	s = clock() - s;
	printf("For Recursive quick sort on sorted array of size %d time taken is %f\n", count, (double)s/CLOCKS_PER_SEC);
	fclose(file_pointer); 
}
