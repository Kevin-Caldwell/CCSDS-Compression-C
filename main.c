#include <stdio.h>

#define TESTING_MATH

#include "testing/generate_image.h"

void TestingCriteria(char** argS){
    if(argS[1][0] == '1'){
            TEST_1();
        } else if (argS[1][0] == '2')
        {   
            BenchmarkVoronoi();
        }
}

int main(int argInt, char** argS){
    if(argInt > 1){
        TestingCriteria(argS);
    } else{
        ReadImage();
    }

    return 0;
}
