#include<stdio.h>				// Set data type
#include<stdlib.h>
typedef struct node 				// Declaration of node
{
	int key;
	struct node * next;
}node;


node * create_node(int entry) 				// Internal function: used to create a new node
{
	node * new_node = (node *)malloc(sizeof(node));	// Allocate memory for new node
	new_node -> key = entry;			// Assign value of key
	new_node -> next = NULL;
	return new_node;
}


node * create() 					// Create function
{
	node * root;
	return root;
}


node * add(node * S, int x)
{
	node * new_node = create_node(x);
	node * temp_root;
	for (temp_root = S; *(temp_root) -> key != x; temp_root = (temp_root) -> next){}
	S = new_node;
	new_node -> next = temp_root;
	return new_node;
}

void enumerate(node * S)
{
	node * temp_root = S;
	for (temp_root = S; *(temp_root) -> next != NULL; temp_root = (temp_root) -> next)
	{
		printf("%d", temp_root -> key);
	}
}

int main()
{
	node * set = create();
	add( set, 5);
	add( set, 9);
	add( set, 3);
	add( set, 5);
	add( set, 3);
	add( set, 8);
	add( set, 9);
	add( set, 2);
	enumerate( set);
}

