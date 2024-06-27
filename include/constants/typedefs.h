/**
 * @file typedefs.h
 * @brief A file containing univerally used typedefs
 * @date May 29, 2024
*/
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <inttypes.h>

typedef enum ACTIONS{
    COMPRESS = 0, 
    PREDICT, 
    ENCODE, 
    TEST_PREDICTOR, 
    TEST_ENCODER,
    TEST_COMPRESSOR, 
    TEST_UHI, 
    TEST_VUF
} ACTION;

/**
 * All Error Codes in Program.
 */
typedef enum ERROR_CODES
{
    RES_OK = 0,
    NO_TASK,
    TASK_NOT_DEFINED,
    ERROR_GENERIC, 
    FILE_NON_EXISTENT,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    MEM_ALLOC_ERROR,
    HASH_FULL,
    PIXEL_BUFFER_INDEX_INVALID, 
    PIXEL_BUFFER_PIXEL_NOT_FOUND
} error_t, ERROR_CODES, EXIT_CODES;

//-----------------PREDICTOR TYPEDEFS------------------//

/** @brief Enum for Types of Local Sum Calculators */
typedef enum t_local_sum
{
    LS_WIDE_NEIGHBOR = 0,
    LS_NARROW_NEIGHBOR,
    LS_WIDE_COLUMN,
    LS_NARROW_COLUMN
} t_local_sum;

/** @brief Enumeration for Prediction Modes. */
typedef enum t_prediction_mode
{
    PM_FULL = 0,
    PM_REDUCED
} t_prediction_mode;

/** @brief char redefined to BOOL */
typedef uint8_t         BOOL;

/** @brief Type encoding a Dimension of the Hyperspectral Image */
typedef int32_t         DIM;

/** @brief unsigned int shorthand */
typedef unsigned int    UINT;

/** @brief Type representing each pixel in Hyperspectral Image */
typedef uint16_t        PIXEL;

/** @brief Type representing Indices of Image */
typedef DIM             INDEX;

/** @brief Type representing vector units in linear_algebra.h */
typedef PIXEL           data_t;

/** @brief Type representing weight values in weights.h */
typedef int32_t        weight_t;

#endif /* TYPEDEFS_H */
