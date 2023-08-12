#ifndef SAMPLE_REPRESENTATIVE_H
#define SAMPLE_REPRESENTATIVE_H

#include "cache/image_instance.h"
#include "constants/constants.h"
#include "cache/cache_predictor.h"
#include "math/linear_algebra.h"
#include "predictor/local_differences.h"
#include "predictor/quantizer.h"


#define SR(hIMG, Z, Y, X)     SampleRepresentative(hIMG, Z, Y, X)
//#define SAMPLE(z,y,x) (0) // TODO

extern data_t damping[];
extern data_t offset[];

data_t SampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x);

uint32_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x);

uint16_t PredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

uint32_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

uint64_t HighResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

uint16_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* SAMPLE_REPRESENTATIVE_H */
