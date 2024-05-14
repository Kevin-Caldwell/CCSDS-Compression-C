/**
 * decoder.h
 * @authors @Kevin-Caldwell @BrianShTsoi
 *
 * Functions for Decoding an image from a .HSP file
 *
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
 * TODO
 *  Finish Decoder_DecodeBody
 *  Finish Decoder_DecodeHeader
 *  Finish Decoder_DecodeImage
 */

#ifndef DECODER_H
#define DECODER_H

#include "dst/image.h"

void Decoder_DecodeBody(image *predicted_samples, const char *file_name);

void TestDecoder(char *filename);

#endif /* DECODER_H */
