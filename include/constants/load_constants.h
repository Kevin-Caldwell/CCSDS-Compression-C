/**
 * @file load_constants.h
 *
 * @brief Abstractions for Loading .CONST files
 * @details
 * Features
 *  Custom .CONST file format with easy-to-read Constant Parameter Storage
 */

#ifndef LOAD_CONSTANTS_H
#define LOAD_CONSTANTS_H

#include <stdlib.h>
#include "dst/hash_table.h"
#include "constants/predictor_constants.h"

/**
 * @brief Loads a .CONST file into a HashTable filled with constants.
*/
int LoadConstantFile(const char *file_name, HashTable *result);


/**
 * @brief Saves the current predictor configuration into a file.
 * @details
 * Saves constants into a .const file.
 * 
 * Stores all constants in format: 
 * <constant_name>:<value>
 * 
 * constant_name: string with a maximum length defined in KEY_LENGTH
 * value: integer which corresponds directly to the constant, or refers to the 
 * respective enumeration.
 */
error_t SavePredictorConstants(S_kPred* kPred, char* file_name);

#endif /* LOAD_CONSTANTS_H */
