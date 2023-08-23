#include "testing/generate_image.h"

#include <string.h>

int main(int argInt, char** argS){
    if(argInt > 1){
        if(!strcmp(argS[1], "generate")){
            GenerateTest((dim3) {atoi(argS[2]), atoi(argS[3]), atoi(argS[4])}, atoi(argS[5]));
        } 
    }
}