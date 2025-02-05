/**
 * @file encoder_constants.h
 *
 * @brief Contains all Encoder-Specific Constants
 * @details
 * Uses
 *  Encoder Abstraction
 * @todo Determine Encoder-Specific Constants
 * @todo Add comments for each Constants
 * 
 * 
 */

#ifndef ENCODER_CONSTANTS_H
#define ENCODER_CONSTANTS_H

#include "math/math_functions.h"
#include "constants/constants.h"

#define OUTPUT_WORD_SIZE 8

/// 00: Sample-Adaptive Entropy Coder\n
/// 01: Hybrid Entropy Coder\n
/// 10: Block-Adaptive Entropy Coder
#define ENTROPY_CODER 0b00

/// 00: Lossless\n
/// 01: Absolute Error Limit Only\n
/// 10: Relative Error Limit Only\n
/// 11: Both Absolute and Relative Errors
#define QUANTIZER_FIDELITY_CONTROL 0b00

#define TABLE_COUNT 0

#define SIZEOF_HEADER_ESSENTIAL 12

#define SAMPLE_REP_FLAG 1
#define WEO_TABLE_FLAG 0
#define WEIGHT_INITIALIZATION_TABLE_FLAG 0

/****************DAMPING AND OFFSET**********************/

/// 0: All bands use same Damping Value\n
/// 1: Varying damping values for each band
#define BAND_VARYING_DAMPING_FLAG 0

/// 0: Damping Table Not included\n
/// 1: Samping Table Included
#define DAMPING_TABLE_FLAG 0

/// 0: All bands use same Offset\n
/// 1: Varyign Offset values for each band
#define BAND_VARYING_OFFSET_FLAG 0

/// 0: Offset Table not included in SR\n
/// 1: Offset Table included in SR
#define OFFSET_TABLE_FLAG 0

#define FIXED_DAMPING 0
#define FIXED_OFFSET 0

/***********************ENTROPY CODER***************************/
// #define UNARY_LENGTH_LIMIT BPOW(5)
#define RESCALING_COUNTER_SIZE 1
#define INITIAL_COUNT_EXPONENT 1
#define ACCUMULATOR_INITIALIZATION 0b1111
#define ACCUMULATOR_INITIALIZATION_TABLE_FLAG 0

extern const uint8_t B;

/*************SAMPLE-ADAPTIVE ENTROPY CODER*********************/

#define INITIAL_COUNT_EXPONENT 1
#define ACCUMULATOR_INITIALIZATION_CONSTANT 14
#define UNARY_LENGTH_LIMIT 8

extern uint32_t U_max;
extern int32_t K;
extern uint32_t Gamma1;

#endif /* ENCODER_CONSTANTS_H */
