#include "predictor/predictor.h"

file_t *fp;
// int _C = 0;
int kC = 0;

error_t Predict_BufferSimple(
    LBuf* buf, dim3 s, 
    INDEX z, INDEX y, INDEX x,
    weight_t* weights,
    PIXEL* predicted_value
){
    error_t res;
    
    LBuf pixel_buffer = *buf;
    data_t raw_data;

    res = LocaleBuffer_FetchPixel(&pixel_buffer, &raw_data, 0, 0, 0);
    log_global_error_handle

    uint16_t local_sum = FindLocalSum(&pixel_buffer, s, z, y, x);
    int64_t predicted_central_local_difference = 
        PredictedCentralLocalDifference(&pixel_buffer, s, weights);

    int64_t high_resolution_predicted_sample = 
        HighResolutionPredictedSample(
            predicted_central_local_difference, 
            local_sum
        );
    
    int32_t double_resolution_predicted_sample = 
        DoubleResolutionPredictedSample(
            &pixel_buffer, 
            z, y, x, 
            high_resolution_predicted_sample);

    uint16_t predicted_sample = 
        PredictedSample(double_resolution_predicted_sample);

    int32_t quantizer_index = 
        QuantizerIndex(raw_data, predicted_sample);

    uint16_t clipped_quantizer_bin_center = 
        ClippedQuantizerBinCenter(raw_data);
        
    int32_t double_resolution_predicted_error = 
        DoubleResolutionPredictionError(
            clipped_quantizer_bin_center,
            double_resolution_predicted_sample
        );

    *predicted_value = MappedQuantizerIndex(
        quantizer_index,
        predicted_sample,
        double_resolution_predicted_sample);

    UpdateWeights(&pixel_buffer, s, weights, z, y, x, double_resolution_predicted_error);

    if (DEBUG)
    {
        char write_buffer[1000];

        #ifdef ARM_COMPILE
        snprintf(write_buffer, 1000, "(%ld,%ld,%ld),%u, %d, %d, %lld, %ld, %lld, [",
                x, y, z,
                raw_data, predicted_sample, *predicted_value,
                predicted_central_local_difference, 
                double_resolution_predicted_sample, 
                high_resolution_predicted_sample);
        #else
       snprintf(write_buffer, 1000, "(%d,%d,%d),%u, %d, %d, %ld, %d, %ld, [",
                x, y, z,
                raw_data, predicted_sample, *predicted_value,
                predicted_central_local_difference, 
                double_resolution_predicted_sample, 
                high_resolution_predicted_sample);        
        #endif

        for (int i = 0; i < kC; i++)
        {
            #ifdef ARM_COMPILE
            sprintf(write_buffer + strlen(write_buffer), "%ld,", weights[i]);
            #else
            sprintf(write_buffer + strlen(write_buffer), "%d,", weights[i]);
            #endif
        }
        sprintf(write_buffer + strlen(write_buffer), "]\n");
        F_WRITE(write_buffer, sizeof(char), strlen(write_buffer), fp);
        
        return RES_OK;
    }
    return RES_OK;
}


int RunPredictor(image *hIMG, image *result)
{
    int res;

    res = LoadConstantFile(PREDICTOR_CONSTANTS_LOCATION, &predictor_constants);
    InitalizePredictorConstants();
#if LOG
    if (res)
    {
        Log_error("Unable to load Predictor Constants");
        return FILE_READ_ERROR;
    }
#endif

    clock_t start, end;
    dim3 s = hIMG->size;

#if LOG
    fp = F_OPEN("../data/logs/c-debug.LOG", WRITE);
    Log_memread = 0;

    Log_add("Setup Complete. Running C Predictor");
    start = clock();
#endif

    LBuf pixel_buffer;
    PIXEL predicted_value;

    
    for (int i = 0; i < s.z; i++)
    {
        if (!kPredictionMode)
        {
            kC = Ps(i) + 3;
        }
        else
        {
            kC = Ps(i);
        }
        
        weight_t weight_vector[kC];
        InitializeWeights(weight_vector, i);

        for (int j = 0; j < s.y; j++)
        {
            for (int k = 0; k < s.x; k++)
            {
                // Load all necessary pixels from image
                res = LocaleBuffer_Load(&pixel_buffer, hIMG, (dim3){i, j, k});
                log_global_error_handle

                Predict_BufferSimple(&pixel_buffer, hIMG->size, i, j, k, weight_vector, &predicted_value);
                // printf("%d\n", predicted_value);
                SetPixel(result, i, j, k, predicted_value);
            }
        }

#if LOG
        double time_elapsed = (double)(clock() - start) / (double)CLOCKS_PER_SEC;
        double time_left = time_elapsed * (s.z - i - 1) / (i + 1);
        printf("\rPredicted %d/%d of Image. (%3.1f seconds Elapsed, %3.1f seconds Left)", (int)(i + 1), (int)s.z, time_elapsed, time_left);
        fflush(stdout);
#endif
    }

#if LOG
    sprintf(log_write_buffer, "Image File accessed %d times.", Log_memread);
    Log_add(log_write_buffer);
    #ifdef ARM_COMPILE
    sprintf(log_write_buffer, "%f Image File Accesses per pixel. (%ld, %ld, %ld)", (float) Log_memread / (s.x * s.y * s.z), s.x, s.y, s.z);
    #else
    sprintf(log_write_buffer, "%f Image File Accesses per pixel. (%d, %d, %d)", (float) Log_memread / (s.x * s.y * s.z), s.x, s.y, s.z);
    #endif
    Log_add(log_write_buffer);

    F_CLOSE(fp);

    end = clock();
    double time_elapsed = (double)(end - start) / (double)CLOCKS_PER_SEC;
    printf("\n%3.3f seconds for image prediction.\n", time_elapsed);

    sprintf(log_write_buffer, "Time taken for prediction: %3.3f seconds", time_elapsed);
    Log_add(log_write_buffer);

    Log_add("Prediction Completed Successfully!");
#endif

    return RES_OK;
}
