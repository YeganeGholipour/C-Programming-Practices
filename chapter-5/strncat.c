#include <stdio.h>
#include <string.h>

void my_strncat(char *s, char *t, int n);

void my_strncat(char *s, char *t, int n) {
    s += strlen(s);

    int t_len = strlen(t) + 1;  
    if (n > t_len) {
        n = t_len;
    }

    while (n-- > 0) {
        *s++ = *t++;
    }
    if (*(s - 1) != '\0') {
        printf("Manually adding null terminator.\n");
        *s = '\0';
    }
}

int main() {
    char string1[100] = "happy birthday ";
    char string2[] = "dear yegene :)";
    
    my_strncat(string1, string2, 15);
    printf("Result: %s\n", string1);  
}
