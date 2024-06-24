#ifndef PERLIN_H
#define PERLIN_H

#include "files/csv-io.h"
#include <math.h>
#include <string.h>
#include <time.h>

void GeneratePerlinImage(dim3 size, int index, int length);

void Perlin4(image *result, int cube_side);

#endif /* PERLIN_H */
