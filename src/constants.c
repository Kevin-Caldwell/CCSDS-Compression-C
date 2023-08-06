#include "constants/constants.h"

#pragma region Do Not Touch

const int D_range = D;

#ifdef UNSIGNED_SAMPLES
const int kSmin = 0;
const int kSmax = BPOW(D) - 1;
const int kSmid = BPOW(D - 1);

#else
const int kSmin = -BPOW(D - 1);
const int kSmax = BPOW(D) - 1;
const int kSmid = 0;
#endif

const int kP = CLIP(PREVIOUS_BAND_SAMPLES, 0, 15);
const int kR = CLIP(REGISTER_SIZE_PARAMETER, MAX(32, D + Omega + 2), 64);

const int kVMax = CLIP(WEIGHT_UPDATE_V_MAX, -6 , 9);
const int kVMin = CLIP(WEIGHT_UPDATE_V_MIN, -6, kVMax);
const int kTInc = CLIP(BPOW(CHANGE_INTERVAL), BPOW(4), BPOW(11));

const int kOmegaMin = -(BPOW(Omega + 2));
const int kOmegaMax = BPOW(Omega + 2) - 1;

#pragma endregion