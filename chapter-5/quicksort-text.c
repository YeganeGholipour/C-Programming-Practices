#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void swap(char **arry, int i, int j);
void quicksort(char *array[], int low, int high);
int partition(char **array, int low, int high);

void swap(char **array, int i, int j) {
    char *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void quicksort(char *array[], int low, int high) {
    if (low < high) {
        int p = partition(array, low, high);

        quicksort(array, low, p);
        quicksort(array, p + 1, high);
    }   
}

int partition(char **array, int low, int high) {
    char *pivot = array[low];
    int left = low - 1;
    int right = high + 1;

    while (true)
    {
        do
        {
            right--;
        } while (strcmp(array[right], pivot) > 0);

        do
        {
            left++;
        } while (strcmp(array[left], pivot) < 0);
        
        if (left >= right)
            return right;
        
        swap(array, left, right);
    }
    
}