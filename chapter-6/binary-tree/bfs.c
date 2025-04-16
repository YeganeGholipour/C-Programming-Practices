#include <stdio.h>


typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;


char *traverse_bfs_iterative(Node *root) {
    if (root == NULL)
        return NULL;

    static char result[100];
    int res_index = 0;

    Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node *node = queue[front++];
        result[res_index++] = node->data;

        if (node->left)
            queue[rear++] = node->left;
        if (node->right)
            queue[rear++] = node->right;
    }

    result[res_index] = '\0';
    return result;
}

