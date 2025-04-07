#include <stdio.h>

void swap(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(int v[], int left, int right) {
    int i, last;
    
    if (left >= right) 
        return; // Base case: array has fewer than 2 elements
    
    // Move partition element (pivot) to the leftmost position
    swap(v, left, (left + right) / 2); 
    
    last = left; // Initialize last index
    
    // Partition the array: elements smaller than pivot go to the left
    // and elements greater than the pivot go to the right
    for (i = left + 1; i <= right; i++) {
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }
    
    // Put the pivot in its correct position
    swap(v, left, last);
    
    // Recursively sort the two subarrays
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

int main(void) {
    int arr[] = {8, 7, 2, 1, 0, 9, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Before Sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Call the quicksort function
    qsort(arr, 0, size - 1);
    
    printf("After Sorting:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
