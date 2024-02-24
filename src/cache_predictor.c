#include "cache/cache_predictor.h"
#include "predictor/local_sum.h"
#include <time.h>

PredictorCache *global_cache = NULL;
char *CacheFiles[] = {"raw.csv",
                      "local-sums.csv",
                      "sample-representatives.csv",
                      "predicted_sample.csv",
                      "central_local_difference.csv",
                      "predicted_central_local_difference.csv",
                      "clipped_quanitzer_bin_center.csv", "quantizer_index.csv"};



int InitializePredictorCache(PredictorCache **ptr_p_cache, image *hIMG)
{
    PredictorCache *p_cache = *ptr_p_cache = malloc(sizeof(PredictorCache));

    int x = hIMG->size.x;
    int y = hIMG->size.y;
    int z = hIMG->size.z;

    p_cache->cache_space[0] = hIMG;

    for (int i = 1; i < 1; i++)
    {
        InitImage(p_cache->cache_space[i], x, y, z);
    }
    for (int j = 1; j < 1; j++)
    {
        for (int i = 0; i < Nx * Ny * Nz; i++)
        {
            p_cache->cache_space[j]->data[i] = -1;
        }
    }

    InitializeWeights(&p_cache->weights, 0, 0, 0);

    return 0;
}

int DeletePredictorCache(PredictorCache *p_cache)
{
    for (int i = 0; i < 1; i++)
    {
        free(p_cache->cache_space[i]);
    }
    free(p_cache);

    return 0;
}
