#include <stdio.h>

void squeeze(char s[], int c)
{
    int i, j;

    for(i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
    printf("%s\n", s);
}

int main(){
    char str[] = "Haccnurckioexc";
    squeeze(str, 'c');
    return 0;
}