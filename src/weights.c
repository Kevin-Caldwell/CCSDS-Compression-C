#include "predictor/weights.h"
#include <math.h>

int InitializeWeights(int32_t **weight_ptr, INDEX z, INDEX y, INDEX x)
{
    InitVector(weight_ptr, C);
    int32_t *weight_vector = *weight_ptr; // TODO Turn into #define for optimization?

    if (!kPredictionMode)
    {
        for (int i = 0; i < 3; i++)
        {
            weight_vector[i] = 0;
        }

        weight_vector[3] = 7 * (int32_t)BPOW(Omega) / 8; // ! Source of Error

        for (INDEX i = 4; i < C; i++)
        {
            weight_vector[i] = weight_vector[i - 1] >> 3; // ! Watch out for Indexing Issues
        }
    }
    else
    {
        weight_vector[0] = 7 * BPOW(Omega - 3);
        for (INDEX i = 1; i < C; i++)
        {
            weight_vector[i] = weight_vector[i - 1] >> 3;
        }
    }

    return RES_OK;
}

int32_t DoubleResolutionPredictionError(int16_t clipped_quantizer_bin_center,
                                        int32_t double_resolution_predicted_sample)
{
    return 2 * (int32_t)clipped_quantizer_bin_center - (int32_t)double_resolution_predicted_sample;
}

int32_t WeightUpdateScalingExponent(INDEX y, INDEX x)
{
    int32_t res = CLIP((int32_t)kVMin +
                           ((int32_t)y * Nx + (int32_t)x - Nx) / (int32_t)kTInc,
                       (int32_t)kVMin, (int32_t)kVMax) +
                  (int32_t)D - (int32_t)Omega;
    return res;
}

int UpdateWeights(image *hIMG, int32_t *weights, INDEX z, INDEX y, INDEX x, int32_t double_resolution_prediction_error)
{
    float scaling_exponent = -WeightUpdateScalingExponent(y, x);
    float exp = exp2f(scaling_exponent) * SIGN_P(double_resolution_prediction_error);

    for (int i = 0; i < 3; i++)
    {
        float val = floor((exp * (float)DLD(hIMG, z, y, x, i) + 1) / 2);
        weights[i] += val;
    }

    for (int i = 3; i < C; i++)
    {
        float val = floor((exp * (float)CentralLocalDifference(hIMG, z - i + 2, y, x) + 1) / 2);
        weights[i] += val;
    }

    for (int i = 0; i < C; i++)
    {
        weights[i] = CLIP(weights[i], kOmegaMin, kOmegaMax);
    }
    return 0;
}