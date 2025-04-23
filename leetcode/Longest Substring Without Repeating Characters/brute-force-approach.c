#include <string.h>
#include <stdio.h>

int has_duplicates(char* s) {
    int i;
    int character;
    int seen[128] = {0};
    for (i = 0; s[i] != '\0'; i++) {
        character = s[i];
        if (seen[character])
            return 1;
        seen[character] = 1;
    }
    return 0;
}

int lengthOfLongestSubstring(char* s) {
    int i, j, k, index;
    int max_len = 0;
    int len = strlen(s);
    char temp[len+1];

    for (i = 0; i < len; i++)
        for (j = len - 1; j >= 0; j--) {
            k = i, index = 0;
            while (k <= j) {
                temp[index++] = s[k++];
            }
            temp[index] = '\0';
            printf("substring: %s\n", temp);
            if (has_duplicates(temp) == 0) {
                printf("had duplicate!\n");
                if (index > max_len) {
                    max_len = index;
                    printf("max_len: %d\n", max_len);
                }
            }
        }
    
    return max_len;
}

int main() {
    printf("%d\n", lengthOfLongestSubstring("pwwkew"));
    printf("######################################\n");
    printf("%d\n", lengthOfLongestSubstring("abcabcbb"));
    printf("######################################\n");
    printf("%d\n", lengthOfLongestSubstring("dvdf"));
    printf("######################################\n");
    printf("%d\n", lengthOfLongestSubstring("bbbbb"));
}