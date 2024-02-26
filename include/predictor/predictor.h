/**
 * predictor.h
 * @author @Kevin-Caldwell
 * 
 * Top Level Function(s) for Running Predictor 
 * on a Hyperspectral Image. Returns a predicted
 * Hyperspectral Image.
 * 
*/

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdlib.h>
#include "constants/constants.h"
#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "dst/image.h"
#include "predictor/quantizer.h"

#define Ps(z) MIN(z, kP)

extern int C;

// typedef to allow for future change
typedef uint32_t weight_t;


int RunPredictor(image* hIMG, image* result);

#endif /* PREDICTOR_H */
