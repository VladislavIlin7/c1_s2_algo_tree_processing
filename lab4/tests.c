#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "avlTree.h"

void createNodeTest() {

    Node *node = createNode("qwe", 52.5);

    assert(node != NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    assert(strcmp(node->key, "qwe") == 0);
    assert(node->data == 52.5);
    assert(node->height == 1);

    freeTree(node);
}

void insertAndSearchTest() {
    Node *root = NULL;

    root = insert(root, "m", 10.0);
    root = insert(root, "a", 5.0);
    root = insert(root, "z", 15.0);

    assert(root != NULL);
    assert(strcmp(root->key, "m") == 0);
    assert(root->data == 10.0);

    Node *leftNode = search(root, "a");
    Node *rightNode = search(root, "z");
    Node *rootNode = search(root, "m");
    Node *missingNode = search(root, "xxx");

    assert(leftNode != NULL);
    assert(strcmp(leftNode->key, "a") == 0);
    assert(leftNode->data == 5.0);

    assert(rightNode != NULL);
    assert(strcmp(rightNode->key, "z") == 0);
    assert(rightNode->data == 15.0);

    assert(rootNode != NULL);
    assert(strcmp(rootNode->key, "m") == 0);

    assert(missingNode == NULL);

    freeTree(root);
}

void rotationAndBalanceTest() {
    Node *root = NULL;

    root = insert(root, "c", 1.0);
    root = insert(root, "b", 2.0);
    root = insert(root, "a", 3.0);

    assert(root != NULL);
    assert(strcmp(root->key, "b") == 0);
    assert(root->left != NULL);
    assert(root->right != NULL);
    assert(strcmp(root->left->key, "a") == 0);
    assert(strcmp(root->right->key, "c") == 0);

    assert(root->height == 2);
    assert(getBalance(root) == 0);

    freeTree(root);
}

void findMinAndDeleteTest() {
    Node *root = NULL;

    root = insert(root, "m", 10.0);
    root = insert(root, "c", 20.0);
    root = insert(root, "t", 30.0);
    root = insert(root, "a", 40.0);
    root = insert(root, "e", 50.0);

    Node *minNode = findMin(root);
    assert(minNode != NULL);
    assert(strcmp(minNode->key, "a") == 0);
    assert(minNode->data == 40.0);

    root = deleteNode(root, "a");
    assert(search(root, "a") == NULL);

    root = deleteNode(root, "m");
    assert(search(root, "m") == NULL);

    assert(root != NULL);
    assert(search(root, "c") != NULL);
    assert(search(root, "t") != NULL);
    assert(search(root, "e") != NULL);

    freeTree(root);
}

void validKeyAndUpdateTest() {
    assert(isValidKey("abc") == 1);
    assert(isValidKey("ABC") == 1);
    assert(isValidKey("AbCd") == 1);

    assert(isValidKey("") == 0);
    assert(isValidKey("abcdefg") == 0);
    assert(isValidKey("abc123") == 0);
    assert(isValidKey("ab-c") == 0);
    assert(isValidKey("абв") == 0);

    Node *root = NULL;

    root = insert(root, "abc", 1.5);
    root = insert(root, "abc", 9.9);

    Node *node = search(root, "abc");
    assert(node != NULL);
    assert(node->data == 9.9);

    freeTree(root);
}

int main() {
    createNodeTest();
    insertAndSearchTest();
    rotationAndBalanceTest();
    findMinAndDeleteTest();
    validKeyAndUpdateTest();

    printf("All tests complete!\n");
    return 0;
}