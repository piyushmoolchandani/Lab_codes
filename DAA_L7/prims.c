#include<stdio.h>
#include<stdlib.h>
void main()
{
	static int i = 1;
	int n = 67;
	for (; i < n; i++)
	{
		printf("%d\n", rand()%i);
		main();
	}
}
