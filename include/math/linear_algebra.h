#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H
#include "constants/constants.h"
#include "math_functions.h"

typedef PIXEL data_t;


int InitVector(data_t** v, UINT len);

int DeleteVector(data_t* v);

int AddVectors(data_t* v1, data_t* v2, data_t* res, UINT size);

int SubtractVectors(data_t* v1, data_t* v2, data_t* res, UINT size);

int InnerProduct(data_t* v1, data_t* v2, UINT size);

int ScalarProduct(data_t* v, data_t scalar, data_t* res, UINT size);

#define AddToVector(v, other, size)  				AddVectors(v, other, v, size)
#define SubtractFromVector(v, other, size) 			SubtractVectors(v, other, v, size)
#define ScalarProduct_C(v, other, size)				ScalarProduct(v, other, v, size)


#endif /* LINEAR_ALGEBRA_H */
