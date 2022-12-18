#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"MyDoublyList.h"

//global variables to work as simple counters and array boundaries
const int NameLength = 29, AmountOfLines = 60171, LineLength = 140;
int LoadedTerms = 0, Collisions = 0;

int hash_function(char* str);
void PrintOutput(char Strings[AmountOfLines][NameLength], int Occurances[ArrayCapacity]);
void printlist();
void printIntArray(int Occurances[ArrayCapacity]);
void removeChar(char *str, char garbage);

int main(){
    struct Person{
        char ID[7];
        char DepoID[11];
        char Surname[NameLength];
        char Forename[NameLength];
        char Age[3];
        char PersonType[15];
        char Gender[15];
        char Nationality[15];
        char Religion[15];
        char Occupation[20];
    };
    for(int i = 0; i < ArrayCapacity; i++){
       head[i] = NULL; 
    }
    FILE *RebellionData = fopen("people.csv", "r");
    if (RebellionData == NULL){
        printf("It didn't work");
    } else {
        printf("people.csv loaded!\n");
        char Disposal[LineLength];
        fgets(Disposal, LineLength, RebellionData);
        for(int i = 0; i < AmountOfLines; i++){
            struct Person *temp = (struct Person*)malloc(sizeof(struct Person));
            char Buffer[LineLength];
            fgets(Buffer, LineLength, RebellionData);
            char * token = strtok(Buffer, ",");
            strcpy((*temp).ID, token);
            removeChar((*temp).ID, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).DepoID, token);
            removeChar((*temp).DepoID, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Surname, token);
            removeChar((*temp).Surname, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Forename, token);
            removeChar((*temp).Forename, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Age, token);
            removeChar((*temp).Age, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).PersonType, token);
            removeChar((*temp).PersonType, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Gender, token);
            removeChar((*temp).Gender, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Nationality, token);
            removeChar((*temp).Nationality, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Religion, token);
            removeChar((*temp).Religion, '"');
            token = strtok(NULL, ",");
            strcpy((*temp).Occupation, token);
            removeChar((*temp).Occupation, '"');
            (*temp).Occupation[strcspn((*temp).Occupation, "\r\n")] = 0;
            (*temp).Occupation[strcspn((*temp).Occupation, "\r\n")] = 0;
            int gethash = hash_function((*temp).Surname);
            int SameName = 0;
            while (head[gethash] != NULL && SameName == 0){
                struct Person *Ptr = (*head[gethash]).DataPointer;
                if (strcmp((*Ptr).Surname, (*temp).Surname) == 0){
                    SameName = 1;
                } else{
                    gethash++;
                    if(gethash >= ArrayCapacity){
                        gethash = 0;
                    }
                    Collisions++;
                }
            }
            if(SameName == 0){
                LoadedTerms++;
            }
            InsertLast(temp, gethash);
        }
    }
    char Quotations = '"';
    double Terms = LoadedTerms;
    double ArrayCap = ArrayCapacity;
    double Load = (Terms/ArrayCap);
    printf(" Capacity  : %i\n", ArrayCapacity);
    printf(" Num Terms  : %i\n", LoadedTerms);
    printf(" Collisions  : %i\n", Collisions);
    printf(" Load  : %.3f\n", Load);
    printf("Enter term to get frequency or type %cquit%c to escape\n", Quotations, Quotations);
    char Name[NameLength];
    strcpy(Name, "NULL");
    while (strcmp(Name, "quit") != 0){
        fgets(Name, NameLength, stdin);
        Name[strcspn(Name, "\r\n")] = 0;
        if(strcmp(Name, "quit") != 0){
            int gethash = hash_function(Name);
            int SameName = 0;
            while (head[gethash] != NULL && SameName == 0){
                struct Person *Ptr = (*head[gethash]).DataPointer;
                if (strcmp((*Ptr).Surname, Name) == 0){
                    SameName = 1;
                } else {
                    gethash++;
                    if(gethash >= ArrayCapacity){
                        gethash = 0;
                    }
                }
            }
            if(SameName == 0){
                printf(">>> %s not in table\n", Name);
            } else {
                struct Node *ListPtr = (head[gethash]);
                printf(">>> Person ID     Deposition ID     Surname         Forename          Age   Person Type   Gender  Nationality    Religion      Occupation\n");
                while(ListPtr != NULL){
                    struct Person *Ptr = (*ListPtr).DataPointer;
                    printf("%8s%10c%-18s%-16s%-18s%-6s%-14s%-8s%-15s%-14s%s\n", (*Ptr).ID, ' ', (*Ptr).DepoID, (*Ptr).Surname, (*Ptr).Forename, (*Ptr).Age, (*Ptr).PersonType, (*Ptr).Gender, (*Ptr).Nationality, (*Ptr).Religion, (*Ptr).Occupation);
                    ListPtr = (*ListPtr).next;
                }
            }
        }
    }
    fclose(RebellionData);
}

// a hash function to return the hash key, this does not include linear probing, that is done in main
int hash_function(char* str){ 
    int hash = 0; 
    while(*str){
        hash = hash + *str;
        str++;
    }
    return(hash % ArrayCapacity);
}

void removeChar(char *str, char garbage) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}
