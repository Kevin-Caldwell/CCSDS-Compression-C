/**
 * sample_representative.h
 * @authors @Kevin-Caldwell @BrianShTsoi
 *
 * A collection of Sample representative calculation
 * functions.
 */

#ifndef SAMPLE_REPRESENTATIVE_H
#define SAMPLE_REPRESENTATIVE_H

#include "dst/image.h"
#include "constants/constants.h"
#include "cache/cache_predictor.h"
#include "math/linear_algebra.h"
#include "predictor/local_differences.h"
#include "predictor/quantizer.h"

#define SR(hIMG, Z, Y, X) GetPixel(hIMG, X, Y, Z)
// #define SAMPLE(z,y,x) (0) // TODO

extern data_t damping[];
extern data_t offset[];

data_t SampleRepresentative(uint16_t sample_value);

uint32_t DoubleResolutionPredictedSample(image *hIMG, INDEX z, INDEX y, INDEX x, int64_t high_resolution_predicted_sample);

uint16_t PredictedSample(uint32_t double_resolution_predicted_sample);

int64_t HighResolutionPredictedSample(int64_t predicted_central_local_difference, uint32_t local_sum);

#endif /* SAMPLE_REPRESENTATIVE_H */
