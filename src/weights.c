#include "predictor/weights.h"

int InitializeWeights(data_t **weight_ptr, INDEX z, INDEX y, INDEX x)
{
    InitVector(weight_ptr, C(z));
    data_t* weight_vector = *weight_ptr; // TODO Turn into #define for optimization?

#ifndef REDUCED_PREDICTION_MODE
    for(int i = 0; i < 3; i++){
        weight_vector[i] = 0;
    }

    weight_vector[3] = 7 * (data_t) BPOW(Omega - 3); // ! Source of Error

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

data_t DoubleResolutionPredictionError(image* hIMG, INDEX z, INDEX y, INDEX x){
    return 2 * ClippedQuantizerBinCenter(hIMG, z,y,x) - DoubleResolutionPredictedSample(hIMG, z,y,x);
}

data_t WeightUpdateScalingExponent(INDEX z, INDEX y, INDEX x){
    return CLIP(kVMin + (y * Nx + x - Nx) / kTInc, kVMin, kVMax) + D - Omega;
}

int UpdateWeights(image* hIMG, data_t* weights, INDEX z, INDEX y, INDEX x){
    if(x == 0 && x == 0){
        InitializeWeights(&global_cache->weights, z,y,x);
        return 0;
    }
    int ibweo = 0;
    for(int i = 0; i < 3; i++){
        weights[i] += (SIGN_P(DoubleResolutionPredictionError(hIMG, z,y,x)) * 
        BPOW(-1*(WeightUpdateScalingExponent(z,y,x) + ibweo) * DLD(hIMG, z,y,z, i)) + 1) / 2; // add 1/2 
    }

    for(int i = 3; i < C(z); i++){
        weights[i] += (SIGN_P(DoubleResolutionPredictionError(hIMG, z,y,x)) * 
        BPOW(-1*(WeightUpdateScalingExponent(z,y,x) + ibweo) * CentralLocalDifference(hIMG, z,y,z)) + 1); // add 1/2 
    }

    for(int i = 0; i < C(z); i++){
        weights[i] = CLIP(weights[i], kOmegaMin, kOmegaMax);
    }
    return 0;
}