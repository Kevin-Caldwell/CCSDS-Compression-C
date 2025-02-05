/**
 * @file local_differences.h
 * @authors Kevin Caldwell @BrianShTsoi
 * @brief Central and Directional Local Difference
 * Functions and Definitions
 */

#ifndef LOCAL_DIFFERENCES_H
#define LOCAL_DIFFERENCES_H

#include "math/linear_algebra.h"
#include "predictor/local_sum.h"

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

/** 
 * @brief Shorthand for Direct Local Difference 
 * @warning Direct Image Access
 */
#define L_DLD(hIMG, z, y, x, d) L_DirectionalLocalDifference(hIMG, z, y, x, d)
#define DLD(hIMG, s, d) DirectionalLocalDifference(hIMG, s, d)
/** 
 * @brief Shorthand for North Direct Local Difference
 * @warning Direct Image Access
 */
#define DLD_N(hIMG) DirectionalLocalDifference(hIMG, N)
/** 
 * @brief Shorthand for West Direct Local Difference
 * @warning Direct Image Access
 */
#define DLD_W(hIMG) DirectionalLocalDifference(hIMG, W)
/** 
 * @brief Shorthand for NorthWest Direct Local Difference
 * @warning Direct Image Access
 */
#define DLD_NW(hIMG) DirectionalLocalDifference(hIMG, NW)

/**
 * @brief Finds the Central Local Difference using Direct Image Access
 * @note Soon Deprecated
 * @warning Direct Image Access
 */
int32_t L_CentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x);
int32_t CentralLocalDifference(LBuf *buf, dim3 s, INDEX z, INDEX y, INDEX x);

/** @brief Finds the Directional Local Difference using Direct Image Access
 * @note Soon Deprecated
 * @warning Direct Image Access
 */
int32_t DirectionalLocalDifference(LBuf *hIMG, dim3 s, int direction);

int32_t L_DirectionalLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, int direction);

/**
 * @brief Finds the Local Direction Vector using Direct Image Access
 * @note Soon Deprecated
 * @warning Direct Image Access
 */
int L_LocalDirectionVector(image *hIMG, int32_t *local_direction_vector, INDEX z, INDEX y, INDEX x);
int LocalDirectionVector(LBuf *buf, dim3 s, int32_t *lDV);

#endif /* LOCAL_DIFFERENCES_H */
