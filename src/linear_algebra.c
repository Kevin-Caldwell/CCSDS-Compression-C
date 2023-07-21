#include "math/linear_algebra.h"

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

int InnerProduct(data_t* v1, data_t* v2, UINT size){
    data_t* sum = 0;
    for(int i = 0; i < size; i++){
        sum += v1[i] * v2[i];
    }
    return 0;
}


int ScalarProduct(data_t* v, data_t scalar, data_t* res, UINT size){
    for(int i = 0; i < size; i++){
        res[i] = v[i] * scalar;
    }
    return 0;
}