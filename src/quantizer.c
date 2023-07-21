#include "predictor/quantizer.h"

// ? Completed
data_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x){
    return CLIP(PredictedSample(hIMG, z,y,x) + QuantizerIndex(hIMG, z,y,x) * (2 * m_z + 1), kSmin, Smax);
}

// ? Completed
data_t PredictionResidual(image* hIMG, INDEX z, INDEX y, INDEX x){
    return S(hIMG, z,y,x) - PredictedSample(hIMG, z,y,x);
}

// ? Completed
data_t QuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x){
    if(x == 0 && y == 0){
        return PredictionResidual(hIMG, z,y,x);
    }
    else{
        data_t pred_res = PredictionResidual(hIMG, z,y,x);
        return SIGN(pred_res) * (abs(pred_res) + m_z) / (2 * m_z + 1);
    }

}

// ? Completed
data_t minTheta(image* hIMG, INDEX z, INDEX y, INDEX x){
    if(x == 0 && y == 0){
        return MIN(PredictedSample(hIMG, z,y,x) - kSmin, Smax - PredictedSample(hIMG, z,y,x));
    } else if (x > 0 && y > 0)
    {
        return  MIN((PredictedSample(hIMG, z,y,x) - kSmin + m_z)/(2 * m_z + 1), 
                (Smax - PredictedSample(hIMG, z,y,x) + m_z)/(2 * m_z + 1));
    }
    
}

// ? Completed
data_t MappedQuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x){
    data_t qz = QuantizerIndex(hIMG, z,y,x);
    data_t theta = minTheta(hIMG, z,y,x);
    data_t a = qz * (DoubleResolutionPredictedSample(hIMG, z,y,x) % 2 ? -1 : 1);

    if(abs(qz) > theta){
        return abs(qz) + theta;
    } else if (0 <= a && a >= theta)
    {
        return 2 * abs(qz);
    } else{
        return 2 * abs(qz) - 1;
    }
    
}