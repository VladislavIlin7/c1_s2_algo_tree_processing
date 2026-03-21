#include "func.h"
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
            printf("Ошибка: не удалось построить дерево\n");
            continue;
        }

        printf("Исходное выражение: ");
        printExpression(root);
        printf("\n\nИсходное дерево:\n");
        printTree(root, 0);

        root = transform(root);

        printf("\nПосле преобразования: ");
        printExpression(root);
        printf("\n\nДерево после преобразования:\n");
        printTree(root, 0);

        freeTree(root);
    }

    return 0;
}