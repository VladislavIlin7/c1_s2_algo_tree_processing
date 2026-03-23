#include "parser.h"

#include <stdio.h>
#include <string.h>

int main() {
    char expr[256];

    while (1) {
        printf("expr> ");

        if (fgets(expr, sizeof(expr), stdin) == NULL) {
            break;
        }

        expr[strcspn(expr, "\n")] = '\0';

        if (expr[0] == '\0') {
            continue;
        }

        if (strcmp(expr, "exit") == 0) {
            break;
        }

        node *root = buildExpressionTree(expr);
        if (root == NULL) {
            printf("Error: can't build a tree\n");
            continue;
        }

        printf("Input: ");
        printExpression(root);
        printf("\n\nOrigin tree:\n");
        printTree(root, 0);

        root = transform(root);

        printf("\nResult: ");
        printExpression(root);
        printf("\n\nResult tree:\n");
        printTree(root, 0);

        freeTree(root);
    }

    return 0;
}