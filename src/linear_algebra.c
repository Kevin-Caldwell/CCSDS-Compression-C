#include "math/linear_algebra.h"

error_t InitVector(int32_t **v, UINT len)
{
    return RES_OK;
}

error_t DeleteVector(data_t *v)
{
    return RES_OK;
}

error_t AddVectors(data_t *v1, data_t *v2, data_t *res, UINT size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = v1[i] + v2[i];
    }
    return RES_OK;
}

error_t SubtractVectors(data_t *v1, data_t *v2, data_t *res, UINT size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = v1[i] - v2[i];
    }
    return RES_OK;
}

int64_t InnerProduct(int32_t *v1, int32_t *v2, UINT size)
{
    int64_t sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += (int64_t)v1[i] * v2[i];
    }
    return sum;
}

error_t ScalarProduct(data_t *v, data_t scalar, data_t *res, UINT size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = v[i] * scalar;
    }
    return 0;
}