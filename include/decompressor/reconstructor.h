/**
 * reconstructor.h
 * @authors @Kevin-Caldwell
 * 
 * Major Function Definitions of Reconstructor Module
 * 
 * Features
 *  Reconstructing an Image
 *  Reconstructing Individual Pixels
 *  Reconstructor Testing
 * 
 * Uses
 *  Validation of Predictor Output
 *  Validation of Complete Compression Output
 * 
 * Dependencies
 *  constants.h
 *  math_functions.h
 *  linear_algebra.h
 *  image.h
 *  quantizer.h
 *  csv-io.h
 *  predictor.h
 * 
 *  inttypes.h
 * 
 * TODO Internal Dependencies
 *  
 * TODO
 *  Finish Reconstructor Module
 *      Test Reconstruct Pixel
 *      Reconstructor
 *      Test Reconstructor
 *      Validate Reconstructor with Python
*/

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

void ReconstructPixel(image *hIMG, image *result, INDEX z, INDEX y, INDEX x, FILE* file_ptr);

void Reconstructor(image* predicted_values, image* reconstructed, FILE* file_ptr);

void TestReconstructor(char* file_name);

#endif /* RECONSTRUCTOR_H */
