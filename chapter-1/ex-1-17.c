#include <stdio.h>

#define MAXLINE 1000
#define MAX 80

int my_getline(char s[], int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) 
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i;

    i = 0; 
    while ((to[i] = from[i]) != '\0')
        i++;
}

int main() {
    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0)  
        if (len > MAX) {
        printf("%s", line);   
        }
    return 0;
}
