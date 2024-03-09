#include <stdio.h>
#include <string.h>

#include "constants/load_constants.h"
#include "testing/generate_image.h"
#include "decompressor/reconstructor.h"
#include "testing/test_varInt.h"
#include "testing/test_UHI.h"

#if LOG
#include "files/logs.h"
#endif

char DEBUG = 0;

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
        // printf("Result: %s", test_UHI() ? "Unsuccessful Run.\n" : "Successful Run.\n");
        // printf("Result: %s", testVUF_Write() ? "Unsuccessful Run.\n" : "Successful Run.\n");
        // printf("Result: %s", testVUF_Read() ? "Failed.\n" : "Passed.\n");
        //PredictImage("../data/test-images/indian_pines.csv", "../data/results/CRESULT_indian_pines_predicted.csv");
        PredictImageUHI("../data/test-images/indian_pines.UHI", "../data/test-images/indian_pines_pred.UHI");
    }

    #if LOG
    Log_close();
    #endif

    return 0;
}