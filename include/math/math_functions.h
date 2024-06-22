/**
 * @file math_functions.h
 * @brief Mathematical Helper Functions for use throughout code.
 */

#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include "constants/typedefs.h"

/**
 * @brief NULL typedef to 0 if it does not exist yet.
 */
#ifndef NULL
#define NULL 0
#endif

/** @brief Restrict x between min_val and max_val */
#define CLIP(x, min_val, max_val) ((x) < (min_val) ? (min_val) : ((x) > (max_val) ? (max_val) : (x)))

/** @brief Check if x is within [min, max] */
#define INSIDE_INTERVAL(x, min, max) (min < x && x < max)
/** @brief Check if x is outside [min, max] */
#define OUTSIDE_INTERVAL(x, min, max) (min > x || x > max)

/** @brief Return 0 if x=0, -1 if x<1, +1 if x>1 */
#define SIGN(x) x < 0 ? -1 : (x > 0 ? 1 : 0)
/** @brief Return -1 if x in (-inf., 0), 1 x in [0, inf.) */
#define SIGN_P(x) (x < 0 ? -1 : 1)

/** @brief Returns an overflow-adjusted modulo */
#define MOD(x, R) ((x + BPOW(R - 1)) % BPOW(R) - BPOW(R - 1))

/** @brief Max of a and b */
#define MAX(a, b) (a > b ? a : b)
/** @brief Min of a and b */
#define MIN(a, b) (a < b ? a : b)

/** @brief Returns 2^x */
#define BPOW(x) (1 << (x))

/** @brief Square of x */
#define SQ(x) ((x) * (x))

/** @brief Calculates Ps, Refer to Standard */
#define Ps(z) MIN(z, kP)

/**
 * @brief struct for 3d coordinates.
 * @details
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

/**
 * @brief struct for 2d coordinates.
 * @details
 * 2D Struct, used to describe size
 * and 2D Indices.
 */
typedef struct dim2
{
    DIM x;
    DIM y;
} dim2;

/**
 * @todo Relocate to reduce scope
 */
UINT Euclidian2(dim2 pt1, dim2 pt2);

/**
 * @todo Relocate to reduce scope
 */
UINT Euclidian3(dim3 pt1, dim3 pt2);


/**
 * @todo Relocate to reduce scope
 */
UINT Manhattan2(dim2 pt1, dim2 pt2);

/**
 * @todo Relocate to reduce scope
 */
UINT Manhattan3(dim3 pt1, dim3 pt2);

#endif /* MATH_FUNCTIONS_H */
