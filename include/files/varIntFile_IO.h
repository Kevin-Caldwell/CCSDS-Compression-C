/**
 * @file varIntFile_IO.h
 * @brief File Input/Output for Variable-Length Words.
 * @authors Kevin Caldwell
 * @bug Unknown, Needs Testing
*/

#ifndef VARINTFILE_IO_H
#define VARINTFILE_IO_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#define L_SHIFT(x, s) (s < 0 ? x >> -s : x << s)

#define BUFFER_SIZE 32;

typedef struct VarUnsignedIntFile{
    FILE *fs;
    uint32_t[BUFFER_SIZE] rw_buffer;
    char io_mode;

    int8_t bit_index;
    int8_t byte_index;
} VUF;

void VUF_initialize(
    VUF* stream, 
    const char* file_name, 
    char io_mode);

void VUF_append(
    VUF* stream, 
    uint32_t* data, 
    uint32_t length);

// Read One VarInt
void VUF_rpop( 
    VUF* stream, 
    uint32_t dump, 
    uint32_t length);

void VUF_close(VUF* stream);

#endif /* VARINTFILE_IO_H */
