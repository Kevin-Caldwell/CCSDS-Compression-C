#include <stdio.h>
#include <string.h>

#include "testing/generate_image.h"
#include "files/logs.h"

typedef enum ACTIONS{
    COMPRESS = 0, 
    PREDICT, 
    ENCODE, 
    TEST_PREDICTOR, 
    TEST_ENCODER,
    TEST_COMPRESSOR, 
    TEST_UHI, 
    TEST_VUF
} ACTIONS;


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

char DEBUG = 0;

char default_image_source[] = "../data/test-images/indian_pines.UHI";
char default_image_destination[] = "../data/test-images/indian_pines.UHI";


int main(int argInt, char **argS)
{

#if LOG
    Log_init();
#endif

    if (argInt > 1)
    {
#if LOG
        Log_add(argS[1]);
        printf("%s", argS[1]);
#endif
        DEBUG = argInt >= 5;

        if (!strcmp(argS[1], "encode"))
        {
            EncodeImage(argS[2], argS[3]);
        }
        else if (!strcmp(argS[1], "predict"))
        {
            PredictImage(argS[2], argS[3]);
        }
        else if (!strcmp(argS[1], "compress"))
        {
            CompressImage(argS[2], argS[3]);
        }
        else
        {
            printf("Command Not Recognized\n");
        }
    }
    else
    {
        printf("Running Base Case.\n");

        // cv_csv_uhi("../data/test-images/indian_pines.csv", "../data/test-images/indian_pines.UHI");
        // PredictImage("../data/test-images/indian_pines.csv", "../data/results/CRESULT_indian_pines_predicted.csv");
        PredictImageUHI(default_image_source, "../data/test-images/indian_pines_pred.UHI");
    }

#if LOG
    Log_close();
#endif

    return 0;
}