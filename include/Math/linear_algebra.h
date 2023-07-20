#include "math_functions.h"

typedef int data_t;


int InitVector(data_t** v, UINT len){
    *v = (data_t*) malloc(sizeof(data_t) * len);

    return 0;
}

int DeleteVector(data_t* v){
    free(v);
}


int AddVectors(data_t* v1, data_t* v2, data_t* res, UINT size){
    for(int i = 0; i < size; i++){
        res[i] = v1[i] + v2[i];
    }
    return 0;
}

int SubtractVectors(data_t* v1, data_t* v2, data_t* res, UINT size){
    for(int i = 0; i < size; i++){
        res[i] = v1[i] - v2[i];
    }
    return 0;
}

int InnerProduct(data_t* v1, data_t* v2, data_t* res, UINT size){
    for(int i = 0; i < size; i++){
        res[i] = v1[i] * v2[i];
    }
    return 0;
}


int ScalarProduct(data_t* v, data_t scalar, data_t* res, UINT size){
    for(int i = 0; i < size; i++){
        res[i] = v[i] * scalar;
    }
    return 0;
}

#define AddToVector(v, other, size)  				AddVectors(v, other, v, size)
#define SubtractFromVector(v, other, size) 			SubtractVectors(v, other, v, size)
#define InnerProduct_C(v, other, size)				InnerProduct(v, other, v, size)
#define ScalarProduct_C(v, other, size)				ScalarProduct(v, other, v, size)

