#include "testing/generate_image.h"

#include "cache/cache_predictor.h"
#include "fileio.h"

#include <stdio.h>


int GenerateData(image** hIMG, dim3* dataPoints, UINT point_count){
    InitImage(hIMG, Nx, Ny, Nz);
    image* img = *hIMG;

    UINT distance;
    UINT minimum_distance = 0;
    UINT index = 0;

    for(int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
            for(int k = 0; k < Nz; k++){
                minimum_distance = INT16_MAX;
                index = 0;
                for(int l = 0; l < point_count; l++){
                    distance = abs(dataPoints[l].x - i) + abs(dataPoints[l].y - j) + abs(dataPoints[l].z - k);
                    if(minimum_distance > distance){
                        minimum_distance = distance;
                        index = l;
                    }
                }
                SetPixel(img, i, j, k, index);
            }
        }
    }
    return 0;
}

#define INIT_ARRAY(T, count) (T*) malloc(sizeof(T) * count)

int SpreadPoints(dim3** points, dim3 bounds, UINT point_count){
    *points = INIT_ARRAY(dim3, point_count);

    for(int i = 0; i < point_count; i++){
        (*points)[i].x = rand() % bounds.x;
        (*points)[i].y = rand() % bounds.y;
        (*points)[i].z = rand() % bounds.z;
    }

    return 0;
}

int TEST_1()
{
    image* data;

    dim3* points;
    dim3 bounds = (dim3) {.x = Nx, .y = Ny, .z = Nz};

    SpreadPoints(&points, bounds, 10000);
    GenerateData(&data, points, 10000);
    printf("Generated Synthetic Data..\n");

    InitializePredictorCache(&global_cache, data);
    printf("Cache Created..\n");
    

    image* predicted_values;
    InitImage(&predicted_values, Nx,Ny,Nz);
    printf("Running Predictor\n");
    //CacheLocalSums(data, predicted_values);
    RunPredictor(data, predicted_values);
    printf("Completed Prediction\n");

    SaveImageAsCSV(predicted_values, "predictor.csv");
    for(int i = 0; i < CACHE_SPACES; i++){
        SaveImageAsCSV(global_cache->cache_space[i], CacheFiles[i]);
    }


    DeletePredictorCache(global_cache);

    free(points);
    free(predicted_values);

    return 0;
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

  //git config --global user.email "you@example.com"
  //git config --global user.name "Your Name"