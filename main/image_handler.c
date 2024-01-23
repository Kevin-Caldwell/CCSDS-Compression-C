#include "testing/generate_image.h"
#include "testing/perlin.h"

#include <string.h>

 char DEBUG = 0;

int main(int argInt, char** argS){
    if(argInt > 1){
        if(!strcmp(argS[1], "generate")){
            if(!strcmp(argS[2], "voronoi")){
                GenerateVoronoiImage((dim3) {atoi(argS[3]), atoi(argS[4]), atoi(argS[5])}, atoi(argS[6]), atoi(argS[7]));
            } if(!strcmp(argS[2], "perlin")){
                GeneratePerlinImage((dim3) {atoi(argS[3]), atoi(argS[4]), atoi(argS[5])}, atoi(argS[6]), atoi(argS[7]));
            }
        } 
    } else{
        GeneratePerlinImage((dim3) {100, 100, 100}, 0, 10);
    }
}