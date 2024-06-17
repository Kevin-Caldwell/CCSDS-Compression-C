/**
 * \file load_constants.h
 * \author Kevin Caldwell
 *
 * \brief Abstractions for Loading .CONST files
 * \details
 * Features
 *  Custom .CONST file format with easy-to-read Constant Parameter Storage
 *
 * \todo Add a SaveConstantFile Function \n
 * FUNCDEF: int SaveConstantFile(const char* file_name, HashTable* save_input)
 */

#ifndef LOAD_CONSTANTS_H
#define LOAD_CONSTANTS_H

#include "dst/hash_table.h"

/**
 * \author Kevin Caldwell
 * \brief Loads a .CONST file into a HashTable filled with constants.
*/
int LoadConstantFile(const char *file_name, HashTable *result);

#endif /* LOAD_CONSTANTS_H */
