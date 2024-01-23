/**
 * load_constants.h
 * @author @Kevin-Caldwell
 * 
 * Abstractions for Loading .CONST files
 * 
 * Features
 *  Custom .CONST file format with easy-to-read Constant Parameter Storage
 * 
 * Uses
 *  Interpreting .CONST Files to load constants for all modules
 *  Stores result in a HashTable structure
 * 
 * Dependencies
 *  hash_table.h
 * 
 * Internal Dependencies
 *  stdio.h
 * 
 * TODO
 *  Add a SaveConstantFile Function
 *      FUNCDEF: int SaveConstantFile(const char* file_name, HashTable* save_input)
*/

#ifndef LOAD_CONSTANTS_H
#define LOAD_CONSTANTS_H

#include "dst/hash_table.h"

int LoadConstantFile(const char* file_name, HashTable* result);

#endif /* LOAD_CONSTANTS_H */
