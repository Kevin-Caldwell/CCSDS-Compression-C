#include "files/uhi_io.h"
#include "dst/image.h"


error_t UHI_Initialize(UHI *stream, dim3 buffer_size, const char *file_name,
                   FileMode file_mode)
{
  stream->fs = F_OPEN(file_name, file_mode);
  if (!stream->fs)
  {
    return FILE_NON_EXISTENT;
  }

  stream->size = buffer_size;

  // Prepare Image for Writing.
  F_SEEK(stream->fs, 0);
  F_WRITE(&buffer_size, sizeof(dim3), 1, stream->fs);

  return RES_OK;
}

// | S S | S S | S S | X X | X X |
//    X     Y     Z     0     1
PIXEL UHI_ReadPixel(UHI *stream, dim3 index)
{
  PIXEL pixel;
  dim3 s = stream->size;
  F_SEEK(
      stream->fs,
      6 + 2 * (MAP3_1(index.x, index.y, index.z, s)));
  F_READ(&pixel, sizeof(PIXEL), 1, stream->fs);
  return pixel;
}

error_t UHI_WritePixel(const UHI *stream, dim3 index, PIXEL value)
{
  dim3 s = stream->size;
  F_SEEK(
      stream->fs,
      6 + 2 * (MAP3_1(index.x, index.y, index.z, s)));
  F_WRITE(&value, sizeof(PIXEL), 1, stream->fs);
  return RES_OK;
}

error_t UHI_close(UHI *stream)
{
  F_CLOSE(stream->fs);
  return RES_OK;
}

PIXEL Proxy_GetPixel(uIMG *hIMG, INDEX x, INDEX y, INDEX z)
{
  return UHI_ReadPixel(hIMG, (dim3){x, y, z});
}

void Proxy_SetPixel(uIMG *hIMG, INDEX x, INDEX y, INDEX z, PIXEL value)
{
  UHI_WritePixel(hIMG, (dim3){x, y, z}, value);
}