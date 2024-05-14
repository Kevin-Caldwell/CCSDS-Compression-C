#include "dst/image.h"

int file_index = 0;

int InitImage(image *img_p, size_t x, size_t y, size_t z)
{
    char file_name[40];
    sprintf(file_name, "_%lux%lux%lu_%d.UHI", x, y, z, file_index);
    UHI_Initialize(img_p, (dim3){x, y, z}, file_name, READ_AND_WRITE);
}

PIXEL GetPixel(image *hIMG, INDEX x, INDEX y, INDEX z)
{
    return UHI_ReadPixel(hIMG, (dim3){x, y, z});
}

void SetPixel(image *hIMG, INDEX x, INDEX y, INDEX z, PIXEL data)
{
    UHI_WritePixel(hIMG, (dim3){x, y, z}, data);
}

int Image_Equals(image *img1, image *img2)
{
    if (img1->size.x != img2->size.x ||
        img1->size.y != img2->size.y ||
        img1->size.z != img2->size.z)
    {
        return 0;
    }
    dim3 size = img1->size;
    for (int i = 0; i < size.x; i++)
    {
        for (int j = 0; j < size.y; j++)
        {
            for (int k = 0; k < size.y; k++)
            {
                if (UHI_ReadPixel(img1, (dim3){i, j, k}) != UHI_ReadPixel(img1, (dim3){i, j, k}))
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}