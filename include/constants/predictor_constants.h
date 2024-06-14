#ifndef PREDICTOR_CONSTANTS_H
#define PREDICTOR_CONSTANTS_H

#include "constants/typedefs.h"
#include "constants/constants.h"


/** \brief Specifies Lossless Compression. Faster than setting Resolution */
BOOL kLosslessCompression;

typedef struct{
    /** \brief 
     * 
     */
    BOOL kLosslessCompression;
    t_prediction_mode kPredictionMode;
    t_local_sum kLocalSumType;
    uint8_t kDynamicRange;
    uint8_t kResolution;
    BOOL kWeightInitialization;
    BOOL kWeightExponentOffsetFlag;
    int32_t kD;
    int kUnsignedSamples;

    int kSmin;
    int kSmax;
    int kSmid;
    
    /** \brief The number of prediction bands */
    int32_t kPredictionBands;

    /** \brief  */
    uint8_t kWeightComponentResolution;

    /** \brief Register Size */
    int64_t kR;

    /** \brief  */
    int kOmegaMin;
    int kOmegaMax;
    
    int kDa;
    int kMz;
    int kC;

    int kVMin;
    int kVMax;
    int kTInc;

} s_predictor_constants, S_kPred;

#endif /* PREDICTOR_CONSTANTS_H */
