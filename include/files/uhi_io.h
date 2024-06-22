/**
 * @file uhi_io.h
 * @authors Kevin Caldwell @lalalalinn
 * @brief Uncompressed Hyperspectral Image file IO for storing
 * pixel values as 16-bit values.
 * @details
 * Functions for Uncompressed Hyperspectral
 * Image files. The file consists of
 * 14-bit pixel data stored as 16-bit data,
 * prioritizing fast read and write capabilities.
 *
 * The First 3 16-bit values store the dimensions
 * of the image, with the format: (kNx, kNy, kNz)
 */

#ifndef UHI_IO_H
#define UHI_IO_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#include "files/file_IO.h"
#include "math/math_functions.h"

/** 
 * @brief Image Size Buffer
 * @deprecated Pixel Caches not stored in UHI anymore. 
 * See locale_buffer.h instead.
 */
#define UHI_CACHE_LENGTH 3 // Image Size Buffer

/**
 * @details
 * Stores UHI file streams.
 *
 * File format designed to store 16 bit pixel data
 * for Hyperspectral Images. The first 3 data values
 * represent the size of the hyperspectral image,
 * and are followed by the pixel values.
 *
 * Designed to be a more RAM-friendly alternative to
 * the image struct defined in image.h. The data is
 * accessed from the filesystem instead of RAM,
 * which increases latency and runtime, but
 * reduces the RAM footprint of the overall program.
 *
 * fs: file_t object for handling file IO
 * size: stores the dimensions of the Hyperspectral image
 * cache: Unused 32 bit static array
 */
typedef struct UncompressedHyperspectralImage
{
    dim3 size;
    file_t *fs;
} F_UHI, UHI, uIMG;

/**
 * @brief Initializes a UHI stream for storing/retrieving image pixels.
 * @details 
 * Opens the file at {file_name}. 
 * @if a new file is being written to, it writes the image dimensions at the 
 * start.
 * @if an existing file is being written to, it writes over the old file. 
 * @if an existing file is being read, it initializes the UHI stream using the 
 * first 3 values in the file.
 * @todo Add Functionality for Reading Images.
 */
error_t UHI_Initialize(
    UHI *stream,
    dim3 size,
    const char *file_name,
    FileMode file_mode);

/**
 * @brief Writes a PIXEL value into an index on a UHI image.
 * @details
 * Stores a 16 bit value into 2 bytes at the index specified by
 * @code
 * 6 + 2 * (MAP3_1(index.x, index.y, index.z))
 * @endcode
 * It Seeks to the respective position, then calls
 * F_WRITE to store the pixel.
 * 
 * @param stream The UHI Stream handling the Image IO
 * @param index The (x, y, z) indices of the pixel to be written to
 * @param value The 16-bit value to be stored at the index
 * @returns RES_OK if success
 * @todo Handle index outside image dimensions.
 */
error_t UHI_WritePixel(
    const UHI *stream,
    dim3 index,
    PIXEL value);

/**
 * @brief Reads a PIXEL value from an index in an UHI image.
 * @details
 * Reads a 16 bit value from 2 bytes at the respective index.
 * The Index is specified as 
 * @code
 * 6 + 2 * (MAP3_1(index.x, index.y, index.z))
 * @endcode
 * Seeks to the Respective Position, then reads one PIXEL
 * at the location.
 * @param stream UHI instance for image storage
 * @param index (x,y,z) for index
 * @todo Handle Errors (Read Error, IndexOutOfBounds Error)
 * @todo Make the seek calculation more flexible
 */
PIXEL UHI_ReadPixel(
    UHI *stream,
    dim3 index);

/**
 * @brief Proxy function behaves the same way as image GetPixel
 * @deprecated Use UHI_ReadPixel instead.
 */
PIXEL Proxy_GetPixel(uIMG *hIMG, INDEX x, INDEX y, INDEX z);

/**
 * @brief Proxy function behaves the same way as image SetPixel
 * @deprecated Use UHI_WritePixel instead.
 */
void Proxy_SetPixel(uIMG *hIMG, INDEX x, INDEX y, INDEX z, PIXEL value);

#endif /* UHI_IO_H */
