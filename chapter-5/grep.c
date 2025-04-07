#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1000 // length of each line
#define MAXFOUND 5000 // maximum number of matches
#define MAXCHARS 1000 // maximum number of each matched character

int strindex(char *s, char *t, int *foundp);
int my_getline(char *line, int lim);
int grep(char *pattern);
char *alloc(int len);
void reverse(char *s);

char *matches[MAXFOUND];

int main() {
    printf("%d\n", grep("oul"));
}

void reverse(char *s) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char *alloc(int len) {
    return (char *)malloc(len * sizeof(char));
}

int strindex(char *s, char *t, int *foundp) {
    char *sp = s, *tp = t, *i, *p;
    int length = 0;
    int steps, pos = 0;
    char match[MAXCHARS];

    while (*sp) {
        if (*sp == *tp) {
            sp++;
            tp++;
            if (*tp == '\0') {
                for (i = sp; pos < MAXCHARS - 1 && *i != ' '; i--) {
                    match[pos++] = *i;
                }
                match[pos] = '\0';

                reverse(match);

                p = alloc(pos);

                if (p != NULL) {
                    strcpy(p, match);
                } else {
                    return -1;
                }

                matches[*foundp] = p;
                *foundp += 1;
                tp = t;
            }
            
        } else {
            if (tp != t) {
                steps = tp - t;
                sp = sp - steps + 1;
                tp = t;
            } else {
                sp++;
            }
        }
    }

    return 0;
}


int my_getline(char *line, int lim) {
    int c, i = 0;
    while ((c = getchar()) != EOF && c != '\n' && i < lim)
    {
        line[i++] = c;
    }
    
    if (c == '\n')
        line[i++] = '\n';

    line[i] = '\0';

    return i;
}


int grep(char *pattern) {
    int len, found = 0;
    char input[MAXLEN];

    while ((len = my_getline(input, MAXLEN)) > 0)
    {
        int found = 0;
        char **i;

        if (strindex(input, pattern, &found) == -1) {
            printf("Error. Cannot allocate memory\n");
        }
        else if (found > 0) {
            for (i = matches; i < matches + found; i++) {
                printf("Found: %s\n", *i);
            }
        }
        else {
            printf("No matches found\n");
        }
        
    }
    
    return found;
}



