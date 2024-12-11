#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// Adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node* adjList[MAX_VERTICES];
    struct Node* reverseAdjList[MAX_VERTICES];
};

// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the graph
void initGraph(struct Graph* graph, int vertices) {
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->reverseAdjList[i] = NULL;
    }
}

// Function to add an edge to the graph (Directed)
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Reverse edge for the reverse graph
    newNode = createNode(src);
    newNode->next = graph->reverseAdjList[dest];
    graph->reverseAdjList[dest] = newNode;
}

// DFS (Depth First Search)
void DFS(struct Graph* graph, int vertex, bool visited[], int stack[], int* stackIndex) {
    visited[vertex] = true;

    struct Node* adjList = graph->adjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            DFS(graph, adjVertex, visited, stack, stackIndex);
        }
        adjList = adjList->next;
    }

    stack[*stackIndex] = vertex;
    (*stackIndex)++;
}

// DFS on reversed graph
void DFSReverse(struct Graph* graph, int vertex, bool visited[], int* component) {
    visited[vertex] = true;
    component[vertex] = 1;

    struct Node* adjList = graph->reverseAdjList[vertex];
    while (adjList != NULL) {
        int adjVertex = adjList->vertex;
        if (!visited[adjVertex]) {
            DFSReverse(graph, adjVertex, visited, component);
        }
        adjList = adjList->next;
    }
}

// Function to perform Kosaraju's Algorithm to find SCCs
void kosarajuSCC(struct Graph* graph) {
    bool visited[MAX_VERTICES] = { false };
    int stack[MAX_VERTICES];
    int stackIndex = 0;

    // Step 1: Perform DFS on the original graph and fill the stack with the vertices in finishing time order
    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            DFS(graph, i, visited, stack, &stackIndex);
        }
    }

    // Step 2: Reverse the graph is already done in `addEdge` function

    // Step 3: Perform DFS on the reversed graph, using the order in the stack
    // We will output the SCCs here
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    printf("Strongly Connected Components (SCCs):\n");

    while (stackIndex > 0) {
        int vertex = stack[--stackIndex];
        if (!visited[vertex]) {
            int component[MAX_VERTICES] = { 0 }; // To track the SCC

            // DFS on the reverse graph to get all nodes in this SCC
            DFSReverse(graph, vertex, visited, component);

            // Print the SCC
            printf("{ ");
            for (int i = 0; i < graph->numVertices; i++) {
                if (component[i]) {
                    printf("%d ", i);
                }
            }
            printf("}\n");
        }
    }
}

// Function to display the graph (adjacency list)
void displayGraph(struct Graph* graph) {
    printf("\nGraph Representation (Adjacency List):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* adjList = graph->adjList[i];
        printf("Vertex %d: ", i);
        while (adjList != NULL) {
            printf("%d -> ", adjList->vertex);
            adjList = adjList->next;
        }
        printf("NULL\n");
    }
}

int main() {
    struct Graph graph;
    int vertices, edges, src, dest, choice;

    // Input number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    initGraph(&graph, vertices);

    // Input edges
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);

        // Add directed edge to the graph
        if (src >= 0 && src < vertices && dest >= 0 && dest < vertices) {
            addEdge(&graph, src, dest);
        } else {
            printf("Invalid edge! Please enter vertices within the range of 0 to %d.\n", vertices - 1);
            i--;  // Decrement i to allow user to input the edge again
        }
    }

    // Main menu
    do {
        printf("\nMenu:\n");
        printf("1. Display Graph\n");
        printf("2. Find Strongly Connected Components (SCCs)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayGraph(&graph);
                break;
            case 2:
                kosarajuSCC(&graph);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
