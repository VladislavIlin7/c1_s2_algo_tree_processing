#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "table.h"

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void resetTable(Table *table) {
    freeTable(table);
    initTable(table);
}

void generateRandomFile(char *filename, int n) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Failed to create file %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        int key_int = rand();
        char key_char = 'A' + rand() % 26;
        fprintf(f, "%d %c value_%d\n", key_int, key_char, i);
    }
    fclose(f);
    printf("File %s successfully created (%d lines)\n", filename, n);
}

void showMenu(void) {
    printf("\n===== MENU =====\n");
    printf("1. Load sorted.txt\n");
    printf("2. Load reversed.txt\n");
    printf("3. Generate random.txt\n");
    printf("4. Load random.txt\n");
    printf("5. Print table\n");
    printf("6. Sort table\n");
    printf("7. Find element\n");
    printf("8. Clear table\n");
    printf("0. Exit\n");
    printf("================\n");
}

void searchMenu(Table *table) {
    if (table->size == 0) {
        printf("Table is empty\n");
        return;
    }

    int key_int;
    char key_char;

    printf("Enter key_int: ");
    if (scanf("%d", &key_int) != 1) {
        clearBuffer();
        printf("Input error\n");
        return;
    }
    printf("Enter key_char: ");
    if (scanf(" %c", &key_char) != 1) {
        clearBuffer();
        printf("Input error\n");
        return;
    }
    clearBuffer();

    selectionSort(table);
    int index = binarySearch(table, key_int, key_char);

    if (index == -1) {
        printf("Element not found\n");
    } else {
        printf("Element found:\n");
        printf("%d %c | %s\n", table->key_int[index], table->key_char[index], table->value[index]);
    }
}

int main(void) {
    Table table;
    initTable(&table);
    int cmd;
    while (1) {
        showMenu();
        if (scanf("%d", &cmd) != 1) {
            clearBuffer();
            printf("Please enter a number\n");
            continue;
        }
        clearBuffer();

        switch (cmd) {
            case 0:
                freeTable(&table);
                printf("Goodbye\n");
                return 0;

            case 1:
                resetTable(&table);
                readTableFromFile(&table, "sorted.txt");
                printf("sorted.txt loaded (%d elements)\n", table.size);
                break;

            case 2:
                resetTable(&table);
                readTableFromFile(&table, "reversed.txt");
                printf("reversed.txt loaded (%d elements)\n", table.size);
                break;

            case 3: {
                int n;
                printf("How many rows to generate: ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    clearBuffer();
                    printf("Invalid number\n");
                    break;
                }
                clearBuffer();

                generateRandomFile("random.txt", n);
                break;
            }

            case 4:
                resetTable(&table);
                readTableFromFile(&table, "random.txt");
                printf("random.txt loaded (%d elements)\n", table.size);
                break;

            case 5:
                if (table.size == 0)
                    printf("Table is empty\n");
                else
                    printTable(&table);
                break;

            case 6:
                if (table.size == 0) {
                    printf("Table is empty\n");
                } else {
                    selectionSort(&table);
                    printf("Table sorted\n");
                }
                break;

            case 7:
                searchMenu(&table);
                break;

            case 8:
                resetTable(&table);
                printf("Table cleared\n");
                break;

            default:
                printf("Unknown command\n");
        }
    }
}
