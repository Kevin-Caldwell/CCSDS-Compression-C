/**
 * \file decoder.h
 * \authors Kevin Caldwell @BrianShTsoi
 *
 * \brief unctions for Decoding an image from a .HSP file
 * \details
 * Features
 *  Functions for Independently Decoding the Header and Body, or both
 *  if necessary.
 *
 * Uses
 *  Core File of the Decoder Module
 *
 * Dependencies
 *  image.h
 *
 * Internal Dependencies
 *  stdio.h
 *  inttypes.h
 *
 * \todo Finish Decoder_DecodeBody
 * \todo Finish Decoder_DecodeHeader
 * \todo Finish Decoder_DecodeImage
 */

#ifndef DECODER_H
#define DECODER_H

// INCLUDES
#include "dst/image.h"

#include <inttypes.h>
#include <time.h>

#include "files/varIntFile_IO.h"
#include "math/math_functions.h"
#include "constants/encoder_constants.h"
#include "encoder/body.h"

// FUNCTION DECLARATIONS

int Decoder_DecodeBody(image *predicted_samples, const char *file_name);

void TestDecoder(char *filename);

#endif /* DECODER_H */
