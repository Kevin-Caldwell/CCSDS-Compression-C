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

#include "constants/typedefs.h"

#ifndef NULL
#define NULL 0
#endif

// Restrict x between min_val and max_val
#define CLIP(x, min_val, max_val) ((x) < (min_val) ? (min_val) : ((x) > (max_val) ? (max_val) : (x)))

// Check if x is within [min, max]
#define INSIDE_INTERVAL(x, min, max) (min < x && x < max)
// Check if x is outside [min, max]
#define OUTSIDE_INTERVAL(x, min, max) (min > x || x > max)

// Return 0 if x=0, -1 if x<1, +1 if x>1
#define SIGN(x) x < 0 ? -1 : (x > 0 ? 1 : 0)
// Return -1 if x in (-inf., 0), 1 x in [0, inf.)
#define SIGN_P(x) (x < 0 ? -1 : 1)

// Returns an overflow-adjusted modulo
#define MOD(x, R) ((x + BPOW(R - 1)) % BPOW(R) - BPOW(R - 1))

// Max of a and b
#define MAX(a, b) (a > b ? a : b)
// Min of a and b
#define MIN(a, b) (a < b ? a : b)

// Returns 2^x
#define BPOW(x) (1 << (x))

// Square of x
#define SQ(x) ((x) * (x))

#define Ps(z) MIN(z, kP)

/// Error Codes: TODO
enum RetVal
{
    OK = 0,
    ERROR
};

/**
 * 3D Dimension Struct, used to describe size
 * and 3D-Indicies.
 *
 * Spatial Dimensions: x, y
 * Spectral Band: z
 */
typedef struct dim3
{
    DIM x;
    DIM y;
    DIM z;
} dim3;

typedef struct dim2
{
    DIM x;
    DIM y;
} dim2;

UINT Euclidian2(dim2 pt1, dim2 pt2);
UINT Euclidian3(dim3 pt1, dim3 pt2);

UINT Manhattan2(dim2 pt1, dim2 pt2);
UINT Manhattan3(dim3 pt1, dim3 pt2);

#endif /* MATH_FUNCTIONS_H */
