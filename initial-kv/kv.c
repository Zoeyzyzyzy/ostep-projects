#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"

void loadHashTableFromFile(HashTable *table, const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    char buffer[1024];
    int key;
    char value[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if(sscanf(buffer, "%d, %1023s", &key, value) == 2){
            put(table, key, value);
        }else{
            fprintf(stderr, "Failed to parse line: %s\n", buffer);
        }
    }
    fclose(file);
}

void saveHashTableToFile(HashTable *table, const char *filename){
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < table->size; i++)
    {
        HashNode *node = table->buckets[i];
        while (node)
        {
            fprintf(file, "%d, %s\n", node->key, node->value);
            node = node->next;
        }
    }
    fclose(file);
}

typedef struct 
{
    char *ops;
    int key;
    char *value;
}inputData;

int main(int argc, char *argv[])
{
    if(argc < 2){
        //printf("Usage: %s 'inputString'\n", argv[0]);
        return 0;
    }
    HashTable table;
    initHashTable(&table, 128);
    loadHashTableFromFile(&table, "database.txt");
    inputData cur;
    for (int i = 1; i < argc; i++)
    {
        char* token;
        int nums = 1;
        while ((token = strsep(&argv[i], ",")) != NULL)
        {
            if(nums == 1)
                cur.ops = token;
            if(nums == 2) cur.key = atoi(token);
            else
                cur.value = token;
            nums++;
        }
        if (strcmp(cur.ops, "p") == 0)
            put(&table, cur.key, cur.value);
        else if (strcmp(cur.ops, "g") == 0)
        {
            char *res = get(&table, cur.key);
            if(res != NULL) 
            {
                printf("%d,%s\n", cur.key, res);
            }
            else {
                printf("%d not found\n", cur.key);
            }
        } else if(strcmp(cur.ops, "d") == 0){
            int res = deleteKey(&table, cur.key);
            if(res == -1){
                printf("%d not found\n", cur.key);
            }
        } else if(strcmp(cur.ops, "c") == 0){
            clear(&table);
        } else if(strcmp(cur.ops, "all") == 0){
            all(&table);
        } else{
            printf("bad command\n");
        }
    }
    saveHashTableToFile(&table, "database.txt");
    return 0;
}
