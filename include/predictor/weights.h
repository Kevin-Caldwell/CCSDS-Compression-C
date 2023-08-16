#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "constants/constants.h"
#include "dst/image.h"
#include "math/linear_algebra.h"
#include "predictor/quantizer.h"
#include <stdio.h>

#define Ps(z) MIN(z, kP)

#ifdef REDUCED_PREDICTION_MODE
#define C(z) (unsigned int) Ps(z)
#else
#define C(z) (unsigned int) Ps(z) + 3
#endif

int InitializeWeights(int32_t **weight_ptr, INDEX z, INDEX y, INDEX x);

int32_t DoubleResolutionPredictionError(int16_t clipped_quantizer_bin_center, 
                                            int32_t double_resolution_predicted_sample);

int32_t WeightUpdateScalingExponent(INDEX y, INDEX x);

int UpdateWeights(image *hIMG, 
            int32_t *weights, 
            INDEX z, INDEX y, INDEX x, 
            int32_t double_resolution_prediction_error);


#endif /* WEIGHTS_H */
