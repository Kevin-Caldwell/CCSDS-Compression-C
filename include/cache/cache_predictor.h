#ifndef CACHE_PREDICTOR_H
#define CACHE_PREDICTOR_H

#include "math/linear_algebra.h"
#include "dst/image.h"

enum CacheEnum{
    raw = 0,
    local_sums,
    sample_representatives,
    predicted_sample,
    central_local_difference,
    predicted_central_local_difference,
    clipped_quanitzer_bin_center,
    quantizer_index,
    CACHE_SPACES};

extern char* CacheFiles[];

struct PredictorCache{
    image* cache_space[CACHE_SPACES];
    int32_t* weights;
};



typedef enum CacheEnum CacheEnum;
typedef struct PredictorCache PredictorCache;
extern PredictorCache* global_cache;

int CacheLocalSums(image* hIMG, image* local_sums);

data_t CheckCache(INDEX z, INDEX y, INDEX x, CacheEnum data_index);

int UpdateCache(INDEX z, INDEX y, INDEX x, CacheEnum data_index, data_t data);

int InitializePredictorCache(PredictorCache** p_cache, image* hIMG);

int DeletePredictorCache(PredictorCache* p_cache);

#endif /* CACHE_PREDICTOR_H */
