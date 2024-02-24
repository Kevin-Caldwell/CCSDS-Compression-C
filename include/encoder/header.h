#ifndef HEADER_H
#define HEADER_H

#include <inttypes.h>

#include "constants/constants.h"
#include "constants/encoder_constants.h"
#include "encoder/encoder_helper_functions.h"

void PrepareImageMetadata(uint8_t* essential);

void PreparePredictorMetadata(uint8_t* predicted_metadata);

void PrepareSampleAdaptiveEntropyCoder(uint8_t* entropy_coder_metadata);
#endif /* HEADER_H */
