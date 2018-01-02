//
// Created by liam on 1/2/2018.
//

#ifndef MIVNE2WET_HEAP_H
#define MIVNE2WET_HEAP_H
#include <cstdlib>

template <class T>
class Heap {
    int numOfElements;
    int sizeOfArray;
    int* array;

public:
    Heap(int numOfElements, int* data);
    void siftDown(int index);
    void postOrderSift(int i);
    void Heap::insert(int data);
};

Heap::Heap(int numOfElements, int* data):numOfElements(numOfElements) {
    sizeOfArray = 2 * numOfElements;
    array = (int *) malloc(sizeof(int) * sizeOfArray);
    for (int i = 0; i < numOfElements; i++) {
        array[i] = data[i];
    }
    for (int i = (numOfElements / 2); i <= 0; i--) {
        siftDown(i);
    }
}


//while Father is bigger then one of his sons switch between root and min
void Heap::siftDown(int index){
    if(2*index>numOfElements){
        return;
    }
    if(2*index==numOfElements){
        if(array[index]>array[2*index]){
            int temp = array[index];
            array[index] = array[2*index];
            array[2*index] = temp;
        }
        return;
    }
    if(array[index] < array[2*index] && array[index] < array[2*index+1]){
        return;
    }
    if(array[2*index] > array[2*index+1]){
        int temp = array[index];
        array[index] = array[2*index+1];
        array[2*index+1] = temp;
        siftDown(2*index+1);
        return;
    }
    int temp = array[index];
    array[index] = array[2*index];
    array[2*index] = temp;
    siftDown(2*index);
}

//void Heap::insert(int data){
//    if(numOfElements=)
//}

#endif //MIVNE2WET_HEAP_H
