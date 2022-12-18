#ifndef T1_H_
#define T1_H_

typedef struct Queue Queue;
struct Queue{
    int index;
    Queue * next;
};

typedef struct Graph Graph;
struct Graph{
    char value;
    Queue * edges;
    int boolean;
};

void insertLast(Graph * g, Queue ** headPointer, int index);
void insertFirst(Graph * g, Queue ** headPointer, int from, int to);
int popFirst(Queue ** headPointer);

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void delete_graph(Graph * graph);
void recursive_delete_graph(Graph * graph, int origin);
void printGraph(Graph * g);
void printList(Queue * list);
int popLast(Queue ** head);



#endif