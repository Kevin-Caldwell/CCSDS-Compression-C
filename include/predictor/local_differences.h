/**
 * @file local_differences.h
 * @authors Kevin Caldwell @BrianShTsoi
 * @brief Central and Directional Local Difference
 * Functions and Definitions
 */

#ifndef LOCAL_DIFFERENCES_H
#define LOCAL_DIFFERENCES_H

#include "constants/constants.h"
#include "math/linear_algebra.h"
#include "math/math_functions.h"
#include "predictor/local_sum.h"
#include "predictor/weights.h"
#include "predictor/sample_representative.h"

/** 
 * @brief Redundant Definition of Ps in math_function.h 
 * @deprecated Soon
 */
#define Ps(z) MIN(z, kP)

/** @brief Direction Definition Shorthands */
enum DIRECTION
{
    N = 0,
    W,
    NW
};

/** @brief Shorthand for Direct Local Difference */
#define DLD(hIMG, z, y, x, d) DirectionalLocalDifference(hIMG, z, y, x, d)
/** @brief Shorthand for North Direct Local Difference */
#define DLD_N(hIMG, z, y, x) DirectionalLocalDifference(hIMG, z, y, x, N)
/** @brief Shorthand for West Direct Local Difference */
#define DLD_W(hIMG, z, y, x) DirectionalLocalDifference(hIMG, z, y, x, W)
/** @brief Shorthand for NorthWest Direct Local Difference */
#define DLD_NW(hIMG, z, y, x) DirectionalLocalDifference(hIMG, z, y, x, NW)

/**
 * @brief Finds the Central Local Difference using Direct Image Access
 * @note Soon Deprecated
 */
int32_t CentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x);

/** @brief Finds the Directional Local Difference using Direct Image Access
 * @note Soon Deprecated
 */
int32_t DirectionalLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, int direction);

/**
 * @brief Finds the Local Direction Vector using Direct Image Access
 * @note Soon Deprecated
 */
int LocalDirectionVector(image *hIMG, int32_t *local_direction_vector, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_DIFFERENCES_H */
