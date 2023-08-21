#include "predictor/predictor.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

FILE *fp;

void Predict(image *hIMG, image *result, INDEX z, INDEX y, INDEX x)
{

    if (x == 0 && y == 0)
    {
        free(global_cache->weights);
        InitializeWeights(&global_cache->weights, z, y, x);
    }

    data_t raw_data = GetPixel(hIMG, x, y, z);
    uint16_t local_sum = FindLocalSum(hIMG, z, y, x);

    int32_t predicted_central_local_difference = PredictedCentralLocalDifference(hIMG, z, y, x);

    int64_t high_resolution_predicted_sample = HighResolutionPredictedSample(predicted_central_local_difference, local_sum);
    int32_t double_resolution_predicted_sample = DoubleResolutionPredictedSample(hIMG, z, y, x, high_resolution_predicted_sample);

    uint16_t predicted_sample = PredictedSample(double_resolution_predicted_sample);
    int32_t quantizer_index = QuantizerIndex(raw_data, predicted_sample);

    uint16_t clipped_quantizer_bin_center = ClippedQuantizerBinCenter(raw_data);
    int32_t double_resolution_predicted_error = DoubleResolutionPredictionError(clipped_quantizer_bin_center,
                                                                                double_resolution_predicted_sample);
    data_t predicted_value = MappedQuantizerIndex(quantizer_index,
                                                  predicted_sample,
                                                  double_resolution_predicted_sample);
    SetPixel(result, x, y, z, predicted_value);

    UpdateWeights(hIMG, global_cache->weights, z, y, x, double_resolution_predicted_error);

    char write_buffer[1000];

    sprintf(write_buffer, "(%d,%d,%d),%u, %d, %d, %d, %d,[", x, y, z, raw_data, predicted_sample, predicted_value, predicted_central_local_difference, double_resolution_predicted_sample);
    for (int i = 0; i < C(z); i++)
    {
        sprintf(write_buffer + strlen(write_buffer), "%d,", global_cache->weights[i]);
    }
    sprintf(write_buffer + strlen(write_buffer), "]\n");
    fwrite(write_buffer, sizeof(char), strlen(write_buffer), fp);
}

int RunPredictor(image *hIMG, image *result)
{
    printf("Running C Predictor.\n");
    time_t start;
    time_t end;
    dim3 size = hIMG->size;
    
    printf("Logging to logs/c-debug.LOG.\n");
    fp = fopen("../data/logs/c-debug.LOG", "w");

    start = time(NULL);
    for (int i = 0; i < size.z; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            for (int k = 0; k < size.x; k++)
            {
                Predict(hIMG, result, i, j, k);
            }
        }
        printf("\rGenerated %d/%d of Image.", (int)(i + 1), (int)hIMG->size.x);
        fflush(stdout);
    }
    fclose(fp);
    end = time(NULL);
    printf("\n%d seconds for image prediction.\n", (int)(end - start));
    return 0;
}
