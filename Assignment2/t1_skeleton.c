#include"t1.h"

const int arrayCapacity = 10;

int main(){
    int array[arrayCapacity];
    fill_ascending(array, arrayCapacity);
    printArray(array, arrayCapacity);
    fill_descending(array, arrayCapacity);
    printArray(array, arrayCapacity);
    fill_uniform(array, arrayCapacity);
    printArray(array, arrayCapacity);
    fill_with_duplicates(array, arrayCapacity);
    printArray(array, arrayCapacity);
    fill_without_duplicates(array, arrayCapacity);
    printArray(array, arrayCapacity);
}