#include <stdio.h>
#include <string.h>


int my_strncmp(char *s, char *t, int n);

int my_strncmp(char *s, char *t, int n) {

    while (n-- > 0) {
        if (*s == *t) {
            if (*s == '\0' || *t == '\0') {
                return 0;
            }
            s++;
            t++;
        }

        else if (*s != *t) {
            return *s - *t;
        }
    }

    return 0;
}


int main() {
    char s[] = "hello";
    char t[] = "hello";
    int n = 20;
    int result = my_strncmp(s, t, n);
    printf("%d\n", result);
    return 0;
}