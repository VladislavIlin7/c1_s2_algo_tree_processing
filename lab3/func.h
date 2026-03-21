#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    char *data;
    struct node *left;
    struct node *right;
} node;

typedef struct stack {
    int size;
    node **data;
    int top;
} stack;

typedef struct stackOperator {
    int size;
    char *data;
    int top;
} stackOperator;

node *createNode(char *value);
void printTree(node *root, int level);

stack *createStack();
int isEmptyStack(stack *s);
int isFullStack(stack *s);
void push(stack *s, node *value);
node *pop(stack *s);
void freeStack(stack *s);

stackOperator *createStackOperator();
int isEmptyStackOperator(stackOperator *s);
int isFullStackOperator(stackOperator *s);
void pushOperator(stackOperator *s, char value);
char popOperator(stackOperator *s);
void freeStackOperator(stackOperator *s);
char peekOperator(stackOperator *s);
void printExpression(node *root);
node *transform(node *root);
void freeTree(node *root);

int isOperator(char op);
int priority(char op);
int isDigit(char ch);
int isLetter(char ch);
int isSpace(char ch);

int getNextToken(const char *expr, int *pos, char **token);
int buildTopSubtree(stack *nodeStack, stackOperator *opStack);
node *buildExpressionTree(const char *expr);
#endif