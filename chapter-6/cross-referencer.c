#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 100
#define MAXWORDS 5000
#define MAXNOISY 100
#define MAXFOUND 1000

Reference *addNode(Reference *root, char *word, int line, int length);
void traverseTreeInOrder(Reference *root);
int is_noisy(char *word);
int getword(char *word, int *line_num, int lim);
int getch(int *line_num);

typedef struct Reference
{
    char *word;
    int lines[MAXFOUND];
    int count;
    struct Reference *left;
    struct Reference *right;
} Reference;

char noisy_words[MAXNOISY][MAXWORDS] = {"and", "or", "but", "the", "a"};
    

int main(void) {
    Reference *root = NULL;
    int status;
    char word[MAXLEN];
    int line_num = 0;
    int length;
    while ((status = getword(word, &line_num, MAXLEN)) > 0) {
        length = strlen(word);
        root = addNode(root, word, line_num, length);
    }

    traverseTreeInOrder(root);
    freeTree(root);
}


Reference *addNode(Reference *root, char *word, int line, int length) {
    if (root == NULL) {
        root = talloc();
        char *wp = alloc(length);
        root->word = wp;
        root->count = 0;
        root->lines[root->count++] = line;
        root->left = root->right = NULL;
    }

    else {
        int comp = strcmp(root->word, word);

        if (comp == 0)
            if (binary_search(root->lines, line, root->count) < 0)
                root->lines[root->count++] = line; 
        else if (comp > 0)
            root->left = addNode(root->left, word, line, length);
        else
            root->right = addNode(root->right, word, line, length);
    }

    return root;
}

int binary_search(int lines[], int line, int count) {
    int high = count - 1, low = 0, mid;

    while (low <= high) {
        mid = (high + low) / 2;

        if (line == lines[mid])
            return mid;
        else if (line < lines[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    
    return -1;
}


Reference *talloc() {
    return (Reference *)malloc(sizeof(Reference));
}

char *alloc(size_t len) {
    return (char *)malloc((len + 1) * sizeof(char));
} 

void freeTree(Reference *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->word);
        free(root);
    }
}

void traverseTreeInOrder(Reference *root) {
    if (root != NULL) {
        traverseTreeInOrder(root->left);

        printf("Word: %s\n", root->word);
        printf("Lines: ");
        for (int i = 0; i < root->count; i++)
            printf("%d ", root->lines[i]);
        printf("\n");

        traverseTreeInOrder(root->right);
    }
}

int is_noisy(char *word) {
    char (*p)[MAXWORDS];
    for (p = noisy_words; p < noisy_words + MAXNOISY; p++) {
        if (strcmp(word, *p) == 0)
            return 1;  
    }
    return 0;  
}

int getword(char *word, int *line_num, int lim) {
    int c;
    char *start = word;

    // skip whitespaces
    while (isspace(c = getch(line_num))) 
        ;

    if (c == EOF)
        return EOF;

    // check if it is inside quotes
    if (c == '"') {
        while ((c = getch(line_num)) != '"' && c != EOF) {
            if (isalpha(c) || c == '_') {
                *word++ = c;
                while (--lim > 0 && (isalnum(c = getch(line_num)) || c == '_')) {
                    *word++ = c;
                }
                break;  
            }
        }
    }

    // check regular words
    else if (isalpha(c) || c == '_') {
        *word++ = c;
        while (--lim > 0 && (isalnum(c = getch(line_num)) || c == '_'))
            *word++ = c;
    } 

    else {
        return 0;
    }

    *word = '\0'; 

    // length less than 2 means it's 0 or 1 characters long
    if (strlen(start) < 2)  
        return 0;

    // check if it is noisy word
    if (is_noisy(word) == 1)
        return 0;

    return start[0];  
}

int getch(int *line_num) {
    int c = getchar();
    
    if (c == '\n')
        (*line_num)++;

    return c;
}