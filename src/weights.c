#include "predictor/weights.h"

int InitializeWeights(int32_t **weight_ptr, INDEX z, INDEX y, INDEX x)
{
    InitVector(weight_ptr, C(z));
    int32_t *weight_vector = *weight_ptr; // TODO Turn into #define for optimization?

#ifndef REDUCED_PREDICTION_MODE
    for (int i = 0; i < 3; i++)
    {
        weight_vector[i] = 0;
    }

    weight_vector[3] = 7 * (data_t)BPOW(Omega - 3); // ! Source of Error

    for (INDEX i = 4; i < C(z); i++)
    {
        weight_vector[i] = weight_vector[i - 1] >> 3; // ! Watch out for Indexing Issues
    }
#else
    weight_vector[0] = 7 * BPOW(Omega - 3);
    for (INDEX i = 1; i < C(z); i++)
    {
        weight_vector[i] = weight_vector[i - 1] >> 3;
    }
#endif

    return 0;
}

int32_t DoubleResolutionPredictionError(uint16_t clipped_quantizer_bin_center, 
                                            uint32_t double_resolution_predicted_sample)
{
    return 2 * (signed) clipped_quantizer_bin_center - (signed) double_resolution_predicted_sample;
}

int32_t WeightUpdateScalingExponent(INDEX y, INDEX x)
{
    return CLIP(kVMin + (y * Nx + x - Nx) / kTInc, kVMin, kVMax) + D - Omega;
}

int UpdateWeights(image *hIMG, int32_t *weights, INDEX z, INDEX y, INDEX x, int32_t double_resolution_prediction_error)
{
    if (x == 0 && y == 0)
    {
        free(global_cache->weights);
        InitializeWeights(&global_cache->weights, z, y, x);
        return 0;
    }
    int ibweo = 0;
    int32_t scale_exp = BPOW(-1 * (WeightUpdateScalingExponent(y, x) + ibweo));
    int32_t fac = SIGN_P(double_resolution_prediction_error) * scale_exp;
    for (int i = 0; i < 3; i++)
    {
        weights[i] += (fac * DLD(hIMG, z, y, x, i) + 1) / 2;
    }

    for (int i = 3; i < C(z); i++)
    {
        weights[i] += (fac * CentralLocalDifference(hIMG, z, y, x) + 1) / 2;
    }

    for (int i = 0; i < C(z); i++)
    {
        weights[i] = CLIP(weights[i], kOmegaMin, kOmegaMax);
    }
    return 0;
}