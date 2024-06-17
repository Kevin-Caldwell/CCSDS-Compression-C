#include "dst/hash_table.h"

error_t Hash_InitializeHashTable(HashTable *hash)
{
    hash->len = 0;
    return RES_OK;
}

error_t Hash_DeleteHashTable(HashTable *hash)
{
    free(hash);
    return RES_OK;
}

error_t Hash_AddEntry(HashTable *hash, const char *name, int32_t data)
{
    char temp[KEY_LENGTH];

    if (hash->len == HASH_CAPACITY)
    {
        return HASH_FULL;
    }

    hash->data[hash->len] = data;

    memcpy(temp, name, KEY_LENGTH);
    memcpy(hash->keys[hash->len], temp, KEY_LENGTH);
    hash->len++;
    
    return RES_OK;
}

INDEX Hash_GetIndex(HashTable *hash, const char *key)
{
    int index = 0;
    for (index = 0; index < hash->len; index++)
    {
        if (!strncmp(hash->keys[index], key, KEY_LENGTH))
        {
            return index;
        }
    }
    return -1;
}

int32_t Hash_GetValue(HashTable *hash, const char *key)
{
    return hash->data[Hash_GetIndex(hash, key)];
}

error_t Hash_SetValue(HashTable *hash, const char *key, int32_t new_data)
{
    hash->data[Hash_GetIndex(hash, key)] = new_data;
    return RES_OK;
}