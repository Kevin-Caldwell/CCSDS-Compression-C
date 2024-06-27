#include "predictor/weights.h"
#include <math.h>

int InitializeWeights(weight_t *weight_ptr, INDEX z)
{
    weight_t *weight_vector = weight_ptr; // TODO Turn into #define for optimization?

    if (!kPredictionMode)
    {
        for (int i = 0; i < 3; i++)
        {
            weight_vector[i] = 0;
        }

        weight_vector[3] = 7 * (int32_t)BPOW(Omega) / 8; // ! Source of Error

        for (INDEX i = 4; i < kC; i++)
        {
            weight_vector[i] = weight_vector[i - 1] >> 3; // ! Watch out for Indexing Issues
        }
    }
    else
    {
        weight_vector[0] = 7 * BPOW(Omega - 3);
        for (INDEX i = 1; i < kC; i++)
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

int32_t WeightUpdateScalingExponent(INDEX y, INDEX x, dim3 img_dim)
{
    int32_t res = CLIP((int32_t)kVMin +
                           ((int32_t)y * img_dim.x + (int32_t)x - img_dim.x) / (int32_t)kTInc,
                       (int32_t)kVMin, (int32_t)kVMax) +
                  (int32_t)kD - (int32_t)Omega;
    return res;
}

int UpdateWeights(LBuf *buf, dim3 s, weight_t *weights, INDEX z, INDEX y, INDEX x, int32_t double_resolution_prediction_error)
{
    float scaling_exponent = -WeightUpdateScalingExponent(y, x, s);
    float exp = exp2f(scaling_exponent) * SIGN_P(double_resolution_prediction_error);


    for (int i = 0; i < 3; i++)
    {
        float val = floor((exp * (float)DLD(buf, s, 0, 0, 0, i) + 1) / 2);
        weights[i] += val;
    }

    for (int i = 3; i < kC; i++)
    {
        float val = floor((exp * (float)CentralLocalDifference(buf, s, - i + 2, 0, 0) + 1) / 2);
        weights[i] += val;
    }

    for (int i = 0; i < kC; i++)
    {
        weights[i] = CLIP(weights[i], kOmegaMin, kOmegaMax);
    }
    return 0;
}

int64_t
PredictedCentralLocalDifference(LBuf *buf, dim3 s, INDEX z, INDEX y, INDEX x, weight_t* weight_vector)
{
    int64_t pcld;
    if (x == 0 && y == 0)
    {
        return 0;
    }
    
    int32_t local_direction_vector[kC];

    LocalDirectionVector(buf, s, local_direction_vector, z, y, x);
    pcld = InnerProduct(weight_vector, local_direction_vector, kC);

    return pcld;
}
