#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

void isOperatorTest() {
    assert(isOperator('+') == 1);
    assert(isOperator('-') == 1);
    assert(isOperator('*') == 1);
    assert(isOperator('/') == 1);
    assert(isOperator('a') == 0);
    assert(isOperator('(') == 0);
}

void priorityTest() {
    assert(priority('+') == 1);
    assert(priority('-') == 1);
    assert(priority('*') == 2);
    assert(priority('/') == 2);
    assert(priority('1') == 0);
}

void getNextTokenTest() {
    const char *expr = "12 + abc*(34+b)";
    int pos = 0;
    char *token = NULL;

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "12") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "+") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "abc") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "*") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "(") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "34") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "+") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, "b") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 1);
    assert(strcmp(token, ")") == 0);
    free(token);

    assert(getNextToken(expr, &pos, &token) == 0);
}

void createNodeTest() {
    node *n = createNode("abc");
    assert(n != NULL);
    assert(strcmp(n->data, "abc") == 0);
    assert(n->left == NULL);
    assert(n->right == NULL);
    freeTree(n);
}

void buildExpressionTreeSimpleTest() {
    node *root = buildExpressionTree("a+b");
    assert(root != NULL);

    assert(strcmp(root->data, "+") == 0);
    assert(root->left != NULL);
    assert(root->right != NULL);

    assert(strcmp(root->left->data, "a") == 0);
    assert(strcmp(root->right->data, "b") == 0);

    freeTree(root);
}

void buildExpressionTreePriorityTest() {
    node *root = buildExpressionTree("a+b*c");
    assert(root != NULL);

    assert(strcmp(root->data, "+") == 0);
    assert(strcmp(root->left->data, "a") == 0);

    assert(root->right != NULL);
    assert(strcmp(root->right->data, "*") == 0);
    assert(strcmp(root->right->left->data, "b") == 0);
    assert(strcmp(root->right->right->data, "c") == 0);

    freeTree(root);
}

void buildExpressionTreeParenthesesTest() {
    node *root = buildExpressionTree("(a+b)*c");
    assert(root != NULL);

    assert(strcmp(root->data, "*") == 0);
    assert(strcmp(root->right->data, "c") == 0);

    assert(root->left != NULL);
    assert(strcmp(root->left->data, "+") == 0);
    assert(strcmp(root->left->left->data, "a") == 0);
    assert(strcmp(root->left->right->data, "b") == 0);

    freeTree(root);
}

void transformleLeftTest() {
    node *root = buildExpressionTree("a*(b+c)");
    assert(root != NULL);

    root = transform(root);

    assert(strcmp(root->data, "+") == 0);

    assert(root->left != NULL);
    assert(strcmp(root->left->data, "*") == 0);
    assert(strcmp(root->left->left->data, "a") == 0);
    assert(strcmp(root->left->right->data, "b") == 0);

    assert(root->right != NULL);
    assert(strcmp(root->right->data, "*") == 0);
    assert(strcmp(root->right->left->data, "a") == 0);
    assert(strcmp(root->right->right->data, "c") == 0);

    freeTree(root);
}

void transformRightTest() {
    node *root = buildExpressionTree("(b+c)*a");
    assert(root != NULL);

    root = transform(root);

    assert(strcmp(root->data, "+") == 0);

    assert(root->left != NULL);
    assert(strcmp(root->left->data, "*") == 0);
    assert(strcmp(root->left->left->data, "b") == 0);
    assert(strcmp(root->left->right->data, "a") == 0);

    assert(root->right != NULL);
    assert(strcmp(root->right->data, "*") == 0);
    assert(strcmp(root->right->left->data, "c") == 0);
    assert(strcmp(root->right->right->data, "a") == 0);

    freeTree(root);
}

void transformNoChangeTest() {
    node *root = buildExpressionTree("a*b");
    assert(root != NULL);

    root = transform(root);

    assert(strcmp(root->data, "*") == 0);
    assert(strcmp(root->left->data, "a") == 0);
    assert(strcmp(root->right->data, "b") == 0);

    freeTree(root);
}

void transformMultipleTest() {
    node *root = buildExpressionTree("a*(b+c)+x*(y+z)");
    assert(root != NULL);

    root = transform(root);

    assert(strcmp(root->data, "+") == 0);

    assert(root->left != NULL);
    assert(strcmp(root->left->data, "+") == 0);

    assert(strcmp(root->left->left->data, "*") == 0);
    assert(strcmp(root->left->left->left->data, "a") == 0);
    assert(strcmp(root->left->left->right->data, "b") == 0);

    assert(strcmp(root->left->right->data, "*") == 0);
    assert(strcmp(root->left->right->left->data, "a") == 0);
    assert(strcmp(root->left->right->right->data, "c") == 0);

    assert(root->right != NULL);
    assert(strcmp(root->right->data, "+") == 0);

    assert(strcmp(root->right->left->data, "*") == 0);
    assert(strcmp(root->right->left->left->data, "x") == 0);
    assert(strcmp(root->right->left->right->data, "y") == 0);

    assert(strcmp(root->right->right->data, "*") == 0);
    assert(strcmp(root->right->right->left->data, "x") == 0);
    assert(strcmp(root->right->right->right->data, "z") == 0);

    freeTree(root);
}

void invalidExpressionTest() {
    node *root1 = buildExpressionTree("a+(b*c");
    assert(root1 == NULL);

    node *root2 = buildExpressionTree("a+b)");
    assert(root2 == NULL);
}

int main() {
    isOperatorTest();
    priorityTest();
    getNextTokenTest();
    createNodeTest();

    buildExpressionTreeSimpleTest();
    buildExpressionTreePriorityTest();
    buildExpressionTreeParenthesesTest();

    transformleLeftTest();
    transformRightTest();
    transformNoChangeTest();
    transformMultipleTest();

    invalidExpressionTest();

    printf("All tests passed\n");
    return 0;
}
