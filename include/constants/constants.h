/**
 * constants.h
 * @author @Kevin-Caldwell
 *
 * A global file for constats that need to be shared between modules.
 *
 * Features
 *  Image Constants
 *
 * Uses
 *  Values used by all modules
 *
 * Dependencies
 *  math_functions.h
 *  global_constants.h
 *
 * TODO
 *  Need to organize values into encoder_constants.h and predictor_constants.h
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "math/math_functions.h"
#include "global_constants.h"

#define TRUE 1
#define FALSE 0

// Image Size Constants
extern DIM Nx;
extern DIM Ny;
extern DIM Nz;

extern int LOSSLESS;

// Predictor Constants

// Comment if using Full Prediction Mode
// #define REDUCED_PREDICTION_MODE

// 0: Full Prediction Mode
// 1: Reduced Prediction Mode
extern int kPredictionMode;

typedef enum t_local_sum
{
    LS_WIDE_NEIGHBOR = 0,
    LS_NARROW_NEIGHBOR,
    LS_WIDE_COLUMN,
    LS_NARROW_COLUMN
} t_local_sum;

// 0b00: Wide Neighbor
// 0b01: Narrow Neighbor
// 0b10: Wide Column
// 0b11: Narrow Column
extern t_local_sum kLocalSumType;

#define DYNAMIC_RANGE 14
#define PREVIOUS_BAND_SAMPLES 3

#define RESOLUTION 100

// 0: Default Weight Initialization
// 1: Custom Weight Initialization
#define WEIGHT_INITIALIZATION 0

// 0: WEO values are zero
// 1: WEO values can be non-zero
#define WEIGHT_EXPONENT_OFFSET_FLAG 0
// 2^WEIGHT_UPDATE_SCALING_EXPONENT_CHANGE_INTERVAL

#pragma region Do Not Touch
// TODO Rename ALL Constants to: kConstant

extern unsigned int D;

extern int kUnsignedSamples;

extern unsigned int kSmin;
extern unsigned int kSmax;
extern unsigned int kSmid;

extern int32_t kP;
extern int Omega;
extern int64_t kR;
extern int kOmegaMin;
extern int kOmegaMax;

extern int Da;
extern int km_z;
extern int C;

extern int kVMin;
extern int kVMax;
extern int kTInc;

void InitalizeImageConstants(dim3 size);
void InitalizePredictorConstants();

#pragma endregion
#endif /* CONSTANTS_H */
