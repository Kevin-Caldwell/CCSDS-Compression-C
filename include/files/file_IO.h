/**
 * @file file_IO.h
 * @brief Abstract Functions for File IO.
 * @details
 * Abstracted Functions for File IO.
 * Implementation in file_IO.c should
 * be adapted to fit the respective
 * file system.
 *
 * The datatype used throughout the code
 * is file_t.
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

#include "constants/global_constants.h"

/// File Handling Abstractions
typedef FILE file_t;

/**
 * @details
 * An abstraction of the stdio file access enum.
 * Used to specify read and write modes 
 */
typedef enum file_mode
{
    READ = 0,
    WRITE,
    APPEND,
    READ_AND_WRITE,
    WRITING_AND_READING,
    APPENDING_AND_READING
} FileMode;

/**
 * @brief Constant Array of strings representing stdio file access modes
 */
extern const char *file_modes_str[];

/**
 * @details 
 * An abstraction function for opening files
 */
file_t *F_OPEN(
    const char *file_name,
    FileMode open_mode);

/**
 * @details 
 * An abstraction function for writing to a file
 */
size_t F_WRITE(
    const void *write_ptr,
    size_t member_size,
    size_t member_count,
    file_t *file_ptr);

/**
 * @details 
 * An abstraction function for reading from a file
 */
size_t F_READ(
    void *destination,
    size_t size,
    size_t arr_length,
    file_t *file_stream);

/**
 * @details 
 * An abstraction function for closing files
 */
int F_CLOSE(file_t *stream);

/**
 * @details 
 * An abstraction function for checking if a file is empty
 */
int F_EMPTY(file_t *stream);

/**
 * @details 
 * An abstraction function for seeking to a specific position in a file. 
 * Makes it possible to get pixel values from specific areas
 */
int F_SEEK(
    file_t *stream,
    long int offset);

#endif /* FILE_IO_H */
