#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int strend(char *s, char *t) {
    char *sp = s, *tp = t;
    int s_len = strlen(s);
    int t_len = strlen(t);

    sp += s_len - 1;
    tp += t_len - 1;

    for (; tp >= t; sp--, tp--) {
        if (*sp != *tp) {
            printf("the second string is not at the end of the first string. \n");
            return 0;
        }
    }
    printf("The second string is at the end of the first string\n");
    return 1;
}

int main() {
    char string1[100] = "hello";
    char string2[100] = "bb";

    int res = strend(string1, string2);
    int res2 = strend("hello", "lo");
}