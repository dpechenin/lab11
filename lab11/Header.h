#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CAPACITY 50000

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

typedef struct Ht_item Ht_item;
struct Ht_item{
    char* key;
    flat* value;
};

typedef struct LinkedList LinkedList;
struct LinkedList {
    Ht_item* item;
    LinkedList* next;
};

typedef struct HashTable HashTable;
struct HashTable{
    Ht_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
};

void printHeader(void); // функция для вывода шапки для данных
void printFlat(flat); // функция для вывода данных про квартиру
tree* treeFromArray(flat*, unsigned int); // функция для создания бинарного дерева из массива
flat* generateData(unsigned int, int); // функиция для генерации данных
void freeTree(tree *p); // функция удаления дерева
void searchTree(tree*, char*); // функция для поиска в дереве
HashTable* create_table(unsigned int);
HashTable* HtFromArray(HashTable*, flat*, unsigned int);
void ht_search(HashTable*, char*);
#endif /* Header_h */
