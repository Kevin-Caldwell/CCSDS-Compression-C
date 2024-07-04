#include "predictor/local_differences.h"

int32_t CentralLocalDifference(LBuf *buf, dim3 s, INDEX offz, INDEX y, INDEX x)
{
    return 4 * SR(buf, offz, y, x) - LS(buf, s, offz, y, x);
}

int32_t DirectionalLocalDifference(LBuf *buf, dim3 s, int direction)
{
    switch (direction)
    {
    case N:
        if (buf->pixel_index.y > 0)
        {
            return 4 * SR(buf, 0, -1, 0) - LS(buf, s, 0, 0, 0);
        }
        else if (buf->pixel_index.y == 0)
        {
            return 0;
        }
        break;
    case W:
        if (buf->pixel_index.x > 0 && buf->pixel_index.y > 0)
        {
            return 4 * SR(buf, 0, 0, -1) - LS(buf, s, 0, 0, 0);
        }
        else if (buf->pixel_index.x == 0 && buf->pixel_index.y > 0)
        {
            return 4 * SR(buf, 0, -1, 0) - LS(buf, s, 0, 0, 0);
        }
        else if (buf->pixel_index.y == 0)
        {
            return 0;
        }
    case NW:
        if (buf->pixel_index.x > 0 && buf->pixel_index.y > 0)
        {
            return 4 * SR(buf, 0, -1, -1) - LS(buf, s, 0, 0, 0);
        }
        else if (buf->pixel_index.x == 0 && buf->pixel_index.y > 0)
        {
            return 4 * SR(buf, 0, -1, 0) - LS(buf, s, 0, 0, 0);
        }
        else if (buf->pixel_index.y == 0)
        {
            return 0;
        }

    default:
        break;
    }
    return 0;
}

int LocalDirectionVector(LBuf *buf, dim3 s, int32_t *lDV)
{
    if (!kPredictionMode)
    {
        for (int i = N; i <= NW; i++)
        {
            lDV[i] = DLD(buf, s, i);
        }

        for (unsigned long int i = 0; i < Ps(buf->pixel_index.z); i++)
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
