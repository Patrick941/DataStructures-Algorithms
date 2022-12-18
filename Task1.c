#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

//global variables to work as simple counters and array boundaries
const int NameLength = 16, AmountOfLines = 51, ArrayCapacity = 53;
int LoadedTerms = 0, Collisions = 0;

int hash_function(char* str);
void PrintOutput(char Strings[AmountOfLines][NameLength], int Occurances[ArrayCapacity]);
void printlist(char Strings[ArrayCapacity][NameLength]);
void printIntArray(int Occurances[ArrayCapacity]);

int main(){
    char NameStrings[AmountOfLines][NameLength];
    FILE *IrishNames = fopen("Names.csv", "r");
    if (IrishNames == NULL){
        printf("It didn't work");
    } else {
        printf("names.csv loaded!\n");
        for(int i = 0; i < AmountOfLines; i++){
            fgets(NameStrings[i], NameLength, IrishNames);
            NameStrings[i][strcspn(NameStrings[i], "\r\n")] = 0;
            NameStrings[i][strcspn(NameStrings[i], "\r\n")] = 0;
        }
    }
    char HashedStrings[ArrayCapacity][NameLength];
    int Occurances[ArrayCapacity];
    for(int i = 0; i < ArrayCapacity; i++){
        Occurances[i] = 0;
    }
    for(int i = 0; i < ArrayCapacity; i++){
        strcpy(HashedStrings[i], "`");
    }
    for(int i = 0; i < AmountOfLines; i++){
        int gethash = hash_function(NameStrings[i]);
        //printf("%c \n", HashedStrings[gethash][0]);
        short Duplicate = 1;
        while ( HashedStrings[gethash][0] != '`' && Duplicate == 1){
            if ((strcmp(HashedStrings[gethash], NameStrings[i])) == 0){
                //printf("%s is the same as %s \n" ,HashedStrings[gethash], NameStrings[i]);
                //printf("The Occurance counter of %s has been increased to %i \n", HashedStrings[gethash], Occurances[gethash]);
                Occurances[gethash]++;
                Duplicate = 0;
            }else{
                Collisions++;
                gethash++;
                if(gethash >= ArrayCapacity){
                    gethash = 0;
                }
            }
        }
        if (Duplicate == 1){
            strcpy(HashedStrings[gethash], NameStrings[i]); 
            LoadedTerms++;
            //printf("%s \n", HashedStrings[gethash]);
            Occurances[gethash] = 1;
        }
    }
    PrintOutput(HashedStrings, Occurances);
    fclose(IrishNames);
    return 0;
}

//A function to print all necessary output
void PrintOutput(char Strings[ArrayCapacity][NameLength], int Occurances[ArrayCapacity]){
    char percent = '%', quotations = '"';
    double Load = (LoadedTerms * 100) / ArrayCapacity;
    printf("        capacity    : %i\n", ArrayCapacity);
    printf("        Num Terms   : %i\n", LoadedTerms);
    printf("        Collisions  : %i\n", Collisions);
    printf("        Load        : %.2f%c\n", Load, percent);
    printf("Enter term to get frequency or type %cquit%c to escape\n", quotations, quotations);
    printf(">>> ");
    char Name[16];
    fgets(Name, NameLength, stdin);
    Name[strcspn(Name, "\r\n")] = 0;
    int truth = strcmp(Name, "quit");
    while(truth != 0){
        int NameHashKey = hash_function(Name);
        int StringPresent = 1 ;
        while(strcmp(Strings[NameHashKey], Name) != 0  && StringPresent == 1){
            NameHashKey++;
            if(NameHashKey >= ArrayCapacity){
                NameHashKey = 0;
            }
            if(Strings[NameHashKey][0] == '`'){
                StringPresent = 0;
                printf("%s is not pressent\n>>> ", Name);
            }
        }
        //printf("The name is %s and the hash key is %i and the Occurance count is %i \n", Strings[NameHashKey], NameHashKey, Occurances[NameHashKey]);
        if (StringPresent == 1){
            printf("%s %i \n>>> ", Name, Occurances[NameHashKey]);
        }
        fgets(Name, NameLength, stdin);
        Name[strcspn(Name, "\r\n")] = 0;
        truth = strcmp(Name, "quit");
    }
}

// A testing function to visualist the hash table, as the array is for testing little effort was made to make it efficient
void printlist(char Strings[ArrayCapacity][NameLength]){
    for (int i = 0; i < ArrayCapacity; i++){
        printf("%s \n", Strings[i]);
    }
}

//Another Testing function to visualise the occurances of each Name in the file, as the array is for testing, little effort was made to make it efficient
void printIntArray(int Occurances[ArrayCapacity]){
    for(int i = 0 ; i < ArrayCapacity; i++){
        printf("%i \n", Occurances[i]);
    }
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