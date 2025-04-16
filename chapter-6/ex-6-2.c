#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 100
#define MAXWORDS 1000
#define NUM 6

typedef struct Tnode {
    char *word;
    struct Tnode *left;
    struct Tnode *right;
} Tnode;


int getword(char *word, int max_len);
int memory_allocation(char *word, char *words[], int max_words, int *num_words);
char *mycalloc(char *w, size_t size);
Tnode *talloc(void);
Tnode *compare(char **words, int num_words, int num);
Tnode *addNode(char *, Tnode *);
void traverseTree(Tnode *root);
void printGroup(Tnode *groupRoot, const char *prefix, int num);


int main(int argc, char *argv[]) {
    int num;
    Tnode *root = NULL;
    int nw = 0, status;
    char first;
    size_t length;
    char word[MAXLEN]; 
    char *words[MAXWORDS];

    if (argc > 1)
        num = atoi(argv[1]);
    else
        num = NUM;
    

    while (isalpha(first = getword(word, MAXLEN)) || first == '_') {
        if ((status = memory_allocation(word, words, MAXWORDS, &nw)) < 0)
            return -1;
    }   

    root = compare(words, nw, num);
}


Tnode *compare(char **words, int nw, int num) {
    int i, j;
    Tnode *groupRoot = NULL;
    int groupSize;

    for (i = 0; i < nw; i++) {
        if (words[i] != NULL) {
            groupRoot = addNode(words[i], NULL);
            groupSize = 1; 
            for (j = i + 1; j < nw; j++) {
                if (words[j] != NULL) {
                    if (strncmp(words[i], words[j], num) == 0 &&
                        strcmp(words[i], words[j]) != 0) {
                        groupRoot = addNode(words[j], groupRoot);
                        words[j] = NULL;
                        groupSize++;
                    }
                }
            }

            if (groupSize > 1) { 
                printGroup(groupRoot, words[i], num);
                printf("\n");
            }

            words[i] = NULL; 
        }
    }

    return NULL; 
}



Tnode *addNode(char *w, Tnode *r) {
    if (r == NULL) {
        r = talloc();
        r->word = w;
        r->left = r->right = NULL;
    }
    else {
        int cmp = strcmp(w, r->word);
        if (cmp == 0)
            ; 
        else if (cmp < 0)
            r->left = addNode(w, r->left);
        else
            r->right = addNode(w, r->right);
    }
    return r;
}


void printGroup(Tnode *groupRoot, const char *prefix, int num) {
    printf("Group starting with \"%.*s\":\n", num, prefix);
    traverseTree(groupRoot);
    printf("\n\n");
}


void traverseTree(Tnode *root) {
    if (root != NULL) {
        traverseTree(root->left);
        printf("%s\n", root->word);
        traverseTree(root->right);
    }
}

int memory_allocation(char *word, char *words[], int max_words, int *num_words) {
    char *p;

    if (*num_words >= max_words) {
        printf("Not enough memory to allocate!\n");
        return -1;
    }

    p = mycalloc(word, sizeof(char));
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }

    strcpy(p, word);
    words[(*num_words)++] = p;
    return 0;
}


char *mycalloc(char *w, size_t size) {
    size_t length = strlen(w) + 1;
    return (char *)malloc(length * size);
}

Tnode *talloc(void) {
    return (Tnode *)malloc(sizeof(Tnode));
}

int getword(char *word, int max_len) {
    int c, next;
    char *start = word;

    while (isspace(c = getchar()))
        ;
    
    if (c == EOF)
        return EOF;

    if (c == '"') {
        while ((next = getchar()) != EOF) {
            if (next == '"')
                break;
        }

        if (c == EOF)
            return EOF;
    }

    else if (c == '/') {
        next = getchar();

        if (next == '/') {
            while ((next = getchar()) != EOF && next != '\n') 
                ;
            
            if (next == EOF)
                return EOF;
        }

        else if (next == '*') {
            while ((next = getchar()) != EOF) {
                if (next == '*') {
                    next = getchar();
                    if (next == '/')
                        break;
                }
                
                if (next == EOF)
                    return EOF;
            }
        }
    }

    else if (isalpha(c) || c == '_') {
        *word++ = c;
    
        while (--max_len > 0 && (isalnum(c = getchar()) || c == '_'))
            *word++ = c;
        
        *word = '\0';
    }
    
    return *start;
}

