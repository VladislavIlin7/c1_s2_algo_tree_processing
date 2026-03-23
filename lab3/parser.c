#include "parser.h"

#include <stdio.h>
#include <stdlib.h>


int isOperator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/';
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}


int isSpace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

int getNextToken(const char *expr, int *pos, char **token) {
    int i = *pos;
    int len = 0;
    int capacity = 8;
    char *buf = NULL;

    *token = NULL;

    while (expr[i] != '\0' && isSpace(expr[i])) {
        i++;
    }

    if (expr[i] == '\0') {
        *pos = i;
        return 0;
    }

    buf = (char *) malloc(capacity * sizeof(char));
    if (buf == NULL) {
        return -1;
    }

    if (isDigit(expr[i])) {
        while (expr[i] != '\0' && isDigit(expr[i])) {
            if (len + 1 >= capacity) {
                capacity *= 2;
                char *tmp = (char *) realloc(buf, capacity * sizeof(char));
                if (tmp == NULL) {
                    free(buf);
                    return -1;
                }
                buf = tmp;
            }
            buf[len++] = expr[i++];
        }
    } else if (isLetter(expr[i])) {
        while (expr[i] != '\0' && (isLetter(expr[i]) || isDigit(expr[i]))) {
            if (len + 1 >= capacity) {
                capacity *= 2;
                char *tmp = (char *) realloc(buf, capacity * sizeof(char));
                if (tmp == NULL) {
                    free(buf);
                    return -1;
                }
                buf = tmp;
            }
            buf[len++] = expr[i++];
        }
    } else if (isOperator(expr[i]) || expr[i] == '(' || expr[i] == ')') {
        buf[len++] = expr[i++];
    } else {
        free(buf);
        return -2;
    }

    buf[len] = '\0';
    *token = buf;
    *pos = i;
    return 1;
}


int buildTopSubtree(stack *nodeStack, stackOperator *opStack) {
    char op = popOperator(opStack);
    if (op == '\0') {
        return -1;
    }

    node *right = pop(nodeStack);
    node *left = pop(nodeStack);

    if (left == NULL || right == NULL) {
        return -1;
    }

    char opStr[2];
    opStr[0] = op;
    opStr[1] = '\0';

    node *newNode = createNode(opStr);
    if (newNode == NULL) {
        return -1;
    }

    newNode->left = left;
    newNode->right = right;

    push(nodeStack, newNode);
    return 0;
}

node *buildExpressionTree(const char *expr) {
    stack *nodeStack = createStack();
    stackOperator *opStack = createStackOperator();

    if (nodeStack == NULL || opStack == NULL) {
        freeStack(nodeStack);
        freeStackOperator(opStack);
        return NULL;
    }

    int pos = 0;
    char *token = NULL;
    int status;

    while ((status = getNextToken(expr, &pos, &token)) == 1) {
        if (isDigit(token[0]) || isLetter(token[0])) {
            node *operandNode = createNode(token);
            if (operandNode == NULL) {
                free(token);
                freeStack(nodeStack);
                freeStackOperator(opStack);
                return NULL;
            }
            push(nodeStack, operandNode);
        } else if (token[0] == '(') {
            pushOperator(opStack, token[0]);
        } else if (token[0] == ')') {
            while (!isEmptyStackOperator(opStack) && peekOperator(opStack) != '(') {
                if (buildTopSubtree(nodeStack, opStack) != 0) {
                    free(token);
                    freeStack(nodeStack);
                    freeStackOperator(opStack);
                    return NULL;
                }
            }

            if (isEmptyStackOperator(opStack)) {
                free(token);
                freeStack(nodeStack);
                freeStackOperator(opStack);
                return NULL;
            }

            popOperator(opStack);
        } else if (isOperator(token[0])) {
            while (!isEmptyStackOperator(opStack) &&
                   peekOperator(opStack) != '(' &&
                   priority(peekOperator(opStack)) >= priority(token[0])) {
                if (buildTopSubtree(nodeStack, opStack) != 0) {
                    free(token);
                    freeStack(nodeStack);
                    freeStackOperator(opStack);
                    return NULL;
                }
            }

            pushOperator(opStack, token[0]);
        }

        free(token);
        token = NULL;
    }

    if (status < 0) {
        freeStack(nodeStack);
        freeStackOperator(opStack);
        return NULL;
    }

    while (!isEmptyStackOperator(opStack)) {
        if (peekOperator(opStack) == '(') {
            freeStack(nodeStack);
            freeStackOperator(opStack);
            return NULL;
        }

        if (buildTopSubtree(nodeStack, opStack) != 0) {
            freeStack(nodeStack);
            freeStackOperator(opStack);
            return NULL;
        }
    }

    node *root = pop(nodeStack);

    if (!isEmptyStack(nodeStack)) {
        freeStack(nodeStack);
        freeStackOperator(opStack);
        return NULL;
    }

    freeStack(nodeStack);
    freeStackOperator(opStack);
    return root;
}
