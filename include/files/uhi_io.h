#ifndef UHI_IO_H
#define UHI_IO_H

#include <inttypes.h>
#include <stdlib.h>
#include <files/file_IO.h>

typedef struct UncompressedHyperspectralImage{
    file_t* fs;
    
} F_UHI, UHI;

#endif /* UHI_IO_H */
