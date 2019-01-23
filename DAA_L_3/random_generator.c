#include<stdio.h>
int main()
{
	FILE *file_pointer;
	file_pointer = fopen("random_numbers.txt", "w");
	for (int i = 0; i < 100000; i++)
	{
		fprintf(file_pointer, "%ld", rand()%500000);
	}
	fclose(file_pointer);
}
