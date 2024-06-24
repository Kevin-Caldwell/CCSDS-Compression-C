#include "dst/image.h"

int Log_memread = 0;

int file_index = 0;

int InitImage(image *img_p, DIM x, DIM y, DIM z)
{
    int res = 0;
    char file_name[40];
    
    res = snprintf(file_name, 40, "_%dx%dx%d_%d.UHI", (int) x, (int) y, (int) z, file_index);
    log_global_error_handle

    res = UHI_Initialize(img_p, (dim3){x, y, z}, file_name, READ_AND_WRITE);
    log_global_error_handle

    
    
    return res;
}

PIXEL GetPixel(image *hIMG, INDEX x, INDEX y, INDEX z)
{
    Log_memread++;
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