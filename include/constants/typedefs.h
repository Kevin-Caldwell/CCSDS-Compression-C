/**
 * \file typedefs.h
 * \author Kevin Caldwell
 * \brief A file containing univerally used typedefs
 * \date May 29, 2024
*/
#ifndef TYPEDEFS_H
#define TYPEDEFS_H



/**
 * All Error Codes in Program.
 */
typedef enum ERROR_CODES
{
    RES_OK = 0,
    FILE_ACCESS_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    MEM_ALLOC_ERROR,
    HASH_FULL
} error_t, ERROR_CODES, EXIT_CODES;

//-----------------PREDICTOR TYPEDEFS------------------//

/** \brief Enum for Types of Local Sum Calculators */
typedef enum t_local_sum
{
    LS_WIDE_NEIGHBOR = 0,
    LS_NARROW_NEIGHBOR,
    LS_WIDE_COLUMN,
    LS_NARROW_COLUMN
} t_local_sum;

/** \brief Enumeration for Prediction Modes. */
typedef enum t_prediction_mode
{
    PM_FULL = 0,
    PM_REDUCED
} t_prediction_mode;

/** \brief char redefined to BOOL */
typedef uint8_t         BOOL;

/** \brief Type encoding a Dimension of the Hyperspectral Image */
typedef int32_t         DIM;

/** \brief unsigned int shorthand */
typedef unsigned int    UINT;

/** \brief Type representing each pixel in Hyperspectral Image */
typedef uint16_t        PIXEL;

/** \brief Type representing Indices of Image */
typedef DIM             INDEX;

#endif /* TYPEDEFS_H */
