#pragma once
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
const int D_range = D;

#ifdef UNSIGNED_SAMPLES
const int Smin = 0;
const int Smax = BPOW(D) - 1;
const int Smid = BPOW(D - 1);

#else
const int Smin = -BPOW(D - 1);
const int Smax = BPOW(D) - 1;
const int Smid = 0;
#endif

const int P = CLIP(PREVIOUS_BAND_SAMPLES, 0, 15);
#define Omega CLIP(WEIGHT_RESOLUTION, 4, 19)
const int R = CLIP(REGISTER_SIZE_PARAMETER, MAX(32, D + Omega + 2), 64);
#define omega_min -(BPOW(Omega + 2)
#define omega_max BPOW(Omega + 2) - 1

#define THETA CLIP(RESOLUTION, 0, 4)

#pragma endregion