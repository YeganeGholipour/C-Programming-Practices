#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(Key))

typedef struct {
    char *word;
    int count;
} Key;

Key keytab[] = {
    {"_Bool", 0}, {"_Complex", 0}, {"_Imaginary", 0}, {"auto", 0},
    {"break", 0}, {"case", 0}, {"char", 0}, {"const", 0},
    {"continue", 0}, {"default", 0}, {"do", 0}, {"double", 0},
    {"else", 0}, {"enum", 0}, {"extern", 0}, {"float", 0},
    {"for", 0}, {"goto", 0}, {"if", 0}, {"inline", 0},
    {"int", 0}, {"long", 0}, {"register", 0}, {"restrict", 0},
    {"return", 0}, {"short", 0}, {"signed", 0}, {"sizeof", 0},
    {"static", 0}, {"struct", 0}, {"switch", 0}, {"typedef", 0},
    {"union", 0}, {"unsigned", 0}, {"void", 0}, {"volatile", 0},
    {"while", 0}
};

int getword(char *, int);
Key *binsearch(char *, Key *, int);
int handle_string(char *word, int lim);
void handle_comment(char next);

int main(void) {
    Key *p;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (!isdigit(word[0])) {
            if ((p = binsearch(word, keytab, NKEYS)) >= 0) {
                p->count++;
            }
        }
    }

    for (p = keytab; p < keytab + NKEYS; p++) {
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
    }

    return 0;
}

Key *binsearch(char *word, Key *tab, int n) {
    int cond;
    Key *low = &tab[0];
    Key *high = &tab[n];
    Key *mid;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, (*mid).word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return NULL;
}

int getword(char *word, int lim) {
    int c, next;

    while (isspace(c = getchar()))
        ;

    if (c == EOF)
        return EOF;

    if (c == '"')
        return handle_string(word, lim);

    else if (c == '#') {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return (c == EOF) ? EOF : getword(word, lim);
    }

    else if (c == '/') {
        next = getchar();
        if (next == '/') {
            handle_comment('/');
            return getword(word, lim);
        } else if (next == '*') {
            handle_comment('*');
            return getword(word, lim);
        } else {
            ungetc(next, stdin);
        }
    }

    if (!isalpha(c) && c != '_') {
        *word++ = c;
        *word = '\0';
        return c;
    }

    *word++ = c;
    while (--lim > 0 && (isalnum(c = getchar()) || c == '_'))
        *word++ = c;

    *word = '\0';
    if (c != EOF)
        ungetc(c, stdin);
    return word[0];
}

int handle_string(char *word, int lim) {
    int c;
    char *start = word;
    *word++ = '"';
    lim--;

    while (lim > 0 && (c = getchar()) != EOF) {
        *word++ = c;
        if (c == '\\') {
            c = getchar();
            if (c != EOF)
                *word++ = c;
        } else if (c == '"')
            break;
    }

    *word = '\0';
    return *start;
}

void handle_comment(char next) {
    int c;
    if (next == '/') {
        while ((c = getchar()) != EOF && c != '\n')
            ;
        return;
    }

    if (next == '*') {
        int prev = 0;
        while ((c = getchar()) != EOF) {
            if (prev == '*' && c == '/')
                return;
            prev = c;
        }
    }
}
