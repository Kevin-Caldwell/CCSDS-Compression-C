#ifndef PERLIN_H
#define PERLIN_H

#include "dst/image.h"

void GeneratePerlinImage(dim3 size, int index, int length);

void Perlin4(image *result, int cube_side);

#endif /* PERLIN_H */
