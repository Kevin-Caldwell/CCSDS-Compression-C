#include "constants/global_constants.h"
#include "predictor/predictor.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "files/logs.h"

FILE *fp;
int C = 0;

void Predict(image *hIMG, image *result, INDEX z, INDEX y, INDEX x)
{

    if (x == 0 && y == 0)
    {
        free(global_cache->weights);
        InitializeWeights(&global_cache->weights, z, y, x);
    }

    data_t raw_data = GetPixel(hIMG, x, y, z);
    uint16_t local_sum = FindLocalSum(hIMG, z, y, x);

    int64_t predicted_central_local_difference = PredictedCentralLocalDifference(hIMG, z, y, x);

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

    if(DEBUG) {
        char write_buffer[1000];

        sprintf(write_buffer, "(%d,%d,%d),%u, %d, %d, %ld, %d, %ld, [",
            x, y, z, 
            raw_data, predicted_sample, predicted_value, 
            predicted_central_local_difference, double_resolution_predicted_sample, high_resolution_predicted_sample);

        for (int i = 0; i < C; i++)
        {
            sprintf(write_buffer + strlen(write_buffer), "%d,", global_cache->weights[i]);
        }
        sprintf(write_buffer + strlen(write_buffer), "]\n");
        fwrite(write_buffer, sizeof(char), strlen(write_buffer), fp);
    }
}

int RunPredictor(image *hIMG, image *result)
{
    int res;

    InitalizeImageConstants(hIMG->size);
    res = LoadConstantFile(PREDICTOR_CONSTANTS_LOCATION, &predictor_constants);
    InitalizePredictorConstants();
    #if LOG
    if(res) {
        Log_error("Unable to load Predictor Constants");
        return FILE_READ_ERROR;
    }
    #endif
    

    clock_t start, end;
    dim3 size = hIMG->size;

    #if LOG
    fp = fopen("../data/logs/c-debug.LOG", "w");

    Log_add("Setup Complete. Running C Predictor");
    start = clock();
    #endif

    for (int i = 0; i < size.z; i++)
    {
        if(!PREDICTION_MODE){
            C = Ps(i) + 3;
        } else{
            C = Ps(i);
        }

        for (int j = 0; j < size.y; j++)
        {
            for (int k = 0; k < size.x; k++)
            {
                Predict(hIMG, result, i, j, k);
            }
        }

        #if LOG
        double time_elapsed = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
        double time_left = time_elapsed * (Nz - i - 1) / (i + 1);
        printf("\rPredicted %d/%d of Image. (%3.1f seconds Elapsed, %3.1f seconds Left)", (int)(i + 1), (int)hIMG->size.z, time_elapsed, time_left);
        fflush(stdout);
        #endif
    }

    #if LOG
    fclose(fp);

    end = clock();
    double time_elapsed = (double) (end - start) / (double) CLOCKS_PER_SEC;
    printf("\n%3.3f seconds for image prediction.\n", time_elapsed);
        

    char out_buff[100];
    sprintf(out_buff, "Time taken for prediction: %3.3f seconds", time_elapsed);

    Log_add(out_buff);
    Log_add("Prediction Complete");
    #endif

    return RES_OK;
}
