#ifndef PARSER_H
#define PARSER_H

#include "stacks.h"
#include "tree.h"


int isOperator(char op);
int priority(char op);
int isDigit(char ch);
int isSpace(char ch);
int getNextToken(const char *expr, int *pos, char **token);

int buildTopSubtree(operandStack *nodeStack, stackOperator *opStack);
node *buildExpressionTree(const char *expr);

#endif