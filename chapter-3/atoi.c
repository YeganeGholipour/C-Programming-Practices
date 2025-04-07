#include <limits.h>
#include <stdio.h>

int atoi(char s[]) {
    int i = 0;
    /* we have white spaces */
    while (s[i] == ' ')
        i++;
    
    /* it has + or - */
    int sign = 1;
    if (s[i] == '-' || s[i] == '+') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    /* it has digits */
    int n = 0;
    while (s[i] >= '0' && s[i]<= '9') {
        int digit = s[i] - '0';
        if (n > (INT_MAX - digit) / 10)
            return (sign == 1) ? INT_MAX : INT_MIN;
        n = 10 * n + digit;
        i++;
    }
    return n*sign;
}


int main() {
    printf("%d\n", atoi("   -42abs"));  // Output: -42
    printf("%d\n", atoi("hello 123"));  // Output: 0
    printf("%d\n", atoi("+gkkn"));  // Output: 0
    printf("%d\n", atoi("4193 with words"));  // Output: 4193
    printf("%d\n", atoi("words and 987"));  // Output: 0
    printf("%d\n", atoi("-91283472332"));  // Output: INT_MIN (-2147483648)
    printf("%d\n", atoi("2147483648"));  // Output: INT_MAX (2147483647)
    return 0;
}