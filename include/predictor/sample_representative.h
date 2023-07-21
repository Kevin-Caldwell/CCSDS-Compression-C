#ifndef SAMPLE_REPRESENTATIVE_H
#define SAMPLE_REPRESENTATIVE_H

#include "image_instance.h"
#include "constants.h"
#include "math/linear_algebra.h"
#include "predictor/local_differences.h"
#include "predictor/quantizer.h"

#define SR(hIMG, z, y, x)     SampleRepresentative(hIMG, z, y, x)
#define SAMPLE(z,y,x) (0) // TODO

extern data_t* damping;
extern data_t* offset;

// TODO
data_t SampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t  PredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t HighResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* SAMPLE_REPRESENTATIVE_H */
