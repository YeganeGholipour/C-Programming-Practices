#include <stdio.h>

void reverse(char s[]) {
    int i, j, size;

    for (size = 0; s[size]; size++);

    j = size - 1;
    i = 0;

    if (s[j] == '\n') {
        s[j] = '\0';
        j--;
    }

    while (i<j) {
        char temp = s[j];
        s[j] = s[i];
        s[i] = temp;

        j--;
        i++;
    }
}

int main() {
    char string[1000];
    while (fgets(string, 1000, stdin))
    {   
        reverse(string);
        printf("%s\n", string);
    }
    
    return 0;

}