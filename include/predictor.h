#ifndef PREDICTOR
#define PREDICTOR

#include <stdlib.h>
#include "constants.h"
#include "math/math_functions.h"
#include "math/linear_algebra.h"
#include "image.h"

#include "predictor/quantizer.h"

/*  s_squiggle_z(t)         Double-Resolution Predicted Sample Value
    s_hat_z(t)              Predicted Sample Value
    C_z                     Number of Local Difference Values used for prediction at each sample in band z
    sigma_z,y,x             Local Sum
    d_z,y,x                 Central Local Difference
    d^(N/W/NW)_z,y,x        Directional Local Differences
    d^^_z(t)                Predicted Central Local Difference
    U_z(t)                  Local Difference Vector
    Omega                   Resolution
    omega                   Weight Value
    W_z(t)                  Weight Vector
    Lambda_z                Weight Initialization Vector
    s_upcurve_z(t)          High Resolution Predicted Sample Value
    s_~_z(t)                Double Resolution Predicted Sample Value
    s_hat_z(t)              Predicted Sample Value

 */

#define Ps(z) MIN(z, P)

#ifdef REDUCED_PREDICTION_MODE
#define C(z) (unsigned int) Ps(z)
#else
#define C(z) (unsigned int) Ps(z) + 3
#endif

#define T(x, y) (y * Nx + x) 

#define DAMPING_MIN 0
#define DAMPING_MAX BPOW(THETA) - 1

// Offset 0 for Lossless
#define OFFSET_MIN 0
#define OFFSET_MAX BPOW(THETA) - 1


// typedef to allow for future change
typedef uint32_t weight_t;


//enum DIRECTION { N = 0, W, NW };

int RunPredictor(image* hIMG, image* result);

/// Per Band Weight Initialization
/// Will be updated with each pass
/* int InitWeightVector(INDEX z, INDEX t)
{
    if (weight_vector)
    {
        free(weight_vector);
    }

    weight_vector = (weight_t *)malloc(sizeof(weight_t) * C((signed) z));
#ifdef REDUCED_PREDICTION_MODE
    weight_vector[0] = 7 * BPOW(Omega - 3);
    for (INDEX i = 1; i < Ps(z); i++)
    {
        weight_vector[i] = weight_vector[i - 1] / 8; // TODO: Change to Bitwise
    }
#else
    weight_vector[0] = 0;
    weight_vector[1] = 0;
    weight_vector[2] = 0;

    weight_vector[3] = 7 * BPOW(Omega - 3);

    for (INDEX i = 4; i < C((signed) z); i++)
    {
        weight_vector[i] = weight_vector[i - 1] / 8; // TODO: Change to bitwise operator
    }
#endif

    return 0;
} */

#endif /* PREDICTOR */
