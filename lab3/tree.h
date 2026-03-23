#ifndef TREE_H
#define TREE_H

typedef struct node {
    char *data;
    struct node *left;
    struct node *right;
} node;

node *createNode(char *value);
void freeTree(node *root);
node *copyTree(node *root);

void printTree(node *root, int level);
void printExpression(node *root);

int isMultiplyNode(node *root);
int isPlusNode(node *root);
int isLetter(char ch);
int isVariableNode(node *root);

node *transform(node *root);

#endif