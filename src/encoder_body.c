#include "encoder/body.h"
#include <time.h>


int32_t K = 0; // CLIP(ACCUMULATOR_INITIALIZATION_CONSTANT, 0, MIN(D-2, 14));
uint32_t U_max = (uint32_t) CLIP(UNARY_LENGTH_LIMIT, 8, 32);
uint32_t Gamma1 = 1;

GolombInt GolombPowerTwo(uint16_t j, uint16_t k)
{
    uint32_t u = 0;
    unsigned int len = 0;
    uint32_t div = j / (BPOW(k));
    if (div < U_max)
    {

        u <<= div;
        u <<= 1;
        u |= 1;
        u <<= k;
        unsigned int mask = (1 << (unsigned) k) - 1;
        u |= (j & mask);
        len = (unsigned int) (u ? (div + 1 + k) : 1);
    }
    else
    {

        u <<= UNARY_LENGTH_LIMIT;
        u <<= (uint32_t) kD;
        /*@unused@*/
        unsigned int mask = (1 << (unsigned) k) - 1; 
        u |= j;
        len = (unsigned int) (k + kD);
    }

    return (GolombInt){u, len};
}


unsigned int InitAccumulatorValue(/*@unused@*/ uint32_t z)
{
    unsigned int k_prime = (unsigned int) ((K <= 30 - kD) ? K : (2 * K + kD - 30));
    return (unsigned int) ((3 * BPOW(k_prime + 6) - 49) * Gamma1);
}

int EncodeBody(image *hIMG, const char *file_name, /*@unused@*/ const char *write_mode, int buffer_size)
{
    DIM kNx=0, kNy=0, kNz=0;
    int res = 0;
    int32_t K_ZPRIME = 0;
    if (K <= 30 - kD)
    {
        K_ZPRIME = K;
    }
    else
    {
        K_ZPRIME = 2 * K + kD - 30;
    }
    /*@unused@*/
    dim3 sz = hIMG->size;
    /*@unused@*/
    uint32_t gamma;
    /*@unused@*/
    uint32_t epsilon_z;
    /*@unused@*/
    uint32_t codeword;
    /*@unused@*/
    uint32_t k_z;

    /*@unused@*/
    file_t *log = F_OPEN("../data/logs/c-encoder-debug.LOG", WRITE);

    VUF stream = {(file_t*)0, 0, 0, 0, };
    res = VUF_initialize(&stream, file_name, buffer_size);
    long int len = 0;

    time_t start = time(NULL);
    #ifndef S_SPLINT_S
    for (int z = 0; z < sz.z; z++)
    {
        for (int y = 0; y < sz.y; y++)
        {
            for (int x = 0; x < sz.x; x++)
            {

                uint16_t data = GetPixel(hIMG, x, y, z);
                if (x == 0 && y == 0)
                {
                    gamma = BPOW(Gamma1);
                    epsilon_z = ((3 * (unsigned int)BPOW(K_ZPRIME + 6) - 49) * gamma) / BPOW(7);
                    VUF_append(&stream, data, kD);
                    len += kD;
                    fprintf(log, "%u:%d,%d\n", data, kD, k_z);
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

                GolombInt res = GolombPowerTwo(data, k_z);
                len += res.length;
                fprintf(log, "(%d, %d, %d) %u:%d, %d, %d, %d\n", x, y, z, res.data, res.length, k_z, gamma, epsilon_z);
                VUF_append(&stream, res.data, res.length);

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
        }
        time_t time_elapsed = time(NULL) - start;
        time_t time_left = time_elapsed * (kNz - z - 1) / (z + 1);
        printf("\rEncoded %d/%d of Image. (%ld seconds Elapsed, %ld seconds Left)", (int)(z + 1), (int)hIMG->size.x, time_elapsed, time_left);
        fflush(stdout);
    }
    #endif
    res = VUF_close(&stream);

    time_t end = time(NULL);
    printf("\n%d seconds for image Encoding.\n", (int)(end - start));
    printf("%ld / %ld bytes=%2.f%% Compression\n", len / 8, (long)((float)kNx * kNy * kNz * kD / 8), (double) (1 - ((float)len / ((float)kNx * kNy * kNz * kD))) * 100);

    return 0;
}