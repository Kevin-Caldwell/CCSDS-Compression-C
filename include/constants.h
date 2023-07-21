#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "math/math_functions.h"

// Comment if using Unsigned Samples
#define UNSIGNED_SAMPLES

// Image Size Constants
#define Nx 640
#define Ny 512
#define Nz 640

//* Uncomment if Lossless compression is required
//#define LOSSLESS

// Predictor Constants

// Comment if using Full Prediction Mode
//#define REDUCED_PREDICTION_MODE

//* Uncomment ONE of the following options for prediction
#define WIDE_NEIGHBOR
//#define NARROW_NEIGHBOR
//#define WIDE_COLUMN
//#define NARROW_COLUMN

#define DYNAMIC_RANGE 2
#define PREVIOUS_BAND_SAMPLES 3

#define RESOLUTION 100

#define WEIGHT_RESOLUTION 19
#define REGISTER_SIZE_PARAMETER 1

#define WEIGHT_UPDATE_V_MIN -6
#define WEIGHT_UPDATE_V_MAX 9
// WEIGHT_UPDATE_SCALING_EXPONENT_CHANGE_INTERVAL
#define CHANGE_INTERVAL BPOW(11)


#ifndef LOSSLESS
#define ABSOLUTE_ERROR_LIMIT 38
#else
#define ABSOLUTE_ERROR_LIMIT 0
#endif


typedef uint16_t PIXEL;
typedef size_t INDEX;


#pragma region Do Not Touch
// TODO Rename ALL Constants to: kConstant

#define D CLIP(DYNAMIC_RANGE, 2, 32)
extern const int D_range;

#ifdef UNSIGNED_SAMPLES
extern const int kSmin;
extern const int Smax;
extern const int Smid;

#else
extern const int Smin;
extern const int Smax;
extern const int Smid;
#endif

extern const int P;
#define Omega CLIP(WEIGHT_RESOLUTION, 4, 19)
extern const int R;
extern const int omega_min;
extern const int omega_max;

#define THETA CLIP(RESOLUTION, 0, 4)

#define Da MIN(D-1, 16)
#define m_z CLIP(Da, 1, BPOW(Da) - 1)

extern const int vMin;
extern const int vMax;
extern const int tInc;

#pragma endregion
#endif /* CONSTANTS_H */
