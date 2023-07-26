#include "predictor/local_sum.h"

// ? Completed, Needs Revision
data_t FindLocalSum(image* hIMG, INDEX z, INDEX y, INDEX x)
{
    data_t val = CheckCache(z,y,x,local_sums);
    if(val != UINT16_MAX){
        return val;
    }
    
#ifdef WIDE_NEIGHBOR
    if (y > 0 &&  0 < x && x < Nx - 1)
    {
        val = SR(hIMG, z, x - 1, y) + SR(hIMG, z, x - 1, y - 1) +
               SR(hIMG, z, x, y - 1) + SR(hIMG, z, x + 1, y - 1);
    }
    else if (y == 0 && x > 0)
    {
        val = 4 * SR(hIMG, z, x - 1, y);
    }
    else if (y > 0 && x == 0)
    {
        val = 2 * (SR(hIMG, z, x, y - 1) + SR(hIMG, z, x + 1, y - 1));
    }
    else if (y > 0 && x == Nx - 1)
    {
        val = SR(hIMG, z, x - 1, y) + SR(hIMG, z, x - 1, y - 1) + 2 * SR(hIMG, z, x, y - 1);
    } 
    else if (y == 0 && x == 0){
        val = 0;
    }
#endif

#ifdef NARROW_NEIGHBOR
    if (y > 0 &&  0 < x && x < Nx - 1)
    {
        val = SR(z, GetT(x - 1, y)) + SR(z, GetT(x - 1, y - 1)) +
               SR(z, GetT(x, y - 1)) + SR(z, GetT(x + 1, y - 1));
    }
    else if (y == 0 && x > 0 && z > 0)
    {
        val = 4 * SR(z, GetT(x - 1, y));
    }
    else if (y > 0 && x == 0)
    {
        val = 2 * (SR(z, GetT(x, y - 1)) + SR_C(z, x + 1, y - 1));
    }
    else if (y > 0 && x == Nx - 1)
    {
        val = SR(z, GetT(x - 1, y)) + SR_C(z, x - 1, y - 1) + 2 * SR(z, GetT(x, y - 1));
    } else if (y == 0 && x > 0 && z == 0)
    {
        /* code */
    }
    
#endif

#ifdef WIDE_COLUMN
    if(y > 0){
        val = 4 * SR(z,y-1,x);
    }
    else if(y == 0 && x > 0){
        val = 4 * SR(z,y,x-1);
    }
#endif

#ifdef NARROW_COLUMN
    if(y > 0){
        val = 4 * SR(z,y-1,x);
    } else if (y == 0 && x > 0 && z > 0)
    {
        val = 4 * SR(z-1,y,x-1);
    } else if (y == 0 && x > 0 && z == 0)
    {
        val = 4 * Smid;
    }
#endif

    UpdateCache(z,y,x, local_sums, val);

    return val;
}