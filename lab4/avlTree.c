#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.h"


int isValidKey(const char *key) {
    int len = strlen(key);
    if (len == 0 || len > 6) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))) {
            return 0;
        }
    }
    return 1;
}

char *copyKey(const char *src) {
    char *copy = (char *) malloc(strlen(src) + 1);
    if (copy == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(copy, src);
    return copy;
}


Node *createNode(const char *key, double data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->key = copyKey(key);
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void updateHeight(Node *node) {
    if (node == NULL) {
        return;
    }
    node->height = 1 + max(height(node->left), height(node->right));
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node *insert(Node *root, const char *key, const double value) {
    if (root == NULL) {
        return createNode(key, value);
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = insert(root->left, key, value);
    } else if (cmp > 0) {
        root->right = insert(root->right, key, value);
    } else {
        root->data = value;
        return root;
    }

    updateHeight(root);

    int balance = getBalance(root);


    if (balance > 1 && strcmp(key, root->left->key) < 0) {
        return rightRotate(root);
    }

    if (balance < -1 && strcmp(key, root->right->key) > 0) {
        return leftRotate(root);
    }

    if (balance > 1 && strcmp(key, root->left->key) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && strcmp(key, root->right->key) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *findMin(Node *root) {
    if (root == NULL) {
        printf("Empty tree\n");
        return NULL;
    }
    while (root && root->left)
        root = root->left;
    return root;
}

Node *deleteNode(Node *root, const char *key) {
    if (root == NULL) {
        printf("Element not found: %s\n", key);
        return NULL;
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = deleteNode(root->left, key);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, key);
    } else {
        // Узел найден
        if (root->left == NULL || root->right == NULL) {
            Node *temp = (root->left != NULL) ? root->left : root->right;

            free(root->key);
            free(root);

            return temp;
        } else {
            Node *temp = findMin(root->right);

            free(root->key);
            root->key = copyKey(temp->key);
            root->data = temp->data;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) {
        return NULL;
    }

    updateHeight(root);

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *search(Node *root, const char *key) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(key, root->key);

    if (cmp == 0) {
        return root;
    }
    if (cmp < 0) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void printTree(Node *root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("|-- %s : %.2lf (h=%d)\n", root->key, root->data, root->height);
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}


void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root->key);
    free(root);
}
