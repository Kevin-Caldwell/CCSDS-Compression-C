#include <stdio.h>
#include <string.h>

#include "testing/generate_image.h"
#include "files/logs.h"

const char default_image_source[] = "../data/test-images/indian_pines.UHI";
const char default_image_destination[] = "../data/results/indian_pines.UHI";
const ACTION default_action = PREDICT;
const char default_debug = 0;
char DEBUG = 0;


char* ACTIONS_str[] = {
    "compress", 
    "predict", 
    "encode", 
    "test_predictor", 
    "test_encoder", 
    "test_compressor", 
    "test_uhi", 
    "test_vuf"
};

error_t execute(
    char image_source[100], 
    char image_destination[100], 
    ACTION action){
    
    switch (action)
    {
    case COMPRESS:
        return CompressImage(image_source, image_destination);
    case PREDICT:
        return PredictImageUHI(image_source, image_destination);
    case ENCODE:
        return EncodeImage(image_source, image_destination);
    case TEST_COMPRESSOR:
        return TASK_NOT_DEFINED;
    case TEST_ENCODER:
        return TASK_NOT_DEFINED;
    case TEST_UHI:
        return TASK_NOT_DEFINED;
    case TEST_VUF:
        return TASK_NOT_DEFINED;
    default:
        return NO_TASK;
    }
}

/**
 * CLI Tags
 * -s       Source Image Path
 * -d       Destination Image Path
 * -a       Action
 * -D       Debug True
 * -l       Log File Path
 */
int main(int argInt, char **argS)
{
    char image_source[100];
    char image_destination[100];
    ACTION action = PREDICT;
    DEBUG = 0;

    strcpy(image_source, default_image_source);
    strcpy(image_destination, default_image_destination);

#if LOG
    Log_init();
#endif

    for(int i = 0; i < argInt; i++){

        if(!strcmp(argS[i], "-s")){
            i++;
            strncpy(image_source, argS[i], 100);

        } else if(!strncmp(argS[i], "-d", 100)){
            i++;
            strncpy(image_destination, argS[i], 100);

        } else if(!strncmp(argS[i], "-a", 100)){
            i++;
            for(int j = 0; j < 8; j++){

                if(!strncmp(argS[i], ACTIONS_str[j], 100)){
                    action = j;
                }
            }
        } else if(!strncmp(argS[i], "-D", 100)){
            DEBUG = 1;
        } else if(!strncmp(argS[i], "-l", 100)){
            strncpy(log_file, argS[i], 100);
        }
    }

    // printf("Source: %s\n", image_source);
    // printf("Destination: %s\n", image_destination);

    error_t res = execute(image_source, image_destination, action);


#if LOG
    Log_close();
#endif

    return res;
}