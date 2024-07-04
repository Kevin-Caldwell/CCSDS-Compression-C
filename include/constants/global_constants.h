/**
 * @file global_constants.h
 *
 * @brief Contains Application-Level Constants
 */

#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

#include "constants/typedefs.h"
#include "constants/load_constants.h"

// Location of global.CONST, configured by default to data/global.CONST
#define GLOBAL_CONSTANTS_LOCATION "/global.CONST"

// Location of predictor.CONST, configured by default to data/predictor.CONST
#define PREDICTOR_CONSTANTS_LOCATION "../data/constants/predictor.CONST"

// Location of encoder.CONST, configured by default to data/encoder.CONST
#define ENCODER_CONSTANTS_LOCATION "/encoder.CONST"

extern HashTable predictor_constants;
extern HashTable encoder_constants;

// Updated through CLI Arguments
extern char DEBUG;
extern char log_file[];
extern const char default_image_source[];
extern const char default_image_destination[];
extern const ACTION default_action;
extern const char default_debug;

#define LOG 1

// Error Handling Define, use log_global_error_handle when possible
#define global_error_handle if(res) return res;

#endif /* GLOBAL_CONSTANTS_H */
