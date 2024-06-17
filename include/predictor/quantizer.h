/**
 * quantizer.h
 * @author Kevin-Caldwell
 *
 * Functions For Quantizer
 */

#ifndef QUANTIZER_H
#define QUANTIZER_H

#include "dst/image.h"
#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "predictor/sample_representative.h"

int32_t QuantizerIndex(
    uint16_t sample_value,
    uint16_t predicted_sample);

data_t MappedQuantizerIndex(
    int32_t quantizer_index,
    int32_t predicted_sample,
    uint32_t double_res_predicted_sample);

int32_t QuantizerIndexUnmapper(
    uint16_t mapped_delta,
    uint16_t predicted_sample,
    int32_t drps);

int16_t PredictionResidual(
    uint16_t sample_value,
    uint16_t predicted_sample);

uint16_t ClippedQuantizerBinCenter(uint16_t sample_value);

#endif /* QUANTIZER_H */
