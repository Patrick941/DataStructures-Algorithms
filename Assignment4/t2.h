#ifndef T2_H_
#define T2_H_

typedef struct Graph Graph;
struct Graph{
    char stopName[40];
    int path;
    int ID;
    double XCords;
    double YCords;
    int totalWeight;
};

typedef struct Queue Queue;
struct Queue{
    int index;
    Queue * next;
};


int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used
void setMatrix(int size);
void printMatrix(int size);
void printEdges(int index);
void printPath(int index);
void cleanString(char *str, int size);
void cleanWeights();
void printGraph();
void insertLast( int index);
int popFirst();

#endif