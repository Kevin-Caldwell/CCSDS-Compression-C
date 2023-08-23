#include "constants/constants.h"

void InitalizeImageConstants(dim3 size)
{
    Nx = size.x;
    Ny = size.y;
    Nz = size.z;
}

#define GET_PCONST(x) (Hash_GetValue(&predictor_constants, x))

void InitalizePredictorConstants()
{
    kTInc = GET_PCONST("CHANGE_INTERVAL");
    kVMin = GET_PCONST("WEIGHT_UPDATE_V_MIN");
    kVMax = GET_PCONST("WEIGHT_UPDATE_V_MAX");

    kUnsignedSamples = GET_PCONST("UNSIGNED_SAMPLES");
    D = GET_PCONST("D");
    Da = MIN(D - 1, 16);
    kSmin = -BPOW(D - 1);

    if (kUnsignedSamples)
    {
        kSmin = 0;
        kSmax = BPOW(D) - 1;
        kSmid = BPOW(D - 1);
    }
    else
    {
        kSmin = -BPOW(D - 1);
        kSmax = BPOW(D) - 1;
        kSmid = 0;
    }

    PREDICTION_MODE = GET_PCONST("PREDICTION_MODE");
    kP = GET_PCONST("P");
    kR = GET_PCONST("REGISTER_SIZE_PARAMETER");

    Omega = GET_PCONST("WEIGHT_RESOLUTION");

    kOmegaMin = -(BPOW(Omega + 2));
    kOmegaMax = BPOW(Omega + 2) - 1;

    LOCAL_SUM_TYPE = GET_PCONST("LOCAL_SUM_TYPE");
    m_z = GET_PCONST("ABSOLUTE_ERROR_LIMIT");
}

#pragma region Do Not Touch

int Nx = 0;
int Ny = 0;
int Nz = 0;

HashTable predictor_constants;
HashTable encoder_constants;

int kUnsignedSamples = 0;
int LOCAL_SUM_TYPE = 0;

int PREDICTION_MODE = 0;

int D = 0;
int Da = 0;

uint kSmin = 0;
uint kSmid = 0;
uint kSmax = 0;

int kP = 0;
int64_t kR = 0;

int kVMax = 0;
int kVMin = 0;
int kTInc = 0;

int Omega = 0;
int kOmegaMin = 0;
int kOmegaMax = 0;

int m_z;

#pragma endregion