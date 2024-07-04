/** 
 * \file predictor_constants.h
 * @brief 
 * Contains the Struct and relevant functions for 
 * Creating and Accessing Predictor Constants.
 * \todo Comments
 * \todo Initialization Function
 */
#ifndef PREDICTOR_CONSTANTS_H
#define PREDICTOR_CONSTANTS_H

#include "constants/typedefs.h"

/** @brief Structure containing all Predictor Constants */
typedef struct{
    /**
     * @brief 
     * Choose between lossy and lossless compression.
     * @details 
     * 0: Lossy
     * 1: Lossless
     * User Defined Constant
     * \note Lossy Compression not fully supported yet
     * \todo Implement use case
     */
    BOOL kLosslessCompression;

    /**
     * @brief 
     * Select Prediction Mode
     * @details
     * User Defined Constant
     */
    t_prediction_mode kPredictionMode;

    /**
     * @brief
     * Determines the type of local sum used. Affects the compression
     * ratio and execution time.
     * @details
     * User Defined Constant
     */
    t_local_sum kLocalSumType;

    /**
     * @brief 
     * Number of Bits used to represent weight values.
     * Must be between 4 and 19 inclusive.
     * @details 
     * User Defined Constant
     * Range: [4, 19]
     */
    uint8_t kWeightResolution;

    /**
     * @brief Selects the Weight Initialization Method
     * 0: Default Weight Initialization
     * 1: Custom Weight Initialization
     * @todo Implement in Predictor
     * @details
     * User Defined Constant
     */
    BOOL kWeightInitialization;

    /**
     * @brief Selects the Weight Exponent Offset Flag
     * 0: WEO values are zero
     * 1: WEO values can be non-zero
     * @todo Implement in Predictor
     * 
     */
    BOOL kWeightExponentOffsetFlag;

    int kUnsignedSamples;

    /** 
     * @brief Lower Sample Value Limit
     * @details
     * If samples are unsigned, 
     * @code kSmin = 0 @endcode
     * If samples are signed, 
     * @code kSmin = -2^(D-1) @endcode
     * 
     * Calculated Constant.
     */
    int kSmin;

    /**
     * @brief Middle Sample Value
     * @details 
     * If samples are unsigned, 
     * @code kSmid = 2^(D-1) @endcode
     * If samples are signed, 
     * @code kSmid = 0 @endcode
     * 
     * Calculated Constant
     */
    int kSmax;

    /**
     * @brief Maximum Sample Value
     * @details 
     * If samples are unsigned, 
     * @code kSmax = 2^(D)-1 @endcode
     * If samples are signed, 
     * @code kSmax = 2^(D-1)-1 @endcode
     * 
     * Calculated Constant
     */
    int kSmid;
    
    /** 
     * @brief The number of prediction bands 
     * @details
     * Range: [0,15]
     * 
     * User Specified Constant.
     */
    int32_t kP;

    /**
     * @brief Prediction Bands for a Spectral Band z
     * @details
     * Pz* = min{z, P}
     * 
     * Calculated Constant.
     */
    int32_t kPz;

    /**
     * @brief Number of Local Difference Values used for prediction
     * @details
     * In Reduced Prediction Mode, 
     * Cz = Pz
     * 
     * 
     * Calculated Constant.
     */
    int32_t kCz;

    /** @brief  */
    uint8_t kWeightComponentResolution;

    /** @brief Register Size */
    int64_t kR;

    /** @brief Minimum value possible for Weight Components */
    int kOmegaMin;
    /** @brief Maximum value possible for Weight Components */
    int kOmegaMax;
    
    /** @brief Absolute Error Limit Bit Depth */
    int kAbsoluteErrorLimitBitDepth;
    int kMaximumErrorValue;
    int kC;

    int kVMin;
    int kVMax;
    int kTInc;

} s_predictor_constants, S_kPred;

error_t InitializePredictorConstants(S_kPred* kPred, char* file_name);

#endif /* PREDICTOR_CONSTANTS_H */
