#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct { // определяем структуру наших данных
    unsigned int flatNum;
    int type;
    char name[50];
    unsigned int debtsUtilityBills;
    unsigned int amountResidents;
} flat;

typedef struct TreeNode{ // структура для бинарного дерева
    flat flat;
    struct TreeNode *left;
    struct TreeNode *right;
} tree;

void printHeader(void); // функция для вывода шапки для данных
void printFlat(flat); // функция для вывода данных про квартиру
tree* treeFromArray(flat*, unsigned int); // функция для создания бинарного дерева из массива
flat* generateData(unsigned int, int); // функиция для генерации данных
void freeTree(tree *p); // функция удаления дерева
void searchTree(tree*, char*); // функция для поиска в дереве

#endif /* Header_h */
