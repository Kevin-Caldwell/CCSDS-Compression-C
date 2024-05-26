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
#include <time.h>
#include <string.h>

#include "dst/image.h"

#include "constants/global_constants.h"
#include "constants/constants.h"

#include "math/math_functions.h"
#include "math/linear_algebra.h"

#include "predictor/weights.h"
#include "predictor/quantizer.h"


#include "files/logs.h"

#define Ps(z) MIN(z, kP)

extern int kC;

int RunPredictor(image *hIMG, image *result);

#endif /* PREDICTOR_H */
