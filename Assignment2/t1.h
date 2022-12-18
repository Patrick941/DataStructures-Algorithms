#ifndef T1_H_
#define T1_H_
#include<stdio.h>
#include<stdlib.h>

void fill_ascending(int *array, int size);
void fill_descending(int *array, int size);
void fill_uniform(int *array, int size);
void fill_with_duplicates(int *array, int size);
void fill_without_duplicates(int *array, int size);
void printArray(int *arr, int size);

void fill_ascending(int *array, int size){
    for (int i = 0; i < size ; i++){
        array[i] = i;
    }
}

void fill_descending(int *array, int size){
    for(int i = 0; i < size ; i++){
        array[i] = size - i - 1;
    }
}

void fill_uniform(int *array, int size){
    int Number = rand() % size;
    for(int i = 0; i < size; i++){
        array[i] = Number;
    }
}

void fill_with_duplicates(int *array, int size){
    for(int i = 0; i < size; i++){
        array[i] = rand() % size;
    }
}

void fill_without_duplicates(int *array, int size){
    int TempArray[size];
    for(int i = 0; i < size; i++){
        TempArray[i] = i;
    }
    for(int i = 0; i < size; i++){
        int Num = rand() % size;
        int EndLoop = 0;
        while (EndLoop == 0){
            if(TempArray[Num] != -1){
                array[i] = Num;
                TempArray[Num] = -1;
                EndLoop = 1;
            }
            else{
                Num = rand() % size;
            }
        }
    }
}

void printArray(int *arr, int size){
    printf("Start of array\n");
    for (int i = 0; i < size; i++){
        printf("%i \n", arr[i]);
    }
    printf("\n");
}

#endif