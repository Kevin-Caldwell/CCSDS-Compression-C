#include "dst/hash_table.h"

int Hash_InitializeHashTable(HashTable **hash)
{
    *hash = malloc(sizeof(HashTable));
    (*hash)->len = 0;

    return 0;
}

int Hash_DeleteHashTable(HashTable *hash)
{
    free(hash);
    return 0;
}

int Hash_AddEntry(HashTable *hash, const char *name, int32_t data)
{
    if (hash->len == HASH_CAPACITY)
    {
        return 1;
    }

    hash->data[hash->len] = data;
    strncpy(hash->keys[hash->len++], name, KEY_LENGTH);
}

int Hash_GetIndex(HashTable *hash, const char *key)
{
    int index = 0;
    for (index = 0; index < hash->len; index++)
    {
        if (!strncmp(hash->keys[index], key, KEY_LENGTH))
        {
            break;
        }
    }
    return index;
}

int32_t Hash_GetValue(HashTable *hash, const char *key)
{
    return hash->data[Hash_GetIndex(hash, key)];
}

int Hash_SetValue(HashTable *hash, const char *key, int32_t new_data)
{
    hash->data[Hash_GetIndex(hash, key)] = new_data;
    return 0;
}