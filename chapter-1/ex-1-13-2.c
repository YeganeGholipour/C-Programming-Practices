#include <stdio.h>

int main(){
    char c;
    int lengths[100];
    int length = 0;
    int max_length = 0;
    int i, j, num_words = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ' || c == '\t') {
            if (length > 0) {
                if (length > max_length) 
                    max_length = length;

                lengths[num_words] = length;
                num_words++;
                length = 0;
            }
        }

        else {
            length++;
        }
    }


    for (i = 0; i < max_length; i++) {
        for (j = 0; j < num_words; j++) {
            if (lengths[j] == 0)
                printf("  ");
            else {
                printf("*");
                printf(" ");
                lengths[j]--;
            }

        }

        putchar('\n');
    }
}

