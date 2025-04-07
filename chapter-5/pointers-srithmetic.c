#include <stdio.h>

int main(void) {
    char *arr[2][3] = {{"happy", "Birth", "day"}, {"yegane", ":", ")"}};
    char **p = arr[0];
    
    for (; p <= *(arr + 1) + 2; p++)
        printf("%s ", *p);

    printf("\n"); 

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         printf("%s ", *(*(arr + i) + j));  
    //     }
    //     printf("\n"); 
    // }

    // for (int i = 0; i < 2; i++) {
    //     // Loop over columns in each row
    //     for (int j = 0; j < 3; j++) {
    //         printf("%s ", arr[i][j]);  
    //     }
    //     printf("\n");  
    // }



    return 0;
}