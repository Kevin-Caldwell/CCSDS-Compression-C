#ifndef RECONSTRUCTOR_H
#define RECONSTRUCTOR_H

#include "constants/constants.h"
#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "dst/image.h"
#include "predictor/quantizer.h"
#include "files/csv-io.h"
#include <inttypes.h>
#include "predictor/predictor.h"

#define Ps(z) MIN(z, kP)
extern int C;
typedef uint32_t weight_t;

void ReconstructPixel(image *hIMG, image *result, INDEX z, INDEX y, INDEX x);

void Reconstructor(image* predicted_values, image* reconstructed);

void TestReconstructor(char* file_name);

#endif /* RECONSTRUCTOR_H */
