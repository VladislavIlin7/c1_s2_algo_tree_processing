#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>

typedef struct Node {
    char *key;
    double data;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

char *copyKey(const char *src);
int isValidKey(const char *key);

Node *createNode(const char *key, double data);

int max(int a, int b);
int height(Node *node);
int getBalance(Node *node);
void updateHeight(Node *node);

Node *rightRotate(Node *y);
Node *leftRotate(Node *x);

Node *insert(Node *root, const char *key, double value);
Node *findMin(Node *root);
Node *deleteNode(Node *root, const char *key);
Node *search(Node *root, const char *key);

void printTree(Node *root, int level);
void freeTree(Node *root);

char *readLineFile(FILE *file);
void printTreeToFile(Node *root, int level, FILE *out);
void processFile(Node **root, const char *inputFilename, const char *outputFilename);

#endif
