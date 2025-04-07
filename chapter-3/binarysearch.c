#include <stdio.h>

int binsearch(int x, int v[], int n) {
    int high = n - 1;
    int low = 0;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1 ;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}


int binsearch(int x, int v[], int n) {
    int low = 0, high = n - 1, mid;

    while (low < high) {  
        mid = low + (high - low) / 2;

        if (x > v[mid])
            low = mid + 1;
        else
            high = mid;  
    }

    if (low < n && v[low] == x)
        return low;
    
    return -1;
}
