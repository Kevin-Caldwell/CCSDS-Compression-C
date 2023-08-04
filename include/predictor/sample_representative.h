#ifndef SAMPLE_REPRESENTATIVE
#define SAMPLE_REPRESENTATIVE

#include "cache/image_instance.h"
#include "constants/constants.h"
#include "cache/cache_predictor.h"
#include "math/linear_algebra.h"
#include "predictor/local_differences.h"
#include "predictor/quantizer.h"


#define SR(hIMG, z, y, x)     SampleRepresentative(hIMG, z, y, x)
#define SAMPLE(z,y,x) (0) // TODO

extern data_t damping[];
extern data_t offset[];

data_t SampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t DoubleResolutionSampleRepresentative(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t  PredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t DoubleResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t HighResolutionPredictedSample(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t ClippedQuantizerBinCenter(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* SAMPLE_REPRESENTATIVE */
