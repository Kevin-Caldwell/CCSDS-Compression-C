#include "Math/constants.h"

#pragma region Do Not Touch

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
const int R = CLIP(REGISTER_SIZE_PARAMETER, MAX(32, D + Omega + 2), 64);

#pragma endregion