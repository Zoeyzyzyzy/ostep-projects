#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode {
    int key;
    char *value;
    struct HashNode *next;
} HashNode;

typedef struct
{
    HashNode **buckets;
    int size;
} HashTable;

void initHashTable(HashTable *table, int size);
void put(HashTable *table, const int key, const char *value);
char *get(HashTable *table, int key);
int deleteKey(HashTable *table, int key);
void clear(HashTable *table);
void all(HashTable *table);


#endif