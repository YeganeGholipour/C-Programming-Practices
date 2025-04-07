#include <stdio.h>
#include <string.h>


void my_strcat(char *s, char *t);
void my_strcat(char *s, char *t) {
    int len = strlen(s);
    s += len;

    while (*s++ = *t++)
        ;
}

int main() {
    char string1[100] = "happy bithday ";
    char string2[100] = "yegane :)";

    my_strcat(string1, string2);

    char *p = string1;
    while (*p != '\0')
        printf("%c", *p++);
    printf("\n");

    // printf("%s\n", string1);
}