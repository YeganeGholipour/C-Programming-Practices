#include <stdio.h>


#define MAXLINE 100

int strindex(char s[], char t[]) {
    int i = 0, j = 0;

    if (t[0] == '\0') {
        return 0;
    }

    while (s[i] != '\0') {
        if (s[i] == t[j]) {
            i++;
            j++;
            if (t[j] == '\0'){
                return i - j;
            }
        }
        else {
            if (j > 0) {
                i = i -j + 1;
                j = 0;
            }
            else {
                i++;
            }
        }
    }

    return -1;
}


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


int grep(char s[], char pattern[]) {
    char line[MAXLINE];
    int found = 0;

    while (my_getline(line, MAXLINE) > 0) {
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    }
    return found;
}

int main() {
    char pattern[] = "oul";
    char s[] = "Hello every body\n could you please tell us how would you \n go there if you could";
    printf("%d/n", grep(s, pattern));
}   
