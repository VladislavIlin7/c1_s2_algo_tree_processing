#include "tree.h"

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

int isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
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