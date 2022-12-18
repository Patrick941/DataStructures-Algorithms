#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

//Function to implement a graph for the letters up the alphabet up for the number of nodes
//assign an index to each letter which is it's posiition in the alphabet
Queue * qHead = NULL;
Queue * lHead = NULL;
int numberOfNodes = 0;

Graph* create_graph(int num_nodes){
    if(num_nodes > 26){
        printf("too many nodes for alphabet");
        return NULL;
    }
    Graph * headPointer = NULL;
    int charASCII = 65;

    headPointer = (Graph*)malloc(sizeof(Graph) * num_nodes);
    headPointer[0].value = charASCII;
    headPointer[0].boolean = 0;
    headPointer[0].edges = NULL;
    //printf("%c has an index %i and has an address %p\n", (*headPointer).value, (*headPointer).index, headPointer);
    charASCII++;
    
    for(int i = 1; i < num_nodes; i++){
        headPointer[i].value = charASCII;
        headPointer[i].boolean = 0;
        headPointer[i].edges = NULL;
        charASCII++;
        //printf("%c has an index %i and has an address %p\n", (*ptr).value, (*ptr).index, ptr);
    }
    numberOfNodes = num_nodes;
    return headPointer;
}

void add_edge(Graph *g, int from, int to){
    if (g != NULL && &g[from].edges != NULL){
        insertFirst(g, &g[from].edges, from, to);
    }
}

void insertFirst(Graph * g, Queue ** headPointer, int from, int to){
    Queue * head = NULL;
    if(headPointer != NULL){
        head = *headPointer;
    }
    Queue * temp = NULL;
    temp = (Queue*)malloc(sizeof(Queue));
    if(g != NULL && temp != NULL){
        (*temp).index = to;
        (*temp).next = head;
        head = temp;
        g[from].edges = temp;
    }
}


int depth = 0;
void dfs(Graph* g, int origin){
    if (g == NULL){
        return;
    }
    if (depth == 0){
        printf("DFS:");
    }
    depth++;
    //printf("%-2c  ", (*edgePtr).value);
    printf(" %c ", origin + 65);
    g[origin].boolean = 1;

    int edgesArray[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++){
        edgesArray[i] = 0;
    }
    edgesArray[origin] = -1;
    Queue * temp = (g[origin]).edges;
    for(int i = 0; i < numberOfNodes && temp != NULL; i++){
       int index = (*temp).index;
       edgesArray[index] = 1;
       if ((*temp).next != NULL){
            temp = (*temp).next;
       }
    }

    for(int i = 0; i < numberOfNodes; i++){
        if(g[i].boolean == 0 && edgesArray[i] == 1){
            dfs(g, i);
        }
    }
    depth--;
    if(depth == 0){
        printf("\n");
        for(int i = 0; i < numberOfNodes; i++){
            g[i].boolean = 0;
        }
    }
}

void bfs(Graph * g, int origin){
    if (g == NULL){
        return;
    }
    if (depth == 0){
        printf("BFS ");
    }
    depth++;
    int edgesArray[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++){
        edgesArray[i] = 0;
    }
    edgesArray[origin] = -1;
    Queue * temp = g[origin].edges;
    for(int i = 0; i < numberOfNodes && temp != NULL; i++){
       int index = (*temp).index;
       edgesArray[index] = 1;
       if ((*temp).next != NULL){
            temp = (*temp).next;
       }
    }
    //printf("%-2c  ", (*edgePtr).value);
    printf(" %c ", origin + 65);
    g[origin].boolean = 1;
    for(int i = 0; i < numberOfNodes; i++){
        if(g[i].boolean == 0 && edgesArray[i] == 1){
            insertLast(g, &qHead, i);
            if(qHead == NULL){
                printf("qHead is NULL");
            }
        }
    }

    while(qHead != NULL){
        //printList(qHead);
        int nextIndex = popFirst(&qHead);
        if(g[nextIndex].boolean == 0){
            bfs(g, nextIndex);
        }
    }
    depth--;
    if(depth == 0){
        printf("\n");
        for(int i = 0; i < numberOfNodes; i++){
            g[i].boolean = 0;
        }
    }
}

void printList(Queue * list){
    while(list != NULL){
        printf("%c ->", (*list).index + 65);
        list = (*list).next;
    }
    printf("0\n");
}

void insertLast(Graph * g, Queue ** headPointer, int index){
    Queue * temp = (Queue*)malloc(sizeof(Queue));
    Queue * head = qHead;
    if(head == NULL){
        *headPointer = temp;
        (*temp).index = index;
        (*temp).next = NULL;
        return;
    } else {
        Queue * ptr = head;
        while((*ptr).next != NULL){
            ptr = (*ptr).next;
        }
        (*ptr).next = temp;
        (*temp).index = index;
        (*temp).next = NULL;
    }
}

int popFirst(Queue ** headPointer){
    Queue * head = *headPointer;
    if(qHead == NULL){
        return -1;
    }
    int output = (*head).index;
    Queue * temp = head;
    if ((*head).next != NULL){
        *headPointer = (*head).next;
        head = (*head).next;
    } else {
        *headPointer = NULL;
        head = NULL;
    }
    free(temp);
    return output;
}

int popLast(Queue ** head){
    Queue * temp = *head;
    Queue * trail = NULL;
    if (temp == NULL){
        return -1;
    }
    while((*temp).next != NULL){
        trail = temp;
        temp = (*temp).next;
    }
    
    if(trail != NULL){
        (*trail).next = NULL;
    } else {
        *head = NULL;
        free(temp);
        return -1;
    }
    int output = (*temp).index;
    //printf("deleting value %c \n", (*temp).index + 65);
    (*trail).next = NULL;
    free(temp);
    return output;
}

void delete_graph(Graph * graph){
    for(int i = 0; i < numberOfNodes; i++){
        Queue * ptr = graph[i].edges;
        while(popLast(&ptr) != -1){
            popLast(&ptr);
        }
    }
    free(graph);
}

void printGraph(Graph * g){
    for(int i = 0; i < numberOfNodes; i++){
        Queue * ptr = g[i].edges;
        printf("%c :", g[i].value);
        while(ptr != NULL){
            int ASCIIvalue = (*ptr).index + 65;
            char ASCIIChar = ASCIIvalue;
            printf("%c -> ", ASCIIChar);
            ptr = (*ptr).next;
        }
        printf("0 \n");
    }
}