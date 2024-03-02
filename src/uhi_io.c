#include "files/uhi_io.h"

#include <stdio.h>

#include "dst/image.h"

int UHI_Initialize(UHI* stream, dim3 buffer_size, const char* file_name,
                   FileMode file_mode) {
  file_t* file = F_OPEN(file_name, file_mode);
  if(stream->fs == NULL){
    return 0;
  }
  // TODO Initialize Full File
  stream->fs = file;
  stream->size = buffer_size;
  stream->cache[0] = 0;
  return 0;
}

// | S S | S S | S S | X X | X X |
//    X     Y     Z     0     1
PIXEL UHI_ReadPixel(UHI* stream, dim3 index) {
  PIXEL pixel;
  dim3 s = stream->size;
  F_SEEK(
      stream->fs,
      6 + 2 * (MAP3_1(index.x, index.y, index.z, s)));
  F_READ(&pixel, sizeof(PIXEL), 1, stream->fs);
  return pixel;
}

int UHI_WritePixel(const UHI* stream, dim3 index, PIXEL value) {
  dim3 s = stream->size;
  F_SEEK(
      stream->fs,
      6 + 2 * (MAP3_1(index.x, index.y, index.z, s)));
  F_WRITE(&value, sizeof(PIXEL), 1, stream->fs);
  return 0;
}

int UHI_close(UHI* stream) {
  F_CLOSE(stream->fs);
  return 0;
}

PIXEL Proxy_GetPixel(uIMG* hIMG, INDEX x, INDEX y, INDEX z) {
  return UHI_ReadPixel(hIMG, (dim3){x, y, z});
}

void Proxy_SetPixel(uIMG* hIMG, INDEX x, INDEX y, INDEX z, PIXEL value) {
  UHI_WritePixel(hIMG, (dim3){x, y, z}, value);
}