#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef int32_t DIM;
typedef unsigned int UINT;
typedef uint16_t PIXEL;
typedef int16_t INDEX;

typedef enum ERROR_CODES
{
    RES_OK = 0,
    FILE_ACCESS_ERROR,
    FILE_READ_ERROR,
    FILE_WRITE_ERROR,
    MEM_ALLOC_ERROR,
    HASH_FULL
} ERROR_CODES;



#endif /* TYPEDEFS_H */
