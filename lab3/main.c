#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readLine() {
    int ch;
    int size = 16;
    int len = 0;

    char *buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        buffer[len++] = ch;

        if (len >= size) {
            size *= 2;
            char *tmp = realloc(buffer, size);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
    }

    if (ch == EOF && len == 0) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}


int main() {
    char expr[256];

    while (1) {
        printf("expr> ");

        char *expr = readLine();
        if (expr == NULL) {
            break;
        }

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
