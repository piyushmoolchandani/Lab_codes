#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r); 
  
/* l is for left index and r is right index of the sub-array 
  of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
   if (l < r) 
   { 
      int m = l+(r-l)/2; //Same as (l+r)/2 but avoids overflow for large l & h 
      mergeSort(arr, l, m); 
      mergeSort(arr, m+1, r); 
      merge(arr, l, m, r); 
   } 
} 
  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
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
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 



/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void mergeIterative(int arr[], int l, int m, int r); 
  
// Utility function to find minimum of two integers 
int min(int x, int y) { return (x<y)? x :y; } 
  
  
/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSortIterative(int arr[], int n) 
{ 
   int curr_size;  // For current size of subarrays to be merged 
                   // curr_size varies from 1 to n/2 
   int left_start; // For picking starting index of left subarray 
                   // to be merged 
  
   // Merge subarrays in bottom up manner.  First merge subarrays of 
   // size 1 to create sorted subarrays of size 2, then merge subarrays 
   // of size 2 to create sorted subarrays of size 4, and so on. 
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) 
   { 
       // Pick starting point of different subarrays of current size 
       for (left_start=0; left_start<n-1; left_start += 2*curr_size) 
       { 
           // Find ending point of left subarray. mid+1 is starting  
           // point of right 
           int mid = left_start + curr_size - 1; 
  
           int right_end = min(left_start + 2*curr_size - 1, n-1); 
  
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end] 
           mergeIterative(arr, left_start, mid, right_end); 
       } 
   } 
} 
  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void mergeIterative(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
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
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 


int main(int argc, char * argv[]) 
{ 
	FILE *file_pointer;
    int count = atoi(argv[1]);
	file_pointer = fopen("random_numbers.txt", "r");
	//int c;
	//fscanf(file_pointer, "%d ", &c);
	
	/*while(c != EOF)
	{
		count ++;
		fscanf(file_pointer, "%ld", &c);
		printf("Came here %d\n", count);
	}
	printf("%d", count);
	fclose(file_pointer);
	
	file_pointer = fopen("random_numbers.txt", "r");*/
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
	mergeSort(for_recursive, 0, count - 1);
	r = clock() - r;
	printf("For Recursive quick sort on unsorted array of size %d time taken is %f\n", count, (double)r/CLOCKS_PER_SEC);
	
	clock_t s;
	s = clock();
	mergeSort(for_recursive, 0, count - 1);
	s = clock() - s;
	printf("For Recursive quick sort on sorted array of size %d time taken is %f\n", count, (double)s/CLOCKS_PER_SEC);
	fclose(file_pointer); 
}
