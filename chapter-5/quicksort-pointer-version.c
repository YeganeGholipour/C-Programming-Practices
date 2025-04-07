#include <stdio.h>

int *partitioning(int *left, int *right);

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

void quicksort(int *low, int *high) {
    if (low < high) {
        int *p = partitioning(low, high);
        quicksort(low, p);
        quicksort(p + 1, high);
    }
}

int *partitioning(int *low, int *high) {
    int pivot = *low;
    int *left = low - 1;
    int *right = high + 1;

    while (1) {
        do {
            right--;
        } while (*right > pivot);

        do {
            left++;
        } while (*left < pivot);

        if (left >= right)
            return right;

        swap(left, right);
    }
}

int main(void) {
    int arr[] = {8, 7, 2, 1, 0, 9, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Before Sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    quicksort(arr, arr + size - 1);

    printf("After Sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
