#include <stdio.h>
#include <stdlib.h>

// Node for adjacency list
struct Node 
{
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph 
{
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

//node creation
struct Node* createNode(int v) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Creating graph
struct Graph* createGraph(int vertices) 
{
    int i;
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++) 
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add edge (undirected)
void addEdge(struct Graph* graph, int src, int dest) 
{
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

//for depth first searching 
void DFS(struct Graph* graph, int vertex) 
{
    int connectedVertex;
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d\t", vertex);

    while (temp != NULL) 
    {
        connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) 
        {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Printing the list (optional helper)
void printGraph(struct Graph* graph) 
{
    int i;
    for (i = 0; i < graph->numVertices; i++) 
    {
        struct Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp) 
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Main
int main() 
{
    int V = 6;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    printf("\nAdjacency List :\n\n");
    printGraph(graph);

    printf("\nDFS traversal starting from vertex 0: \n");
    DFS(graph, 0);
    printf("\n");

    return 0;
}
