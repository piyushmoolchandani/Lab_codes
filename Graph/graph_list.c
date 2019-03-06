#include<stdio.h>
#include<stdlib.h>

/** Stack -------------------------------------------------------------------------------------------------**/
struct snode
{
    int key;
    struct snode * next;
};

typedef struct snode snode;

snode * create_stack()
{
    return NULL;
}

 snode * create_snode (int key)
{
    snode * temp = (snode *)malloc(sizeof(snode));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

void push(snode ** root, int key)
{
    if (*root == NULL)
    {
        *root = create_snode(key);
        return;
    }

    snode * temp = create_snode(key);
    temp -> next = *root;
    *root = temp;
    return;
}

int is_empty(snode * root)
{
    if (root == NULL)
        return 1;
    return 0;
}

void pop(snode ** root)
{
    if (!is_empty(*root))
    {
        snode * temp_snode = *root;
        *root = (*root) -> next;
        free(temp_snode);
        return;
    }
}

int top(snode ** root)
{
    if (!is_empty(*root))
    {
        int temp = (*root) -> key;
        return temp;
    }
}

void print_stack(snode * root)
{
    if (!is_empty(root))
    {
        snode * temp = root;
        while (temp != NULL)
        {
            printf("%d\t", temp -> key);
            temp = temp -> next;
        }
        printf("\n");
        return;
    }
    printf("%s\n", "Stack Empty!");
}
/** -------------------------------------------------------------------------------------------------------**/

/** Graph Utilities **/
typedef struct adj_list_node{
    int destination;
    struct adj_list_node * next;
}node;

typedef struct adj_list{
    node * head;
}adj_list;

typedef struct graph{
    int vertices;
    struct adj_list * array;
}graph;

graph * create_graph(int vertices)
{
    graph * new = (graph *)malloc(sizeof(graph));
    new -> vertices = vertices;
    new -> array = (adj_list *)malloc(vertices * sizeof(adj_list));
    for (int i = 0; i < vertices; i++)
        new -> array[i].head = NULL;
    return new;
}

node * create_node(int destination)
{
    node * temp = (node *)malloc(sizeof(node));
    temp -> destination = destination;
    temp -> next = NULL;
    return temp;    
}

void add_edge(graph * Graph, int source, int destination)
{
    node * new_node = create_node(destination);
    new_node -> next = Graph -> array[source].head;
    Graph -> array[source].head = new_node;
}

void add_edge_undirected(graph * Graph, int source, int destination)
{
    node * new_node = create_node(destination);
    new_node -> next = Graph -> array[source].head;
    Graph -> array[source].head = new_node;

    new_node = create_node(source);
    new_node -> next = Graph -> array[destination].head;
    Graph -> array[destination].head = new_node;
}

void print_graph(graph * g)
{
    for (int i = 0; i < g -> vertices; i++)
    {
        node * temp = g -> array[i].head;
        printf("%d: ", i);
        while(temp)
        {
            printf("%d -> ", temp -> destination);
            temp = temp -> next;
        }
        printf("\n");
    }
}

int * create_visited(int n)
{
    int * temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        temp[i] = 0;
    return temp;
}

void print_array(int v[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d\t", v[i]);
    printf("\n");
}
/** ------------------------------------**/

/** --------- TOPOLOGICAL SORT ---------**/
void topological_sort_(graph * Graph, int i, int visited[], snode ** Stack)
{
    visited[i] = 1;
    node * temp = Graph -> array[i].head;
    for (node * temp = Graph -> array[i].head; temp != NULL; temp = temp -> next)
    {    
        if (visited[temp -> destination] == 0)
            topological_sort_(Graph, temp -> destination, visited, Stack);
    }
    push(Stack, i);
}

void topological_sort(graph * Graph)
{
    int v = Graph -> vertices;
    int visited[v];
    for (int i = 0; i < v; i++)
        visited[i] = 0;
    snode * Stack = create_stack();
    for (int i = 0; i < Graph -> vertices; i++)
        if (visited[i] == 0)
            topological_sort_(Graph, i, visited, &Stack);
    print_stack(Stack);
}
/** -----end topological sort------**/

/** -----DFS----- **/
void DFS_connected(graph * g, int v, int visited[])
{
    visited[v] = 1;
    for (node * temp = g -> array[v].head; temp != NULL; temp = temp -> next)
        if (!visited[temp -> destination])
            DFS_connected(g, temp -> destination, visited);
    /*printf("%d \t", v);
    for (int i = 0; i < g -> vertices; i++)
        printf("%d\t", visited[i]);
    printf("\n");*/
}

int DFS_success(graph * g, int v)
{
    int n = g -> vertices;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    DFS_connected(g, v, visited);

    for (int i = 0; i < g -> vertices; i++)
        if (!visited[i])
            return 0;
    return 1;    
}

int mother_vertex(graph * g)
{
    int v = g -> vertices;
    int visited[v];
    for (int i = 0; i < v; i++)
        visited[i] = 0;
    
    int temp;
    for (int i = 0; i < v; i++)
        if (visited[i] == 0)
        {
            DFS_connected(g, i, visited);
            temp = i;
        }

    int check = DFS_success(g, temp);
    if (check)
        return temp;
    return -1;
}

// Question 3
int dfs_directed_cycle(graph * g, int v, int visited[], int present[])
{
    visited[v] = 1;
    present[v] = 1;

    for (node * temp = g -> array[v].head; temp != NULL; temp = temp -> next)
        if (present[temp -> destination])
            return 1;
        else if (!visited[temp -> destination])
            if (dfs_directed_cycle(g, temp -> destination, visited, present))
                return 1;

    present[v] = 0;
    return 0;
}

int is_cyclic_directed(graph * g)
{
    int n = g -> vertices;
    int visited[n];
    int present[n];
    for (int i = 0; i < n; i++)
        visited[i] = present[i] = 0;
    
    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            int temp = dfs_directed_cycle(g, i, visited, present);
            if (temp)
                return temp;
        }
    return 0;
}

int dfs_undirected_cycle(graph * g, int i, int visited[], int parent)
{
    visited[i] = 1;
    for (node * temp = g -> array[i].head; temp != NULL; temp = temp -> next)
    {  
        if (!visited[temp -> destination])
        {
            if (dfs_undirected_cycle(g, temp -> destination, visited, i))
                return 1;
        }
        else if (visited[temp -> destination] && temp -> destination != parent)
            return 1;
    }
    return 0;
}

int is_cyclic_undirected(graph * g)
{
    int n = g -> vertices;
    int visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    
    for (int i = 0; i < n; i++)
        if (!visited[i])
            if (dfs_undirected_cycle(g, i, visited, -7))
                return 1;
    return 0;
}

int dfs_for_bipartite(graph * g, int v, int color[], int colour)
{
    color[v] = colour;
    for (node * temp = g -> array[v].head; temp != NULL; temp = temp -> next)
    {
        if (color[temp -> destination] == colour)
            return 0;
        else if (!color[temp -> destination])
            if (!dfs_for_bipartite(g, temp -> destination, color, (colour % 2) + 1))
                return 0;
    }
    return 1;
}

int is_bipartite(graph * g)
{
    int v = g -> vertices;
    int * color = create_visited(v);

    if (dfs_for_bipartite(g, 0, color, 1))
        return 1;
    return 0;
}

int main()
{
    graph * Graph = create_graph(6);
    add_edge(Graph, 5, 2);
    add_edge(Graph, 5, 0);
    add_edge(Graph, 4, 0);
    add_edge(Graph, 4, 1);
    add_edge(Graph, 2, 3);
    add_edge(Graph, 3, 1);
    printf("%s\n", "Following is a Topological Sort of the given graph:"); 
    topological_sort(Graph);
    //printf("Mother vertex: %d\n", mother_vertex(Graph));

    graph * Graph_2 = create_graph(10);
    add_edge(Graph_2, 7, 1);
    add_edge(Graph_2, 7, 3);
    add_edge(Graph_2, 7, 6);
    add_edge(Graph_2, 5, 3);
    add_edge(Graph_2, 5, 6);
    add_edge(Graph_2, 6, 8);
    add_edge(Graph_2, 4, 8);
    add_edge(Graph_2, 4, 2);
    add_edge(Graph_2, 2, 10);
    printf("%s\n", "Following is a Topological Sort of the given graph:"); 
    topological_sort(Graph_2);
    //printf("Mother vertex: %d\n", mother_vertex(Graph_2));

    graph * Graph_3 = create_graph(7);
    add_edge(Graph_3, 0, 1);
    add_edge(Graph_3, 0, 2);
    add_edge(Graph_3, 1, 3);
    add_edge(Graph_3, 4, 1);
    add_edge(Graph_3, 5, 2);
    add_edge(Graph_3, 5, 6);
    add_edge(Graph_3, 6, 0);
    add_edge(Graph_3, 6, 4);
    //print_graph(Graph_3);
    printf("Mother vertex: %d\n", mother_vertex(Graph_3));

    while(1)
    {
        int cont;
        printf("Enter 0 to break out: ");
        scanf("%d", &cont);
        if (cont)
        {
            int v;
            printf("Enter number of vertices: ");
            scanf("%d", &v);
            graph * g = create_graph(v);

            int e;
            printf("Enter number of edges: ");
            scanf("%d", &e);

            while(e--)
            {
                int source, destination;
                scanf("%d%d", &source, &destination);
                add_edge_undirected(g, source, destination);
            }
            print_graph(g);
            printf("%d\n", is_cyclic_directed(g));
            printf("%d\n", is_cyclic_undirected(g));
            printf("%d\n", is_bipartite(g));
            continue;
        }
        break;
    }
}
