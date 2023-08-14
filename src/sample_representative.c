#include "predictor/sample_representative.h"
#include <stdio.h>

data_t offset[Nz];
data_t damping[Nz];

#define T_G_zero(x,y) (x > 0 || y > 0)
#define T_E_zero(x,y) (x == 0 && y == 0)


data_t SampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
#ifdef LOSSLESS
    return S(hIMG, z,y,x);
#else
    data_t val;
    
    if(T_E_zero(x,y)){
        val = S(hIMG,z,y,x);
    } else if (x > 0 || y > 0)
    {
        val = (DoubleResolutionSampleRepresentative(hIMG, z,y,x) + 1) / 2;
    }
    
    return val;
#endif
}


uint32_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
    return (4 * (BPOW(THETA) - damping[z]) * (ClippedQuantizerBinCenter(hIMG, z,y,x) * BPOW(Omega) - 
    SIGN(QuantizerIndex(hIMG, z,y,x)) * m_z * offset[z] * BPOW(Omega - THETA) + damping[z] * 
    HighResolutionPredictedSample(hIMG, z,y,x)) - damping[z,y,x] * BPOW(Omega + 1)) / (BPOW(Omega + THETA + 1));
}

/* // Simplified to ignore offset and damping
data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){

    return (ClippedQuantizerBinCenter(hIMG, z,y,x));
}  */

// Simplified to ignore offset and damping, Lossless?
/*data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){

    return 2 * S(hIMG, z,y,x);
}*/


uint16_t PredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    return DoubleResolutionPredictedSample(hIMG, z,y,x) / 2;
}

uint32_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    if(x > 0 || y > 0){ // ? Substitute for t>0
        uint64_t hrps = HighResolutionPredictedSample(hIMG, z,y,x) / (BPOW(Omega + 1));
        return hrps;
    } else if ((x == 0 && y == 0) && kP > 0 && z > 0) // ? Substitute for t == 0
    {
        return 2 * S(hIMG, z-1,y,x);
    } else if ((x == 0 && y == 0) && (kP == 0 || z == 0)) // ? Substitute for t == 0
    {
        return 2 * kSmid;
    }
    
    return 0;
}

uint64_t HighResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x){
    uint32_t d_hat = PredictedCentralLocalDifference(hIMG, z,y,x);
    uint64_t temp = CLIP(MOD((d_hat + BPOW(Omega) * (LS(hIMG, z,y,x) - 4 * kSmid)), kR) + BPOW(Omega + 2) * kSmid + BPOW(Omega + 1), 
    BPOW(Omega + 2) * kSmin, BPOW(Omega+2) * kSmax + BPOW(Omega+1));
    return temp;
}