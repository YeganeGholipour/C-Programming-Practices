#include <stdio.h>

int main(void) {
    FILE *fp = fopen("test.txt", "r");  

    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);  
    }

    fclose(fp);  
    return 0;
}
