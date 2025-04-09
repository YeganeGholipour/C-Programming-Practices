#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int *arry, int i, int j);
void quicksort(int *array, int low, int high);
int partition(int *array, int low, int high);

void swap(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void quicksort(int *array, int low, int high) {
    if (low < high) {
        int p = partition(array, low, high);

        quicksort(array, low, p);
        quicksort(array, p + 1, high);
    }   
}

int partition(int *array, int low, int high) {
    int pivot = array[low];
    int left = low - 1;
    int right = high + 1;

    while (true)
    {
        do
        {
            right--;
        } while (array[right] > pivot);

        do
        {
            left++;
        } while (array[left] < pivot);
        
        if (left >= right)
            return right;
        
        swap(array, left, right);
    }
    
}