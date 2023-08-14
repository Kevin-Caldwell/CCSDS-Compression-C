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
    if (argInt > 1)
    {
        if (!strcmp(argS[1], "gentest"))
        {
            for (int i = 0; i < 10; i++)
            {
                GenerateTest((dim3){640, 512, 640}, i);
                GenerateTest((dim3){100, 100, 100}, i);
                GenerateTest((dim3){3, 3, 3}, i);
            }
        }
        if (strcmp(argS[1], "file")){
            
        }
    } else{
        TEST_1();
    }

    return 0;
}