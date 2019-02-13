#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap_(int a[], int i , int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void heapify(int arr[], int n, int i)
{ 
    int largest = i; 
    int l = 2*i + 1; 
    int r = 2*i + 2;  
  
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
   
    if (largest != i) 
    { 
        swap_(arr, i, largest); 
  
        heapify(arr, n, largest); 
    } 
} 
  
void heapSort(int arr[], int n) 
{ 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    for (int i=n-1; i>=0; i--) 
    { 
        swap_(arr, 0, i); 
  
        heapify(arr, i, 0); 
    } 
} 

void printArray(int arr[], int n) 
{ 
    for (int i=0; i<n; ++i) 
        printf("%d ", arr[i]);
    printf("\n");
}

int main(int argc, char * argv[])
{
	FILE *file_pointer;
	file_pointer = fopen("random_numbers.txt", "r");
	int count = atoi(argv[1]);
	int heap[count];
	int temp;
	for (int i = 0; i < count; i++)
	{
		fscanf(file_pointer, "%d", &temp);
		heap[i] = temp;
	}
	
	clock_t t;
	t = clock();
	heapSort(heap, count);
	t = clock() - t;
	printf("For heap sort on unsorted array of size %d time taken is %f\n", count, (double)t/CLOCKS_PER_SEC);
	
	t = clock();
	heapSort(heap, count);
	t = clock() - t;
	printf("For heap sort on sorted array of size %d time taken is %f\n", count, (double)t/CLOCKS_PER_SEC);
}
