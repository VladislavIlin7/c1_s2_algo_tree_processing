#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

node* createTree(int data) {
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation error");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* insert(node *root, int data) {
    if (root == NULL) {
        return createTree(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;
}

node* findMin(node *root) {
    if (root == NULL) {
        return NULL;
    }
    node *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

node* deleteNode(node *root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    else {
        if (root->left == NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            node *temp = root->left;
            free(root);
            return temp;
        }
        node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void printTree(node *root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("|-- %d\n", root->data);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

int getDegree(node *node) {
    if (node == NULL) {
        return 0;
    }
    int degree = 0;
    if (node->left != NULL) {
        degree++;
    }
    if (node->right != NULL) {
        degree++;
    }
    return degree;
}

int countVerticesWithSameDegree(node *root) {
    if (root == NULL) {
        return 0;
    }
    int count = 0;
    if (root->data == getDegree(root)) {
        count++;
    }
    return count + countVerticesWithSameDegree(root->left) +
           countVerticesWithSameDegree(root->right);
}

void freeTree(node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    node *root = NULL;
    root = insert(root, 850);
    root = insert(root, 900);
    root = insert(root, 8000);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 300);
    root = insert(root, 35);
    root = insert(root, 22);

    printTree(root, 0);

    freeTree(root);

    return 0;
}