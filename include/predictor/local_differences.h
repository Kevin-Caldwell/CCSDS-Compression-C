/**
 * local_differences.h
 * @authors Kevin Caldwell @BrianShTsoi
 *
 * Central and Directional Local Difference
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

#define Ps(z) MIN(z, kP)

enum DIRECTION
{
    N = 0,
    W,
    NW
};

#define DLD(hIMG, z, y, x, d) DirectionalLocalDifference(hIMG, z, y, x, d)
#define DLD_N(hIMG, z, y, x) DirectionalLocalDifference(hIMG, z, y, x, N)
#define DLD_W(hIMG, z, y, x) DirectionalLocalDifference(hIMG, z, y, x, W)
#define DLD_NW(hIMG, z, y, x) DirectionalLocalDifference(hIMG, z, y, x, NW)

int32_t CentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x);

int32_t DirectionalLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, int direction);

int LocalDirectionVector(image *hIMG, int32_t *local_direction_vector, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_DIFFERENCES_H */
