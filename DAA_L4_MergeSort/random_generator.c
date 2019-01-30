#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *file_pointer;
	file_pointer = fopen("random_numbers.txt", "w");
	for (int i = 0; i < 1000000; i++)
	{
		fprintf(file_pointer, "%d\n", rand()%50000);
	}
	fclose(file_pointer);
}