#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLEN 100
#define MAXWORDS 1000

typedef struct Node {
    char *word;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

void traverseTreeInOrder(Node *root, Node *list[], int *index);
void sort(Node *list[], size_t length);
void quicksort(Node **list, int low, int high);
int partition(Node **list, int low, int high);
void swap(Node **list, int left, int right);
Node *addNode(Node *root, char *word);
int getword(char *word, int lim);
void printNodes(Node *list[], size_t length);
Node *talloc(void);
int compare(Node *a, Node *b);
void freeTree(Node *root);

int main(void) {
    Node *root = NULL;
    int status, nwords = 0;
    int index = 0;
    char word[MAXLEN];
    Node *in_order_traverse[MAXWORDS];
    
    while ((status = getword(word, MAXLEN)) > 0) 
        root = addNode(root, word);
    
    traverseTreeInOrder(root, in_order_traverse, &index);
    int len = index;
    sort(in_order_traverse, len);
    printNodes(in_order_traverse, len);

    freeTree(root);

    return 0;
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->word);
        free(root);
    }
}

void printNodes(Node *list[], size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("Word: %s, Count: %d\n", list[i]->word, list[i]->count);
    }
}

void traverseTreeInOrder(Node *root, Node *list[], int *index) {
    if (root != NULL) {
        traverseTreeInOrder(root->left, list, index);
        list[(*index)++] = root;
        traverseTreeInOrder(root->right, list, index);
    }
}

void sort(Node *list[], size_t length) {
    int low = 0, high = length - 1;
    quicksort(list, low, high);
}


void quicksort(Node **list, int low, int high) {
    if (low < high) {
        int p = partition(list, low, high);

        quicksort(list, low, p - 1);
        quicksort(list, p + 1, high);
    }
}

int partition(Node **list, int low, int high) {
    int left = low - 1;
    int right = high + 1;

    Node *pivot = list[low];

    while (1) {
        do
        {
            right--;
        } while (compare(list[right], pivot) > 0);
        
        do
        {
            left++;
        } while (compare(list[left], pivot) < 0);

        if (left >= right)
            return right;
        
        swap(list, left, right);
    }
}

int compare(Node *a, Node *b) {
    return a->count - b->count;
}

void swap(Node **list, int left, int right) {
    Node *temp = list[left];
    list[left] = list[right];
    list[right] = temp;
}

Node *addNode(Node *root, char *word) {
    if (root == NULL) {
        root = talloc();
        root->word = strdup(word);
        root->count = 1;
        root->left = NULL;
        root->right = NULL;
    } else {
        int comp = strcmp(root->word, word);
        
        if (comp == 0) 
            root->count++;
        else if (comp > 0)
            root->left = addNode(root->left, word);
        else
            root->right = addNode(root->right, word);
    }

    return root;
} 

char *strdup(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}


Node *talloc(void) {
    Node *np = malloc(sizeof(Node));
    return np;
}

int getword(char *word, int lim) {
    int c;
    char *start = word;

    // skip whitespaces
    while (isspace(c = getchar())) 
        ;

    if (c == EOF)
        return EOF;

    // check if it is inside quotes
    if (c == '"') {
        while ((c = getchar()) != '"' && c != EOF) {
            if (isalpha(c) || c == '_') {
                *word++ = c;
                while (--lim > 0 && (isalnum(c = getchar()) || c == '_')) {
                    *word++ = c;
                }
                break;  
            }
        }
    }

    // check regular words
    else if (isalpha(c) || c == '_') {
        *word++ = c;
        while (--lim > 0 && (isalnum(c = getchar()) || c == '_'))
            *word++ = c;
    } 

    else {
        return 0;
    }

    *word = '\0'; 

    // length less than 2 means it's 0 or 1 characters long
    if (strlen(start) < 2)  
        return 0;

    return start[0];  
}
