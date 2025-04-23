#include <string.h>
#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
    int left = 0, right = 0;
    int last_seen[128];
    int max_len = 0, len;

    for (int i = 0; i < 128; i++)
        last_seen[i] = -1;

    while (s[right] != '\0') {
        int character = s[right];
        if (last_seen[character] != -1 && last_seen[character] >= left) {
            left = last_seen[character] + 1;
        }
        len = right - left + 1;

        if (len > max_len)
            max_len = len;
            
        last_seen[character] = right;
        right++;
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