#include "predictor/predictor.h"

error_t Predict(
    image *hIMG, 
    image *result, 
    INDEX z, 
    INDEX y, 
    INDEX x, 
    weight_t* weights
) {

    data_t raw_data = GetPixel(hIMG, x, y, z);
    uint16_t local_sum = L_FindLocalSum(hIMG, z, y, x);

    int64_t predicted_central_local_difference = 
        L_PredictedCentralLocalDifference(hIMG, z, y, x, weights);

    int64_t high_resolution_predicted_sample = 
        HighResolutionPredictedSample(
            predicted_central_local_difference, 
            local_sum
        );
    
    int32_t double_resolution_predicted_sample = 
        L_DoubleResolutionPredictedSample(
            hIMG, 
            z, 
            y, 
            x, 
            high_resolution_predicted_sample
        );

    uint16_t predicted_sample = 
        PredictedSample(double_resolution_predicted_sample);
    int32_t quantizer_index = 
        QuantizerIndex(raw_data, predicted_sample);

    uint16_t clipped_quantizer_bin_center = 
        ClippedQuantizerBinCenter(raw_data);
    int32_t double_resolution_predicted_error = 
        DoubleResolutionPredictionError(
            clipped_quantizer_bin_center,
            double_resolution_predicted_sample
        );

    data_t predicted_value = MappedQuantizerIndex(
        quantizer_index,
        predicted_sample,
        double_resolution_predicted_sample);

    SetPixel(result, x, y, z, predicted_value);

    L_UpdateWeights(hIMG, weights, z, y, x, double_resolution_predicted_error);

    if (DEBUG)
    {
        char write_buffer[1000];

        #ifdef ARM_COMPILE
        sprintf(write_buffer, "(%ld,%ld,%ld),%u, %d, %d, %lld, %ld, %lld, [",
                x, y, z,
                raw_data, predicted_sample, predicted_value,
                predicted_central_local_difference, 
                double_resolution_predicted_sample, 
                high_resolution_predicted_sample);
        #else 
        sprintf(write_buffer, "(%d,%d,%d),%u, %d, %d, %ld, %d, %ld, [",
                x, y, z,
                raw_data, predicted_sample, predicted_value,
                predicted_central_local_difference, 
                double_resolution_predicted_sample, 
                high_resolution_predicted_sample);
        #endif

        for (int i = 0; i < kC; i++)
        {
            #ifdef ARM_COMPILE
            sprintf(write_buffer + strlen(write_buffer), "%ld,", weights[i]);
            #else
            sprintf(write_buffer + strlen(write_buffer), "%d,", weights[i]);
            #endif
        }
        sprintf(write_buffer + strlen(write_buffer), "]\n");
        F_WRITE(write_buffer, sizeof(char), strlen(write_buffer), fp);
        
        return RES_OK;
    }

    return RES_OK;
}

int64_t
L_PredictedCentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, weight_t* weight_vector)
{
    int64_t pcld;
    if (x == 0 && y == 0)
    {
        return 0;
    }
    
    int32_t local_direction_vector[kC];

    L_LocalDirectionVector(hIMG, local_direction_vector, z, y, x);
    pcld = 0; //InnerProduct(weight_vector, local_direction_vector, kC);

    return pcld;
}

int L_UpdateWeights(image *hIMG, weight_t *weights, INDEX z, INDEX y, INDEX x, int32_t double_resolution_prediction_error)
{
    float scaling_exponent = -WeightUpdateScalingExponent(y, x, hIMG->size);
    float exp = exp2f(scaling_exponent) * SIGN_P(double_resolution_prediction_error);


    for (int i = 0; i < 3; i++)
    {
        float val = floor((exp * (float)L_DLD(hIMG, z, y, x, i) + 1) / 2);
        weights[i] += val;
    }

    for (int i = 3; i < kC; i++)
    {
        float val = floor((exp * (float)L_CentralLocalDifference(hIMG, z - i + 2, y, x) + 1) / 2);
        weights[i] += val;
    }

    for (int i = 0; i < kC; i++)
    {
        weights[i] = CLIP(weights[i], kOmegaMin, kOmegaMax);
    }
    return 0;
}

