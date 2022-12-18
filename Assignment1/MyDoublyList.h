#include<stdlib.h>
const int ArrayCapacity = 99991;

struct Node *head[99991];
struct Node *tail[99991];

struct Node {
    void *DataPointer;
    struct Node *next;
    struct Node *prev;
};

void InsertFirst(void *Value, int index){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if (head[index] != NULL){
        (*head[index]).prev = temp;
        (*temp).next = head[index];
    } else{
        tail[index] = temp;
        (*temp).next = NULL;
    }
    (*temp).DataPointer = Value;
    (*temp).prev = NULL;
    head[index] = temp;
}

void InsertLast(void *Value, int index){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if (tail[index] != NULL){
        (*tail[index]).next = temp;
        (*temp).prev = tail[index]; 
    } else{
        (*temp).prev = NULL;
        head[index] = temp;
    }
    (*temp).DataPointer = Value;
    (*temp).prev = NULL;
    tail[index] = temp;
}
