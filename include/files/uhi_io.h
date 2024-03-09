/**
 * uhi_io.h
 * @authors @Kevin-Caldwell @lalalalinn
 * 
 * Functions for Uncompressed Hyperspectral
 * Image files. The file consists of 
 * 14-bit pixel data stored as 16-bit data, 
 * prioritizing fast read and write capabilities.
 * 
 * The First 3 16-bit values store the dimensions 
 * of the image, with the format: (Nx, Ny, Nz)
*/

#ifndef UHI_IO_H
#define UHI_IO_H

#include <inttypes.h>
#include <stdlib.h>
#include "files/file_IO.h"
#include "math/math_functions.h"

#define UHI_CACHE_LENGTH 3 // Image Size Buffer

/**
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
typedef struct UncompressedHyperspectralImage{
    file_t* fs;
    dim3 size;
    int32_t cache[UHI_CACHE_LENGTH]; // TODO: Pixel Caching
} F_UHI, UHI, uIMG;


int UHI_Initialize(
    UHI* stream, 
    dim3 size,
    const char* file_name, 
    FileMode file_mode
);

int UHI_WritePixel(
    const UHI* stream, 
    dim3 index,
    PIXEL value
);

PIXEL UHI_ReadPixel(
    UHI* stream, 
    dim3 index
);


PIXEL Proxy_GetPixel(uIMG* hIMG, INDEX x, INDEX y, INDEX z);

void Proxy_SetPixel(uIMG* hIMG, INDEX x, INDEX y, INDEX z, PIXEL value);


#endif /* UHI_IO_H */
