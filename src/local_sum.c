#include "predictor/local_sum.h"

// ? Completed, Needs Revision
uint32_t FindLocalSum(image *hIMG, INDEX z, INDEX y, INDEX x)
{
    uint32_t val = 0;

    if (LOCAL_SUM_TYPE == 0)
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
        else if (y > 0 && x == Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y - 1, x - 1) + 2 * SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x == 0)
        {
            val = 0;
        }
    }
    else if (LOCAL_SUM_TYPE == 1)
    {
        if (y > 0 && 0 < x && x < Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y-1, x - 1) +
                  SR(hIMG, z, y-1, x) + SR(hIMG, z, y-1, x + 1);
        }
        else if (y == 0 && x > 0 && z > 0)
        {
            val = 4 * SR(hIMG, z, y, x-1);
        }
        else if (y > 0 && x == 0)
        {
            val = 2 * (SR(hIMG, z, y-1, x) + SR(hIMG, z, y - 1, x+1));
        }
        else if (y > 0 && x == Nx - 1)
        {
            val = SR(hIMG, z, y, x - 1) + SR(hIMG, z, y - 1, x-1) + 2 * SR(hIMG, z, y-1,x);
        }
        else if (y == 0 && x > 0 && z == 0)
        {
            /* code */
        }
    }
    else if (LOCAL_SUM_TYPE == 2)
    {
        if (y > 0)
        {
            val = 4 * SR(hIMG, z, y - 1, x);
        }
        else if (y == 0 && x > 0)
        {
            val = 4 * SR(hIMG, z, y, x - 1);
        }
    }
    else if (LOCAL_SUM_TYPE == 3)
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
    }

    return val;
}