/**
 * body.h
 * @author @Kevin-Caldwell
 * 
 * Helper Functions for Encoding the body of the Compressed Image
 * 
 * Features
 *  Golomb Power-of-Two
 *  Accumulator Value
 *  Encoding the Body of the Compressed file
 * 
 * Dependencies
 *  math_functions.h
 *  image.h
 *  encoder_constants.h
 *  stream_encoder.h
 * 
 * TODO
 *  Validate Results
*/

#ifndef BODY_H
#define BODY_H

#include <inttypes.h>

#include "math/math_functions.h"
#include "dst/image.h"
#include "constants/encoder_constants.h"
#include "encoder/stream_encoder.h"

extern int K;
extern unsigned int U_max;
extern int Gamma1;

#define GAMMA_STAR 5

/**
 * Package Struct for storing Compressed Data.
 * 
 * data: 32 bit int storing varInt Data
 * length: bit length of the value stored in data
*/
typedef struct GolombInt{
    uint32_t data;
    uint32_t length;
} GolombInt;

GolombInt GolombPowerTwo(uint16_t j, uint16_t k);

unsigned int InitAccumulatorValue(uint32_t z);

int EncodeBody(image* hIMG, const char* file_name, const char* write_mode, int buffer_size);

#endif /* BODY_H */
