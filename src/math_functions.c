#include "math/math_functions.h"

UINT Euclidian2(dim2 pt1, dim2 pt2){
    return (UINT) sqrtf((double) (SQ(pt1.x - pt2.x) + SQ(pt1.y - pt2.y)));
}

UINT Euclidian3(dim3 pt1, dim3 pt2){
    return (UINT) ((SQ(pt1.x - pt2.x) + SQ(pt1.y - pt2.y) + SQ(pt1.z - pt2.z)));
}

UINT Manhattan2(dim2 pt1, dim2 pt2){
    return (UINT) (abs(pt1.x - pt2.x) + abs(pt1.y - pt2.y));
}

UINT Manhattan3(dim3 pt1, dim3 pt2){
    return (UINT) (abs(pt1.x - pt2.x) + abs(pt1.y - pt2.y) + abs(pt1.z - pt2.z));
}