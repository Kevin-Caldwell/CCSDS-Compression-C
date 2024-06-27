#include "predictor/local_differences.h"

int32_t CentralLocalDifference(LBuf *buf, dim3 s, INDEX z, INDEX y, INDEX x)
{
    return 4 * SR(buf, z, y, x) - LS(buf, s, z, y, x);
}

int32_t DirectionalLocalDifference(LBuf *buf, dim3 s, INDEX z, INDEX y, INDEX x, int direction)
{
    switch (direction)
    {
    case N:
        if (y > 0)
        {
            return 4 * SR(buf, 0, -1, 0) - LS(buf, s, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
        break;
    case W:
        if (x > 0 && y > 0)
        {
            return 4 * SR(buf, 0, 0, -1) - LS(buf, s, z, y, x);
        }
        else if (x == 0 && y > 0)
        {
            return 4 * SR(buf, 0, -1, 0) - LS(buf, s, z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
    case NW:
        if (x > 0 && y > 0)
        {
            return 4 * SR(buf, 0, -1, -1) - LS(buf, s, z, y, x);
        }
        else if (x == 0 && y > 0)
        {
            return 4 * SR(buf, 0, -1, 0) - LS(buf, s, z, y, x);
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

int LocalDirectionVector(LBuf *buf, dim3 s, int32_t *lDV, INDEX z, INDEX y, INDEX x)
{
    if (!Hash_GetValue(&predictor_constants, "PREDICTION_MODE"))
    {
        for (int i = N; i <= NW; i++)
        {
            lDV[i] = DLD(buf, s, 0, 0, 0, i);
        }

        for (unsigned long int i = 0; i < Ps(z); i++)
        {
            lDV[i + 3] = CentralLocalDifference(buf, s, (signed int)(- i - 1), 0, 0);
        }
    }
    else
    {

        for (int i = 0; i < kC; i++)
        {
            lDV[i] = CentralLocalDifference(buf, s, - 1 - i, 0, 0);
        }
    }
    return RES_OK;
}
