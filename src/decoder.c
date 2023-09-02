#include "decompressor/decoder.h"

#include <inttypes.h>
#include <stdio.h>

#define DECODE_READ_BUFFER 512





void Decoder_DecodeBody(image* predicted_samples, const char* file_name){
    dim3 size = predicted_samples->size;
    
    FILE* fp = fopen(file_name, "r");
    int32_t file_buffer[DECODE_READ_BUFFER];

    int x = 0, y = 0, z = 0;

    int i = 0;

    
}

