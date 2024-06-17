/** 
 * \file predictor_constants.h
 * \brief 
 * Contains the Struct and relevant functions for 
 * Creating and Accessing Predictor Constants.
 * \todo Comments
 * \todo Initialization Function
 */
#ifndef PREDICTOR_CONSTANTS_H
#define PREDICTOR_CONSTANTS_H

#include "constants/typedefs.h"

/** Structure containing all Predictor Constants */
typedef struct{
    /**
     * \brief 
     * Choose between lossy and lossless compression 
     * 0: Lossy
     * 1: Lossless
     * \note Lossy Compression not fully supported yet
     * \todo Implement use case
     */
    BOOL kLosslessCompression;

    /**
     * \brief 
     * Select Prediction Mode
     */
    t_prediction_mode kPredictionMode;

    /**
     * \brief
     * Determines the type of local sum used. Affects the compression
     * ratio and execution time.
     */
    t_local_sum kLocalSumType;

    /** 
     * \brief
     * Number of bits needed to represent values in the image.
     */
    uint8_t kDynamicRange;

    /**
     * \brief 
     * Number of Bits used to represent weight values.
     * Must be between 4 and 19 inclusive.
     */
    uint8_t kWeightResolution;

    /**
     * \brief Selects the Weight Initialization Method
     * 0: Default Weight Initialization
     * 1: Custom Weight Initialization
     * \todo Implement in Predictor
     */
    BOOL kWeightInitialization;

    /**
     * \brief Selects the Weight Exponent Offset Flag
     * 0: WEO values are zero
     * 1: WEO values can be non-zero
     * \todo Implement in Predictor
     */
    BOOL kWeightExponentOffsetFlag;

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

    /** \brief Minimum value possible for Weight Components */
    int kOmegaMin;
    /** \brief Maximum value possible for Weight Components */
    int kOmegaMax;
    
    /** \brief Absolute Error Limit Bit Depth */
    int kAbsoluteErrorLimitBitDepth;
    int kMaximumErrorValue;
    int kC;

    int kVMin;
    int kVMax;
    int kTInc;

} s_predictor_constants, S_kPred;

#endif /* PREDICTOR_CONSTANTS_H */
