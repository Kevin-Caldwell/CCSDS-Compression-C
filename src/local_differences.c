#include "predictor/local_differences.h"

int32_t CentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x)
{
    return 4 * SR(hIMG, z, y, x) - LS(hIMG, z, y, x);
}

int32_t DirectionalLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x, int direction)
{
    switch (direction)
    {
    case N:
        if (y > 0)
        {
            return 4 * SR(hIMG, z, y - 1, x) - LS(hIMG, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
        break;
    case W:
        if (x > 0 && y > 0)
        {
            return 4 * SR(hIMG, z, y, x - 1) - LS(hIMG, z, y, x);
        }
        else if (x == 0 && y > 0)
        {
            return 4 * SR(hIMG, z, y - 1, x) - LS(hIMG, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
    case NW:
        if (x > 0 && y > 0)
        {
            return 4 * SR(hIMG, z, y - 1, x - 1) - LS(hIMG, z, y, x);
        }
        else if (x == 0 && y > 0)
        {
            return 4 * SR(hIMG, z, y - 1, x) - LS(hIMG, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }

    default:
        break;
    }
    return 0;
}

int LocalDirectionVector(image *hIMG, int32_t **local_direction_vector, INDEX z, INDEX y, INDEX x)
{
    InitVector(local_direction_vector, C);
    int32_t *lDV = *local_direction_vector;

    if (!Hash_GetValue(&predictor_constants, "PREDICTION_MODE"))
    {
        for (int i = N; i <= NW; i++)
        {
            lDV[i] = DLD(hIMG, z, y, x, i);
        }

        for (unsigned long int i = 0; i < Ps(z); i++)
        {
            lDV[i + 3] = CentralLocalDifference(hIMG, (signed int)(z - i - 1), y, x);
        }
    }
    else
    {

        for (int i = 0; i < C; i++)
        {
            lDV[i] = CentralLocalDifference(hIMG, z - 1 - i, y, x);
        }
    }
}

int64_t PredictedCentralLocalDifference(image *hIMG, INDEX z, INDEX y, INDEX x)
{
    int64_t pcld;
    if (x == 0 && y == 0)
    {
        return 0;
    }

    int32_t *weight_vector = global_cache->weights;
    int32_t *local_direction_vector;

    LocalDirectionVector(hIMG, &local_direction_vector, z, y, x);
    pcld = InnerProduct(weight_vector, local_direction_vector, C);

    free(local_direction_vector);

    return pcld;
}