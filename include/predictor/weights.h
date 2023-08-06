#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "constants/constants.h"
#include "dst/image.h"
#include "math/linear_algebra.h"
#include "predictor/quantizer.h"

#define Ps(z) MIN(z, kP)

#ifdef REDUCED_PREDICTION_MODE
#define C(z) (unsigned int) Ps(z)
#else
#define C(z) (unsigned int) Ps(z) + 3
#endif

int InitializeWeights(data_t** weights, INDEX z, INDEX y, INDEX x);

data_t DoubleResolutionPredictionError(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t WeightUpdateScalingExponent(INDEX z, INDEX y, INDEX x);

int UpdateWeights(image* hIMG, data_t* weights, INDEX z, INDEX y, INDEX x);


#endif /* WEIGHTS_H */
