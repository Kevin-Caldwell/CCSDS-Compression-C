#ifndef UHI_IO_H
#define UHI_IO_H

#include <inttypes.h>
#include <stdlib.h>
#include <files/file_IO.h>
#include <dst/image.h>

#define UHI_CACHE_LENGTH 3 // Image Size Buffer

/// @brief A struct for Managing UHI Images
typedef struct UncompressedHyperspectralImage{
    file_t* fs;
    dim3 size;
    int32_t cache[UHI_CACHE_LENGTH]; // TODO: Pixel Caching
} F_UHI, UHI;


int UHI_Initialize(
    UHI* stream, 
    dim3 buffer_size,
    const char* file_name, 
    FileMode file_mode
);

int UHI_WriteImage(
    const char* filename, 
    const image* source
);

int UHI_WritePixel(
    const UHI* stream, 
    dim3 index,
    PIXEL value
);

int UHI_ReadPixel(
    UHI* stream, 
    dim3 index
);
#endif /* UHI_IO_H */
