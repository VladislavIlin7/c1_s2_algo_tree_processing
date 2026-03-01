#ifndef TREE_H
#define TREE_H


typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;


Node *createNode(int data);

void insert(Node **root, int data);

Node *findMin(Node *root);

void deleteNode(Node **root, int data);

void printTree(Node *root, int level);

int getDegree(Node *node);

int countVerticesWithSameDegree(Node *root);

void freeTree(Node **root);

#endif
