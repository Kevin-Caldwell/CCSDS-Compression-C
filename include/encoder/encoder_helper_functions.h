#ifndef ENCODER_HELPER_FUNCTIONS_H
#define ENCODER_HELPER_FUNCTIONS_H

#include <inttypes.h>
#include "stdio.h"

void PrintBinary(uint8_t byte);

void Encode(uint8_t* destination, uint8_t index, uint8_t data, uint8_t length);

#endif /* ENCODER_HELPER_FUNCTIONS_H */
