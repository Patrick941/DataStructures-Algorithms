#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2.h"
#include <stdio.h>

int listSize = 0;

const int maxLineLength = 200;
const int amountOfLines = 4806;
const int allocationSize = 9612;
const int amountOfEdges = 6180;

int journeyLength = 99999999;

Graph *verticesPtr = NULL;

int ** edgesMatrix = NULL;

int * keys = NULL;

Queue *head = NULL;


#include <stdio.h>
#include <stdlib.h>
#include "t2.h"
#include <stdio.h>


int
main ( int argc, char *argv[] ) {

	if ( argc < 3 ) {
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if ( !load_vertices( argv[1] ) ) {
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if ( !load_edges( argv[2] ) ) {
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

	


    // get the start and end point
    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);

	shortest_path(startingNode, endingNode);
    

	free_memory();

	return EXIT_FAILURE;
}

void printEdges(int index){
	printf("edges for node index %i with key %i\n", index, keys[index]);
	for(int i = 0; i < amountOfLines; i++){
		//printf("%i  ", edgesMatrix[keys[index]][i]);
		if(edgesMatrix[keys[index]][i] > 0){
			printf("%i  ", verticesPtr[i].ID);
		}
	}
	printf("\n");
}

void printStop(int ID, char name[], float X, float Y){
	printf("%-5i%-19s %f %f\n", ID, name, X, Y);
    //printf("%i %s\n", ID, name);
}

int depth = 0, found = 0;
void shortest_path(int startNode, int endNode){
    int startIndex = keys[startNode];
	int endIndex = keys[endNode];
	if (depth == 0){
		verticesPtr[startIndex].totalWeight = 0;
	}
	depth++;
	//printStop(verticesPtr[startIndex].ID, (verticesPtr[startIndex]).stopName, (verticesPtr[startIndex]).XCords, (verticesPtr[startIndex].YCords));
    if (verticesPtr == NULL || verticesPtr[startIndex].totalWeight >= journeyLength){
		found = 1;
		depth--;
		if (depth == 0){
			printPath(endNode);
		}
        return;
    }
	if(startIndex == endIndex && verticesPtr[startIndex].totalWeight < journeyLength){
		journeyLength = verticesPtr[startIndex].totalWeight;
	} else if (verticesPtr[startIndex].totalWeight < journeyLength){
		for(int i = 0; i < amountOfLines; i++){
			if(edgesMatrix[startIndex][i] > 0 && startIndex != i && (verticesPtr[startIndex].totalWeight + edgesMatrix[startIndex][i]) <  verticesPtr[i].totalWeight){
				verticesPtr[i].totalWeight = verticesPtr[startIndex].totalWeight + edgesMatrix[startIndex][i];
				verticesPtr[i].path = startIndex;
				insertLast(verticesPtr[i].ID);
				//printf("i is %i, ID is %i, start weight is %i, junction weight is %i, listSize is %i\n", i, verticesPtr[i].ID, verticesPtr[startIndex].totalWeight, edgesMatrix[startIndex][i], listSize);
			}
		}
	}
	while(head != NULL){
		int nextNode = popFirst();
		shortest_path(nextNode, endNode);
	}
	depth--;
	if (found == 0 && depth == 0){
		printf("route not found\n");
	} else if (depth == 0 && found == 1){
		printPath(endNode);
		cleanWeights();
		found = 0;
	}
}

void printPath(int index){
	int endIndex = keys[index];
	int currentIndex = endIndex;
	int path[100];
	int pathLength = 0;
	for(int i = 0; i < 100; i++){
		path[i] =  currentIndex;
		currentIndex = verticesPtr[currentIndex].path;
		if(currentIndex == -1){
			pathLength = i+1;
			break;
		}
	}
	for(int i = pathLength - 1; i >= 0; i--){
		printStop(verticesPtr[path[i]].ID, (verticesPtr[path[i]]).stopName, (verticesPtr[path[i]]).XCords, (verticesPtr[path[i]].YCords));
		/*if(i == 0){
			printf("Total weight is %i\n",(verticesPtr[path[i]]).totalWeight);
		}*/
	}
	
	//printStop(verticesPtr[startIndex].ID, (verticesPtr[startIndex]).stopName, (verticesPtr[startIndex]).XCords, (verticesPtr[startIndex].YCords));
}

void cleanWeights(){
	for(int i = 0; i < allocationSize; i++){
		verticesPtr[i].totalWeight = 99999999;
		verticesPtr[i].path = -1;
	}
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
    for(int i = 0; i < amountOfEdges; i++){
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
		edgesMatrix[keys[secondVertex]][keys[firstVertex]] = weight;
    }
    printf("Loaded 6179 edges\n");
    return 1;
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
		verticesPtr[i].totalWeight = 99999999;
		verticesPtr[i].path = -1;
    }
    printf("Loaded 4806 vertices\n");
    return 1;
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


void insertLast(int index){
	listSize++;
    Queue * temp = (Queue*)malloc(sizeof(Queue));
    if(head == NULL){
        head = temp;
        (*head).index = index;
        (*head).next = NULL;
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

int popFirst(){
    if(head == NULL){
        return -1;
    }
	listSize--;
    int output = (*head).index;
    Queue * temp = head;
    if ((*head).next != NULL){
        head = (*head).next;
    } else {
        head = NULL;
    }
    free(temp);
    return output;
}