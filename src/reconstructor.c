#include "decompressor/reconstructor.h"

#include <time.h>

image *sample;
void Reconstructor(image *predicted_values, image *reconstructed, FILE* file_ptr)
{
    InitalizeImageConstants(predicted_values->size);
    LoadConstantFile(PREDICTOR_CONSTANTS_LOCATION, &predictor_constants);
    InitalizePredictorConstants();
    time_t start;
    time_t end;
    dim3 size = predicted_values->size;

    start = time(NULL);
    for (int z = 0; z < size.z; z++)
    {
        if (!PREDICTION_MODE)
        {
            C = Ps(z) + 3;
        }
        else
        {
            C = Ps(z);
        }
        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
            {
                ReconstructPixel(predicted_values, reconstructed, z, y, x, file_ptr);
            }
        }

        time_t time_elapsed = time(NULL) - start;
        time_t time_left = time_elapsed * (Nz - z - 1) / (z + 1);
        printf("\rPredicted %d/%d of Image. (%ld seconds Elapsed, %ld seconds Left)", (int)(z + 1), (int)size.z, time_elapsed, time_left);
        fflush(stdout);
    }
    end = time(NULL);
    printf("\n%d seconds for image prediction.\n", (int)(end - start));
}

void ReconstructPixel(image *mapped, image *data, INDEX z, INDEX y, INDEX x, FILE* file_ptr)
{
    if (x == 0 && y == 0)
    {
        free(global_cache->weights);
        InitializeWeights(&global_cache->weights, z, y, x);
    }
    data_t mapped_data = GetPixel(mapped, x, y, z);
    uint16_t local_sum = FindLocalSum(data, z, y, x);

    int64_t predicted_central_local_difference = PredictedCentralLocalDifference(data, z, y, x);

    int64_t high_resolution_predicted_sample = HighResolutionPredictedSample(predicted_central_local_difference, local_sum);
    int32_t double_resolution_predicted_sample = DoubleResolutionPredictedSample(data, z, y, x, high_resolution_predicted_sample);

    uint16_t predicted_sample = PredictedSample(double_resolution_predicted_sample);

    int32_t delta = QuantizerIndexUnmapper(mapped_data,
                                           predicted_sample,
                                           double_resolution_predicted_sample);
    uint16_t clipped_quantizer_bin_center = ClippedQuantizerBinCenter(predicted_sample + delta);
    int32_t double_resolution_predicted_error = DoubleResolutionPredictionError(clipped_quantizer_bin_center,
                                                                                double_resolution_predicted_sample);
    // int32_t double_resolution_predicted_error = 2 * (predicted_sample + delta) - double_resolution_predicted_error
    SetPixel(data, x, y, z, (uint16_t)predicted_sample + delta);

    UpdateWeights(data, global_cache->weights, z, y, x, double_resolution_predicted_error);

    char write_buffer[1000];

    // sprintf(write_buffer, "(%d,%d,%d),%d, %d, %d\n",  x, y, z, delta + predicted_sample, predicted_sample, delta);

    sprintf(write_buffer, "(%d,%d,%d),%u, %d, %d, %ld, %d, %ld, [", x, y, z, delta + predicted_sample, predicted_sample, mapped_data, 
        predicted_central_local_difference, double_resolution_predicted_sample, high_resolution_predicted_sample);

    for (int i = 0; i < C; i++)
    {
        sprintf(write_buffer + strlen(write_buffer), "%d,", global_cache->weights[i]);
    }
    sprintf(write_buffer + strlen(write_buffer), "]\n");

    sprintf(write_buffer + strlen(write_buffer), "UpdateWeights args: %d %d %d %d\n", z, y, x, double_resolution_predicted_error);
    F_WRITE(write_buffer, sizeof(char), strlen(write_buffer), file_ptr);
}

void TestReconstructor(char *file_name)
{
    file_t* file_ptr;

    printf("Testing Reconstructor...\n");
    image sample_data;
    ReadImageFromCSV(&sample_data, file_name);
    printf("Finished Reading Image.\n");
    sample = &sample_data;

    image predicted_data;
    InitImage(&predicted_data, sample_data.size.x, sample_data.size.y, sample_data.size.z);

    printf("Running Predictor...\n");
    fflush(stdout);
    InitializePredictorCache(&global_cache, &sample_data);
    printf("Cache Created..\n");
    RunPredictor(&sample_data, &predicted_data);
    printf("Completed Prediction.\n");

    printf("Logging to logs/c-debug.LOG.\n");
    file_ptr = F_OPEN("../data/logs/c-reconstructor-debug.LOG", WRITE);

    image reconstructed_data;
    InitImage(&reconstructed_data, sample_data.size.x, sample_data.size.y, sample_data.size.z);

    for(int i = 0; i < sample->size.x * sample->size.y * sample->size.z; i++){
        reconstructed_data.data[i] = 0;
    }

    printf("Running Reconstructor...\n");
    Reconstructor(&predicted_data, &reconstructed_data, file_ptr);
    printf("Completed Reconstruction.\n");

    int res = Image_Equals(&sample_data, &reconstructed_data);

    if (res == INT32_MAX)
    {
        printf("Reconstruction Success!\n");
    }
    else
    {
        printf("Reconstruction Failed at i= %d.\n", res);
    }

    F_CLOSE(file_ptr);

    free(sample_data.data);
    free(predicted_data.data);
    free(reconstructed_data.data);
}