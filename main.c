#include <stdio.h>
#include "tree.h"


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void showMenu() {
    printf("\n===== MENU =====\n");
    printf("1. Add node\n");
    printf("2. Print tree\n");
    printf("3. Delete node\n");
    printf("4. Count vertices (data == degree)\n");
    printf("0. Exit\n");
    printf("================\n");
    printf("Choose option: ");
}


void addNodeMenu(Node **root) {
    int value;

    printf("Enter value: ");
    if (scanf("%d", &value) == 1) {
        insert(root, value);
        printf("Node added.\n");
    } else {
        printf("Invalid input!\n");
    }
    clearBuffer();
}

void deleteNodeMenu(Node **root) {
    int value;

    printf("Enter value to delete: ");
    if (scanf("%d", &value) == 1) {
        deleteNode(root, value);
        printf("Delete operation completed.\n");
    } else {
        printf("Invalid input!\n");
    }
    clearBuffer();
}


void countVerticesMenu(Node *root) {
    int count = countVerticesWithSameDegree(root);
    printf("Vertices with data == degree: %d\n", count);
}


int main(void) {
    Node *root = NULL;
    int choice;

    while (1) {
        showMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                addNodeMenu(&root);
                break;

            case 2:
                if (root == NULL)
                    printf("Tree is empty.\n");
                else
                    printTree(root, 0);
                break;

            case 3:
                deleteNodeMenu(&root);
                break;

            case 4:
                countVerticesMenu(root);
                break;

            case 0:
                freeTree(&root);
                printf("Memory freed. Bye Bye!\n");
                return 0;

            default:
                printf("Unknown command!\n");
        }
    }
}
