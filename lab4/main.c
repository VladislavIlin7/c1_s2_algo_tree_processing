#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlTree.h"

char *readLine() {
    int ch;
    int size = 16;
    int len = 0;
    char *buffer = malloc(size);
    if (buffer == NULL) return NULL;
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

void showMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Add node\n");
    printf("2. Delete node\n");
    printf("3. Print tree\n");
    printf("4. Search by key\n");
    printf("0. Exit\n");
    printf("================\n");
    printf("Choose option: ");
}

int main() {
    Node *root = NULL;

    while (1) {
        showMenu();

        char *line = readLine();
        if (line == NULL) continue;

        int choice;
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid input!\n");
            free(line);
            continue;
        }
        free(line);

        if (choice == 1) {
            char *key;
            char *line;
            double value;

            printf("Enter key: ");
            key = readLine();
            if (key == NULL) {
                printf("Input error!\n");
                continue;
            }

            if (!isValidKey(key)) {
                printf("Invalid key! Only Latin letters, max 6 chars\n");
                free(key);
                continue;
            }

            printf("Enter value: ");
            line = readLine();
            if (line == NULL || sscanf(line, "%lf", &value) != 1) {
                printf("Invalid value!\n");
                free(key);
                free(line);
                continue;
            }
            free(line);

            root = insert(root, key, value);
            printf("Node added\n");

            free(key);
        } else if (choice == 2) {
            char *key;

            printf("Enter key to delete: ");
            key = readLine();
            if (key == NULL) {
                printf("Input error\n");
                continue;
            }

            if (!isValidKey(key)) {
                printf("Invalid key! Only Latin letters, max 6 chars\n");
                free(key);
                continue;
            }

            root = deleteNode(root, key);
            printf("Delete completed\n");

            free(key);
        } else if (choice == 3) {
            if (root == NULL) {
                printf("Tree is empty\n");
            } else {
                printTree(root, 0);
            }
        } else if (choice == 4) {
            char *key;

            printf("Enter key to search: ");
            key = readLine();
            if (key == NULL) {
                printf("Input error!\n");
                continue;
            }

            if (!isValidKey(key)) {
                printf("Invalid key! Only Latin letters, max 6 chars\n");
                free(key);
                continue;
            }

            Node *res = search(root, key);

            if (res == NULL) {
                printf("Key not found\n");
            } else {
                printf("Found: %s -> %.2lf\n", res->key, res->data);
            }

            free(key);
        } else if (choice == 0) {
            freeTree(root);
            printf("Memory freed\n");
            break;
        } else {
            printf("Unknown command!\n");
        }
    }

    return 0;
}
