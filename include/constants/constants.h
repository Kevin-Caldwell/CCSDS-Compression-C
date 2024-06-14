/**
 * @file constants.h
 * @brief A Global File for constants shared between modules
 * @details 
 * Contains constants for the predictor, as well as some image-related
 * constants.
 * @author Kevin Caldwell
 * @date May 29, 2024
 * 
 * 
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "math/math_functions.h"
#include "global_constants.h"

#define TRUE 1
#define FALSE 0

// Predictor Constants

/**
 * \brief
 * Selects the Prediction Mode
 * 0: Full Prediction Mode
 * 1: Reduced Prediction Mode
 */
extern t_prediction_mode kPredictionMode;


/**
 * \brief
 * Local Sum Type Selected
 * 0b00: Wide Neighbor
 * 0b01: Narrow Neighbor
 * 0b10: Wide Column
 * 0b11: Narrow Column
 */
extern t_local_sum kLocalSumType;

/** \brief Range of Pixel values possible */
extern uint8_t kDynamicRange;

/** \brief Sets the precision of the Damping and Offset Variables */
extern uint8_t kResolution;

// 0: Default Weight Initialization
// 1: Custom Weight Initialization
#define WEIGHT_INITIALIZATION 0

// 0: WEO values are zero
// 1: WEO values can be non-zero
#define WEIGHT_EXPONENT_OFFSET_FLAG 0
// 2^WEIGHT_UPDATE_SCALING_EXPONENT_CHANGE_INTERVAL

#pragma region Do Not Touch

extern int32_t kD;

extern int kUnsignedSamples;

extern int kSmin;
extern int kSmax;
extern int kSmid;

extern int32_t kP;
extern uint8_t Omega;
extern int64_t kR;
extern int kOmegaMin;
extern int kOmegaMax;

extern int kDa;
extern int km_z;
extern int kC;

extern int kVMin;
extern int kVMax;
extern int kTInc;

void InitalizePredictorConstants();
void Constants_validate();

#pragma endregion
#endif /* CONSTANTS_H */
