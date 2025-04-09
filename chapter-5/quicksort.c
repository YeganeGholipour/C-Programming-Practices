#include <stdio.h>

int partitioning(int *v, int left, int right);
void swap(int *v, int i, int j);
int partitioning(int *v, int low, int high);


void swap(int *v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void quicksort(int *v, int low, int high) {
    if (low < high) {
        int p = partitioning(v, low, high);
        quicksort(v, low, p);
        quicksort(v, p + 1, high);
    }
}

int partitioning(int *v, int low, int high) {
    int pivot = v[low];
    int left = low - 1;
    int right = high + 1;

    while (1) {
        do {
            right--;
        } while (v[right] > pivot);

        do {
            left++;
        } while (v[left] < pivot);

        if (left >= right)
            return right;

        swap(v, left, right);
    }
}

int main(void) {
    int arr[] = {8, 7, 2, 1, 0, 9, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Before Sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    quicksort(arr, 0, size - 1);

    printf("After Sorting:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
