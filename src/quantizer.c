#include "predictor/quantizer.h"

uint16_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x){
    return  CLIP(PredictedSample(hIMG, z,y,x) + QuantizerIndex(hIMG, z,y,x) * (2 * m_z + 1), kSmin, kSmax);
}

int16_t PredictionResidual(image* hIMG, INDEX z, INDEX y, INDEX x){
    return S(hIMG, z,y,x) - PredictedSample(hIMG, z,y,x);
}

SignedLongData QuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x){
#ifdef LOSSLESS
    return PredictionResidual(hIMG, z,y,x);

#else
    SignedLongData qInd;
    uint16_t pred_res = PredictionResidual(hIMG, z,y,x);
    if(x == 0 && y == 0){
        qInd = pred_res;
    }
    else{
        qInd = SIGN(pred_res) * (abs(pred_res) + m_z) / (2 * m_z + 1);
    }
    return qInd;
#endif
}


uint16_t minTheta(image* hIMG, INDEX z, INDEX y, INDEX x){
    uint16_t pred_res = PredictedSample(hIMG, z,y,x);

#ifndef LOSSLESS
    if(x == 0 && y == 0){
        return MIN(pred_res - kSmin, kSmax - pred_res);
    } else if (x > 0 || y > 0)
    {
        return  MIN((pred_res - kSmin + m_z)/(2 * m_z + 1), 
                (kSmax - pred_res + m_z)/(2 * m_z + 1));
    }
#else
    return MIN(pred_res - kSmin, kSmax - pred_res);
#endif
    
}


data_t MappedQuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x){
    SignedLongData qz = QuantizerIndex(hIMG, z,y,x);
    SignedLongData theta = minTheta(hIMG, z,y,x);
    SignedLongData a = qz * (DoubleResolutionPredictedSample(hIMG, z,y,x) % 2 ? -1 : 1);

    if(abs(qz) > theta){
        return abs(qz) + theta;
    } else if (0 <= a && a >= theta)
    {
        return 2 * abs(qz);
    } else{
        return 2 * abs(qz) - 1;
    }
    
}