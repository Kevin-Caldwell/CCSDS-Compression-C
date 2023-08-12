#ifndef QUANTIZER_H
#define QUANTIZER_H

#include "cache/image_instance.h"
#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "predictor/sample_representative.h"
#include "dst/data_types.h"

// ! DO NOT USE
// Replaced by m_z 
int QuantizerFidelityControl(INDEX z, INDEX y, INDEX x);

SignedLongData QuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t MappedQuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x);

int16_t PredictionResidual(image* hIMG, INDEX z, INDEX y, INDEX x);

uint16_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* QUANTIZER_H */
