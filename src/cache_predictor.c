#include "cache/cache_predictor.h"
#include "predictor/local_sum.h"
#include <time.h>
#include <stdio.h>

PredictorCache *global_cache = NULL;
char *CacheFiles[] = {"raw.csv",
                      "local-sums.csv",
                      "sample-representatives.csv",
                      "predicted_sample.csv",
                      "central_local_difference.csv",
                      "predicted_central_local_difference.csv",
                      "clipped_quanitzer_bin_center.csv", "quantizer_index.csv"};

int CacheLocalSums(image *hIMG, image *local_sums)
{
    time_t start;
    time_t end;
    dim3 size = hIMG->size;

    for (int i = 0; i < size.z; i++)
    {
        start = time(NULL);
        for (int j = 0; j < size.x; j++)
        {
            for (int k = 0; k < size.y; k++)
            { // size.y    CLIP(Nz - j, 0, size.y)
                SetPixel(local_sums, j, k, i, FindLocalSum(hIMG, j, i, k));
            }
        }
        end = time(NULL);
        printf("Cached frame %d in %d seconds.\n", i, (int)(end - start));

        /*         for(int i = 0; i < CACHE_SPACES; i++){
                    SaveImageAsCSV(global_cache->cache_space[i], CacheFiles[i]);
                } */
    }

    return 0;
}

int InitializePredictorCache(PredictorCache **ptr_p_cache, image *hIMG)
{
    PredictorCache *p_cache = *ptr_p_cache = malloc(sizeof(PredictorCache));

    int x = hIMG->size.x;
    int y = hIMG->size.y;
    int z = hIMG->size.z;

    p_cache->cache_space[0] = hIMG;

    for (int i = 1; i < CACHE_SPACES; i++)
    {
        InitImage(&p_cache->cache_space[i], x, y, z);
    }
    for (int j = 1; j < CACHE_SPACES; j++)
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
    for (int i = 0; i < CACHE_SPACES; i++)
    {
        free(p_cache->cache_space[i]);
    }
    free(p_cache);
}

data_t CheckCache(INDEX z, INDEX y, INDEX x, CacheEnum data_index)
{
    return GetPixel(global_cache->cache_space[data_index], x, y, z);
}

int UpdateCache(INDEX z, INDEX y, INDEX x, CacheEnum data_index, data_t data)
{
    SetPixel(global_cache->cache_space[data_index], x, y, z, data);
    return 0;
}