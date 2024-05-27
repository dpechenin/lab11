#include "Header.h"

unsigned long getHash(char *str, unsigned long len, unsigned int n) {
    unsigned long b = 378551;
    unsigned long a = 63689;
    unsigned long hash = 0;
    unsigned long i = 0;
    
    for (i = 0; i < len; str++, i++) {
        hash = hash * a + (unsigned long)(*str);
        a = a * b;
    }
    return hash % n;
}

HashTable* createTable(flat* arr, unsigned int n) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (table != NULL) {
        table->flats = (flat**)calloc(n, sizeof(flat*));
        if (table->flats != NULL) {
            for (int i = 0; i < n; i++) {
                table->flats[i] = NULL;
            }
            
            for (unsigned int i = 0; i < n; i++) {
                unsigned long hash = getHash(arr[i].name, (unsigned long)(strlen(arr->name)), n);
                printf("hash is %ld\n", hash);
                if (table->flats[hash] == NULL) {
                    table->flats[hash] = (flat*)malloc(sizeof(flat));
                    table->flats[hash]->type = arr[i].type;
                    table->flats[hash]->flatNum= arr[i].flatNum;
                    strcpy(table->flats[hash]->name, arr[i].name);
                    table->flats[hash]->debtsUtilityBills = arr[i].debtsUtilityBills;
                    table->flats[hash]->amountResidents = arr[i].amountResidents;
                }
            }
            
            return table;
        }
    }
    return NULL;
}

void hashSearch(HashTable *table, char *key) {
    if (table == NULL) {
        printf("Ваша хэщ-таблица пуста\n");
        return;
    }
}
