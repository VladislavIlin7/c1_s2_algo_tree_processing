#ifndef STACKS_H
#define STACKS_H

#include "tree.h"

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

stack *createStack();
int isEmptyStack(stack *s);
int isFullStack(stack *s);
void push(stack *s, node *value);
node *pop(stack *s);
void freeStack(stack *s);

stackOperator *createStackOperator();
int isEmptyStackOperator(stackOperator *s);
int isFullStackOperator(stackOperator *s);
char peekOperator(stackOperator *s);
void pushOperator(stackOperator *s, char value);
char popOperator(stackOperator *s);
void freeStackOperator(stackOperator *s);

#endif