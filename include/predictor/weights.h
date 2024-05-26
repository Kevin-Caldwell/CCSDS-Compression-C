/**
 * weights.h
 * @author @Kevin-Caldwell
 *
 * Functions for Initializing, Calculating
 * and Updating Weights for Predictor and
 * Reconstructor.
 */

#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "constants/constants.h"
#include "dst/image.h"
#include "math/linear_algebra.h"
#include "predictor/quantizer.h"
#include "predictor/local_differences.h"


#define Ps(z) MIN(z, kP)

typedef uint32_t weight_t;

int InitializeWeights(weight_t *weight_ptr, INDEX z);

int32_t DoubleResolutionPredictionError(int16_t clipped_quantizer_bin_center,
                                        int32_t double_resolution_predicted_sample);

int32_t WeightUpdateScalingExponent(INDEX y, INDEX x);

int UpdateWeights(image *hIMG,
                  weight_t *weights,
                  INDEX z, INDEX y, INDEX x,
                  int32_t double_resolution_prediction_error);

int64_t PredictedCentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, weight_t* weights);

#endif /* WEIGHTS_H */
