#include <stdio.h>
#include <limits.h>

int atoi(char s[]) {
    int i = 0;
    /* starts with white spaces */
    while (s[i] == ' ') {
        i++;
    }
    while (s[i] != '\0') {
        /* starts with - or + */
        if ((s[i] == '-' || s[i] == '+') && (s[i + 1] >= '0' && s[i + 1] <= '9')) {
            int sign = (s[i] == '-') ? -1 : 1;
            int j, n = 0;
            for (j = i + 1; s[j] != '\0' && s[j] >= '0' && s[j] <= '9'; j++) {
                if (n > (INT_MAX - (s[j] - '0')) / 10) {
                    // Overflow detected, return the appropriate boundary
                    return sign == 1 ? INT_MAX : INT_MIN;
                }
                n = (10 * n) + (s[j] - '0');
            }
            i = j;
            return sign * n;
        }

        /* starts with digit */
        else if (s[i] >= '0' && s[i] <= '9') {
            int j, n = 0;
            for (j = i; s[j] != '\0' && s[j] >= '0' && s[j] <= '9'; j++) {
                if (n > (INT_MAX - (s[j] - '0')) / 10) {
                    // Overflow detected, return the appropriate boundary
                    return INT_MAX;
                }
                n = 10 * n + (s[j] - '0');
            }
            i = j;
            return n;
        }

        /* start with a non-numeric character */
        return 0;
    }
    return 0; 
}




int main() {
    printf("%d\n", atoi("   -42abs"));  // Output: -42
    printf("%d\n", atoi("hello 123"));  
    printf("%d\n", atoi("+gkkn")); 
    printf("%d\n", atoi("4193 with words"));  // Output: 4193
    printf("%d\n", atoi("words and 987"));  // Output: 0
    printf("%d\n", atoi("-91283472332"));  // Output: INT_MIN (-2147483648)
    printf("%d\n", atoi("2147483648"));  // Output: INT_MAX (2147483647)
    return 0;
}