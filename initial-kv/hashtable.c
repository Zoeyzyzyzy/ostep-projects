#include "hashtable.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>


void initHashTable(HashTable *table, int size){
    table->size = size;
    table->buckets = calloc(size, sizeof(HashNode *));
}

unsigned int hashFunction(const int key, int tableSize){
    unsigned int hash = key;
    return hash % tableSize;
}

void put(HashTable *table, const int key, const char *value) {
    unsigned int index = hashFunction(key, table->size);
    HashNode *current = table->buckets[index];
    while (current != NULL)
    {
        if(current->key == key){
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    HashNode *newNode = malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = strdup(value);
    newNode->next = table->buckets[index]; //插入到表头
    table->buckets[index] = newNode;
}

char* get(HashTable *table, int key){
    unsigned int index = hashFunction(key, table->size);
    HashNode *node = table->buckets[index];
    while (node)
    {
        if(node->key == key)
            return node->value;
        node = node->next;
    }
    return NULL;
}

int deleteKey(HashTable *table, int key){
    unsigned int index = hashFunction(key, table->size);
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;

    while (node)
    {
        if(node->key == key){
            if(prev == NULL)
                table->buckets[index] = node->next;
            else
                prev->next = node->next;
            node->next = NULL;
            free(node->value);
            free(node);
            return 0;
        }
        prev = node;
        node = node->next;
    }
    return -1;
}

void clear(HashTable *table){
    if(table == NULL)
        return;
    for (int i = 0; i < table->size; i++){
        HashNode *node = table->buckets[i];
        while (node)
        {
            HashNode *temp = node;
            node = node->next;
            free(temp->value);
            free(temp);
        }
    }
    free(table->buckets);
    table->buckets = NULL;
    table->size = 0;
}

void all(HashTable *table){
    if(table == NULL)
        return;
    for (int i = 0; i < table->size; i++){
        HashNode *node = table->buckets[i];
        while (node)
        {
            printf("%d, %s\n", node->key, node->value);
            node = node->next;
        }
    }
}