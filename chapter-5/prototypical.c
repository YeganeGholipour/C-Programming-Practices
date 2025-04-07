#include <stdio.h>

int main() {
    char message[100];
    int c, i = 0;

    while ((c = getchar()) != '\n' && c != EOF && i < 99) {
        if (c >= 'a' && c <= 'z')  
            message[i++] = c - ('a' - 'A'); 
        else
            message[i++] = c; 
    }
    message[i] = '\0';  

    printf("Converted text: ");
    for (int j = 0; message[j] != '\0'; j++) {
        char character = message[j];
        switch (character) {
            case 'A': printf("4"); break;
            case 'B': printf("8"); break;
            case 'E': printf("3"); break;
            case 'I': printf("1"); break;
            case 'O': printf("0"); break;
            case 'S': printf("5"); break;
            default: printf("%c", character);
        }
    }

    printf("\n");
    return 0;
}
