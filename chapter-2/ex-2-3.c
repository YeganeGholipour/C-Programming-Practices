#include <stdio.h>
#include <string.h>


int htoi(char hex[]) {
    int i=0, j, d, n=0;
    if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) 
        i = 2;

    int limit = strlen(hex);
    for (j = i; j < limit; j++) {
        if (hex[j] >= '0' && hex[j] <= '9')
            d = hex[j] - '0';
        else if (hex[j] >= 'a' && hex[j] <= 'f')
            d = hex[j] - 'a' + 10;
        else if (hex[j] >= 'A' && hex[j] <= 'F')
            d = hex[j] - 'A' + 10;
        else {
            printf("Error: Invalid hex digit '%c'\n", hex[i]);
            return 0;
        }
        
        n = 16 * n + d;
    }

    return n;    
}

int main() {
    printf("%d\n", htoi("0x1A3"));  
    printf("%d\n", htoi("FF"));     
    printf("%d\n", htoi("0XbEef")); 
    printf("%d\n", htoi("1G2"));

    char c[1000];
    int number;

    while (scanf("%s", c) != EOF) {
        number = htoi(c);
        printf("The hexadecimal number: %s is = %d\n", c, number);
    }

    return 0;
}


// int main() {
//     char hex[1000];
//     int i = 0;
//     char ch;

//     printf("Enter a hex number: ");
//     while ((ch = getchar()) != '\n' && ch != EOF) {  
//         hex[i++] = ch;
//     }
//     hex[i] = '\0';  // Null-terminate the string

//     printf("You entered: %s\n", hex);
//     return 0;
// }