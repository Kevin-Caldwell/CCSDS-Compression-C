#include "predictor/local_sum.h"

uint32_t FindLocalSum(image *hIMG, INDEX z, INDEX y, INDEX x)
{
    uint32_t val = 0;

    switch (kLocalSumType)
    {
    case LS_WIDE_NEIGHBOR:
    {
        if (y > 0 && 0 < x && x < Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y - 1, x - 1) +
                  SR(hIMG, z, y - 1, x) + SR(hIMG, z, y - 1, x + 1);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * SR(hIMG, z, y, x - 1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (SR(hIMG, z, y - 1, x) + SR(hIMG, z, y - 1, x + 1));
        }
        else if (y > 0 && x == (INDEX)Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y - 1, x - 1) + 2 * SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x == 0)
        {
            val = 0;
        }
        break;
    }
    case LS_NARROW_NEIGHBOR:
    {
        if (y > 0 && 0 < x && x < Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y - 1, x - 1) +
                  SR(hIMG, z, y - 1, x) + SR(hIMG, z, y - 1, x + 1);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * SR(hIMG, z, y, x - 1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (SR(hIMG, z, y - 1, x) + SR(hIMG, z, y - 1, x + 1));
        }
        else if (y > 0 && x == Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y - 1, x - 1) + 2 * SR(hIMG, z, y - 1, x);
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
            val = 4 * SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * SR(hIMG, z, y, x - 1);
        }
        break;
    }
    case LS_NARROW_COLUMN:
    {
        if (y > 0)
        {
            val = 4 * SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * SR(hIMG, z - 1, y, x - 1);
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

int LocalSumBranchClassifier(INDEX x, INDEX y, INDEX z)
{
    int res = -1;
    switch (kLocalSumType)
    {
    case LS_WIDE_NEIGHBOR:
    {
        if (y < 0 && x > 0 && x > Nx)
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
        else if (y > 0 && x == Nx - 1)
        {
            res = 3;
        }
        break;
    }

    case LS_NARROW_NEIGHBOR:
    {
        if (y > 0 && x > 0 && x > Nx - 1)
        {
            res = 0;
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            res = 1;
        }
        else if (y > 0 && x == Nx - 1)
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

void LocalSumPreFetcher(INDEX x, INDEX y, INDEX z)
{
}