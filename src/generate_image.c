#include "testing/generate_image.h"

#include "cache/cache_predictor.h"
#include "testing/synthetic_image_generator.h"
#include "files/csv-io.h"

#include "encoder/header.h"

#include "files/csv-io.h"

#include <stdio.h>
#include <time.h>

void GenerateTest(dim3 size, int index){
    char filename[100];
    sprintf(filename, "../test-images/TEST_%lux%lux%lu_%d.csv", 
                                        size.x, size.y, size.z, index);
    image* testImage;
    InitImage(&testImage, size.x, size.y, size.z);
    GenerateVoronoiFlat3DLocal(testImage, size.x * size.y * size.z / 180000);

    SaveImageAsCSV(testImage, filename);
    free(testImage->data);
    free(testImage);
}

int TEST_1()
{
    image *data;

    dim3 bounds = (dim3){.x = Nx, .y = Ny, .z = Nz};

    InitImage(&data, Nx, Ny, Nz);

    int pts = 1000;

    time_t start = time(NULL);
    // GenerateVoronoiFlat3DNaive(data, pts);
    time_t end = time(NULL);

    // printf("Generated Synthetic Data in %d seconds..\n", (int) (end - start));
    // SaveImageAsCSV(data, "data_naive.csv");

    start = time(NULL);
    GenerateVoronoiFlat3DLocal(data, pts);
    end = time(NULL);

    printf("Generated Synthetic Data in %d seconds..\n", (int)(end - start));
    SaveImageAsCSV(data, "data_locale.csv");

    InitializePredictorCache(&global_cache, data);
    printf("Cache Created..\n");

    image *predicted_values;
    InitImage(&predicted_values, Nx, Ny, Nz);
    printf("Running Predictor\n");
    // CacheLocalSums(data, predicted_values);
    RunPredictor(data, predicted_values);
    printf("Completed Prediction\n");

    SaveImageAsCSV(predicted_values, "predictor.csv");
    char filename[80];
    for (int i = 0; i < CACHE_SPACES; i++)
    {
        sprintf(filename, "../results/%s", CacheFiles[i]);
        SaveImageAsCSV(global_cache->cache_space[i], filename);
    }

    DeletePredictorCache(global_cache);
    free(predicted_values);

    

    return 0;
}



void TestHeader(){
    uint8_t header[22];
    PrepareImageMetadata(header);
    PreparePredictorMetadata(header + 12);
    PrepareSampleAdaptiveEntropyCoder(header + 12 + 8);
}

void BenchmarkVoronoi()
{
    image *data;

    dim3 bounds = (dim3){.x = Nx, .y = Ny, .z = Nz};

    InitImage(&data, Nx, Ny, Nz);

    int pts = 1000;
    time_t start = time(NULL);
    GenerateVoronoiFlat3DLocal(data, pts);
    time_t end = time(NULL);

    printf("Generated Synthetic Data in %d seconds..\n", (int)(end - start));
    SaveImageAsCSV(data, "data_locale.csv");
    free(data);
}

/*
    for(int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
            for(int k = 0; k < Nz; k++){
                printf("%hu\t", data->data[MAP3_1(i,j,k, bounds)]);
            }

            printf("\n");
        }
        printf("\n");
    }
    printf("\n");  */

// git config --global user.email "you@example.com"
// git config --global user.name "Your Name"

void TestReadImage(){
    image* img;
    ReadImageFromCSV(&img, "data_locale.csv");
    SaveImageAsCSV(img, "data_locale2.csv");
    free(img->data);
    
}