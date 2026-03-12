#ifndef TABLE_H
#define TABLE_H

typedef struct Table{
    int size;
    int *key_int;
    char *key_char;
    char **value;
} Table;

void initTable(Table *table);
int key_cmp(int a_int, char a_char, int b_int, char b_char);
void addElement(Table *table, int key_int, char key_char, const char *value);
void readTableFromFile(Table *table, const char *filename);
void selectionSort(Table *t);
int binarySearch(const Table *table, int key_int, char key_char);
void printFindElement(const Table *table, int index);
void printTable(const Table *table);
void freeTable(Table *table);
#endif