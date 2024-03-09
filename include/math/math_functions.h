/**
 * math_functions.h
 * @author @Kevin-Caldwell
 * 
 * Mathematical Helper Functions for use throughout code.
*/

#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <stddef.h>

#ifndef NULL
#define NULL 0
#endif


#define CLIP(x, min_val, max_val) ((x) < (min_val) ? (min_val) : ((x) > (max_val) ? (max_val) : (x)))

#define INSIDE_INTERVAL(x, min, max)    ( min < x && x < max )
#define OUTSIDE_INTERVAL(x, min, max)   ( min > x || x > max )

#define SIGN(x) x < 0 ? -1 : (x > 0 ? 1 : 0)
#define SIGN_P(x) (x < 0 ? -1 : 1)

#define MOD(x, R) ((x + BPOW(R - 1)) % BPOW(R) - BPOW(R - 1))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define BPOW(x) (1 << (x))

#define SQ(x) ((x)*(x))

typedef uint16_t DIM;
typedef unsigned int UINT;
typedef uint16_t PIXEL;
typedef uint16_t INDEX;

/// Error Codes: TODO
enum RetVal{
    OK = 0, ERROR
};

//typedef uint16_t PIXEL;


/**
 * 3D Dimension Struct, used to describe size 
 * and 3D-Indicies.
 * 
 * Spatial Dimensions: x, y
 * Spectral Band: z
*/
typedef struct dim3{
    DIM x;
    DIM y;
    DIM z;
} dim3;

typedef struct dim2{
    DIM  x;
    DIM y;
} dim2;

UINT Euclidian2(dim2 pt1, dim2 pt2);
UINT Euclidian3(dim3 pt1, dim3 pt2);

UINT Manhattan2(dim2 pt1, dim2 pt2);
UINT Manhattan3(dim3 pt1, dim3 pt2);

#endif /* MATH_FUNCTIONS_H */
