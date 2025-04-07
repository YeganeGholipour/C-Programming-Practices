#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[]) {
    int i = 0, j = 0;
    
    while (i < strlen(s1)) {  
        if (s1[i] == s2[j]) {
            j++;  
            if (s2[j] == '\0')  
                return i - j + 1;  
        } else {
            j = 0;  
        }
        i++;  
    }
    
    return -1; 
}

int main() {
    char string1[] = "hello world";
    char string2[] = "lo";

    int a = any(string1, string2);
    printf("Match found at index: %d\n", a);  
    return 0;
}
