#ifndef QUANTIZER_H
#define QUANTIZER_H

#include "image_instance.h"
#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "predictor/sample_representative.h"

// ! DO NOT USE
// Replaced by m_z 
int QuantizerFidelityControl(INDEX z, INDEX y, INDEX x);

data_t QuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t MappedQuantizerIndex(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t PredictionResidual(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* QUANTIZER_H */
