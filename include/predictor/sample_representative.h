/**
 * @file sample_representative.h
 * @authors Kevin Caldwell BrianShTsoi
 *
 * @brief A collection of Sample representative calculation
 * functions.
 */

#ifndef SAMPLE_REPRESENTATIVE_H
#define SAMPLE_REPRESENTATIVE_H

#include "dst/locale_buffer.h"

/** 
 * @brief Shorthand for GetPixel 
 * @warning Direct Image Access
 */
#define L_SR(hIMG, Z, Y, X) GetPixel(hIMG, X, Y, Z)
#define SR(B, Z, Y, X) LocaleBuffer_FetchPixel_Direct(B, Z, Y, X)

// #define SAMPLE(z,y,x) (0) // TODO

/** 
 * @brief Damping Offsets
 * @todo Move into Predictor Constants
 */
extern data_t damping[];

/** 
 * @brief Offset Coefficients
 * @todo Move into Predictor Constants
 */
extern data_t offset[];

/**
 * @brief Sample Representative Calculation
 * @details 
 * For Lossy Compression, this is calculated according to 
 * the CCSDS-123 Standard.
 * 
 * For Lossless Compression, the Sample Representative returns
 * the value of the pixel.
 * @note Use SR definition when using lossless compression.
 */
data_t SampleRepresentative(uint16_t sample_value);

/**
 * @brief Double Resolution Prediction Sample Calculation
 * @details
 * See Standard for Details.
 * @warning Direct Image Access
 */
uint32_t L_DoubleResolutionPredictedSample(image *hIMG, INDEX z, INDEX y, INDEX x, int64_t high_resolution_predicted_sample);

uint32_t DoubleResolutionPredictedSample(LBuf* buf, INDEX z, INDEX y, INDEX x, int64_t high_resolution_predicted_sample);
/**
 * @brief Predicted Sample Calculation
 * @details 
 * See Standard for Details.
 */
uint16_t PredictedSample(uint32_t double_resolution_predicted_sample);

/**
 * @brief High Resolution Prediction Sample Calculation
 * @details
 * See Standard for Details.
 */
int64_t HighResolutionPredictedSample(int64_t predicted_central_local_difference, uint32_t local_sum);

#endif /* SAMPLE_REPRESENTATIVE_H */
