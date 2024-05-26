#include "Header.h"

unsigned int RSHash(char *str, unsigned int len) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;
    
    for (i = 0; i < len; str++, i++) {
        hash = hash * a + (unsigned int)(*str);
        a = a * b;
    }
    return hash;
}

LinkedList* allocate_list (void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }
    
    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }
    
    LinkedList* temp = list;
    while (temp->next->next) {
        temp = temp->next;
    }
    
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    
    return list;
}

Ht_item* linkedlist_remove(LinkedList* list) {
    if (!list) return NULL;
    if (!list->next) return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item);
    free(temp);
    return it;
}

void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item);
        free(temp);
    }
}

LinkedList** create_overflow_buckets(HashTable* table) {
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    for (int i=0; i<table->size; i++)
                   buckets[i] = NULL;
    return buckets;
}

void free_overflow_buckets(HashTable* table) {
    LinkedList** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++)
          free_linkedlist(buckets[i]);
    free(buckets);
}

void del_item(Ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

HashTable* create_table(unsigned int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**)calloc(table->size, sizeof(Ht_item*));
    for (unsigned int i=0; i<table->size; i++) {
        table->items[i] = NULL;
    }
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

void free_table(HashTable* table) {
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            del_item(item);
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
    LinkedList* head = table->overflow_buckets[index];

    if (head == NULL) {
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
 }

void ht_search(HashTable* table, char* key) {
    int index = RSHash(key, (unsigned int)strlen(key));
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];
    
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            printFlat(*(item->value));
        }
        item = head->item;
        head = head->next;
    }
}

Ht_item* create_item(char* key, flat* value) {
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*)malloc(strlen(key) + 1);
    item->value = (flat*)malloc(sizeof(flat));
    
    strcpy(item->key, key);
    item->value = value;

    return item;
}

void ht_insert(HashTable* table, char* key, flat* value) {
    Ht_item* item = create_item(key, value);

    unsigned long index = RSHash(key, (unsigned int)strlen(key));

    Ht_item* current_item = table->items[index];
    
    if (current_item == NULL) {
        if (table->count == table->size) {
            printf("Insert Error: Hash Table is full\n");
            del_item(item);
            return;
        }
        
        table->items[index] = item;
        table->count++;
    }

    else {
            if (strcmp(current_item->key, key) == 0) {
                table->items[index]->value = value;
                return;
            }
    
        else {
            handle_collision(table, index, item);
            return;
        }
    }
}

void HtFromArray(HashTable* table, flat* arr, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        ht_insert(table, arr[i].name, &arr[i]);
    }
}
