#include "cache/cache_predictor.h"
#include "predictor/local_sum.h"
#include <time.h>

/*@NULL@*/
PredictorCache *global_cache = NULL;
char *CacheFiles[] = {"raw.csv",
                      "local-sums.csv",
                      "sample-representatives.csv",
                      "predicted_sample.csv",
                      "central_local_difference.csv",
                      "predicted_central_local_difference.csv",
                      "clipped_quanitzer_bin_center.csv", "quantizer_index.csv"};

int InitializePredictorCache(PredictorCache **ptr_p_cache)
{
    PredictorCache *p_cache = *ptr_p_cache = (PredictorCache *)malloc(sizeof(PredictorCache));

    InitializeWeights(&p_cache->weights, 0, 0, 0);

    return 0;
}

int DeletePredictorCache(PredictorCache *p_cache)
{
    free(p_cache->weights);
    free(p_cache);

    return 0;
}
