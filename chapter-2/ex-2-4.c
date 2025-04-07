#include <stdio.h>
#include <string.h>

void squeeze(char s1[], char s2[]) {
    int i, j, k;
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);

    for (i = k = 0; i < s1_len; i++) {
        int found = 0;
        for (j = 0; j < s2_len; j++) {
            if (s1[i] == s2[j]) {
                found = 1;
                break;  
            }
        }

        if (!found) //found == 0 --> the ! (logical NOT) operator converts any non-zero value to false and zero to true
            s1[k++] = s1[i];
    }

    s1[k] = '\0';  // Null-terminate the modified string
}

int main() {
    char s1[] = "hello world";
    char s2[] = "lo";
    
    squeeze(s1, s2);
    printf("Result: %s\n", s1); // Expected output: "he wrd"
    
    return 0;
}
