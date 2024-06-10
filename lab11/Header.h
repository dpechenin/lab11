#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CAPACITY 500000

typedef struct flat flat;
struct flat{ // определяем структуру наших данных
    unsigned int flatNum;
    int type;
    char name[50];
    unsigned int debtsUtilityBills;
    unsigned int amountResidents;
};

typedef struct TreeNode tree;
struct TreeNode{ // структура для бинарного дерева
    flat flat;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct LinkedList LinkedList;
struct LinkedList {
    flat *flat;
    LinkedList *next;
};

typedef struct HashTable HashTable;
struct HashTable{
    flat **flats;
    LinkedList** overflow_buckets;
};

void printHeader(void); // функция для вывода шапки для данных
void printFlat(flat); // функция для вывода данных про квартиру
tree* treeFromArray(flat*, unsigned int); // функция для создания бинарного дерева из массива
flat* generateData(unsigned int, int); // функиция для генерации данных
void freeTree(tree *p); // функция удаления дерева
void searchTree(tree*, char*); // функция для поиска в дереве
HashTable* createTable(flat*, unsigned int, unsigned int);
void deleteTable(HashTable*, unsigned int);
void hashSearch(HashTable*, char*, unsigned int);
#endif /* Header_h */

