#ifndef CACHE_PREDICTOR_H
#define CACHE_PREDICTOR_H

#include "math/linear_algebra.h"
#include "dst/image.h"

enum CacheEnum{
    raw = 0,
    local_sums,
    CACHE_SPACES};

extern char* CacheFiles[];

struct PredictorCache{
    image* cache_space[CACHE_SPACES];
    int32_t* weights;
};



typedef enum CacheEnum CacheEnum;
typedef struct PredictorCache PredictorCache;
extern PredictorCache* global_cache;

int InitializePredictorCache(PredictorCache** p_cache, image* hIMG);

int DeletePredictorCache(PredictorCache* p_cache);


#endif /* CACHE_PREDICTOR_H */
