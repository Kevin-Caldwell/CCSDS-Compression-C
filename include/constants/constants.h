#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "math/math_functions.h"

// Comment if using Unsigned Samples
#define UNSIGNED_SAMPLES

// Image Size Constants
#define Nx ((uint16_t) 640) // 100 //640
#define Ny ((uint16_t) 512) // 100 //512
#define Nz ((uint16_t) 640) // 100 //640

//* Uncomment if Lossless compression is required
#define LOSSLESS

// Predictor Constants

// Comment if using Full Prediction Mode
//#define REDUCED_PREDICTION_MODE


// 0: Full Prediction Mode
// 1: Reduced Prediction Mode
#define PREDICTION_MODE 0

//* Uncomment ONE of the following options for prediction
#define WIDE_NEIGHBOR
//#define NARROW_NEIGHBOR
//#define WIDE_COLUMN
//#define NARROW_COLUMN

// 00: Wide Neighbor
// 01: Narrow Neighbor
// 10: Wide Column
// 11: Narrow Column
#define LOCAL_SUM_TYPE 0b00

#define DYNAMIC_RANGE 14
#define PREVIOUS_BAND_SAMPLES 3

#define RESOLUTION 100

#define WEIGHT_RESOLUTION 19
#define REGISTER_SIZE_PARAMETER 32


// 0: Default Weight Initialization
// 1: Custom Weight Initialization
#define WEIGHT_INITIALIZATION 0

// 0: WEO values are zero
// 1: WEO values can be non-zero
#define WEIGHT_EXPONENT_OFFSET_FLAG 0

#define WEIGHT_UPDATE_V_MIN -6
#define WEIGHT_UPDATE_V_MAX 9
// 2^WEIGHT_UPDATE_SCALING_EXPONENT_CHANGE_INTERVAL
#define CHANGE_INTERVAL 4


#ifndef LOSSLESS
#define ABSOLUTE_ERROR_LIMIT 38
#else
#define ABSOLUTE_ERROR_LIMIT 0
#endif


#pragma region Do Not Touch
// TODO Rename ALL Constants to: kConstant

#define D CLIP(DYNAMIC_RANGE, 2, 32)
extern const int D_range;


extern const int kSmin;
extern const int kSmax;
extern const int kSmid;

extern const int kP;
#define Omega CLIP(WEIGHT_RESOLUTION, 4, 19)
extern const int64_t kR;
extern const int kOmegaMin;
extern const int kOmegaMax;

#define THETA CLIP(RESOLUTION, 0, 4)

#define Da MIN(D-1, 16)
#define m_z ABSOLUTE_ERROR_LIMIT

extern const int kVMin;
extern const int kVMax;
extern const int kTInc;

#pragma endregion
#endif /* CONSTANTS_H */
