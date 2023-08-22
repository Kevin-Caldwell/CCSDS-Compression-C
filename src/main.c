#include <stdio.h>
#include <string.h>
#define TESTING_MATH

#include "testing/generate_image.h"
#include "encoder/body.h"

void TestingCriteria(char **argS)
{
    if (argS[1][0] == '1')
    {
        TEST_1();
    }
    else if (argS[1][0] == '2')
    {
        BenchmarkVoronoi();
    }
}


int main(int argInt, char **argS)
{
    if (argInt > 1)
    {
        if (!strcmp(argS[1], "gentest"))
        {
            for (int i = 0; i < 1; i++)
            {
                GenerateTest((dim3) {atoi(argS[2]), atoi(argS[3]), atoi(argS[4])}, atoi(argS[5]));
            }
        }
        else if (!strcmp(argS[1], "file")){
            char res_buf[200];
            char s_buf[200];
            
            sprintf(res_buf, "../data/results/CRESULT%s_predicted.csv", argS[2]);
            sprintf(s_buf, "../data/test-images/TEST%s.csv", argS[2]);
            
            PredictImage(s_buf, res_buf);
        } else{
            printf("Command Not Recognized\n");
        }
    } else{

        // Base Case if no command line aguments are given.
        PredictImage("../data/test-images/TEST_100x100x100_0.csv", "../results/CRESULT_100x200x100_0_predicted.csv");
    }

    return 0;
}