#include <stdio.h>

#define TESTING_MATH

#include "testing/generate_image.h"

int main(int argInt, char** argS){
    printf("Starting Program...\n");

    BenchmarkVoronoi();
    
    return 0;
}
