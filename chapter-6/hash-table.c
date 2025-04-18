#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

typedef struct Node {
    struct Node *next;
    char *name;
    char *definition;
} Node;

Node *hashtab[HASHSIZE];


/* hash: from hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
Node *lookup(char *s) {
    Node *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

/* install: put (name, definition) in hashtab */
Node *install(char *name, char *def) {
    Node *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (Node *)malloc(sizeof(Node));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else 
        free((void *) np->definition);
    if ((np->definition = strdup(def)) == NULL)
        return NULL;

    return np;
}


Node *undef(char *name, char *def) {
    Node *np;
    unsigned hashval = hash(name);

    Node *current = hashtab[hashval];
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL)
                // the head
                hashtab[hashval] = current->next;
            else 
                prev->next = current->next;

            free(current->definition);
            free(current->name);
            free(current);

            return current;
        }

        prev = current;
        current = current->next;
    }
    return NULL;
}