uint32_t L_FindLocalSum(image *hIMG, INDEX z, INDEX y, INDEX x)
{
    dim3 s = hIMG->size;
    uint32_t val = 0;

    switch (kLocalSumType)
    {
    case LS_WIDE_NEIGHBOR:
    {
        if (y > 0 && 0 < x && x < s.x - 1)
        {
            val = L_SR(hIMG, z, y, x - 1) + L_SR(hIMG, z, y - 1, x - 1) +
                  L_SR(hIMG, z, y - 1, x) + L_SR(hIMG, z, y - 1, x + 1);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * L_SR(hIMG, z, y, x - 1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (L_SR(hIMG, z, y - 1, x) + L_SR(hIMG, z, y - 1, x + 1));
        }
        else if (y > 0 && x == (INDEX)s.x - 1)
        {
            val = L_SR(hIMG, z, y, x - 1) + L_SR(hIMG, z, y - 1, x - 1) + 2 * L_SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x == 0)
        {
            val = 0;
        }
        break;
    }
    case LS_NARROW_NEIGHBOR:
    {
        if (y > 0 && 0 < x && x < s.x - 1)
        {
            val = L_SR(hIMG, z, y, x - 1) + L_SR(hIMG, z, y - 1, x - 1) +
                  L_SR(hIMG, z, y - 1, x) + L_SR(hIMG, z, y - 1, x + 1);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * L_SR(hIMG, z, y, x - 1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (L_SR(hIMG, z, y - 1, x) + L_SR(hIMG, z, y - 1, x + 1));
        }
        else if (y > 0 && x == s.x - 1)
        {
            val = L_SR(hIMG, z, y, x - 1) + L_SR(hIMG, z, y - 1, x - 1) + 2 * L_SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            val = 4 * kSmid;
        }
        break;
    }
    case LS_WIDE_COLUMN:
    {
        if (y > 0)
        {
            val = 4 * L_SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * L_SR(hIMG, z, y, x - 1);
        }
        break;
    }
    case LS_NARROW_COLUMN:
    {
        if (y > 0)
        {
            val = 4 * L_SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * L_SR(hIMG, z - 1, y, x - 1);
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            val = 4 * kSmid;
        }
        break;
    }
    default:
        break;
    }

    return val;
}

int32_t L_CentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x)
{
    return 4 * L_SR(hIMG, z, y, x) - L_FindLocalSum(hIMG, z, y, x);
}

uint32_t L_DoubleResolutionPredictedSample(image *hIMG, INDEX z, INDEX y, INDEX x, int64_t high_resolution_predicted_sample)
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

int32_t L_DirectionalLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, int direction)
{
    switch (direction)
    {
    case N:
        if (y > 0)
        {
            return 4 * L_SR(hIMG, z, y - 1, x) - L_LS(hIMG, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
        break;
    case W:
        if (x > 0 && y > 0)
        {
            return 4 * L_SR(hIMG, z, y, x - 1) - L_LS(hIMG, z, y, x);
        }
        else if (x == 0 && y > 0)
        {
            return 4 * L_SR(hIMG, z, y - 1, x) - L_LS(hIMG, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
    case NW:
        if (x > 0 && y > 0)
        {
            return 4 * L_SR(hIMG, z, y - 1, x - 1) - L_LS(hIMG, z, y, x);
        }
        else if (x == 0 && y > 0)
        {
            return 4 * L_SR(hIMG, z, y - 1, x) - L_LS(hIMG, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }

    default:
        break;
    }
    return 0;
}

int L_LocalDirectionVector(image *hIMG, int32_t *lDV, INDEX z, INDEX y, INDEX x)
{
    if (!kPredictionMode)
    {
        for (int i = N; i <= NW; i++)
        {
            lDV[i] = L_DLD(hIMG, z, y, x, i);
        }

        for (unsigned long int i = 0; i < Ps(z); i++)
        {
            lDV[i + 3] = L_CentralLocalDifference(hIMG, (signed int)(z - i - 1), y, x);
        }
    }
    else
    {

        for (int i = 0; i < kC; i++)
        {
            lDV[i] = L_CentralLocalDifference(hIMG, z - 1 - i, y, x);
        }
    }
    return RES_OK;
}