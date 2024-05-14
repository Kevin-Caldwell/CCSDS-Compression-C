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
    kTInc = (int)GET_PCONST("CHANGE_INTERVAL");
    kVMin = (int)GET_PCONST("WEIGHT_UPDATE_V_MIN");
    kVMax = (int)GET_PCONST("WEIGHT_UPDATE_V_MAX");

    kUnsignedSamples = (int)GET_PCONST("UNSIGNED_SAMPLES");
    D = (UINT)GET_PCONST("D");
    Da = (int)MIN(D - 1, 16);
    kSmin = -BPOW(D - 1);

    if (kUnsignedSamples)
    {
        kSmin = 0;
        kSmax = BPOW((unsigned)D) - 1;
        kSmid = BPOW((unsigned)D - 1);
    }
    else
    {
        kSmin = -BPOW(D - 1);
        kSmax = BPOW(D) - 1;
        kSmid = 0;
    }

    kPredictionMode = (int)GET_PCONST("PREDICTION_MODE");
    kP = (int32_t)GET_PCONST("P");
    kR = (int64_t)GET_PCONST("REGISTER_SIZE_PARAMETER");

    Omega = (int)GET_PCONST("WEIGHT_RESOLUTION");

    kOmegaMin = -(BPOW((UINT)(Omega + 2)));
    kOmegaMax = BPOW((UINT)(Omega + 2)) - 1;

    kLocalSumType = (int)GET_PCONST("LOCAL_SUM_TYPE");
    km_z = (int)GET_PCONST("ABSOLUTE_ERROR_LIMIT");
}

DIM Nx = (DIM)0;
DIM Ny = (DIM)0;
DIM Nz = (DIM)0;

HashTable predictor_constants;
HashTable encoder_constants;

int kUnsignedSamples = 0;
t_local_sum kLocalSumType = 0;

int kPredictionMode = 0;

unsigned int D;
int Da = 0;

unsigned int kSmin = 0;
unsigned int kSmid = 0;
unsigned int kSmax = 0;

int32_t kP = 0;
int64_t kR = 0;

int kVMax = 0;
int kVMin = 0;
int kTInc = 0;

int Omega = 0;
int kOmegaMin = 0;
int kOmegaMax = 0;

int km_z;