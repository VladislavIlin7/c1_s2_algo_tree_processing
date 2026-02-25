#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node *left;
    struct node *right;
}node;

node* create_tree(int data) {
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
        return create_tree(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else {
        root->right = insert(root->right, data);
    }
    return root;

}

node* findMin(node *val) {
    if (val == NULL) {
        return NULL;
    }
    node *current = val;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

node* delete(node *root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = delete(root->left, data);
    }
    else if (data > root->data) {
        root->right = delete(root->right, data);
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
        root->right = delete(root->right, temp->data);
    }
    return root;
}

int main(void) {
    printf("Hello, World!\n");
    return 0;
}