#include <stdio.h>
#include <string.h>
#define TESTING_MATH

#include "testing/generate_image.h"

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
    printf("Entered C Main.\n");
    if (argInt > 1)
    {
        if (!strcmp(argS[1], "gentest"))
        {
            for (int i = 0; i < 1; i++)
            {
                //GenerateTest((dim3){640, 512, 640}, i);
                GenerateTest((dim3){100, 100, 100}, i);
                GenerateTest((dim3){3, 3, 3}, i);
            }
        }
        else if (!strcmp(argS[1], "file")){
            printf("%s\n", argS[2]);
            char res_buf[200];
            char s_buf[200];
            sprintf(res_buf, "../results/CRESULT%s_predicted.csv", argS[2]);
            sprintf(s_buf, "../test-images/TEST%s.csv", argS[2]);
            //printf("%s\n", )
            PredictImage(s_buf, res_buf); // /
        } else{
            printf("Command Not Recognized\n");
        }
    } else{
        PredictImage("../test-images/TEST_100x100x100_0.csv", "../results/CRESULT_100x100x100_0_predicted.csv");
    }

    return 0;
}