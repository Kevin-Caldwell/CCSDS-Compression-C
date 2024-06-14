/**
 * \file typedefs.h
 * \author Kevin Caldwell
 * \brief A file containing univerally used typedefs
 * \date May 29, 2024
*/
#ifndef TYPEDEFS_H
#define TYPEDEFS_H


typedef uint8_t         BOOL;            
typedef int32_t         DIM;    //!\brief Type encoding a Dimension of the Hyperspectral Image
typedef unsigned int    UINT;   //!\brief unsigned int shorthand
typedef uint16_t        PIXEL;  //!\brief Type representing a pixel 
typedef DIM             INDEX;  //!\brief Type representing an index

typedef enum ERROR_CODES        //!\brief Enumeration of all the Exit Codes
{
    RES_OK = 0,
    FILE_ACCESS_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    MEM_ALLOC_ERROR,
    HASH_FULL
} ERROR_CODES, EXIT_CODES;

//-----------------PREDICTOR TYPEDEFS------------------//

typedef enum t_local_sum        //!\brief Enum for Types of Local Sum Calculators
{
    LS_WIDE_NEIGHBOR = 0,
    LS_NARROW_NEIGHBOR,
    LS_WIDE_COLUMN,
    LS_NARROW_COLUMN
} t_local_sum;

typedef enum t_prediction_mode
{
    PM_FULL = 0,
    PM_REDUCED
} t_prediction_mode;

#endif /* TYPEDEFS_H */
