#ifndef UHI_IO_H
#define UHI_IO_H

#include <inttypes.h>
#include <stdlib.h>
#include "files/file_IO.h"
#include "dst/image.h"

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

int UHI_WritePixel(
    const UHI* stream, 
    dim3 index,
    PIXEL value
);

PIXEL UHI_ReadPixel(
    UHI* stream, 
    dim3 index
);


// Image Proxy for Limiting RAM usage
typedef struct image_proxy{
    dim3 size;
    UHI* image_stream;
} image_proxy;

int InitProxyImage(
    image_proxy* img, 
    dim3 size, 
    const char* file_name
);

PIXEL Proxy_GetPixel(image_proxy* hIMG, INDEX x, INDEX y, INDEX z);

void Proxy_SetPixel(image_proxy* hIMG, INDEX x, INDEX y, INDEX z, PIXEL value);


#endif /* UHI_IO_H */
