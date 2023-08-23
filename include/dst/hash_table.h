#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#define HASH_CAPACITY 30
#define KEY_LENGTH 30

typedef struct HashTable
{
    char keys[HASH_CAPACITY][KEY_LENGTH];
    int32_t data[HASH_CAPACITY];
    int len;
} HashTable;

int Hash_InitializeHashTable(HashTable **hash);

int Hash_DeleteHashTable(HashTable* hash);

int Hash_AddEntry(HashTable *hash, const char* name, int32_t data);

int Hash_GetIndex(HashTable *hash, const char *key);

int32_t Hash_GetValue(HashTable *hash, const char *key);

int Hash_SetValue(HashTable *hash, const char *key, int32_t new_data);

#endif /* HASH_TABLE_H */
