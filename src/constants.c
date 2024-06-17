#include "constants/constants.h"
#include "constants/global_constants.h"

#define GET_PCONST(x) (Hash_GetValue(&predictor_constants, x))

void InitalizePredictorConstants()
{
    kTInc = (int)GET_PCONST("CHANGE_INTERVAL");
    kVMin = (int)GET_PCONST("WEIGHT_UPDATE_V_MIN");
    kVMax = (int)GET_PCONST("WEIGHT_UPDATE_V_MAX");

    kUnsignedSamples = (int)GET_PCONST("UNSIGNED_SAMPLES");
    kD = (int32_t) GET_PCONST("D");
    kDa = (int)MIN(kD - 1, 16);
    // kSmin = -BPOW(kD - 1);

    if (kUnsignedSamples)
    {
        kSmin = 0;
        kSmax = (int) BPOW((unsigned) kD) - 1;
        kSmid = (int) BPOW((unsigned) kD - 1);
    }
    else
    {
        kSmin = (int) -BPOW((unsigned) kD - 1);
        kSmax = (int) BPOW((unsigned)   kD) - 1;
        kSmid = 0;
    }

    kPredictionMode = (int)GET_PCONST("PREDICTION_MODE");
    kP = (int32_t)GET_PCONST("P");
    kR = (int64_t)GET_PCONST("REGISTER_SIZE_PARAMETER");

    Omega = (uint8_t)GET_PCONST("WEIGHT_RESOLUTION");

    kOmegaMin = -(BPOW((UINT)(Omega + 2)));
    kOmegaMax = BPOW((UINT)(Omega + 2)) - 1;

    kLocalSumType = (int)GET_PCONST("LOCAL_SUM_TYPE");
    km_z = (int)GET_PCONST("ABSOLUTE_ERROR_LIMIT");
}

DIM kNx = (DIM)0;
DIM kNy = (DIM)0;
DIM kNz = (DIM)0;

HashTable predictor_constants;
HashTable encoder_constants;

int kUnsignedSamples = 0;
t_local_sum kLocalSumType = 0;

t_prediction_mode kPredictionMode = PM_FULL;

uint8_t kResolution = 0;

int32_t kD;
int kDa = 0;

int kSmin = 0;
int kSmid = 0;
int kSmax = 0;

int32_t kP = 0;
int64_t kR = 0;

int kVMax = 0;
int kVMin = 0;
int kTInc = 0;

uint8_t Omega = 0;
int kOmegaMin = 0;
int kOmegaMax = 0;

int km_z;