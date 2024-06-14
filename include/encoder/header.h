#ifndef HEADER_H
#define HEADER_H

/**
 * header.h
 * @author @Kevin-Caldwell
 *
 * File Contains Functions for Preparing
 * Image, Predictor, Encoder and Entropy
 * coder Header Sections of the
 * Compressed Image.
 */

#include <inttypes.h>

#include "constants/constants.h"
#include "constants/encoder_constants.h"
#include "encoder/encoder_helper_functions.h"

void PrepareImageMetadata(uint8_t *essential, dim3 image_size);

void PreparePredictorMetadata(uint8_t *predicted_metadata);

void PrepareSampleAdaptiveEntropyCoder(uint8_t *entropy_coder_metadata);
#endif /* HEADER_H */
