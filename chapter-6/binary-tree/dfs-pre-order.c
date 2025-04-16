#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100


typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;


Node *createNode(char val);
void traverse_pre_order_recursive_print(Node *root);
void traverse_pre_order_recursive(Node *root, char *result, int *res_index, int len);
char *traverse_pre_order_iterative(Node *root, char *result, int *res_index, int len);

int main() {
    Node *root = createNode('R');
    Node *nodeA = createNode('A');
    Node *nodeB = createNode('B');
    Node *nodeC = createNode('C');
    Node *nodeD = createNode('D');
    Node *nodeE = createNode('E');
    Node *nodeF = createNode('F');
    Node *nodeG = createNode('G');

    root->right = nodeB;
    root->left = nodeA;

    nodeA->left = nodeC;
    nodeA->right = nodeD;

    nodeB->left = nodeE;
    nodeB->right = nodeF;

    nodeF->left = nodeG;

    char result[MAX_NODES];
    int index = 0;

    // traverse_pre_order_recursive(root, result, &index, MAX_NODES);
    traverse_pre_order_iterative(root, result, &index, MAX_NODES);
    printf("Pre-order Traversal: ");
    for (int i = 0; i < index; i++) {
        printf("%c ", result[i]);
    }
    printf("\n");
}

Node *createNode(char val) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void traverse_pre_order_recursive_print(Node *root) {
    char result[100];

    if (root == NULL) {
        printf("Empty!\n");
        return;
    }

    printf("%c ", root->data);
    traverse_pre_order_recursive_print(root->left);
    traverse_pre_order_recursive_print(root->right);
}

void traverse_pre_order_recursive(Node *root, char *result, int *res_index, int len) {
    if (root == NULL)
        return;
    
    if (*res_index < len)
        result[(*res_index)++] = root->data;

    traverse_pre_order_recursive(root->left, result, res_index, len);
    traverse_pre_order_recursive(root->right, result, res_index, len);
}

char *traverse_pre_order_iterative(Node *root, char *result, int *res_index, int len) {
    if (root == NULL)
        return NULL;

    Node *stack[100];  
    int top = 0;

    stack[top++] = root;

    while (top > 0) {
        Node *node = stack[--top];  

        if (*res_index < len) {
            result[*res_index] = node->data;  
            (*res_index)++;

            if (node->right)
                stack[top++] = node->right;
            if (node->left)
                stack[top++] = node->left;
        }
    }

    return result;
}
