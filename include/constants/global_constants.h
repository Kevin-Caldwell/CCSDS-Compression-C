/**
 * global_constants.h
 * @author @Kevin-Caldwell
 *
 * Contains Application-Level Constants
 *
 * Uses
 *  Log Files
 *  Constant Source Files
 *  Error Enumerations
 *
 * Dependencies
 *  Load Constants
 *
 * TODO
 *  Global Constants
 *  Consolidate all Constants under respective files
 */

#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

#include "constants/typedefs.h"

#include "constants/load_constants.h"

#define GLOBAL_CONSTANTS_LOCATION "/global.CONST"
#define PREDICTOR_CONSTANTS_LOCATION "../data/constants/predictor.CONST"
#define ENCODER_CONSTANTS_LOCATION "/encoder.CONST"

extern HashTable predictor_constants;
extern HashTable encoder_constants;

// Updated through CLI Arguments
extern char DEBUG;
extern char log_file[];

// #define ARM_GCC
#define WIN_GCC

#define LOG 1

#define global_error_handle if(res) return res;

#endif /* GLOBAL_CONSTANTS_H */
