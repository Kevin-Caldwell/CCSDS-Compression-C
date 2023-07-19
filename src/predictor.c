#include "predictor.h"

int FindLocalSum(INDEX z, INDEX y, INDEX x)
{
#ifdef WIDE_NEIGHBOR
    if (y > 0, 0 < x < Nx - 1)
    {
        return SR(z, GetT(x - 1, y)) + SR(z, GetT(x - 1, y - 1)) +
               SR(z, GetT(x, y - 1)) + SR(z, GetT(x + 1, y - 1));
    }
    else if (y == 0 && x > 0)
    {
        return 4 * SR(z, GetT(x - 1, y));
    }
    else if (y > 0 && x == 0)
    {
        return 2 * (SR(z, GetT(x, y-1) + SR(z, GetT(x+1, y-1));
    }
    else if (y > 0 && x == Nx - 1)
    {
        return SR(z, GetT(x-1, y)) + SR(z, GetT(x-1, y-1)) 
        + 2 * SR(z, GetT(x, y-1);
    }
#endif

    // TODO Implement other options: Time-saving algorithms
}

int CentralLocalDifference(INDEX x, INDEX y, INDEX z)
{
    return 4 * SR(z, GetT(x, y)) - LS(z, y, x);
}

int DirectionalLocalDifferences(INDEX x, INDEX y, INDEX z, DIRECTION d)
{
    switch (d)
    {
    case N:
        if (y > 0)
        {
            return 4 * SR(z, y, x - 1) - LS(z, y, x);
        }
        else if (y == 0)
        {
            return 0;
        }
        break;
    case W:
        if(x > 0 && y > 0){
            return 4 * SR(z,y,x-1) - LS(z, y, x);
        } else if(x == 0 && y > 0){
            return 4 * SR(z,y-1,x) - LS(z,y,x);
        } else if(y == 0){
            return 0;
        }
    case NW:
        if(x > 0 && y > 0){
            return 4 * SR(z,y-1,x-1) - LS(z, y, x);
        } else if (x == 0 && y > 0)
        {
            return 4 * SR(z,y-1,x) - LS(z,y,x);
        } else if (y == 0){
            return 0;
        }
        
    default:
        break;
    }
}

int CalculateHighResolutionSample(INDEX i)
{
    return 0;
}

int SampleRepresentative(INDEX z, INDEX t)
{
    if (t == 0)
    {
        return GetPixel(hIMG, GetX(t), GetY(t), z);
    }
}

// Spectral Band z
// Resolution Parameter THETA
// damping theta_z
// offset phi_z

int DoubleResolutionSampleRepresentative(INDEX z, INDEX t)
{
    // TODO start
    int sPrime = 0;
    int qz = 0;
    int mz_t = 0;
    int s_curve = 0;
    // TODO end

    int sampleRep = 4 * (BPOW(Theta) - damping[z]) * ((sPrime * BPOW(Omega) - SIGN(qz) * mz_t * offset[z] * BPOW(Omega - THETA))) + damping[z] * s_curve - offset[z] * BPOW(Omega + 1);
    return sampleRep / (BPOW(Omega + THETA + 1));
}

int QuantizerBinCenter(INDEX z, INDEX t)
{
    // TODO start
    int s_hat = 0;
    int q_z = 0;
    int m_t = 0;
    // TODO end

    return CLIP(s_hat + q_z * (2 * m_t + 1), Smin, Smax);
}

int DoubleResolutionPredictedSample(INDEX z, INDEX t)
{
    // TODO start
    int s_curve = 0;
    int x = 0;
    int y = 0;
    // TODO end

    if (t > 0)
    {
        return s_curve / (BPOW(Omega + 1));
    }
    else if (!t || P > 0 || z > 0)
    {
        return 2 * GetPixel(hIMG, x, y, z - 1);
    }
    else if (t == 0 && (P == 0 || Q == 0))
    {
        return 2 * Smid;
    }
}
