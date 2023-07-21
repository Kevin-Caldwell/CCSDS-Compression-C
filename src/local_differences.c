#include "predictor/local_differences.h"

// ? Completed
int CentralLocalDifference(image* hIMG, INDEX z, INDEX y, INDEX x)
{
    return 4 * SR(hIMG, z, x, y) - LS(hIMG, z, y, x);
}

// ? Completed
int DirectionalLocalDifference(image* hIMG, INDEX z, INDEX y, INDEX x, int direction)
{
    switch (direction)
    {
    case N:
        if (y > 0)
        {
            return 4 * SR(hIMG, z, y, x - 1) - LS(hIMG, z, y, x);
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

// ? Completed
int LocalDirectionVector(image* hIMG, data_t **local_direction_vector, INDEX z, INDEX y, INDEX x)
{
    InitVector(local_direction_vector, C(z));
    data_t* lDV = *local_direction_vector;
#ifndef REDUCED_PREDICTION_MODE

    for (int i = N; i <= NW; i++)
    {
        lDV[i] = DLD(hIMG, z, y, x, i);
    }

    for (int i = 3; i < C(z); i++)
    {
        lDV[i] = CentralLocalDifference(hIMG, z-i-2,y,x);
    }

#else

    for (int i = 0; i < C(z); i++)
    {
        lDV[i] = CentralLocalDifference(z - 1 - i, y, x);
    }
#endif
}

// ? Completed
data_t PredictedCentralLocalDifference(image* hIMG, INDEX z, INDEX y, INDEX x){
    data_t* weight_vector;
    data_t* local_direction_vector;
    
    LocalDirectionVector(hIMG, &local_direction_vector, z,y,x);
    InitializeWeights(&weight_vector, z,y,x);

    data_t pcld = InnerProduct(weight_vector, local_direction_vector, C(z));

    free(weight_vector);
    free(local_direction_vector);

    return pcld;
}