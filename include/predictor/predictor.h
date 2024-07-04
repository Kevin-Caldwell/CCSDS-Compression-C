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

#include "predictor/weights.h"
#include "predictor/quantizer.h"

extern file_t* fp;
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
