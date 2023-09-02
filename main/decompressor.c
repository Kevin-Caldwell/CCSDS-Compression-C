
#include "decompressor/reconstructor.h"
#include <string.h>

int main(int argInt, char** argS){
    if(argInt > 1){
        if(!strcmp(argS[1], "reconstruct")){
            TestReconstructor(argS[2]);
        } 
    } else {
        TestReconstructor("../data/test-images/TEST_100x100x100_0.csv");
    }
    return 0;
}