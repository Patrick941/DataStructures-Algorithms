#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

//functions to slightly simplify printing a character
void print(char data);
void println(char data);

//A function to find the next character in the BST
Tree_Node * nextVal(Tree_Node * originalPtr);

//A function to find the lowest value character in the BST
Tree_Node * getLowestVal(Tree_Node * headPointer);

//A function to find the next root to delete
Tree_Node * getRootToDelete(Tree_Node * ptr);

//A function that frees the pointer being pointer at and also sets all pointers pointing at it to NULL
void deleteNode(Tree_Node ** ptr);

//A function to insert a character into the binary search tree at the correct position
void tree_insert(Tree_Node** root, char data){
    //To create first Node if there currently isnt any values
    if(*root == NULL){
        *root = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*(*root)).data = data;
        (*(*root)).branch1 = NULL;
        (*(*root)).branch2 = NULL;
        (*(*root)).prev = NULL;
        return;
    }
    //For every other node, find the new position for the character and assign the new addresses to pointers
    Tree_Node * temp = (Tree_Node*)malloc(sizeof(Tree_Node));
    Tree_Node * destinationPtr = *root;
    (*temp).data = data;
    (*temp).branch1 = NULL;
    (*temp).branch2 = NULL;
    (*temp).prev = NULL;
    int exitCondition = 0;
    int value = data;
    while(exitCondition == 0){
        if(value <= (*destinationPtr).data){
            if ((*destinationPtr).branch1 != NULL){
                destinationPtr = (*destinationPtr).branch1;
            }
            else{
                (*temp).prev = destinationPtr;
                (*destinationPtr).branch1 = temp;
                exitCondition = 1;
            }
        } else {
            if ((*destinationPtr).branch2 != NULL){
                destinationPtr = (*destinationPtr).branch2;
            }
            else{
                (*temp).prev = destinationPtr;
                (*destinationPtr).branch2 = temp;
                exitCondition = 1;
            }
        }
    }
    return;
    
}

//A function which creates a Binary search tree with the data provided in the character array
Tree_Node* create_bst (char data[]){
    Tree_Node * headPointer = NULL;
    {
        int i = 0;
        while(data[i] != '\0'){
            tree_insert(&headPointer, data[i]);
            i++;
        }
    }
    return headPointer;
}

//A function which searches for a certain character and if the character is present it will return a pointer to the Node holding the character
Tree_Node* tree_search(Tree_Node* root, char data){
    int charCast = data;
    for(;;){
        if((*root).data == charCast && root != NULL){
            return root;
        } else if ((*root).data > charCast && (*root).branch1 != NULL){
            root = (*root).branch1;
        } else if ((*root).data < charCast && (*root).branch2 != NULL){
            root = (*root).branch2;
        } else {
            break;
        }  
    }   
    return NULL;
}

//A function which will print the sorted tree of a binary search tree
void tree_print_sorted(Tree_Node* root){
    Tree_Node * ptr = NULL;
    if (root == NULL){
        return;
    } else{
        ptr = getLowestVal(root);
        print((*ptr).data);
        while(ptr != NULL){
            ptr = nextVal(ptr);
            if(ptr != NULL){
                print((*ptr).data);
            }
        }
    }
}


//A function which will delete every node from a tree and free up the memory
void tree_delete(Tree_Node* root){
    for(;;){
        Tree_Node * ptr = root;
        if(((*root).branch1 == NULL) && (*root).branch2 == NULL){
            free(root);
            return;
        } else {
            ptr = getRootToDelete(ptr);
            deleteNode(&ptr);
        }
    }
}

Tree_Node * getRootToDelete(Tree_Node * ptr){
    if((*ptr).branch1 != NULL){
        ptr = (*ptr).branch1; 
        ptr = getRootToDelete(ptr);
    } else if ((*ptr).branch2 != NULL){
        ptr = (*ptr).branch2;
        ptr = getRootToDelete(ptr);
    }
    return ptr;
}

void deleteNode(Tree_Node ** ptr){
    if((*(**ptr).prev).branch1 == *ptr){
        (*(**ptr).prev).branch1 = NULL;
    } else if((*(**ptr).prev).branch2 == *ptr){
        (*(**ptr).prev).branch2 = NULL;
    }
    free(*ptr);
    *ptr = NULL;
}

Tree_Node * getLowestVal(Tree_Node * headPointer){
    while ((*headPointer).branch1 != NULL){
        headPointer = (*headPointer).branch1;
    }
    return headPointer;
}

Tree_Node * nextVal(Tree_Node * originalPtr){
    int currentval = (*originalPtr).data;
    if((*originalPtr).branch2 != NULL){
        originalPtr = (*originalPtr).branch2;
        originalPtr = getLowestVal(originalPtr);
        return originalPtr;
    } else{
        while((*(*originalPtr).prev).data < currentval){
            originalPtr = (*originalPtr).prev;  
            if((*originalPtr).prev == NULL){
                return NULL;
            }
        }
        originalPtr = (*originalPtr).prev;
        return originalPtr;
    }
    return NULL;
}

void print(char data){
    printf("%c", data);
}

void println(char data){
    printf("%c\n", data);
}