/**
 * @file predictor.h
 * @brief Functions for the Predictor System
 * @details
 * Top Level Function(s) for Running Predictor
 * on a Hyperspectral Image. Returns a predicted
 * Hyperspectral Image.
 *
 */

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dst/image.h"

#include "constants/global_constants.h"
#include "constants/constants.h"
#include "constants/predictor_constants.h"

#include "math/math_functions.h"
#include "math/linear_algebra.h"

#include "dst/locale_buffer.h"

#include "predictor/weights.h"
#include "predictor/quantizer.h"


#include "files/logs.h"

/** 
 * @brief Redundant Definition from math_functions.h
 * @todo remove this
 */
#define Ps(z) MIN(z, kP)

/** 
 * @brief Finds the kC constant, updated every pass.
 * @todo Remove or Integrate with PredictorConstants Structure.
 */
extern int kC;

/**
 * @brief Run Predictor on hIMG
 * @param hIMG Hyperspectral Image to run prediction
 * @param result Store Prediction Result
 */
int RunPredictor(image *hIMG, image *result);

#endif /* PREDICTOR_H */
