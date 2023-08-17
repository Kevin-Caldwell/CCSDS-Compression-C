#ifndef IMAGE_H
#define IMAGE_H

#include "math/math_functions.h"
#include "constants/constants.h"
#include <stdlib.h>

#define FRAME_SIZE(size) (size.x * size.y)
#define MAP3_1(i, j, k, size) (k * FRAME_SIZE(size) + size.x * j + i)
#define GetT(x, y) (y * Nx + x) 
#define GetX(t) (t % Nx)
#define GetY(t) ((int)t / Nx)

typedef struct image{
    dim3 size;
    PIXEL* data;
} image, image3;

int InitImage(image** img_p, size_t x, size_t y, size_t z);

PIXEL GetPixel(image* hIMG, INDEX x, INDEX y, INDEX z);
PIXEL* GetFrame(image* hIMG, INDEX y);

void SetPixel(image* hIMG, INDEX x, INDEX y, INDEX z, PIXEL data);

#define S(hIMG, z,y,x) GetPixel(hIMG, x,y,z)

typedef struct image2{
    dim2 size;
    PIXEL* data;
} image2;



#endif /* IMAGE_H */
