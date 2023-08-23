#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

#include "constants/load_constants.h"

#define GLOBAL_CONSTANTS_LOCATION           "/global.CONST"
#define PREDICTOR_CONSTANTS_LOCATION        "/predictor.CONST"
#define ENCODER_CONSTANTS_LOCATION          "/encoder.CONST"

extern HashTable predictor_constants;
extern HashTable encoder_constants;

#endif /* GLOBAL_CONSTANTS_H */
