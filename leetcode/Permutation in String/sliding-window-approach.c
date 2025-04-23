#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool checkInclusion(char* s1, char* s2) {
    int window_length = strlen(s1);
    int left = 0, right = left + window_length - 1;
    if (strlen(s1) > strlen(s2)) return false;
    int i, j, character;
    int seen[128] = {0};
    int tmp[128];

    for (i = 0; s1[i] != '\0'; i++) {
        character = s1[i];
        seen[character] += 1;
    }

    while (s2[right] != '\0') {
        memcpy(tmp, seen, sizeof(seen));

        for (j = left; j <= right; j++) {
            character = s2[j];
            printf("Character: %c\n", character);
            if (tmp[character] != 0) {
                printf("Seen: %d\n", tmp[character]);
                tmp[character] -= 1;
                if (j == right) {
                    printf("Finished!");
                    return true;
                }
            }
            else 
                break;
        }
        left++;
        right++;
    }
    return false; 
}

int main(void) {
    printf("%d\n", checkInclusion("aba", "eidbaaooo"));
    return 0;
}