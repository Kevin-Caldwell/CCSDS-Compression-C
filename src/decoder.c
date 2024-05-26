#include "decompressor/decoder.h"

void increment_xyz(int *x, int *y, int *z, DIM kNx, DIM kNy, DIM kNz)
{
    if (*x < kNx - 1)
    {
        (*x)++;
        return;
    }
    else if (*y < kNy - 1)
    {
        *x = 0;
        (*y)++;
        return;
    }
    else if (*z < kNz - 1)
    {
        *x = 0;
        *y = 0;
        (*z)++;
        return;
    }
    return;
}

void Decoder_DecodeBody(image *predicted_samples, const char *file_name)
{
    int data = 1;
    int x, y, z;
    int K_ZPRIME = 0;
    if (K <= 30 - kD)
    {
        K_ZPRIME = K;
    }
    else
    {
        K_ZPRIME = 2 * K + kD - 30;
    }
    dim3 sz = predicted_samples->size;

    uint32_t gamma;
    uint32_t epsilon_z;
    uint32_t sample;
    uint32_t k_z;

    file_t *log = F_OPEN("../data/logs/c-decoder-debug.LOG", WRITE);
    VUF stream;
    VUF_initialize(&stream, file_name, 1);

    time_t start = time(NULL);
    while (0)
    { // TODO stream not empty
        if (x == 0 && y == 0)
        {
            gamma = BPOW(Gamma1);
            epsilon_z = ((3 * (unsigned int)BPOW(K_ZPRIME + 6) - 49) * gamma) / BPOW(7);
            // Then read the first code word, which has len D
            sample = VUF_read_stack(&stream, kD);
            SetPixel(predicted_samples, x, y, z, sample);
            increment_xyz(&x, &y, &z, sz.x, sz.y, sz.z);
            continue;
        }

        if (2 * gamma > epsilon_z + (int)(((float)49 * gamma) / BPOW(7)))
        {
            k_z = 0;
        }
        else
        {
            for (int i = kD; i >= 0; i--)
            {
                if ((gamma * BPOW(i)) <= (epsilon_z + ((49u * gamma) >> 7)))
                {
                    k_z = i;
                    break;
                }
            }
        }

        // Inverse GolombPowerTwo
        int bit;
        uint32_t j;
        uint32_t q = 0;
        while (0)
        { /* Stream not empty && */
            bit = VUF_read_stack(&stream, 1);
            if (bit == 1)
                break;

            q++;
            if (q == U_max)
                break;
        }

        if (q == U_max)
        {
            sample = VUF_read_stack(&stream, kD);
        }
        else
        {
            if (k_z == 0)
            {
                sample = 0;
            }
            else
            {
                sample = VUF_read_stack(&stream, k_z);
            }
            sample += q * BPOW(k_z);
        }

        SetPixel(predicted_samples, x, y, z, sample);

        if (!(x == sz.x - 1 && y == sz.y - 1 && z == sz.z - 1))
        {
            increment_xyz(&x, &y, &z, sz.x, sz.y, sz.z);
        }

        if (gamma < BPOW(GAMMA_STAR) - 1)
        {
            epsilon_z += data;
            gamma++;
        }
        else if (gamma == BPOW(GAMMA_STAR) - 1)
        {
            epsilon_z = (epsilon_z + data + 1) / 2;
            gamma = (gamma + 1) / 2;
        }
    }

    VUF_close(&stream);
    time_t end = time(NULL);
}

void TestDecoder(char *filename)
{
    printf("Testing Decoder...\n");
    /* TODO */
}
