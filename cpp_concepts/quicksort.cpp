#include<iostream>

using size_type = unsigned int;

template< class T >
void printArray(T arr[], size_type size){
    for(size_type i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

template< class T >
void swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template< class T >
size_type partition(T arr[], size_type low, size_type high){
    T pivot = arr[high];
    size_type i = low - 1;
    for(size_type j = low; j <= high - 1; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[++i], &arr[high]);
    return i;
}

template< class T >
void quickSort(T arr[], size_type low, size_type high){
    if(low < high){
        size_type part = partition(arr, low, high);
        quickSort(arr, low, part-1);
        quickSort(arr, part+1, high);
    }

}

int main(){
    int arr[] = {9,1,4,2,6,7,8,3,4};
    size_type size = sizeof(arr)/sizeof(arr[0]);
    printArray(arr,size);
    quickSort(arr,0,size-1);
    printArray(arr,size);

}