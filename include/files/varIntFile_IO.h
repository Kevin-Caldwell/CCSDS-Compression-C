/**
 * @file varIntFile_IO.h
 * @brief File Input/Output for Variable-Length Words.
 * @details
 * VUF files are the end result of HyperC's Compressor.
 * Files are structured as a bit stream, where each value is stored
 * as an i-bit value, where i can change between successive reads. 
 * @note Base Functionality Tested
 * @bug Currently in Testing for Compressed Images
 */

#ifndef VARINTFILE_IO_H
#define VARINTFILE_IO_H

#include <inttypes.h>
#include <stdlib.h>

#include "files/file_IO.h"
#include "files/logs.h"

#include "constants/global_constants.h"
#include "encoder/encoder_helper_functions.h"

/**
 * @brief Number of Buffer Elements
 */
#define BUFFER_LENGTH 6
/**
 * @brief Bit size of each Buffer Element
 */
#define BUFFER_SIZE 32

typedef enum file_modes
{
    READ_BINARY = 0,
    WRITE_BINARY
} file_modes;

/**
 * @details
 * Manages VUF files.
 *
 * Variable Unsigned Files are designed to
 * store integers of sizes less than
 * 32 bits and greater than 0 bits.
 */
typedef struct VarUnsignedIntFile
{
    file_t *fs;
    char io_mode;

    int8_t bit_index;
    int8_t byte_index;
    uint32_t rw_buffer[BUFFER_LENGTH];
} VUF;


/** 
 * @brief Initializes a VUF file
 * @details 
 * Opens the file at file_name and initializes the buffers in the stream.
 * @param stream VUF struct that stores the file handle and relevant buffers
 * @param file_name 
 * @param io_mode Either READ_BINARY or WRITE_BINARY
 */
error_t VUF_initialize(
    VUF *stream,
    const char *file_name,
    file_modes io_mode);

/**
 * @brief Appends a VUF file with data of a certain length.
 * @details 
 * Splits data into 2 parts: One part that fits on the active buffer element
 * and the overflow.
 * The first part is appended into the active buffer element, and 
 * the overflow is loaded onto the next.
 * @param stream VUF Stream
 * @param data Input data in a 32-bit integer
 * @param length Length in bits of the data
 */
error_t VUF_append(
    VUF *stream,
    uint32_t data,
    uint32_t length);

/**
 * @brief Reads the next value of size length from the VUF file.
 * @details 
 * Reads the next {length} bits from the buffer.
 * Once the buffer is completely read, the buffer is filled with 
 * more data read from the file.
 */
// Read One VarInt
uint32_t VUF_read_stack(
    VUF *stream,
    uint32_t length);

error_t VUF_close(VUF *stream);

#endif /* VARINTFILE_IO_H */
