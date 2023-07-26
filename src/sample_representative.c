#include "predictor/sample_representative.h"

data_t offset[Nz];
data_t damping[Nz];

#define T_G_zero(x,y) (x > 0 || y > 0)
#define T_E_zero(x,y) (x == 0 && y == 0)


data_t SampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
    data_t val = CheckCache(z,y,x,sample_representatives);
    if(val != UINT16_MAX){
        return val;
    }
    
    if(T_E_zero(x,y)){
        val = S(hIMG,z,y,x);
    } else if (T_G_zero(x,y))
    {
        val = (DoubleResolutionSampleRepresentative(hIMG, z,y,x) + 1) / 2;
    }

    UpdateCache(z,y,x,sample_representatives, val);
    
    return val;
}


/* data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
    return (4 * (BPOW(THETA) - damping[z]) * (ClippedQuantizerBinCenter(hIMG, z,y,x) * BPOW(Omega) - 
    SIGN(QuantizerIndex(hIMG, z,y,x)) * m_z * offset[z] * BPOW(Omega - THETA) + damping[z] * 
    HighResolutionPredictedSample(hIMG, z,y,x)) - damping[z,y,x] * BPOW(Omega + 1)) / (BPOW(Omega + THETA + 1));
} */

/* // Simplified to ignore offset and damping
data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){

    return (ClippedQuantizerBinCenter(hIMG, z,y,x));
}  */

// Simplified to ignore offset and damping, Lossless?
data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){

    return 2 * S(hIMG, z,y,x);
}


data_t  PredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    data_t val = CheckCache(z,y,x, predicted_sample);
    if(val != UINT16_MAX){
        return val;
    }

    val = DoubleResolutionPredictedSample(hIMG, z,y,x) / 2;
    UpdateCache(z,y,x, predicted_sample, val);
    return val;
}

data_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    if(x > 0 || y > 0){ // ? Substitute for t>0
        return HighResolutionPredictedSample(hIMG, z,y,x) / (BPOW(Omega + 1));
    } else if ((x == 0 && y == 0) && P > 0 && z > 0) // ? Substitute for t == 0
    {
        return 2 * SAMPLE(z-1,y,x);
    } else if ((x == 0 && y == 0) && (P == 0 || z == 0)) // ? Substitute for t == 0
    {
        return Smid;
    }
    UpdateWeights(hIMG, global_cache->weights, z,y,x);
    
    return 0;
}

data_t HighResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    data_t d_hat = PredictedCentralLocalDifference(hIMG, z,y,x);
    data_t temp = CLIP(MOD(R, (d_hat + BPOW(Omega) * (LS(hIMG, z,y,x) - 4 * Smid))) + BPOW(Omega + 2) * Smid + BPOW(Omega + 1), 
    BPOW(Omega + 2) * kSmin, BPOW(Omega+2) * Smax + BPOW(Omega+1));
    return 0;
}