/**
 * \file hash_table.h
 * \details
 * Hash Table Implementation for Storing Constants.
 *
 * Dependencies
 *  stdlib
 *  inttypes
 *  string
 *
 * Features
 *  Initialization
 *  Deletion
 *  Add Entries
 *  Get Index
 *  Get and Set Value
 *
 * \todo Comments
 * \todo Statically Allocated Memory (High Priority)
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "constants/typedefs.h"

/**
 * @brief The maximum number of Hash Values possible.
 */
#define HASH_CAPACITY 30

/**
 * @brief Maximum Length of Key strings.
 */
#define KEY_LENGTH 30

/**
 * \struct HashTable
 * @brief A Hash Table which retrieves the integer
 * value of a text key. Designed for storing the contents
 * of .CONST files. 
 * \note Might be Deprecated in the future due to its
 * limited functionality.
 */
struct HashTable
{
    /** @brief Stores String Keys in an array */
    char keys[HASH_CAPACITY][KEY_LENGTH];

    /** @brief Stores integer data in a 1-1 relation to keys */
    int32_t data[HASH_CAPACITY];

    /** @brief Stores the number of values used up. */
    int len;
};
typedef struct HashTable HashTable;

/**
 * @brief Sets len to 0, always passes.
 * \note Not always necessary to initialize struct.
 */
error_t Hash_InitializeHashTable(HashTable *hash);

/**
 * @brief Frees a HashTable allocated on the heap.
 * \deprecated Dynamic Allocation is no longer supported
 */
error_t Hash_DeleteHashTable(HashTable *hash);

/**
 * @brief 
 * Copies the key and data into the top of the Hash.
 * Returns HASH_FULL if unable to insert new element.
 */
error_t Hash_AddEntry(HashTable *hash, const char *name, int32_t data);

/**
 * \returns The Index of the first occurance of key
 */
INDEX Hash_GetIndex(HashTable *hash, const char *key);

/**
 * @brief Returns the value associated with a key.
 * @details Returns the value associated with a key 
 * by finding the corresponding index of the key, 
 * then mapping it to the data.
 * @returns The value of the key
 * @bug Does not handle getting index of keys not already in HashTable
 */
int32_t Hash_GetValue(HashTable *hash, const char *key);

/**
 * @brief Sets new value of a given key.
 * @details Sets new value of key by mapping key with corresponding value
 * in the HashTable
 * @bug Does not handle Setting value for key not already in HashTable
 */
error_t Hash_SetValue(HashTable *hash, const char *key, int32_t new_data);

#endif /* HASH_TABLE_H */
