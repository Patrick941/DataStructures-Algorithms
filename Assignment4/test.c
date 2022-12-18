#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2.h"
#include <stdio.h>

void setMatrix(int size);

void printMatrix(int size);

int maxLineLength = 200;

Graph *verticesPtr = NULL;

void cleanString(char *str, int size);

void printGraph();

int ** edgesMatrix = NULL;

int * keys = NULL;

int main(){
    //int edgesMatrix[amountOfLines][amountOfLines];
    //Graph arr[amountOfLines];
    load_vertices("vertices.csv");
    load_edges("edges.csv");
    //printMatrix(amountOfLines);
    //printGraph();
    free_memory();
}

void free_memory(){
    for(int i = 0; i < amountOfLines; i++){
        free(edgesMatrix[i]);
    }
    free(edgesMatrix);
    free(keys);
    free(verticesPtr);
}

int load_edges(char *fname){
    edgesMatrix = (int **)malloc(sizeof(int) * allocationSize);
    for(int i = 0; i < amountOfLines; i++){
        edgesMatrix[i] = (int*)malloc(allocationSize * sizeof(int));
    }
    setMatrix(amountOfLines);
    FILE * edgesCSV = fopen("edges.csv", "r");
    for(int i = 0; i < amountOfLines; i++){
        char buffer[maxLineLength];
        fgets(buffer, maxLineLength, edgesCSV);
        cleanString(buffer, maxLineLength);
        char * token = strtok(buffer, ",");
        char firstAsString[9];
        char secondAsString[9];
        char weightAsString[9];
        int firstVertex;
        int secondVertex;
        int weight;
        strcpy(firstAsString, token);
        cleanString(firstAsString, 9);
        firstVertex = atoi(firstAsString);
        token = strtok(NULL, ",");
        strcpy(secondAsString, token);
        cleanString(secondAsString, 9);
        secondVertex = atoi(secondAsString);
        token = strtok(NULL, ",");
        strcpy(weightAsString, token);
        cleanString(weightAsString, 9);
        weightAsString[strcspn(weightAsString, "\n")] = 0;
        weight = atoi(weightAsString);
        edgesMatrix[keys[firstVertex]][keys[secondVertex]] = weight;
    }
    printf("edges.csv was loaded\n");
}

void setMatrix(int size){
    for(int i = 0; i < amountOfLines; i++){
        for(int j = 0; j < amountOfLines; j++){
            if(i != j){
                edgesMatrix[i][j] = 0;
            } else {
                edgesMatrix[i][j] = -1;
            }
        }
    }
}
void printMatrix(int size){
    for(int i = 0; i < amountOfLines; i++){
        for(int j = 0; j < amountOfLines; j++){
            if(edgesMatrix[i][j] != 0 && edgesMatrix[i][j] != -1){
                printf("%-10i", edgesMatrix[i][j]);
            }
        }
        printf("\n");
    }
}

int load_vertices(char *fname){
    verticesPtr = (Graph*)malloc(sizeof(Graph) * allocationSize);
    FILE * verticesCSV = fopen(fname, "r");
    char bin[maxLineLength];
    fgets(bin, maxLineLength, verticesCSV);
    keys = (int*)malloc(sizeof(int) * 7700);
    for(int i = 0; i < amountOfLines; i++){
        char buffer[maxLineLength];
        fgets(buffer, maxLineLength, verticesCSV);
        cleanString(buffer, maxLineLength);
        char * token = strtok(buffer, ",");
        char IDAsString[7];
        char XCordsAsString[16];
        char YCordsAsString[16];
        strcpy(IDAsString, token);
        (verticesPtr[i]).ID = atoi(IDAsString);
        token = strtok(NULL, ",");
        strcpy((verticesPtr[i]).stopName, token);
        token = strtok(NULL, ",");
        strcpy(XCordsAsString, token);
        (verticesPtr[i]).XCords = atof(XCordsAsString);
        token = strtok(NULL, ",");
        strcpy(YCordsAsString, token);
        YCordsAsString[strcspn(YCordsAsString, "\n")] = 0;
        (verticesPtr[i]).YCords = atof(YCordsAsString);
        keys[(verticesPtr[i]).ID] = i;
    }
    printf("vertices.csv was loaded\n");
    return 0;
}

void printGraph(){
    for(int i = 0; i < amountOfLines; i++){
        printf("ID: %i, Key is: %i, Name: %s, XCords: %f, YCords: %f\n", (verticesPtr[i]).ID, keys[(verticesPtr[i]).ID], (verticesPtr[i]).stopName, (verticesPtr[i]).XCords, (verticesPtr[i]).YCords);
    }
}

void cleanString(char *str, int size){
    for(int i = 0; i < size - 1; i++){
        if(str[i] == '\"' ){
            for(int j = i; j < size - 1; j++){
                str[j] = str[j+1];
            }
        }
    }
} 