#include "files/uhi_io.h"

int UHI_Initialize(
    UHI* stream, 
    dim3 buffer_size,
    const char* file_name, 
    FileMode file_mode
){
    stream->fs = F_OPEN(file_name, READ);
    // TODO Initialize Full File
    stream->cache[0] = 0;
    return 0;
}

int UHI_WriteImage(
    const char* filename, 
    const image* source
) {

    return 0;
}


// | S S | S S | S S | X X | X X |
//    X     Y     Z     0     1
PIXEL UHI_ReadPixel(
    UHI* stream, 
    dim3 index
) {
    PIXEL pixel;
    dim3 s = stream->size;
    F_SEEK(stream->fs, stream->cache[6 + 2 * (s.x * s.y * index.z + s.x * index.y + index.x)]);
    F_READ(&pixel, sizeof(PIXEL), 1, stream->fs);
    return 0;
}

int UHI_WritePixel(
    const UHI* stream, 
    dim3 index,
    PIXEL value
){
    // Replace with Code
}

int UHI_close(UHI* stream){
    F_CLOSE(stream->fs);
}


PIXEL Proxy_GetPixel(uIMG* hIMG, INDEX x, INDEX y, INDEX z){
    return UHI_ReadPixel(hIMG, (dim3) {x, y, z});
}

void Proxy_SetPixel(uIMG* hIMG, INDEX x, INDEX y, INDEX z, PIXEL value){
    UHI_WritePixel(hIMG, (dim3) {x, y, z}, value);
}