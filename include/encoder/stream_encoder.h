#ifndef STREAM_ENCODER_H
#define STREAM_ENCODER_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#define L_SHIFT(x, s) (s < 0 ? x >> -s : x << s)

#define BUFFER_REG_SIZE 32

typedef struct VarIntFileStream
{
    FILE *fs;

    uint32_t *buffer;
    uint32_t buffer_size;

    int32_t bit_ptr;
    uint32_t byte_ptr;
} VIFS;

void InitializeVarIntStream(VIFS *stream, const char *file_name, uint32_t buffer_size);

void StreamVarInteger(VIFS *stream, uint32_t data, uint32_t length);

void CloseVarIntegerStream(VIFS* stream);



#endif /* STREAM_ENCODER_H */
