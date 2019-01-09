#include<stdio.h>
int main()
{
	FILE *file_pointer;
	file_pointer = fopen("a.txt", "w");
	for (int i = 0; i <= 100000; i++)
	{
		fprintf(file_pointer, "%ld\n", rand()%10000000);
	}
	fclose(file_pointer);
}
