#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

int partition (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; 
	int i = (low - 1); 

	for (int j = low; j <= high- 1; j++) 
	{ 
		if (arr[j] <= pivot) 
		{ 
			i++; 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 

void quickSortRecursive(int arr[], int low, int high) 
{ 
	if (low < high) 
	{ 
		int pi = partition(arr, low, high); 

		quickSortRecursive(arr, low, pi - 1); 
		quickSortRecursive(arr, pi + 1, high); 
	} 
} 

void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("n"); 
} 
  
void quickSortIterative (int arr[], int l, int h) 
{ 
    int stack[ h - l + 1 ]; 
    
    int top = -1; 
     
    stack[ ++top ] = l; 
    stack[ ++top ] = h; 
    
    while ( top >= 0 ) 
    {
        h = stack[ top-- ]; 
        l = stack[ top-- ]; 
   
        int p = partition( arr, l, h ); 
  
        if ( p-1 > l ) 
        { 
            stack[ ++top ] = l; 
            stack[ ++top ] = p - 1; 
        } 
  
        if ( p+1 < h ) 
        { 
            stack[ ++top ] = p + 1; 
            stack[ ++top ] = h; 
        } 
    } 
} 

int main() 
{ 
	FILE *file_pointer;
	file_pointer = fopen("random_numbers.txt", "r");
	int c;
	fscanf(file_pointer, "%ld", &c);
	int count = 100000;
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
		fscanf(file_pointer, "%ld", &for_iterative[i]);
		for_recursive[i] = for_iterative[i];
	}
	
	clock_t t;
	t = clock();
	quickSortIterative(for_iterative, 0, count - 1);
	t = clock() - t;
	printf("For Iterative quick sort on unsorted array of size %d time taken is %f\n", count, (double)t/CLOCKS_PER_SEC);
	
	clock_t q;
	q = clock();
	quickSortIterative(for_iterative, 0, count - 1);
	q = clock() - q;
	printf("For Iterative quick sort on sorted array of size %d time taken is %f\n", count, (double)q/CLOCKS_PER_SEC);
	
	clock_t r;
	r = clock();
	quickSortRecursive(for_recursive, 0, count - 1);
	r = clock() - r;
	printf("For Recursive quick sort on unsorted array of size %d time taken is %f\n", count, (double)r/CLOCKS_PER_SEC);
	
	clock_t s;
	s = clock();
	quickSortRecursive(for_recursive, 0, count - 1);
	s = clock() - s;
	printf("For Recursive quick sort on sorted array of size %d time taken is %f\n", count, (double)s/CLOCKS_PER_SEC);
	fclose(file_pointer); 
}

