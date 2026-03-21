#include "func.h"

#include <stdio.h>
#include <stdlib.h>


node *createNode(char *value) {
    node *temp = (node *)malloc(sizeof(node));
    if (temp == NULL) {
        return NULL;
    }

    int len = 0;
    while (value[len] != '\0') {
        len++;
    }

    temp->data = (char *)malloc((len + 1) * sizeof(char));
    if (temp->data == NULL) {
        free(temp);
        return NULL;
    }

    for (int i = 0; i <= len; i++) {
        temp->data[i] = value[i];
    }

    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void freeTree(node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root->data);
    free(root);
}

void printTree(node *root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("|-- %s\n", root->data);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

void printExpression(node *root) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL || root->right != NULL) {
        printf("(");
    }

    printExpression(root->left);
    printf("%s", root->data);
    printExpression(root->right);

    if (root->left != NULL || root->right != NULL) {
        printf(")");
    }
}

int isMultiplyNode(node *root) {
    return root != NULL && root->data != NULL && root->data[0] == '*' && root->data[1] == '\0';
}

int isPlusNode(node *root) {
    return root != NULL && root->data != NULL && root->data[0] == '+' && root->data[1] == '\0';
}

int isVariableNode(node *root) {
    if (root == NULL || root->data == NULL) {
        return 0;
    }

    if (root->left != NULL || root->right != NULL) {
        return 0;
    }

    return isLetter(root->data[0]);
}

node *copyTree(node *root) {
    if (root == NULL) {
        return NULL;
    }

    node *newNode = createNode(root->data);
    if (newNode == NULL) {
        return NULL;
    }

    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}
node *transform(node *root) {
    if (root == NULL) {
        return NULL;
    }

    root->left = transform(root->left);
    root->right = transform(root->right);

    if (!isMultiplyNode(root)) {
        return root;
    }

    if (isVariableNode(root->left) && isPlusNode(root->right)) {
        node *a1 = copyTree(root->left);
        node *a2 = copyTree(root->left);
        node *b  = copyTree(root->right->left);
        node *c  = copyTree(root->right->right);

        node *mul1 = createNode("*");
        node *mul2 = createNode("*");
        node *plus = createNode("+");

        if (a1 == NULL || a2 == NULL || b == NULL || c == NULL ||
            mul1 == NULL || mul2 == NULL || plus == NULL) {
            return root;
            }

        mul1->left = a1;
        mul1->right = b;

        mul2->left = a2;
        mul2->right = c;

        plus->left = mul1;
        plus->right = mul2;

        freeTree(root);
        return transform(plus);
    }

    if (isPlusNode(root->left) && isVariableNode(root->right)) {
        node *b  = copyTree(root->left->left);
        node *c  = copyTree(root->left->right);
        node *a1 = copyTree(root->right);
        node *a2 = copyTree(root->right);

        node *mul1 = createNode("*");
        node *mul2 = createNode("*");
        node *plus = createNode("+");

        if (a1 == NULL || a2 == NULL || b == NULL || c == NULL ||
            mul1 == NULL || mul2 == NULL || plus == NULL) {
            return root;
            }

        mul1->left = b;
        mul1->right = a1;

        mul2->left = c;
        mul2->right = a2;

        plus->left = mul1;
        plus->right = mul2;

        freeTree(root);
        return transform(plus);
    }

    return root;
}


stack *createStack() {
    stack *s = malloc(sizeof(stack));
    if (s == NULL) {
        return NULL;
    }

    s->size = 2;
    s->data = malloc(s->size * sizeof(node *));
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    s->top = -1;
    return s;
}

int isEmptyStack(stack *s) {
    if (s->top == -1) {
        return 1;
    }
    return 0;
}

int isFullStack(stack *s) {
    if (s->top == s->size - 1) {
        return 1;
    }
    return 0;
}

void push(stack *s, node *value) {
    if (isFullStack(s)) {
        s->size *= 2;
        node **tmp = realloc(s->data, s->size * sizeof(node *));
        if (tmp == NULL) {
            printf("realloc error\n");
            return;
        }
        s->data = tmp;
    }

    s->data[++s->top] = value;
}

node *pop(stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    return s->data[s->top--];
}

void freeStack(stack *s) {
    if (s == NULL) {
        return;
    }
    if (s->data != NULL) {
        free(s->data);
    }
    free(s);
    printf("stack free\n");
}




stackOperator *createStackOperator() {
    stackOperator *s = malloc(sizeof(stackOperator));
    if (s == NULL) {
        return NULL;
    }

    s->size = 2;
    s->data = malloc(s->size * sizeof(char));
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    s->top = -1;
    return s;
}

int isEmptyStackOperator(stackOperator *s) {
    if (s->top == -1) {
        return 1;
    }
    return 0;
}

int isFullStackOperator(stackOperator *s) {
    if (s->top == s->size - 1) {
        return 1;
    }
    return 0;
}

char peekOperator(stackOperator *s) {
    if (isEmptyStackOperator(s)) {
        return '\0';
    }
    return s->data[s->top];
}

void pushOperator(stackOperator *s, char value) {
    if (isFullStackOperator(s)) {
        s->size *= 2;
        char *tmp = realloc(s->data, s->size * sizeof(char));
        if (tmp == NULL) {
            printf("realloc error\n");
            return;
        }
        s->data = tmp;
    }

    s->data[++s->top] = value;
}

char popOperator(stackOperator *s) {
    if (isEmptyStackOperator(s)) {
        printf("Stack is empty\n");
        return '\0';
    }
    return s->data[s->top--];
}

void freeStackOperator(stackOperator *s) {
    if (s == NULL) {
        return;
    }
    if (s->data != NULL) {
        free(s->data);
    }
    free(s);
    printf("stack operator free\n");
}





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

int isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
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

    buf = (char *)malloc(capacity * sizeof(char));
    if (buf == NULL) {
        return -1;
    }

    if (isDigit(expr[i])) {
        while (expr[i] != '\0' && isDigit(expr[i])) {
            if (len + 1 >= capacity) {
                capacity *= 2;
                char *tmp = (char *)realloc(buf, capacity * sizeof(char));
                if (tmp == NULL) {
                    free(buf);
                    return -1;
                }
                buf = tmp;
            }
            buf[len++] = expr[i++];
        }
    }
    else if (isLetter(expr[i])) {
        while (expr[i] != '\0' && (isLetter(expr[i]) || isDigit(expr[i]))) {
            if (len + 1 >= capacity) {
                capacity *= 2;
                char *tmp = (char *)realloc(buf, capacity * sizeof(char));
                if (tmp == NULL) {
                    free(buf);
                    return -1;
                }
                buf = tmp;
            }
            buf[len++] = expr[i++];
        }
    }
    else if (isOperator(expr[i]) || expr[i] == '(' || expr[i] == ')') {
        buf[len++] = expr[i++];
    }
    else {
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
        }

        else if (token[0] == '(') {
            pushOperator(opStack, token[0]);
        }

        else if (token[0] == ')') {
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
        }

        else if (isOperator(token[0])) {
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