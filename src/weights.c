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

    weight_vector[3] = 7 * (int32_t)BPOW(Omega) / 8; // ! Source of Error

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

    int ibweo = 0;
    int32_t scale_exp = (-1 * (WeightUpdateScalingExponent(y, x)));
    int32_t fac = SIGN_P(double_resolution_prediction_error);
    for (int i = 0; i < 3; i++)
    {

        int32_t val = fac * (int32_t)DLD(hIMG, z, y, x, i);
        int32_t temp = scale_exp < 0 ? abs(val) >> abs(scale_exp) : abs(val) << abs(scale_exp);
        val = (SIGN_P(val) * (temp)) + 1;
        int32_t half_int = val / 2;

        if (val < 0)
        {
            if (half_int * 2 - val)
            {
                half_int--;
            }
        }
        weights[i] += half_int;
    }

    for (int i = 3; i < C(z); i++)
    {
        int32_t val = fac * (int32_t)CentralLocalDifference(hIMG, z-i+2, y, x);
        int32_t temp = scale_exp < 0 ? abs(val) >> abs(scale_exp) : abs(val) << abs(scale_exp);
        val = (SIGN_P(val) * (temp)) + 1;
        int32_t half_int = val / 2;

        if (val < 0)
        {
            if (half_int * 2 - val)
            {
                half_int--;
            }
        }
        weights[i] += half_int;
        // int32_t val = fac * CentralLocalDifference(hIMG, z, y, x) + 1;

        // weights[i] += (val) / 2;
    }

    for (int i = 0; i < C(z); i++)
    {
        weights[i] = CLIP(weights[i], kOmegaMin, kOmegaMax);
    }

    if (x == 70 && y == 0 && z == 29)
    {
        printf("exp:%d,fac:%d\n", scale_exp, fac);
    }
    return 0;
}