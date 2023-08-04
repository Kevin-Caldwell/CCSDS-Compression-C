#include "constants/constants.h"

#pragma region Do Not Touch

const int D_range = D;

#ifdef UNSIGNED_SAMPLES
const int kSmin = 0;
const int Smax = BPOW(D) - 1;
const int Smid = BPOW(D - 1);

#else
const int Smin = -BPOW(D - 1);
const int Smax = BPOW(D) - 1;
const int Smid = 0;
#endif

const int P = CLIP(PREVIOUS_BAND_SAMPLES, 0, 15);
const int R = CLIP(REGISTER_SIZE_PARAMETER, MAX(32, D + Omega + 2), 64);

const int vMax = CLIP(WEIGHT_UPDATE_V_MAX, -6 , 9);
const int vMin = CLIP(WEIGHT_UPDATE_V_MIN, -6, vMax);
const int tInc = CLIP(CHANGE_INTERVAL, BPOW(4), BPOW(11));

const int omega_min = -(BPOW(Omega + 2));
const int omega_max = BPOW(Omega + 2) - 1;

#pragma endregion