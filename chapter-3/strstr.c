#include <stdio.h>

int mystrstr(char s1[], char s2[]) {
    if (s2[0] == '\0') return 0;  
    
    int i = 0, j = 0;
    while (s1[i] != '\0') {
        if (s1[i] == s2[j]) {
            i++, j++;
            if (s2[j] == '\0')  
                return i - j;
        } else {
            if (j > 0) {
                i = i - j + 1; 
                j = 0;
            } else {
                i++;
            }
        }
    }
    return -1; 
}

int main() {
    printf("%d\n", mystrstr("hello world", "lo"));       // 3
    printf("%d\n", mystrstr("happy birthday", "thd"));  // 9
    printf("%d\n", mystrstr("abcdef", "abc"));          // 0
    printf("%d\n", mystrstr("this is a test", "test")); // 10
    printf("%d\n", mystrstr("aaabaaa", "aaa"));         // 0
    printf("%d\n", mystrstr("openai", "ai"));           // 4
    printf("%d\n", mystrstr("hello", ""));             // 0
    printf("%d\n", mystrstr("", "world"));             // -1
    printf("%d\n", mystrstr("abcabcabcd", "abcabcd")); // 3 (fixed case!)
}
