/**
 * file_IO.h
 * @author @Kevin-Caldwell
 *
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

typedef enum file_mode
{
    READ = 0,
    WRITE,
    APPEND,
    READ_AND_WRITE,
    WRITING_AND_READING,
    APPENDING_AND_READING
} FileMode;

extern const char *file_modes_str[];

/*@null@*/
file_t *F_OPEN(
    const char *file_name,
    FileMode open_mode);

size_t F_WRITE(
    const void *write_ptr,
    size_t member_size,
    size_t member_count,
    file_t *file_ptr);

size_t F_READ(
    void *destination,
    size_t size,
    size_t arr_length,
    file_t *file_stream);

int F_CLOSE(file_t *stream);

int F_EMPTY(file_t *stream);

int F_SEEK(
    file_t *stream,
    long int offset);

#endif /* FILE_IO_H */
