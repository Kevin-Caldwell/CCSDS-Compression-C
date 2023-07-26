#ifndef MATH_FUNCTIONS
#define MATH_FUNCTIONS

#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <stddef.h>

#ifndef NULL
#define NULL 0
#endif


#define CLIP(x, min_val, max_val) ((x) < (min_val) ? (min_val) : ((x) > (max_val) ? (max_val) : (x)))
#define SIGN(x) x < 0 ? -1 : (x > 0 ? 1 : 0)
#define SIGN_P(x) x >> (sizeof(x) * 8 - 1) ? -1 : 1

#define MOD(x, R) (x + BPOW(R - 1) % BPOW(R) - BPOW(R - 1))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define BPOW(x) (1 << (x))

/// Error Codes: TODO
enum RetVal{
    OK = 0, ERROR
};

typedef size_t DIM;
typedef unsigned int UINT;


/* Spatial Dimensions: x, y
Spectral Band: z
*/
typedef struct dim3{
    DIM x;
    DIM y;
    DIM z;
} dim3;

#endif /* MATH_FUNCTIONS */
