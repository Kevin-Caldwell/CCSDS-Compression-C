#include "predictor/sample_representative.h"

data_t SampleRepresentative(uint16_t sample_value)
{
    return sample_value;
}

uint16_t PredictedSample(uint32_t double_resolution_predicted_sample)
{
    return double_resolution_predicted_sample / 2;
}

uint32_t DoubleResolutionPredictedSample(image *hIMG, INDEX z, INDEX y, INDEX x, int64_t high_resolution_predicted_sample)
{
    if (x > 0 || y > 0)
    { // ? Substitute for t>0
        return (high_resolution_predicted_sample / (int64_t)BPOW(Omega + 1));
    }
    else if ((x == 0 && y == 0) && kP > 0 && z > 0) // ? Substitute for t == 0
    {
        return 2 * S(hIMG, z - 1, y, x);
    }
    else if ((x == 0 && y == 0) && (kP == 0 || z == 0)) // ? Substitute for t == 0
    {
        return 2 * kSmid;
    }

    return 0;
}

int64_t HighResolutionPredictedSample(int64_t predicted_central_local_difference, uint32_t local_sum)
{
    int64_t temp1 = (int64_t)predicted_central_local_difference + (int64_t)BPOW(Omega) * ((int64_t)local_sum - (int64_t)(4 * kSmid));
    int64_t mod = (temp1 + (1L << (kR - 1))) % (1L << (kR));
    mod = (mod < 0) ? (mod + (1L << (kR))) : mod;
    int64_t temp2 = mod - (1L << (kR - 1)); // MOD(temp1, ((int64_t) kR));
    int64_t temp3 = temp2 + (int64_t)BPOW(Omega + 2) * (int64_t)kSmid + (int64_t)BPOW(Omega + 1);

    int64_t hrps_max = BPOW(Omega + 2) * (int64_t)kSmax + BPOW(Omega + 1);
    int64_t hrps_min = BPOW(Omega + 2) * kSmin;

    int64_t temp = CLIP(temp3, hrps_min, hrps_max);
    return temp;
}