#include <stdio.h>
#include <string.h>
#define TESTING_MATH

#include "constants/load_constants.h"

#include "testing/generate_image.h"

int main(int argInt, char **argS)
{
    if (argInt > 1)
    {
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
        // Base Case if no command line aguments are given.
        //PredictImage("../data/test-images/TEST_100x100x100_0.csv", "../data/results/CRESULT_100x100x100_0_predicted.csv");
        EncodeImage("../data/results/CRESULT_100x100x100_0_predicted.csv", "../data/results/CRESULT_100x100x100_0_encoded.hsp");
    }

    return 0;
}