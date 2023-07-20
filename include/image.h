#ifndef IMAGE_H
#define IMAGE_H

#include "Math/math_functions.h"
#include "Math/constants.h"
#include <stdlib.h>

typedef uint16_t PIXEL;
typedef size_t INDEX;

#define FRAME_SIZE(size) size.x * size.z
#define MAP3_1(x, y, z, size) (y * FRAME_SIZE(size) + size.x * z + y)
#define GetT(x, y) (y * Nx + x) 
#define GetX(t) (t % Nx)
#define GetY(t) ((int)t / Nx)

/* The frame is a 3 Dimensional array of unsigned integers
The data is stored as a sequence of y x-z images
x and y are spatial variables, and z is a spectral band variable

(On MCU, only partial images can be loaded)
Range of each dimension: 1 - 2^16
In this case: 0 - 2^16-1 
While it is possible to translate this scale, 
The Size of an image on the final prototype is guaranteed to be 
(Nx, Ny, Nz) = (640, 512, 640)
*/
typedef struct image{
    dim3 size;
    PIXEL* data;
} image;

int InitImage(image** img_p, size_t x, size_t y, size_t z);

PIXEL GetPixel(image* hIMG, INDEX x, INDEX y, INDEX z);
PIXEL* GetFrame(image* hIMG, INDEX y);

void SetPixel(image* hIMG, INDEX x, INDEX y, INDEX z, PIXEL data);

#endif