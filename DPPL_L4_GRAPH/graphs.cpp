#include<bits/stdc++.h>
#include<queue>
#define MAX 5

using namespace std;

int find_index(int m[], int p)
{
	int temp = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (m[i] == p)
		{
			return temp;
		}
		temp++;
	}
}

int main()
{
	int element[MAX];
	for (int i = 0; i < MAX; i++)
	{
		cin >> element[i];
	}


	printf("%s", "Now enter adjacency matrix: \n");


	int map[MAX][MAX];


	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			cin >> map[i][j];
		}
	}

	bool visited[MAX];

	queue <int> a;

	a.push(element[0]);

	while (!a.empty())
	{
		int temp = a.front();
		visited[0] = 1;
		cout << temp;
		int index = find_index(element, temp);
		for (int i = 0; i < MAX; i++)
		{
			if (i != index)
			{
				if (!visited[find_index(element, map[i][index])])
					a.push(element[i]);
			}
		}
	}
}
