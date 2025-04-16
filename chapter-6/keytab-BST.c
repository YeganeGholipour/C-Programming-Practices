#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

typedef struct Tnode {
    char *word;
    int count;
    struct Tnode *left;
    struct Tnode *right;
} Tnode;


Tnode *addTree(Tnode *, char *);
void treeprint(Tnode *);
Tnode *talloc(void);
char *strdup(char *);
int getword(char *, int);
int handle_string(char *, int);
void handle_comment(char);


int main(void) {
    Tnode *root;
    char word[MAXWORD];

    root = NULL;
    while(getword(word, MAXWORD) != EOF) 
        if (isalpha(word[0]))
            root = addTree(root, word);
    treeprint(root);
    return 0;
}


Tnode *addTree(Tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addTree(p->left, w);
    else
        p->right = addTree(p->right, w);
    
    return p;
}


void treeprint(Tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}


Tnode *talloc(void) {
    return (Tnode *)malloc(sizeof(Tnode));
}


char *strdup(char *s) {
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    
    return p;
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
