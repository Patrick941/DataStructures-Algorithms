#include"t2.h"
#include"t1.h"

int ArrayCapacity = 1000;


void Swap(int *Value1, int *Value2);
void Partition(int arr[], int LowerIndex, int UpperIndex);

int main(){
    int Data[ArrayCapacity];
    fill_with_duplicates(Data, ArrayCapacity);
    quickSort(Data, ArrayCapacity);
    printArray(Data, ArrayCapacity);
}

//A function to implement selection sort without counting swaps and comparisons
void selectionSort(int arr[], int size){
    //Initialise the variable that will be used to remember the lower Number each time the loop goes through the Array
    int LocalMinValue, LocalMinIndex; 
    for(int i = 0; i < size; i++){
        LocalMinIndex = i;     
        LocalMinValue = arr[i];   
        //The next loop which goes through the array starts at i becuase everything that is before i should already be sorted
        for(int j = i; j < size; j++){
            //If the data at the current index is lower than the current local min value set the local min index to j and update the value of localminvalue to the value at this index
            if (arr[j] < LocalMinValue){
                LocalMinIndex = j;
                LocalMinValue = arr[j];
            }
        }
        //This is swapping the positions of the data at index i and the data which has the lowest value
        arr[LocalMinIndex] = arr[i];
        arr[i] = LocalMinValue;
    }
}

//A function to implement insertion sort without counting swaps and comparisons
void insertionSort(int arr[], int size){
    //Start at first element, check that everything to the left of it is higher than it, this is always true
    //for the rest of the elements scroll through the array until a number to the left is lower than it, then place the element to the right of this number that is lower than it
    for (int i = 0; i < size; i++){
        int PointFound = 0;
        for(int j = i; j >  0 && PointFound == 0; j--){
            //Test if j >0 as if j is not greater than 0, than there is no number to the left of  it and it should be inserted at index 0
            //Test whether the number at index j is less than the number at index i, if it is, leaving the loop, else swap the values
            if(arr[j - 1] < arr[j]){
                PointFound = 1;
            }
            else {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

//A function to implement quick sort without counting swaps and comparisons
void quickSort(int arr[], int size){
    Partition(arr, 0, ArrayCapacity - 1);
}

void Partition(int arr[], int LowerIndex, int UpperIndex){
    int i, j, pivot;
    if(LowerIndex < UpperIndex){
      pivot = LowerIndex;
      i = LowerIndex;
      j = UpperIndex;

        while(i<j){
            while(arr[i] <= arr[pivot] && i < UpperIndex){
                i++;
            }
            while(arr[j] > arr[pivot])
                j--;
            if(i<j){
                Swap(&arr[i], &arr[j] );
            }
        }
        Swap(&arr[pivot], &arr[j]);
        Partition(arr ,LowerIndex ,j-1);
        Partition(arr,j+1,UpperIndex);
   }
}


//A function to swap the values that the pointer arguments are pointing too
void Swap(int *Value1, int *Value2){
    int Temp = *Value1;
    *Value1 = *Value2;
    *Value2 = Temp;
    return;
}