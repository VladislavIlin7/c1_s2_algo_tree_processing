#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Table {
    int size;
    int *key_int;
    char *key_char;
    char **value;
} Table;

void initTable(Table *table) {
    table->size = 0;
    table->key_int = NULL;
    table->key_char = NULL;
    table->value = NULL;
}
char *readLine(FILE *file) {
    char ch;
    int size = 32;
    int len = 0;
    char *buffer = malloc(size);

    if (buffer == NULL) { 
        exit(1);
    }

    while ((ch = fgetc(file)) != '\n' && ch != EOF) {
        buffer[len++] = ch;
        if (len + 1 >= size) {
            size *= 2;
            char *new_line = realloc(buffer, size);
            if (new_line == NULL) { 
                free(buffer);
                exit(1);
            }
            buffer = new_line;
        }
        if (ch == EOF && len == 0) {
            free(buffer);
            return NULL;
        }
    }
    buffer[len] = '\0';
    return buffer;

}


int key_cmp(int a_int, char a_char, int b_int, char b_char) {
    if (a_int < b_int) return -1;
    if (a_int > b_int) return 1;

    if (a_char < b_char) return -1;
    if (a_char > b_char) return 1;

    return 0;
}


void addElement(Table *table, const int key_int, const char key_char, const char *value) {
    int current_size = table->size;
    table->size++;

    table->key_int = (int *) realloc(table->key_int, sizeof(int) * table->size);
    table->key_char = (char *) realloc(table->key_char, sizeof(char) * table->size);
    table->value = realloc(table->value, sizeof(char *) * table->size);
    if (table->key_int == NULL || table->key_char == NULL || table->value == NULL) {
        exit(1);
    }

    table->key_int[current_size] = key_int;
    table->key_char[current_size] = key_char;
    table->value[current_size] = malloc(strlen(value) + 1);
    strcpy(table->value[current_size], value);
}

int lenInt(int n) {
    int count = 0;
    if (n == 0) count = 1;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}

void readTableFromFile(Table *table, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("%s - not found\n", filename);
        return;
    }

    char line[2048];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        char *key_str = strtok(line, " ");
        char *key_char = strtok(NULL, " ");
        char *value = strtok(NULL, "");

        if (!key_str || !key_char) {
            continue;
        }

        if (strlen(key_char) != 1 || !isalpha(key_char[0])) {
            continue;
        }

        int key_int = atoi(key_str);
        if (lenInt(key_int) != strlen(key_str)) {
            continue;
        }
        if (!value) {
            addElement(table, key_int, key_char[0], "");
        } else {
            addElement(table, key_int, key_char[0], value);
        }
    }

    fclose(file);
}

void selectionSort(const Table *t) {
    for (int i = 0; i < t->size - 1; i++) {
        int min = i;

        for (int j = i + 1; j < t->size; j++) {
            if (key_cmp(t->key_int[j], t->key_char[j],
                        t->key_int[min], t->key_char[min]) < 0) {
                min = j;
            }
        }

        if (min != i) {
            int ti = t->key_int[i];
            t->key_int[i] = t->key_int[min];
            t->key_int[min] = ti;

            char tc = t->key_char[i];
            t->key_char[i] = t->key_char[min];
            t->key_char[min] = tc;

            char *tmp = t->value[i];
            t->value[i] = t->value[min];
            t->value[min] = tmp;
        }
    }
}

int binarySearch(const Table *table, int key_int, char key_char) {
    int left = 0;
    int right = table->size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        int cmp = key_cmp(table->key_int[mid], table->key_char[mid], key_int, key_char);

        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void printFindElement(const Table *table, int index) {
    if (index < 0 || index >= table->size) {
        printf("index out of range\n");
        return;
    }
    printf("Find element: %d", table->key_int[index]);
}

void printTable(const Table *table) {
    for (int i = 0; i < table->size; i++) {
        printf("%d %c | %s\n",
               table->key_int[i],
               table->key_char[i],
               table->value[i]);
    }
}

void freeTable(Table *table) {
    for (int i = 0; i < table->size; i++) {
        free(table->value[i]);
    }

    free(table->value);
    free(table->key_int);
    free(table->key_char);

    table->size = 0;
    table->key_int = NULL;
    table->key_char = NULL;
    table->value = NULL;
}
