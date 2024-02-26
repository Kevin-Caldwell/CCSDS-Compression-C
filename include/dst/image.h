/**
 * image.h
 * @authors @Kevin-Caldwell
 * 
 * Image Structure for Storing 3D bitmaps with a 
 * maximum dynamic range of 16 bits
 * 
 * Features
 *  Initialize Image
 *  Get/Set Pixels
 *  Image Compare
 *  Coordinate Transform from x,y,z to t,z
 * 
 * Uses
 *  Raw Data
 *  Predicted Image
 * 
 * Dependencies
 *  math_functions.h
 *  constants.h
 *  stdlib.h    
 * 
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "math/math_functions.h"
#include "constants/constants.h"
#include <stdlib.h>
#include "files/uhi_io.h"

#define FRAME_SIZE(size) (size.x * size.y)
#define MAP3_1(i, j, k, size) (k * FRAME_SIZE(size) + size.x * j + i)
#define GetT(x, y) (y * Nx + x) 
#define GetX(t) (t % Nx)
#define GetY(t) ((int)t / Nx)

#define S(hIMG, z,y,x) GetPixel(hIMG, x,y,z)

#if MEMORY_SAVING

#include "files/uhi_io.h"

typedef UHI image;
typedef UHI image3;

#else

/**
 * Image Stuct for storing all the contexts of a hyperspectral 
 * image in a linear array. 
 * 
 * The size member is a dim3 which contains the dimensions of 
 * the image in the format: {Nx, Ny, Nz}
 * The data member is a dynamically allocated array of PIXELs
 * arranged according to the MAP3_1 Macro defined in image.h
 * 
 * It has only been created as a testing feature. The entire 
 * hyperspectral image cannot be stored in RAM on an embedded
 * device such as the STM32H7. 
 * The UHI file structure replaces this struct when the 
 * MEMORY_SAVING feature is enabled through CMake. 
*/
typedef struct image{
    dim3 size;
    PIXEL* data;
} image, image3;

#endif

int InitImage(image* img_p, size_t x, size_t y, size_t z);

PIXEL GetPixel(image* hIMG, INDEX x, INDEX y, INDEX z);
PIXEL* GetFrame(image* hIMG, INDEX y);

void SetPixel(image* hIMG, INDEX x, INDEX y, INDEX z, PIXEL data);

int Image_Equals(image* img1, image* img2);

/**
 * Unused Struct for 2-D images.
*/
typedef struct image2{
    dim2 size;
    PIXEL* data;
} image2;


#endif /* IMAGE_H */
