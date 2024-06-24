/**
 * @file quantizer.h
 *
 * @brief Functions For the Quantizer Steps
 * @details
 * Quantizer Functions do not need direct access to the image.
 * @todo Reorganize Functions to have less cyclic inclusions.
 */

#ifndef QUANTIZER_H
#define QUANTIZER_H

#include "constants/constants.h"

/**
 * @brief Finds the Quantizer Index
 * @details
 * Refer to the CCSDS-123 Standard.
 * Does not need Image Access.
 */
int32_t QuantizerIndex(
    uint16_t sample_value,
    uint16_t predicted_sample);

/** 
 * @brief Finds the Mapped Quantizer Index
 * @details 
 * Refer to the CCSDS-123 Standard.
 * Does not need Image Access.
 */
data_t MappedQuantizerIndex(
    int32_t quantizer_index,
    int32_t predicted_sample,
    uint32_t double_res_predicted_sample);

/**
 * @brief Finds the Quantizer Index Unmapper
 * @details
 * Refer to the CCSDS-123 Standard.
 * Does not need Image Access.
 */
int32_t QuantizerIndexUnmapper(
    uint16_t mapped_delta,
    uint16_t predicted_sample,
    int32_t drps);

/**
 * @brief Finds the Prediction Residual
 * @details
 * Refer to the CCSDS-123 Standard.
 * Does not need Image Access.
 */
int16_t PredictionResidual(
    uint16_t sample_value,
    uint16_t predicted_sample);

/**
 * @brief Finds the Clipped Quantizer Bin Center
 * @details
 * Refer to the CCSDS-123 Standard.
 * Does not need Image Access.
 */
uint16_t ClippedQuantizerBinCenter(uint16_t sample_value);

#endif /* QUANTIZER_H */
