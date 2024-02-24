/**
 * encoder_helper_functions.h
 * @author @Kevin-Caldwell
 * 
 * Global Functions for Encoding the image
 * 
 * Features
 *  Print a byte in Binary
 *  Encode n bit data into m bit buffer, n < 8, data < 8
 * 
 * Dependencies
 *  inttypes.h
 *  stdio.h
*/

#ifndef ENCODER_HELPER_FUNCTIONS_H
#define ENCODER_HELPER_FUNCTIONS_H

#include <inttypes.h>

void PrintBinary(uint8_t byte);

void Encode(uint8_t* destination, uint8_t index, uint8_t data, uint8_t length);

#endif /* ENCODER_HELPER_FUNCTIONS_H */
