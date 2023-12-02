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

#define L_SHIFT(x, s) (s == 32 ? 0 : (s < 0 ? (unsigned) x >> -s : (unsigned) x << s))

#define BUFFER_LENGTH 6
#define BUFFER_SIZE 32

typedef enum file_modes {READ_BINARY=0, WRITE_BINARY} file_modes;

typedef struct VarUnsignedIntFile{
    FILE *fs;
    uint32_t rw_buffer[BUFFER_LENGTH];
    char io_mode;

    int8_t bit_index;
    int8_t byte_index;
} VUF;

void VUF_initialize(
    VUF* stream, 
    const char* file_name, 
    file_modes io_mode);

void VUF_append(
    VUF* stream, 
    uint32_t data, 
    uint32_t length);

// Read One VarInt
uint32_t VUF_read_stack(
    VUF* stream, 
    uint32_t length);

void VUF_close(VUF* stream);

#endif /* VARINTFILE_IO_H */
