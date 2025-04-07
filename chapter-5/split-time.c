#include <stdio.h>

void split_time(long total_sec, int *hr, int *min, int *sec);

int main() {
    long total_sec;
    int hr, min, sec;

    printf("Enter total seconds since midnight: ");
    scanf("%ld", &total_sec);

    split_time(total_sec, &hr, &min, &sec);

    printf("Time: %02d:%02d:%02d\n", hr, min, sec);

    return 0;
}

void split_time(long total_sec, int *hr, int *min, int *sec) {
    *hr = (total_sec / 3600) % 24;  // Get hours (0-23)
    *min = (total_sec % 3600) / 60; // Get minutes (0-59)
    *sec = total_sec % 60;          // Get seconds (0-59)
}
