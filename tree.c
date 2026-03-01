#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;


Node *createNode(int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void insert(Node **root, int data) {
    if (*root == NULL) {
        *root = createNode(data);
        return;
    }

    if (data < (*root)->data) {
        insert(&((*root)->left), data);
    } else {
        insert(&((*root)->right), data);
    }
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

void deleteNode(Node **root, int data) {
    if (*root == NULL) {
        printf("Element not found\n");
        return;
    }
    if (data < (*root)->data) {
        deleteNode(&(*root)->left, data);
    } else if (data > (*root)->data) {
        deleteNode(&(*root)->right, data);
    } else {
        if ((*root)->left == NULL) {
            Node *temp = (*root)->right;
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            Node *temp = (*root)->left;
            free(*root);
            *root = temp;
        } else {
            Node *temp = findMin((*root)->right);
            (*root)->data = temp->data;
            deleteNode(&(*root)->right, temp->data);
        }
    }
}

void printTree(Node *root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("|-- %d\n", root->data);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

int getDegree(Node *node) {
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

int countVerticesWithSameDegree(Node *root) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;
    if (root->data == getDegree(root)) {
        count++;
    }
    return count + countVerticesWithSameDegree(root->left) + countVerticesWithSameDegree(root->right);
}

void freeTree(Node **root) {
    if (*root == NULL) {
        return;
    }

    freeTree(&(*root)->left);
    freeTree(&(*root)->right);
    free(*root);
    *root = NULL;
}
