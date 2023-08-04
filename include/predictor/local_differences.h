#ifndef LOCAL_DIFFERENCES
#define LOCAL_DIFFERENCES

#include "constants/constants.h"
#include "math/linear_algebra.h"
#include "math/math_functions.h"
#include "predictor/local_sum.h"
#include "predictor/sample_representative.h"
#include "predictor/weights.h"

#define Ps(z) MIN(z, P)

#ifdef REDUCED_PREDICTION_MODE
#define C(z) (unsigned int) Ps(z)
#else
#define C(z) (unsigned int) Ps(z) + 3
#endif

enum DIRECTION { N = 0, W, NW };

#define DLD(hIMG, z,y,x,d)    DirectionalLocalDifference(hIMG, z,y,x,d)
#define DLD_N(hIMG, z,y,x)    DirectionalLocalDifference(hIMG, z,y,x,N)
#define DLD_W(hIMG, z,y,x)    DirectionalLocalDifference(hIMG, z,y,x,W)
#define DLD_NW(hIMG, z,y,x)   DirectionalLocalDifference(hIMG, z,y,x,NW)

data_t CentralLocalDifference(image* hIMG, INDEX z, INDEX y, INDEX x);

data_t DirectionalLocalDifference(image* hIMG, INDEX z, INDEX y, INDEX x, int direction);

int LocalDirectionVector(image* hIMG, data_t** local_direction_vector, INDEX z, INDEX y, INDEX x);

data_t PredictedCentralLocalDifference(image* hIMG, INDEX z, INDEX y, INDEX x);

#endif /* LOCAL_DIFFERENCES */
