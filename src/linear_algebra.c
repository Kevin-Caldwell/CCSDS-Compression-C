#include "math/linear_algebra.h"

int InitVector(int32_t **v, UINT len)
{
    // *v = (int32_t *)malloc(sizeof(int32_t) * len);

    return 0;
}

int DeleteVector(data_t *v)
{
    free(v);
}

int AddVectors(data_t *v1, data_t *v2, data_t *res, UINT size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = v1[i] + v2[i];
    }
    return 0;
}

int SubtractVectors(data_t *v1, data_t *v2, data_t *res, UINT size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = v1[i] - v2[i];
    }
    return 0;
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

int ScalarProduct(data_t *v, data_t scalar, data_t *res, UINT size)
{
    for (int i = 0; i < size; i++)
    {
        res[i] = v[i] * scalar;
    }
    return 0;
}