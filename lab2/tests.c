#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

Table createSimpleTable(void) {
    Table table;
    initTable(&table);

    addElement(&table, 52, 'A', "piter");
    addElement(&table, 4, 'C', "hello world");
    addElement(&table, 77, 'B', "moscow");
    addElement(&table, 17, 'X', "apple");
    addElement(&table, 3, 'E', "banana");
    addElement(&table, 91, 'F', "computer");
    addElement(&table, 45, 'G', "keyboard");
    addElement(&table, 28, 'H', "monitor");
    addElement(&table, 64, 'I', "window");

    return table;
}

void initTest() {
    Table table;
    initTable(&table);

    assert(table.size == 0);
    assert(table.key_int == NULL);
    assert(table.key_char == NULL);
    assert(table.value == NULL);
}

void addElementTest() {
    Table table;
    initTable(&table);

    addElement(&table, 10, 'Z', "test");

    assert(table.size == 1);
    assert(table.key_int[0] == 10);
    assert(table.key_char[0] == 'Z');
    assert(strcmp(table.value[0], "test") == 0);

    freeTable(&table);
}

void keyCmpTest() {
    assert(key_cmp(1, 'A', 2, 'A') < 0);
    assert(key_cmp(2, 'A', 1, 'A') > 0);
    assert(key_cmp(5, 'A', 5, 'B') < 0);
    assert(key_cmp(5, 'C', 5, 'B') > 0);
    assert(key_cmp(7, 'D', 7, 'D') == 0);
}

void simpleAddAndSortTest() {
    Table table = createSimpleTable();
    selectionSort(&table);

    assert(table.key_int[0] == 3);
    assert(table.key_char[0] == 'E');
    assert(strcmp(table.value[0], "banana") == 0);

    assert(table.key_int[1] == 4);
    assert(table.key_char[1] == 'C');

    assert(table.key_int[2] == 17);
    assert(table.key_char[2] == 'X');

    freeTable(&table);
}

void binarySearchTest() {
    Table table = createSimpleTable();
    selectionSort(&table);

    int index1 = binarySearch(&table, 45, 'G');
    int index2 = binarySearch(&table, 3, 'E');
    int index3 = binarySearch(&table, 100, 'Q');

    assert(index1 != -1);
    assert(table.key_int[index1] == 45);
    assert(table.key_char[index1] == 'G');
    assert(strcmp(table.value[index1], "keyboard") == 0);

    assert(index2 != -1);
    assert(table.key_int[index2] == 3);
    assert(table.key_char[index2] == 'E');

    assert(index3 == -1);

    freeTable(&table);
}

void freeTableTest() {
    Table table = createSimpleTable();
    freeTable(&table);

    assert(table.size == 0);
    assert(table.key_int == NULL);
    assert(table.key_char == NULL);
    assert(table.value == NULL);
}

void readTableFromFileTest() {
    Table table;
    initTable(&table);

    readTableFromFile(&table, "test_input.txt");

    assert(table.size == 4);

    assert(table.key_int[0] == 12);
    assert(table.key_char[0] == 'B');
    assert(strcmp(table.value[0], "moscow") == 0);

    assert(table.key_int[1] == 5);
    assert(table.key_char[1] == 'A');
    assert(strcmp(table.value[1], "apple") == 0);

    assert(table.key_int[2] == 7);
    assert(table.key_char[2] == 'K');
    assert(strcmp(table.value[2], "linux") == 0);

    assert(table.key_int[3] == 33);
    assert(table.key_char[3] == 'D');
    assert(strcmp(table.value[3], "android") == 0);

    freeTable(&table);
}

int main() {
    initTest();
    addElementTest();
    keyCmpTest();
    simpleAddAndSortTest();
    binarySearchTest();
    freeTableTest();
    readTableFromFileTest();

    printf("All tests passed\n");
    return 0;
}
