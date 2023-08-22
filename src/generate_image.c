#include "testing/generate_image.h"
#include "encoder/body.h"

void GenerateTest(dim3 size, int index){
    char filename[100];
    sprintf(filename, "../data/test-images/TEST_%lux%lux%lu_%d.csv", 
                                        size.x, size.y, size.z, index);
    image* testImage;
    InitImage(&testImage, size.x, size.y, size.z);
    GenerateVoronoiFlat3DLocal(testImage, size.x * size.y * size.z / 180000);

    SaveImageAsCSV(testImage, filename);
    free(testImage->data);
    free(testImage);
}

void PredictImage(char* source, char* destination){
    image* hIMG;
    image* result;
    printf("___________C PREDICTOR____________\n");

    ReadImageFromCSV(&hIMG, source);
    printf("Read File.\n");

    InitializePredictorCache(&global_cache, hIMG);
    printf("Cache Created..\n");


    InitImage(&result, hIMG->size.x, hIMG->size.y, hIMG->size.z);
    RunPredictor(hIMG, result);
    EncodeBody(result, "out.hype", "w", 20);    

    SaveImageAsCSV(result, destination);

    DeletePredictorCache(global_cache);

    //free(hIMG->data);
    free(result->data);
    //free(hIMG);
    free(result);
}

int TEST_1()
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

    InitializePredictorCache(&global_cache, data);
    printf("Cache Created..\n");

    image *predicted_values;
    InitImage(&predicted_values, Nx, Ny, Nz);
    printf("Running Predictor\n");
    RunPredictor(data, predicted_values);
    printf("Completed Prediction\n");

    SaveImageAsCSV(predicted_values, "predictor.csv");
    char filename[80];
    for (int i = 0; i < CACHE_SPACES; i++)
    {
        sprintf(filename, "../data/results/%s", CacheFiles[i]);
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

void TestReadImage(){
    image* img;
    ReadImageFromCSV(&img, "data_locale.csv");
    SaveImageAsCSV(img, "data_locale2.csv");
    free(img->data);
    
}