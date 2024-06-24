/**
 * @file weights.h
 *
 * @brief Functions for Initializing, Calculating
 * and Updating Weights for Predictor and
 * Reconstructor.
 */

#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "predictor/local_differences.h"

/** @brief Redefinition of Ps @todo Remove Redundant defintions */
#define Ps(z) MIN(z, kP)

/** @brief Initialize Weights using Default Initialization */
int InitializeWeights(weight_t *weight_ptr, INDEX z);

/** 
 * @brief Double Resolution Prediction Error Calculation
 * @details
 * See Standard for Details.
 */
int32_t DoubleResolutionPredictionError(int16_t clipped_quantizer_bin_center,
                                        int32_t double_resolution_predicted_sample);

/** 
 * @brief Weight Update Scaling Exponent Calculation
 * @details 
 * See Standard for Details.
 */
int32_t WeightUpdateScalingExponent(INDEX y, INDEX x, dim3 img_dim);

/**
 * @brief Update Weights Calculations
 * @details 
 * See Standard for Details.
 * @warning Direct Image Access
 */
int UpdateWeights(image *hIMG,
                  weight_t *weights,
                  INDEX z, INDEX y, INDEX x,
                  int32_t double_resolution_prediction_error);

/** 
 * @brief Predicted Central Local Difference Calculation
 * @details 
 * See Standard for Details.
 * @warning Direct Image Access
 */
int64_t PredictedCentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, weight_t* weights);

#endif /* WEIGHTS_H */
