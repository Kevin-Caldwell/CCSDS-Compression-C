#include "predictor.h"

// ! Old Functions, Not in Use anymore
// ! New versions found in predictor folder

/* int SampleRepresentative(INDEX z, INDEX t)
{
    if (t == 0)
    {
        return GetPixel(hIMG, GetX(t), GetY(t), z);
    }

    return 0;

}
 */
// Spectral Band z
// Resolution Parameter THETA
// damping theta_z
// offset phi_z

/* int DoubleResolutionSampleRepresentative(INDEX z, INDEX t)
{
    // TODO start
    int sPrime = 0;
    int qz = 0;
    int mz_t = 0;
    int s_curve = 0;
    // TODO end

    int sampleRep = 4 * (BPOW(THETA) - damping[z]) * ((sPrime * BPOW(Omega) - SIGN(qz) * mz_t * offset[z] * BPOW(Omega - THETA))) + damping[z] * s_curve - offset[z] * BPOW(Omega + 1);
    return sampleRep / (BPOW(Omega + THETA + 1));
} */


// // TODO
/* int QuantizerBinCenter(INDEX z, INDEX t)
{
    // TODO start
    int s_hat = 0;
    int q_z = 0;
    int m_t = 0;
    // TODO end

    return CLIP(s_hat + q_z * (2 * m_t + 1), kSmin, Smax);
} */

