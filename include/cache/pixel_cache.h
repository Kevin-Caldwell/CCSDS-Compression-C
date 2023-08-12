#ifndef PIXEL_CACHE_H
#define PIXEL_CACHE_H

#include <inttypes.h>

struct PixelCache{
    uint16_t sample;

    uint16_t sample_representative;
    uint32_t double_resolution_sample_representative;

    uint16_t predicted_sample;
    uint32_t double_resolution_predicted_sample;
    uint64_t high_resolution_predicted_sample;
    uint16_t clipped_quantizer_bin_center;
    


    uint16_t prediction_residual;
    int32_t quantizer_index;
    int16_t prediction_residual;

};

typedef struct PixelCache PixelCache;

#endif /* PIXEL_CACHE_H */
