#include "constants/load_constants.h"
#include "files/file_IO.h"

#include <stdio.h>

int LoadConstantFile(const char *file_name, HashTable *result)
{
    char line_buffer[KEY_LENGTH + 1 + 32];
    char key_buffer[KEY_LENGTH];
    int32_t data_buffer = 0;

    int constant_count = 0;
    char* res;
    char* token;

    file_t *fp = F_OPEN(file_name, READ);

    // Get the Number of Constants
    res = fgets(line_buffer, sizeof(char) * 10, fp);
    if(!res) return FILE_READ_ERROR; // ERROR HANDLING
    constant_count = atoi(line_buffer);


    for (int i = 0; i < constant_count; i++)
    {
        // Read Entire Line
        res = fgets(line_buffer, sizeof(char) * (KEY_LENGTH + 1 + 32), fp);
        if(!res) return FILE_READ_ERROR; // ERROR HANDLING

        // Parse Key
        token = strtok(line_buffer, ":");
        if (token)
        {
            strncpy(key_buffer, token, KEY_LENGTH);
        }

        // Parse Value
        token = strtok(NULL, ":");
        if (token)
        {
            data_buffer = atoi(token);
        }

        Hash_AddEntry(result, key_buffer, data_buffer);
    }
    
    F_CLOSE(fp);
    return RES_OK;
}

const int kpred_constant_count = 13;
const char* kpred_constant_names[] = {
    "LOSSLESS_COMPRESSION", 
    "PREDICTION_MODE", 
    "LOCAL_SUM",
    "WEIGHT_RESOLUTION", 
    "WEIGHT_INITIALIZATION", 
    "UNSIGNED_SAMPLES", 
    "PREDICTION_BANDS", 
    "WEIGHT_COMPONENT_RESOLUTION", 
    "REGISTER_SIZE", 
    "ABSOLUTE_ERROR_LIMIT_BIT_DEPTH", 
    "V_MIN", 
    "V_MAX", 
    "T_INC"
};

error_t SavePredictorConstants(S_kPred* kPred, char* file_name) {
    char write_buffer[100];

    int pred_constant_values[] = {
        (int) kPred->kLosslessCompression, 
        (int) kPred->kPredictionMode, 
        (int) kPred->kLocalSumType, 
        (int) kPred->kWeightResolution, 
        (int) kPred->kWeightInitialization, 
        (int) kPred->kUnsignedSamples, 
        (int) kPred->kP, 
        (int) kPred->kWeightComponentResolution, 
        (int) kPred->kR, 
        (int) kPred->kAbsoluteErrorLimitBitDepth, 
        (int) kPred->kVMin,
        (int) kPred->kVMax, 
        (int) kPred->kTInc
    };

    file_t* fp = F_OPEN(file_name, WRITE);
    if(!fp){
        return FILE_NON_EXISTENT;
    }

    snprintf(write_buffer, 100, "%d\n", kpred_constant_count);
    F_WRITE(write_buffer, sizeof(char), 100, fp);

    for(int i = 0; i < kpred_constant_count; i++){
        snprintf(write_buffer, 100, "%s:%d\n", kpred_constant_names[i], pred_constant_values[i]);
        F_WRITE(write_buffer, sizeof(char), 100, fp);
    }

    F_CLOSE(fp);

    return RES_OK;
}