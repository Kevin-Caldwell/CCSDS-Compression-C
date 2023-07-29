#ifndef SYNTHETIC_IMAGE_GENERATOR
#define SYNTHETIC_IMAGE_GENERATOR

#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "math/image.h"

#define INIT_ARRAY(T, count) (T*) malloc(sizeof(T) * count)

int WithinRect2(dim2 point, dim2 top_left, dim2 bottom_right);

int WithinRect3(dim3 point, dim3 top_left, dim3 bottom_right);

int SpreadPoint2(dim2** points, dim2 bounds, UINT point_count);

int SpreadPoint3(dim3** points, dim3 bounds, UINT point_count);

int GenerateVoronoiFlat2D(image2* result, UINT sample_points);

int GenerateVoronoiFlat3DNaive(image3* result, UINT sample_points);

int GenerateVoronoiFlat3DLocal(image3* result, UINT sample_points);

#endif /* SYNTHETIC_IMAGE_GENERATOR */
