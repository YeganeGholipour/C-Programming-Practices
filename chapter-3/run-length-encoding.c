#include <stdio.h>
#include <string.h>

char* encoding(char s[], char t[]) {
    int i = 1;
    int index = 0;
    char before = s[0], character;
    int length = 1;
    
    while (s[i] != '\0') {
        character = s[i];
        if (before == character) {
            length++;
        } else {
            t[index++] = before;
            
            if (length > 1) {
                index += sprintf(&t[index], "%d", length);  
            }
            
            before = character;
            length = 1;
        } 
        i++;
    }

    t[index++] = before;
    if (length > 1) {
        index += sprintf(&t[index], "%d", length);
    }
    
    t[index] = '\0';

    return t;
}

int main() {
    char str[] = "aaabbcddddee";
    char des[100];  
    char *t = encoding(str, des);
    printf("%s\n", t);  // Expected output: a3b2c1d4e2
    return 0;
}
