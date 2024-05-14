/**
 * @file cache_predictor.h
 * @brief Deprecated, Used as a buffer for debugging and temporary storage
 * @authors Kevin Caldwell
 * @bug No Bugs
 * @deprecated Large Memory Usage, ineffective for debug.
 */

#ifndef CACHE_PREDICTOR_H
#define CACHE_PREDICTOR_H

#include "math/linear_algebra.h"
#include "dst/image.h"

extern char *CacheFiles[];

/**
 * @brief Struct PredictorCache is a struct for storing
 * the intermediate results obtained through the predictor.
 *
 * cache_space: dynamically allocated image array for storing multiple
 * images
 *
 * weights: dynamcially allocated int32_t array for storing the weights
 *
 * @deprecated
 * The Predictor testing has been re-implemented to accomodate more
 * streamlined and memory-efficient debugging processes.
 *
 * See predictor.c for more details
 */
struct PredictorCache
{
    image *cache_space[1];
    int32_t *weights;
};
typedef struct PredictorCache PredictorCache;

extern PredictorCache *global_cache;

int InitializePredictorCache(PredictorCache **p_cache);

int DeletePredictorCache(PredictorCache *p_cache);

#endif /* CACHE_PREDICTOR_H */
