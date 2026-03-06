#include <assert.h>
#include <stdio.h>
#include "tree.h"


void createTreeTest() {
    printf("test 1, create node test:\n");
    Node *node = createNode(52);

    assert(node != NULL);
    assert(node -> left == NULL);
    assert(node -> right == NULL);
    assert(node -> data == 52);

    freeTree(&node);
    printf("test 1 - OK\n");
}

void insertTest() {
    printf("test 2, insert node test:\n");
    Node *root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);

    assert(root != NULL);
    assert(root->data == 10);
    assert(root->left->data == 5);
    assert(root->right->data == 15);

    freeTree(&root);
    printf("test 2 - OK\n");
}

void findMinTest() {
    printf("test 3, find min node test:\n");
    Node *root = NULL;

    insert(&root, 20);
    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);

    Node *min = findMin(root);
    assert(min != NULL);
    assert(min->data == 5);

    freeTree(&root);
    printf("test 3 - OK\n");
}

void deleteNodeTest() {
    printf("test 4, delete node test:\n");
    Node *root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);

    deleteNode(&root, 5);
    assert(root->left == NULL);

    deleteNode(&root, 10);
    assert(root->data == 15);

    freeTree(&root);
    printf("test 4 - OK\n");
}

void getDegreeTest() {
    Node *root = NULL;

    insert(&root, 10);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 20);

    assert(getDegree(root) == 2);
    assert(getDegree(root->left) == 0);
    assert(getDegree(root->right) == 1);

    freeTree(&root);
}

void countVerticesTest() {
    printf("test 5, count vertices test:\n");
    Node *root = NULL;

    insert(&root, 2);
    insert(&root, 0);
    insert(&root, 3);

    assert(countVerticesWithSameDegree(root) == 2);

    freeTree(&root);
    printf("test 5 - OK\n");
}



int main() {
    createTreeTest();
    insertTest();
    findMinTest();
    deleteNodeTest();
    getDegreeTest();
    countVerticesTest();

    printf("All tests complete!\n");
    return 0;
}
