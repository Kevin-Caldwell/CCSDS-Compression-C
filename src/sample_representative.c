#include "predictor/sample_representative.h"
#include <stdio.h>

data_t offset[Nz];
data_t damping[Nz];

#define T_G_zero(x,y) (x > 0 || y > 0)
#define T_E_zero(x,y) (x == 0 && y == 0)


data_t SampleRepresentative(uint16_t sample_value){
#ifdef LOSSLESS
    return sample_value;
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

#ifndef LOSSLESS
uint32_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){
    return (4 * (BPOW(THETA) - damping[z]) * (ClippedQuantizerBinCenter(hIMG, z,y,x) * BPOW(Omega) - 
    SIGN(QuantizerIndex(hIMG, z,y,x)) * m_z * offset[z] * BPOW(Omega - THETA) + damping[z] * 
    HighResolutionPredictedSample(hIMG, z,y,x)) - damping[z,y,x] * BPOW(Omega + 1)) / (BPOW(Omega + THETA + 1));
}
#endif // LOSSLESS

/* // Simplified to ignore offset and damping
data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){

    return (ClippedQuantizerBinCenter(hIMG, z,y,x));
}  */

// Simplified to ignore offset and damping, Lossless?
/*data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x){

    return 2 * S(hIMG, z,y,x);
}*/


uint16_t PredictedSample(uint32_t double_resolution_predicted_sample){
    return double_resolution_predicted_sample / 2;
}

uint32_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x, int64_t high_resolution_predicted_sample){
    if(x > 0 || y > 0){ // ? Substitute for t>0
        if(x==0 && y==79 && z==28){
            printf("%ld, %d, %ld\n", high_resolution_predicted_sample, BPOW(Omega + 1), (high_resolution_predicted_sample / (int64_t) BPOW(Omega + 1)));
        }
        return (high_resolution_predicted_sample / (int64_t) BPOW(Omega + 1));
    } else if ((x == 0 && y == 0) && kP > 0 && z > 0) // ? Substitute for t == 0
    {
        return 2 * S(hIMG, z-1,y,x);
    } else if ((x == 0 && y == 0) && (kP == 0 || z == 0)) // ? Substitute for t == 0
    {
        return 2 * kSmid;
    }
    
    return 0;
}

int64_t HighResolutionPredictedSample(int32_t predicted_central_local_difference, uint32_t local_sum){
    // int64_t temp = CLIP(MOD((predicted_central_local_difference + BPOW(Omega) * (local_sum - 4 * kSmid)), kR) + BPOW(Omega + 2) * kSmid + BPOW(Omega + 1), 
    // BPOW(Omega + 2) * kSmin, BPOW(Omega+2) * kSmax + BPOW(Omega+1));
    int64_t temp1 = (int64_t)predicted_central_local_difference + BPOW(Omega) * ((int64_t) local_sum - (int64_t) (4 * kSmid));
    int64_t mod = (temp1 + (1L << (kR-1))) % (1L << (kR));
    mod = (mod < 0) ? (mod + (1L << (kR))) : mod;
    int64_t temp2 = mod - (1L << (kR - 1));//MOD(temp1, ((int64_t) kR));
    int64_t temp3 = temp2 + (uint64_t) BPOW(Omega + 2) * (uint64_t) kSmid + (uint64_t) BPOW(Omega + 1);
 


    int64_t hrps_max = BPOW(Omega+2) * (int64_t) kSmax + BPOW(Omega+1);
    int64_t hrps_min = BPOW(Omega + 2) * kSmin;

    if(predicted_central_local_difference == -4378040 && local_sum == 4)
        printf("%ld, %ld, %ld\n", temp1, (1L << (kR-1L)), ((temp1 + (1L << (kR-1))) % (1L << (kR))));

    int64_t temp = CLIP(temp3, hrps_min, hrps_max);
    // if(predicted_central_local_difference == -4378040 && local_sum == 4)
    //     printf("%ld, %ld, %ld, %ld, %ld, %ld, %ld,\n", temp1, temp2, temp3, hrps_max, hrps_min, kR, temp);
    return temp;
}