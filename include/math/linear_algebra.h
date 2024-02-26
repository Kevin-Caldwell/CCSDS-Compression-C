/**
 * linear_algebra.h
 * @authors Kevin Caldwell @BrianShTsoi
 * 
 * Skeleton File for Generic Vector Operations.
 * 
 * Features
 *  Initialization
 *  Deletion
 *  Addition
 *  Subtraction
 *  Scalar Product
 *  Inner Product (Dot Product)
 * 
 * Uses
 *  Local Difference Vector
 *  Weight Vector
 * 
 * Dependencies
 *  constants.h
 *  math_functions.h 
*/


#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H
#include "constants/constants.h"
#include "math_functions.h"

typedef PIXEL data_t;


int InitVector(int32_t** v, UINT len);

int DeleteVector(data_t* v);

int AddVectors(data_t* v1, data_t* v2, data_t* res, UINT size);

int SubtractVectors(data_t* v1, data_t* v2, data_t* res, UINT size);

int64_t InnerProduct(int32_t* v1, int32_t* v2, UINT size);

int ScalarProduct(data_t* v, data_t scalar, data_t* res, UINT size);

#define AddToVector(v, other, size)  				AddVectors(v, other, v, size)
#define SubtractFromVector(v, other, size) 			SubtractVectors(v, other, v, size)
#define ScalarProduct_C(v, other, size)				ScalarProduct(v, other, v, size)


#endif /* LINEAR_ALGEBRA_H */
