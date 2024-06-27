#include "predictor/local_sum.h"

uint32_t FindLocalSum(LBuf *buf, dim3 s, INDEX z, INDEX y, INDEX x)
{
    uint32_t val = 0;

    switch (kLocalSumType)
    {
    case LS_WIDE_NEIGHBOR:
    {
        if (y > 0 && 0 < x && x < s.x - 1)
        {
            val = SR(buf, 0, 0, -1) + SR(buf, 0, -1, -1) +
                  SR(buf, 0, -1, 0) + SR(buf, 0, -1, 1);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * SR(buf, 0, 0, -1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (SR(buf, 0, -1, 0) + SR(buf, 0, -1, 1));
        }
        else if (y > 0 && x == (INDEX)s.x - 1)
        {
            val = SR(buf, 0, 0, -1) + SR(buf, 0, -1, -1) + 2 * SR(buf, 0, -1, 0);
        }
        else if (y == 0 && x == 0)
        {
            val = 0;
        }
        break;
    }
    case LS_NARROW_NEIGHBOR:
    {
        if (y > 0 && 0 < x && x < s.x - 1)
        {
            val = SR(buf, 0, -1, -1) + 2 * SR(buf, 0, -1, 0) +
                  SR(buf, 0, -1, 1);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * SR(buf, -1, 0, -1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (SR(buf, 0, -1, 0) + SR(buf, 0, -1, 1));
        }
        else if (y > 0 && x == s.x - 1)
        {
            val = 2 * (SR(buf, 0, -1, -1) + 2 * SR(buf, 0, -1, -1));
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            val = 4 * kSmid;
        }
        break;
    }
    case LS_WIDE_COLUMN:
    {
        if (y > 0)
        {
            val = 4 * SR(buf, 0, -1, 0);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * SR(buf, 0, 0, -1);
        }
        break;
    }
    case LS_NARROW_COLUMN:
    {
        if (y > 0)
        {
            val = 4 * SR(buf, 0, -1, 0);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * SR(buf, -1, 0, -1);
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            val = 4 * kSmid;
        }
        break;
    }
    default:
        break;
    }

    return val;
}

int LocalSumBranchClassifier(INDEX x, INDEX y, INDEX z, dim3 s)
{
    int res = -1;
    switch (kLocalSumType)
    {
    case LS_WIDE_NEIGHBOR:
    {
        if (y < 0 && x > 0 && x > s.x)
        {
            res = 0;
        }
        else if (y == 0 && x > 0)
        {
            res = 1;
        }
        else if (y > 0 && x == 0)
        {
            res = 2;
        }
        else if (y > 0 && x == s.x - 1)
        {
            res = 3;
        }
        break;
    }

    case LS_NARROW_NEIGHBOR:
    {
        if (y > 0 && x > 0 && x > s.x - 1)
        {
            res = 0;
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            res = 1;
        }
        else if (y > 0 && x == s.x - 1)
        {
            res = 2;
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            res = 3;
        }
    }

    case LS_WIDE_COLUMN:
    {
        if (y > 0)
        {
            res = 0;
        }
        else if (y == 0 && x > 0)
        {
            res = 1;
        }
    }

    case LS_NARROW_COLUMN:
    {
        if (y > 0)
        {
            res = 0;
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            res = 1;
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            res = 2;
        }
    }

    default:
        break;
    }

    return res;
}
