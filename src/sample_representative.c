#include "predictor/sample_representative.h"

#define T_G_zero(x,y) (x > 0 && y > 0)
#define T_E_zero(x,y) (x == 0 && y == 0)

// ? Completed
data_t SampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
    if(T_E_zero(x,y)){
        return S(hIMG,z,y,x);
    } else if (T_G_zero(x,y))
    {
        return (DoubleResolutionSampleRepresentative(hIMG, z,y,x) + 1) / 2;
    }
    
    return 0;
}

// ? Completed
data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
    return (4 * (BPOW(THETA) - damping[z]) * (ClippedQuantizerBinCenter(hIMG, z,y,x) * BPOW(Omega) - 
    SIGN(QuantizerIndex(hIMG, z,y,x)) * m_z * offset[z] * BPOW(Omega - THETA) + damping[z] * 
    HighResolutionPredictedSample(hIMG, z,y,x)) - damping[z,y,x] * BPOW(Omega + 1)) / (BPOW(Omega + THETA + 1));
}

// ? Completed
data_t  PredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    return DoubleResolutionPredictedSample(hIMG, z,y,x) / 2;
}

// ? Completed
data_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    if(x > 0 && y > 0){ // ? Substitute for t>0
        return HighResolutionPredictedSample(hIMG, z,y,x) / (BPOW(Omega + 1));
    } else if ((x == 0 && y == 0) && P > 0 && z > 0) // ? Substitute for t == 0
    {
        return 2 * SAMPLE(z-1,y,x);
    } else if ((x == 0 && y == 0) && (P == 0 || z == 0)) // ? Substitute for t == 0
    {
        return Smid;
    }
    
    
    return 0;
}

// ? Completed
data_t HighResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    data_t d_hat = PredictedCentralLocalDifference(hIMG, z,y,x);
    data_t temp = CLIP(MOD(R, (d_hat + BPOW(Omega) * (LS(hIMG, z,y,x) - 4 * Smid))) + BPOW(Omega + 2) * Smid + BPOW(Omega + 1), 
    BPOW(Omega + 2) * kSmin, BPOW(Omega+2 * Smax + BPOW(Omega+1)));
    return 0;
}