#ifndef STACKS_H
#define STACKS_H

#include "tree.h"

typedef struct operandStack {
    int size;
    node **data;
    int top;
} operandStack;

typedef struct stackOperator {
    int size;
    char *data;
    int top;
} stackOperator;

operandStack *createOperandStack();
int isEmptyOperandStack(operandStack *s);
int isFullOperandStack(operandStack *s);
void pushOperandStack(operandStack *s, node *value);
node *popOperandStack(operandStack *s);
void freeOperandStack(operandStack *s);

stackOperator *createStackOperator();
int isEmptyStackOperator(stackOperator *s);
int isFullStackOperator(stackOperator *s);
char peekOperator(stackOperator *s);
void pushOperator(stackOperator *s, char value);
char popOperator(stackOperator *s);
void freeStackOperator(stackOperator *s);

#endif