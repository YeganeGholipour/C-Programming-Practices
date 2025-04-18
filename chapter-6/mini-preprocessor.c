#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100
#define HASHSIZE 101

typedef struct Node {
    char *name;            
    char *def;              
    struct Node *next;
} Node;

Node *hashtab[HASHSIZE];    

void parser(char *w, int max_len);
int getword(char *w, int max_len);
Node *install(char *macro, char *value);
Node *lookup(char *macro);
unsigned hash(char *s);
int my_getline(char *w, int max_len);

int main() {
    char word[MAXLEN];
    parser(word, MAXLEN);
    return 0;
}

void parser(char *w, int max_len) {
    char macro[MAXLEN];
    char value[MAXLEN];
    Node *np;

    // Read macro definitions first
    while (getword(w, max_len) > 0) {
        if (strcmp(w, "#define") == 0) {
            if (getword(macro, max_len) > 0 && my_getline(value, max_len) > 0) {
                install(macro, value);
            }
        } else {
            break;
        }
    }

    // Print the first non-#define word
    if ((np = lookup(w)) != NULL) {
        printf("%s", np->def);
    } else {
        printf("%s", w);
    }

    // Continue parsing and replacing macros
    int c;
    while ((c = getchar()) != EOF) {
        if (isalpha(c) || c == '_') {
            ungetc(c, stdin);
            getword(w, max_len);
            if ((np = lookup(w)) != NULL) {
                printf("%s", np->def);
            } else {
                printf("%s", w);
            }
        } else {
            putchar(c); // Preserve spacing, punctuation, etc.
        }
    }
}

// Reads one word/token (macro, identifier, or directive)
int getword(char *w, int max_len) {
    int c;
    char *start = w;

    while (isspace(c = getchar()))
        ;
    if (c == EOF)
        return EOF;

    if (isalpha(c) || c == '_') {
        *w++ = c;
        while (--max_len > 0 && (isalnum(c = getchar()) || c == '_'))
            *w++ = c;
        ungetc(c, stdin);
    } else if (c == '#') {
        *w++ = c;
        while (--max_len > 0 && isalpha(c = getchar()))
            *w++ = c;
        ungetc(c, stdin);
    } else {
        return 0;
    }

    *w = '\0';
    return 1;
}

// Reads rest of line for macro value
int my_getline(char *w, int max_len) {
    int c;
    char *start = w;
    while ((c = getchar()) != EOF && c != '\n') {
        if (--max_len > 0)
            *w++ = c;
    }
    *w = '\0';
    return (w != start);
}

// Install a macro in the hashtable
Node *install(char *macro, char *value) {
    Node *np;
    unsigned hashval;

    if ((np = lookup(macro)) == NULL) {
        np = (Node *)malloc(sizeof(Node));
        if (np == NULL || (np->name = strdup(macro)) == NULL)
            return NULL;
        hashval = hash(macro);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->def);  // replace old value
    }

    if ((np->def = strdup(value)) == NULL)
        return NULL;

    return np;
}

// Lookup a macro in the hashtable
Node *lookup(char *macro) {
    Node *np;
    unsigned hashval = hash(macro);
    for (np = hashtab[hashval]; np != NULL; np = np->next)
        if (strcmp(np->name, macro) == 0)
            return np;
    return NULL;
}

// Simple hash function
unsigned hash(char *s) {
    unsigned hashval = 0;
    for (; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}
