// Time of day logic 
// include library and measure time
// use binary search
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int binary_search(int a[], int s, int l, int to_search)
{
	int m;
	m = (s + l)/2;
	if (l >= s)
	{
		int ans;
		if ( a[m] < to_search)
		{
			ans = binary_search(a, m+1, l, to_search);
		}
		else if (a[m] > to_search)
		{
			ans = binary_search(a, s, m-1, to_search);
		}
		else if (a[m] == to_search)
		{
			ans = m;
			return ans;
		}	
	}
	else
	{
		printf("\nNumber is not here fellas.\n");
		return -1;
	}	
}
int binary_search_iterative(int a[], int s, int l, int to_search)
{
	while (l >= s)
	{	
		int m;
		m = s + (l-s)/2;
		if (a[m] == to_search)
		{
			return m;
		}
		if ( a[m] < to_search)
		{
			l = m+1;
		}
		else
		{
			s = m-1;
		}
		
	}
	printf("%s", "\nNumber is not here fellas.\n");
	return -1;
}
int main()
{
	clock_t t;
	t = clock();
	int a[] = {2, 5, 6 ,23, 252};
	printf("\n%d\n", binary_search(a, 0, 4, 6));
	printf("%d\n", binary_search(a, 0, 4, 252));
	printf("%d\n", binary_search_iterative(a, 0, 4, 6));
	printf("%d\n", binary_search_iterative(a, 0, 4, 252));
}

