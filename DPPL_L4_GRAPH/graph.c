#include<iostream.h>






















#include<stdio.h>
#include<stdlib.h>
#define MAX 5
int main()
{
	int element[MAX];
	for (int i = 0; i < MAX; i++)
	{
		scanf("%d", element[i]);
	}
	
	printf("%s", "Now enter adjacency matrix");
	int map[MAX][MAX];
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			scanf("%d", map[i][j]);
		}
	}
	
