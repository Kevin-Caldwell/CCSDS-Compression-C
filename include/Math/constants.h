#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "math_functions.h"

// Comment if using Unsigned Samples
#define UNSIGNED_SAMPLES

// Image Size Constants
#define Nx 640
#define Ny 512
#define Nz 640


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

//* Uncomment if Lossless compression is required
//#define LOSSLESS

#pragma region Do Not Touch

#define D CLIP(DYNAMIC_RANGE, 2, 32)
extern const int D_range;

#ifdef UNSIGNED_SAMPLES
extern const int Smin;
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
#define omega_min -(BPOW(Omega + 2)
#define omega_max BPOW(Omega + 2) - 1

#define THETA CLIP(RESOLUTION, 0, 4)

#pragma endregion
#endif