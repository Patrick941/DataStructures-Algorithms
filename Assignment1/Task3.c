#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>

//global variables to work as simple counters and array boundaries
const int NameLength = 16, AmountOfLines = 51, ArrayCapacity = 53;
int LoadedTerms = 0, Collisions = 0;

//function declarations
int PrimaryHash(char* str);
void PrintOutput(char Strings[AmountOfLines][NameLength], int Occurances[ArrayCapacity]);
void printlist(char Strings[ArrayCapacity][NameLength]);
void printIntArray(int Occurances[ArrayCapacity]);
int SecondaryHash(char* s);

int main(){
    //An array of strings in unhashed order
    char NameStrings[AmountOfLines][NameLength];
    FILE *IrishNames = fopen("Names.csv", "r");
    if (IrishNames == NULL){
        printf("It didn't work");
    } else {
        //Reading in each line and removing the end lines from them
        printf("names.csv loaded!\n");
        for(int i = 0; i < AmountOfLines; i++){
            fgets(NameStrings[i], NameLength, IrishNames);
            NameStrings[i][strcspn(NameStrings[i], "\r\n")] = 0;
            NameStrings[i][strcspn(NameStrings[i], "\r\n")] = 0;
        }
    }
    //An Array to store strings in an index of their hash value
    char HashedStrings[ArrayCapacity][NameLength];
    int Occurances[ArrayCapacity];
    for(int i = 0; i < ArrayCapacity; i++){
        Occurances[i] = 0;
    }
    //Setting this array to store only the ` key to distinguish between filled and unfilled indexes of the array
    for(int i = 0; i < ArrayCapacity; i++){
        strcpy(HashedStrings[i], "`");
    }
    //Storing the strings at the index of their hash values, we then use linear probing to resolve collissions
    for(int i = 0; i < AmountOfLines; i++){
        short Duplicate = 1;
        int iteration = 0;
        int gethash = (PrimaryHash(NameStrings[i]) + (iteration * SecondaryHash(NameStrings[i]))) % ArrayCapacity;
        while ( HashedStrings[gethash][0] != '`' && Duplicate == 1){
            if ((strcmp(HashedStrings[gethash], NameStrings[i])) == 0){
                Occurances[gethash]++;
                Duplicate = 0;
            }else{
                iteration++;
                gethash = (PrimaryHash(NameStrings[i]) + (iteration * SecondaryHash(NameStrings[i]))) % ArrayCapacity;
                Collisions++;
                if(gethash >= ArrayCapacity){
                    gethash = 0;
                }
            }
        }
        if (Duplicate == 1){
            strcpy(HashedStrings[gethash], NameStrings[i]); 
            LoadedTerms++;
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
        int StringPresent = 1 ;
        int iteration = 0;
        int gethash = (PrimaryHash(Name) + (iteration * SecondaryHash(Name))) % ArrayCapacity;
        while (Strings[gethash][0] != '`' && StringPresent == 1){
            if ((strcmp(Strings[gethash], Name)) == 0){
                StringPresent = 0;
            }else{
                iteration++;
                gethash = (PrimaryHash(Name) + (iteration * SecondaryHash(Name))) % ArrayCapacity;
                if(gethash >= ArrayCapacity){
                    gethash = 0;
                }
            }
        }
        //printf("The name is %s and the hash key is %i and the Occurance count is %i \n", Strings[NameHashKey], NameHashKey, Occurances[NameHashKey]);
        if (StringPresent == 0){
            printf("%s %i \n>>> ", Name, Occurances[gethash]);
        }
        else{
            printf("%s is not pressent\n>>>", Name);
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


int PrimaryHash(char* str){
    int hash = 0; 
    while(*str){
        hash = hash + *str;
        str++;
    }
    return(hash % ArrayCapacity);
}

int SecondaryHash(char* s){
    int hash = 0;
    while(*s){
        hash = (1+ (hash + *s)) % (ArrayCapacity);
        s++;
    }
    return hash;
}
