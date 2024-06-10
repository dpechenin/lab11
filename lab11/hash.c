#include "Header.h"

unsigned long getHash(char *str, unsigned long len, unsigned int m) {
    unsigned long b = 378551;
    unsigned long a = 63689;
    unsigned long hash = 0;
    unsigned long i = 0;
    
    for (i = 0; i < len; str++, i++) {
        hash = hash * a + (unsigned long)(*str);
        a = a * b;
    }
    return hash % m;
}

HashTable* createTable(flat* arr, unsigned int n, unsigned int m) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (table != NULL) {
        table->flats = (flat**)calloc(m, sizeof(flat*));
        table->overflow_buckets = (LinkedList**)calloc(m, sizeof(LinkedList*));
        if (table->flats != NULL && table->overflow_buckets != NULL) {
            for (int i = 0; i < m; i++) {
                table->flats[i] = NULL;
                table->overflow_buckets[i] = NULL;
            }
            
            for (unsigned int i = 0; i < n; i++) {
                unsigned long hash = getHash(arr[i].name, (unsigned long)(strlen(arr->name)), m);
                if (table->flats[hash] == NULL) {
                    table->flats[hash] = (flat*)malloc(sizeof(flat));
                    table->flats[hash]->type = arr[i].type;
                    table->flats[hash]->flatNum= arr[i].flatNum;
                    strcpy(table->flats[hash]->name, arr[i].name);
                    table->flats[hash]->debtsUtilityBills = arr[i].debtsUtilityBills;
                    table->flats[hash]->amountResidents = arr[i].amountResidents;
                }
                else if (table->overflow_buckets[hash] == NULL) {
                    table->overflow_buckets[hash] = (LinkedList*)malloc(sizeof(LinkedList));
                    table->overflow_buckets[hash]->flat = (flat*)malloc(sizeof(flat));
                    table->overflow_buckets[hash]->flat->flatNum = arr[i].flatNum;
                    table->overflow_buckets[hash]->flat->type = arr[i].type;
                    strcpy(table->overflow_buckets[hash]->flat->name, arr[i].name);
                    table->overflow_buckets[hash]->flat->debtsUtilityBills = arr[i].debtsUtilityBills;
                    table->overflow_buckets[hash]->flat->amountResidents = arr[i].amountResidents;
                    table->overflow_buckets[hash]->next = NULL;
                }
                else {
                    LinkedList *tmp = table->overflow_buckets[hash];
                    while (tmp->next != NULL) {
                        tmp = tmp->next;
                    }
                    LinkedList *newEl = (LinkedList*)malloc(sizeof(LinkedList));
                    if (newEl != NULL) {
                        newEl->flat = (flat*)malloc(sizeof(flat));
                        newEl->flat->type = arr[i].type;
                        newEl->flat->amountResidents = arr[i].amountResidents;
                        newEl->flat->debtsUtilityBills = arr[i].debtsUtilityBills;
                        newEl->flat->flatNum = arr[i].flatNum;
                        strcpy(newEl->flat->name, arr[i].name);
                        newEl->next = NULL;
                        tmp->next = newEl;
                    }
                }
            }
            
            return table;
        }
    }
    return NULL;
}

void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->flat);
        free(temp);
    }
}

void deleteTable(HashTable *table, unsigned int m) {
    if (table == NULL) {
        return;
    }
    if (table->flats != NULL) {
        for (unsigned int i = 0; i < m; i++) {
            free(table->flats[i]);
        }
    }
    if (table->overflow_buckets != NULL) {
        LinkedList** buckets = table->overflow_buckets;
            for (int i=0; i < m; i++)
                  free_linkedlist(buckets[i]);
            free(buckets);
    }
    free(table->flats);
    free(table);
}

void hashSearch(HashTable *table, char *key, unsigned int m) {
    int count = 0;
    if (table == NULL) {
        printf("Ваша хэш-таблица пуста\n");
        return;
    }
    unsigned long hash = getHash(key, strlen(key), m);
    if (!strcmp(key, table->flats[hash]->name)) {
        printFlat((*table->flats[hash]));
        count++;
    }
    LinkedList *tmp = table->overflow_buckets[hash];
    if (tmp != NULL) {
        if (!strcmp(tmp->flat->name, key)) {
            printFlat(*(tmp->flat));
            count++;
        }
        while (tmp->next != NULL) {
            if (!strcmp(tmp->next->flat->name, key)) {
                printFlat(*(tmp->next->flat));
                count++;
            }
            tmp = tmp->next;
        }
    }
    if (!count) {
        printf("Ничего не было найдено!\n");
    }
}
